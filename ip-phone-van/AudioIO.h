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
#include <QtMultimedia/QAudioOutput>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>
#include <QObject>
#include <QBuffer>
#include <QFile>
#include <string>
#include "wav.h"
#include <fstream>

/**
 * @class AudioIO
 */
class AudioIO : public QObject
{
    Q_OBJECT

public:

    AudioIO();
	virtual ~AudioIO();

    WAV *wav_header;

    /**
     * @brief Getter for path;
     * @return this->path
     */
    QString getPath() const;
    /**
     * @brief Setter for path;
     * @param path
     */
    void setPath(const QString &value);

    void startPlayback();
    void pausePlayback();
    void stopPlayback ();

    bool isOpen();

    bool copyFileTo(QString newpath);

private:

    QBuffer *buffer;

    QAudioOutput* out;

    QString path;

    QAudioFormat format;
    /**
     * @brief File to read/write.
	 */
	QFile sourceFile;


};
#endif // !defined(EA_156433C8_98E7_4462_AB16_1CEF25E5C1A0__INCLUDED_)
