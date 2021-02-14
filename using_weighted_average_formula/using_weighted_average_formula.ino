#define PWMa 7  //define PWM pins
#define PWMb 5
#define PWMc 8
#define PWMd 6

#define motorSpeed 145  //define motor speed for PWM output
int leftMotorSpeed, rightMotorSpeed;
int sensor0Value, sensor1Value, sensor2Value, sensor3Value; //left to right array

float formulaNumerator, formulaDenom, weightedAverage;
float error;

const int bigRedButton = 4; //pin used to pause program

void setup() {
  Serial.begin(9600);
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
    analogWrite(PWMa, 0 * motorSpeed); //turn off the motors
    analogWrite(PWMb, 0 * motorSpeed);
    analogWrite(PWMc, 0 * motorSpeed);
    analogWrite(PWMd, 0 * motorSpeed);
  }

  sensor0Value = analogRead(A0);
  sensor1Value = analogRead(A1);
  sensor2Value = analogRead(A2);
  sensor3Value = analogRead(A3);

  //adjust sensor values so that black is high ouput, and range is 0 to 100 (0 = white, 9 = black)
  sensor0Value = map(sensor0Value, 0, 1023, 100, 0);
  sensor1Value = map(sensor1Value, 0, 1023, 100, 0);
  sensor2Value = map(sensor2Value, 0, 1023, 100, 0);
  sensor3Value = map(sensor3Value, 0, 1023, 100, 0);

  Serial.println("#############");
  Serial.println(sensor0Value);
  Serial.println(sensor1Value);
  Serial.println(sensor2Value);
  Serial.println(sensor3Value);

  //refernce point centre point of vehicle
  //working in cm
  
 
  formulaNumerator = ((sensor0Value * (-2.1)) + (sensor1Value * (-0.65)) + (sensor2Value * (0.8) ) + (sensor3Value * (2.3)));  
  formulaDenom = sensor0Value + sensor1Value + sensor2Value + sensor3Value;
  weightedAverage = formulaNumerator / formulaDenom;

  error = - weightedAverage;    
  //4.6cm from left edge to centre
  Serial.println("");
  Serial.println("Error: ");
  Serial.println(error);

}
