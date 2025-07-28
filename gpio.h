#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
	low,
	high
}PinState;

typedef enum {
	gpio_out,
	gpio_in
}GPIO_Mode;

typedef struct {
	uint8_t gpio_mode;
	uint8_t gpio_reg;
}GPIO;

typedef enum {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD
}GPIO_Port;

extern GPIO GPIOx[4];
extern uint8_t gpio_reg_init;

GPIO* get_GPIO(const char* name);
void gpio_create(GPIO* gpio);
void gpio_mode(GPIO* gpio, int pin, GPIO_Mode mode);
void set_gpio (GPIO* gpio, int pin, PinState state);
void toggle_gpio (GPIO* gpio, int pin);
void print_pin_state (GPIO* gpio, int pin);
void print_gpio_reg (GPIO*);
void print_pin_mode (GPIO* gpio, int pin);
void print_mode_reg (GPIO*);

#endif
