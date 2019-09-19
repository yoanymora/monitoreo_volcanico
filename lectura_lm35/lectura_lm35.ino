#define lm35 A0                                     //pin conectado a LM35
float raw_temp = 0, temperatura = 0;                //variables globales para leer adc y obtener temperatura
unsigned long tiempo = 0;
char delimitador_1 = ":";
char delimitador_2 = ",";
char inicio_cadena = "{";
char fin_cadena = "}";

void setup() {
  Serial.begin(9600);
  pinMode(lm35, INPUT);
}

void loop() {
  tiempo = millis();
  raw_temp = analogRead(lm35);                      //leer sensor de temperatura
  temperatura = ((raw_temp) * (500.0)) / 1023.0;    //conversion de adc
  Serial.println("{milisegundos:" + String(tiempo) + "," + "temperatura:" + String(temperatura) + "}");
  delay(2000);
}
