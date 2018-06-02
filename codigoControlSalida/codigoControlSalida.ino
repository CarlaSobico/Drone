/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

/* the setup routine runs once when you press reset:*/
#define MAX_DATOS 11
#define HEADER_1 0x01
#define HEADER_2 0x03

  
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

  Serial.begin(9600);
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  LX = (uint8_t)analogRead(A0);
  LY = (uint8_t)analogRead(A1);;
  RY = (uint8_t)analogRead(A2);
  RX = (uint8_t)analogRead(A3);
  CH6 = (uint8_t)analogRead (A4);
  TRAINER = (uint8_t)digitalRead(2);//ver si va con D antes del 2
  CH5 = (uint8_t)digitalRead(3);
  ELEV = (uint8_t)digitalRead(4);
                                                                             
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

  //Serial.print(data[10]);


  delay(300);//para probar el dato en pantalla
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
  /*  // print out the value you read:
  Serial.print(RX);
  Serial.print('\t');
  Serial.print(RY);
  Serial.print('\t');
  Serial.print(LX);
  Serial.print('\t');
  Serial.print(LY);
  Serial.print('\t');
  Serial.print(CH6);
  Serial.print('\t');
  Serial.print(TRAINER);
  Serial.print('\t');
  Serial.print(CH5);
  Serial.print('\t');
  Serial.print(ELEV);
  Serial.print('\n');
  delay(1);     // delay in between reads for stability*/
  

/*void itoc(
{
int a=1;

char b[2];

String str;

str=String(a);

str.toCharArray(b,2);
}*/
 


