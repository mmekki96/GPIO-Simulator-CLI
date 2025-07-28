#include "gpio.h"
#include <stdio.h>
#include <string.h>
#include "cli.h"

int main() {
	GPIO* gpio;
	PinState pin_state;
	GPIO_Mode pin_mode;
	char input[255];
	char* command;
	char** tokens;
	int pin;
	gpio_create(&GPIOx[GPIOA]);
	gpio_create(&GPIOx[GPIOB]);
	gpio_create(&GPIOx[GPIOC]);
	gpio_create(&GPIOx[GPIOD]);

    	printf("Commands Format:\nTo write pin: set <GPIOx> <num_pin> <state>\n");
	printf("To toggle pin: toggle <GPIOx> <num_pin>\n");
	printf("To change the mode of a pin: mode <GPIOx> <num_pin> <mode>\n");
	printf("To print the state of register: regst <GPIOx>\n");
	printf("To print the state of a single pin: pinst <GPIOx> <num_pin>\n");
	printf("To print the register mode: regmode <GPIOx> \n");
	printf("To print a target pin mode: pinmode <GPIOx> <num_pin> \n");
	
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
			       	printf("regst <GPIOx>\n");
				printf("pinst <GPIOx> <num_pin>\n");
				printf("regmode <GPIOx>\n");
				printf("pinmode <GPIOx> <num_pin>\n");	
			}
			else if (strcmp(command, "exit") == 0) {
				printf("GoodBye!\n");
				return 0;
			}
			continue;
		}

		if (strcmp(command, "mode") == 0) {
			if (num_tokens == 4) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D)\n");
					continue;
				}
				pin = atoi(tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Choose number pin between 0-7\n");
					continue;
				}
				if (strcmp(tokens[3], "out") == 0)
					pin_mode = gpio_out;
				else if (strcmp(tokens[3], "in") == 0)
					pin_mode = gpio_in;
				else {
					printf("Wrong pin mode, in or out\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type -h\n");
				continue;
			}
			gpio_mode (gpio, pin, pin_mode);
		}
		
		if (strcmp(command, "set") == 0) {
			if (num_tokens == 4) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D)\n");
					continue;
				}
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
				printf("Invalid command, type help\n");
				continue;
			}
			set_gpio (gpio, pin, pin_state);	
		}

		else if (strcmp(command, "toggle") == 0) {
			if (num_tokens == 3) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D)\n");
					continue;
				}
				pin = atoi(tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Choose pin : 0-7\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type help\n");
				continue;
			}
				toggle_gpio (gpio, pin);		
		}
		
		else if (strcmp(command, "regst") == 0) {
			if (num_tokens == 2) {
				gpio = get_GPIO (tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D)\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type help\n");
				continue;
			}
			print_gpio_reg (gpio);
		}
		
		else if (strcmp(command, "pinst") == 0) {
			if (num_tokens == 3) {
				gpio = get_GPIO (tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D)\n");
					continue;
				}
				pin = atoi (tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Choose pin: 0-7\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type help\n");
				continue;
			}
			print_pin_state (gpio, pin);
		}
		else if (strcmp(command, "regmode") == 0) {
			if (num_tokens == 2) {
				gpio = get_GPIO(tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type -h\n");
				continue;
			}
			print_mode_reg (gpio);
		}
		else if (strcmp(command, "pinmode") == 0) {
			if (num_tokens == 3) {
				gpio = get_GPIO (tokens[1]);
				if (gpio == NULL) {
					printf("Select proper GPIOx (A, B, C or D\n");
					continue;
				}
				pin = atoi(tokens[2]);
				if (pin < 0 || pin > 7) {
					printf("Pin should be between 0-7\n");
					continue;
				}
			}
			else {
				printf("Invalid command, type -h\n");
				continue;
			}
			print_pin_mode (gpio, pin);
		}
		free_tokens (tokens);
	}


	return 0;
}

