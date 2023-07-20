//Library Example
//The following example continually sends sequence of numbers 0..255 to the PC via Universal Serial Bus. usbdsc.c must be included in the project (via mikroC PRO for PIC IDE tool or via #include mechanism in source code).

unsigned short m, k;
unsigned short userRD_buffer[64];
unsigned short userWR_buffer[64];

void interrupt() {
  asm CALL _Hid_InterruptProc
  asm nop
}

void Init_Main() {
  // Disable all interrupts
  // Disable GIE, PEIE, TMR0IE, INT0IE,RBIE
  INTCON = 0;
  INTCON2 = 0xF5;
  INTCON3 = 0xC0;
  // Disable Priority Levels on interrupts
  RCON.IPEN = 0;
  PIE1 = 0;
  PIE2 = 0;
  PIR1 = 0;
  PIR2 = 0;

  // Configure all ports with analog function as digital
  ADCON1 |= 0x0F;

  // Ports Configuration
  TRISA = 0;
  TRISB = 0;
  TRISC = 0xFF;
  //TRISD = 0xFF;
  //TRISE = 0x07;

  LATA = 0;
  LATB = 0;
  LATC = 0;
  //LATD = 0;
  //LATE = 0;

  // Clear user RAM
  // Banks [00 .. 07] ( 8 x 256 = 2048 Bytes )
  asm {
    LFSR     FSR0, 0x000
    MOVLW    0x08
    CLRF     POSTINC0, 0
    CPFSEQ   FSR0H, 0
    BRA      $ - 2
  }

  // Timer 0
  T0CON  = 0x07;
  TMR0H  = (65536-156) >> 8;
  TMR0L  = (65536-156) & 0xFF;
  INTCON.T0IE = 1;            // Enable T0IE
  T0CON.TMR0ON = 1;
}


/** Main Program Routine **/

void main() {
  Init_Main();
  Hid_Enable(&userRD_buffer, &userWR_buffer);

  do {
    for (k = 0; k < 255; k++) {
      // Prepare send buffer
      userWR_buffer[0] = k;

      // Send the number via USB
      Hid_Write(&userWR_buffer, 1);
    }
  } while (1);

  Hid_Disable();
}