#include <miniaudio/miniaudio.h>

#include <atomic>
#include <string>

class wavetable
{
public:
    wavetable(const std::string &path, ma_uint64 framesPerWave);
    ~wavetable();

    bool isValid() const;
    size_t read(void *out, ma_uint64 frames);

private:
    ma_uint64 framesPerWave;
    ma_uint64 totalFrames;
    std::atomic<size_t> currentWave;
    bool valid;
    ma_decoder decoder;
};
