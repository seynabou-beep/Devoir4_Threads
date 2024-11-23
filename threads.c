#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


 int compteur = 0;
int n;
int m;
sem_t sem1, sem2;

// fonction executee parthread 1
void* increment(void* arg) {
    FILE* fic = (FILE*)arg;
    for (int cycle = 0; cycle < m; cycle++) {
        sem_wait(&sem1);
        // Compte de 1 a n
        for(int i = 1; i <= n; i++) {
            compteur = i;
            fprintf(fic, "%d\n", compteur);
            printf("Thread 1: %d\n", compteur);
            fflush(fic);
            fflush(stdout);
        }
        sem_post(&sem2);
    }
    pthread_exit(NULL);
}

// Foction exeutee par le thread 2
void* decrement(void* arg) {
    FILE* fic = (FILE*)arg;
    for (int cycle = 0; cycle < m; cycle++) {
        sem_wait(&sem2);
        // Compte de -1 a -n
        for(int i = 1; i <= n; i++) {
            compteur = -i;
            fprintf(fic, "%d\n", compteur);
            printf("Thread 2: %d\n", compteur);
            fflush(fic);
            fflush(stdout);
        }
        sem_post(&sem1);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("nombre dargument insuffisant");
        return EXIT_FAILURE;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);

    if (n <= 0 || m <= 0) {
        fprintf(stderr, "Les valrs de n et m doivent etre des entiers positifs.\n");
        return EXIT_FAILURE;
    }


    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

    // Creation du fichier
    FILE* fic = fopen("resultat.txt", "w");
    if (fic == NULL) {
        perror("Erreur d'ouverture du fichier");
        return EXIT_FAILURE;
    }


    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, fic);
    pthread_create(&t2, NULL, decrement, fic);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    fclose(fic);
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    printf("Les resultats ont ete enregistres dans 'resultat.txt'\n");
    return EXIT_SUCCESS;
}


