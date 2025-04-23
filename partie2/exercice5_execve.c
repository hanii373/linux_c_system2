#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = getpid();     // Obtenir le PID du processus courant
    pid_t ppid = getppid();   // Obtenir le PPID (PID du parent)
    printf("Exercice5_execve: PID=%d, PPID=%d\n", pid, ppid);

    // Préparer les arguments pour execve
    char *args[] = {"./exercice5_affiche_pids", NULL};
    char *env[] = {NULL};     // Pas de variables d'environnement spéciales

    // Exécuter le programme exercice5_affiche_pids
    execve("./exercice5_affiche_pids", args, env);

    // Si execve échoue
    perror("Erreur d'exécution avec execve");
    return 1;
}
