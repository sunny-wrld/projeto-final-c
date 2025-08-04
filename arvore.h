#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char caminho_completo[100];
    int tipo;
    int tamanho_kb;
    Data data_modificacao;
} elemento;

typedef struct nodo *ptrNodo;
struct nodo {
    elemento info;
    ptrNodo esq;
    ptrNodo dir;
};

typedef ptrNodo tree;

void define(tree *t) {
    *t = NULL;
}

void criaRaiz(tree *t, elemento item) {
    tree no = (ptrNodo)malloc(sizeof(struct nodo));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    *t = no;
}

int vazia(tree t) {
    return (t == NULL);
}

void criarNodoDir(tree t, elemento item) {
    tree no = (ptrNodo)malloc(sizeof(struct nodo));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    t->dir = no;
}

void criarNodoEsq(tree t, elemento item) {
    tree no = (ptrNodo)malloc(sizeof(struct nodo));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    t->esq = no;
}

int inserir_item(tree *t, elemento item) {
    if (*t == NULL) {
        criaRaiz(t, item);
        return 1;
    }
    
    int comp = strcmp(item.caminho_completo, (*t)->info.caminho_completo);
    
    if (comp < 0) {
        if ((*t)->esq == NULL) {
            criarNodoEsq(*t, item);
            return 1;
        } else {
            return inserir_item(&((*t)->esq), item);
        }
    } else if (comp > 0) {
        if ((*t)->dir == NULL) {
            criarNodoDir(*t, item);
            return 1;
        } else {
            return inserir_item(&((*t)->dir), item);
        }
    }
    return 0; // ja existe
}

ptrNodo buscar_item(tree t, char *caminho) {
    if (t == NULL) return NULL;
    
    int comp = strcmp(caminho, t->info.caminho_completo);
    
    if (comp == 0) return t;
    if (comp < 0) return buscar_item(t->esq, caminho);
    return buscar_item(t->dir, caminho);
}

void listar_todos_itens_em_ordem(tree t) {
    if (t != NULL) {
        listar_todos_itens_em_ordem(t->esq);
        
        printf("%s - %s - %d KB - %02d/%02d/%04d\n", 
               t->info.caminho_completo,
               t->info.tipo == 0 ? "Arquivo" : "Diretorio",
               t->info.tamanho_kb,
               t->info.data_modificacao.dia,
               t->info.data_modificacao.mes,
               t->info.data_modificacao.ano);
        
        listar_todos_itens_em_ordem(t->dir);
    }
}

int calcula_tamanho_aux(tree t, char *dir) {
    if (t == NULL) return 0;
    
    int total = 0;
    
    total += calcula_tamanho_aux(t->esq, dir);
    
    if (t->info.tipo == 0) { // se e arquivo
        if (strstr(t->info.caminho_completo, dir) == t->info.caminho_completo) {
            total += t->info.tamanho_kb;
        }
    }
    
    total += calcula_tamanho_aux(t->dir, dir);
    
    return total;
}

int calcular_tamanho_total_diretorio(tree t, char *caminho_diretorio) {
    ptrNodo dir = buscar_item(t, caminho_diretorio);
    if (dir == NULL || dir->info.tipo == 0) {
        return -1;
    }
    
    return calcula_tamanho_aux(t, caminho_diretorio);
}

// Feita de maneira integral pelo gpt
void lista_indentada_aux(tree t) {
    if (t != NULL) {
        lista_indentada_aux(t->esq);
        
        // conta quantas barras tem para saber o nivel
        int nivel = 0;
        for (int i = 0; t->info.caminho_completo[i] != '\0'; i++) {
            if (t->info.caminho_completo[i] == '/') nivel++;
        }
        
        // imprime espaços
        for (int i = 0; i < nivel; i++) printf("  ");
        
        // pega so o nome final
        char *nome = strrchr(t->info.caminho_completo, '/');
        if (nome == NULL) nome = t->info.caminho_completo;
        else nome++;
        
        printf("%s", nome);
        if (t->info.tipo == 1) printf("/");
        printf("\n");
        
        lista_indentada_aux(t->dir);
    }
}

void listar_arvore_indentada(tree t) {
    lista_indentada_aux(t);
}

int carregar_dados_arquivo(tree *t, char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) return 0;
    
    char linha[200];
    int count = 0;
    
    while (fgets(linha, 200, f)) {
        elemento item;
        char tipo[20], data[20];
        
        sscanf(linha, "%[^,],%[^,],%d,%s", item.caminho_completo, tipo, &item.tamanho_kb, data);
        
        if (strcmp(tipo, "arquivo") == 0) {
            item.tipo = 0;
        } else {
            item.tipo = 1;
        }
        
        sscanf(data, "%d/%d/%d", &item.data_modificacao.dia, &item.data_modificacao.mes, &item.data_modificacao.ano);
        
        if (inserir_item(t, item)) count++;
    }
    
    fclose(f);
    return count;
}