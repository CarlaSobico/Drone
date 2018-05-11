/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
/*
int pushButton2 = 2;
int pushButton3 = 3;
int pushButton4 = 4;
*/
/* the setup routine runs once when you press reset:*/
#define MAX_DATOS 10
  
  short int R1X;
  short int R1Y;
  short int R2X;
  short int R2Y;
  short int CH6;
  short int TRAINER; /* los ultimos tres son char */
  short int CH5;
  short int ELEV;
 
  char data[MAX_DATOS];

  

void setup() {
  // initialize serial communication at 9600 bits per second:


  Serial.begin(9600);

  
}

// the loop routine runs over and over again forever:
void loop() {
  R1X =/* analogRead(A0);*/1;
  R1Y =/* analogRead(A1);*/2;
  R2X =/* analogRead(A3);*/3;
  R2Y =/* analogRead(A2);*/4;
  CH6 =/* analogRead (4);*/5;
  TRAINER = /*digitalRead(2);*/6;
  CH5 = /*digitalRead(3);*/7;
  ELEV = /*digitalRead(4);*/8;
 
  // read the input on analog pin 0:
  data[0]='0';/*header*/
  data[1]=(char*)R1X;
  data[2]=(char*)R1Y;
  data[3]= (char*)R2X;
  data[4]= (char*)R2Y;
  data[5]= (char*)CH6;
  data[6]= (char*)TRAINER;
  data[7]= (char*)CH5;
  data[8]= (char*)ELEV;
  data[9]=(char*)XORChecksum8(data,MAX_DATOS-1);

  Serial.write(data[9]);
  delay(1000);
}
 
uint8_t XORChecksum8(byte *data, size_t dataLength)
{

   uint8_t value = 0;
  for (size_t i = 1; i+1 < dataLength ; i++)
  {
  value ^= (uint8_t)data[i];
  Serial.print(value);
  }
  return value;
}

  

/*void itoc(
{
int a=1;

char b[2];

String str;

str=String(a);

str.toCharArray(b,2);
}*/
 
 /* // print out the value you read:
  Serial.print(R1X);
  Serial.print('\t');
  Serial.print(R1Y);
  Serial.print('\t');
  Serial.print(R2X);
  Serial.print('\t');
  Serial.print(R2Y);
  Serial.print('\t');
  Serial.print(CH6);
  Serial.print('\t');
  Serial.print(TRAINER);
  Serial.print('\t');
  Serial.print(CH5);
  Serial.print('\t');
  Serial.print(ELEV);
  Serial.print('\n');
  delay(1);     // delay in between reads for stability
}*/
