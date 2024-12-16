#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

sig_atomic_t signal_received = 0; // Глобальная переменная для демонстрации синхронизации (при ее изменении выходим из цикла)

void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        signal_received = 1;
    }
}

int main() {
    pid_t pid;
    struct sigaction sa;
    sigset_t mask, oldmask, suspendmask;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL); 

    sigemptyset(&mask); // Создание новой маски сигналов, блокирующей SIGUSR1
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, &oldmask); // Блокировка сигнала SIGUSR1

    pid = fork();

    if (pid == 0) {
        printf("Child: PID = %d\n", getpid());

        printf("Child: Waiting for signal...\n"); // Ожидание получения сигнала SIGUSR1

        suspendmask = oldmask; // Установка маски для sigsuspend (разрешаем SIGUSR1)
        sigdelset(&suspendmask, SIGUSR1);

        while (signal_received == 0) { // Приостановка процесса до получения сигнала, разрешенного в suspendmask (то есть только SIGUSR1)
            sigsuspend(&suspendmask);
        }

        printf("Child: Signal received!\n");
        sigprocmask(SIG_SETMASK, &oldmask, NULL); // Восстановление исходной маски сигналов
        printf("Child: Exiting.\n");

    } else {
        printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);
        
        sleep(1);  // Небольшая задержка, чтобы дочерний процесс успел запустить sigsuspend
        printf("Parent: Sending signal to child...\n");
        kill(pid, SIGUSR1);  // Отправка сигнала SIGUSR1 дочернему процессу

        wait(NULL); // Ожидание завершения дочернего процесса

        // Восстановление исходной маски сигналов
        sigprocmask(SIG_SETMASK, &oldmask, NULL);
        printf("Parent: Exiting.\n");
    }

}