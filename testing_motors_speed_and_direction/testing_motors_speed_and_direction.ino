const int potPin = A7;
const int leftSelect = 12;
const int rightSelect = 13;

const int bigRedButton = 4;

#define PWMa 7  //define PWM pins
#define PWMb 5
#define PWMc 8
#define PWMd 6

int motorSpeed, leftMotorSpeed, rightMotorSpeed;
int leftState, rightState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWMa, OUTPUT);  //define PWM motor pins
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);

  pinMode(potPin, INPUT);
  pinMode(leftSelect, INPUT);
  pinMode(rightSelect, INPUT);
  analogWrite(PWMa, 0); //turn off the motors
  analogWrite(PWMb, 0);
  analogWrite(PWMc, 0);
  analogWrite(PWMd, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(bigRedButton) == 1) {
    Serial.println("Program paused");
    analogWrite(PWMa, 0); //turn off the motors
    analogWrite(PWMb, 0);
    analogWrite(PWMc, 0);
    analogWrite(PWMd, 0);
  }


  leftState = digitalRead(leftSelect);
  rightState = digitalRead(rightSelect);
  motorSpeed = analogRead(potPin) / 4;

  leftMotorSpeed = 255 - motorSpeed;
  rightMotorSpeed = motorSpeed;

  if (leftState == 0 && rightState == 0) {
    Serial.println("Just chilling");
    analogWrite(PWMa, 0); //turn off the motors
    analogWrite(PWMb, 0);
    analogWrite(PWMc, 0);
    analogWrite(PWMd, 0);
  }

  if (leftState == 1 && rightState == 0) {
    Serial.print("Left motor selected, motor speed:");
    Serial.println(motorSpeed);
    analogWrite(PWMc, 255);
    analogWrite(PWMd, leftMotorSpeed);
  }

  if (leftState == 0 && rightState == 1) {
    Serial.print("Right motor selected, motor speed:");
    Serial.println(motorSpeed);
    analogWrite(PWMa, 0);
    analogWrite(PWMb, motorSpeed);
  }

  if (leftState == 1 && rightState == 1){
    Serial.print("Right: ");
    Serial.println(rightMotorSpeed);
    Serial.print("Left: ");
    Serial.println(leftMotorSpeed);
    analogWrite(PWMa, 0);
    analogWrite(PWMb, rightMotorSpeed);
    analogWrite(PWMc, 255);
    analogWrite(PWMd, leftMotorSpeed);
  }
}


/*
  if (error < -1) { //erroris negative, so centre point is left of black line, right turn is needed
    rightMotorSpeed = 0.5 * motorSpeed;
    leftMotorSpeed = 255 - motorSpeed;  
    
    analogWrite(PWMa, 0);
    analogWrite(PWMb, rightMotorSpeed);  //slow down right motor 
    analogWrite(PWMc, 255);
    analogWrite(PWMd, leftMotorSpeed);

  }

*/ //for use in weighted average program later?
