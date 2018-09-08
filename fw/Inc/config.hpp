#ifndef __CONFIG_INLUDED__
#define __CONFIG_INLUDED__

#include "cm-hal.hpp"
#include "cm-rgb.hpp"
#include "cm-gun.hpp"

class Config
{
private:
    bool is_alive;
    bool is_reset;
    uint8_t address;
    RGB color;
    gun_button_function_t button_function;
public:
    inline Config()
    {
        address         = 0;
        button_function = GUN_BUTTON_FUNCTION_DEACTIVATE;
        color.set_rgb(1, 1, 1);
        live = true;
    }
};

#endif // ifndef __CONFIG_INLUDED__
