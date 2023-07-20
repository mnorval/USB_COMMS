#line 1 "C:/DOCUMENTS/PROGRAMMING & ELECTRONICS/PIC MICRO/PROJECTS/MIKRO_C/USB_COMMS/USB_COMMS.c"



unsigned short m, k;
unsigned short userRD_buffer[64];
unsigned short userWR_buffer[64];

void interrupt() {
 asm CALL _Hid_InterruptProc
 asm nop
}

void Init_Main() {


 INTCON = 0;
 INTCON2 = 0xF5;
 INTCON3 = 0xC0;

 RCON.IPEN = 0;
 PIE1 = 0;
 PIE2 = 0;
 PIR1 = 0;
 PIR2 = 0;


 ADCON1 |= 0x0F;


 TRISA = 0;
 TRISB = 0;
 TRISC = 0xFF;



 LATA = 0;
 LATB = 0;
 LATC = 0;





 asm {
 LFSR FSR0, 0x000
 MOVLW 0x08
 CLRF POSTINC0, 0
 CPFSEQ FSR0H, 0
 BRA $ - 2
 }


 T0CON = 0x07;
 TMR0H = (65536-156) >> 8;
 TMR0L = (65536-156) & 0xFF;
 INTCON.T0IE = 1;
 T0CON.TMR0ON = 1;
}




void main() {
 Init_Main();
 Hid_Enable(&userRD_buffer, &userWR_buffer);

 do {
 for (k = 0; k < 255; k++) {

 userWR_buffer[0] = k;


 Hid_Write(&userWR_buffer, 1);
 }
 } while (1);

 Hid_Disable();
}
