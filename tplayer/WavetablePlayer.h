#include <miniaudio/miniaudio.h>

#include <memory>

class Wavetable;

class WavetablePlayer
{
public:
    WavetablePlayer(std::shared_ptr<Wavetable> wavetable);
    ~WavetablePlayer();

    bool isValid() const;

private:
    std::shared_ptr<Wavetable> wavetable;
    bool valid;
    ma_device device;
};
