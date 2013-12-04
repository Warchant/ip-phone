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


const unsigned char *WAV::getOriginalData() const
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
    this->header_data["subChunk2Size"] = int2str  (p_header->WAVE_D.subChunk2Size);
    this->header_data["d_subChunkID"]  = clearName(p_header->WAVE_D.subChunkID,4);
}

WAV::~WAV()
{
    delete p_header;
}

void WAV::open(QString path)
{
    FILE *pFile = fopen(path.toLocal8Bit(),"rb");

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
            fseek(pFile, sizeof(short), SEEK_CUR);
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

        // Allocate memory for data
        this->data = new unsigned char[p_header->WAVE_D.subChunk2Size + 1];
        this->data[p_header->WAVE_D.subChunk2Size] = 0;

        // Read in the sound data into the soundData variable
        if (!fread(data, p_header->WAVE_D.subChunk2Size, 1, pFile))
        {
            throw FILE_DATA_LOAD_FAIL;
        }

        // Close file
        fclose(pFile);
        this->state = true;

        // replace 0 => 2
        for(int i=0;i<p_header->WAVE_D.subChunk2Size;i++)
        {
            this->data[i] = this->data[i]==0?2:this->data[i];
        }

        // save original data
        this->original_data = new unsigned char [p_header->WAVE_D.subChunk2Size];
        memcpy(this->original_data, this->data, p_header->WAVE_D.subChunk2Size);
        // fill std::map
        this->fillHeaderData();
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
        this->data[i] = (unsigned char)(y[i]);
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
