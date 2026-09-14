#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <wctype.h> //interação com input de teclado, vamos por partes

//para melhor leitura do codigo
#define VAZIO 0
#define BOMBA 1
#define PLAYER 2
#define CHEGADA 3
#define PASSADO 4

typedef struct obj_campo{
    char data;
    int x;
    int y;
    struct obj_campo *norte;
    struct obj_campo *nordeste;
    struct obj_campo *noroeste;
    struct obj_campo *sul;
    struct obj_campo *sudeste;
    struct obj_campo *sudoeste;
    struct obj_campo *leste;
    struct obj_campo *oeste;
}obj_campo;

//cabeçalho das funções
void inicializar();
void teste_campo();
int Bperto(int ip, int ij);

int main()
{
    obj_campo *com_camp = NULL;
    obj_campo *fim_camp = NULL;
    obj_campo *atual = NULL;
    int Bombas, ip=0, jp=0;
    int mov;

    inicializar();
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

obj_campo *inicializar()
{
    int x = 1, y = 1, QBtotal = 120, tam_camp = 10*50-6, pctg_bomba;
    obj_campo *novo = (obj_campo *)malloc(sizeof(obj_campo));

    if(novo == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    do{
        novo->x = x;
        novo->y = y;
        if(x == 1 && y == 1 || x == 2 && y == 1 || x == 1 && y == 2 || x == 49 && y == 10 || x == 50 && y == 9){
            novo->data = VAZIO;
        }else{
            
        }

    }while(x)
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
