//#define Opins[0] 8 //OIN == origo in
//#define Opins[1] 9
//#define Opins[2] 10
//#define Opins[3] 11
//
//#define Epins[0] 2 //EIN == elbow in
//#define Epins[1] 3
//#define Epins[2] 4
//#define Epins[3] 5

int origoPins[] = {8, 9, 10, 11};
int elbowPins[] = {2, 3, 4, 5};

int cstep = 0;
int WAIT = 900;

long time;
int timeOut = 15;

int currentValue = 0;
int values[] = {
  0,0};
  
int origo = values[0];
int elbow = values[1];
int oldOrigo = origo;
int oldElbow = elbow;

void setup(){
  Serial.begin(9600);
  
  for(int i = 0; i < 4; i++){
   pinMode(origoPins[i], OUTPUT); 
  }

  for(int i = 0; i < 4; i++){
   pinMode(elbowPins[i], OUTPUT); 
  }

  time = millis();
}


void loop(){
  if(Serial.available()){
    int incomingValue = Serial.read();
    values[currentValue] = incomingValue;

    currentValue++;
    if(currentValue > 1){
      currentValue = 0; 
    }
  
    origo = values[0];
    elbow = values[1];
    
    moveTo(oldOrigo, origo, origoPins);
    
   oldOrigo = origo;
  oldElbow = elbow; 
   

  }
}

//// Functions for controlling the motor 

void moveTo(int currentAngle, int targetAngle, int pins[]){

  int distanceToTurn = abs(targetAngle - currentAngle);
  distanceToTurn = map(distanceToTurn, 0, 360, 0, 4096); //FIX THIS!! this lowers the resolution and counteracts the point of using a stepper over a servo (right????)

  if(targetAngle > currentAngle){
    for(int i = 0; i < distanceToTurn; i++){
      stepcw(pins);
      delayMicroseconds(WAIT);
//      if(time - millis() > timeOut){
//        time = millis();
//        break; 
//      }
    }
  }
  else{
    for(int i = 0; i < distanceToTurn; i++){
      stepccw(pins);
      delayMicroseconds(WAIT);
//      if(time - millis() > timeOut){
//        time = millis();
//        break; 
//      }
    } 
  }
}

void stepccw(int pins[])
{
  //stepp
  switch(cstep)
  {
  case 0:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], HIGH);
    break; 
  case 1:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    break; 
  case 2:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    break; 
  case 3:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    break; 
  case 4:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  case 5:
    digitalWrite(pins[0], HIGH); 
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  case 6:
    digitalWrite(pins[0], HIGH); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  case 7:
    digitalWrite(pins[0], HIGH); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], HIGH);
    break; 
  default:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  }

  cstep=cstep+1;
  if(cstep==8)
  {
    cstep=0;
  }
}

void stepcw(int pins[])
{
  //stepp
  switch(cstep)
  {
  case 7:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], HIGH);
    break; 
  case 6:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], HIGH);
    break; 
  case 5:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    break; 
  case 4:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], HIGH);
    digitalWrite(pins[3], LOW);
    break; 
  case 3:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  case 2:
    digitalWrite(pins[0], HIGH); 
    digitalWrite(pins[1], HIGH);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  case 1:
    digitalWrite(pins[0], HIGH); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  case 0:
    digitalWrite(pins[0], HIGH); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], HIGH);
    break; 
  default:
    digitalWrite(pins[0], LOW); 
    digitalWrite(pins[1], LOW);
    digitalWrite(pins[2], LOW);
    digitalWrite(pins[3], LOW);
    break; 
  }

  cstep=cstep+1;
  if(cstep==8)
  {
    cstep=0;
  }
}


