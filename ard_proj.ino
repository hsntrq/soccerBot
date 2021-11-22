#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ENA PB6
#define IN1 PB12
#define IN2 PB13
#define ENB PB7
#define IN3 PB14
#define IN4 PB15

const byte address[6] = "00007";
RF24 radio(PA4, PA3); // CE, CNS

void setup() {
  Serial1.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial1.println("init");
}


void loop() {
  
  if (radio.available()) {
    char text[18] = "12345678912345678";
    radio.read(&text, sizeof(text));
    Serial1.print("Receiving");
    Serial1.println(sizeof(text));
    Serial1.println(text);
    brake();
  }
  turnRight();
}
  

void Forward()
{
 motorAForward();
 motorBForward();
}

void Backward()
{
 motorABackward();
 motorBBackward();
}

void turnLeft()
{
 motorABackward();
 motorBForward();
}

void turnRight()
{
 motorAForward();
 motorBBackward();
}

void coast()
{
 motorACoast();
 motorBCoast();

}

void brake()
{
 motorABrake();
 motorBBrake();
 
}
////////////////////////////////MOTOR A CONTROL

void motorAForward()
{
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 analogWrite(ENA, 75);
}

void motorABackward()
{
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 analogWrite(ENA, 75);
}
////////////////////////////////MOTOR B CONTROL

void motorBForward()
{
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 analogWrite(ENB, 75);
}

void motorBBackward()
{
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 analogWrite(ENB, 75);
}

//////////////////////////////////////////COASTING AND BREAKING

void motorACoast()
{
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
}

void motorABrake()
{
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
}

void motorBCoast()
{
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
}

void motorBBrake()
{
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
}
