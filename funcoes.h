#ifndef _funcoes_H_
#define _funcoes_H_

typedef struct Carro{
    char placa[10];
    char marca[30];
    int ano;
    struct Carro* prox;
}carro;

typedef struct Arvore{
    carro* lista_carros;
    struct Arvore *sad;
    struct Arvore *sae;
    
}arvore;

carro *cria_lista();
void inicia_lista(carro *le);
void cadastrar_carro(carro *le);
void deleta_carro(carro *le, char placa[10]);
void imprime_carros(carro *le);
void libera_lista(carro *le);
int quantidade_carros(carro *le);
int arv_vazia(arvore* a);
arvore* arv_cria_vazia();
arvore* ordena_arvore_ano(arvore* a, carro *lec, int cadastro);
arvore* ordena_arvore_placa(arvore* a, carro *lec, int cadastro);
arvore* ordena_arvore_marca(arvore* a, carro *lec, int cadastro);
arvore* busca_placa_arvore(arvore* a, char placa[10]);
arvore* arv_libera(arvore* a);
void recebe_dados_de_busca(arvore* a);
void arv_imprime(arvore* a);
void menu_principal(); 

#endif