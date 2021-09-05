#include <Arduino.h>

// Configurations :-
int minWaterLevel = 10; // Enter the Minimum water levell of tank. - cemtimeters(cm)
int maxWaterLevel = 40; // Enter the Maximum water levell of tank. - centimeters(cm)
int height = 50;        // Enter the Height of tank. - centimeter(cm)

int fillingToneInterval = 3000; // Enter the interval time for beep tone, when the tank is filling. - milliseconds(ms)
int filledToneInterval = 800;   // Enter the interval time for beep tone, when the tank is filled. - milliseconds(ms)

//[ DO NOT CHANGE THIS SECTION !!!! ]________________________________________________________________________________________________________________________________________________

int lastTime, timeGap;
long duration, depth;
bool runMotor = true;
#define trigPin 11
#define echoPin 12
#define buzzer 10
#define relayPin 9

void setup()
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(relayPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
}

void loop()
{
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    depth = (duration / 2) / 29.1;
    Serial.print(depth);
    Serial.println(" cm");
    if (depth <= height - maxWaterLevel)
    {
        runMotor = false;
    }
    if (depth >= height - minWaterLevel)
    {
        runMotor = true;
    }
    if (runMotor)
    {
        digitalWrite(relayPin, HIGH);
        fillingTone();
    }
    else
    {
        digitalWrite(relayPin, LOW);
        filledTone();
    }
}

void fillingTone()
{
    timeGap = (millis() - lastTime);
    if (timeGap > fillingToneInterval)
    {
        tone(buzzer, 500);
        if (timeGap > fillingToneInterval + 500)
        {
            noTone(buzzer);
            lastTime = millis();
        }
    }
}

void filledTone()
{
    timeGap = millis() - lastTime;
    if (timeGap > filledToneInterval)
    {
        tone(buzzer, 500);
        if (timeGap > filledToneInterval + 500)
        {
            noTone(buzzer);
            lastTime = millis();
        }
    }
}
