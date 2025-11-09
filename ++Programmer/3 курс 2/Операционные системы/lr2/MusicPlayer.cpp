#include <iostream>
#include "MusicList.h"

int main() {
    MusicList list;
    list.addTrack("Track 1");
    list.addTrack("Track 2");
    list.addTrack("Track 3");
    list.play();
    return 0;
}
