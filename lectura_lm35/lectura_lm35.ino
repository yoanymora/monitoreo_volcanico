//leer temperatura::LM35

#define LM35 A0   //pin conectado a LM35
float raw_temp = 0, temp = 0; //variables globales para leer adc y obtener temperatura

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(LM35, INPUT);
}

void loop() {
  raw_temp = analogRead(LM35); //leer sensor de temperatura
  temp = ((raw_temp) * (1.1) * (100.0)) / 1024.0;//conversion de adc
  Serial.print("Lectura ADC: ");
  Serial.println(raw_temp);//imprimir en consola
  Serial.print("Temperatura: ");
  Serial.println(temp);//imprimir en consola
  delay(4000);
}
