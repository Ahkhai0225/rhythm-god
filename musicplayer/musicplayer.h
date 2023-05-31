#include "mbed.h"
#include <vector>

extern BusOut ledrow1;
extern BusOut ledrow2;

class musicplayer {
    public:
        musicplayer(PinName pin);
        void selectSong(int song);
    private:
        void play(vector<float> notes, int song, int tempo, float speed);
        void playHarryPotter();
        void playStarWars();
        void playFurElise();
        PwmOut _Device;
};
