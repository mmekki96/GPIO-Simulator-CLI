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

void gpio_mode (GPIO* gpio, int pin, GPIO_Mode mode) {
	if (gpio == NULL) {
		printf("GPIO pointer is null at gpio_mode\n");
		exit(1);
	}
	gpio->gpio_mode &= ~(1 << pin); //Reset mode pin
	gpio->gpio_mode |= (mode << pin); // Set pin: 0 output and 1 input 
	if (mode == gpio_in)
		printf("The pin is set to Input\n");
	else if (mode == gpio_out)
		printf("The pin is set to Output\n");
	else
		printf("Wrong command\n");
}

void set_gpio (GPIO *gpio, int pin, PinState state) {
	if (gpio == NULL) {
		printf("GPIO pointer is null in set_gpio\n");
		exit(1);
	}

	if ((gpio->gpio_mode & (1 << pin)) == gpio_out) { 
		if (state == high) {	
			gpio->gpio_reg |= (1 << pin);
			printf("Register set successfully\n");
		}
		else if (state == low) {
			gpio->gpio_reg &= ~(1 << pin);
			printf("Register cleared successfully\n");
		}
	}
	else {
		printf("The pin is at Input mode\n");
	}
}

void toggle_gpio (GPIO *gpio, int pin) {
	if (gpio == NULL) { 
		printf("GPIO pointer is null in toggle_gpio\n");
		exit(1);
	}
	gpio->gpio_reg ^= (1 << pin);
	printf("Register toggle successfully\n");
}

void print_gpio_reg (GPIO* gpio) {
	if (gpio == NULL) {
		printf("GPIO pointer is null\n");
		exit(1);
	}
	for (int i=7; i>=0; i--) {
		printf("%d", (gpio->gpio_reg >> i) & 1);
	}
	printf("\n");
}

void print_pin_state (GPIO* gpio, int pin) {
	if (gpio == NULL) {
		printf("GPIO pointer is null in gpio_state\n");
		exit(1);
	}
	if ((gpio->gpio_reg & (1 << pin)) == 0)
		printf("The pin %d is set to LOW\n", pin);
	else 
		printf("The pin %d is set to HIGH\n", pin);

}

void print_mode_reg (GPIO* gpio) {
        if (gpio == NULL) {
                printf("GPIO pointer is null\n");
                exit(1);
        }
        for (int i=7; i>=0; i--) {
                printf("%d", (gpio->gpio_mode >> i) & 1);
        }
        printf("\n");
}

void print_pin_mode (GPIO* gpio, int pin) {
        if (gpio == NULL) {
                printf("GPIO pointer is null in gpio_state\n");
                exit(1);
        }
        if ((gpio->gpio_mode & (1 << pin)) == 0)
                printf("The pin %d is set to Output\n", pin);
        else
                printf("The pin %d is set to Input\n", pin);

}


