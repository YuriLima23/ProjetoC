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
    int cpu2;
} Process;

typedef struct
{
    int comeco;
    int fim;
    Process p[3];
} Fila;


Process vet[3];

Fila * createFila()
{
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->comeco = 0;
    fila->fim = -1;
    return fila;
}
Process firstPositionFila(Fila *fila)
{
    int i = 0;
    return fila->p[fila->comeco];
}

void insertFila(Fila *fila, Process p)
{
    if(fila->fim == 3 - 1)
		printf("Fila está lotada, aguarde... \n");
	else
	{
        
		fila->fim++;
		fila->p[fila->fim] = p;
        printf("Um item foi inserido na fila \n \n ");
	}
    
}
//  ta removendo errado
void removeFila(Fila *fila)
{
    if(fila->fim < fila->comeco)
		printf("fila Vazia\n");
	else{
        printf("UM elemento foi removido \n \n ");
        fila->comeco++;
    }

		
  
}

void listFila(Fila *fila)
{
    printf("Lista de Processos Pontos : \n");
   int i = 0;
    	if(fila->fim < fila->comeco)
		printf("fila Vazia \n");
	else
	{
    		while(i < 3)
		{
			printf("Posicao : %d  PID :  %ld Esta Pronto :  \n", i,fila->p[i].pid);
			i++;
		}
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

void orderPosition()
{
    int i, j;
    Process aux;
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (vet[i].time < vet[j].time)
            {
                //aqui acontece a troca, do maior cara  vaia para a direita e o menor para a esquerda
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

    int main()
    {
        Process exec;

        int min = 100000;
        bool t = false;
        Fila *prontos = createFila(); 
        Fila *espera = createFila();
       
        Process p1, p2, p3, psAux;
        psAux.pid =0;
        psAux.time =0;
        psAux.cpu1 =0;
        psAux.cpu2 =0;


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

       
        exec = psAux;
        for (int i = 0; i < sumProcessTime(vet); i++)
        {
           
            if (vet[x].time == i)
            {
                insertFila(prontos, vet[x]);
                listFila(prontos);
              
                if (x >= 2){
                    x = 0;
                    
                }else{
                    x++;
                    
                }
                
            }
             if (exec.pid == psAux.pid)
                {
                    exec = firstPositionFila(prontos);
                    removeFila(prontos);
                } 
                    if (exec.cpu1 > 0){

                        printf("O PID : %ld esta em execução Tempo : %d \n \n", exec.pid, exec.cpu1--);
                        listFila(prontos);
                        j = true;
                       
                        }else{
                            printf("O PID : %ld esta FINALIZADO \n \n", exec.pid);
                            exec = psAux;  
                            listFila(prontos);
                    }
          
           
        }
    }


/*
Autor Marcio spents

*/

/*


#include <stdio.h>
#include <stdlib.h>

struct no {
   int valor;
   struct no *proxptr;
   };

typedef struct no NO;
typedef NO *NOPTR;

void insere_fila(NOPTR *, NOPTR *, int);
void retira_fila (NOPTR *, NOPTR *);
void mostra_fila (NOPTR);


int main(void)
{
   NOPTR inicio=NULL, fim=NULL;
   int elemento=0;
   int opcao=-1;

   while (opcao != 0)
         {
printf ("\n\n1 - Insere elemento na fila");
printf ("\n2 - Retira elemento da fila");
printf ("\n3 - Mostra fila");
printf ("\n0 - Encerra programa");
printf ("\nOpcao ?");
scanf ("%d", &opcao);
switch (opcao)
    {
case 1:
        printf ("\nInforme valor: ");
scanf ("%d", &elemento);
insere_fila(&inicio, &fim, elemento);
mostra_fila(inicio);
printf ("\n\n");
break;
case 2:
retira_fila(&inicio, &fim);
mostra_fila(inicio);
printf ("\n\n");
break;
case 3:
mostra_fila(inicio);
printf ("\n\n");
break;
}
}

   return 1;
}

void insere_fila (NOPTR *inicio, NOPTR *fim,  int elemento)
{
NOPTR novo;

novo = (NOPTR) malloc (sizeof (NO));
novo->valor = elemento;
novo->proxptr = NULL;

    if (*inicio == NULL)
*inicio = novo;
else
(*fim)->proxptr = novo;
*fim = novo;
}

void retira_fila (NOPTR *inicio, NOPTR *fim)
{
NOPTR temp=NULL;
    if (*inicio == NULL)
     printf ("Fila esta vazia...");
    else
    {

temp = *inicio;
*inicio = (*inicio)->proxptr;
if (*inicio == NULL)
    *fim = NULL;

    free(temp);
    }
}

void mostra_fila (NOPTR corrente)
{


while (corrente != NULL  )
    {
printf ("%d --> ", corrente->valor);
corrente = corrente->proxptr;
}

}
*/

