#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

// Define the GPIO pin number for monitoring
#define GPIO_PIN 18

// Define the path to the GPIO value file for the specified pin
#define GPIO_PATH "/sys/class/gpio/gpio18/value"

// Define the interval (in milliseconds) to check the GPIO status
#define INTERVAL 250  // Check interval in milliseconds

// Function to shut down the Android device by executing a system command
void shutdown_android_device() {
    system("reboot -p");  // "-p" option for power-off
}

int main() {
    // Export the GPIO pin for use (makes it available in the system directory)
    int export_fd = open("/sys/class/gpio/export", O_WRONLY);
    if (export_fd < 0) {
        perror("Error exporting GPIO");
        return EXIT_FAILURE;
    }

    // Write the GPIO pin number to the export file as a string
    char gpio_pin_str[4];
    snprintf(gpio_pin_str, sizeof(gpio_pin_str), "%d", GPIO_PIN);
    write(export_fd, gpio_pin_str, sizeof(gpio_pin_str));
    close(export_fd);

    // Set GPIO direction to "input" (we want to read the pin state)
    char direction_path[50];
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%d/direction", GPIO_PIN);
    int direction_fd = open(direction_path, O_WRONLY);
    if (direction_fd < 0) {
        perror("Error setting direction");
        return EXIT_FAILURE;
    }

    write(direction_fd, "in", 2);  // Set GPIO direction to input
    close(direction_fd);

    // Enter an infinite loop to continually monitor the GPIO pin value
    while (1) {
        // Open the GPIO value file for reading the current pin state
        char gpio_value;
        int value_fd = open(GPIO_PATH, O_RDONLY);
        if (value_fd < 0) {
            perror("Error reading GPIO value");
            return EXIT_FAILURE;
        }

        // Read the GPIO value (one byte: '0' or '1')
        read(value_fd, &gpio_value, 1);
        close(value_fd);

        // Check if the GPIO value is '0' (button pressed or signal detected)
        if (gpio_value == '0') {
            shutdown_android_device();  // Trigger device shutdown
            break;  // Exit the loop after shutdown
        } else {
            // Wait for the specified interval before rechecking
            usleep(INTERVAL * 1000);  // Convert interval to microseconds
        }
    }

    return EXIT_SUCCESS;  // Program completes successfully
}
