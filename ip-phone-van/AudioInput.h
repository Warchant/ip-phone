///////////////////////////////////////////////////////////
//  AudioInput.h
//  Implementation of the Class AudioInput
//  Created on:      05-Oct-2013 16:54:14
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_851064DC_F84C_43c5_8E2B_31141C653E35__INCLUDED_)
#define EA_851064DC_F84C_43c5_8E2B_31141C653E35__INCLUDED_

#include "AudioIO.h"

/**
 * @class AudioInput
 * @brief This class uses to record and save media file.
 */
class AudioInput : public AudioIO
{

public:
	AudioInput();
	virtual ~AudioInput();

	void startRecording();
	virtual void stateChanged(QAudio::State newState);
	void stopRecording();

private:
	/**
	 * @brief Input device manager.
	 */
	QAudioInput * audio;

};
#endif // !defined(EA_851064DC_F84C_43c5_8E2B_31141C653E35__INCLUDED_)
