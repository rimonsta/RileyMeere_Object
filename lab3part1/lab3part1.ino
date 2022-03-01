// variables to store output pin values
const int led5 = 5;
const int led6 = 6;

void setup() {
  // initialize serial communications
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  // initialize serial moniter
  Serial.begin(9600);
}

void loop() {
  // read potentiometer input
  int potentVal = analogRead(A0);
  // read photoresistor input
  int photoVal = analogRead(A1);

  // print potentiometer value
  Serial.print("Potentiometer: ");
  Serial.println(potentVal);
  // print photoresistor value
  Serial.print("Photoresistor: ");
  Serial.println(photoVal);
  
  // map potentiometer value to led5
  int potentMap = map(potentVal, 0, 1023, 0, 255);
  analogWrite(5, potentMap);
  // map photoresistor value to led6
  int photoMap = map(photoVal, 400, 200, 0, 255);
  analogWrite(6, photoMap);
  
}
