#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// build table
#define SEPARADOR -10

// Start Struct Process ===============================

typedef struct
{
    long pid;
    int time;
    int cpu1;
    int inOut;
    int cpu2;
    char state[2];
} Process;

Process espera[3];
Process pronto[3];
Process exec;
Process vetAux[3];


void listProntos()
{
    printf("Lista de Processos Prontos : \n ");
    if (pronto[0].pid == 0)
    {
        pronto[0] = pronto[1];
        pronto[1] = pronto[2];
        pronto[2] = vetAux[0];
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Posição %d  PID: %ld \n ", i, pronto[i].pid);
    }
}

void listEspera()
{
    printf("Lista de Processos em Espera : \n");
    if (espera[0].pid == 0)
    {
        espera[0] = espera[1];
        espera[1] = espera[2];
        espera[2] = vetAux[0];
    }
    for (int i = 0; i < 3; i++)
    {
        printf("Posição %d  PID: %ld \n", i, espera[i].pid);
    }
}

void stateMode(Process p)
{

    if (strcmp(p.state, "p") == 0 || strcmp(p.state, "P") == 0)
    {
        printf("Processo pid : %ld Esta Pronto \n", p.pid);
        listProntos();
    }
    if (strcmp(p.state, "ex") == 0 || strcmp(p.state, "Ex") == 0)
    {

        printf("Processo pid : %ld Esta em Execução \n", p.pid);
        
    }
    if (strcmp(p.state, "e") == 0 || strcmp(p.state, "e") == 0)
    {
        printf("Processo pid : %ld Esta em Espera \n", p.pid);
        listEspera();
    }
    if (strcmp(p.state, "n") == 0 || strcmp(p.state, "N") == 0)
    {
        printf("Processo pid : %ld Esta sendo Criado \n", p.pid);
    }
}

int sumProcessTime(Process p[3])
{
    int soma = 0;
    for (int i = 0; i < 3; i++)
    {
        soma = (p[i].cpu1 + p[i].cpu2) + soma;
    }
    return soma;
}
int listExec(int i)
{
    exec.cpu1 = exec.cpu1 - 1;
    if (exec.cpu1 == 0 || exec.cpu1 < 0)
    {
        printf("\n \n Processo PID : %ld esta FINALIZADO \n \n ", exec.pid);
        return 1;
    }
    else
    {
        printf("\n Processos na lista de execução : \n");
        printf("PID: %ld  Tempo de execução : %d \n \n", exec.pid, exec.cpu1);
        return 0;
    }
}


void generatorTable(Process p[3])
{

    printf("+--------+-----+--------+--------+-----+-----+---+                                       |\n");
    printf("| .::Informações do process::.                                                           |\n");
    printf("+--------+-----+--------+--------+-----+-----+---+                                       |\n");
    printf("| Pid     |    Time In       |    CPU 1       |  IN/OUT         |    CPU2         |\n");
    printf("|-----    |                  |                |                 |                 ||\n");
    printf("| %ld     |     %d           |    %d          |   %d            |   %d            ||\n", p[0].pid, p[0].time, p[0].cpu1, p[0].inOut, p[0].cpu2);
    printf("| %ld     |     %d           |    %d          |   %d            |   %d            ||\n", p[1].pid, p[1].time, p[1].cpu1, p[1].inOut, p[1].cpu2);
    printf("| %ld     |     %d           |    %d          |   %d            |   %d            ||\n", p[2].pid, p[2].time, p[2].cpu1, p[2].inOut, p[2].cpu2);
}

int main()
{
    Process vet[3];

    int min = 100000;
    int x = 0, k = 0;
    bool t = false;

    Process p1, p2, p3, psAux;

    pronto[0] = p1;
    pronto[1] = p1;
    pronto[2] = p1;
    p1.pid = rand() % 10000;
    p2.pid = rand() % 10000;
    p3.pid = rand() % 10000;
    psAux.pid = rand() % 10000;
    // // Process P1 ==============================
    printf("Digite Tempo de Chegada do Processo P1 :");
    scanf("%d", &p1.time);
    printf("Digite Tempo de Processamento do Processo P1 :");
    scanf("%d", &p1.cpu1);
    printf("Digite Tempo de Entrada/Saida do Processo P1 :");
    scanf("%d", &p1.inOut);
    printf("Digite Tempo de Processamento 2 do Processo P1 :");
    scanf("%d", &p1.cpu2);

    // // Process P2 =============================
    printf("Digite Tempo de Chegada do Processo P2 :");
    scanf("%d", &p2.time);
    printf("Digite Tempo de Processamento do Processo P2 :");
    scanf("%d", &p2.cpu1);
    printf("Digite Tempo de Entrada/Saida do Processo P2 :");
    scanf("%d", &p2.inOut);
    printf("Digite Tempo de Processamento 2 do Processo P2 :");
    scanf("%d", &p2.cpu2);

    // // END Process P2 ==========================

    // // Process P3 =============================
    printf("Digite Tempo de Chegada do Processo P3 :");
    scanf("%d", &p3.time);
    printf("Digite Tempo de Processamento do Processo P3 :");
    scanf("%d", &p3.cpu1);
    printf("Digite Tempo de Entrada/Saida do Processo P3 :");
    scanf("%d", &p3.inOut);
    printf("Digite Tempo de Processamento 2 do Processo P3 :");
    scanf("%d", &p3.cpu2);

    // END Process P3 ==========================
    vet[0] = p1;
    vet[1] = p2;
    vet[2] = p3;
    generatorTable(vet);

    // // Find min Number
    for (int i = 0; i <= 2; i++)
    {
        if (vet[i].time < min)
        {
            min = vet[i].time;
        }
    }

    // start execute
    printf("Inciando Gerenciamento de Processos : \n");
    printf("Processo do Sistema em execução \n");
    printf(" ================================================================ \n");
    int w = 0;
    t = false;
    for (int i = 0; i < sumProcessTime(vet); i++)
    {
        if (i == vet[x].time && t == false)
        {
            printf("Entrou um novo PID: \n");
            if (pronto[0].pid == 0){
                pronto[0] = vet[x];
            }else if (pronto[1].pid == 0) {
                 pronto[1] = vet[x];
            }else{
                 pronto[2] = vet[x];
            }
            strcpy(vet[x].state, "p");
            stateMode(pronto[x]);
            listProntos();
            printf("\n \n ");
            (x == 2) ? x = 0 : x++;
            t = true;
        }
        //tira dos prontos e inicia a execução
        if (t == true)
        {
            printf("Começou a execução \n");
            //esse if é para colocar na lista de espera
            if (exec.pid != 0){
                if ( espera[0].pid == 0){
                espera[0] = exec;
                }else if (espera[1].pid == 0) {
                  espera[1] = exec;
                }else{
                 pronto[2] = exec;
                }
                espera[w] = exec;
                exec = vetAux[0];
                strcpy(espera[w].state,"e");
                stateMode(espera[w]);
                (w == 2) ? w = 0 : w++;
            }
            exec = pronto[0];
            pronto[0] = vetAux[0];
            strcpy(exec.state, "ex");
            stateMode(exec);
            int d = listExec(i);
            if (d == 1)
            {
                break;
            }
            listProntos();
            t = false;
           
        }
        // segue a execução contando enquanto não entra um novo
        else
        {
            printf("Seguiu Processo \n");
            int j = listExec(i);
            if (j == 1)
            {
                continue;
            }
        }
    }
}
