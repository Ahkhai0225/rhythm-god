#include "C12832.h"
#include "mbed.h"
#include "musicplayer.h"

// PwmOut speaker(p26);
AnalogIn pot1(p19);
DigitalIn joystickCenter(p14);
C12832 lcd(p5, p7, p6, p8, p11);
BusIn joy(p15, p12);
BusOut leds(LED1, LED2, LED3, LED4);

int main() {
  int i = 0;
  int dimX = 120;
  int dimY = 28;
  int x = 0, y = 0;
  lcd.cls();
  lcd.locate(0, 3);
  lcd.printf("welcome to rythm-god game");
  ThisThread::sleep_for(2 * 100);
  int flag = 0;
  int j = 0;
  int cst = 4;
  int fDimX = dimX - cst;
  int fDimY = dimY - cst;
  int score = 0;

  while (1) {
    // CONDITION FOR CHECKING FOR THE center joystick
    if (joystickCenter) {
      leds = 0xf;
      flag = 100;
      musicplayer speaker(p26);
      speaker.selectSong(1);
    } else {
      if (flag == 0) {
        leds = joy;
        // moving the snake up
        if (joy == 0x1) {
          j = j - cst;
          if (j < 0)
            j = dimY;
        }
        // moving the snake down
        else if (joy == 0x2) {
          j = (j + cst) % dimY;
        }
      }
    }
    if (flag == 0) {
      lcd.cls();
      lcd.locate(i, j);
      lcd.printf("->");
      lcd.locate(3, 0);
      lcd.printf("Easy");
      lcd.locate(15, 0);
      lcd.printf("Medium");
      lcd.locate(30, 0);
      lcd.printf("Hard");
      lcd.locate(0, 22);
      lcd.printf("%d", score);
    }
  }
}
