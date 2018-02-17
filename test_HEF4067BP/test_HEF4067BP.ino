// Set Analog I/O pin to use for reading channel values from multiplexer.
int ComIOpin = A1;  // HEF4067BP(X)(ICpin-01)

// Set which pins tell the multiplexer which input to read from.
//int DpinA0 = 10;  // HEF4067BP Address Input A0 (A)(ICpin-10)
//int DpinA1 = 11;  // HEF4067BP Address Input A1 (B)(ICpin-11)
//int DpinA2 = 12;  // HEF4067BP Address Input A2 (C)(ICpin-14)
//int DpinA3 = 13;  // HEF4067BP Address Input A3 (D)(ICpin-13)
int ledPins[] = {10, 11, 12, 13};

void setup() {

  // Set the digital pins to outputs.
  pinMode(ledPins[0], OUTPUT);  // HEF4067BP Address Input A = pin10
  pinMode(ledPins[1], OUTPUT);  // HEF4067BP Address Input B = pin11
  pinMode(ledPins[2], OUTPUT);  // HEF4067BP Address Input C = pin12
  pinMode(ledPins[3], OUTPUT);  // HEF4067BP Address Input D = pin13
  Serial.begin(9600); // Set Serial COM
}

void loop()

{
  Serial.println("--------------------------");

  //1
  digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], LOW);
  int readvol = analogRead(ComIOpin);
  Serial.println(readvol);

  digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], LOW);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

  digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], LOW);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

    digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], LOW);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], LOW);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], LOW);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], LOW);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);

      digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[3], HIGH);
  readvol = analogRead(ComIOpin);
  Serial.println(readvol);
  
  /*
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
    readvol = analogRead(ComIOpin);
    Serial.println("3 : " + readvol);

    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], LOW);
    readvol = analogRead(ComIOpin);
    Serial.println("4 : " + readvol);
  */
  Serial.println("--------------------------");
}
