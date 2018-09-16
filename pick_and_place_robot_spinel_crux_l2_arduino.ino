#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <movingAvg.h>          
movingAvg avgy(10);         
movingAvg avgx(10);                 
SoftwareSerial HC12(10, 11);


int x,sx;
int y,sy;
int lr;
int bf;
int sw;
String input;
int boundLow;
int boundHigh;
const char delimiter = ',';

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50

uint8_t servonum = 0;

void setup() {
avgy.begin();
avgx.begin();
    
Serial.begin(9600);
HC12.begin(9600);
pinMode (2, OUTPUT);
pinMode (3, OUTPUT);
pinMode (4, OUTPUT);
pinMode (5, OUTPUT);

Serial.println("16 channel Servo test!");
pwm.begin();
pwm.setPWMFreq(FREQUENCY);
}

int pulseWidth(int angle)
{
int pulse_wide, analog_value;
pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
//Serial.println(analog_value);
return analog_value;
}

void loop() {

  if(HC12.available())
  {
  input = HC12.readStringUntil('\n');
  if (input.length() > 0)
      {
        Serial.println(input);
       
       boundLow = input.indexOf(delimiter);
        x = input.substring(0, boundLow).toInt();
    
        boundHigh = input.indexOf(delimiter, boundLow+1);
        y = input.substring(boundLow+1, boundHigh).toInt();
    
        boundLow = input.indexOf(delimiter, boundHigh+1);
        lr = input.substring(boundHigh+1, boundLow).toInt();

        boundHigh = input.indexOf(delimiter, boundLow+1);
        bf = input.substring(boundLow+1, boundHigh).toInt();
    
        sw = input.substring(boundHigh+1).toInt();
  
sx=map(x, 500, 200, 200, 100);
int ay = avgx.reading(sx);   // calculate the moving average

sy=map(y, 500, 200, 10, 140);
int ax = avgy.reading(sy);



pwm.setPWM(0, 0, pulseWidth(150));
pwm.setPWM(1, 0, pulseWidth(ax));
pwm.setPWM(2, 0, pulseWidth(ay));
pwm.setPWM(3, 0, pulseWidth(80));
delay(10); 
       
}

//Hand Close/Open
if (sw <= 10)
{
pwm.setPWM(0, 0, pulseWidth(200));
}

if (sw >= 10)
{
pwm.setPWM(0, 0, pulseWidth(150));
}


//Robot Movement
if (bf <= 50)
{
forward();
}
else if (bf >= 900)
{

backward();
}

else if (lr <= 50)
{
right();
}
else if (lr >= 900)
{

left();
}
else
{
stop();
}
}
}




void backward() {
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
Serial.println(" Moving Forward");
}

void forward() {
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
Serial.println(" Moving Backward");
}

void stop() {
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
Serial.println(" STOP ");
}

void right() {
digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
Serial.println(" Moving Left");
}

void left() {
digitalWrite(2, LOW);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
Serial.println(" Moving Right");
}
