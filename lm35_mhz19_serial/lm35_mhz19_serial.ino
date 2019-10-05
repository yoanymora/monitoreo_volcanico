#define lm35PIN A0
#define mhz19PIN A7

int prevVal = LOW, myVal;
long th, tl, h, l, ppm, tt;
float raw_temperatura = 0, temperatura = 0;

void setup() {
  Serial.begin(9600);
  pinMode(mhz19PIN, INPUT);
  pinMode(lm35PIN, INPUT);
}

void loop() {
  tt = millis();
  myVal = digitalRead(mhz19PIN);
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
  raw_temperatura = analogRead(lm35PIN);
  temperatura = (raw_temperatura * 500.0) / (1023.0);
  Serial.println("PPM = " + String(ppm));
  Serial.println("Temperatura: " + String(temperatura));
}
