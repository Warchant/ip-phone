///////////////////////////////////////////////////////////
//  WAV.cpp
//  Implementation of the Class WAV
//  Created on:      05-Oct-2013 18:51:42
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "wav.h"

WAV::WAV(QString path) : header_size(sizeof(HEADER))
{
    this->state = false;
    p_header = new HEADER();
    this->open(path);
}

WAV::WAV() : header_size(sizeof(HEADER))
{
    this->p_header = new HEADER();
}


const std::map<std::string, std::string> WAV::getHeader() const
{
    return this->header_data;
}


const packet *WAV::getOriginalData() const
{
    return this->original_data;
}


void WAV::fillHeaderData()
{
    // RIFF chunk
    this->header_data["chunkID"]       = clearName(p_header->RIFF.chunkID,4);
    this->header_data["chunkSize"]     = int2str  (p_header->RIFF.chunkSize);
    this->header_data["format"]        = clearName(p_header->RIFF.format,4);
    // WAVE_FORMAT chunk

    this->header_data["audioFormat"]   = int2str(p_header->WAVE_F.audioFormat);
    this->header_data["bitsPerSample"] = int2str(p_header->WAVE_F.bitsPerSample);
    this->header_data["blockAlign"]    = int2str(p_header->WAVE_F.blockAlign);
    this->header_data["byteRate"]      = int2str(p_header->WAVE_F.byteRate);
    this->header_data["numChannels"]   = int2str(p_header->WAVE_F.numChannels);
    this->header_data["sampleRate"]    = int2str(p_header->WAVE_F.sampleRate);
    this->header_data["f_subChunkID"]  = clearName(p_header->WAVE_F.subChunkID,4);
    this->header_data["subChunkSize"]  = int2str  (p_header->WAVE_F.subChunkSize);
    // WAVE_DATA chunk
    this->header_data["subChunk2Size"] = int2str  (p_header->WAVE_D.subChunk2Size );
    this->header_data["d_subChunkID"]  = clearName(p_header->WAVE_D.subChunkID,4);
}

WAV::~WAV()
{
    //delete p_header;
}


