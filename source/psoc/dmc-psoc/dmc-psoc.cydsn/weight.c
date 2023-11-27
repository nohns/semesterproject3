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


    #include "weight.h"
    #include "project.h"
    
    struct weight* current_weight;
    
    static int NUM_OF_MEASUREMENTS = 1;
    
    enum WEIGHT_DIVIDE{
        WEIGHT_1_DIVIDER = 0,
        WEIGHT_2_DIVIDER = 0,
        WEIGHT_3_DIVIDER = 0,
    };
    
    enum WEIGHT_MIN{
        WEIGHT_1_MIN = 0,
        WEIGHT_2_MIN = 0,
        WEIGHT_3_MIN = 0,
        
    };
    enum  WEIGHT_MAX{
       WEIGHT_1_MAX = 0,
       WEIGHT_2_MAX = 0,
       WEIGHT_3_MAX = 0,        
    };
    
   
void kalibrate_weights()
{
    weight1.adc_divider = WEIGHT_1_DIVIDER;
    weight2.adc_divider = WEIGHT_2_DIVIDER;
    weight3.adc_divider = WEIGHT_3_DIVIDER;
    
    weight1.min = WEIGHT_1_MIN;
    weight2.min = WEIGHT_2_MIN;
    weight3.min = WEIGHT_3_MIN;
    
    weight1.max = WEIGHT_1_MAX;
    weight2.max = WEIGHT_2_MAX;
    weight3.max = WEIGHT_3_MAX;
}

void set_current_weight(enum dmc_weight_number weight_number)
{
    switch(weight_number)
    {
        case WEIGHT_1:
    {
        current_weight = &weight1;
        break;
    }
        case WEIGHT_2:
    {
        current_weight = &weight2;
        break;
    }
        case WEIGHT_3:
    {
        current_weight = &weight3;
        break;
    }
    default: current_weight = NULL; 
    }
}


    
uint16_t measure_weight(enum dmc_weight_number weight_number)
{
    set_current_weight(weight_number);
    
    uint16_t result;
    
    for (int i = 0; i < NUM_OF_MEASUREMENTS; i++)
    {
        
        if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
            {
                result += ADC_SAR_1_GetResult16();
            }
    }
    return result/NUM_OF_MEASUREMENTS;

};

