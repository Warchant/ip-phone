///////////////////////////////////////////////////////////
// WAV.h
// Implementation of the Class WAV
// Created on: 05-Oct-2013 18:51:42
// Original author: Bogdan Vaneev warchantua@gmail.com
///////////////////////////////////////////////////////////

#if !defined(EA_9D02C5A1_1D02_4287_8FFE_606E2687AEFF__INCLUDED_)
#define EA_9D02C5A1_1D02_4287_8FFE_606E2687AEFF__INCLUDED_

#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <QVector>
#include <QString>
#include <QTextCodec>
#include "functions.h"
#include <QDebug>
#include <QFile>


class WAV
{
public:
    // exceptions
    enum EXCEPTION{
         FILE_MISSING,
         FILE_BAD_HEADER,
         FILE_DATA_LOAD_FAIL
    };

    /*
     * @param path Input path to the wav file.
     */
    WAV(QString path);
    WAV();
    ~WAV();

    /*
     * @brief Getter for p_header
     */
    const std::map<std::string, std::string> getHeader() const;
    const unsigned char *getOriginalData() const;

    unsigned char *data;

    void convert2data(QVector<double> y);

    int getHeaderSize();

private:

    std::string clearName(const char *a, int size);

    const int header_size;
    unsigned char *original_data;
    void fillHeaderData();

    std::map <std::string, std::string> header_data;


    /*
    * @brief This function opens the WAVE file.
    * @param path Path to the WAVE file to open it.
    */
    void open(QString path);
    operator bool();


    /*
    * Struct that holds the RIFF data of the Wave file.
    * The RIFF data is the meta data information that holds,
    * the ID, size and format of the wave file
    */
    struct RIFF_Header {
    char chunkID[4];
    int chunkSize;//size not including chunkSize or chunkID
    char format[4];
    };

    /*
    * Struct to hold fmt subchunk data for WAVE files.
    */
    struct WAVE_Format {
    char  subChunkID[4];
    int  subChunkSize;
    short audioFormat;
    short numChannels;
    int  sampleRate;
    int  byteRate;
    short blockAlign;
    short bitsPerSample;
    };

    /*
    * Struct to hold the data of the wave file
    */
    struct WAVE_Data {
    char subChunkID[4]; //should contain the word data
    int subChunk2Size; //Stores the size of the data block
    };

    /*
    * @brief Header of WAVE file. Read about it: @link https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
    */
    struct HEADER
    {
    RIFF_Header RIFF;
    WAVE_Format WAVE_F;
    WAVE_Data WAVE_D;
    };

    /*
    * @brief Header of WAVE file.
    */
    HEADER *p_header;
    bool state;
};

#endif // !defined(EA_9D02C5A1_1D02_4287_8FFE_606E2687AEFF__INCLUDED_)
