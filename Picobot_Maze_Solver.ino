#include <Servo.h> // need the standard Arduino servo library

int trigPin = A4;   // Analog pin 0 used for the Ping Pin (Trig)
int echoPin = A5;   // Analog pin 1 used for the Echo Pin (Echo)
unsigned long duration, inches;
int indec, cmdec;
int inchconv = 147; // ratio between pulse width and inches
int cmconv = 59;    // ratio between pulse width and cm
int L1 = 2, L2 = 3, L3 = 4, L4 =5; // Pins connected to Motor driver L298N H-Bridge module
#define LED 13  // Blue LED pin

void setup()
{
  Serial.begin(115200);
 
  // initialize the ultrasonic sensor pins and centre the servos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(L1, OUTPUT);     
  pinMode(L2, OUTPUT);     
  pinMode(L3, OUTPUT);     
  pinMode(L4, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  int cm, lcm, rcm;
  cm = getDistance();
  Serial.println(cm);
  delay(1000);
  if (cm < 20)
  {
    rightSpin(1000);
  }
  else
  {
  forward(2000);  // parameter is delay in ms after performing operation
  }
  
  halt(500);
}


int getDistance()
{
  int rval;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 38000L);  // Set timeout to 38mS
  rval = microsecondsToCentimeters(duration);
  Serial.println(rval);
  return rval;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / cmconv;
}
void robMove(int l1, int l2, int r1, int r2)
{
  digitalWrite(L1, l1);
  digitalWrite(L2, l2);
  digitalWrite(L3, r1);
  digitalWrite(L4, r2);  
}

void reverse(int wait)
{
  Serial.println("Moving backward");
  robMove(LOW, HIGH, HIGH, LOW);
  delay(wait);
}

void forward(int wait)
{
  Serial.println("Moving forward");
  robMove(HIGH, LOW, LOW, HIGH);
  delay(wait);
}

void rightSpin(int wait)
{
  Serial.println("Spinning right");
  robMove(HIGH, LOW, HIGH, LOW);
  delay(wait);
}

void leftSpin(int wait)
{
  Serial.println("Spinning left");
  robMove(LOW, HIGH, LOW, HIGH);
  delay(wait);
}

void halt(int wait)
{
  Serial.println("Stopping");
  robMove(LOW, LOW, LOW, LOW);
  delay(wait);
}

