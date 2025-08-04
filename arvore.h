#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

//arquivo ou pasta
typedef struct {
    char caminho[100];
    int tipo;
    int tamanho;
    Data modificacao;
} Item;

// No da arvore
typedef struct No *PtrNo;
struct No {
    Item dados;
    PtrNo esquerda;
    PtrNo direita;
};

typedef PtrNo Arvore;

// Inicia a arvore
void inicializar(Arvore *raiz) {
    *raiz = NULL;
}

// Cria a raiz
void criarRaiz(Arvore *raiz, Item novo) {
    Arvore novoNo = (PtrNo)malloc(sizeof(struct No));
    novoNo->dados = novo;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    *raiz = novoNo;
}

// Verifica se a arvore esta vazia
int estaVazia(Arvore raiz) {
    return (raiz == NULL);
}

// Insere na arvore
int inserir(Arvore *raiz, Item novo) {
    if (*raiz == NULL) {
        criarRaiz(raiz, novo);
        return 1;
    }

    int comp = strcmp(novo.caminho, (*raiz)->dados.caminho);

    if (comp < 0) {
        return inserir(&((*raiz)->esquerda), novo);
    } else if (comp > 0) {
        return inserir(&((*raiz)->direita), novo);
    }
    
    return 0;
}

// Busca item pelo caminho dado
PtrNo buscar(Arvore raiz, char *caminho) {
    if (raiz == NULL) return NULL;

    int comp = strcmp(caminho, raiz->dados.caminho);

    if (comp == 0) return raiz;
    else if (comp < 0) return buscar(raiz->esquerda, caminho);
    else return buscar(raiz->direita, caminho);
}

//tive um auxilio do sonnet pra arrumar a estrutura
// Lista os itens em ordem (ordenado pelo caminho)
void listarEmOrdem(Arvore raiz) {
    if (raiz != NULL) {
        listarEmOrdem(raiz->esquerda);

        char *tipoTexto;
        if (raiz->dados.tipo == 0) {
            tipoTexto = "Arquivo";
        } else {
            tipoTexto = "Diretorio";
        }

        printf("%s - %s - %d KB - %02d/%02d/%04d\n",
               raiz->dados.caminho,
               tipoTexto,
               raiz->dados.tamanho,
               raiz->dados.modificacao.dia,
               raiz->dados.modificacao.mes,
               raiz->dados.modificacao.ano);

        listarEmOrdem(raiz->direita);
    }
}

// Calcula tamanho de um diretorio
int somaTamanho(Arvore raiz, char *diretorio) {
    if (raiz == NULL) return 0;

    int total = 0;
    total += somaTamanho(raiz->esquerda, diretorio);

    if (raiz->dados.tipo == 0) {
        if (strstr(raiz->dados.caminho, diretorio) == raiz->dados.caminho) {
            total += raiz->dados.tamanho;
        }
    }

    total += somaTamanho(raiz->direita, diretorio);
    return total;
}

int tamanhoTotalDiretorio(Arvore raiz, char *diretorio) {
    PtrNo encontrado = buscar(raiz, diretorio);
    if (encontrado == NULL || encontrado->dados.tipo == 0) return -1;

    return somaTamanho(raiz, diretorio);
}

// Foi o sonnet que fez, pois nao entendi como se faz isso e quando tentei tive mt dificuldade
// Mostra os itens em formato de arvore com indentacao
void mostrarIndentadoAux(Arvore raiz) {
    if (raiz != NULL) {
        mostrarIndentadoAux(raiz->esquerda);

        int nivel = 0;
        for (int i = 0; raiz->dados.caminho[i] != '\0'; i++) {
            if (raiz->dados.caminho[i] == '/') nivel++;
        }

        for (int i = 0; i < nivel; i++) printf("  ");

        char *nome = strrchr(raiz->dados.caminho, '/');
        if (nome == NULL) nome = raiz->dados.caminho;
        else nome++;

        printf("%s", nome);
        if (raiz->dados.tipo == 1) printf("/");
        printf("\n");

        mostrarIndentadoAux(raiz->direita);
    }
}

void mostrarEstrutura(Arvore raiz) {
    mostrarIndentadoAux(raiz);
}

// Tive o auxilio do sonnet pq estava dando erro devido a formatacao nao consegui resolver
// Carrega dados de um arquivo de texto
int carregarArquivo(Arvore *raiz, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) return 0;

    char linha[200];
    int adicionados = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        Item novo;
        char tipoStr[20], dataStr[20];

        sscanf(linha, "%[^,],%[^,],%d,%s", novo.caminho, tipoStr, &novo.tamanho, dataStr);

        if (strcmp(tipoStr, "arquivo") == 0)
            novo.tipo = 0;
        else
            novo.tipo = 1;

        sscanf(dataStr, "%d/%d/%d", &novo.modificacao.dia, &novo.modificacao.mes, &novo.modificacao.ano);

        if (inserir(raiz, novo)) adicionados++;
    }

    fclose(arquivo);
    return adicionados;
}
