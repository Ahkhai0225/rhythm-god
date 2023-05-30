#include "mbed.h"

PwmOut speaker(p26);
AnalogIn pot1(p19);
DigitalIn joystickCenter(p14);
 
int main() {
    enum noteNames {C, Cs, D, Eb, E, F, Fs, G, Gs, A, Bb, B};
    float NT[12][9] = { {16.35}, {17.32}, {18.35}, {19.45}, {20.60}, {21.83},
                        {23.12}, {24.5}, {25.96}, {27.5}, {29.14}, {30.87} };

    for (int i = 0; i < 12; i++) 
        for (int j = 1; j < 9; j++) 
            NT[i][j] = NT[i][j-1] * 2;

    float harrypotter[] = {
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
    
    int numOfNotes = sizeof(harrypotter)/sizeof(harrypotter[2])/2;
    int tempo = 157;
    int divider = 0, noteDuration = 0;
    int wholenote = 60000 * 4 / tempo;
    while(1) {
        for (int i = 0; i < numOfNotes * 2; i+=2) {
            divider = harrypotter[i+1];
            if(divider > 0) {
                noteDuration = wholenote/divider;
            }
            else if(divider < 0) {
                noteDuration = wholenote/abs(divider);
                noteDuration *= 1.5;
            }
            speaker.period(1 / (4*harrypotter[i]) );
            speaker = 0.5;
            ThisThread::sleep_for(noteDuration * 0.1);
        }
        if (joystickCenter)
            break;
    }
}
