///////////////////////////////////////////////////////////
//  AudioOutput.cpp
//  Implementation of the Class AudioOutput
//  Created on:      05-Oct-2013 16:54:19
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "AudioOutput.h"


AudioOutput::AudioOutput(){
}



AudioOutput::~AudioOutput(){
    delete this->audio;
}





void AudioOutput::pausePlayback(){

}


void AudioOutput::startPlayback(){
/* TODO
 *    sourceFile.open(QIODevice::ReadOnly);

    std::map<std::string,std::string> wav = wav_header->getHeader();

    // Set up the format, eg.
    format.setSampleRate  ( str2int(wav["sampleRate"]) );
    format.setChannelCount( str2int(wav["numChannels"]));
    format.setSampleSize  ( str2int(wav["sampleRate"]) );
    format.setCodec       ( "audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(bps == 8 ? QAudioFormat::UnSignedInt : QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
   if (!info.isFormatSupported(format)) {
       printf("Raw audio format not supported by backend, cannot play audio.");
       return;
   }

   audio = new QAudioOutput(format, 0);
   //connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
   audio->start(&sourceFile);
   */
}


void AudioOutput::stateChanged(QAudio::State newState){

}


void AudioOutput::stopPlayback(){
    audio->stop();
}
