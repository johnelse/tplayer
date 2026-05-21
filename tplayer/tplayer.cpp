#include "Wavetable.h"
#include "WavetablePlayer.h"

#include <argparse/argparse.hpp>
#include <miniaudio/miniaudio.h>

#include <iostream>
#include <memory>
#include <stddef.h>

static constexpr size_t DEFAULT_FRAMES = 2048;

void playWavetable(const std::string &path, size_t frames)
{
    auto wavetable = std::make_shared<Wavetable>(path, frames);
    WavetablePlayer player(wavetable);
    player.start();

    printf("Press any key to stop...");
    getchar();

    player.stop();
}

int main(int argc, char ** argv)
{
    argparse::ArgumentParser parser("tplayer");

    parser.add_argument("--frames")
        .help("The number of frames per waveform")
        .default_value(DEFAULT_FRAMES)
        .scan<'u', size_t>();

    parser.add_argument("path")
        .help("The path to the wavetable file to open");

    try
    {
        parser.parse_args(argc, argv);
    }
    catch (const std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    const std::string path = parser.get<std::string>("path");
    const size_t frames = parser.get<size_t>("frames");
    playWavetable(path, frames);

    return 0;
}
