// i) INTERRUPCION EXTERNA CON PUSH BUTTON.
//    INT1 - digital pin 20.
//    LED1 (f = 1 Hz) - 
//    LED2 (INT)

void setup()
{
Serial.begin(115200);
DDRB = DDRB | B11111111; // Data Direction Register B: Inputs 0-6, Output 7
DDRA = DDRA | B11111111; // Data Direction Register B: Inputs 0-6, Output 7

cli();
DDRD &= ~(1 << DDD1); // PORTD1 is now an input
PORTD |= (1 << PORTD1); // Pull-up activated
EICRA |= (1 << ISC10); // Sets INT1 to trigger on ANY logic change
EIMSK |= (1 << INT1); // Turns on INT1
asm("LDI r23, 0 \n\t");
sei(); //Turn on interrupts
}
ISR(INT1_vect)
{
  asm (
   "INC r23 \n\t"
   "out 0x02,r23 \n\t"
);
}

void loop()
{
  
asm (

"inicio: \n\t" 
"sbi 0x05,0x01 \n\t"
"call tiempo \n\t"
"cbi 0x05,0x01 \n\t"
"call tiempo \n\t"
"jmp main \n\t"

"tiempo: \n\t"
"LDI r22, 61 \n\t"
"LOOP_3: \n\t"
"LDI r21, 255 \n\t"
"LOOP_2: \n\t"
"LDI r20, 255 \n\t"
"LOOP_1: \n\t"
"DEC r20 \n\t"
"BRNE LOOP_1 \n\t"
"DEC r21 \n\t"
"BRNE LOOP_2 \n\t"
"DEC r22 \n\t"
"BRNE LOOP_3 \n\t"
"ret \n\t"
);
}
