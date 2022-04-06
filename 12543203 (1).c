/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   Turma 04 - Prof. Luciano Antonio Digiampietri                 **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   Guilherme Narciso Lee                   nUSP: 12543203        **/
/**                                                                 **/
/*********************************************************************/
// Apanhei pra pegar no início, mas dps foi.
#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}


bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}

bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){

	PONT atual = f->cabeca->prox;
    PONT atualnp = f->inicioNaoPref;
    PONT ref;
    if(id<0) return false;
    if(ehPreferencial==true)//Se for inserir um preferencial
    {
        if(atual == f->inicioNaoPref)//Se for o primeiro elemento preferencial
        {
            PONT ins = (PONT)malloc(sizeof(ELEMENTO));
            f->cabeca->prox = ins;
            ins->ant = f->cabeca;
            ins->prox = f->inicioNaoPref;
            f->inicioNaoPref->ant = ins;
            ins->ehPreferencial = ehPreferencial;
            ins->id = id;
            return true;
        }
        else//Caso não, lul
        {
            while((atual->prox!=f->cabeca)&&(atual->prox!=f->inicioNaoPref))
            {
                if(atual->id==id) return false;
                atual = atual->prox;
            }
            PONT ins = (PONT)malloc(sizeof(ELEMENTO));
            atual->prox = ins;
            ins->ant = atual;
            ins->prox = f->inicioNaoPref;
            f->inicioNaoPref->ant = ins;
            ins->ehPreferencial = ehPreferencial;
            ins->id = id;
            return true;
        }
    }
    else//Se for inserir um não-preferencial
    {
        if((f->inicioNaoPref == f->cabeca) && (atual == f->cabeca))//Se não tiver elementos
        {
            PONT ins = (PONT)malloc(sizeof(ELEMENTO));
            f->inicioNaoPref = ins;
            f->inicioNaoPref->ant = f->cabeca;
            f->inicioNaoPref->prox = f->cabeca;
            f->cabeca->prox = f->inicioNaoPref;
            f->cabeca->ant = f->inicioNaoPref;
            ins->ant = f->cabeca;
            ins->prox = f->cabeca;
            ins->ehPreferencial = ehPreferencial;
            ins->id = id;
            return true;
        }
        else if((f->inicioNaoPref == f->cabeca) && !(atual == f->inicioNaoPref))//Se já tiver preferenciais mas não não-preferenciais
        {
            while((atual->prox!=f->inicioNaoPref))
            {
                if(atual->id==id) return false;
                atual = atual->prox;
            }
            PONT ins = (PONT)malloc(sizeof(ELEMENTO));
            f->inicioNaoPref = ins;
            f->inicioNaoPref->ant = atual;
            atual->prox = f->inicioNaoPref;
            f->inicioNaoPref->prox = f->cabeca;
            f->cabeca->ant = f->inicioNaoPref;
            ins->ehPreferencial = ehPreferencial;
            ins->id = id;
            return true;
        }
        else if(!(f->inicioNaoPref == f->cabeca) && (atual == f->inicioNaoPref))//Se já tiver não-preferenciais mas não preferenciais
        {
            while((atualnp->prox!=f->cabeca))
            {
                if(atualnp->id==id) return false;
                atualnp = atualnp->prox;
            }
            PONT ins = (PONT)malloc(sizeof(ELEMENTO));
            atualnp->prox = ins;
            ins->ant = atualnp;
            ins->prox = f->cabeca;
            f->cabeca->ant = ins;
            ins->ehPreferencial = ehPreferencial;
            ins->id = id;
            return true;
        }
        else
        {
            while((atualnp->prox!=f->cabeca))
            {
                if(atualnp->id==id) return false;
                atualnp = atualnp->prox;
            }
            PONT ins = (PONT)malloc(sizeof(ELEMENTO));
            atualnp->prox = ins;
            ins->ant = atualnp;
            ins->prox = f->cabeca;
            f->cabeca->ant = ins;
            ins->ehPreferencial = ehPreferencial;
            ins->id = id;
            return true;
            }
    }
}

bool atenderPrimeiraDaFila(PFILA f, int* id){

    bool ep = false;
	PONT atual = f->cabeca->prox;
    PONT depois = f->cabeca->prox->prox;
    if(atual==f->cabeca) return false; //Não houver elementos
    id = &atual->id;
    if(f->cabeca->prox == f->inicioNaoPref)
    {
        f->inicioNaoPref = depois;
        f->inicioNaoPref->prox = depois->prox;
    }
    f->cabeca->prox = depois;
    depois->ant = f->cabeca;
    free(atual);
	return true;
}
bool desistirDaFila(PFILA f, int id){

	PONT atual = f->cabeca->prox;
    if(atual==f->cabeca || id<0) return false;
    while(atual!=f->cabeca)
    {
    PONT depois = atual->prox, antes = atual->ant;
        if(atual->id==id)
        {
            if(atual==f->inicioNaoPref)
            {
                f->inicioNaoPref = depois;
                f->inicioNaoPref->prox = depois->prox;
            }
            antes->prox = depois;
            depois->ant = antes;
            free(atual);
            return true;
        }
        atual = atual->prox;
    }
	return false;
}
