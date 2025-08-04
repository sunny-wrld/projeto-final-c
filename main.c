/* Felipe Murilo Ribeiro
Elia Carlos
Daniel Lewi */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

//  menu principal
void exibir_menu() {
    printf("\n=== SISTEMA DE GERENCIAMENTO DE ARQUIVOS ===\n");
    printf("1. Carregar dados do arquivo\n");
    printf("2. Inserir novo item\n");
    printf("3. Buscar item pelo caminho\n");
    printf("4. Listar todos os itens (em ordem)\n");
    printf("5. Calcular tamanho de um diretorio\n");
    printf("6. Mostrar estrutura da arvore (indentada)\n");
    printf("7. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Arvore arvore;
    inicializar(&arvore); // comeca com a arvore vazia por isso e O(1)

    int opcao;
    char caminho[100];
    Item novo_item;
    
    // usei o sonnet pra ajudar por algum motivo estava dando erro. ele adicionou o int na frente e tirou do if else
    // Tenta carregar os dados do arquivo padrao
    int itens_iniciais = carregarArquivo(&arvore, "dados_arquivos.txt");

    if (itens_iniciais > 0) {
        printf("Sistema iniciado com sucesso! %d itens carregados.\n", itens_iniciais);
    } else {
        printf("Nenhum dado foi carregado. Verifique o arquivo 'dados_arquivos.txt'.\n");
    }

    do {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();
        getchar();

        switch (opcao) {
            case 1:
                // Recarrega os dados do arquivo
                inicializar(&arvore); // limpa a arvore atual
                int itens_carregados = carregarArquivo(&arvore, "dados_arquivos.txt"); //-> Melhor caso: O(m * log n)

                if (itens_carregados > 0) {
                    printf("Arquivo carregado com sucesso! %d itens inseridos.\n", itens_carregados);
                } else {
                    printf("Erro ao carregar os dados. Verifique se o arquivo existe.\n");
                }
                break;

            case 2:
                // Cadastra novo item
                // Melhor caso: O(log n) pior O(n)
                printf("Digite o caminho completo: "); 
                fgets(novo_item.caminho, 100, stdin); 
                novo_item.caminho[strcspn(novo_item.caminho, "\n")] = 0;

                printf("Digite o tipo 0 para arquivo e 1 para diretorio: ");
                scanf("%d", &novo_item.tipo);

                printf("Digite o tamanho em KB: ");
                scanf("%d", &novo_item.tamanho);

                // usei a ia so pra ver como inseria a data
                printf("Digite a data de modificacao (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &novo_item.modificacao.dia,
                                  &novo_item.modificacao.mes,
                                  &novo_item.modificacao.ano);
                getchar();

                if (inserir(&arvore, novo_item)) {
                    printf("Item inserido com sucesso!\n");
                } else {
                    printf("Ja existe um item com esse caminho.\n");
                }
                break;

            case 3:
                // Busca pelo caminho a complexidade e melhor caso: O(log n) e na pior e  O(n)
                printf("Digite o caminho: ");
                fgets(caminho, 100, stdin);
                caminho[strcspn(caminho, "\n")] = 0;

                PtrNo encontrado = buscar(arvore, caminho);
                if (encontrado != NULL) {
                    char *tipoTexto;
                    if (encontrado->dados.tipo == 0) {
                        tipoTexto = "Arquivo";
                    } else {
                        tipoTexto = "Diretorio";
                    }
                    
                    printf("Item encontrado: %s - %s - %d KB - %02d/%02d/%04d\n",
                        encontrado->dados.caminho,
                        tipoTexto,
                        encontrado->dados.tamanho,
                        encontrado->dados.modificacao.dia,
                        encontrado->dados.modificacao.mes,
                        encontrado->dados.modificacao.ano);
                } else {
                    printf("Item nao encontrado.\n");
                }
                break;

            case 4:
                // Listar em ordem a complexidade e O(n)
                listarEmOrdem(arvore);
                break;

            case 5:
                // Tamanho total de um diretorio O(n)
                printf("Digite o caminho do diretorio: ");
                fgets(caminho, 100, stdin);
                caminho[strcspn(caminho, "\n")] = 0;

                // era pra esta na tad mas tava dando erro
                int total = tamanhoTotalDiretorio(arvore, caminho);
                if (total == -1) {
                    printf("Diretorio nao encontrado ou o caminho e de um arquivo.\n");
                } else {
                    printf("Tamanho total: %d KB\n", total);
                }
                break;

            case 6:
                // Foi o sonnet que fez essa funcao inteira, pois nao entendi como se faz isso e quando tentei tive mt dificuldade
                // Exibe estrutura da arvore O(n)
                mostrarEstrutura(arvore); 
                break;

            case 7:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 7);

    return 0;
}
