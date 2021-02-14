
int sensor0ValueB, sensor1ValueB, sensor2ValueB, sensor3ValueB; 
int sensor0ValueW, sensor1ValueW, sensor2ValueW, sensor3ValueW;

const int blackSelect = 13;
const int whiteSelect = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT); //define IR sensor pins
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(blackSelect, INPUT);
  pinMode(whiteSelect, INPUT);
}

void loop() {


  if (digitalRead(blackSelect) == 1) {
    Serial.println("Black selected");
    sensor0ValueB = analogRead(A0);
    sensor1ValueB = analogRead(A1);
    sensor2ValueB = analogRead(A2);
    sensor3ValueB = analogRead(A3);
  }

  if (digitalRead(whiteSelect) == 1) {
    sensor0ValueW = analogRead(A0);
    sensor1ValueW = analogRead(A1);
    sensor2ValueW = analogRead(A2);
    sensor3ValueW = analogRead(A3);
  }

  Serial.print("\n\nB A0: ");
  Serial.println(sensor0ValueB);
  Serial.print("B A1: ");
  Serial.println(sensor1ValueB);
  Serial.print("B A2: ");
  Serial.println(sensor2ValueB);
  Serial.print("B A3: ");
  Serial.println(sensor3ValueB);
  Serial.println("\n");
  Serial.print("W A0: ");
  Serial.println(sensor0ValueW);
  Serial.print("W A1: ");
  Serial.println(sensor1ValueW);
  Serial.print("W A2: ");
  Serial.println(sensor2ValueW);
  Serial.print("W A3: ");
  Serial.println(sensor3ValueW);
  Serial.println("\n\n");


}
