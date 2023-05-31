#include "mbed.h"
#include <vector>

extern BusOut ledrow1;
extern BusOut ledrow2;
extern Serial pc;

class musicplayer {
    public:
        musicplayer(PinName pin);
        void selectSong(int song);
    private:
        void play(vector<float> notes, int beatmap, int tempo, float speed);
        void playHarryPotter(int beatmap);
        void playStarWars(int beatmap);
        void playFurElise(int beatmap);
        PwmOut _Device;
};
