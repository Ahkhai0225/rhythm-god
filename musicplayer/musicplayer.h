#include "mbed.h"
#include <vector>

extern Serial pc;

class musicplayer {
    public:
        musicplayer(PinName pin);
        void selectSong(int song);
    private:
        void play(vector<float> notes, int beatmap, int tempo, float speed);
        void playPinkPanther(int beatmap);
        void playHarryPotter(int beatmap);
        void playFurElise(int beatmap);
        PwmOut _Device;
};
