#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h>
#include "kbhit.h"
#include <time.h>
 
#include "beagle_gpio.h"
#include "beagle_hd44780.h"
 
 
int main()
{
 
char mensaje[16];
 
    int selectedPins[]={P8_14,P8_12,P8_11,P9_15,P9_13,P9_12};
    const char *pinDescription[] = {"DB7","DB6","DB5","DB4","RS","E"};
 
    struct gpioID enabled_gpio[6];    
 
    initialize_Screen(enabled_gpio,selectedPins);   
     
    clear_Screen(enabled_gpio);
    stringToScreen("prueba2",enabled_gpio);
 
    goto_ScreenLine(1,enabled_gpio);
    stringToScreen("funciona?",enabled_gpio);
     
    sleep(2);
     
    while(1){
    printf("Mensaje para imprimir: ");
    gets(mensaje);
    clear_Screen(enabled_gpio);
    goto_ScreenLine(1,enabled_gpio);
    stringToScreen(mensaje,enabled_gpio);
    }
 
    terminate_Screen(enabled_gpio,selectedPins);
 
    return 1;
}
