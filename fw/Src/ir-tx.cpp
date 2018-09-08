#include "ir-tx.hpp"

IR::IR(
    GPIO_TypeDef *     port,
    uint16_t           pin,
    TIM_HandleTypeDef *htim_measure,
    TIM_HandleTypeDef *htim_carrier,
    uint32_t           tim_carrier_channel
)
{
    this->tim_carrier_channel = tim_carrier_channel;
    led_ir        = Out(port, pin);
    timer_measure = Timer(htim_measure);
    timer_carrier = Timer(htim_carrier);
    timer_carrier.start();
    timer_measure.start();
    HAL_TIM_OC_Start(htim_carrier, tim_carrier_channel);
    set_address(0);
}

void IR::set_address(uint8_t address)
{
    this->address = address;
    this->crc     = CRC16::calculate(address);
    this->data    = (address << 16) | crc;
}

void IR::tx(void)
{
    // start puls
    timer_measure.set_cnt(0);
    led_ir.on();
    while (timer_measure.get_cnt() < IR_TIM_START_PULS)
        ;

    timer_measure.set_cnt(0);
    led_ir.off();
    while (timer_measure.get_cnt() < IR_TIM_START_SPACE)
        ;

    // data
    for (uint8_t i = 0; i < 24; i++)
    {
        timer_measure.set_cnt(0);
        led_ir.on();
        while (timer_measure.get_cnt() < IR_TIM_DATA_PULS)
            ;

        timer_measure.set_cnt(0);
        led_ir.off();
        if ( (data << i) & 0x00800000)
        {
            while (timer_measure.get_cnt() < IR_TIM_DATA1_SPACE)
                ;
        }
        else
        {
            while (timer_measure.get_cnt() < IR_TIM_DATA0_SPACE)
                ;
        }
    }

    // split puls for detect width end space
    timer_measure.set_cnt(0);
    led_ir.on();
    while (timer_measure.get_cnt() < IR_TIM_END_PULS)
        ;
    led_ir.off();

    // data space
    while (timer_measure.get_cnt() < IR_TIM_PACKET_SPACE)
        ;
} // IR::tx
