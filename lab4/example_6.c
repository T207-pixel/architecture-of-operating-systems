#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>

int main() {
    const char *fifo_name = "mypipe";
    int result = mkfifo(fifo_name, 0666); // Права доступа: чтение и запись для всех
    if (result == 0) {
        printf("Именованный канал %s успешно создан.\n", fifo_name);
    } else {
        perror("Ошибка при создании именованного канала");
    }
    return 0;
}