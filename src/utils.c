#include "../include/utils.h"
#include "../include/tty.h"
#include "../include/timer.h"
#include "../include/stdlib.h"

void show_random_binary() {
    for (int i = 0; i < 100; i++) // Mostra 100 linhas de números aleatórios
    {
        for (int j = 0; j < 80; j++) // Cada linha tem 80 caracteres
        {
            printk("%d", rand() % 2); // Gera aleatoriamente 0 ou 1
        }
        printk("\n");
    }
}

void print_logo() {
    printk("\t                                                                                    \n");
    printk("\t ___.   .__  _______  _______          __   .__    .___  .___________    _________  \n");
    printk("\t \_ |__ |  | \   _  \ \   _  \ ___  __|  | _|__| __| _/__| _/\_____  \  /   _____/  \n");
    printk("\t | __ \|  | /  /_\\  \/  /_\\  \\  \/  /  |/ /  |/ __ |/ __ |  /   |   \ \_____  \    \n");
    printk("\t | \_\ \  |_\  \_/   \  \_/   \>    <|    <|  / /_/ / /_/ | /    |    \/        \   \n");
    printk("\t |___  /____/\_____  /\_____  /__/\_ \__|_ \__\____ \____ | \_______  /_______  /   \n");
    printk("\t     \/            \/       \/      \/    \/       \/    \/         \/        \/    \n");
    printk("\t                                                                                    \n");
}

void boot_sequence() {
    show_random_binary();
    sleep(10); // Espera 10 segundos
    print_logo();
}

void about(const char *version) {
    printk("\n\tbl00xkiddOS - An bl00xkidd Team OS for roblox games hacking", version);
    printk("\n\tJoin Team bl00xkidd!: https://discord.gg/bjjQEx9uBr\n");
};

#endif  // _INCLUDE_INCLUDE_UTILS_H_INCLUD_H_
