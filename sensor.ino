char sensor_indutivo = 7;

void setup() {
   Serial.begin(9600);
   pinMode(sensor_indutivo, INPUT);

}

void loop() {

  Serial.println(analogRead(sensor_indutivo));

  delay(20);

}
