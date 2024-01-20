#!/usr/bin/env python
import subprocess
import random
import argparse
import re  # Import the regular expression module for MAC address validation

def generate_random_mac():
    return ':'.join(f"{random.randint(10, 99):02x}" for _ in range(6))

def is_valid_mac(mac):
    # Use a regular expression to check if the MAC address is in a valid format
    mac_pattern = re.compile(r'^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$')
    return bool(mac_pattern.match(mac))

def change_mac(interface, new_mac):
    print(f"[+] Changing MAC address of {interface} to {new_mac}")
    subprocess.call(f"ifconfig {interface} down; ifconfig {interface} hw ether {new_mac}; ifconfig {interface} up", shell=True)

def main():
    parser = argparse.ArgumentParser(description="Change MAC address of a network interface.")
    parser.add_argument("-i", "--interface", help="Specify the network interface (e.g., wlan0, eth0)", required=True)
    parser.add_argument("-m", "--mac", help="Specify the new MAC address")
    parser.add_argument("-r", "--random", help="Use a random MAC address", action="store_true")

    args = parser.parse_args()

    interface = args.interface

    if args.random:
        new_mac = generate_random_mac()
    elif args.mac:
        new_mac = args.mac
        if not is_valid_mac(new_mac):
            print(f"Error: Invalid MAC address format: {new_mac}")
            return
    else:
        new_mac = input("Enter the new MAC address: ")

    change_mac(interface, new_mac)

if __name__ == "__main__":
    main()
