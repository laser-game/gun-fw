#include "global.hpp"

Global *global = Global::instance();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == global->trigger->get_pin())
    {
        if (global->trigger->is_active())
        {
            global->color_driver->rgb(RGB(1, 1, 1));
            global->laser->on();
            global->ir->tx();
            global->laser->off();
        }
        else
        {
            global->color_driver->rgb(0, 0, 0);
        }
    }
}
