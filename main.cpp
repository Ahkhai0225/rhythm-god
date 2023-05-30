#include "mbed.h"
#include "musicplayer.h"

// PwmOut speaker(p26);
AnalogIn pot1(p19);
DigitalIn joystickCenter(p14);
 
int main() {
    musicplayer speaker(p26);
    while(1) {
        speaker.selectSong(1);
    }
}
