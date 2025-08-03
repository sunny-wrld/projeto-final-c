# Sistema de Gerenciamento de Arquivos

Este projeto implementa um sistema de gerenciamento de arquivos em C usando uma árvore binária de busca (BST) para organizar e manipular informações sobre arquivos e diretórios.

## Funcionalidades

- **Carregar dados do arquivo**: Carrega informações iniciais de arquivos e diretórios a partir de um arquivo de texto
- **Inserir novo item**: Adiciona novos arquivos ou diretórios ao sistema
- **Buscar item por caminho**: Localiza arquivos ou diretórios específicos
- **Listar todos os itens**: Exibe todos os itens em ordem alfabética
- **Calcular tamanho de diretório**: Calcula o tamanho total de um diretório específico
- **Listar árvore indentada**: Mostra a estrutura hierárquica dos arquivos e diretórios

## Estrutura do Projeto

- `mai.c` - Arquivo principal com a interface do usuário e lógica do menu
- `arvore.h` - Implementação da árvore binária de busca e todas as operações
- `dados_arquivos.txt` - Arquivo de dados com informações iniciais dos arquivos

## Como Compilar e Executar

```bash
gcc mai.c -o sistema_arquivos
./sistema_arquivos
```

## Formato do Arquivo de Dados

O arquivo `dados_arquivos.txt` deve seguir o formato:
```
caminho_completo,tipo,tamanho_kb,data_modificacao
```

Exemplo:
```
a.txt,arquivo,10,01/01/2025
Documentos/,diretorio,0,04/01/2025
```

## Estrutura de Dados

O sistema utiliza uma árvore binária de busca onde cada nó contém:
- Caminho completo do arquivo/diretório
- Tipo (0 = arquivo, 1 = diretório)
- Tamanho em KB
- Data de modificação (DD/MM/AAAA)

## Autor

Projeto desenvolvido como trabalho final para a disciplina de Estruturas de Dados.
