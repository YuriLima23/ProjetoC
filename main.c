#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// http://www.inf.ufg.br/~hebert/disc/aed1/AED1_09_Pilas.pdf pode ajudar ;
//  https://www.cos.ufrj.br/~rfarias/cos121/filas.html
// https://www.cprogressivo.net/2014/05/Filas-em-C-Como-Programar-Tutorial-Estrutura-de-Dados-Dinamica-Queue.html
// build table
#define SEPARADOR -10

// Start Struct Process ===============================

typedef struct
{
    long pid;
    int time;
    int cpu1;
    int inOut;
    int tempoEspera;
    int cpu2;
} Process;

Process vet[3], psAux, vazio;

Process espera[3], prontos[3];

void listProntos()
{

    for (int i = 0; i < 3; i++)
    {
        printf("Posicao:  %d  PID : %ld esta Pronto \n \n ", i, prontos[i].pid);
    }
}

void removePronto()
{

    prontos[0] = psAux;
    while (prontos[0].pid == -1)
    {
        prontos[0] = prontos[1];
        prontos[1] = prontos[2];
        prontos[2] = vazio;
    }
    printf("Um Item FOI REMOVIDO dos Prontos : \n \n ");
}

void insertPronto(Process p)
{

    if (prontos[0].pid == 0)
    {
        printf("\n \n Colocu na PRIMEIRA POSICAO Pronto \n \n ");
        prontos[0] = p;
    }
    else if (prontos[1].pid == 0)
    {
        printf("\n \n Colocu na SEGUNDA POSICAO Pronto\n \n ");
        prontos[1] = p;
    }
    else
    {
        printf("\n \n Colocu na TERCEIRA POSICAO Pronto \n \n ");
        prontos[2] = p;
    }
}

Process getPrimeiroProcesso()
{
    return prontos[0];
}

void listEspera()
{

    for (int i = 0; i < 3; i++)
    {
        printf("Posicao:  %d  PID : %ld esta em Espera\n \n  \n", i, espera[i].pid);
    }
}

void removeEspera(Process p)
{
     for (int i = 0; i < 3; i++)
    {
        if (espera[i].pid == p.pid)
        {
            espera[i] = psAux;
            break;
        }
    }

    while (espera[0].pid == -1)
    {
        espera[0] = espera[1];
        espera[1] = espera[2];
        espera[2] = vazio;
    }
   
    printf("Um Item FOI REMOVIDO da Espera : \n \n ");
}

void insertEspera(Process p)
{

    if (espera[0].pid == 0)
    {
        printf("\n \n Colocu na PRIMEIRA POSICAO \n \n ");
        espera[0] = p;
    }
    else if (espera[1].pid == 0)
    {
        printf("\n \n Colocu na SEGUNDA POSICAO \n \n ");
        espera[1] = p;
    }
    else
    {
        printf("\n \n Colocu na TERCEIRA POSICAO \n \n ");
        espera[2] = p;
    }
}

Process getPrimeiroProcessoEspera()
{
    return espera[0];
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

void orderPosition()
{
    int i, j;
    Process aux;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (vet[i].time < vet[j].time)
            {

                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
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

Process procuraVetorOriginal(Process p)
{
    for (int i = 0; i < 3; i++)
    {
        if (vet[i].pid == p.pid)
        {
            return vet[i];
        }
    }
}

void verificaEspera(int j)
{
    if (espera[0].pid != 0){
        for (int i = 0; i < 3; i++)
    {
        espera[i].tempoEspera = espera[i].inOut + j;
        if (espera[i].tempoEspera == j )
        {
            printf("Removeu espera pid : %ld \n \n ",espera[i].pid);
            removeEspera(espera[i]);
            insertPronto(espera[i]);
            break;
        }
    }
    }
    
}

int main()
{
    Process exec;

    int min = 100000;
    bool t = false;
    Process p1, p2, p3, eliminado;
    psAux.pid = -1;
    psAux.time = 0;
    psAux.cpu1 = 0;
    psAux.cpu2 = 0;

    p1.pid = rand() % 10000;
    p2.pid = rand() % 10000;
    p3.pid = rand() % 10000;

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
    orderPosition(vet);
    generatorTable(vet);
    // start execute
    printf("Inciando Gerenciamento de Processos : \n");
    printf("Processo do Sistema em execução \n");
    printf(" ================================================================ \n");

    int x = 0;
    bool j = true;
    int tempo = -1;
    Process pro;

    exec = psAux;
    for (int i = 0; i < sumProcessTime(vet); i++)
    {
        printf("\n \n  TEMPO I  : %d \n \n ", i);

        if (vet[x].time == i)
        {
            insertPronto(vet[x]);
            listProntos();

            if (x >= 2)
            {
                x = 0;
            }
            else
            {
                x++;
            }
        }
        if (exec.pid == psAux.pid)
        {
            exec = getPrimeiroProcesso();
            removePronto();
        }
        if (exec.cpu1 > 0)
        {

            printf("O PID : %ld esta em execução Tempo : %d \n \n", exec.pid, exec.cpu1--);
            listProntos();
            verificaEspera(i);
            listEspera();
           

            j = true;
        }
        if (exec.cpu1 == 0)
        {
            printf("O PID : %ld esta FINALIZADO Tempo : %d \n \n", exec.pid, exec.cpu1);
            // a variavel tempo vai ser quabndo ele vai sair da espera para pronto
            eliminado = exec;

            exec = psAux;

            //  printf("\n \n PRo : %d \n \n  ",pro.inOut);
            // printf("\n \n PRo : %d \n \n  ",pro.tempoEspera);
            insertEspera(eliminado);
        }
       
    }
}
