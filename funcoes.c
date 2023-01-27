#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "funcoes.h"

void inicia_lista(carro *le){
	le->prox = NULL;
}

carro *cria_lista(){
	carro *novo = (carro*)malloc(sizeof(carro));
	if(!novo){
		printf("\nSem memoria disponivel!");
		exit(1);
	}
  	return novo;
}

void cadastrar_carro(carro *le){ 
    printf("\n-> Novo cadastro de carro <-");
    carro *aux, *novo = cria_lista(); 
    
	printf("\nInforme a placa: "); 
    scanf (" %[^\n]", novo->placa);
    printf("Informe a marca: "); 
    scanf (" %[^\n]", novo->marca);
    printf("Informe o ano: ");  
    scanf("%d", &novo->ano);
    
    if (le->prox == NULL){
        novo->prox = NULL;
        le->prox=novo;
    }
    else if (strcmp(novo->placa, le->prox->placa)<0){
        novo->prox = le->prox;
        le->prox = novo;
    }
    else{
        aux = le->prox;
        while (aux->prox && strcmp(novo->placa, aux->prox->placa)>0) aux = aux->prox; 
        novo->prox = aux->prox;
        aux->prox = novo;
    }    
    printf("\n-> Cadastro realizado com sucesso.\n");
}

int quantidade_carros(carro *le){
    carro *tmp;
    tmp = le->prox;
    int qtde = 0;
    while(tmp != NULL){
        tmp = tmp->prox;
        qtde++;
    }
    return qtde; 
}

void deleta_carro(carro *le, char placa[10]){
    if (le->prox == NULL) printf("\nSem carros cadastradas!\n");
    else{
        carro *tmp = le;
        carro *anterior;
        while (tmp != NULL && (strcmp(tmp->placa, placa) != 0)){
            anterior = tmp;
            tmp = tmp->prox;
        }
        if (anterior == NULL) tmp = tmp->prox;
        else anterior->prox = tmp->prox;
        free(tmp);
        printf("Cadastro deletado com sucesso.\n");
    }
}

void imprime_carros(carro *le){
    if (le->prox == NULL) printf("Sem carros cadastrados!\n"); 
    else{
        carro *tmp;
        tmp = le->prox;
        while(tmp != NULL){
            printf("\nPlaca: %s - ", tmp->placa);
            printf("Ano: %d - ", tmp->ano); 
            printf("Marca: %s", tmp->marca); 
            tmp = tmp->prox;
        }
    }
}

void libera_lista(carro *le){
    if (le->prox != NULL)
    {
		carro *proxNo, *atual;
		atual = le->prox;
		while(atual != NULL){
			proxNo = atual->prox;
			free(atual);
			atual = proxNo;
		}
	}
}

arvore* arv_cria_vazia(){ 
    return NULL;
} 

int arv_vazia(arvore* a){
    return a==NULL;
}

arvore* ordena_arvore_ano(arvore* a, carro *lec, int cadastro){
    carro *Carro;
    Carro = lec->prox;
    for (int i = 1; i <= cadastro; i++) if (i != cadastro) Carro = Carro->prox;
    
    if (a==NULL){
        a = (arvore*)malloc(sizeof(arvore));
        a->lista_carros = Carro; 
        a->sae = a->sad = NULL;
    }
    else if (Carro->ano < a->lista_carros->ano)  a->sae = ordena_arvore_ano(a->sae, lec, cadastro); 
    else a->sad = ordena_arvore_ano(a->sad, lec, cadastro);
    return a;
}

arvore* ordena_arvore_placa(arvore* a, carro *lec, int cadastro){
    carro *Carro;
    Carro = lec->prox;
    for (int i = 1; i <= cadastro; i++) if (i != cadastro) Carro = Carro->prox;

    if (a==NULL){
        a = (arvore*)malloc(sizeof(arvore));
        a->lista_carros = Carro; 
        a->sae = a->sad = NULL; 
    }
    else if (strcmp(Carro->placa, a->lista_carros->placa)<0) a->sae = ordena_arvore_placa(a->sae, lec, cadastro);  
    else a->sad = ordena_arvore_placa(a->sad, lec, cadastro);
    return a;
}

