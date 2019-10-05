#include <SPI.h>
#include <SD.h>

#define lm35_pin A0
#define mhz19_pin A7
#define sd_pin A3

File datos;

int prevVal = LOW, myVal;
long th, tl, h, l, ppm, tt;
float raw_temperatura = 0, temperatura = 0;
unsigned long milisegundos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(mhz19_pin, INPUT);
  pinMode(lm35_pin, INPUT);

  while(!Serial){;}                                 //espero hasta que se establezca comunicacioon serial
  Serial.println("Iniciando tarjeta SD");
  if(!SD.begin(sd_pin)){
      "Inicializacion de tarjeta SD fallida";
  }
  Serial.println("Inicializacion de tarjeta SD exitosa");
}

void loop() {
  
  tt = millis();
  milisegundos = millis();
  myVal = digitalRead(mhz19_pin);
  if (myVal == HIGH) {
    if (myVal != prevVal) {
      h = tt;
      tl = h - l;
      prevVal = myVal;
    }
  }  else {
    if (myVal != prevVal) {
      l = tt;
      th = l - h;
      prevVal = myVal;
      ppm = 5000 * (th - 2) / (th + tl - 4);
    }
  }
  raw_temperatura = analogRead(lm35_pin);
  temperatura = (raw_temperatura * 500.0) / (1023.0);
  Serial.println("{milisegundos: " + String(milisegundos) +  ", temperatura: " + String(temperatura) + ", ppm: " + String(ppm) + "}");

  datos = SD.open("test.txt", FILE_WRITE);
  if(datos){
    datos.println("{milisegundos: " + String(milisegundos) +  ", temperatura: " + String(temperatura) + ", ppm: " + String(ppm) + "}");
    datos.close();
  }
}
