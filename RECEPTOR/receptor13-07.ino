#define PWM_CH_VAL_MIN  920   //representa un 0 lógico en el canal  (todo en microsegundos)
#define PWM_CH_VAL_MAX  2120   //representa un 1 lógico en el canal
#define PWM_PRE_PULSE   400   //tiempo entre cada pulso (cada canal)
#define PWM_SEPARATION  1500   //tiempo entre mensajes
#define PWM_MSG_MIN     (8 * PWM_CH_VAL_MIN) + (7 * PWM_PRE_PULSE) + PWM_SEPARATION //tiempo minimo del mensaje pwm 
#define PWM_MSG_MAX     (8 * PWM_CH_VAL_MAX) + (7 * PWM_PRE_PULSE) + PWM_SEPARATION //tiempo maximo del mensaje pwm
#define NUMBER_OF_CHANNELS 8
#define NUMBER_MSG_ELEMENTS 11 // 2 headers, 8 channels y chk
#define HEADER_1_POS 0 //elemento 1 de la cadena
#define HEADER_2_POS 1 //elemento 2 de la cadena
#define CHKSUM_POS 10 //elemento 11 de la cadena 
#define HEADER_1_VALUE 0x00 //verificar valores de headers !!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define HEADER_2_VALUE 0x01

#define CE_PIN 9
#define CSN_PIN 10


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


byte direccion[5] ={'c','a','n','a','l'};//Variable con la dirección del canal que se va a leer


RF24 radio(CE_PIN, CSN_PIN); //creamos el objeto radio (NRF24L01)

//variables globales
unsigned char arr_channels_byte[NUMBER_MSG_ELEMENTS]; //vector para los datos recibidos
double arr_channels_time[NUMBER_OF_CHANNELS]; //arreglo de los channels convertidos a tiempo
const int MyPin = 7;  //por este pin sale el tren de pulsos 



void setup()
{ 
  radio.begin(); //inicializamos el NRF24L01
  Serial.begin(9600); //inicializamos el puerto serie
  pinMode(MyPin, OUTPUT); //inicializo el pin "My pin" como salida (del tren de pulso) 
  radio.openReadingPipe(1, direccion); //Abrimos el canal de Lectura  
  radio.startListening();//empezamos a escuchar por el canal
 
}
float datos[3]; 
void loop() {

  
 if (radio.available()){ 

  //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Dato0= " );
     Serial.print(datos[0]);
     Serial.print(" V, ");
     Serial.print("Dato1= " );
     Serial.print(datos[1]);
     Serial.print(" ms, ");
     Serial.print("Dato2= " );
     Serial.println(datos[2]);
/*
     //Leemos los datos y los guardamos en la variable arr_channels_byte[]
     radio.read(arr_channels_byte, sizeof(arr_channels_byte);

     //FUNCION QUE VALIDE HEADER Y CHK
     if(validate_msg(arr_channels_byte) != true){}
      // return ROMPER TODO // QUEDATE QUIERO
     
     pwm_read (arr_channels_byte, arr_channels_time);
     
     for(size_t i=0; i<NUMBER_OF_CHANNELS; i++){
        BlinkPin(MyPin, arr_channels_time[i]);
        delayMicroseconds(PWM_PRE_PULSE);                    //estuvo en high lo que cada channel dice que debe estar, luego esta en low lo que vale PWM_PRE_PULSE
     }
 */    
 }
 else{
     Serial.println("No hay datos de radio disponibles");
 }
 
 delayMicroseconds(PWM_SEPARATION);

}


void BlinkPin (int pin, double msecs){  /*deja un 1 por "msec" milisegundos en el pin "pin"*/ 
  digitalWrite(pin, HIGH);   // turn433H is the voltage level)
  delayMicroseconds(msecs);                       // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
}

double convert_bit_to_usec(int bit){
  double t;
  
  t = ((bit/255)*(PWM_CH_VAL_MAX - PWM_CH_VAL_MIN)) + PWM_CH_VAL_MIN ;
  
  return t;
}

void pwm_read (unsigned char * arr, double * arr_double){

  size_t i;

  for(i=0; i<NUMBER_OF_CHANNELS; i++){
    arr_double[i]=convert_bit_to_usec(arr[i+2]);
  }
  
}

unsigned char XORChecksum8( unsigned char * arr, size_t dataLength){//datalength LARGO DEL ARREGLO MENOS 1
  
  unsigned char value = 0;

  for(size_t i = 0; i < dataLength; i++){
    value ^= (unsigned char)arr[i];
  }

  return value;
}


bool validate_msg(unsigned char * arr){ //por ahora retorno void, hasta saber como será el manejo de errores.

  //valido los header
  if(arr[HEADER_1_POS] != HEADER_1_VALUE)
    return false;

  if(arr[HEADER_2_POS] != HEADER_2_VALUE)
    return false;

  //valido el checksum
  if(arr[CHKSUM_POS] != XORChecksum8(arr, NUMBER_MSG_ELEMENTS - 1))
    return false;

    return true;
}

