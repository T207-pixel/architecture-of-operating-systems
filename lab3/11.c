#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// Глобальная переменная для демонстрации синхронизации
sig_atomic_t signal_received = 0;

// Обработчик сигнала
void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        signal_received = 1;
    }
}

int main() {
    pid_t pid;
    struct sigaction sa;
    sigset_t mask, oldmask, suspendmask;

    // Настройка обработчика сигнала SIGUSR1
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL); 

    // Создание новой маски сигналов, блокирующей SIGUSR1
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    // Блокировка сигнала SIGUSR1
    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    // Создание дочернего процесса
    pid = fork();

    if (pid == 0) { // Дочерний процесс
        printf("Child: PID = %d\n", getpid());

        // Ожидание получения сигнала SIGUSR1
        printf("Child: Waiting for signal...\n");

        // Установка маски для sigsuspend (разрешаем SIGUSR1)
        suspendmask = oldmask;
        sigdelset(&suspendmask, SIGUSR1);

        // Приостановка процесса до получения сигнала, разрешенного в suspendmask
        while (signal_received == 0) {
            sigsuspend(&suspendmask);
        }

        printf("Child: Signal received!\n");

        // Восстановление исходной маски сигналов
        sigprocmask(SIG_SETMASK, &oldmask, NULL);
        
        printf("Child: Exiting.\n");
        exit(0);

    } else { // Родительский процесс
        printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);

        // Небольшая задержка, чтобы дочерний процесс успел запустить sigsuspend
        sleep(1);
        printf("Parent: Sending signal to child...\n");

        // Отправка сигнала SIGUSR1 дочернему процессу
        kill(pid, SIGUSR1);

        // Ожидание завершения дочернего процесса
        wait(NULL);

        // Восстановление исходной маски сигналов
        sigprocmask(SIG_SETMASK, &oldmask, NULL);
        printf("Parent: Exiting.\n");
    }

}