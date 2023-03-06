#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

typedef struct elemento{
    int codigo;
    int qtd;
   float valor;
    struct elemento *prox;
}Elem;

typedef struct fila{
    struct elemento *inicio;
    struct elemento *fim;
}Fila;

Fila * cria_fila(){
    Fila *fi = (Fila *) malloc (sizeof(Fila));
    if(fi != NULL){
        fi->inicio = NULL;
        fi->fim = NULL;
    }
    return fi;
}

int insere_fila(Fila *fi, int codigo,int qtd,float valor){
    Elem *novo;
    if(fi == NULL){
        return 0;
    }
    novo = (Elem *) malloc (sizeof(Elem));
    if(novo == NULL){
        return 0;
    }

    novo->codigo = codigo;
    novo->qtd = qtd;
    novo->valor = valor;

    novo->prox = NULL;

    if(fi->inicio == NULL){
        fi->inicio = novo;
    }
    else{
     fi->fim->prox = novo;
    }
     fi->fim = novo;
     return 1;

}

void Imprime(Fila *fi)
{
    Elem *aux;
    aux = fi->inicio;
if(aux == NULL)
    printf("\nFila vazia.\n");

    printf("\n==Papelaria Gama==\n");
    while(aux != NULL){
        printf("========================================");
        printf("\nCodigo do produto: %d",aux->codigo);
        printf("\nQuantidade do produto: %d",aux->qtd);
        printf("\nValor do produto: R$ %.2f",aux->valor);
        printf("\n========================================\n");
        aux = aux->prox;
    }
    printf("\n");
}

int remove_fila(Fila *fi,int *codigo,float *valor)
{
    Elem *no; int qtd;

    if(fi == NULL)
        return 0;
    if(fi->fim == NULL)
        return 0;

    no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    qtd = no->qtd;
    *codigo = no->codigo;
    *valor = no->valor;
    if(fi->inicio == NULL)
        fi->fim = NULL;
    free(no);
    return qtd;
}

 int tamanho(Fila *fi)
 {
     int cont =0; Elem *no;
     if(fi == NULL)
     {
         return 0;
     }
     no = fi->inicio;
     while(no)
     {
         cont++;
         no = no->prox;
     }
     return cont;
 }




 void Altera(Fila *fi,int codigo, int qtd,float valor)
{
    Elem *aux;
    aux = fi->inicio;
if(aux == NULL)
    printf("\Sem Estoque.\n");

    printf("\n==Papelaria Gama==\n");
    while(aux != NULL){

       if(codigo == aux->codigo)
       {
           aux->qtd = qtd;
           aux->valor = valor;
       }
        aux = aux->prox;
    }
    printf("\n Produto atualizado.");
    printf("\n Pressione qualquer tecla  para continuar....!\n");
}


void verifica(Fila *fi,int codigo,int *existe)
{
    Elem *aux;
    aux = fi->inicio;

    while(aux != NULL){
        if(aux->codigo == codigo)
            *existe = 2;
        else
            *existe = 0;
        aux = aux->prox;
    }
    printf("\n");
}


int main (){
    setlocale(LC_ALL, "Portuguese");
    Fila *fi;
    int aux, resp,tamanhof,qtd,existe = 0;
    float valor;
    fi = cria_fila();
    if(fi == NULL){ //!f1 tbm funciona
        printf("Erro na criação");
        return 0;
    }
    int opcao = 0;
    do{
        system("cls");
        printf("\n====PAPELARIA GAMA====\n");
        printf("\n [1] - INSERIR PRODUTOS");
        printf("\n [2] - IMPRIMIR PRODUTOS SALVOS");
        printf("\n [3] - REMOVER PRODUTOS SEM QUANTIA NO ESTOQUE");
        printf("\n [4] - ALTERAR PRODUTO NO ESTOQUE");
        printf("\n [0] - Sair");
        printf("\n Digite a opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                system("cls");
                printf("\n [1] - Digite o codigo do produto: ");
                scanf("%d", &aux);
                verifica(fi,aux,&existe);
                while(existe!=0){
                printf("\n [1] - Digite o codigo do produto: ");
                scanf("%d", &aux);
                    verifica(fi,aux,&existe);
                }
                printf("\n [1] - Digite a quantidade do produto: ");
                scanf("%d", &qtd);
                printf("\n [1] - Digite o valor do produto: ");
                scanf("%f", &valor);
                resp = insere_fila(fi,aux,qtd,valor);
                if(resp == 0){
                    printf("\n ERRO\n");
                }else{
                    printf("\n Inserido!\n");
                   printf("\n Pressione qualquer tecla  para continuar....!\n");
                    getch();
                }
            break;
            case 2:
               Imprime(fi);
               printf("\n Pressione qualquer tecla  para continuar....!\n");
               getch();
               break;
            case 3:
             Imprime(fi);
          tamanhof = tamanho(fi);
                   for(int i =0; i<tamanhof; i++){
                        resp = remove_fila(fi,&aux,&valor);
                        if(resp !=0){
                        insere_fila(fi,aux,resp,valor);
                        }
                    }
             printf("\Removido produtos que não existia no estoque.\n");
             Imprime(fi);
             getch();
                break;
            case 4:
                system("cls");
                Imprime(fi);
                printf("\n [4] - Digite o codigo do produto: ");
                scanf("%d", &aux);
                printf("\n [4] - Digite a nova quantidade do produto: ");
                scanf("%d", &qtd);
                printf("\n [4] - Digite o novo valor do produto: ");
                scanf("%f", &valor);

                Altera(fi,aux,qtd,valor);
                    getch();
                break;
        }

    }while(opcao != 0);
    return 0;
}

