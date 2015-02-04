#define OIN1 8 //OIN == origo in
#define OIN2 9
#define OIN3 10
#define OIN4 11

#define EIN1 2 //EIN == elbow in
#define EIN2 3
#define EIN3 4
#define EIN4 5

int cstep = 0;
int WAIT = 900;

int currentValue = 0;
int values[] = {
  0,0};

void setup(){
  Serial.begin(9600);
  pinMode(OIN1, OUTPUT); 
  pinMode(OIN2, OUTPUT); 
  pinMode(OIN3, OUTPUT); 
  pinMode(OIN4, OUTPUT);

  pinMode(EIN1, OUTPUT); 
  pinMode(EIN2, OUTPUT); 
  pinMode(EIN3, OUTPUT); 
  pinMode(EIN4, OUTPUT);
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

  }
}

//// Functions for controlling the motor 

void moveTo(int currentAngle, int targetAngle){

  int distanceToTurn = abs(targetAngle - currentAngle);
  distanceToTurn = map(distanceToTurn, 0, 360, 0, 4096);

  if(targetAngle > currentAngle){
    for(int i = 0; i < distanceToTurn; i++){
      stepcw();
      delayMicroseconds(WAIT); 
    }
  }
  else{
    for(int i = 0; i < distanceToTurn; i++){
      stepccw();
      delayMicroseconds(WAIT);
    } 
  }
}

void stepccw()
{
  //stepp
  switch(cstep)
  {
  case 0:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break; 
  case 1:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    break; 
  case 2:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break; 
  case 3:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break; 
  case 4:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  case 5:
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  case 6:
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  case 7:
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break; 
  default:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  }

  cstep=cstep+1;
  if(cstep==8)
  {
    cstep=0;
  }
}

void stepcw()
{
  //stepp
  switch(cstep)
  {
  case 7:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break; 
  case 6:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    break; 
  case 5:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break; 
  case 4:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    break; 
  case 3:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  case 2:
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  case 1:
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  case 0:
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    break; 
  default:
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    break; 
  }

  cstep=cstep+1;
  if(cstep==8)
  {
    cstep=0;
  }
}

