#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// Funcao para exibir o menu
void exibir_menu() {
    printf("\n=== Sistema de Gerenciamento de Arquivos ===\n");
    printf("1. Carregar dados iniciais (do arquivo)\n");
    printf("2. Inserir novo item\n");
    printf("3. Buscar item por caminho\n");
    printf("4. Listar todos os itens (em ordem)\n");
    printf("5. Calcular tamanho total de um diretorio\n");
    printf("6. Listar Arvore Indentada\n");
    printf("7. Sair\n");
    printf("Escolha uma opcaoo: ");
}

int main() {
    tree arvore;
    define(&arvore);
    int opcao;
    char caminho[100];
    elemento novo_item;
    
    // Carregar dados iniciais do arquivo, esse int foi o gpt que gerou, pelo q entendi ja que esta dando erro e provalvelmente vai retornar umm intiero se botar int na frente vai funcionar
    int itens_iniciais = carregar_dados_arquivo(&arvore, "dados_arquivos.txt");
    if (itens_iniciais == 0) {
        // Tenta buscar na pasta pai se nao encontrou na pasta atual
        itens_iniciais = carregar_dados_arquivo(&arvore, "../dados_arquivos.txt");
    }
    
    if (itens_iniciais > 0) {
        printf("Sistema iniciado! %d itens carregados do arquivo.\n", itens_iniciais);
    } else {
        printf("Aviso: Nenhum item foi carregado. Verifique se o arquivo 'dados_arquivos.txt' existe.\n");
    }

    do {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                // Recarregar do arquivo
                define(&arvore); // limpa a arvore
                 // Carregar dados iniciais do arquivo, esse int foi o gpt que gerou
                int itens_carregados = carregar_dados_arquivo(&arvore, "dados_arquivos.txt");
                if (itens_carregados == 0) {
                    // Tenta buscar na pasta pai se nao encontrou na pasta atual
                    itens_carregados = carregar_dados_arquivo(&arvore, "../dados_arquivos.txt");
                }
                
                if (itens_carregados > 0) {
                    printf("Dados iniciais carregados com sucesso! %d itens carregados.\n", itens_carregados);
                } else {
                    printf("Erro ao carregar dados ou arquivo vazio.\n");
                }
                break;
            case 2:
                // Inserir novo item
                printf("Digite o caminho completo: ");
                fgets(novo_item.caminho_completo, 100, stdin);
                novo_item.caminho_completo[strcspn(novo_item.caminho_completo, "\n")] = 0; // Remover nova linha

                printf("Digite o tipo (0 para arquivo, 1 para diretorio): ");
                scanf("%d", &novo_item.tipo);
                printf("Digite o tamanho em KB: ");
                scanf("%d", &novo_item.tamanho_kb);
                printf("Digite a data de modificacao (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &novo_item.data_modificacao.dia, &novo_item.data_modificacao.mes, &novo_item.data_modificacao.ano);
                getchar();
                getchar();

                if (inserir_item(&arvore, novo_item)) {
                    printf("Item inserido com sucesso.\n");
                } else {
                    printf("Erro: item com o mesmo caminho ja existe.\n");
                }
                break;
            case 3:
                // Buscar item por caminho
                printf("Digite o caminho do item: ");
                fgets(caminho, 100, stdin);
                caminho[strcspn(caminho, "\n")] = 0; // Remover nova linha

                ptrNodo resultado = buscar_item(arvore, caminho);
                if (resultado != NULL) {
                    printf("Item encontrado: %s - %s - %d KB - %02d/%02d/%04d\n",
                           resultado->info.caminho_completo,
                           resultado->info.tipo == 0 ? "Arquivo" : "Diretorio",
                           resultado->info.tamanho_kb,
                           resultado->info.data_modificacao.dia,
                           resultado->info.data_modificacao.mes,
                           resultado->info.data_modificacao.ano);
                } else {
                    printf("Item nao encontrado.\n");
                }
                break;
            case 4:
                // Listar todos os itens em ordem
                listar_todos_itens_em_ordem(arvore);
                break;
            case 5:
                // Calcular tamanho total de um diretorio
                printf("Digite o caminho do diretorio: ");
                fgets(caminho, 100, stdin);
                caminho[strcspn(caminho, "\n")] = 0; // Remover nova linha

                int tamanho_total = calcular_tamanho_total_diretorio(arvore, caminho);
                if (tamanho_total == -1) {
                    printf("Diretorio nao encontrado ou nao e um diretorio.\n");
                } else {
                    printf("Tamanho total do diretorio: %d KB\n", tamanho_total);
                }
                break;
            case 6:
                // Listar arvore indentada
                listar_arvore_indentada(arvore);
                break;
            case 7:
                // Sair
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
