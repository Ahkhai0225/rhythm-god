#include "musicplayer.h"
#include "mbed.h"
#include "LM75B.h"
#include <vector>
#include "light.h"
#include "switch.h"

BusOut display(p9,p10,p12,p13,p14,p15,p16);
LM75B tempSensor(p28, p27);

enum noteNames { C, Cs, D, Eb, E, F, Fs, G, Gs, A, Bb, B };
float NT[12][9] = {
    {16.35}, {17.32}, {18.35}, {19.45}, {20.60}, {21.83},
    {23.12}, {24.5},  {25.96}, {27.5},  {29.14}, {30.87}
};

const int segmentValues[4] = {
    0b0000000,  // - (Start Game)
    0b0000110,  // 1
    0b1011011,  // 2
    0b1001111,  // 3
};


vector<float> harryPotter, furElise, pinkPanther;

musicplayer::musicplayer(PinName pin) : _Device(pin) {
    for (int i = 0; i < 12; i++) {
        for (int j = 1; j < 9; j++) {
            NT[i][j] = NT[i][j - 1] * 2;
        }
    }
}

void musicplayer::selectSong(int song) {
    switch (song) {
        case 1:
            playPinkPanther(song);
            break;
        case 2:
            playHarryPotter(song);
            break;
        case 3:
            playFurElise(song);
            break;
        default:
            break;
    }
}

void musicplayer::timerStart() {
    int countdown = 3;
        while (countdown>0){
            display = segmentValues[countdown];
            countdown = countdown-1;
            wait_us(1000000);
        }
        display = segmentValues[countdown];
}

void musicplayer::play(vector<float> notes, int beatmap, int tempo, float speed) {
    score = 0;
    int divider = 0, noteDuration = 0;
    int wholenote = 60000 * 4 / tempo;
    int a = 0;
    Timer timer;
    for (int i = 0; i < notes.size(); i += 2) {
        if(tempSensor.read() >= 36) {
            lcd.cls();
            lcd.locate(0, 3);
            lcd.printf("OVERHEAT!!!!!!");
            _Device.period(0);
            exit(1);
        }
        divider = notes[i + 1];
        if (divider > 0) {
            noteDuration = wholenote / divider;
        } else if (divider < 0) {
            noteDuration = wholenote / abs(divider);
            noteDuration *= 1.5;
        }
        _Device.period(1 / (4 * notes[i]));
        _Device = 0.5;
        songChoice(beatmap, i);
        switchIndicator(noteDuration, speed);
        defaultled();
    }
}

void musicplayer::playPinkPanther(int beatmap) {
    
    pinkPanther = {
        0,         2,   0,         4,   0,         8,   NT[Eb][4], 8,
        NT[E][4],  -4,  0,         8,   NT[Fs][4], 8,   NT[G][4],  -4,
        0,         8,   NT[Eb][4], 8,   NT[E][4],  -8,  NT[Fs][4], 8,
        NT[G][4],  -8,  NT[C][5],  8,   NT[B][4],  -8,  NT[E][4],  8,
        NT[G][4],  -8,  NT[B][4],  8,   NT[Bb][4], 2,   NT[A][4],  -16,
        NT[G][4],  -16, NT[E][4],  -16, NT[D][4],  -16, NT[E][4],  2,
        0,         4,   0,         8,   NT[Eb][4], 4,
        NT[E][4],  -4,  0,         8,   NT[Fs][4], 8,   NT[G][4],  -4,
        0,         8,   NT[Eb][4], 8,   NT[E][4],  -8,  NT[Fs][4], 8,
        NT[G][4],  -8,  NT[C][5],  8,   NT[B][4],  -8,  NT[G][4],  8,
        NT[B][4],  -8,  NT[E][5],  8,   NT[Eb][5], 1,   NT[D][5],  2,
        0,         4,   0,         8,   NT[Eb][4], 8,   NT[E][4],  -4,
        0,         8,   NT[Fs][4], 8,   NT[G][4],  -4,  0,         8,
        NT[Eb][4], 8,   NT[E][4],  -8,  NT[Fs][4], 8,   NT[G][4],  -8,
        NT[C][5],  8,   NT[B][4],  -8,  NT[E][4],  8,   NT[G][4],  -8,
        NT[B][4],  8,
        NT[Bb][4], 2,   NT[A][4],  -16, NT[G][4],  -16, NT[E][4],  -16,
        NT[D][4],  -16, NT[E][4],  -4,  0,         4,   0,         4,
        NT[E][5],  -8,  NT[D][5],  8,   NT[B][4],  -8,  NT[A][4],  8,
        NT[G][4],  -8,  NT[E][4],  -8,  NT[Bb][4], 16,  NT[A][4],  -8,
        NT[Bb][4], 16,  NT[A][4],  -8,  NT[Bb][4], 16,  NT[A][4],  -8,
        NT[Bb][4], 16,  NT[A][4],  -8,  NT[G][4],  -16, NT[E][4],  -16,
        NT[D][4],  -16, NT[E][4],  16,  NT[E][4],  16,  NT[E][4],  2,
        0, 4
    };
    play(pinkPanther, 1, 120, 0.1);
}

