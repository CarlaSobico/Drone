int numero = 1570;
byte imprimir;
void setup(){
  Serial.begin(115200);
}

void loop() {
  imprimir=highByte(numero);
  /*Me quedo con el bloque mas significativo en bytes*/
  Serial.print(imprimir);
  /*Me quedo con el bloque menos significativo en bytes*/
  imprimir=lowByte(numero);
  Serial.print(imprimir);
  delay(1000);
  Serial.println();

}
