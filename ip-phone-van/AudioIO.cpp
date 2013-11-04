///////////////////////////////////////////////////////////
//  AudioIO.cpp
//  Implementation of the Class AudioIO
//  Created on:      05-Oct-2013 16:54:08
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#include "AudioIO.h"
#define TEMP_WAV_PATH "./temp_buffer"

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

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
      QMessageBox warning;
      warning.setText(tr("Raw audio format not supported by backend, cannot play audio."));
      warning.exec();

      delete this->wav_header;
      this->wav_header = new WAV();

      return;
    }
}


void AudioIO::startRecording(int sampleRate, int channels, int bps)
{
    format.setSampleRate  ( sampleRate);
    format.setChannelCount( channels);
    format.setSampleSize  ( bps );
    format.setCodec       ( "audio/pcm" );
    format.setByteOrder   ( QAudioFormat::LittleEndian );
    format.setSampleType  ( bps == 8 ? QAudioFormat::UnSignedInt : QAudioFormat::SignedInt );

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        QMessageBox warning;
        warning.setText(tr("Default format not supported, trying to use the nearest."));
        warning.exec();
        format = info.nearestFormat(format);
    }

    sourceFile.setFileName(TEMP_WAV_PATH);
    if(!sourceFile.open( QIODevice::WriteOnly | QIODevice::Truncate ))
    {
        printf("bad\n");
    }

    in = new QAudioInput(format, this);
    connect(in, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleInputStateChanged(QAudio::State)));

    in->start(&sourceFile);
}


void AudioIO::pausePlayback(){
    out->stop();
}


void AudioIO::startPlayback(){
    if(!sourceFile.isOpen())
        sourceFile.open(QIODevice::ReadOnly);
    out = new QAudioOutput(format, this);
    out->start(&sourceFile);
    connect(out, SIGNAL(stateChanged(QAudio::State)), SLOT(handleOutputStateChanged(QAudio::State)));
}


void AudioIO::stopRecording()
{
    delete in;
    sourceFile.close();

}


void AudioIO::stopPlayback(){
    pausePlayback();
    delete out;
    sourceFile.close();
}


bool AudioIO::isOpen()
{
    return sourceFile.isOpen();
}

void AudioIO::addWavHeader()
{

}

/*
 * TODO
 */
void AudioIO::handleOutputStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            stopPlayback();
            break;

        case QAudio::StoppedState:
            // Stopped for other reasons
            if (out->error() != QAudio::NoError) {
                // Error handling
            }
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}

/*
 * TODO
 */
void AudioIO::handleInputStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::StoppedState:
            if (in->error() != QAudio::NoError) {
                // Error handling
            } else {
                // Finished recording
            }
            break;

        case QAudio::ActiveState:
            // Started recording - read from IO device
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}
