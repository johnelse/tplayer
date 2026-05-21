#include <miniaudio/miniaudio.h>

#include <memory>

class Wavetable;

class WavetablePlayer
{
public:
    WavetablePlayer(std::shared_ptr<Wavetable> wavetable);
    ~WavetablePlayer();

    bool isValid() const;

    bool start();
    bool stop();

private:
    std::shared_ptr<Wavetable> wavetable;
    bool valid;
    ma_device device;
};
