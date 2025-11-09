#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <string>
#include <vector>

class MusicList
{
    public:
        void addTrack(const std::string& trackName);
        void play();
        void stop();
    private:
        std::vector<std::string> tracks;
};

#endif // MUSICLIST_H
