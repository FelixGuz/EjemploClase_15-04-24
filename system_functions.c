 // FileName:        system_functions.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Authors:         Jos� Luis Chac�n M. y Jes�s Alejandro Navarro Acosta.
 // Updated:         12/2018

#include "system.h"

void System_InicialiceIO(void)
{
    GPIO_init_board();
}

void System_InicialiceUART (void)
{
    UART_init();
}

void funcion_inicial (void)
{
    GPIO_setOutput(BSP_LED1_PORT,  BSP_LED1,  1);
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);
    GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  0);
    GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);
    UART_putsf(MAIN_UART, "Hola version 8.\r\n");
}

/*Declaracion de variables para contadores de pulsaciones de cada Switch/Push B*/
uint8_t SW_1 = 0;
uint8_t SW_2 = 0;

void process_events(void)
{
    static bool bandera_blink = FALSE;
    /*Ciclo infinito de parpadeo*/
    if(bandera_blink==FALSE){
        P1OUT ^= BIT0;
        _delay_cycles(1000000);
    }
    else{
        P1OUT &= ~BIT0;
    }



    //---------Control_PB_1----------------------------------------------------------------------------------------------------------------------------//
    if(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE) // Entra cuando se presiona el bot�n 1.*/
    {
        SW_1++;    /*Incrementamos en 1 el contador cada que el Switch 1 sea pulsado*/
        /*Caso 2, con dos pulsos en SW 1, Enciende color Verde.*/
        if(SW_1 == 1)
        {
            UART_putsf(MAIN_UART, "Se ha pulsado una vez SW 1\n\r");
        }
        if(SW_1 == 2)
        {
            UART_putsf(MAIN_UART, "Se ha pulsado dos veces SW 1\n\r");
            if(bandera_blink == FALSE)
            {
                bandera_blink = TRUE;   /*Cambiamos estado de la bandera*/
                GPIO_setOutput(BSP_LED2_PORT, BSP_LED2, 0); /*RGB_RED_OFF*/
                GPIO_setOutput(BSP_LED2_PORT, BSP_LED3, 1); /*RGB_GREEN_ON*/
                GPIO_setOutput(BSP_LED2_PORT, BSP_LED4, 0); /*RGB_BLUE_OFF*/
            }
        }
        else
        {
            bandera_blink = FALSE; /*REGRESA EL ESTADO DE LA VARIABLE A FALSE*/
        }
        if( SW_1 == 3)
        {
            UART_putsf(MAIN_UART, "Se ha reiniciado ambas cuentas\n\r");
            SW_1 = 0;
            SW_2 = 0;
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED2, 0); //RGB_RED_OFF*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED3, 0); //RGB_GREEN_OFF*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED4, 0); //RGB_BLUE_OFF*/
        }
      while(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE);
    }


    //---------Control_PB_2----------------------------------------------------------------------------------------------------------------------------//
    if(GPIO_getInputPinValue(BSP_BUTTON2_PORT, BSP_BUTTON2) !=BOARD_BUTTON_NORMAL_STATE) /*Entra cuando se presiona el bot�n 2.*/
    {
    SW_2++;    /*Incrementamos en 1 cada que el Switch 2 es pulsado*/

    /*Caso 1 con un pulso enciende Magenta:*/
    if(SW_2 == 1)
    {
        UART_putsf(MAIN_UART, "Se ha pulsado una vez SW 2\n\r");
        if(bandera_blink == FALSE)
        {
            bandera_blink = TRUE;   /*Cambiamos estado de la bandera*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED2, 1); /*RGB_RED_OFF*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED3, 0); /*RGB_GREEN_OFF*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED4, 1); /*RGB_BLUE_ON*/
        }
    }
    else
    {
        bandera_blink = FALSE; /*REGRESA EL ESTADO DE LA VARIABLE A FALSE*/
    }
    /*Caso 3 con un pulso enciende Rojo:*/
    if(SW_2 == 2)
    {
        UART_putsf(MAIN_UART, "Se ha pulsado dos veces SW 2\n\r");
        if(bandera_blink == FALSE)
        {
            bandera_blink = TRUE;   /*Cambiamos estado de la bandera*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED2, 1); /*RGB_RED_ON*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED3, 0); /*RGB_GREEN_OFF*/
            GPIO_setOutput(BSP_LED2_PORT, BSP_LED4, 0); /*RGB_BLUE_OFF*/
        }
    }

    if(SW_2 == 3)
    {
        UART_putsf(MAIN_UART, "Se ha reiniciado ambas cuentas\n\r");
        SW_1 = 0;
        SW_2 = 0;
        GPIO_setOutput(BSP_LED2_PORT, BSP_LED2, 0); /*RGB_RED_OFF*/
        GPIO_setOutput(BSP_LED2_PORT, BSP_LED3, 0); /*RGB_GREEN_OFF*/
        GPIO_setOutput(BSP_LED2_PORT, BSP_LED4, 0); /*RGB_BLUE_OFF*/
    }
   while(GPIO_getInputPinValue(BSP_BUTTON2_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE);
    }
}
