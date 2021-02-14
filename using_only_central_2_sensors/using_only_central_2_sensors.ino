#define PWMa 7  //define PWM pins
#define PWMb 5
#define PWMc 8
#define PWMd 6

#define motorSpeed 145  //define motor speed for PWM output
int leftMotorSpeed, rightMotorSpeed;
int sensor1Value, sensor2Value; //sensor 1 is left of centre, sensor 2 is right of centre.
#define white 800 //define brightness levels
#define black 400

const int bigRedButton = 4; //pin used to pause program

void setup() {
  Serial.begin(9600);
  pinMode(PWMa, OUTPUT);  //define PWM motor pins
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);

  pinMode(A1, INPUT);   //define IR sensor pins
  pinMode(A2, INPUT);
  pinMode(bigRedButton, INPUT); //define pin to terminate program

}

void loop() {
  while (digitalRead(bigRedButton) == 1) {
    Serial.println("Program paused");
    analogWrite(PWMa, 0 * motorSpeed); //turn off the motors
    analogWrite(PWMb, 0 * motorSpeed);
    analogWrite(PWMc, 0 * motorSpeed);
    analogWrite(PWMd, 0 * motorSpeed);
  }

  sensor1Value = analogRead(A1);
  sensor2Value = analogRead(A2);

  Serial.print("Left sensor: ");
  Serial.println(sensor1Value);
  Serial.print("Right sensor: ");
  Serial.println(sensor2Value);
  Serial.println("");




  if ((sensor1Value >= black && sensor1Value <= white) || (sensor2Value >= black && sensor2Value <= white) || (sensor1Value <= black && sensor2Value <= black) || (sensor1Value >= white && sensor2Value >= white)) { //ambiguous values likely means on the line, or both see same colour, so move forwards
    //ambiguous - sensor 1 in undefined range, sensor 2 in undefined range, both sensors see black, both sensors see white.    
    Serial.println("FORWARDS");
    rightMotorSpeed = 0.7 * motorSpeed;
    leftMotorSpeed = 255 - 0.7 * motorSpeed;  //requires reversal due to wiring
    Serial.print("Right motor: ");
    Serial.println(rightMotorSpeed);    //just to slow it down, reducing motor speed variable means lacking enough for turns
    Serial.print("Left motor: ");
    Serial.print(leftMotorSpeed);
    Serial.print("     Equivalent: ");
    Serial.println(rightMotorSpeed);
    Serial.println("");

    analogWrite(PWMa, 0);
    analogWrite(PWMb, rightMotorSpeed);
    analogWrite(PWMc, 255);
    analogWrite(PWMd, leftMotorSpeed);
  }



  if (sensor1Value >= white && sensor2Value <= black) { //left sensor sees white, right sees black, so right turn is needed (CW)
    Serial.println("Left sensor sees white, right sensor sees black, TURNING RIGHT");
    rightMotorSpeed = 0.5 * motorSpeed;
    leftMotorSpeed = 255 - motorSpeed;  //requires reversal due to wiring
    
    Serial.print("Right motor: ");
    Serial.println(rightMotorSpeed);
    Serial.print("Left motor: ");
    Serial.print(leftMotorSpeed);
    Serial.print("     Equivalent: ");
    Serial.println(motorSpeed);
    Serial.println("");

    analogWrite(PWMa, 0);
    analogWrite(PWMb, rightMotorSpeed);  //slow down the right motor to turn right
    analogWrite(PWMc, 255);
    analogWrite(PWMd, leftMotorSpeed);
  }

  if (sensor1Value <= black && sensor2Value >= white) { //left sensor sees black, right sees white, so left turn is needed (CCW)
    Serial.println("Left sensor sees black, right sensor see white, TURNING LEFT");
    rightMotorSpeed = motorSpeed;
    leftMotorSpeed = 255 - 0.5 * motorSpeed;  //requires reversal due to wiring
    
    Serial.print("Right motor: ");
    Serial.println(rightMotorSpeed);
    Serial.print("Left motor: ");
    Serial.print(leftMotorSpeed);
    Serial.print("     Equivalent: ");
    Serial.println(0.5 * motorSpeed);
    Serial.println("");

    analogWrite(PWMa, 0);
    analogWrite(PWMb, rightMotorSpeed);
    analogWrite(PWMc, 255);
    analogWrite(PWMd, leftMotorSpeed);  //even though we are increasing the value, this decreases the speed
  }                                           //PWM duty cycle


}
