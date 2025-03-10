CC=gcc
AS=as
GCCPARAMS = -m32 -nostdlib -fno-builtin -fno-exceptions -ffreestanding -fno-leading-underscore -Wall -Wextra -Wpedantic
ASPARAMS = --32
LDPARAMS = -melf_i386

SRC_DIR=src
HDR_DIR=include/
OBJ_DIR=obj
ISO_DIR=iso

SRC_FILES1=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES1=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES1))
SRC_FILES2=$(wildcard $(SRC_DIR)/*.s)
OBJ_FILES2=$(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRC_FILES2))
SRC_FILES3=$(wildcard $(SRC_DIR)/*.asm)
OBJ_FILES3=$(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(SRC_FILES3))

# Regra principal (compila tudo)
all: check_dir primus-os.bin

# Criar diretório de objetos se não existir
check_dir:
	@if not exist "$(OBJ_DIR)" mkdir $(OBJ_DIR)

# Compilação dos arquivos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(GCCPARAMS) -I$(HDR_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASPARAMS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	nasm -f elf32 -o $@ $<

# Linkando os objetos
primus-os.bin: $(SRC_DIR)/linker.ld $(OBJ_FILES1) $(OBJ_FILES2) $(OBJ_FILES3)
	ld $(LDPARAMS) -T $< -o $@ $(OBJ_DIR)/*.o

# Criar a ISO
bl00xkiddOS.iso: primus-os.bin
	./update_version
	@if not exist "$(ISO_DIR)/boot/grub" mkdir $(ISO_DIR)/boot/grub
	copy primus-os.bin $(ISO_DIR)/boot/bl00xkiddOS.bin
	echo set timeout=0                      > $(ISO_DIR)/boot/grub/grub.cfg
	echo set default=0                     >> $(ISO_DIR)/boot/grub/grub.cfg
	echo.                                 >> $(ISO_DIR)/boot/grub/grub.cfg
	echo menuentry "bl00xkiddOS" {         >> $(ISO_DIR)/boot/grub/grub.cfg
	echo   multiboot /boot/bl00xkiddOS.bin >> $(ISO_DIR)/boot/grub/grub.cfg
	echo   boot                           >> $(ISO_DIR)/boot/grub/grub.cfg
	echo }                                >> $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue --output=bl00xkiddOS.iso $(ISO_DIR)
	rmdir /s /q $(ISO_DIR)

# Instalar no /boot (caso rode em Linux)
install: primus-os.bin
	copy $< C:\boot\primus-os.bin

# Limpeza
clean:
	del /s /q $(OBJ_DIR)\*.o *.bin *.iso *.bak bl00xkiddOS 2> nul
	rmdir /s /q $(OBJ_DIR) $(ISO_DIR) 2> nul