#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define UP 2
#define RIGHT_ 3
#define LEFT_ 5
#define DOWN 4
#define BTN_E 6
#define BTN_F 7
#define BTN_G 8
#define Y 1
#define X 0
#define ROAD_X_DARK 1
#define ROAD_X_LIGHT 14

int heart_1 = 5000;
int heart_2 = 3500;
int steps_2 = 0;
int steps_1 = 0;
int xp = 0;
int hod_1 = 0;
int step_heart_1 = 0;
int istreb_ur = 0;
int super_ur_2 = 0;
int shans_krit_ur = 0;

uint8_t kaylo[8] = {0b11100,
                    0b11100,
                    0b11000,
                    0b11110,
                    0b11101,
                    0b10100,
                    0b10100
                   };

uint8_t kaylo2[8] = {0b00000,
                     0b00011,
                     0b01110,
                     0b11000,
                     0b00000,
                     0b00000,
                     0b00000,
                     0b00000
                    };

uint8_t xp1[8]  =  {0b00110,
                    0b00111,
                    0b00011,
                    0b01111,
                    0b00111,
                    0b00101,
                    0b00101
                   };

uint8_t istreb_1[8] = {0b011110,
                       0b111111,
                       0b111111,
                       0b111111,
                       0b111111,
                       0b011110,
                       0b000000,
                       0b011111
                      };

LiquidCrystal_I2C game(0x27, 16, 2);

