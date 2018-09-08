#ifndef __IR_TX_INLUDED__
#define __IR_TX_INLUDED__

#include "cm-hal.hpp"
#include "cm-ir.hpp"
#include "cm-crc.hpp"
#include "cm-timer.hpp"
#include "cm-gpio.hpp"

class IR
{
private:
    uint16_t crc;
    uint32_t data;
    uint8_t address;
    uint32_t tim_carrier_channel;
    Out led_ir;
    Timer timer_carrier;
    Timer timer_measure;
public:
    IR(
        GPIO_TypeDef *     port,
        uint16_t           pin,
        TIM_HandleTypeDef *htim_measure,
        TIM_HandleTypeDef *htim_carrier,
        uint32_t           tim_carrier_channel
    );
    void set_address(uint8_t address);
    void tx(void);
};

#endif // ifndef __IR_TX_INLUDED__
