#include "globals.hpp"

Global *global = Global::instance();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == global->trigger->get_pin())
    {
        if (global->trigger->is_active())
        {
            RGB green(0, 100, 0);
            global->color_driver->rgb(green);
        }

        else
        {
            global->color_driver->rgb(0, 0, 0);
        }
    }
}
