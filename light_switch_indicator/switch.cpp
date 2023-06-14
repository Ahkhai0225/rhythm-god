#include "mbed.h"
#include "light.h"
#include "switch.h"

DigitalIn but1(p23);
DigitalIn but2(p24);
DigitalIn but3(p25);

int score;
bool pressed = false;
Timer timer;

void switchIndicator(int noteDuration, float speed)
{
    timer.start();
        while (float(timer.read_ms())/10 < noteDuration*speed){
            if(ledrow3.read() == 0b100 && but1 == 1 && pressed == false) {
                if (but2 == 1 || but3 == 1){
                    pressed = true;
                }
                else{
                    score++;
                    lcd.locate(0, 22);
                    lcd.printf("Score: %d", score);
                    pressed = true;
                }
            }
            else if(ledrow3.read() == 0b010 && but2 == 1 && pressed == false) {
                if (but1 == 1 || but3 == 1){
                    pressed = true;
                }
                else{
                    score++;
                    lcd.locate(0, 22);
                    lcd.printf("Score: %d", score);
                    pressed = true;
                }
            }
            else if(ledrow3.read() == 0b001 && but3 == 1 && pressed == false) {
                if (but1 == 1 || but2 == 1){
                    pressed = true;
                }
                else{
                    score++;
                    lcd.locate(0, 22);
                    lcd.printf("Score: %d", score);
                    pressed = true;
                }            
            }
        }
        timer.stop();
        timer.reset();
        pressed = false;
}