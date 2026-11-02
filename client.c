//
// Created by osmane on 11/2/26.
//
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "segdef.h"

#define sem_number 3
#define REQ_AMOUNT 1000

int pid;
int semid, shmid;
long res;
long long sum;
//struct sembuf sop;
segment *seg;

void init() {
    pid = getpid();
    init_rand();
    shmid = shmget(cle,segsize,0);
    if (shmid == -1) {
        perror("shmget() error");
        exit(EXIT_FAILURE);
    }
    semid = semget(cle,sem_number,0);
    if (semid == -1) {
        perror("semget() error");
        exit(EXIT_FAILURE);
    }
    seg = (segment *)shmat(shmid,NULL, 0);
    if (seg == (void *)-1) {
        perror("shmat() error");
        exit(EXIT_FAILURE);
    }
}

int main() {
    //récupère les identifiant du segment,
    //des sémaphores et initialise le générateur.
    if (fork() != -1) {
    if (fork() != -1) {
    if (fork() != -1) {
    if (fork() != -1) {
    if (fork() != -1) {
        init();
        for (int req=0; req<REQ_AMOUNT; req++) {
            //demande à acquérir seg_dispo
            printf("pid %d; request %d; Accessing...\n", pid, req);
            acq_sem(semid, seg_dispo);
            printf("pid %d; request %d; Access Granted\n", pid, req);
            //initialise segment et acquiert seg_init
            seg->pid = pid;
            seg->req = req;
            sum = 0;
            for (int i = 0; i<maxval; i++) {
                long rand = getrand();
                sum += rand;
                seg->tab[i] = rand;
            }
            acq_sem(semid, seg_init);
            sum = sum / maxval;
            //attend que res_ok passe à 0
            wait_sem(semid, res_ok);
            //lit résultat et libère seg_init
            if(seg->pid != pid) {
                printf("    Wrong pid !\n"
                   "    Original : %d\n"
                   "    Answer   : %d\n"
                   "    ===============", pid, seg->pid);
            }
            if(seg->req != req) {
                printf("    Wrong request !\n"
                   "    Original : %d\n"
                   "    Answer   : %d\n"
                   "    ===============", req, seg->req);
            }
            res = seg->result;
            if (res != (long)sum) {
                printf("    Wrong result !\n"
                   "    Expected : %lx\n"
                   "    Answer   : %lx\n"
                   "    ===============", (long)sum, seg->result);
            }
            lib_sem(semid, seg_init);
            //attendre la libération de res_ok          ??
            acq_sem(semid,res_ok); lib_sem(semid, res_ok);
            //affiche résultats
            printf("pid %d; request %d; Done.\n", pid, req);
            //libère seg_dispo
            lib_sem(semid, seg_dispo);
        }//boucle sur l’étape 1
    } else { printf("Fork Error Layer 5");}
    } else { printf("Fork Error Layer 4");}
    } else { printf("Fork Error Layer 3");}
    } else { printf("Fork Error Layer 2");}
    } else { printf("Fork Error Layer 1");}
    exit(EXIT_SUCCESS);
}