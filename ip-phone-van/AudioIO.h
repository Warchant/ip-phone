///////////////////////////////////////////////////////////
//  AudioIO.h
//  Implementation of the Class AudioIO
//  Created on:      05-Oct-2013 16:54:08
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_)
#define EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_

#include <QtMultimedia/QMultimedia>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudio>
#include <QFileDialog>
#include <QObject>
#include <QFile>
#include <string>
#include "wav.h"
/**
 * @class AudioIO
 */
class AudioIO
{

public:
	AudioIO();
	virtual ~AudioIO();

    WAV *wav_header;

	virtual void stateChanged(QAudio::State newState);

    std::string getPath() const;
    void setPath(const std::string &value);

protected:
    std::string path;

    QAudioFormat format;
    /**
     * @brief File to read/write.
	 */
	QFile sourceFile;

};
#endif // !defined(EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_)
