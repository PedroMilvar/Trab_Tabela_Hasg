#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "tab_hash.h"


int colisao = 0;
int iguais = 0;

int getIguais(){
  return iguais;
}
int getColisao(){
  return colisao;
}

TabelaHs *criar (int tam) {

    TabelaHs *tabelaHash; 
  int i;
 
    if((tabelaHash = (TabelaHs *) malloc(sizeof(TabelaHs))) == NULL ) {
        return NULL;
    }
    if((tabelaHash->tab = malloc(sizeof(Termo *) * tam)) == NULL) {
        return NULL;
    }

    for(i = 0; i < tam; i++ ) {
        tabelaHash->tab[i] = NULL;
    }

    tabelaHash->tamanho = tam;
  tabelaHash->qtde = 0;
    return tabelaHash;
}


int ht_hash(TabelaHs *tabTermos, char *pt) {
    unsigned long int hashval = 0;
  int i = 0;

    while(hashval < ULONG_MAX && i < strlen(pt) ) {
        hashval = hashval << 8;  
        hashval += pt[i];
        i++;
    }
    return hashval % tabTermos->tamanho;
}



void inserir(TabelaHs *tabTermos, char *ptChave, char *enValor) {
    int bin = 0, i, fim = 0;
    Termo *novoT = NULL;
    Termo *pos = NULL;


    bin = ht_hash(tabTermos,ptChave);
 

    pos = tabTermos->tab[bin]; 

  if(pos == NULL){
     novoT = criarNovoTermo(ptChave, enValor);
     tabTermos->tab[bin] = novoT;
     tabTermos->qtde++;
  }
  else {
       
        if(strcmp(ptChave, pos->port ) == 0 ) {
          iguais++;
              strcpy(pos->engl,enValor);
      }
        else {
    
          colisao++;
          i = bin+1;
          if (i >= tabTermos->tamanho) i = 0; 
          while(tabTermos->tab[i] != NULL){
              
             
              if(strcmp(ptChave, tabTermos->tab[i]->port ) == 0 ) {
                 iguais++;
                     strcpy(tabTermos->tab[i]->engl,enValor);
                 fim = 1;
                 break;
              }
            i++;
            if (i >= tabTermos->tamanho) i = 0; 
          }
        
          if (i < tabTermos->tamanho && fim == 0){
            novoT = criarNovoTermo(ptChave, enValor);
            tabTermos->tab[i] = novoT;
            tabTermos->qtde++;
           
          }
          else if (fim == 0) 
                 printf("\nChave encont/substituida em pos estendida (%d)",i);

      }
    }
}

char *buscar (TabelaHs *tabTermos, char *chv ) {
    int bin = 0,i;
    Termo *par;

    bin = ht_hash(tabTermos, chv);



    par = tabTermos->tab[bin];


    if(par == NULL)
      return NULL;
  else{
     i = bin;
     while(par!=NULL){
        if (strcmp(tabTermos->tab[i]->port, chv) == 0)
           return tabTermos->tab[i]->engl;
        i++;
        if (i >= tabTermos->tamanho) i = 0; 
        par = tabTermos->tab[i];
     }
  }
  return NULL;
}