void musicplayer::playHarryPotter(int beatmap) {
    harryPotter = {
        0,         2,  0,         2,  NT[D][3],  4,  NT[G][3],  -4, NT[Bb][3], 8,
        NT[A][3],  4,  NT[G][3],  2,  NT[D][4],  4,  NT[C][4],  -2, NT[A][3],  -2,
        NT[G][3],  4,  NT[Bb][3], 8,  NT[A][3],  4,  NT[F][3],  2,  NT[Gs][3], 4,
        NT[D][3],  -1, NT[D][3],  4,  NT[G][3],  -4, NT[Bb][3], 8,  NT[A][3],  4,
        NT[G][3],  2,  NT[D][4],  4,  NT[F][4],  2,  NT[E][4],  4,  NT[Eb][4], 2,
        NT[B][3],  4,  NT[Eb][4], -4, NT[D][4],  8,  NT[Cs][4], 4,  NT[Cs][3], 2,
        NT[B][3],  4,  NT[G][3],  -1, NT[Bb][3], 4,  NT[D][4],  2,  NT[Bb][3], 4,
        NT[D][4],  2,  NT[Bb][3], 4,  NT[Eb][4], 2,  NT[D][4],  4,  NT[Cs][4], 2,
        NT[A][3],  4,  NT[Bb][3], -4, NT[D][4],  8,  NT[Cs][4], 4,  NT[Cs][3], 2,
        NT[D][3],  4,  NT[D][4],  -1, 0,         4,  NT[Bb][3], 4,  NT[D][4],  2,
        NT[Bb][3], 4,  NT[D][4],  2,  NT[Bb][3], 4,  NT[F][4],  2,  NT[E][4],  4,
        NT[Eb][4], 2,  NT[B][3],  4,  NT[Eb][4], -4, NT[D][4],  8,  NT[Cs][4], 4,
        NT[Cs][3], 2,  NT[Bb][3], 4,  NT[G][3],  -1, 0,         4
    };
    play(harryPotter, 2, 157, 0.1);
}

void musicplayer::playFurElise(int beatmap) {
    furElise = {
        0, 16, 0, 16, NT[E][5],  16, NT[Eb][5], 16, NT[E][5],  16, NT[Eb][5], 16,
        NT[E][5],  16, NT[B][4],  16, NT[D][5],  16, NT[C][5],  16,
        NT[A][4],  -8, NT[C][4],  16, NT[E][4],  16, NT[A][4],  16,
        NT[B][4],  -8, NT[E][4],  16, NT[Gs][4], 16, NT[B][4],  16,
        NT[C][5],  8,  0,         16, NT[E][4],  16, NT[E][5],  16,
        NT[Eb][5], 16, NT[E][5],  16, NT[Eb][5], 16, NT[E][5],  16,
        NT[B][4],  16, NT[D][5],  16, NT[C][5],  16, NT[A][4],  -8,
        NT[C][4],  16, NT[E][4],  16, NT[A][4],  16, NT[B][4],  -8,
        NT[E][4],  16, NT[C][5],  16, NT[B][4],  16, NT[A][4],  4,
        0,         8,  NT[E][5],  16, NT[Eb][5], 16, NT[E][5],  16,
        NT[Eb][5], 16, NT[E][5],  16, NT[B][4],  16, NT[D][5],  16,
        NT[C][5],  16, NT[A][4],  -8, NT[C][4],  16, NT[E][4],  16,
        NT[A][4],  16, NT[B][4],  -8, NT[E][4],  16, NT[Gs][4], 16,
        NT[B][4],  16, NT[C][5],  8,  0,         16, NT[E][4],  16,
        NT[E][5],  16, NT[Eb][5], 16, NT[E][5],  16, NT[Eb][5], 16,
        NT[E][5],  16, NT[B][4],  16, NT[D][5],  16, NT[C][5],  16,
        NT[A][4],  -8, NT[C][4],  16, NT[E][4],  16, NT[A][4],  16,
        NT[B][4],  -8, NT[E][4],  16, NT[C][5],  16, NT[B][4],  16,
        NT[A][4],  8,  0,         16, NT[B][4],  16, NT[C][5],  16,
        NT[D][5],  16, NT[E][5],  -8, NT[G][4],  16, NT[F][5],  16,
        NT[E][5],  16, NT[D][5],  -8, NT[F][4],  16, NT[E][5],  16,
        NT[D][5],  16, NT[C][5],  -8, NT[E][4],  16, NT[D][5],  16,
        NT[C][5],  16, NT[B][4],  8,  0,         16, NT[E][4],  16,
        NT[E][5],  16, 0,         16, 0,         16, NT[E][5],  16,
        NT[E][6],  16, 0,         16, 0,         16, NT[Eb][5], 16,
        NT[E][5],  16, 0,         16, 0,         16, NT[Eb][5], 16,
        NT[E][5],  16, NT[Eb][5], 16, NT[E][5],  16, NT[Eb][5], 16,
        NT[E][5],  16, NT[B][4],  16, NT[D][5],  16, NT[C][5],  16,
        NT[A][4],  8,  0,         16, NT[C][4],  16, NT[E][4],  16,
        NT[A][4],  16, NT[B][4],  8,  0,         16, NT[E][4],  16,
        NT[Gs][4], 16, NT[B][4],  16, NT[C][5],  8,  0,         16,
        NT[E][4],  16, NT[E][5],  16, NT[Eb][5], 16, NT[E][5],  16,
        NT[Eb][5], 16, NT[E][5],  16, NT[B][4],  16, NT[D][5],  16,
        NT[C][5],  16, NT[A][4],  8,  0,         16, NT[C][4],  16,
        NT[E][4],  16, NT[A][4],  16, NT[B][4],  8,  0,         16,
        NT[E][4],  16, NT[C][5],  16, NT[B][4],  16, NT[A][4],  8,
        0,         16
    };
    play(furElise, 3, 80, 0.2);
}