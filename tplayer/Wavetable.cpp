#include "Wavetable.h"

Wavetable::Wavetable(const std::string &path, ma_uint64 framesPerWave)
    : framesPerWave(framesPerWave)
    , currentWave(0)
    , valid(false)
{
    ma_result result = ma_decoder_init_file(path.data(), NULL, &decoder);
    if (result != MA_SUCCESS)
        return;

    ma_uint64 totalFrames;
    result = ma_decoder_get_length_in_pcm_frames(&decoder, &totalFrames);
    if (result != MA_SUCCESS)
        return;

    if (totalFrames % framesPerWave)
        return;

    valid = true;
}

Wavetable::~Wavetable()
{
    ma_decoder_uninit(&decoder);
}

bool Wavetable::isValid() const
{
    return valid;
}

ma_format Wavetable::getOutputFormat() const
{
    return decoder.outputFormat;
}

ma_uint32 Wavetable::getOutputChannels() const
{
    return decoder.outputChannels;
}

ma_uint32 Wavetable::getSampleRate() const
{
    return decoder.outputSampleRate;
}

size_t Wavetable::read(void *out, ma_uint64 frames)
{
    const ma_uint64 waveStart = currentWave * framesPerWave;
    const ma_uint64 waveEnd = waveStart + framesPerWave;
    ma_uint64 cursor, framesToRead, read = 0;

    ma_result result = ma_decoder_get_cursor_in_pcm_frames(&decoder, &cursor);
    if (result != MA_SUCCESS)
        return read;

    if (cursor >= waveEnd)
    {
        result = ma_decoder_seek_to_pcm_frame(&decoder, waveStart);
        if (result != MA_SUCCESS)
            return read;

        cursor = waveStart;
    }

    framesToRead = waveEnd - cursor;
    ma_decoder_read_pcm_frames(&decoder, out, framesToRead, &read);

    return read;
}
