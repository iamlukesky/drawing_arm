#include <Servo.h>

int origoServoPin = 11;
int elbowServoPin = 9;
Servo origoServo;
Servo elbowServo;

int currentValue = 0;
int values[] = {
  0,0};

void setup(){
  pinMode(origoServoPin, OUTPUT);
  pinMode(elbowServoPin, OUTPUT);

  origoServo.attach(origoServoPin);
  elbowServo.attach(elbowServoPin);

  elbowServo.write(90);
  origoServo.write(90);
  delay(500);

  Serial.begin(9600);
}


void loop(){
  if(Serial.available()){
    int incomingValue = Serial.read();
    values[currentValue] = incomingValue;

    currentValue++;
    if(currentValue > 1){
      currentValue = 0; 
    }


    int origo = values[0];
    int elbow = values[1];

    // Serial.println(origo + ", " + elbow);

    origoServo.write(180-origo);
    elbowServo.write(180-elbow);

    //delay(10);
  }
}



