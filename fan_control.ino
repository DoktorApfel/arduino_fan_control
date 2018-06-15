// Quelle https://gist.github.com/adlerweb/fab155592dac2dd0acdfbb9db373de67
unsigned long last = 0;
unsigned long lasts = 0;
unsigned int dur = 0;
byte tgt = 128;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), tacho, FALLING);

  //Timer 1: Prescaler 0
  TCCR1B = TCCR1B & B11111000 | B00000001;
  analogWrite(9, 128);
}

void loop() {
  unsigned long cm = millis();

  if (Serial.available()) {
    byte tmp = Serial.parseInt();
    if (tmp > 0) tgt = map(tmp, 0, 100, 0, 255);
  }

  if (lasts > cm || (lasts + 1000) < cm) {
    Serial.print("Delay: ");
    Serial.print(dur);
    Serial.println("µs");

    unsigned long freq = 100000000 / dur;
    Serial.print("Frequenz: ");
    Serial.print(freq / 100);
    Serial.print('.');
    Serial.print(freq % 100);
    Serial.println("Hz");

    freq *= 60;
    freq /= 200;
    Serial.print("RPM: ");
    Serial.println(freq);


    Serial.print("Ziel: ");
    Serial.print(map(tgt, 0, 255, 0, 100));
    Serial.println('%');
    Serial.println("-----");
    lasts = millis();
  }

  analogWrite(9, tgt);
}

void tacho() {
  unsigned long cm = micros();
  dur = (cm - last);
  last = cm;
}


