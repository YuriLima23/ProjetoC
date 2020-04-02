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
    bool state;
    int cpu2;
    int ts;
    float tmip;
    float tt;
    float ttts;
} Process;

Process vet[3], psAux, vazio, dados[3];

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
    listProntos();
}

Process getPrimeiroProcesso()
{
    return prontos[0];
}

void listEspera()
{

    for (int i = 0; i < 3; i++)
    {
        printf("Posicao:  %d  PID : %ld esta em Espera , Tempo Espera : %d\n \n  \n", i, espera[i].pid, espera[i].tempoEspera);
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
    // espera[0] = psAux;
    while (espera[0].pid == -1)
    {
        espera[0] = espera[1];
        espera[1] = espera[2];
        espera[2] = vazio;
    }

    printf("Um Item FOI REMOVIDO da Espera : \n \n ");
    listEspera();
}

void insertEspera(Process p)
{

    if (espera[0].pid == 0)
    {

        espera[0] = p;
    }
    else if (espera[1].pid == 0)
    {

        espera[1] = p;
    }
    else
    {

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
void frameInfo(Process p[3])
{

    printf("+--------+-----+--------+--------+---|\n");
    printf("| .::Informações To processamento ::.|\n");
    printf("+--------+-----+--------+--------+---|\n");
    printf("| PID | TC | TS | TMIP | TT   | TT/TS |\n");
    printf("|-----|---------|------|------|-------|\n");
    printf("| %ld | %d | %d |  %2f  | %2f |   %3f  |\n", vet[0].pid, vet[0].time, vet[0].ts, vet[0].tmip, vet[0].tt, vet[0].ttts);
    printf("| %ld | %d | %d |  %2f  | %2f |   %3f  |\n", vet[1].pid, vet[1].time, vet[1].ts, vet[1].tmip, vet[1].tt, vet[1].ttts);
    printf("| %ld | %d | %d |  %2f  | %2f |   %3f  |\n", vet[2].pid, vet[2].time, vet[2].ts, vet[2].tmip, vet[2].tt, vet[2].ttts);
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
    if (espera[0].pid != -1 && espera[0].pid != 0)
    {
        bool t;
        for (int i = 0; i < 3; i++)
        {
            if (espera[i].tempoEspera == j && espera[i].cpu1 <= 0)
            {
                espera[i].state = true;
                insertPronto(espera[i]);
                printf("Entrou no verifica espera posicao %d \n \n ", i);
            }
        }
        //precisa desse segundo for igual pra remover, pq se colocar tudo no mesmo for ele se perde nas posições
        //ex : quando eu removo da espera todos os itens são realocados então na prox vez que ele for compara os itens ja estão fora do lugar
        for (int i = 0; i < 3; i++)
        {
            if (espera[i].tempoEspera == j && espera[i].cpu1 <= 0)
            {
                espera[i].state = true;
                removeEspera(espera[i]);
                printf("Entrou no verifica espera 2 posicao %d \n \n ", i);
            }
        }
    }
}
Process calculaEspera(Process pa, int j)
{
    pa.tempoEspera = pa.inOut + j;
    return pa;
}
// ================================================ Revisão Professor  ====================================
void calculaTmip(Process p, int tempI)
{
    
    for (int i = 0; i < 3; i++)
    {
        
        if (vet[i].pid == p.pid)
        {
            // precisa disso pq o primeiro processo é calculado 2 vezes devido ao codigo mal feito 
            //então eu coloco -1 no inicio e se for diferente de -1 então ele ja foi calculado e só ignora 
            if (vet[i].tmip == -1)
            {
                vet[i].tmip = tempI - vet[i].time;
               
                break;
            }
        }
      
    }
}

void calculaTT(Process p, int fimT)
{
    float valor = 0;
    for (int i = 0; i < 3; i++)
    {
        if (vet[i].pid == p.pid)
        {
            // professor tem que verificar isso
            vet[i].tt = (fimT - vet[i].time);
            break;
        }
    }
}

void calculTtts()
{
    for (int i = 0; i < 3; i++)
    {
        
        vet[i].ttts = vet[i].tt / vet[i].ts;
        
    }
}

// ====================================== End Revisão =======================================

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

    p1.ts = 0;
    p2.ts = 0;
    p3.ts = 0;

    p1.tmip = -1;
    p2.tmip = -1;
    p3.tmip = -1;

    p1.tt = 0;
    p2.tt = 0;
    p3.tt = 0;

    p1.ttts = 0;
    p2.ttts = 0;
    p3.ttts = 0;

    p1.state = false;
    p2.state = false;
    p3.state = false;
    p1.tempoEspera = -1;
    p2.tempoEspera = -1;
    p3.tempoEspera = -1;

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
    bool j = false;
    int tempo = -1;
    Process pro;
    Process exec2;
    eliminado.pid = 0;
    exec = psAux;
    exec2 = psAux;
    int m = 0;
    int l = 0;
    int o = 0;
    for (int i = 0; i <= sumProcessTime(vet); i++)
    {
        printf("\n \n  TEMPO I  : %d \n \n ", i);

        if (j == false)
        {
            if (vet[x].time == i)
            {
                insertPronto(vet[x]);

                if (x >= 2)
                {
                    x = 0;
                }
                else
                {
                    x++;
                }
                // por causa do primeiro processo
                if (exec.pid == psAux.pid)
                {
                    exec = getPrimeiroProcesso();
                    // Calcula TMIP -------
                    calculaTmip(exec, i);
                    // End TMIP ------

                    // calcula tempo de processaento medio
                    removePronto();
                }
            }

            if (exec.cpu1 == 0)
            {
                printf("O PID : %ld esta FINALIZADO Tempo : %d \n \n", exec.pid, exec.cpu1);
                // a variavel tempo vai ser quabndo ele vai sair da espera para pronto

                eliminado = exec;
                exec = psAux;
                if (eliminado.pid != 0)
                {
                    eliminado = calculaEspera(eliminado, i);
                    insertEspera(eliminado);
                }
                if (exec.pid == psAux.pid)
                {
                    exec = getPrimeiroProcesso();
                    calculaTmip(exec, i);
                    if (exec.state == true)
                    {
                        j = true;
                        exec2 = psAux;
                    }
                    else
                    {
                        j = false;
                        removePronto();
                    }
                }
            }
            if (exec.cpu1 > 0)
            {

                printf("O PID : %ld esta em execução Tempo : %d \n \n", exec.pid, exec.cpu1--);
            }
        }

        // aqui começa a segunda parte a CPU2
        if (j == true)
        {

            if (exec2.pid == psAux.pid)
            {
                exec2 = getPrimeiroProcesso();

                removePronto(exec2);
            }

            if (exec2.cpu2 == 0)
            {
                printf("O PID CPU 2 : %ld esta FINALIZADO Tempo : %d \n \n", exec2.pid, exec2.cpu2);
                calculaTT(exec2, i);
                exec2 = psAux;
                if (exec2.pid == psAux.pid)
                {
                    exec2 = getPrimeiroProcesso();
                    removePronto(exec2);
                }

            }

            if (exec2.cpu2 > 0)
            {
                printf("O PID CPU 2 : %ld esta em execução Tempo : %d \n \n", exec2.pid, exec2.cpu2--);
                //tentando calcular o Turnaround Time
                
            }
        }
        else
        {
            verificaEspera(i);
            continue;
        }
        verificaEspera(i);
    }

    //calculo  tempo de serviço TS
    vet[0].ts = vet[0].cpu1 + vet[0].cpu2;
    vet[1].ts = vet[1].cpu1 + vet[1].cpu2;
    vet[2].ts = vet[2].cpu1 + vet[2].cpu2;

    calculTtts();

    // end tempo serviço
    // tabela final
    frameInfo(vet);
}
