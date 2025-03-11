# bl00xkiddOS

bl00xkiddOS é um sistema operacional experimental desenvolvido em C e Assembly. Ele foi criado para explorar conceitos de sistemas operacionais, como gerenciamento de memória, entrada e saída, e interação com hardware de baixo nível.

## Características
- Bootloader em Assembly
- Kernel escrito em C
- Implementação de funções matemáticas e de manipulação de strings
- Módulos de criptografia (SHA-224 e SHA-256)
- Sistema básico de shell
- Manipulação de entrada e saída (I/O)

## Estrutura do Projeto
```
bl00xkiddOS/
│-- assembly/          # Código em Assembly para bootloader e funções de baixo nível
│   │-- data.asm
│   │-- mbr.asm
│   │-- serial.asm
│   │-- settings.asm
│   │-- stdio.asm
│   │-- stdlib.asm
│   │-- string.asm
│
│-- include/           # Arquivos de cabeçalho do kernel
│   │-- bool.h
│   │-- calculator.h
│   │-- crypto.h
│   │-- heap.h
│   │-- io.h
│   │-- kbd.h
│   │-- limits.h
│   │-- linked_list.h
│   │-- math.h
│   │-- math_shell.h
│   │-- memory.h
│   │-- os_defines.h
│   │-- parsing.h
│   │-- random.h
│   │-- sha224.h
│   │-- sha256.h
│   │-- shell_history.h
│   │-- sleep.h
│   │-- string.h
│   │-- thread.h
│   │-- time.h
│   │-- tty.h
│   │-- utils.h
│   │-- version.h
│
│-- src/               # Implementação do kernel e funcionalidades
│   │-- calculator.c
│   │-- crypto.c
│   │-- io.c
│   │-- kbd.c
│   │-- kernel.c
│   │-- linker.ld
│   │-- loader.s
│   │-- math.c
│   │-- math_shell.c
│   │-- memory.c
│   │-- parsing.c
│   │-- random.c
│   │-- sha224.c
│   │-- sha256.c
│   │-- shell_history.c
│   │-- string.c
│   │-- time.c
│   │-- tty.c
│   │-- utils.c
│
│-- build/             # Diretório de compilação
│   │-- SETUP/         # Arquivos gerados pelo processo de build
│       │-- Analysis-00.toc
│       │-- EXE-00.toc
│       │-- PKG-00.toc
│       │-- PYZ-00.pyz
│       │-- SETUP.pkg
│       │-- base_library.zip
│       │-- warn-SETUP.txt
│       │-- xref-SETUP.html
│
│-- helloworld/        # Teste de bootloader
│   │-- bootloader.asm
│
│-- .gitignore         # Arquivos ignorados pelo Git
│-- Makefile           # Arquivo para compilação automática
│-- SETUP.exe          # Instalador do sistema operacional
│-- SETUP.py           # Script para instalação
│-- primus-os.bin      # Arquivo binário do sistema operacional
│-- current_version.txt # Versão atual do sistema
│-- update_version.c   # Código para atualização de versão
```

## Requisitos
- Compilador GCC para cross-compilation
- NASM para montagem do bootloader
- QEMU ou Bochs para emulação

## Como Compilar e Executar
1. Instale os pacotes necessários:
   ```sh
   sudo apt update && sudo apt install build-essential nasm qemu-system-x86
   ```
2. Clone o repositório e entre na pasta do projeto:
   ```sh
   git clone https://github.com/bl00xkidd/bl00xkiddOS/tree/main
   cd bl00xkiddOS
   ```
3. Compile o sistema:
   ```sh
   make
   ```
4. Execute no QEMU:
   ```sh
   qemu-system-x86_64 -kernel primus-os.bin
   ```

## Contribuição
Se quiser contribuir, sinta-se à vontade para enviar PRs ou relatar problemas na seção de issues.

## Licença
Este projeto é distribuído sob a Licença MIT.

