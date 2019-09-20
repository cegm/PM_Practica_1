// d) Rutina de tiempo de 0.5s - se hace parpadear 1 LED a 1Hz.

void setup()
{
DDRB = DDRB | B11111111; // Data Direction Register B: Inputs 0-6, Output 7
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
"LDI r22, 62 \n\t"
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
