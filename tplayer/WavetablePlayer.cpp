#include "WavetablePlayer.h"

#include "Wavetable.h"

namespace
{
    void dataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
    {
        if (Wavetable *wavetable = static_cast<Wavetable *>(pDevice->pUserData))
        {
            wavetable->read(pOutput, frameCount);
        }
    }
}

WavetablePlayer::WavetablePlayer(std::shared_ptr<Wavetable> wavetable)
    : wavetable(wavetable)
    , valid(false)
{
    if (!wavetable)
        return;

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = wavetable->getOutputFormat();
    config.playback.channels = wavetable->getOutputChannels();
    config.sampleRate        = wavetable->getSampleRate();
    config.dataCallback      = dataCallback;
    config.pUserData         = wavetable.get();

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS)
        return;

    valid = true;
}

WavetablePlayer::~WavetablePlayer()
{
    ma_device_uninit(&device);
}

bool WavetablePlayer::isValid() const
{
    return valid;
}
