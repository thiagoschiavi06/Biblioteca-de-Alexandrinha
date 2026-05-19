#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
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
        printf("3. Buscar Livro\n");
        printf("4. Editar Livro Existente\n");
        printf("5. Excluir um Livro\n");
        printf("0. Sair do Programa\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1; 
        }

        switch (opcao) {
            case 1: {
                limparBuffer();
                printf("\n--- CADASTRO DE LIVRO ---\n");
                int idDigitado = pedirIdValidado("ID do novo livro: ");
                
                if (verificarIdExiste(idDigitado, nomeDoArquivo)) {
                    printf("\n[ERRO] O ID %d ja existe! Cadastro cancelado.\n", idDigitado);
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
                limparBuffer();
                printf("\n--- BUSCAR LIVRO ---\n");
                printf("1. Buscar por ID\n");
                printf("2. Buscar por Titulo\n");
                printf("3. Buscar por Autor\n");
                printf("4. Buscar por Genero\n");
                printf("Escolha o tipo de busca: ");

                int tipoBusca;
                if (scanf("%d", &tipoBusca) != 1) {
                    limparBuffer();
                    tipoBusca = -1;
                }

                if (tipoBusca == 1) {
                    limparBuffer();
                    int idBusca = pedirIdValidado("Digite o ID para busca: ");
                    if (!buscarLivroPorId(idBusca, nomeDoArquivo)) {
                        printf("\n[ERRO] Livro com ID %d nao encontrado.\n", idBusca);
                    }
                } else if (tipoBusca >= 2 && tipoBusca <= 4) {
                    limparBuffer();
                    char termo[100];
                    printf("Digite o termo da busca: ");
                    fgets(termo, sizeof(termo), stdin);
                    termo[strcspn(termo, "\n")] = '\0';

                    if (strlen(termo) > 0) {

                        buscarLivroPorTermo(termo, tipoBusca - 1, nomeDoArquivo); 
                    } else {
                        printf("\n[ERRO] O termo de busca nao pode ser vazio.\n");
                    }
                } else {
                    printf("\n[ERRO] Opcao de busca invalida!\n");
                }
                break;
            }
            
            case 4: {
                limparBuffer();
                printf("\n--- EDITAR LIVRO ---\n");
                int idEditar = pedirIdValidado("Digite o ID do livro a ser editado: ");
                if (verificarIdExiste(idEditar, nomeDoArquivo)) {
                    editarLivro(idEditar, nomeDoArquivo);
                } else {
                    printf("\n[ERRO] Livro com ID %d nao encontrado.\n", idEditar);
                }
                break;
            }
            
            case 5: {
                limparBuffer();
                printf("\n--- EXCLUSAO DE LIVRO ---\n");
                printf("Como deseja encontrar o livro para apagar?\n");
                printf("1. Digitar o ID direto\n");
                printf("2. Buscar lista por Titulo\n");
                printf("3. Buscar lista por Autor\n");
                printf("4. Buscar lista por Genero\n");
                printf("Escolha uma opcao: ");

                int tipoBusca;
                if (scanf("%d", &tipoBusca) != 1) {
                    limparBuffer();
                    tipoBusca = -1;
                }

                int idParaApagar = -1;

                if (tipoBusca >= 2 && tipoBusca <= 4) {
                    limparBuffer();
                    char termo[100];
                    printf("Digite o termo da busca: ");
                    fgets(termo, sizeof(termo), stdin);
                    termo[strcspn(termo, "\n")] = '\0';

                    if (strlen(termo) > 0) {
                        if (buscarLivroPorTermo(termo, tipoBusca - 1, nomeDoArquivo)) {
                            printf("\nCom base na lista acima, ");
                            idParaApagar = pedirIdValidado("digite o ID do livro que deseja apagar: ");
                        } else {
                            idParaApagar = -1; 
                        }
                    } else {
                        printf("\n[ERRO] O termo de busca nao pode ser vazio.\n");
                    }
                } 
                else if (tipoBusca == 1) {
                    limparBuffer();
                    idParaApagar = pedirIdValidado("Digite o ID do livro que deseja apagar: ");
                } 
                else {
                    printf("\n[ERRO] Opcao invalida!\n");
                }

                if (idParaApagar > 0) {
                    if (buscarLivroPorId(idParaApagar, nomeDoArquivo)) {
                        char confirmacao;
                        printf("\nTem certeza absoluta que deseja EXCLUIR este livro? (s/n): ");
                        scanf(" %c", &confirmacao);
                        
                        if (confirmacao == 's' || confirmacao == 'S') {
                            excluirLivro(idParaApagar, nomeDoArquivo);
                        } else {
                            printf("-> Exclusao cancelada pelo usuario.\n");
                        }
                    } else {
                        printf("\n[ERRO] Livro com ID %d nao encontrado.\n", idParaApagar);
                    }
                }
                break;
            }
                
            case 0:
                printf("\nSaindo do sistema... Ate mais!\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu...");
            if (opcao != 1 && opcao != 3 && opcao != 4) limparBuffer(); 
            getchar(); 
        }

    } while (opcao != 0);

    return 0;
}