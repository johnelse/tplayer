add_executable(tplayer
    ../libs/miniaudio/miniaudio.c
    tplayer.cpp
    Wavetable.cpp
    WavetablePlayer.cpp)

target_include_directories(tplayer PRIVATE "../libs")
