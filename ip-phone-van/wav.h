#ifndef WAV_H
#define WAV_H

#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

// exceptions
enum WAV_EXCEPTION{
    FILE_MISSING,
    FILE_BAD_HEADER
};

class WAV
{
public:
    /*
     * @param path Input path to the wav file.
     */
    WAV(std::string path);
    ~WAV();

    //std::vector <HEADER.bits_per_sample> readn(const int n, const int offset = 0);
private:

    /*
     * @brief This function opens the WAVE file.
     * @throws FILE_MISSING if file is missing.
     * @throws FILE_BAD_HEADER if input is not WAVE file.
     * @param path Path to the WAVE file to open it.
     */
    void open(std::string path);

    /*
     * @brief Header of WAVE file. Read about it: @link https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
     */
    struct HEADER
    {
        char chunk_id[4];           // RIFF
        int chunk_size;             // chunk_size + 8 = fileSize;
        char format[4];             // WAVE
        char subchunk1_id[4];
        int subchunk1_size;
        short int audio_format;
        short int num_channels;     // Mono(1)/Stereo(2)
        int sample_rate;			// sample_rate denotes the sampling rate.
        int byte_rate;              // byte rate 8000/11025/22050/44100 etc
        short int block_align;
        short int bits_per_sample;  // bps: 8/16 Bit
        char subchunk2_id[4];
        int subchunk2_size;			// subchunk2_size denotes the number of samples.
    };

    /*
     * @brief Header of WAVE file.
     */
    HEADER *p_header;

};

#endif // WAV_H
