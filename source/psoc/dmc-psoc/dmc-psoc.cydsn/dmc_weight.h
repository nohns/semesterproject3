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

#ifndef WEIGHT_H
#define WEIGHT_H
    #include <stdint.h>
    
    
    enum dmc_weight_number{
         WEIGHT_1 = 1,
         WEIGHT_2 = 2,
         WEIGHT_3 = 3,          
    };
    
    struct weight {
         enum dmc_weight_number weight_number;
         uint16_t result;
         int16_t tara;
         uint16_t adc_divider;
         uint16_t min;
         uint16_t max;
         uint8_t out_of_order;
    };
    
    struct weight weight1;
    struct weight weight2;
    struct weight weight3;
    
    struct weight* current_weight;

    void set_current_weight(enum dmc_weight_number current_weight);
    void weight_init();
    uint16_t measure_weight_value();
    
#endif //WEIGHT_H