#ifndef __GLOBALS_INLUDED__
#define __GLOBALS_INLUDED__

#include "stm32f0xx_hal.h"

#include "cm-gpio.hpp"
#include "cm-uart.hpp"
#include "cm-color-driver.hpp"

using namespace std;

class Global
{
private:
    Global(){ };
public:
    inline static Global * instance()
    {
        static Global object;
        return &object;
    }

    Out *laser;
    Out *flashlight_wh;
    Out *flashlight_uv;
    In *trigger;
    In *fuse;
    UART *uart;
    ColorDriver *color_driver;

    inline void init(void)
    { }
};

extern Global *global;

#endif // ifndef __GLOBALS_INLUDED__