void WAV::open(QString path)
{

    pFile = fopen(path.toLocal8Bit(),"rb");

    if(pFile!=NULL) // if file is exists
    {
        fread(&p_header->RIFF, sizeof(p_header->RIFF), 1, pFile);
        //check for RIFF and WAVE tag in memeory
        if ((p_header->RIFF.chunkID[0] != 'R' ||
             p_header->RIFF.chunkID[1] != 'I' ||
             p_header->RIFF.chunkID[2] != 'F' ||
             p_header->RIFF.chunkID[3] != 'F') ||
            (p_header->RIFF.format[0] != 'W' ||
             p_header->RIFF.format[1] != 'A' ||
             p_header->RIFF.format[2] != 'V' ||
             p_header->RIFF.format[3] != 'E'))
        {
             throw FILE_BAD_HEADER;
        }

        //Read in the 2nd chunk for the wave info
        fread(&p_header->WAVE_F, sizeof(p_header->WAVE_F), 1, pFile);
        //check for fmt tag in memory
        if (p_header->WAVE_F.subChunkID[0] != 'f' ||
            p_header->WAVE_F.subChunkID[1] != 'm' ||
            p_header->WAVE_F.subChunkID[2] != 't' ||
            p_header->WAVE_F.subChunkID[3] != ' ')
        {
            throw FILE_BAD_HEADER;
        }

        //check for extra parameters;
        if (p_header->WAVE_F.subChunkSize > 16)
        {
            char d[4];
            bool read;
            do
            {
                read = fread(&d,sizeof(char)*4,1,pFile);
                fseek(pFile,-3,SEEK_CUR);
                this->header_size+=1;
            }while(read && (d[0]!='d' ||
                            d[1]!='a' ||
                            d[2]!='t' ||
                            d[3]!='a' ));
            fseek(pFile,-1,SEEK_CUR);
            header_size-=1;
        }

        //Read in the the last byte of data before the sound file
        fread(&p_header->WAVE_D, sizeof(p_header->WAVE_D), 1, pFile);
        //check for data tag in memory
        if (p_header->WAVE_D.subChunkID[0] != 'd' ||
            p_header->WAVE_D.subChunkID[1] != 'a' ||
            p_header->WAVE_D.subChunkID[2] != 't' ||
            p_header->WAVE_D.subChunkID[3] != 'a')
        {
            throw FILE_BAD_HEADER;
        }

        int  bps = p_header->WAVE_F.bitsPerSample;
             bps = bps !=8 && bps !=16 ? 8 : bps;
             p_header->WAVE_F.bitsPerSample = bps;


        // Read in the sound data into the soundData variable
        this->bytedata = new unsigned char [p_header->WAVE_D.subChunk2Size + 1];
        this->bytedata[p_header->WAVE_D.subChunk2Size] = STOP_SYMBOL; // STOP symbol
        if(!fread(bytedata, p_header->WAVE_D.subChunk2Size, 1, pFile))
        {
            throw FILE_DATA_LOAD_FAIL;
        }

        int size = bps == 8 ? p_header->WAVE_D.subChunk2Size :
                              p_header->WAVE_D.subChunk2Size/2;

        this->data = new packet[size];

        if(bps == 16)
        {
            // convert unsigned char* bytedata array into packet* data;
            for(int i=0; i<size;i++)
            {
                data[i] = twoCharToInt(bytedata[2*i+1],bytedata[2*i]);
                this->data[i] = this->data[i]==0?2:this->data[i]; // replace 0 => 2
            }
        }
        else
        {
            for(int i=0; i < p_header->WAVE_D.subChunk2Size; i++)
            {
                data[i] = bytedata[i];
                this->data[i] = this->data[i]==0?2:this->data[i]; // replace 0 => 2
            }
        }

        for(int i=0; i< p_header->WAVE_D.subChunk2Size; i++)
        {
            this->bytedata[i] = this->bytedata[i]==0?2:this->bytedata[i]; // replace 0 => 2
        }

        // Close file
        fclose(pFile);
        this->state = true;

        // save original data
        this->original_data = new packet [size];
        memcpy(this->original_data, this->data, sizeof(packet) * (size));

        // fill std::map
        p_header->WAVE_D.subChunk2Size = size;
        this->fillHeaderData();
        /*
        if(p_header->WAVE_F.bitsPerSample != 8)
        {
            throw FILE_HEADER_NOT8BPS;
        }
        */
    }
    else
    {
        throw FILE_MISSING;
    }
}


WAV::operator bool(){
	return this->state;
}


void WAV::convert2data(QVector<double> y)
{
    for(int i=0;i<y.size();i++)
    {
        this->data[i] = (packet)(y[i]);
        this->data[i] = this->data[i] == 0 ? 2 : this->data[i];

    }

    if(p_header->WAVE_F.bitsPerSample == 8)
    {
        for(int i=0; i<y.size();i++)
        {
            this->bytedata[i] = this->data[i];
        }
    }
    else if(p_header->WAVE_F.bitsPerSample == 16)
    {
        for(int i=0; i<p_header->WAVE_D.subChunk2Size; i++)
        {
            if(data[i]!=PLACEHOLDER)
            {
                unsigned char * ch = intToTwoChar(data[i]);
                this->bytedata[2*i+1] = ch[0] == 0 || ch[0] == 1 ? 2 : ch[0];
                this->bytedata[2*i]   = ch[1] == 0 || ch[1] == 1 ? 2 : ch[1];
                delete [] ch;
            }
            else
            {
                bytedata[2*i+1] = 1;
                bytedata[2*i]   = 1;
            }
        }
    }
}

int WAV::getHeaderSize()
{
    return this->header_size;
}


std::string WAV::clearName(const char *a, int size)
{
    std::string cor = a;
    cor.resize(size);
    cor+='\0';
    return cor;
}
