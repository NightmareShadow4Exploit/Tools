#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void change_interface_mode(const char *interface, const char *new_mode) {
    char command[100];

    // Bring the interface down
    sprintf(command, "ifconfig %s down", interface);
    system(command);

    // Kill processes that might interfere with the interface
    system("airmon-ng kill");

    // Change the mode of the interface
    sprintf(command, "iwconfig %s mode %s", interface, new_mode);
    system(command);

    // Bring the interface back up
    sprintf(command, "ifconfig %s up", interface);
    system(command);

    printf("Mode of interface %s changed to %s.\n", interface, new_mode);
}

int main(int argc, char *argv[]) {
    // Check if arguments are provided correctly
    if (argc != 3) {
        printf("Usage: %s <interface> <new_mode>\n", argv[0]);
        return 1;
    }

    // Call the function to change the mode
    change_interface_mode(argv[1], argv[2]);

    return 0;
}
