void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int color = analogRead(A0);
  //Serial.print("COLOR:" );
  //Serial.println(color);
  int sides = analogRead(A1);
  //Serial.print("SIDES: ");
  //Serial.println(sides);
  int color_mapped = map(color, 20, 80, 0, 3);
  int sides_mapped = map(sides, 0, 1023, 3, 8);
  
  Serial.print(color_mapped);
  Serial.print(',');
  Serial.println(sides_mapped);

}
