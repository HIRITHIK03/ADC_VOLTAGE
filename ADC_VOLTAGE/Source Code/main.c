#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "ADC0_Configure.h"

// Define memory-mapped register address for ADC FIFO
#define ADC0_SSFIFO3       (*((volatile uint32_t *)0x400380A8U)) // ADC Sample Sequence Result FIFO

// Global variables to store ADC resolution and voltage
int resolution = 0;
float voltage = 0;

int main(void)
{
    //Configure ADC0
    ADC0_Configure();

    while(1) //Infinite Loop
    {
        // Trigger ADC conversion
        ADCProcessorTrigger(ADC0_BASE, 3);

        // Wait for ADC conversion to complete
        while(!ADCIntStatus(ADC0_BASE, 3, false));

        // Clear ADC interrupt
        ADCIntClear(ADC0_BASE, 3);

        // Read ADC result from FIFO
        resolution = ADC0_SSFIFO3;

        // Convert ADC resolution to voltage
        voltage = (float)resolution / 819.2; // Assuming 12-bit ADC and Vref = 5V

    }
}
