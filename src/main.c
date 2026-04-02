#include "gpio.h"
#include <stdio.h>
#include <string.h>
#include "cli.h"

void display_welcome_banner() {
	printf("========================================\n");
	printf("       REGISTER SIMULATOR CLI           \n");
    printf("========================================\n");
    printf(" Welcome! Type a command to begin.\n\n");
    printf("  -help    Show the commands menu\n");
    printf("  -exit    Exit the simulator\n");
    printf("----------------------------------------\n\n");
}

void display_menu() {
	printf("\n--- REGISTER SIMULATOR COMMANDS ---\n");
    printf("\n[ Pin Manipulation ]\n");
    printf("  set <PORT> <PIN> <STATE>    Set pin state (\'low\', \'high\')\n");
    printf("  toggle <PORT> <PIN>         Invert current pin state\n");
    printf("\n[ Status & Monitoring ]\n");
    printf("  regst <PORT>                Display full register status\n");
    printf("  pinst <PORT> <PIN>          Show state of a specific pin\n");
    printf("\n[ Configuration ]\n");
    printf("  regmode <PORT>              Show port configuration mode\n");
    printf("  pinmode <PORT> <PIN>        Show mode of a specific pin\n");
    printf("\n[ System ]\n");
    printf("  -help                       Show this menu\n");
    printf("  -exit                       Close simulator\n");
    printf("-----------------------------------\n\n");
}

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

    	display_welcome_banner();

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
				display_menu();
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

