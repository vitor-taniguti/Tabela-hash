#include "tabela_hash.h"
#include <stdio.h>
#include <stdlib.h>

#define capacidade_inicial_tabela 2
#define capacidade_maxima_bucket 3

typedef struct{
    int id;
} Conteudo;

typedef struct{
    int contador;
    Conteudo* vetor[capacidade_maxima_bucket];
} Bucket;

typedef struct{
    int tamanho;
    Bucket** buckets;
} Tabela;

tabela criarEInicializarTabela(){
    Tabela* t = malloc(sizeof(Tabela));
    if (!t) return NULL;

    t->tamanho = capacidade_inicial_tabela;
    t->buckets = malloc(t->tamanho * sizeof(Bucket*));

    for (int i = 0; i < t->tamanho; i++){
        t->buckets[i] = malloc(sizeof(Bucket));
        t->buckets[i]->contador = 0;
    }

    return (tabela)t;
}

int getTamanhoTabela(tabela t){
    Tabela* tab = (Tabela*) t;
    return tab->tamanho;
}

void extenderTabela(tabela t){
    Tabela* tab = (Tabela*) t;
    
    int tamanho_antigo = tab->tamanho;
    Bucket** buckets_antigos = tab->buckets;

    tab->tamanho *= 2;
    tab->buckets = malloc(tab->tamanho * sizeof(Bucket*));

    for (int i = 0; i < tab->tamanho; i++){
        tab->buckets[i] = malloc(sizeof(Bucket));
        tab->buckets[i]->contador = 0;
    }

    for (int i = 0; i < tamanho_antigo; i++){
        for (int j = 0; j < buckets_antigos[i]->contador; j++){
            Conteudo* c = buckets_antigos[i]->vetor[j];
            int novo_indice = funcaoHash(c->id, tab->tamanho);
            
            tab->buckets[novo_indice]->vetor[tab->buckets[novo_indice]->contador] = c;
            tab->buckets[novo_indice]->contador++;
        }
        free(buckets_antigos[i]);
    }
    free(buckets_antigos);
}

int funcaoHash(int id, int tamanho){
    return id % tamanho;
}

conteudo criarConteudo(int id){
    Conteudo* novo = malloc(sizeof(Conteudo));
    novo->id = id;
    return (conteudo)novo;
}

void inserirConteudo(tabela t, conteudo c){
    Tabela* tab = (Tabela*) t;
    Conteudo* cont = (Conteudo*) c;
    int indice = funcaoHash(cont->id, tab->tamanho);

    if (tab->buckets[indice]->contador == capacidade_maxima_bucket){
        extenderTabela(tab);
        indice = funcaoHash(cont->id, tab->tamanho); 
    }

    tab->buckets[indice]->vetor[tab->buckets[indice]->contador] = cont;
    tab->buckets[indice]->contador += 1;
}

conteudo buscarConteudo(tabela t, conteudo c){
    Tabela* tab = (Tabela*) t;
    Conteudo* cont = (Conteudo*) c;
    int indice = funcaoHash(cont->id, tab->tamanho);

    for (int i = 0; i < tab->buckets[indice]->contador; i++){
        if (tab->buckets[indice]->vetor[i]->id == cont->id) {
            return (conteudo)tab->buckets[indice]->vetor[i];
        }
    }

    return NULL;
}

void removerConteudo(tabela t, conteudo c){
    Tabela* tab = (Tabela*) t;
    Conteudo* cont = (Conteudo*) c;
    int indice = funcaoHash(cont->id, tab->tamanho);
    Bucket* b = tab->buckets[indice];

    for (int i = 0; i < b->contador; i++){
        if (b->vetor[i]->id == cont->id){
            free(b->vetor[i]);

            for (int j = i; j < b->contador - 1; j++){
                b->vetor[j] = b->vetor[j + 1];
            }
            
            b->contador -= 1;
            break;
        }
    }
}

void liberarTabela(tabela t){
    Tabela* tab = (Tabela*) t;

    for (int i = 0; i < tab->tamanho; i++){
        for (int j = 0; j < tab->buckets[i]->contador; j++){
            free(tab->buckets[i]->vetor[j]);
        }
        free(tab->buckets[i]);
    }
    
    free(tab->buckets);
    free(tab);
}