void setup() {
  game.init();
  game.backlight();
  game.createChar(1, kaylo);
  game.createChar(2, xp1);
  game.createChar(3, kaylo2);
  game.createChar(4, istreb_1);
  pinMode(UP, INPUT);
  pinMode(RIGHT_, INPUT);
  pinMode(LEFT_, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(BTN_E, INPUT);
  pinMode(BTN_F, INPUT);
  pinMode(BTN_G, INPUT);
  digitalWrite(UP, HIGH);
  digitalWrite(RIGHT_, HIGH);
  digitalWrite(LEFT_, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(BTN_E, LOW);
  digitalWrite(BTN_F, HIGH);
  digitalWrite(BTN_G, LOW);
}

void loop() {
  if (digitalRead(BTN_E) == true) {
    Star_wars_dark();
    Star_wars_1_xp();
    if (heart_1 <= 0) {
      porash();
    }
  }
}

void Star_wars_dark(void) {
  game.setCursor(0, 0);
  game.print(heart_1);
  game.setCursor(ROAD_X_DARK, 1);
  game.write(1);
  game.write(3);
  if (analogRead(X) < 472 or analogRead(Y) > 530 or analogRead(X) > 480 or analogRead(Y) < 520) {
    int x = random(100, 450);
    hod_1 = hod_1 + 1;
    shans_krit_ur = shans_krit_ur + 1;
    step_heart_1 = step_heart_1 + 1;
    istreb_ur = istreb_ur + 1;
    steps_1 = steps_1 + 1;
    heart_2 = heart_2 - x;
    game.setCursor(8, 0);
    game.print(x);
    delay(500);
    game.clear();
    game.setCursor(3, 1);
    game.write(1);
    game.write(3);
    delay(1000);
    game.clear();
    game.setCursor(ROAD_X_DARK, 1);
    game.write(1);
    game.write(3);
    if (digitalRead(DOWN) >= 10){
      shans_krit_ur = shans_krit_ur - 10;
      heart_2 = heart_2 - x;
      heart_2 = heart_2 - x;
      hod_1 = hod_1 + 1;
    }
    if (steps_1 >= 3) {
      game.clear();
      game.setCursor(1, 0);
      game.print("stas_uron: 100%");
      delay(1000);
      game.clear();
    }
    if (step_heart_1 >= 4) {
      game.clear();
      game.setCursor(3, 0);
      game.print("+heart: 100%");
      delay(1000);
      game.clear();
    }
    if (istreb_ur >= 8) {
      game.clear();
      game.setCursor(1, 0);
      game.print("istr_uron:100%");
      delay(1000);
      game.clear();
    }
    if (shans_krit_ur >= 10){
      game.clear();
      game.setCursor(0, 0);
      game.print("S_krit_uron:100%");
      delay(1000);
      game.clear();
    }
  }
  if (digitalRead(UP) == false and steps_1 >= 3) {
    heart_2 = heart_2 - 280;
    steps_1 = steps_1 - 3;
    delay(500);
    game.clear();
    game.setCursor(5, 1);
    game.write(1);
    game.write(3);
    delay(1000);
    game.clear();
    game.setCursor(ROAD_X_DARK, 1);
    game.write(1);
    game.write(3);
  }
  if (digitalRead(RIGHT_) == false and step_heart_1 >= 4) {
    step_heart_1 = step_heart_1 - 4;
    heart_1 = heart_1 + 200;
  }
  if (digitalRead(LEFT_) == false and istreb_ur >= 8) {
    istreb_ur = istreb_ur - 8;
    int r = random(800, 1000);
    heart_2 = heart_2 - r;
    game.clear();
    game.setCursor(10, 0);
    game.write(4);
    delay(1000);
    game.clear();
  }
}
void Star_wars_1_xp(void) {
  game.setCursor(12, 0);
  game.print(heart_2);
  game.setCursor(ROAD_X_LIGHT, 1);
  game.write(2);
  if (hod_1 == 1) {
    hod_1 = hod_1 - 1;
    delay(100);
    int y = random(20, 400);
    steps_2 = steps_2 + 1;
    heart_1 = heart_1 - y;
    game.setCursor(5, 0);
    game.print(y);
    delay(500);
    game.clear();
    game.setCursor(12, 1);
    game.write(2);
    delay(1000);
    game.clear();
    game.setCursor(ROAD_X_LIGHT, 1);
    game.write(2);
  }
  if (steps_2 >= 3) {
    steps_2 = steps_2 - 3;
    heart_2 = heart_2 + 300;
  }
  if (heart_2 <= 0) {
    winner();
    delay(10);
    game.setCursor(12, 0);
    heart_2 = 4500;
    game.print(heart_2);
    game.setCursor(ROAD_X_LIGHT, 1);
    game.write(2);
    if (hod_1 == 1) {
      hod_1 = hod_1 - 1;
      delay(100);
      int t = random(100, 400);
      steps_2 = steps_2 + 1;
      heart_1 = heart_1 - t;
      game.setCursor(5, 0);
      game.print(t);
      delay(500);
      game.clear();
      game.setCursor(11, 1);
      game.write(2);
      delay(1000);
      game.clear();
      game.setCursor(ROAD_X_LIGHT, 1);
      game.write(2);
    }
    if (steps_2 >= 3) {
      steps_2 = steps_2 - 3;
      heart_2 = heart_2 + 100;
    } if (heart_2 <= 0) {
      winner();
      delay(10);
      game.setCursor(12, 0);
      heart_2 = 7000;
      game.print(heart_2);
      game.setCursor(ROAD_X_LIGHT, 1);
      game.write(2);
      if (hod_1 == 1) {
        hod_1 = hod_1 - 1;
        super_ur_2 = super_ur_2 + 1;
        delay(100);
        int d = random(150, 450);
        steps_2 = steps_2 + 1;
        heart_1 = heart_1 - d;
        game.setCursor(5, 0);
        game.print(d);
        delay(500);
        game.clear();
        game.setCursor(11, 1);
        game.write(2);
        delay(1000);
        game.clear();
        game.setCursor(ROAD_X_LIGHT, 1);
        game.write(2);
      }
      if (steps_2 >= 3) {
        steps_2 = steps_2 - 3;
        heart_2 = heart_2 + 100;
      }
      if (super_ur_2 >= 4) {
        super_ur_2 = super_ur_2 - 4;
        int i = random(1000, 1500);
        heart_1 = heart_1 - i;
        game.clear();
        game.setCursor(10, 0);
        game.write(4);
        delay(1000);
        game.clear();
      }
      if (heart_2 <= 0) {
        winner_2();
        delay(20);
      }
    }
  }
}

void porash(void) {
  game.clear();
  game.setCursor(3, 0);
  game.print("Game Over!");
  delay(1000);
}

void winner(void) {
  xp = xp + 1;
  game.clear();
  game.setCursor(3, 0);
  game.print("You win!");
  game.setCursor(3, 1);
  game.print(xp);
  game.print(": 100%");
  delay(2000);
  game.clear();
  if (xp == 2) {
    game.setCursor(6, 0);
    game.print("final");
    delay(1000);
    game.clear();
  } else {
    game.setCursor(5, 0);
    game.print("progress");
    delay(1000);
    game.clear();
  }
}

void winner_2(void) {
  game.clear();
  game.setCursor(3, 0);
  game.print("You win!");
  game.setCursor(3, 1);
  game.print(xp);
  game.print(": 100%");
  delay(20000);
}
