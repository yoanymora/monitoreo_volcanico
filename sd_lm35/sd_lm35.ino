#include <SPI.h>
#include <SD.h>

#define lm35 A0                                     //pin conectado a LM35
#define sd A3                                       //pin conectado a adaptador SD
float raw_temp = 0, temperatura = 0;                //variables globales para leer adc y obtener temperatura
unsigned long tiempo = 0;
char delimitador_1 = ":";
char delimitador_2 = ","; 
char inicio_cadena = "{";
char fin_cadena = "}";
File datos;

void setup() {
  Serial.begin(9600);
  pinMode(lm35, INPUT);
  while(!Serial){;}                                 //espero hasta que se establezca comunicacioon serial
  Serial.println("Iniciando tarjeta SD");
  if(!SD.begin(sd)){
      "Inicializacion de tarjeta SD fallida";
    }
    Serial.println("Inicializacion de tarjeta SD exitosa");

    datos = SD.open("test.txt");
    if(datos){
        Serial.println("leyendo datos");
        while(datos.available()){
            Serial.write(datos.read());
          }
          datos.close();
     }else{
      Serial.println("error al leer datos");
      }
} 

void loop() {
  tiempo = millis();
  raw_temp = analogRead(lm35);                      //leer sensor de temperatura
  temperatura = ((raw_temp) * (500.0)) / 1023.0;    //conversion de adc
  Serial.println("{milisegundos:" + String(tiempo) + "," + "temperatura:" + String(temperatura) + "}");
  
  datos = SD.open("test.txt", FILE_WRITE);
  if(datos){
    datos.println("{milisegundos:" + String(tiempo) + "," + "temperatura:" + String(temperatura) + "}");
    datos.close();
    }
  delay(2000);
}
