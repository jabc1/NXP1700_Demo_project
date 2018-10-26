#ifndef _uart_h
#define _uart_h
#include <lpc17xx.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "debug_frmwrk.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"



void uart_config0(uint32_t Baud_rate);


#endif

