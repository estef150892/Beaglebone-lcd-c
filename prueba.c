#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
 
#include "kbhit.h"
#include "bbb_dht_read.h"
#include "beagle_gpio.h"
#include "beagle_hd44780.h"
 
 
 
int main(int argc, char** argv)
{
    int sensor = DHT11;
    int base = 1;
    int number = 15;
    int retries = 1;
    int out_short = 0;
    int out_temp = 0;
    int out_humi = 0;
    int i =0;
     
    char mensaje[16];
    int selectedPins[]={P8_14,P8_12,P8_11,P9_15,P9_13,P9_12};
    const char *pinDescription[] = {"DB7","DB6","DB5","DB4","RS","E"};
    struct gpioID enabled_gpio[6];    
    initialize_Screen(enabled_gpio,selectedPins);   
    clear_Screen(enabled_gpio);
    stringToScreen("prueba",enabled_gpio);
    goto_ScreenLine(1,enabled_gpio);
    stringToScreen("funciona?",enabled_gpio);
    sleep(2);
    clear_Screen(enabled_gpio);
     
    // Parse command-line
    for( i = 1; i < argc; ++i)
    {
        if(argv[i][0] == '-')
        {
            if(argv[i][1] == '-')
            {
                if(strcmp(argv[i], "--short") == 0) out_short = 1;
                else if(strcmp(argv[i], "--temperature") == 0) out_temp = 1;
                else if(strcmp(argv[i], "--humidity") == 0) out_humi = 1;
            }
            else
            {
                char* arg = argv[i];
                while(*(++arg))
                {
                    switch(*arg)
                    {
                        case 's': out_short = 1; break;
                        case 't': out_temp = 1; break;
                        case 'h': out_humi = 1; break;
                    }
                }
            }
        }
        else if(sensor == 0)
            sensor = atoi(argv[i]);
        else if(base == 0)
            base = atoi (argv[i]);
        else if(number == 0)
            number = atoi (argv[i]);
        else
            retries = atoi(argv[i]);
    }
  
    // Validate command-line args
    if(!out_temp && !out_humi)
    {
        out_temp = 1;
        out_humi = 1;
    }
    if(sensor == 0 ||number < 0 || base < 0)
    {
        fprintf(stderr, "Usage: %s <11|22|2302> <pin> [retries]\n", argv[0]);
        return 1;
    }
  
    if(sensor != DHT11 && sensor != DHT22 && sensor != AM2302)
    {
        fprintf(stderr, "Invalid sensor type. Possible values are:\n- 11 for DHT11\n- 22 for DHT22\n- 2302 for AM2302\n");
        return 2;
    }
    if(number < 0 || base < 0)
    {
        fprintf(stderr, "Invalid pin number.\n");
        return 2;
    }
    if(retries < 1)
        retries = 1;
  
    // Do the reading
      
    float temperature, humidity;
    int status;
    char output[48] = { 0 };
    int pos = 0;
    int io = 0;
     
    while(1){//ciclo infinito
        status = bbb_dht_read(sensor, base, number, &humidity, &temperature); //leer sensor
         
        //no se asegura que se tenga un 100% de lectura de los datos del sensor
 
        if(status != DHT_SUCCESS)//lectura erronea
        {
            //fprintf(stderr, "Error while trying to read data: %i\n", status);
            //return status;
        }
  
        // Output the result
        if(status == DHT_SUCCESS)//lectura exitosa
        {
            for(io=0;io<=47;io++)//borrar buffer
                output[io] = 0;
        pos = 0;
        if(out_temp){
            pos = sprintf(output, out_short ? "%.2f" : "T:%.2fC", temperature);//acomodo del buffer temperatura
            sprintf(mensaje, out_short ? "%.2f" : "T:%.2fC", temperature);//cadena a imprimir temperatura
            clear_Screen(enabled_gpio);
            stringToScreen(mensaje,enabled_gpio);
            goto_ScreenLine(1,enabled_gpio);
             
        }
        if(out_humi){
            pos += sprintf(output + pos, out_short ? (pos ? " %.2f" : "%.2f") : (pos ? ", H:%.2f%%" : "H:%.2f%%"), humidity);//acomodo del buffer humedad
            sprintf(mensaje, out_short ? (pos ? " %.2f" : "%.2f") : (pos ? "H:%.2f%%" : "H:%.2f%%"), humidity);//cadena a imprimir humedad
            stringToScreen(mensaje,enabled_gpio);
        }
      
        sprintf(output + pos, "\n");
        printf("\n");
        printf(output);
 
        }
        sleep(2);// tiempo muerto
    } 
    return 0;
}
