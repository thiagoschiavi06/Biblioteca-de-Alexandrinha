#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h"

int main() {
    const char *nomeDoArquivo = "dados_biblioteca.bin";
    int opcao;

    do {
        printf("\n=====================================\n");
        printf("        SISTEMA DA BIBLIOTECA        \n");
        printf("=====================================\n");
        printf("1. Cadastrar Novo Livro\n");
        printf("2. Listar Todos os Livros\n");
        printf("3. Excluir um Livro\n");
        printf("0. Sair do Programa\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char entradaId[50];
                int idDigitado = -1;
                
                limparBuffer(); 
                
                printf("\n--- CADASTRO DE LIVRO ---\n");
                
                do {
                    printf("ID do novo livro (apenas numeros positivos): ");
                    fgets(entradaId, sizeof(entradaId), stdin);
                    entradaId[strcspn(entradaId, "\n")] = '\0';
                    
                    if (strlen(entradaId) == 0) {
                        printf("[ERRO] O ID nao pode ser vazio!\n");
                        idDigitado = -1; // Mantém o loop
                    } 
                    else if (!idInt(entradaId)) {
                        printf("[ERRO] ID invalido! Nao use letras, espacos ou simbolos.\n");
                        idDigitado = -1;
                    } 
                    else {
                        idDigitado = atoi(entradaId);
                        if (idDigitado <= 0) {
                            printf("[ERRO] O ID nao pode ser negativo ou zero!\n");
                            idDigitado = -1;
                        }
                    }
                } while (idDigitado <= 0);
                
                // Verifica imediatamente se o ID já existe no arquivo binário
                if (verificarId(idDigitado, nomeDoArquivo)) {
                    printf("\n[ERRO] O ID %d ja existe no sistema! Cadastro cancelado.\n", idDigitado);
                } else {
                    Livro *meuLivro = criarLivro(idDigitado); 
                    
                    if (meuLivro != NULL) {
                        salvarLivro(meuLivro, nomeDoArquivo);
                        free(meuLivro);
                    }
                }
                break;
            }
            case 2:
                carregarLivros(nomeDoArquivo);
                break;

            case 3: {
                char entradaId[50];
                int idParaApagar = -1;
                
                limparBuffer();
                printf("\n--- EXCLUSAO DE LIVRO ---\n");
                
                do {
                    printf("Digite o ID do livro que deseja apagar: ");
                    fgets(entradaId, sizeof(entradaId), stdin);
                    entradaId[strcspn(entradaId, "\n")] = '\0';
                    
                    if (strlen(entradaId) == 0) {
                        printf("[ERRO] O ID nao pode ser vazio!\n");
                    } else if (!idInt(entradaId)) {
                        printf("[ERRO] ID invalido! Digite apenas numeros.\n");
                    } else {
                        idParaApagar = atoi(entradaId);
                        if (idParaApagar <= 0) {
                            printf("[ERRO] O ID nao pode ser negativo ou zero!\n");
                            idParaApagar = -1;
                        }
                    }
                } while (idParaApagar <= 0);
                
                excluirLivro(idParaApagar, nomeDoArquivo);
                break;
            }
                
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}