#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define GPIO_PIN 18
#define GPIO_PATH "/sys/class/gpio/gpio18/value"
#define INTERVAL 250  // Check interval in milliseconds

void shutdown_android_device() {
    system("reboot -p");
}

int main() {
    // Export the GPIO pin
    int export_fd = open("/sys/class/gpio/export", O_WRONLY);
    if (export_fd < 0) {
        perror("Error exporting GPIO");
        return EXIT_FAILURE;
    }

    char gpio_pin_str[4];
    snprintf(gpio_pin_str, sizeof(gpio_pin_str), "%d", GPIO_PIN);
    write(export_fd, gpio_pin_str, sizeof(gpio_pin_str));
    close(export_fd);

    // Set direction to input
    char direction_path[50];
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%d/direction", GPIO_PIN);
    int direction_fd = open(direction_path, O_WRONLY);
    if (direction_fd < 0) {
        perror("Error setting direction");
        return EXIT_FAILURE;
    }

    write(direction_fd, "in", 2);
    close(direction_fd);

    while (1) {
        // Read the GPIO value
        char gpio_value;
        int value_fd = open(GPIO_PATH, O_RDONLY);
        if (value_fd < 0) {
            perror("Error reading GPIO value");
            return EXIT_FAILURE;
        }

        read(value_fd, &gpio_value, 1);
        close(value_fd);

        if (gpio_value == '0') {
            shutdown_android_device();
            break;
        } else {
	    usleep(INTERVAL * 1000);  // Sleep in microseconds
        }
    }

    return EXIT_SUCCESS;
}

