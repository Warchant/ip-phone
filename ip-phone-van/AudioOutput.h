///////////////////////////////////////////////////////////
//  AudioOutput.h
//  Implementation of the Class AudioOutput
//  Created on:      05-Oct-2013 16:54:19
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_A6B0520D_42BE_4af2_AC18_06DF6508ADAF__INCLUDED_)
#define EA_A6B0520D_42BE_4af2_AC18_06DF6508ADAF__INCLUDED_

#include "AudioIO.h"

/**
 * @class AudioOutput
 * @brief This class uses to playback media file.
 */
class AudioOutput : public AudioIO
{

public:
	AudioOutput();
	virtual ~AudioOutput();

	void pausePlayback();
	void startPlayback();
	virtual void stateChanged(QAudio::State newState);
	void stopPlayback();

private:
	QAudioOutput* audio;

};
#endif // !defined(EA_A6B0520D_42BE_4af2_AC18_06DF6508ADAF__INCLUDED_)
