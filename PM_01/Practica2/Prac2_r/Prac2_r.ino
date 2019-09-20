// r) SEMAFORO con Timers
  // V_1 - digital pin 53
  // A_1 - digital pin 52
  // R_1 - digital pin 51
  // V_2 - digital pin 10
  // A_2 - digital pin 11
  // R_2 - digital pin 12

void setup()
{
DDRB = DDRB | B11111111; // Data Direction Register B: Inputs 0-6, Output 7
cli();
TCCR1B = 0; 
TCCR1A = 0; //Output compare mode NORMAL, PWM disabled.
TCCR1B |= (1 << CS12); //Divide clock by 256. 62,500 counts per second. Timer can count up to 65536.
TCNT1 = 336; //65536-65200 = 336;
TIMSK1 |= (1 << TOIE1); // Timer Overflow Interruption Enable;
sei();

asm("LDI r22,0 \n\t"); //Sets counter register on zero
}

ISR(TIMER1_OVF_vect) //Interruption
{
  TCNT1 = 336; //Resets timer
  asm(
    "INC r22 \n\t" //Increments counter that helps change states
  );
}

void loop(){
asm (
"inicio: \n\t" 
"cpi r22, 0 \n\t" //compares r22 with constant 0 
"BRNE D0 \n\t" // If r22 != 0 branch to tag D0
"call ESTADO_0 \n\t" // If r22 = 0 call ESTADO_0
"D0: \n\t" //If r22 != 0 //Subroutine returns to this instruction.
"cpi r22, 6 \n\t" //compare r22 with constant 5
"BRLO D0 \n\t" // If lower compare again
"call ESTADO_1 \n\t" //if r22 = 5 call ESTADO_1
"D1: \n\t"
"cpi r22, 7 \n\t" //compare r22 with constant 6
"BRLO D1 \n\t" // If lower compare again
"call ESTADO_2 \n\t" //if r22 = 6 call ESTADO_2
"D2: \n\t"
"cpi r22, 12 \n\t" //compare r22 with constant 11
"BRLO D2 \n\t" // If lower compare again
"call ESTADO_3 \n\t" //if r22 = 11 call ESTADO_2
"D3: \n\t"
"cpi r22, 13 \n\t" //compare r22 with constant 11
"BRLO D3 \n\t" // If lower compare again
"call ESTADO_4 \n\t" //if r22 = 12 call ESTADO_4
"LDI r22,0 \n\t"
"jmp main \n\t"


"ESTADO_0: \n\t" //Sets green_1 and red_2. 
"sbi 0x05,0x00 \n\t"
"sbi 0x05,0x06 \n\t"
"ret \n\t" 

"ESTADO_1: \n\t" //Sets yellow_1 and clears green_1
"cbi 0x05,0x00 \n\t"
"sbi 0x05,0x01 \n\t"
"ret \n\t"

"ESTADO_2: \n\t" //Clears yellow_1, sets red_1; clears red_2 and sets green_2
"cbi 0x05,0x01 \n\t"
"cbi 0x05,0x06 \n\t"
"sbi 0x05,0x02 \n\t"
"sbi 0x05,0x04 \n\t"
"ret \n\t"

"ESTADO_3: \n\t" //Sets yellow_2 and clears green_2
"cbi 0x05,0x04 \n\t"
"sbi 0x05,0x05 \n\t"
"ret \n\t"

"ESTADO_4: \n\t" //clears yellow_2 and clears red_1
"cbi 0x05,0x05 \n\t"
"cbi 0x05,0x02 \n\t"
"ret \n\t"
);

}
