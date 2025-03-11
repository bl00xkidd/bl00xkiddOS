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
    
def instalar_pacotes(sistema):
    print_colorido("\nInstalando dependências...", "AZUL")
    if sistema == "linux":
        subprocess.run(["apt-get", "update"], check=True)
        subprocess.run(["apt-get", "install", "-y", "locales", "sudo", "grub-pc", "syslinux", "efibootmgr"], check=True)
    elif sistema == "macos":
        subprocess.run(["brew", "update"], check=True)
        subprocess.run(["brew", "install", "grub", "syslinux"], check=True)
    elif sistema == "windows":
        # Instala dependências no Windows (exemplo: Chocolatey)
        subprocess.run(["powershell", "Set-ExecutionPolicy", "Bypass", "-Scope", "Process", "-Force"], check=True)
        subprocess.run(["powershell", "Install-PackageProvider", "-Name", "NuGet", "-MinimumVersion", "2.8.5.201", "-Force"], check=True)
        subprocess.run(["powershell", "Install-Module", "-Name", "PSWindowsUpdate", "-Force"], check=True)
        print_colorido("Dependências do Windows instaladas.", "VERDE")

def configurar_localizacao(idioma, sistema):
    print_colorido("\nConfigurando localização...", "AZUL")
    locale = "pt_BR.UTF-8" if idioma == "pt" else "en_US.UTF-8"
    if sistema == "linux":
        with open("/etc/locale.gen", "a") as f:
            f.write(f"{locale} UTF-8\n")
        subprocess.run(["locale-gen"], check=True)
        with open("/etc/default/locale", "w") as f:
            f.write(f"LANG={locale}\n")
    elif sistema == "macos":
        subprocess.run(["sudo", "defaults", "write", ".GlobalPreferences", "AppleLocale", locale], check=True)
    elif sistema == "windows":
        subprocess.run(["powershell", "Set-WinSystemLocale", locale], check=True)

def criar_usuario(usuario, sistema):
    print_colorido(f"\nCriando usuário {usuario}...", "AZUL")
    if sistema == "linux" or sistema == "macos":
        subprocess.run(["sudo", "useradd", "-m", "-G", "sudo", usuario], check=True)
        subprocess.run(["sudo", "passwd", usuario], input=f"{usuario}\n{usuario}\n".encode(), check=True)
    elif sistema == "windows":
        subprocess.run(["net", "user", usuario, usuario, "/add"], check=True)
        subprocess.run(["net", "localgroup", "Administrators", usuario, "/add"], check=True)

def configurar_hostname(hostname, sistema):
    print_colorido(f"\nDefinindo hostname: {hostname}", "AZUL")
    if sistema == "linux" or sistema == "macos":
        with open("/etc/hostname", "w") as f:
            f.write(f"{hostname}\n")
        subprocess.run(["hostnamectl", "set-hostname", hostname], check=True)
    elif sistema == "windows":
        subprocess.run(["powershell", "Rename-Computer", "-NewName", hostname], check=True)

def configurar_grub(disco, fastboot, sistema):
    print_colorido("\nConfigurando GRUB...", "AZUL")
    if sistema == "linux":
        cmdline = "quiet splash" if not fastboot else "quiet splash fastboot"
        with open("/etc/default/grub", "r") as f:
            conteudo = f.read()
        conteudo = conteudo.replace('GRUB_CMDLINE_LINUX_DEFAULT=""', 
                                   f'GRUB_CMDLINE_LINUX_DEFAULT="{cmdline}"')
        with open("/etc/default/grub", "w") as f:
            f.write(conteudo)
        subprocess.run(["grub-install", disco], check=True)
        subprocess.run(["update-grub"], check=True)
    else:
        print_colorido("GRUB não suportado neste sistema.", "VERMELHO")

def configurar_syslinux(disco, fastboot, sistema):
    print_colorido("\nConfigurando Syslinux...", "AZUL")
    if sistema == "linux":
        subprocess.run(["syslinux-install_update", "-iam"], check=True)
        config = f"""DEFAULT linux
LABEL linux
KERNEL /vmlinuz
APPEND root={disco}1 ro {'fastboot' if fastboot else ''}
"""
        with open("/boot/syslinux/syslinux.cfg", "w") as f:
            f.write(config)
    else:
        print_colorido("Syslinux não suportado neste sistema.", "VERMELHO")

