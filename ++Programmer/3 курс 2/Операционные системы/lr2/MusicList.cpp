#include <iostream>
#include <vector>
#include "MusicList.h"

void MusicList::addTrack(const std::string& trackName)
{
    tracks.push_back(trackName);
}

void MusicList::play() {
    std::cout << "Playing music tracks:" << std::endl;
    for (const auto& track : tracks)
    {
        std::cout << "- " << track << std::endl;
    }
}

void MusicList::stop() {
    std::cout << "Stopped playing music." << std::endl;
}
