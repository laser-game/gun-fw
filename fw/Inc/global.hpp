#ifndef __GLOBALS_INLUDED__
#define __GLOBALS_INLUDED__

#include "cm-hal.hpp"
#include "cm-gpio.hpp"
#include "cm-uart.hpp"
#include "cm-color-driver.hpp"
#include "cm-crc.hpp"
#include "ir-tx.hpp"

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
    In *button;
    UART *uart;
    ColorDriver *color_driver;
    IR *ir;

    inline void init(void)
    {
        CRC16::init();
    }
};

extern Global *global;

#endif // ifndef __GLOBALS_INLUDED__
