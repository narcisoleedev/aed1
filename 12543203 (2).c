/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   Turma 04 - Prof. Luciano Antonio Digiampietri                 **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   Guilherme Narciso Lee                  nUSP: 12543203         **/
/**                                                                 **/
/*********************************************************************/
// Feliz Natal professor, espero que eu não fique de recuperação haha.

#include "filaDePrioridade.h"
#define MAX 5

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->referencias = (PONT*) malloc(sizeof(PONT)*MAX);
  res->heap = (PONT*) malloc(sizeof(PONT)*MAX);
  int i;
  for (i=0;i<MAX;i++) {
    res->referencias[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}


bool exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f){
  int tam = 0;
  tam = f->elementosNoHeap;
  return tam;
}
void ajeitarheap(PFILA f, int i){
  int e= 2*i-1, d=2*i, p=i-1;
  int maior=0;
  if(e+1<=f->elementosNoHeap && f->heap[e]->prioridade>f->heap[p]->prioridade)
  {
    maior=e;
  }
  else{
    maior = p;
  }
  if(d+1<=f->elementosNoHeap && f->heap[d]->prioridade>f->heap[maior]->prioridade)
  {
    maior=d;
  }
  if(maior!=p){
    PONT par;
    int parint;
    parint=p;
    par=f->heap[p];
    f->heap[p]->posicao = maior;
    f->heap[p]=f->heap[maior];
    f->heap[maior]->posicao = parint;
    f->heap[maior]=par;
  }
}
void construirheap(PFILA f){
  if(f->elementosNoHeap%2==0)
  {
    for(int i=f->elementosNoHeap/2; i>0;i--) ajeitarheap(f, i);
  }
  else{
    for(int i=((f->elementosNoHeap-1)/2); i>0;i--) ajeitarheap(f, i);
  }
}
bool inserirElemento(PFILA f, int id, float prioridade){
  if(id<0 || id>=MAX) return 0;
  int i=0;
  for(int i=0;i<f->elementosNoHeap;i++)
  {
    if(f->referencias[i]->id==id) return 0;
  }
  f->elementosNoHeap++;
  PONT elemento = malloc(sizeof(ELEMENTO));
  elemento->id = id;
  elemento->prioridade = prioridade;
  elemento->posicao = f->elementosNoHeap-1;
  f->referencias[f->elementosNoHeap-1] = elemento;
  f->heap[f->elementosNoHeap-1] = elemento;
  construirheap(f);
  return 1;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  if(id<0 || id>=MAX) return 0;
  for(int i=0; i<f->elementosNoHeap;i++)
  {
    if(id==f->heap[i]->id && f->heap[i]->prioridade<novaPrioridade){
      f->heap[i]->prioridade = novaPrioridade;
      construirheap(f);
      return 1;
      break;
    }
  }
  return 0;
}
bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  if(id<0 || id>=MAX) return 0;
  for(int i=0; i<f->elementosNoHeap;i++)
  {
    if(id==f->heap[i]->id && f->heap[i]->prioridade>novaPrioridade){
      f->heap[i]->prioridade = novaPrioridade;
      construirheap(f);
      return 1;
      break;
    }
  }
  return 0;
}

PONT removerElemento(PFILA f){
  if(f->elementosNoHeap==0) return NULL;
  PONT ret = f->heap[0];
  int id = f->heap[0]->id;
  f->heap[0]=f->heap[f->elementosNoHeap-1];
  f->heap[f->elementosNoHeap-1]==NULL;
  f->heap[0]->posicao = 0;
  /*for(int i=0; i<f->elementosNoHeap-1;i++)
  {
    f->heap[i]->posicao--;
  }*/
  f->elementosNoHeap--;
  for(int j=0; j<f->elementosNoHeap+1; j++)
  {
    if(f->referencias[j]->id==id)
    {
      PONT par;
      par = f->referencias[j];
      f->referencias[j]=NULL;
      for(int k=j+1;k<f->elementosNoHeap+1; k++)
      {
        f->referencias[k-1] = f->referencias[k];
      }
    }
  }
  construirheap(f);
  return ret;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  if(id<0 || id>=MAX) return 0;
  for(int i=0;i<f->elementosNoHeap;i++){
    if(id==f->heap[i]->id)
    {
      resposta = &f->heap[i]->prioridade;
      return 1;
    }
  }
  return 0;
}
