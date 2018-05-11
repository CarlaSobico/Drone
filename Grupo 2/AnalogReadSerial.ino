

/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int pote_izq_y = analogRead(A0);
  int pote_izq_x = analogRead(A1);
  int pote_der_y = analogRead(A2);
  int pote_der_x = analogRead(A3);

  pote_izq_y = map(pote_izq_y, 0, 1023, 0, 255);
  pote_izq_x = map(pote_izq_x, 0, 1023, 0, 255);
  pote_der_y = map(pote_der_y, 0, 1023, 0, 255);
  pote_der_x = map(pote_der_x, 0, 1023, 0, 255);
  
  // print out the value you read:
  
  Serial.print(pote_izq_y);
  Serial.print("\t");
  Serial.print(pote_izq_x);
  Serial.print("\t");
  Serial.print(pote_der_y);
  Serial.print("\t");
  Serial.println(pote_der_x);
  
  delay(1);        // delay in between reads for stability
}
