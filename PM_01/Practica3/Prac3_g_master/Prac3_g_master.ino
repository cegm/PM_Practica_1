
//SPI MASTER (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST
#include<SPI.h>                             //Library for SPI 
int button_1 = 8;
int button_2 = 9;
//int SS = 53;
int buttonvalue;
int x;

void setup (void)
{
  Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200 
  
  pinMode(button_1,INPUT);                //Sets pin 2 as input 
  pinMode(button_2,INPUT);
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
}
void loop(void)
{
  
  int var1 = digitalRead(button_1);
  int var2 = digitalRead(button_2);
  
  if(var1 == LOW && var2 == LOW) {
    transmission(0b00);
  }
  if(var1 == LOW && var2 == HIGH) {
    transmission(0b01);
  }
  if(var1 == HIGH && var2 == LOW) {
    transmission(0b10);
  }
  if(var1 == HIGH && var2 == HIGH) {
    transmission(0b11);
  }

  
  delay(50);
}

void transmission(byte frame) {
  byte Mastersend,Mastereceive;  
  digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master                           
  Mastereceive=SPI.transfer(frame); //Send the mastersend value to slave also receives value from slave
}