def configurar_boot_windows(disco):
    print_colorido("\nConfigurando boot no Windows...", "AZUL")
    try:
        # Define o caminho relativo para o bootloader
        caminho_script = os.path.dirname(os.path.abspath(__file__))  # Diretório do script
        caminho_bootloader = os.path.join(caminho_script, "..", "helloworld", "bootloader.bin")  # Caminho relativo
        caminho_bootloader = os.path.normpath(caminho_bootloader)  # Normaliza o caminho

        # Adiciona uma nova entrada de boot para o seu sistema operacional
        resultado = subprocess.run(["bcdedit", "/create", "/d", "bl00xkiddOS", "/application", "bootsector"], capture_output=True, text=True, check=True)
        novo_guid = resultado.stdout.split("{")[1].split("}")[0]  # Extrai o GUID da nova entrada
        subprocess.run(["bcdedit", "/set", "{" + novo_guid + "}", "device", "partition=" + disco], check=True)
        subprocess.run(["bcdedit", "/set", "{" + novo_guid + "}", "path", caminho_bootloader], check=True)
        subprocess.run(["bcdedit", "/displayorder", "{" + novo_guid + "}", "/addlast"], check=True)
        subprocess.run(["bcdedit", "/timeout", "5"], check=True)  # Define timeout de 5 segundos
        print_colorido("Boot do Windows configurado com sucesso!", "VERDE")
    except subprocess.CalledProcessError as e:
        print_colorido(f"Erro ao configurar o boot no Windows: {e}", "VERMELHO")

def configurar_debug(sistema):
    print_colorido("\nAtivando debug...", "AZUL")
    if sistema == "linux":
        Path("/etc/systemd/system/emergency.service").symlink_to("/usr/lib/systemd/system/rescue.service")
        subprocess.run(["systemctl", "enable", "debug-shell.service"])
    elif sistema == "macos":
        subprocess.run(["sudo", "launchctl", "load", "-w", "/System/Library/LaunchDaemons/com.apple.debugserver.plist"], check=True)
    elif sistema == "windows":
        subprocess.run(["sc", "config", "debugsvc", "start=auto"], check=True)

def main(config, sistema):
    try:
        barra_progresso("Iniciando instalação", 0)
        
        instalar_pacotes(sistema)
        barra_progresso("Pacotes instalados", 25)
        
        configurar_localizacao(config["idioma"], sistema)
        barra_progresso("Localização configurada", 35)
        
        criar_usuario(config["usuario"], sistema)
        barra_progresso("Usuário criado", 50)
        
        configurar_hostname(config["hostname"], sistema)
        barra_progresso("Hostname definido", 60)
        
        if sistema == "windows":
            configurar_boot_windows(config["disco"])
        elif config["bootloader"] == "grub":
            configurar_grub(config["disco"], config["fastboot"], sistema)
        else:
            configurar_syslinux(config["disco"], config["fastboot"], sistema)
        barra_progresso("Bootloader configurado", 80)
        
        if config["debug"]:
            configurar_debug(sistema)
        barra_progresso("Debug configurado", 90)
        
        time.sleep(1)
        barra_progresso("Instalação completa!", 100)
        print_colorido("\nInstalação concluída com sucesso!", "VERDE")

    except subprocess.CalledProcessError as e:
        print_colorido(f"\nErro durante a instalação: {e}", "VERMELHO")
        sys.exit(1)

def barra_progresso(mensagem, percentual):
    blocos = int(percentual / 2)
    print_colorido(f"\r[{mensagem}] [{'█' * blocos}{'-' * (50 - blocos)}] {percentual}%", "AZUL", end="")
    sys.stdout.flush()
    
def modify_kernel_config(config):
    kernel_file = "../helloworld/kernel.asm"
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
        detectar_sistema()
        definir_cor(cor):
        print_colorido(texto, cor)
        barra_progresso(mensagem, percentual)
        configurar_syslinux(disco, fastboot, sistema)
        configurar_boot_windows(disco, fastboot, sistema)
        configurar_grub(disco)
        configurar_usuario()
        configurar_localizacao(idioma, sistema)
        configurar_hostname(hostname, sistema)
        configurar_debug(sistema)
        instalar_pacotes(sistema)
        main(config, sistema)
        
        print_colorido("Instalação concluída com sucesso!", "VERDE")
    else:
        print_colorido("Instalação cancelada.", "VERMELHO")

if __name__ == "__main__":
    main()
