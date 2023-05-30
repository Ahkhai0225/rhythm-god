#include "mbed.h"
#include <vector>

class musicplayer {
    public:
        musicplayer(PinName pin);
        void selectSong(int song);
    private:
        void play(vector<float> notes, int tempo, float speed);
        void playHarryPotter();
        void playStarWars();
        PwmOut _Device;
};
