#!/usr/bin/env python3
import os
import sys
import time
import subprocess
from pathlib import Path

def definir_cor(cor):
    sistema = detectar_sistema()
    if sistema == "windows":
        if cor == "AZUL":
            os.system("color 1")
        elif cor == "VERDE":
            os.system("color 2")
        elif cor == "VERMELHO":
            os.system("color 4")
    else:
        cores = {"AZUL": "\033[34m", "VERDE": "\033[32m", "VERMELHO": "\033[31m"}
        print(cores.get(cor, ""), end="")

def print_colorido(texto, cor):
    definir_cor(cor)
    print(texto)

def detectar_sistema():
    if sys.platform == "win32":
        return "windows"
    elif sys.platform == "darwin":
        return "macos"
    else:
        return "linux"

def configurar_usuario():
    print_colorido("\n=== bl00xkiddOS SETUP ===", "AZUL")
    return {
        "usuario": input("Nome do usuário principal: ").strip(),
        "senha": input("Senha do usuário: ").strip(),
        "idioma": input("Idioma (pt/en): ").strip().lower()[:2],
        "fastboot": input("Ativar Fastboot? (s/n): ").lower() == "s",
        "bootloader": input("Bootloader (syslinux/grub): ").strip().lower(),
        "debug": input("Ativar modo debug? (s/n): ").lower() == "s",
        "hostname": input("Hostname da máquina: ").strip(),
        "disco": input("Disco de instalação (ex: /dev/sda ou C:): ").strip(),
        "boot_logo": input("Texto para o logo de boot: ").strip()
    }

def modify_kernel_config(config):
    kernel_file = "kernel.asm"
    with open(kernel_file, "r") as f:
        lines = f.readlines()
    new_lines = []
    for line in lines:
        if line.startswith("username DB"):
            new_lines.append(f"username DB '{config['usuario']}', 0\n")
        elif line.startswith("password DB"):
            new_lines.append(f"password DB '{config['senha']}', 0\n")
        elif line.startswith("fastboot DB"):
            new_lines.append(f"fastboot DB {int(config['fastboot'])}   ; 1 = Ativado, 0 = Desativado\n")
        elif line.startswith("debug_mode DB"):
            new_lines.append(f"debug_mode DB {int(config['debug'])}   ; 0 = Desativado, 1 = Ativado\n")
        elif line.startswith("device_name DB"):
            new_lines.append(f"device_name DB '{config['hostname']}', 0\n")
        elif line.startswith("boot_logo DB"):
            new_lines.append(f"boot_logo DB '{config['boot_logo']}', 0\n")
        else:
            new_lines.append(line)
    with open(kernel_file, "w") as f:
        f.writelines(new_lines)
    print("Configurações do kernel modificadas com sucesso!")

def main():
    sistema = detectar_sistema()
    print_colorido(f"Detectado sistema: {sistema.capitalize()}", "AZUL")
    config = configurar_usuario()
    print("\nConfiguração selecionada:")
    for k, v in config.items():
        print(f"{k.capitalize()}: {v}")
    confirmar = input("\nConfirmar instalação? (s/n): ").lower()
    if confirmar == "s":
        modify_kernel_config(config)
        print_colorido("Instalação concluída com sucesso!", "VERDE")
    else:
        print_colorido("Instalação cancelada.", "VERMELHO")

if __name__ == "__main__":
    main()
