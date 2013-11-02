///////////////////////////////////////////////////////////
//  AudioIO.h
//  Implementation of the Class AudioIO
//  Created on:      05-Oct-2013 16:54:08
//  Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_)
#define EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_

#include <QPushButton>
#include <QtMultimedia/QMultimedia>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>
#include <QFileDialog>
#include <QObject>
#include <QFile>
#include <string>
#include "wav.h"

/**
 * @class AudioIO
 */
class AudioIO : public QObject
{
    Q_OBJECT
private slots:

    void handleStateChanged(QAudio::State newState);

public:

    AudioIO();
	virtual ~AudioIO();

    WAV *wav_header;

    /**
     * @brief Getter for path;
     * @return this->path
     */
    std::string getPath() const;
    /**
     * @brief Setter for path;
     * @param std::string path
     */
    void setPath(const std::string &value);

    void startRecording();
    void stopRecording();

    void pausePlayback();
    void startPlayback();
    void stopPlayback ();

    bool isOpen();

    QAudioOutput* out;
    QAudioOutput* in;

private:

    std::string path;

    QAudioFormat format;
    /**
     * @brief File to read/write.
	 */
	QFile sourceFile;


};
#endif // !defined(EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_)
