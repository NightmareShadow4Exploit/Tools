#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAC_LENGTH 18

void generate_random_mac(char *random_mac) {
    int i;
    for (i = 0; i < 6; i++) {
        sprintf(random_mac + 3 * i, "%02x:", rand() % 256);
    }
    random_mac[MAC_LENGTH - 1] = '\0'; // Null-terminate the string
}

int is_valid_mac(const char *mac) {
    // MAC address format validation
    int i, len = strlen(mac), count = 0;
    if (len != MAC_LENGTH - 1) return 0; // Check length

    for (i = 0; i < len; i++) {
        if (i % 3 == 2) {
            if (mac[i] != ':') return 0; // Check separator
            count++;
        } else {
            if (!isxdigit(mac[i])) return 0; // Check hex digit
        }
    }
    if (count != 5) return 0; // Check separator count
    return 1;
}

void change_mac(const char *interface, const char *new_mac) {
    char command[100];
    // Construct the command to change the MAC address
    snprintf(command, sizeof(command), "ifconfig %s down && ifconfig %s hw ether %s && ifconfig %s up", interface, interface, new_mac, interface);
    printf("[+] Changing MAC address of %s to %s\n", interface, new_mac);
    system(command); // Execute the command
}

int main(int argc, char *argv[]) {
    char interface[20], new_mac[MAC_LENGTH];
    if (argc < 2) {
        printf("Usage: %s -i <interface> [-m <new_mac> | -r]\n", argv[0]);
        return 1;
    }
    int opt;
    while ((opt = getopt(argc, argv, "i:m:r")) != -1) {
        switch (opt) {
            case 'i':
                strcpy(interface, optarg);
                break;
            case 'm':
                strcpy(new_mac, optarg);
                if (!is_valid_mac(new_mac)) {
                    printf("Error: Invalid MAC address format: %s\n", new_mac);
                    return 1;
                }
                break;
            case 'r':
                generate_random_mac(new_mac);
                break;
            default:
                printf("Usage: %s -i <interface> [-m <new_mac> | -r]\n", argv[0]);
                return 1;
        }
    }
    if (argc == 2) { // Ask for new MAC address if not provided
        printf("Enter the new MAC address: ");
        scanf("%s", new_mac);
        if (!is_valid_mac(new_mac)) {
            printf("Error: Invalid MAC address format: %s\n", new_mac);
            return 1;
        }
    }
    change_mac(interface, new_mac);
    return 0;
}
