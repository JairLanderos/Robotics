//Conexiones de LCD al PIC
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;
sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;

unsigned int opcion = 1;            //Opción para modo automático o manual
long joy1_x;        //Valor ADC del joystick 1 eje X
long joy1_y;        //Valor ADC del joystick 1 eje Y
long joy2_x;        //Valor ADC del joystick 2 del eje X
long angulo;        //Ángulo al que se posicionará el servomotor
long duty;          //Ciclo de trabajo necesario para mover el servo
char digito = 48;

int modo_seleccion(void);      //Función para seleccionar el modo del robot
long map(long x, long in_min, long in_max, long out_min, long out_max);    //Función para mapear
void VDelay_us(unsigned time_us);          //Función para hacer un delay con variable como parámetro

void main(){
     OPTION_REG = OPTION_REG & 0x7F;       //Activa Weak Pull-up
     TRISA = 0x0F;                         //Pines RA0, RA1, RA2 Y RA3 como entrada
     ANSEL = 0x0F;                         //Entradas analógicas en puerto A
     INTCON = 0;                           //Interrupciones deshabilitadas
     ADCON0.ADON=1;                        //Inicia ADC
     TRISD = ~0x07;                        //Pines RD0, RD1 y RD2 como salida
     PORTD = 0x00;
     ANSELH = 0;                           //Entradas digitales
     delay_ms(100);
     
     Lcd_init();                    //Inicia el LCD
     Lcd_cmd(_LCD_CLEAR);           //Limpia la pantalla
     Lcd_cmd(_LCD_CURSOR_OFF);      //Deshabilita el cursor
     Lcd_out(1,1,"    Proyecto");
     Lcd_out(2,1,"Manipulador 3DOF");
     delay_ms(2000);
     
     while(1){
     Lcd_cmd(_LCD_CLEAR);           //Limpia la pantalla
     Lcd_out(1,1,"1.Automatico");
     Lcd_out(2,1,"2.Manual");
     Lcd_Chr(1,16,60);
     opcion = modo_seleccion();     //Elección del modo del manipulador
         if(opcion==1){             //Modo automático
         Lcd_cmd(_LCD_CLEAR);
         Lcd_out(1,1,"Modo automatico");
         Lcd_out(2,1,"Regresar");
         Lcd_Chr(2,16,60);      //Muestra la flecha en la línea 2
         while(PORTB.RB2){
            if(~PORTB.RB3){             //Detección de objeto por el sensor
            
                       UART1_Init(9600);            //Inicia UART
                       
                       //Articulación 1 = 0°
                       duty = map(0, -90, 90, 1000, 2000);
                       PORTD.RD0 = 1;
                       VDelay_us(duty);
                       PORTD.RD0 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("0*");
                       delay_ms(1000);
                       
                       //Articulación 2 = -45°
                       duty = map(-45, -90, 90, 1000, 2000);
                       PORTD.RD1 = 1;
                       VDelay_us(duty);
                       PORTD.RD1 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("-45*");
                       delay_ms(1000);
                       
                       //Articulación 3 = -30°
                       duty = map(-30, -90, 90, 1000, 2000);
                       PORTD.RD2 = 1;
                       VDelay_us(duty);
                       PORTD.RD2 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("-20*");
                       delay_ms(1000);
                       
                       //Articulación 1 = -90
                       duty = map(-90, -90, 90, 1000, 2000);
                       PORTD.RD0 = 1;
                       VDelay_us(duty);
                       PORTD.RD0 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("-90*");
                       delay_ms(1000);
                       
                       //Articulación 2 = -25
                       duty = map(-25, -90, 90, 1000, 2000);
                       PORTD.RD1 = 1;
                       VDelay_us(duty);
                       PORTD.RD1 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("-25*");
                       delay_ms(1000);
                       
                       //Articulación 3 = -45
                       duty = map(-45, -90, 90, 1000, 2000);
                       PORTD.RD2 = 1;
                       VDelay_us(duty);
                       PORTD.RD2 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("-45*");
                       delay_ms(1000);
                       
                       //Articulación 0 = 0
                       duty = map(0, -90, 90, 1000, 2000);
                       PORTD.RD0 = 1;
                       VDelay_us(duty);
                       PORTD.RD0 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("0*");
                       delay_ms(1000);
                       
                       //Articulación 2 = 0
                       duty = map(0, -90, 90, 1000, 2000);
                       PORTD.RD1 = 1;
                       VDelay_us(duty);
                       PORTD.RD1 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("0*");
                       delay_ms(1000);
                       
                       //Articulación 3 = 0
                       duty = map(0, -90, 90, 1000, 2000);
                       PORTD.RD0 = 1;
                       VDelay_us(duty);
                       PORTD.RD0 = 0;
                       VDelay_us(20000-duty);
                       UART1_Write_Text("0*");
                       delay_ms(1000);
                       
            }
         }
         }
         else if(opcion==2){          //Modo manual
         Lcd_cmd(_LCD_CLEAR);
         Lcd_out(1,1,"Modo manual");
         Lcd_out(2,1,"Regresar");
         Lcd_Chr(2,16,60);      //Muestra la flecha en la línea 2
         UART1_Init(9600);
         while(PORTB.RB2){
                       delay_ms(1000);
                       
                       joy1_x = ADC_Read(0);        //Lectura analógica canal 0
                       angulo = map(joy1_x, 0, 1023, -90, 90);
                       duty = map(angulo, -90, 90, 1000, 2000);
                       PORTD.RD0 = 1;
                       VDelay_us(duty);
                       PORTD.RD0 = 0;
                       VDelay_us(20000-duty);
                       longtostr(angulo/10,digito);
                       UART1_Write_Text(digito);
                       longtostr(abs(angulo%10),digito);
                       UART1_Write_Text(digito);
                       UART1_Write_Text("*");

                       joy1_y = ADC_Read(1);       //Lectura analógica canal 1
                       angulo = map(joy1_y, 0, 1023, -90, 90);
                       duty = map(angulo, -90, 90, 1000, 2000);
                       PORTD.RD1 = 1;
                       VDelay_us(duty);
                       PORTD.RD1 = 0;
                       VDelay_us(20000-duty);
                       longtostr(angulo/10,digito);
                       UART1_Write_Text(digito);
                       longtostr(abs(angulo%10),digito);
                       UART1_Write_Text(digito);
                       UART1_Write_Text("*");
                       
                       joy2_x = ADC_Read(2);       //Lectura analógica canal 2
                       angulo = map(joy2_x, 0, 1023, -90, 90);
                       duty = map(angulo, -90, 90, 1000, 2000);
                       PORTD.RD2 = 1;
                       VDelay_us(duty);
                       PORTD.RD2 = 0;
                       VDelay_us(20000-duty);
                       longtostr(angulo/10,digito);
                       UART1_Write_Text(digito);
                       longtostr(abs(angulo%10),digito);
                       UART1_Write_Text(digito);
                       UART1_Write_Text("*");
                       }
         }
     }

}

int modo_seleccion(){
    delay_ms(1000);
    while(PORTB.RB2){             //Repite hasta que se selecciona una opción
    
      if(~PORTB.RB0){             //Botón ARRIBA
           Lcd_Chr(2,16,32);      //Borra la flecha de la línea 2
           Lcd_Chr(1,16,60);      //Muestra la flecha en la línea 1
           opcion = 1;
       }

       else if(~PORTB.RB1){       //Botón ABAJO
           Lcd_Chr(1,16,32);      //Borra la flecha de la línea 1
           Lcd_Chr(2,16,60);      //Muestra la flecha en la línea 2
           opcion = 2;
           }
    }
    delay_ms(1000);
    return opcion;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void VDelay_us(unsigned time_us){
        unsigned n_cyc;
  n_cyc = Clock_MHz()>>2;
  n_cyc *= time_us>>4;
  while (n_cyc--){
      asm nop;
      asm nop;
  }
}