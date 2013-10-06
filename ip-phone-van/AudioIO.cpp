///////////////////////////////////////////////////////////
//  AudioIO.cpp
//  Implementation of the Class AudioIO
//  Created on:      05-Oct-2013 16:54:08
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "AudioIO.h"


AudioIO::AudioIO(){

}



AudioIO::~AudioIO(){

}

std::string AudioIO::getPath() const
{
    return path;
}

void AudioIO::setPath(const std::string &value)
{
    path = value;
}


void AudioIO::stateChanged(QAudio::State newState){

}
