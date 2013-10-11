///////////////////////////////////////////////////////////
//  AudioIO.cpp
//  Implementation of the Class AudioIO
//  Created on:      05-Oct-2013 16:54:08
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "AudioIO.h"


AudioIO::AudioIO(){
    this->wav_header = new WAV();
}



AudioIO::~AudioIO(){
    delete this->wav_header;
}


std::string AudioIO::getPath() const
{
    return path;
}


void AudioIO::setPath(const std::string &value)
{
    delete this->wav_header;
    path = value;
    this->wav_header = new WAV(this->path);
    this->sourceFile.setFileName(value.c_str());
}


void AudioIO::stateChanged(QAudio::State newState){

}
