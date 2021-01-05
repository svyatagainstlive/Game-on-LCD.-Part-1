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


int heart_kaylo = 3500;
int heart_rey = 3500;
int steps_Rey = 0;
int steps_Kaylo = 0;

uint8_t kaylo[8] = {0b11100,
                    0b11100,
                    0b11000,
                    0b11110,
                    0b11101,
                    0b10100,
                    0b10100};

uint8_t kaylo2[8] = {0b00000,
                     0b00011,
                     0b01110,
                     0b11000,
                     0b00000,
                     0b00000,
                     0b00000,
                     0b00000};

uint8_t Rey[8]  =  {0b10111,
                    0b10111,
                    0b10011,
                    0b10111,
                    0b11111,
                    0b10101,
                    0b00101};

LiquidCrystal_I2C game(0x27, 16, 2);

void setup() {
  game.init();
  game.backlight();
  game.createChar(1, kaylo);
  game.createChar(2, Rey); 
  game.createChar(3, kaylo2);
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
  if(digitalRead(BTN_E) == true){
    Star_wars_dark();
    Star_wars_light();
    if(heart_kaylo <= 0){
      Game_over();
      game.setCursor(5, 1);
      game.print(" Rey");
  }
  if(heart_rey <= 0){
    Game_over();
    game.setCursor(4, 1);
    game.print(" Kaylo");
  }
  }
}

void Star_wars_dark(void){
  game.setCursor(0, 0);
  game.print(heart_kaylo);
  game.setCursor(ROAD_X_DARK, 1);
  game.write(1);
  game.write(3);
  if (analogRead(X) < 472 or analogRead(Y) > 530){
    int x = random(0, 350);
    int l = 0;
    steps_Kaylo = steps_Kaylo + 1;
    heart_rey = heart_rey - x;
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
    Point_right();
    if (analogRead(X) < 472 <= 472 or analogRead(Y) > 530){
      heart_rey = heart_rey - l;
    }
  }
  if (digitalRead(BTN_G) == false and steps_Kaylo >= 3){
    heart_rey = heart_rey - random(200, 300);
    steps_Kaylo = steps_Kaylo - 3;
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
    Point_left();
  }
}

void Star_wars_light(void){
  game.setCursor(12, 0);
  game.print(heart_rey);
  game.setCursor(ROAD_X_LIGHT, 1);
  game.write(2);
  if (digitalRead(UP) == false){
    int y = random(0, 350);
    steps_Rey = steps_Rey + 1;
    heart_kaylo = heart_kaylo - y;
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
    Point_left();
    if (digitalRead(UP) <= false){
      heart_kaylo = heart_kaylo - y;
    }
  }
  if(digitalRead(DOWN) == false and steps_Rey >= 3){
    steps_Rey = steps_Rey - 3;
    heart_rey = heart_rey + random(200, 300);
    Point_right();
  }
}

void Game_over(void){
  game.clear();
  game.setCursor(3, 0);
  game.print("Game Over!");
}

void Point_right(){
  game.setCursor(8.5, 1);
  game.print(">");
}

void Point_left(){
  game.setCursor(8.5, 1);
  game.print("<");
}
