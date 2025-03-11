%include "bootloader.asm"
%include "../assembly/serial.asm"
%include "../assembly/string.asm"
%include "../assembly/stdlib.asm"
%include "../assembly/stdio.asm"
%include "../assembly/data.asm"

[ORG 0x7C00]             ; Código carregado no endereço 0x7C00

; Configuração de variáveis modificáveis por SETUP.py
fastboot DB 0           ; 1 = Ativado, 0 = Desativado
username DB 'Usuário', 0
password DB '1234', 0   ; Senha do usuário
debug_mode DB 0         ; 0 = Desativado, 1 = Ativado
device_name DB 'MeuKernel', 0
boot_logo DB 'BIOS v1.0', 0 ; Logo de inicialização
input_buffer TIMES 16 DB 0  ; Buffer para entrada do usuário

; Inicialização
MOV AH, 0x0E            ; Serviço de exibição de caracteres
CMP BYTE [fastboot], 1  ; Verifica se fastboot está ativado
JE skip_logo            ; Pula logo se fastboot ativado
MOV SI, boot_logo       ; Exibe o logo na inicialização
CALL print_string

skip_logo:
MOV SI, msg             ; Ponteiro para a string de mensagem
CALL print_string       ; Chama a função para imprimir

CALL login              ; Chama a função de login
CALL check_debug        ; Verifica se modo debug está ativado

HLT                     ; Para a execução

; Função para imprimir strings
print_string:
    MOV AL, [SI]        ; Pega o caractere atual
    CMP AL, 0           ; Verifica se é o fim da string
    JE done             ; Se for, termina
    INT 0x10            ; Imprime o caractere
    INC SI              ; Move para o próximo caractere
    JMP print_string    ; Repete

done:
    RET                 ; Retorna da função

; Função de login
login:
    MOV SI, login_prompt
    CALL print_string
    CALL read_input      ; Lê entrada do usuário
    MOV SI, input_buffer
    CALL compare_username
    JNE login_fail
    
    MOV SI, pass_prompt
    CALL print_string
    CALL read_input
    MOV SI, input_buffer
    CALL compare_password
    JNE login_fail
    
    MOV SI, login_success
    CALL print_string
    RET

login_fail:
    MOV SI, login_error
    CALL print_string
    JMP login

; Função para verificar modo debug
check_debug:
    CMP BYTE [debug_mode], 1
    JNE debug_skip
    MOV SI, debug_msg
    CALL print_string

debug_skip:
    RET

; Função para comparar input com username
compare_username:
    MOV DI, username
    CALL compare_strings
    RET

; Função para comparar input com password
compare_password:
    MOV DI, password
    CALL compare_strings
    RET

; Função para ler input do usuário
read_input:
    MOV SI, input_buffer
    CALL stdio_read_line
    RET

username_msg DB 'Bem-vindo, ', 0
msg DB 'Kernel Iniciado!', 0
debug_msg DB 'Modo Debug Ativado!', 0
login_prompt DB 'Digite o usuário: ', 0
pass_prompt DB 'Digite a senha: ', 0
login_success DB 'Login bem-sucedido!', 0
login_error DB 'Usuário ou senha incorretos!', 0

TIMES 510-($-$$) DB 0   ; Preenche até 510 bytes
DW 0xAA55               ; Assinatura do bootloader
