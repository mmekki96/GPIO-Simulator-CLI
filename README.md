# ⚡ GPIO Simulator CLI

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-555?style=flat)

A command-line tool written in pure C that simulates the GPIO register behavior of a microcontroller. Control pin states, set directions, toggle outputs, and inspect data and mode registers — all from your terminal.

### Prerequisites
* **Compiler:** `gcc`
* **Build Tool:** `make`
* **Environment:** Linux

## Features

### General commands
- `help` — list all available commands
- `exit` — quit the simulator

### Pin state control
- `set <port> <pin> high` — drive a pin HIGH
- `set <port> <pin> low` — drive a pin LOW
- `toggle <port> <pin>` — toggle a pin between HIGH and LOW

### Pin direction control
- `mode <port> <pin> in` — set pin as input
- `mode <port> <pin> out` — set pin as output

### Register inspection
- `regst <port>` — display the simulated data register (current pin states)
- `regmode <port>` — display the simulated mode register (input/output directions)
- `pinst <port> <pin>` — display the current state of a specific pin

> Supported ports: `gpioa`, `gpiob`, `gpioc`, `gpiod` — 8 pins each (0-7).

---

## Build & run

The project uses a modular `src/include` structure. Use the provided shell script to automate the creation of the `build/` directory and run the simulator:

```bash
git clone https://github.com/mmekki96/GPIO-Simulator-CLI.git
cd GPIO-Simulator-CLI
chmod +x start.sh
./start.sh
```

---


## Usage examples

```bash
set gpioa 4 high
mode gpioc 3 out
toggle gpiob 1
pinst gpiod 7
regst gpioa
```

---

Part of my embedded systems portfolio — [github.com/mmekki96](https://github.com/mmekki96)
