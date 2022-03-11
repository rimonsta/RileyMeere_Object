// variable to store speaker pin value
const int speakerPin = 8;
// variable to store photoresistor readings
int phototVal;
// variable to store frequency value
float freq;

void setup() {
  // initialize serial communications
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  // initialize serial moniter
  Serial.begin(9600);
}

void loop() {
  // read photoresistor input
  int photoVal = analogRead(A0);

  // print photoresistor value
  // range determined at 300-750
  Serial.print("Photoresistor: ");
  Serial.println(photoVal);
  
  // map photoresistor value to speaker value
  int photoPitch = map(photoVal, 100, 1000, 20, 000);
  // print pitch value
  Serial.print("Pitch: ");
  Serial.println(photoPitch);
  tone(8, photoPitch, 10);
  delay(1000);
}
