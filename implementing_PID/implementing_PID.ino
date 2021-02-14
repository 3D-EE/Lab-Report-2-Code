#define PWMa 7  //define PWM pins
#define PWMb 5
#define PWMc 8
#define PWMd 6

#define baseSpeed 180  //define motor speed for PWM output

#define DEBUG 1

int leftMotorSpeed, rightMotorSpeed;
int sensor0Value, sensor1Value, sensor2Value, sensor3Value; //left to right array

float formulaNumerator, formulaDenom, weightedAverage;
const int kP = 8.6, kI = 0.01, kD = 1;
unsigned long currentTime, previousTime;
float  error, cumulativeError, rateError, outputU = 1;
float elapsedTime = 0, lastError = 0;

const int bigRedButton = 4; //pin used to pause program

void setup() {
  Serial.begin(57600);
  pinMode(PWMa, OUTPUT);  //define PWM motor pins
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);

  pinMode(A0, INPUT);     //define IR sensor pins
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A4, INPUT);

  pinMode(bigRedButton, INPUT); //define pin to terminate program

}

void loop() {
  while (digitalRead(bigRedButton) == 1) {
    Serial.println("Program paused");
    analogWrite(PWMa, 0 * baseSpeed); //turn off the motors
    analogWrite(PWMb, 0 * baseSpeed);
    analogWrite(PWMc, 0 * baseSpeed);
    analogWrite(PWMd, 0 * baseSpeed);
  }

  sensor0Value = analogRead(A0);
  sensor1Value = analogRead(A1);
  sensor2Value = analogRead(A2);
  sensor3Value = analogRead(A3);

  //adjust sensor values so that black is high ouput, and range is 0 to 100 (0 = white, 9 = black)
//    sensor0Value = map(sensor0Value, 0, 1023, 100, 0);
//    sensor1Value = map(sensor1Value, 0, 1023, 100, 0);
//    sensor2Value = map(sensor2Value, 0, 1023, 100, 0);
//    sensor3Value = map(sensor3Value, 0, 1023, 100, 0);

  sensor0Value = constrain(sensor0Value, 173, 1016);
  sensor1Value = constrain(sensor1Value, 142, 1016);
  sensor2Value = constrain(sensor2Value, 199, 1017);
  sensor3Value = constrain(sensor3Value, 164, 1017);
  
  sensor0Value = map(sensor0Value, 173, 1016, 100, 0);
  sensor1Value = map(sensor1Value, 142, 1016, 100, 0);
  sensor2Value = map(sensor2Value, 199, 1017, 100, 0);
  sensor3Value = map(sensor3Value, 164, 1017, 100, 0);

#if DEBUG == 1
  Serial.println(sensor0Value);
  Serial.println(sensor1Value);
  Serial.println(sensor2Value);
  Serial.println(sensor3Value);
#endif

  //refernce point centre point of vehicle


  //formulaNumerator = ((sensor0Value * (-2.1)) + (sensor1Value * (-0.65)) + (sensor2Value * (0.8) ) + (sensor3Value * (2.3))); //working in cm
  formulaNumerator = ((sensor0Value * (-22)) + (sensor1Value * (-6.3)) + (sensor2Value * (9.3) ) + (sensor3Value * (24.6))); //working in mm
  formulaDenom = sensor0Value + sensor1Value + sensor2Value + sensor3Value;
  weightedAverage = formulaNumerator / formulaDenom;


  calculatePID(weightedAverage);


  rightMotorSpeed = baseSpeed + outputU ;
  leftMotorSpeed =  255 - (baseSpeed - outputU); //fixes the inverted way left control works

  if (rightMotorSpeed > 254) { //prevent values too high that are nonsensical
    rightMotorSpeed = 255;
  }
  if (leftMotorSpeed < 2) {
    leftMotorSpeed = 1;
  }

#if DEBUG == 1
  Serial.print("Right motor speed = ");
  Serial.println(rightMotorSpeed);
  Serial.print("Left motor speed = ");
  Serial.print(leftMotorSpeed);
  Serial.print("     Adjusted: ");
  Serial.println(255 - leftMotorSpeed);
  Serial.println("");
  Serial.println("#############################################");
#endif


  analogWrite(PWMa, 0);
  analogWrite(PWMb, rightMotorSpeed);
  analogWrite(PWMc, 255);
  analogWrite(PWMd, leftMotorSpeed);

}

float calculatePID(float weightedAverage) {

  currentTime = millis();
  elapsedTime = (float)(currentTime - previousTime);


  error = - weightedAverage;  //as centre is setpoint, setpoint = 0
  cumulativeError += error * elapsedTime; //calculate integral (summing up many rectangles to determine integral)
  rateError = (error - lastError) / elapsedTime;  //calculate derivative, i.e. rate of change of error

  if (isnan(cumulativeError)) {   //check for nan
    cumulativeError = 0;
  }

  outputU = kP * error + kI * cumulativeError + kD * rateError;

#if DEBUG == 1
  Serial.println("\n\nWithin PID function:");
  Serial.print("error (mm) = ");
  Serial.println(error);
  Serial.print("cumulativeError = ");
  Serial.println(cumulativeError);
  Serial.print("rateError = ");
  Serial.println(rateError);
  Serial.println("");
  Serial.print("OutputU = ");
  Serial.println(outputU);
  Serial.println("");
#endif

  lastError = error;
  previousTime = currentTime;

  return outputU;
}
