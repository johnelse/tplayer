add_executable(tplayer
    ../libs/miniaudio/miniaudio.c
    tplayer.cpp)

target_include_directories(tplayer PRIVATE "../libs")
