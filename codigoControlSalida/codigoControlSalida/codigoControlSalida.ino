
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SHIFT_10_TO_8 2
#define BIN_TO_8_BIT 255

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

#define MAX_DATOS 11
#define HEADER_1 0x01
#define HEADER_2 0x03

byte direccion[5] ={'c','a','n','a','l'};


//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);
  
  uint8_t RX;
  uint8_t RY;
  uint8_t LX;
  uint8_t LY;
  uint8_t CH6;
  uint8_t TRAINER; /* los ultimos tres son char */
  uint8_t CH5;
  uint8_t ELEV;
 
  uint8_t data[MAX_DATOS];

  int ok = 0;
  
void setup() {
  // initialize serial communication at 9600 bits per second:
//inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);
}

// the loop routine runs over and over again forever:
void loop() {
  
  LX = analogRead(A0) >> SHIFT_10_TO_8 ;
  LY = analogRead(A1) >> SHIFT_10_TO_8 ;
  RY = analogRead(A2) >> SHIFT_10_TO_8;
  RX = analogRead(A3) >> SHIFT_10_TO_8;
  CH6 = analogRead (A4) >> SHIFT_10_TO_8;
  TRAINER = (uint8_t)digitalRead(2) * BIN_TO_8_BIT;
  CH5 = (uint8_t)digitalRead(3) * BIN_TO_8_BIT ;
  ELEV = (uint8_t)digitalRead(4) * BIN_TO_8_BIT;
                                                                             
  // read the input on analog pin 0:
  data[0] = HEADER_1;
  data[1] = HEADER_2;
  data[2] = RX;
  data[3] = RY;
  data[4] = LX;
  data[5] = LY; 
  data[6] = CH6;
  data[7] = TRAINER;
  data[8] = CH5;
  data[9] = ELEV;
  data[10] = XORChecksum8(data,MAX_DATOS-1);//mando menos uno porque el check sum es el dato 10

  bool ok = radio.write(data, sizeof(data));
  
  //reportamos por el puerto serial los datos enviados 
 
  if(ok)
  {
     Serial.println("Datos enviados"); 
  }
  else
  {
     Serial.println("no se ha podido enviar");
  }
  delay(500);

  Serial.print(RX);
   Serial.print("RX");
  Serial.print('\t');
  Serial.print(RY);
  Serial.print("RY");
  Serial.print('\t');
  Serial.print(LX);
  Serial.print("LX");
  Serial.print('\t');
  Serial.print(LY);
     Serial.print("LY");
  Serial.print('\t');
  Serial.print(CH6);
     Serial.print("CH6");
  Serial.print('\t');
  Serial.print(TRAINER);
     Serial.print("TRAINER");
  Serial.print('\t');
  Serial.print(CH5);
     Serial.print("CH5");
  Serial.print('\t');
  Serial.print(ELEV);
     Serial.print("ELEV");
  Serial.print('\n');
  delay(500);     // delay in between reads for stability
  
}
 
uint8_t XORChecksum8(byte *data, size_t dataLength)
{

    uint8_t value = 0;
    
    for (size_t i = 0; i < dataLength ; i++)
    {
       value ^= (uint8_t)data[i];
       //Serial.print(value);
       //delay(200);
    }
    return value;
}
  
 


