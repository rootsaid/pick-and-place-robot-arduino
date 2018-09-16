#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial HC12(10, 11);

int x;
int y;
int lr;
int bf;
int sw;

void setup()
{ 
HC12.begin(9600);
Serial.begin(9600);
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
pinMode(2, OUTPUT);

}
void loop()
{
digitalWrite(A0,0);
digitalWrite(2, HIGH);
x = analogRead(A0);
y = analogRead(A1);

lr = analogRead(A3);
bf = analogRead(A2);
sw = analogRead(A4);

HC12.print(x);
Serial.print(",");
HC12.print(y);
Serial.print(",");
HC12.print(lr);
Serial.print(",");
HC12.print(br);
Serial.print(",");
HC12.print(sw);
Serial.print(",");

delay(100);
}