arvore* ordena_arvore_marca(arvore* a, carro *lec, int cadastro){
    carro *Carro;
    Carro = lec->prox;
    for (int i = 1; i <= cadastro; i++) if (i != cadastro) Carro = Carro->prox;

    if (a==NULL){
        a = (arvore*)malloc(sizeof(arvore));
        a->lista_carros = Carro; 
        a->sae = a->sad = NULL; 
    }
    else if (strcmp(Carro->marca, a->lista_carros->marca)<0) a->sae = ordena_arvore_marca(a->sae, lec, cadastro);   
    else a->sad = ordena_arvore_marca(a->sad, lec, cadastro);
    return a;
}

arvore* busca_placa_arvore(arvore* a, char placa[10]){
    if (a==NULL) return NULL; 
    else if (strcmp(placa, a->lista_carros->placa)<0) return busca_placa_arvore(a->sae, placa);
    else if (strcmp(placa, a->lista_carros->placa)>0) return busca_placa_arvore(a->sad, placa);
    else{
        printf("\nPlaca: %s - Ano: %d - Marca: %s", a->lista_carros->placa, a->lista_carros->ano, a->lista_carros->marca);
        return a;
    }
}

void recebe_dados_de_busca(arvore* a){
    char placa[10];
    arvore *busca_placa;
    printf("\nInforme a placa que deseja buscar: ");
    scanf (" %[^\n]", placa);
    busca_placa = busca_placa_arvore(a, placa);

    if (busca_placa==NULL) printf("A placa - %s - nao esta cadastrada no sistema.", placa);
    else printf("\nA placa esta cadastrada no sistema.");
}

void arv_imprime(arvore* a){
    if (!arv_vazia(a)){
        arv_imprime(a->sae);    
        printf("\nPlaca: %s - ", a->lista_carros->placa);
        printf("Ano: %d - ", a->lista_carros->ano); 
        printf("Marca: %s", a->lista_carros->marca); 
        arv_imprime(a->sad);    
    }
}

arvore* arv_libera(arvore* a){
    if(!arv_vazia(a)){
        arv_libera(a->sae);
        arv_libera(a->sad);
        free(a);
    }
    return NULL;
}

void menu_principal(){
    int main_op, total_carros = 0;
    char placa[10];
    carro *lec = cria_lista();
    inicia_lista(lec);
    arvore *arv_ano = arv_cria_vazia();
    arvore *arv_placa = arv_cria_vazia();
    arvore *arv_marca = arv_cria_vazia();
    do
    {
        printf("\n\n---- SISTEMA NACIONAL DE VEICULOS ----\n");
        printf("\n\t--> 1. CADASTRAR VEICULO");
        printf("\n\t--> 2. EXCLUIR VEICULO");
        printf("\n\t--> 3. BUSCAR VEICULO ");
        printf("\n\t--> 4. LISTAR OS VEICULOS PELA PLACA");
        printf("\n\t--> 5. LISTAR OS VEICULOS PELA MARCA");
        printf("\n\t--> 6. LISTAR OS VEICULOS PELO ANO");
        printf("\n\t--> 7. SAIR");
        printf("\n\t---> Opcao: ");
        scanf("%d", &main_op);
        switch (main_op)
        {
            case 1:
                cadastrar_carro(lec);
                break;
            case 2:
                printf("\nInforme a placa: "); 
                scanf (" %[^\n]", placa);
                deleta_carro(lec, placa);
                break;
            case 3:
                recebe_dados_de_busca(arv_placa);         
                break;
            case 4:
                arv_placa = NULL;
                printf("\nLista ordenada pela placa:\n");
                for (int i = 1; i <= total_carros; i++) arv_placa = ordena_arvore_placa(arv_placa, lec, i);
                imprime_carros(lec);
                break;  
            case 5:
                arv_marca = NULL;
                printf("\nArvore ordenada pela marca:\n");
                for (int i = 1; i <= total_carros; i++) arv_marca = ordena_arvore_marca(arv_marca, lec, i); 
                arv_imprime(arv_marca); 
                break;  
            case 6:
                arv_ano = NULL;
                printf("\nArvore ordenada pelo ano:\n");
                for (int i = 1; i <= total_carros; i++) arv_ano = ordena_arvore_ano(arv_ano, lec, i);
                arv_imprime(arv_ano); 
                break; 
            case 7:
                printf("\tFinalizando o programa...\n");
                break;  
            default:
                printf("\n\t---> Opcao invalida, tente novamente!\n");
                break;
        }
        total_carros = quantidade_carros(lec);
    } while (main_op != 7);

    libera_lista(lec);
    arv_libera(arv_ano);
    arv_libera(arv_placa);
    arv_libera(arv_marca);
}   