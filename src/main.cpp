#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUZZER 9
#define RELAY 2

int presentage = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcdWrite(String txt, int x = 0, int y = 0)
{
  lcd.setCursor(x, y);
  lcd.print(txt);
}

void homeScreen(int presentage)
{
  int x1 = 5;
  int x2 = 9;
  if (presentage < 10)
  {
    x1 = 6;
    x2 = 8;
  }
  else if (presentage < 100)
  {
    x1 = 6;
  }

  lcd.clear();
  lcdWrite(String(presentage), x1, 0);
  lcdWrite("%", x2, 0);
  lcdWrite("REMAINING", 3, 1);
}

void fillingScreen(int presentage, float ETA)
{
  int x1 = 12;
  int x2 = 11;
  if (presentage < 10)
  {
    x1 = 14;
  }
  else if (presentage < 100)
  {
    x1 = 13;
  }
  if (ETA < 10.0)
  {
    x2 = 12;
  }

  lcd.clear();
  lcdWrite("FILLING...");
  lcdWrite(String(presentage), x1, 0);
  lcdWrite("%", 15, 0);
  lcdWrite("ETA -", 0, 1);
  lcdWrite(String(ETA), x2, 1);
}

void setup()
{
  pinMode(RELAY, OUTPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available())
  {
    String text = Serial.readString();
    Serial.println(text.toInt());
    fillingScreen(text.toInt(), 10.12);
  }
}