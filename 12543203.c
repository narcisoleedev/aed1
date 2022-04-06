/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/** Guilherme Narciso Lee   nUSP:12543203                           **/
/**                                                                 **/
/*********************************************************************/

// Esse EP me tomou umas boas horas professor, haha, principalmente a ordenação.

#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}
void organizar(PLISTA l,  int tipo, PONT end, PONT ant){
    ant->proxProd = end->proxProd;
    end->proxProd = NULL;
    PONT atual, prox, pref;
    atual = l->LISTADELISTAS[tipo];
    prox = atual->proxProd;
    while(prox!=NULL)
    {
        if(end->valorUnitario*end->quantidade>=prox->quantidade*prox->valorUnitario) 
        {
            pref = prox->proxProd;
            atual->proxProd = prox;
            end->proxProd = prox->proxProd;
            prox->proxProd = end;
        }
        else{
            atual->proxProd = end;
            end->proxProd = prox;
            break;
        }
        atual = prox;
        prox = pref;
    }
}
bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
    PONT atual, ant, prox, pref;
    if(tipo<0 || tipo>=10) return false;
    if(quantidade<=0 || valor<=0 || id<=0) return false;
    for(int i=0;i<NUMTIPOS;i++){ 
        atual = l->LISTADELISTAS[i]->proxProd;
        while(atual)
        {
            if(atual->id == id) return false;
            atual = atual->proxProd;
        }
    }
    ant = (PONT)malloc(sizeof(REGISTRO));
    ant->id = id;
    ant->quantidade = quantidade;
    ant->valorUnitario = valor;
    ant->proxProd = NULL;
    prox = l->LISTADELISTAS[tipo];
    while(prox->proxProd!=NULL){
        if(quantidade*valor>=prox->proxProd->quantidade*prox->proxProd->valorUnitario)prox = prox->proxProd;
        else{
            pref = prox->proxProd;
            prox->proxProd = ant;
            ant->proxProd = pref;
            pref->proxProd=NULL;
            break;
        }
    }
    prox->proxProd = ant;
    return true;
}

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){
    PONT atual, ant, end;
    int tipo;
    if(quantidade<=0 || id<=0) return false;
    for(int i=0;i<NUMTIPOS;i++){ 
        ant = l->LISTADELISTAS[i];
        atual = l->LISTADELISTAS[i]->proxProd;
        while(atual)
        {
            if(atual->id == id){
                if(quantidade < atual->quantidade)
                {
                    atual->quantidade = atual->quantidade-quantidade;
                    tipo = i;
                    end=atual;
                    if(l->LISTADELISTAS[i]->proxProd->proxProd==NULL);
                    else{
                        organizar(l, tipo, end, ant);
                    }
                    return true;
                }
                else if(quantidade==atual->quantidade){
                    ant->proxProd = atual->proxProd;
                    free(atual);
                    return true;
                }
                else{
                    return false;
                }
            }
            ant = ant->proxProd;
            atual = atual->proxProd;
        }
    }
    return false;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){
    PONT atual, ant, end;
    int tipo;
    if(valor<=0) return 0;
    for(int i=0;i<NUMTIPOS;i++){ 
        atual = l->LISTADELISTAS[i]->proxProd;
        ant = l->LISTADELISTAS[i];
        while(atual)
        {
            if(atual->id == id)
            {
                atual->valorUnitario = valor;
                tipo = i;
                end=atual;
                if(l->LISTADELISTAS[i]->proxProd->proxProd==NULL);
                else{
                    organizar(l, tipo, end, ant);
                }
                return true;
            }
            ant = atual;
            atual = atual->proxProd;
        }
    }
    return false;
}