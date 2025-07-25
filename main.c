#include "gpio.h"
#include <stdio.h>
#include <string.h>
#include "cli.h"

int main() {
	GPIO* gpio;
	PinState pin_state;
	char input[255];
	char* command;
	char** tokens;
	int pin;
	gpio_create(&GPIOx[GPIOA]);
	gpio_create(&GPIOx[GPIOB]);
	gpio_create(&GPIOx[GPIOC]);
	gpio_create(&GPIOx[GPIOD]);

    	printf("Commands Format:\nTo write pin: set GPIOx <num_pin> <state>\n");
	printf("To toggle pin: toggle GPIOx <num_pin>\n");
	printf("To print the state of register: preg GPIOx\n");
	printf("To print the state of a single pin: ppin GPIOx <num_pin>\n");
	
	while(1) {
		int num_tokens = 0;
		printf(">> ");
		fgets(input, 255, stdin);
		tokens = CLI(input);
		if (tokens == NULL) {
			continue;
		}
		command = tokens[0];
		num_tokens = getCliArg(tokens);	
		if (num_tokens == 1) {
			if (strcmp(command, "help") == 0) {
				printf("set <GPIOx> <num_pin> <pin_state>\n");
				printf("toggle <GPIOx> <num_pin>\n");
			       	printf("preg <GPIOx>\n");
				printf("ppin <GPIOx> <num_pin>\n");	
			}
			else if (strcmp(command, "exit") == 0) {
				printf("GoodBye!\n");
				return 0;
			}
			continue;
		}
		
		if (strcmp(command, "set") == 0) {
			if (num_tokens == 4) {
				gpio = get_GPIO(tokens[1]);
				pin = atoi(tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Choose number pin between 0-7\n");
					continue;
				}
				if (strcmp(tokens[3], "high") == 0)
					pin_state = high;
				else if (strcmp(tokens[3], "low") == 0)
					pin_state = low;
				else {
					printf("Wrong pin state, high or low\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type -help\n");
				continue;
			}
			set_gpio (gpio, pin, pin_state);	
		}

		else if (strcmp(command, "toggle") == 0) {
			if (num_tokens == 3) {
				gpio = get_GPIO(tokens[1]);
				pin = atoi(tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Choose pin : 0-7\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type -help\n");
				continue;
			}
				toggle_gpio (gpio, pin);		
		}
		
		else if (strcmp(command, "preg") == 0) {
			if (num_tokens == 2) {
				gpio = get_GPIO (tokens[1]);
			}
			else {
				printf("Invalid command, type -help\n");
				continue;
			}
			print_reg (gpio);
		}
		
		else if (strcmp(command, "ppin") == 0) {
			if (num_tokens == 3) {
				gpio = get_GPIO (tokens[1]);
				pin = atoi (tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Choose pin: 0-7\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type -help\n");
				continue;
			}
			print_gpio_state (gpio, pin);
		}
		free_tokens (tokens);
	}


	return 0;
}

