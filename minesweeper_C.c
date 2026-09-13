#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wctype.h> //tentativa de interação com input de teclado

//para melhor leitura do codigo
#define VAZIO 0
#define BOMBA 1
#define PLAYER 2
#define CHEGADA 3
#define PASSADO 4

//matrizes e lista global (na epoca tinha que ser global)
char campo[10][50]; //campo exibido para o player
char CBomba[10][50]; //campo que o programa vai ver
char elementos[] = {"OXPCo"}; //lista com elementos interativos

//cabeçalho das funções
void inicializar(int QBtotal);
void teste_campo();
int Bperto(int ip, int ij);

int main()
{
    int QBtotal = 120, Bombas, ip=0, jp=0;
    int mov;

    inicializar(QBtotal);
    do
    {
        teste_campo();
        Bombas = Bperto(ip, jp);
        printf("1:W 2:A 3:S 4:D Sair: 0 Bombas: %d\n", Bombas);
        scanf("%d", &mov);
        //mov = towupper(mov);

        //impede o player de sair do mapa
        if((mov==1&&jp==0)||(mov==2&&ip==0)||(mov==3&&ip==9)||(mov==4&&jp==49))
            continue;
        else
        {
            switch(mov)
            {
                case 1: //move pra cima e atualiza a posição do player
                    campo[ip][jp] = elementos[PASSADO];
                    jp--;
                    campo[ip][jp] = elementos[PLAYER];
                case 2: //move pra esquerda e atualiza a posição do player
                    campo[ip][jp] = elementos[PASSADO];
                    ip--;
                    campo[ip][jp] = elementos[PLAYER];
                case 3: //move pra direita e atualiza a posição do player
                    campo[ip][jp] = elementos[PASSADO];
                    ip++;
                    campo[ip][jp] = elementos[PLAYER];
                case 4: //move pra baixo e atualiza a posição do player
                    campo[ip][jp] = elementos[PASSADO];
                    jp++;
                    campo[ip][jp] = elementos[PLAYER];
                case 0: //sair
                    mov = 0;
            }
        }
    }
    while(mov!=0);

    return 0;
}

void inicializar(int QBtotal)
{
    int i, j, QIbomba;

    QIbomba = 0;

    srand(time(NULL)); //sem isso o campo de bombas é sempre o mesmo

    //cria os campos
    for(i=0; i<10; i++)
    {
        for(j=0; j<50; j++)
        {
            campo[i][j] = elementos[VAZIO];
            CBomba[i][j] = elementos[VAZIO];
        }
    }

    //define alguns elementos padrão
    campo[0][0] = elementos[PLAYER];
    campo[9][49] = elementos[CHEGADA];
    CBomba[9][49] = elementos[CHEGADA];

    //preenche o campo de bombas
    while(QIbomba<QBtotal)
    {
        //randomiza numeros
        i = rand()%10;
        j = rand()%50;
        //cria uma area sem bombas ao redor do player no começo e no final
        if((i==0&&j==0)||(i==9&&j==49)||(i==1&&j==1)||(i==0&&j==1)||(i==1&&j==0)||(i==9&&j==48)||(i==8&&j==49))
            continue;
        //não põe duas bombas no mesmo lugar
        if(CBomba[i][j]==elementos[BOMBA])
            continue;
        else
        {
            CBomba[i][j] = elementos[BOMBA];
            QIbomba++;
        }
    }
}

void teste_campo()
{
    int i, j;

    for(i=0; i<10; i++)
    {
        for(j=0; j<50; j++)
        {
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int Bperto(int ip, int jp) //recebe a posição do player
{
    int i, j, c;

    c = 0;

    //verifica cada posição ao redor do player e conta as bombas
    for(i=ip-1; i<ip+1; i++)
    {
        for(j=jp-1; j<jp+1; j++)
        {
            if(CBomba[i][j]=='X')
                c++;
        }
    }

    return c;
}
