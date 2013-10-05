#include "wav.h"

WAV::WAV(std::string path)
{
    p_header = new HEADER();

    try
    {
        this->open(path);
    }
    catch (WAV_EXCEPTION &e)
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
        }
    }
}

std::string WAV::getPath() const
{
    return path;
}

WAV::WAV()
{
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
        // read wav header
        fread(p_header,1,sizeof(HEADER),pFile);

        // is is wav file? if not -- throw FILE_BAD_HEADER.
        if(strncmp(p_header->chunk_id,"RIFF",4) || strncmp(p_header->format,"WAVE",4))
        {
            throw FILE_BAD_HEADER;
        }
    }
    else
    {
        throw FILE_MISSING;
    }
}
