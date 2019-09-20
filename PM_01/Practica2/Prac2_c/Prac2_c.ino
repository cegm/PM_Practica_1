// c) LEDs a 1/4Hz, 1/2Hz, 1Hz, 2Hz con subrutinas.

void setup()
{
DDRB = DDRB | B1111111; // Data Direction Register B: Inputs 0-6, Output 7
}

void loop()
{

asm (
 
"inicio: \n\t"
"LDI r23, 15 \n\t"
"count: \n\t"
"COM r23 \n\t"
"OUT 0x05, r23  \n\t"
"COM r23 \n\t"
"DEC r23  \n\t"
"BREQ inicio \n\t"
"call tiempo \n\t"
"jmp count \n\t"
"jmp main \n\t"

"tiempo: \n\t"
"LDI r22, 15 \n\t"
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
