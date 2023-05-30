#include "mbed.h"
#include "musicplayer.h"
#include <vector>

enum noteNames {C, Cs, D, Eb, E, F, Fs, G, Gs, A, Bb, B};
float NT[12][9] = { 
    {16.35}, {17.32}, {18.35}, {19.45}, {20.60}, {21.83},    
    {23.12}, {24.5}, {25.96}, {27.5}, {29.14}, {30.87}
};

vector<float> harryPotter, starWars;

musicplayer::musicplayer(PinName pin): _Device(pin) { 
    for (int i = 0; i < 12; i++) {
        for (int j = 1; j < 9; j++) {
            NT[i][j] = NT[i][j-1] * 2;
        }
    }
}

void musicplayer::selectSong(int song) {
    switch(song) {
        case 1:
            playHarryPotter();
            break;
        case 2:
            playStarWars();
            break;
        default:
            break;
    }
}

void musicplayer::play(vector<float> notes, int tempo, float speed) {
    int divider = 0, noteDuration = 0;
    int wholenote = 60000 * 4 / tempo;
    for (int i = 0; i < notes.size(); i+=2) {
        divider = notes[i+1];
        if(divider > 0) {
            noteDuration = wholenote/divider;
        }
        else if(divider < 0) {
            noteDuration = wholenote/abs(divider);
            noteDuration *= 1.5;
        }
        _Device.period(1 / (4*notes[i]));
        _Device = 0.5;
        ThisThread::sleep_for(noteDuration * speed);
    }
}

void musicplayer::playHarryPotter() {
    harryPotter = {
        0, 2, NT[D][3], 4,
        NT[G][3], -4, NT[Bb][3], 8, NT[A][3], 4,
        NT[G][3], 2, NT[D][4], 4,
        NT[C][4], -2,
        NT[A][3], -2,
        NT[G][3], 4, NT[Bb][3], 8, NT[A][3], 4,
        NT[F][3], 2, NT[Gs][3], 4,
        NT[D][3], -1,
        NT[D][3], 4,
        NT[G][3], -4, NT[Bb][3], 8, NT[A][3], 4,
        NT[G][3], 2, NT[D][4], 4,
        NT[F][4], 2, NT[E][4], 4,
        NT[Eb][4], 2, NT[B][3], 4,
        NT[Eb][4], -4, NT[D][4], 8, NT[Cs][4], 4,
        NT[Cs][3], 2, NT[B][3], 4,
        NT[G][3], -1,
        NT[Bb][3], 4,
        NT[D][4], 2, NT[Bb][3], 4,
        NT[D][4], 2, NT[Bb][3], 4,
        NT[Eb][4], 2, NT[D][4], 4,
        NT[Cs][4], 2, NT[A][3], 4,
        NT[Bb][3], -4, NT[D][4], 8, NT[Cs][4], 4,
        NT[Cs][3], 2, NT[D][3], 4,
        NT[D][4], -1,
        0, 4, NT[Bb][3], 4,
        NT[D][4], 2, NT[Bb][3], 4,
        NT[D][4], 2, NT[Bb][3], 4,
        NT[F][4], 2, NT[E][4], 4,
        NT[Eb][4], 2, NT[B][3], 4,
        NT[Eb][4], -4, NT[D][4], 8, NT[Cs][4], 4,
        NT[Cs][3], 2, NT[Bb][3], 4,
        NT[G][3], -1
    };
    play(harryPotter, 157, 0.1);
}

void musicplayer::playStarWars() {
    starWars = {
        NT[A][1], 8, NT[A][1], 8, NT[A][1], 8,
        NT[F][1], 4, NT[C][2], 4, NT[A][1], 8,
        NT[F][1], 4, NT[C][2], 4, NT[A][1], 8,
        NT[E][2], 8, NT[E][2], 8, NT[E][2], 8,
        NT[F][2], 4, NT[C][2], 4, NT[Gs][1], 8,
        NT[F][1], 4, NT[C][2], 4, NT[A][1], 16,
        NT[A][2], 8, NT[A][1], 4, NT[A][1], 4,
        NT[A][2], 8, NT[Gs][2], 4, NT[G][2], 4,
        NT[Fs][2], 2, NT[F][2], 2, NT[Fs][2], 2,
        NT[Bb][1], 2, NT[Eb][2], 8, NT[D][2], 4,
        NT[Cs][2], 4, NT[C][2], 2, NT[B][1], 2,
        NT[C][2], 2, NT[F][1], 2, NT[Gs][1], 8,
        NT[F][1], 4, NT[Gs][1], 4, NT[C][2], 8,
        NT[A][1], 4, NT[C][2], 4, NT[E][2], 16,
        NT[A][2], 8, NT[A][1], 4, NT[A][1], 4,
        NT[A][2], 8, NT[Gs][2], 4, NT[G][2], 4,
        NT[Fs][2], 2, NT[F][2], 2, NT[Fs][2], 2,
        NT[Bb][1], 2, NT[Eb][2], 8, NT[D][2], 4,
        NT[Cs][2], 4
    };
    play(starWars, 91, 0.1);
}