# Raspberry Pi 4 GPIO Shutdown Script

This C program monitors a GPIO pin on a Raspberry Pi 4. When the specified GPIO pin detects a low signal (e.g., when a button connected to the GPIO pin is pressed or in my case when a cars ignintion gets turned to off), the program initiates a safe shutdown of the Raspberry Pi. This is useful for creating a physical shutdown button to turn off the device without needing to access the terminal.

## Prerequisites

This script requires:
- A Raspberry Pi 4 running a Unix-based OS (e.g., Raspberry Pi OS, Android)
- Access to the `/sys/class/gpio` interface to control GPIO pins
- A push button connected between the GPIO pin and ground or some other way of turning power off to a GPIO pin

## How It Works

1. The script first exports the desired GPIO pin for use, making it accessible in the system directory.
2. It sets the GPIO pin as an input pin to read its state.
3. The program then enters a continuous loop, reading the GPIO value at a specified interval (250 milliseconds by default).
4. When the button is pressed or power is lost on that pin (the GPIO pin reads a low signal), the script runs a shutdown command to safely power on and off the Raspberry Pi.

## GPIO Pin

This program is set to monitor **GPIO pin 18** by default. To use a different GPIO pin, change the `GPIO_PIN` macro definition in the code.
