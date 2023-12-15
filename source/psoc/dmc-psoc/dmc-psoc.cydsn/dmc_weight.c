/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */


    #include "dmc_weight.h"
    #include "project.h"
    #include <stdio.h>
    
    
    uint8_t NUM_OF_MEASUREMENTS = 3;
 
void weight_init()
    {
    weight_selector_Init();
    weight_adc_Start();
    weight_adc_StartConvert();
           
    weight1.adc_divider = 1849;
    weight2.adc_divider = 1097;
    weight3.adc_divider = 1772;
    
    weight1.min = 740;
    weight2.min = 320;
    weight3.min = 460;
    
    weight1.max = 2040;
    weight2.max = 1051;
    weight3.max = 1708;
    
    weight1.weight_number = WEIGHT_1;
    weight2.weight_number = WEIGHT_2;
    weight3.weight_number = WEIGHT_3;
    
    weight1.out_of_order = 0;
    weight2.out_of_order = 0;
    weight3.out_of_order = 0;
    
    
    weight1.tara = 0;
    weight2.tara = 0;
    weight3.tara = 0;
    
    set_current_weight(WEIGHT_1);
    weight1.result = measure_weight_value();
    set_current_weight(WEIGHT_2);
    weight2.result = measure_weight_value();
    set_current_weight(WEIGHT_3);
    weight3.result = measure_weight_value();
    
    }
    
void set_current_weight(enum dmc_weight_number weight_number)
{
    switch(weight_number)
    {
        case WEIGHT_1:
    {
        current_weight = &weight1;
        weight_selector_Select(0);
        return;
    }
        case WEIGHT_2:
    {
        current_weight = &weight2;
        weight_selector_Select(1);
        return;
    }
        case WEIGHT_3:
    {
        current_weight = &weight3;
        weight_selector_Select(2);
        return;
    }
    }
}


    
uint16_t measure_weight_value()
{
    uint32_t result = 0;
    for (int8_t i = 0; i < NUM_OF_MEASUREMENTS; i++)
    {
        
        if (weight_adc_IsEndConversion(weight_adc_WAIT_FOR_RESULT))
            {
                result += weight_adc_GetResult16();
            }
    }
    return result/NUM_OF_MEASUREMENTS;
};



