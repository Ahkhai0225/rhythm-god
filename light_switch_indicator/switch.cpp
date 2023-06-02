#include "mbed.h"
#include "light.h"

DigitalIn but1(p9);
DigitalIn but2(p10);
DigitalIn but3(p12);
int scoree;
int a = 0;
Timer timer;

void switchIndicator(int noteDuration, float speed)
{
    timer.start();
        while (timer.read_ms()/10 < noteDuration*speed){
            if(ledrow3.read() && but1 == 1 && a == 0) {
                scoree++;
                a++;
            }
            else if(ledrow3 == 0b010 && but2 == 1 && a == 0) {
                scoree++;
                a++;
            }
            else if(ledrow3 == 0b001 && but3 == 1 && a == 0) {
                scoree++;
                a++;                  
            }
        }
        timer.stop();
        timer.reset();
        a = 0;
}