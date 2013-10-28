///////////////////////////////////////////////////////////
//  WAV.cpp
//  Implementation of the Class WAV
//  Created on:      05-Oct-2013 18:51:42
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "WAV.h"

WAV::WAV(std::string path)
{
    this->state = false;
    p_header = new HEADER();
    try
    {
        this->open(path);
    }
    catch (WAV::EXCEPTION &e)
    {
        switch(e)
        {
            case FILE_MISSING:
            {
                printf("wav file is missing\n");
                break;
            }
            case FILE_BAD_HEADER:
            {
                printf("it is not wav file\n");
                break;
            }
            case FILE_DATA_LOAD_FAIL:
            {
                printf("cant't load file data\n");
                break;
            }
        }
    }
}

WAV::WAV()
{
    this->p_header = new HEADER();
}

WAV::~WAV()
{
    delete p_header;
}

void WAV::open(std::string path)
{
    FILE *pFile = fopen(path.c_str(),"rb");;

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

        //Allocate memory for data
        this->data = new unsigned char[p_header->WAVE_D.subChunk2Size];

        // Read in the sound data into the soundData variable
        if (!fread(data, p_header->WAVE_D.subChunk2Size, 1, pFile))
        {
            throw FILE_DATA_LOAD_FAIL;
        }

        // Close file
        fclose(pFile);
        this->state = true;
    }
    else
    {
        throw FILE_MISSING;
    }
}



WAV::HEADER *WAV::getHeader()
{
    return this->p_header;
}
