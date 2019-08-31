//Leer LM35:Sensor de temperatura

#define lm35PIN A0   //pin conectado a LM35
float raw_temp = 0, temp = 0; //variables globales para leer adc y obtener temperatura

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(lm35PIN, INPUT);
}

void loop() {
  raw_temp = analogRead(lm35PIN); //leer sensor de temperatura
  temp = ((raw_temp) * (500.0)) / 1023.0;//conversion de adc
  Serial.print("Lectura ADC: ");
  Serial.println(raw_temp);//imprimir en consola
  Serial.print("Temperatura: ");
  Serial.println(temp);//imprimir en consola
  delay(2000);
}
