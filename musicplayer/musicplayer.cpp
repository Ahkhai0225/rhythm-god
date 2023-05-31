#include "mbed.h"
#include "musicplayer.h"
#include <vector>

BusOut ledrow1(p30, p29, p28);
BusOut ledrow2(p27, p22, p21);
BusOut ledrow3(p20, p18, p17);

enum noteNames {C, Cs, D, Eb, E, F, Fs, G, Gs, A, Bb, B};
float NT[12][9] = { 
    {16.35}, {17.32}, {18.35}, {19.45}, {20.60}, {21.83},    
    {23.12}, {24.5}, {25.96}, {27.5}, {29.14}, {30.87}
};

float harryPotterled[] = {
    0b000, 0b000, 0b100, 0b010, 0b001, 0b010, 0b100, 0b001, 0b100, 0b010, 0b001, 0b100, 0b010, 0b100, 0b001, 0b010, 
    0b001, 0b100, 0b010, 0b100, 0b010, 0b100, 0b001, 0b100, 0b010, 0b100, 0b001, 0b100, 0b010, 0b100, 0b100, 0b001,
    0b010, 0b100, 0b001, 0b010, 0b100, 0b010, 0b100, 0b001, 0b100, 0b010, 0b100, 0b001, 0b001, 0b010, 0b100, 0b000, 
    0b010, 0b100, 0b001, 0b100, 0b010, 0b100, 0b001, 0b100, 0b010, 0b010, 0b100, 0b001, 0b100, 0b010, 0b100 
};

vector<float> harryPotter, starWars, furElise;

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
            playHarryPotter(song);
            break;
        case 2:
            playStarWars(song);
            break;
        case 3:
            playFurElise(song);
            break;
        default:
            break;
    }
}

void musicplayer::play(vector<float> notes, int beatmap, int tempo, float speed) {
    int divider = 0, noteDuration = 0;
    int wholenote = 60000 * 4 / tempo;
    for (int i = 0; i < notes.size(); i+=2) {
        pc.printf("%f\t", notes[i]);
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
        ledrow1 = harryPotterled[i/2 + 2];
        ledrow2 = harryPotterled[i/2 + 1];
        ledrow3 = harryPotterled[i/2];
        ThisThread::sleep_for(noteDuration * speed);
        ledrow1 = 0000;
        ledrow2 = 0000;
        ledrow3 = 0000;
    }
}

void musicplayer::playHarryPotter(int beatmap) {
    harryPotter = {
        0, 2, 0, 2, NT[D][3], 4,
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
        NT[G][3], -1, 0, 4
    };
    play(harryPotter, beatmap, 157, 0.1);
}

void musicplayer::playStarWars(int beatmap) {
    starWars = {
        NT[A][1], 8, NT[A][1], 8, NT[A][1], 8,
        NT[F][1], 2, NT[C][2], 2, NT[A][1], 8,
        NT[F][1], 8, NT[C][2], 8, NT[A][1], 2,
        NT[E][2], 4, NT[E][2], 8, NT[E][2], 8,
        NT[F][2], 8, NT[C][2], 2, NT[Gs][1], 4,
        NT[F][1], 8, NT[C][2], 8, NT[A][1], 8,
        NT[A][2], 2, NT[A][1], 8, NT[A][1], 8,
        NT[A][2], 8, NT[Gs][2], 2, NT[G][2], 2,
        NT[Fs][2], 8, NT[F][2], 8, NT[Fs][2], 8,
        NT[Bb][1], 2, NT[Eb][2], 4, NT[D][2], 8,
        NT[Cs][2], 8, NT[C][2], 8, NT[B][1], 2, 
        NT[C][2], 4, NT[F][1], 8, NT[Gs][1], 8,
        NT[F][1], 8, NT[Gs][1], 2, NT[C][2], -8,
        NT[A][1], 16, NT[C][2], -4, NT[E][2], 8,
        NT[A][2], 8, NT[A][1], 8, NT[A][1], 8,
        NT[A][2], 8, NT[Gs][2], 8, NT[G][2], 8,
        NT[Fs][2], 8, NT[F][2], 4, NT[Fs][2], 8,
        NT[Bb][1], 4, NT[Eb][2], -8, NT[D][2], 16,
        NT[Cs][2], -4
    };
    play(starWars, beatmap, 91, 0.1);
}

