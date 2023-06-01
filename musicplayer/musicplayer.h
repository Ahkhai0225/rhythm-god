#include "mbed.h"
#include <vector>

extern BusOut ledrow1;
extern BusOut ledrow2;
extern Serial pc;
extern int scoree;

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
