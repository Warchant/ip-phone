///////////////////////////////////////////////////////////
//  AudioOutput.cpp
//  Implementation of the Class AudioOutput
//  Created on:      05-Oct-2013 16:54:19
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "AudioOutput.h"


AudioOutput::AudioOutput(){
    this->sourceFile.open(QIODevice::ReadOnly);
    //this->format.setSampleRate();
}



AudioOutput::~AudioOutput(){
    delete this->audio;
}





void AudioOutput::pausePlayback(){

}


void AudioOutput::startPlayback(){

}


void AudioOutput::stateChanged(QAudio::State newState){

}


void AudioOutput::stopPlayback(){

}