void musicplayer::playFurElise(int beatmap) {
    pc.printf("Hey Im in fur elise");
    furElise = {
        NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], -8, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8,  0, 16, NT[E][4], 16, NT[E][5], 16,  NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16, 
        NT[B][4], -8, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16, 
        NT[A][4] , 4, 0, 8, 
        NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], -8, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8,  0, 16, NT[E][4], 16, NT[E][5], 16,  NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16, 
        NT[B][4], -8, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16, 
        NT[A][4], 8, 0, 16, NT[B][4], 16, NT[C][5], 16, NT[D][5], 16,
        NT[E][5], -8, NT[G][4], 16, NT[F][5], 16, NT[E][5], 16, 
        NT[D][5], -8, NT[F][4], 16, NT[E][5], 16, NT[D][5], 16,
        NT[C][5], -8, NT[E][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, 0, 16,
        0, 16, NT[E][5], 16, NT[E][6], 16, 0, 16, 0, 16, NT[Eb][5], 16,
        NT[E][5], 16, 0, 16, 0, 16, NT[Eb][5], 16, NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8, 0, 16, NT[E][4], 16, NT[E][5], 16,  NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16,
        NT[A][4], 8, 0, 16, NT[B][4], 16, NT[C][5], 16, NT[D][5], 16,
        NT[E][5], -8, NT[G][4], 16, NT[F][5], 16, NT[E][5], 16, 
        NT[D][5], -8, NT[F][4], 16, NT[E][5], 16, NT[D][5], 16, 
        NT[C][5], -8, NT[E][4], 16, NT[D][5], 16, NT[C][5], 16, 
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, 0, 16,
        0, 16, NT[E][5], 16, NT[E][6], 16, 0, 16, 0, 16, NT[Eb][5], 16,
        NT[E][5], 16, 0, 16, 0, 16, NT[Eb][5], 16, NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16, 
        NT[C][5], 8, 0, 16, NT[E][4], 16, NT[E][5], 16,  NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16,
        NT[A][4], 8, 0, 16, NT[C][5], 16, NT[C][5], 16, NT[C][5], 16, 
        NT[C][5] , 4, NT[F][5], -16, NT[E][5], 32, 
        NT[E][5], 8, NT[D][5], 8, NT[Bb][5], -16, NT[A][5], 32,
        NT[A][5], 16, NT[G][5], 16, NT[F][5], 16, NT[E][5], 16, NT[D][5], 16, NT[C][5], 16,
        NT[Bb][4], 8, NT[A][4], 8, NT[A][4], 32, NT[G][4], 32, NT[A][4], 32, NT[B][4], 32,
        NT[C][5] , 4, NT[D][5], 16, NT[Eb][5], 16,
        NT[E][5], -8, NT[E][5], 16, NT[F][5], 16, NT[A][4], 16,
        NT[C][5] , 4,  NT[D][5], -16, NT[B][4], 32,
        NT[C][5], 32, NT[G][5], 32, NT[G][4], 32, NT[G][5], 32, NT[A][4], 32, NT[G][5], 32, NT[B][4], 32, NT[G][5], 32, NT[C][5], 32, NT[G][5], 32, NT[D][5], 32, NT[G][5], 32, 
        NT[E][5], 32, NT[G][5], 32, NT[C][6], 32, NT[B][5], 32, NT[A][5], 32, NT[G][5], 32, NT[F][5], 32, NT[E][5], 32, NT[D][5], 32, NT[G][5], 32, NT[F][5], 32, NT[D][5], 32,
        NT[C][5], 32, NT[G][5], 32, NT[G][4], 32, NT[G][5], 32, NT[A][4], 32, NT[G][5], 32, NT[B][4], 32, NT[G][5], 32, NT[C][5], 32, NT[G][5], 32, NT[D][5], 32, NT[G][5], 32,
        NT[E][5], 32, NT[G][5], 32, NT[C][6], 32, NT[B][5], 32, NT[A][5], 32, NT[G][5], 32, NT[F][5], 32, NT[E][5], 32, NT[D][5], 32, NT[G][5], 32, NT[F][5], 32, NT[D][5], 32, 
        NT[E][5], 32, NT[F][5], 32, NT[E][5], 32, NT[Eb][5], 32, NT[E][5], 32, NT[B][4], 32, NT[E][5], 32, NT[Eb][5], 32, NT[E][5], 32, NT[B][4], 32, NT[E][5], 32, NT[Eb][5], 32,
        NT[E][5], -8, NT[B][4], 16, NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], -8, NT[B][4], 16, NT[E][5], 16, 0, 16,
        0, 16, NT[Eb][5], 16, NT[E][5], 16, 0, 16, 0, 16, NT[Eb][5], 16, 
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16, 
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16,
        NT[A][4], 8, 0, 16, NT[B][4], 16, NT[C][5], 16, NT[D][5], 16,
        NT[E][5], -8, NT[G][4], 16, NT[F][5], 16, NT[E][5], 16,
        NT[D][5], -8, NT[F][4], 16, NT[E][5], 16, NT[D][5], 16,
        NT[C][5], -8, NT[E][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, 0, 16,
        0, 16, NT[E][5], 16, NT[E][6], 16, 0, 16, 0, 16, NT[Eb][5], 16,
        NT[E][5], 16, 0, 16, 0, 16, NT[Eb][5], 16, NT[E][5], 16, NT[D][5], 16, 
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], 8, 0, 16, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16, 
        NT[B][4], 8, 0, 16, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16,
        NT[A][4], 8, 0, 16, 0, 16, 0, 8, 
        NT[Cs][5] , -4, 
        NT[D][5] , 4, NT[E][5], 16, NT[F][5], 16,
        NT[F][5] , 4, NT[F][5], 8, 
        NT[E][5] , -4,
        NT[D][5] , 4, NT[C][5], 16, NT[B][4], 16,
        NT[A][4] , 4, NT[A][4], 8,
        NT[A][4], 8, NT[C][5], 8, NT[B][4], 8,
        NT[A][4] , -4,
        NT[Cs][5] , -4,
        NT[D][5] , 4, NT[E][5], 16, NT[F][5], 16, 
        NT[F][5] , 4, NT[F][5], 8,
        NT[F][5] , -4,
        NT[Eb][5] , 4, NT[D][5], 16, NT[C][5], 16,
        NT[Bb][4] , 4, NT[A][4], 8,
        NT[Gs][4] , 4, NT[G][4], 8,
        NT[A][4] , -4,
        NT[B][4] , 4, 0, 8,
        NT[A][3], -32, NT[C][4], -32, NT[E][4], -32, NT[A][4], -32, NT[C][5], -32, NT[E][5], -32, NT[D][5], -32, NT[C][5], -32, NT[B][4], -32,
        NT[A][4], -32, NT[C][5], -32, NT[E][5], -32, NT[A][5], -32, NT[C][6], -32, NT[E][6], -32, NT[D][6], -32, NT[C][6], -32, NT[B][5], -32, 
        NT[A][4], -32, NT[C][5], -32, NT[E][5], -32, NT[A][5], -32, NT[C][6], -32, NT[E][6], -32, NT[D][6], -32, NT[C][6], -32, NT[B][5], -32,
        NT[Bb][5], -32, NT[A][5], -32, NT[Gs][5], -32, NT[G][5], -32, NT[Fs][5], -32, NT[F][5], -32, NT[E][5], -32, NT[Eb][5], -32, NT[D][5], -32,
        NT[Cs][5], -32, NT[C][5], -32, NT[B][4], -32, NT[Bb][4], -32, NT[A][4], -32, NT[Gs][4], -32, NT[G][4], -32, NT[Fs][4], -32, NT[F][4], -32, 
        NT[E][4], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], -8, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, NT[Eb][5], 16, 
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16, 
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16, 
        NT[B][4], -8, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16, 
        NT[A][4], -8, 0, -8,
        0, -8, NT[G][4], 16, NT[F][5], 16, NT[E][5], 16,
        NT[D][5] , 4, 0, 8,
        0, -8, NT[E][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[B][4], -8, NT[E][4], 16, NT[E][5], 8, 
        NT[E][5], 8, NT[E][6], -8, NT[Eb][5], 16,
        NT[E][5], 16, 0, 16, 0, 16, NT[Eb][5], 16, NT[E][5], 16, NT[Eb][5], 16,
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], -8, NT[E][4], 16, NT[Gs][4], 16, NT[B][4], 16,
        NT[C][5], 8, 0, 16, NT[E][4], 16, NT[E][5], 16, NT[Eb][5], 16, 
        NT[E][5], 16, NT[Eb][5], 16, NT[E][5], 16, NT[B][4], 16, NT[D][5], 16, NT[C][5], 16,
        NT[A][4], -8, NT[C][4], 16, NT[E][4], 16, NT[A][4], 16,
        NT[B][4], -8, NT[E][4], 16, NT[C][5], 16, NT[B][4], 16,
        NT[A][4] , -4, 0, 4
    };
    play(furElise, beatmap, 80, 0.1);
}