#include "gpio.h"
#include <stdio.h>
#include <string.h>

uint8_t gpio_reg_init = 0x00;
GPIO GPIOx[4];

GPIO* get_GPIO(const char* name) {
	if (strcmp(name, "gpioa") == 0)
		return &GPIOx[GPIOA];
	else if (strcmp(name, "gpiob") == 0)
		return &GPIOx[GPIOB];
	else if (strcmp(name,"gpioc") == 0)
		return &GPIOx[GPIOC];
	else if (strcmp(name, "gpiod") == 0)
		return &GPIOx[GPIOD];
	else
		return NULL;
}

void gpio_create(GPIO* gpio) {
	if (gpio != NULL)
		gpio->gpio_reg = gpio_reg_init;
}

void set_gpio (GPIO *gpio, int pin, PinState state) {
	if (gpio == NULL) {
		printf("GPIO pointer is null in set_gpio\n");
		exit(1);
	}

	if (state == high) {	
		gpio->gpio_reg |= (1 << pin);
		printf("Register set successfully\n");
	}
	else if (state == low){
		gpio->gpio_reg &= ~(1 << pin);
		printf("Register cleared successfully\n");
	}
    else
        exit(1);
}

void toggle_gpio (GPIO *gpio, int pin) {
	if (gpio == NULL) { 
		printf("GPIO pointer is null in toggle_gpio\n");
		exit(1);
	}
	gpio->gpio_reg ^= (1 << pin);
	printf("Register toggle successfully\n");
}

void print_reg (GPIO* gpio) {
	if (gpio == NULL) {
		printf("GPIO pointer is null in read_gpio\n");
		exit(1);
	}
	printf("Register state: %08b\n", gpio->gpio_reg);	
}

void print_gpio_state (GPIO* gpio, int pin) {
	if (gpio == NULL) {
		printf("GPIO pointer is null in gpio_state\n");
		exit(1);
	}
	if ((gpio->gpio_reg & (1 << pin)) == 0)
		printf("The pin %d is set to LOW\n", pin);
	else 
		printf("The pin %d is set to HIGH\n", pin);

}

