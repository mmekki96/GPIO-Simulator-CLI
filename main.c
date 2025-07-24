#include "gpio.h"
#include <stdio.h>
#include <string.h>

GPIO *gpio;
PinState pin_state;

int main () {
	int num_token;
	char* tokens[5];
	char input[255];
	char* command;

	gpio_create(&GPIOx[GPIOA]);
	gpio_create(&GPIOx[GPIOB]);
	gpio_create(&GPIOx[GPIOC]);
	gpio_create(&GPIOx[GPIOD]);

    	printf("Commands Format:\nTo write pin: set GPIOx <num_pin> <state>\n");
	printf("To toggle pin: GPIOx toggle <num_pin>\n");
	printf("To print the state of register: preg GPIOx\n");
	printf("To print the state of a single pin: ppin GPIOx <num_pin>\n");
	while (1) {
		printf(">> ");
		fgets(input, 255, stdin);
		input[strcspn(input, "\n")] = '\0';
		if (strlen(input) == 0)
			continue;
		num_token = 0;
		char* token = strtok(input, " ");
		while (token != NULL) {
			tokens[num_token++] = token;
			token = strtok(NULL, " ");
		}
		if (num_token == 0)
			continue;
		command = tokens[0];
		if (strcmp(command, "set") == 0) {
			if (num_token == 4) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Invalid GPIO port name\n");
					continue;
				}
				int pin = atoi(tokens[2]);
				if (strcmp(tokens[3], "low") == 0) {
					pin_state = low;
                		}
				else if (strcmp(tokens[3], "high") == 0) {
					pin_state = high;
                		}
			set_gpio (gpio, pin, pin_state);	
			}
			else {
				printf("Invalid command, check manual\n");
				continue;	
			}	
		}
		else if (strcmp(command, "toggle") == 0) {
			if (num_token == 3) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Invalid GPIO port name\n");
					continue;
				}
				int pin = atoi(tokens[2]);
				toggle_gpio (gpio, pin);
			}
			else {
				printf("Invalid command, check manual\n");
				continue;
			}
		}
		else if (strcmp (command, "preg") == 0) {
			if (num_token == 2) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Invalid GPIO port name\n");
					continue;
				}
				print_reg (gpio);
			}
			else {
				printf("Invalid command, check manual\n");
				continue;
			}
		}
		else if (strcmp (command, "ppin") == 0) {
			if (num_token == 3) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Invalid GPIO port name\n");
					continue;
				}
				int pin = atoi(tokens[2]);
				print_gpio_state (gpio, pin);
				}
			else {
				printf("Invalid command, check the manual\n");
				continue;
			}
		}

	}
	return 0;
}
