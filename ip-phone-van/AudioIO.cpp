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
    sourceFile.close();
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

    std::map<std::string,std::string> wav = wav_header->getHeader();
    // Set up the format, eg.
    int bps = str2int(wav["bitsPerSample"]);

    format.setSampleRate  ( str2int(wav["sampleRate"]) );
    format.setChannelCount( str2int(wav["numChannels"]) );
    format.setSampleSize  ( bps );
    format.setCodec       ( "audio/pcm" );
    format.setByteOrder   ( QAudioFormat::LittleEndian );
    format.setSampleType  ( bps == 8 ? QAudioFormat::UnSignedInt : QAudioFormat::SignedInt );
    /*
     * TODO: connect signal to slot
     */
    //connect(out,SIGNAL(outputStateChanged(QAudio::State)),this, SLOT(finishedPlayback(QAudio::State)));

}



void AudioIO::pausePlayback(){
    out->stop();
}


void AudioIO::startPlayback(){
    if(!sourceFile.isOpen())
        sourceFile.open(QIODevice::ReadOnly);
    out = new QAudioOutput(format);
    out->start(&sourceFile);
}


void AudioIO::stopPlayback(){
    delete out;
    sourceFile.close();
}

bool AudioIO::isOpened()
{
    return sourceFile.isOpen();
}

void AudioIO::finishedPlayback(QAudio::State newState)
{
    if (newState == QAudio::IdleState) {
        pausePlayback();
        stopPlayback();
    }
}


void AudioIO::outputStateChanged(QAudio::State newState)
{
switch (newState) {
    case QAudio::StoppedState:
        if (out->error() != QAudio::NoError) {
            printf("Something bad with audio stopping\n");
        } else {
            pausePlayback();
            stopPlayback();
        }
    break;
    }
}
