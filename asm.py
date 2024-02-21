import subprocess
import argparse

def run_assembly(file_name):
    # Assemble the assembly code
    subprocess.run(['nasm', '-f', 'elf32', file_name + '.asm'])

    # Link the object file
    subprocess.run(['ld', '-m', 'elf_i386', '-o', file_name, file_name + '.o'])

    # Run the executable
    subprocess.run(['./' + file_name])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Run x86 assembly code on Kali Linux.')
    parser.add_argument('file_name', type=str, help='Name of the assembly file (without .asm extension)')
    args = parser.parse_args()

    run_assembly(args.file_name)
