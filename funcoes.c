#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ehApenasNumero(const char *str) {
    int tamanho = strlen(str);
    for (int i = 0; i < tamanho; i++) {
        if (!isdigit(str[i])) {
            return 0; // Encontrou um caractere não numérico
        }
    }
    return 1; 
}

// Função auxiliar que centraliza a validação de IDs
int pedirIdValidado(const char *mensagem) {
    char entradaId[50];
    int idDigitado = -1;
    do {
        printf("%s", mensagem);
        fgets(entradaId, sizeof(entradaId), stdin);
        entradaId[strcspn(entradaId, "\n")] = '\0';
        
        if (strlen(entradaId) == 0) {
            printf("[ERRO] O ID nao pode ser vazio!\n");
        } else if (!ehApenasNumero(entradaId)) {
            printf("[ERRO] ID invalido! Digite apenas numeros.\n");
        } else {
            idDigitado = atoi(entradaId);
            if (idDigitado <= 0) {
                printf("[ERRO] O ID nao pode ser negativo ou zero!\n");
                idDigitado = -1;
            }
        }
    } while (idDigitado <= 0);
    return idDigitado;
}

// Retorna 1 se o ID existir no arquivo binário, 0 caso contrário
int verificarIdExiste(int id, const char *nomeArquivo) {
    // "rb" = read binary (leitura de arquivo binário)
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) return 0; 

    Livro livroTemp;
    while (fread(&livroTemp, sizeof(Livro), 1, arquivo) == 1) {
        if (livroTemp.id == id) {
            fclose(arquivo);
            return 1; 
        }
    }
    fclose(arquivo);
    return 0; 
}

// Aloca e preenche os dados de um novo livro com validações
Livro* criarLivro(int id) {
    Livro *novoLivro = (Livro*) malloc(sizeof(Livro));
    if (novoLivro == NULL) return NULL;

    novoLivro->id = id; 

    do {
        printf("Titulo: ");
        fgets(novoLivro->titulo, sizeof(novoLivro->titulo), stdin);
        novoLivro->titulo[strcspn(novoLivro->titulo, "\n")] = '\0'; 
        if (strlen(novoLivro->titulo) == 0) printf("[ERRO] Campo obrigatorio!\n");
    } while (strlen(novoLivro->titulo) == 0);

    do {
        printf("Autor: ");
        fgets(novoLivro->autor, sizeof(novoLivro->autor), stdin);
        novoLivro->autor[strcspn(novoLivro->autor, "\n")] = '\0';
        if (strlen(novoLivro->autor) == 0) printf("[ERRO] Campo obrigatorio!\n");
    } while (strlen(novoLivro->autor) == 0);

    do {
        printf("Genero: ");
        fgets(novoLivro->genero, sizeof(novoLivro->genero), stdin);
        novoLivro->genero[strcspn(novoLivro->genero, "\n")] = '\0';
        if (strlen(novoLivro->genero) == 0) printf("[ERRO] Campo obrigatorio!\n");
    } while (strlen(novoLivro->genero) == 0);

    do {
        printf("Ano de publicacao (positivo): ");
        if (scanf("%d", &novoLivro->ano) != 1 || novoLivro->ano <= 0) {
            printf("[ERRO] Ano invalido! Digite um numero maior que 0.\n");
            limparBuffer(); 
            novoLivro->ano = -1; 
        }
    } while (novoLivro->ano <= 0);

    do {
        printf("Disponivel (1 = Sim / 0 = Nao): ");
        if (scanf("%d", &novoLivro->disponivel) != 1 || (novoLivro->disponivel != 0 && novoLivro->disponivel != 1)) {
            printf("[ERRO] Entrada invalida!\n");
            limparBuffer();
            novoLivro->disponivel = -1; 
        }
    } while (novoLivro->disponivel != 0 && novoLivro->disponivel != 1);

    limparBuffer(); 
    return novoLivro;
}

void salvarLivro(Livro *livro, const char *nomeArquivo) {
    // "ab" = append binary (adiciona novos blocos sem apagar os antigos)
    FILE *arquivo = fopen(nomeArquivo, "ab"); 
    if (arquivo == NULL) {
        printf("[ERRO] Falha ao abrir arquivo para salvar!\n");
        return;
    }
    fwrite(livro, sizeof(Livro), 1, arquivo);
    fclose(arquivo);
    printf("-> Sucesso: Livro gravado no disco!\n");
}

// Lista todos os registros
void carregarLivros(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); 
    if (arquivo == NULL) {
        printf("\nO catalogo esta vazio ou arquivo inexistente.\n");
        return;
    }

    Livro livroTemp; 
    printf("\n=== LIVROS CADASTRADOS ===\n");
    int encontrou = 0;
    while (fread(&livroTemp, sizeof(Livro), 1, arquivo) == 1) {
        encontrou = 1;
        printf("ID: %d | Titulo: %s | Autor: %s | Genero: %s | Ano: %d | Disponivel: %s\n", 
               livroTemp.id, livroTemp.titulo, livroTemp.autor, livroTemp.genero, livroTemp.ano,
               livroTemp.disponivel == 1 ? "Sim" : "Nao");
    }
    if (!encontrou) printf("Nenhum livro registrado.\n");
    printf("==========================\n");
    fclose(arquivo);
}

int buscarLivroPorId(int id, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) return 0;

    Livro livroTemp;
    while (fread(&livroTemp, sizeof(Livro), 1, arquivo) == 1) {
        if (livroTemp.id == id) {
            printf("\n--- LIVRO ENCONTRADO ---\n");
            printf("Titulo: %s\nAutor: %s\nGenero: %s\nAno: %d\nDisponibilidade: %s\n",
                   livroTemp.titulo, livroTemp.autor, livroTemp.genero, livroTemp.ano,
                   livroTemp.disponivel == 1 ? "Sim" : "Nao");
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

void editarLivro(int id, const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb");
    if (arquivoOriginal == NULL) return;

    FILE *arquivoTemp = fopen("temp_livros.bin", "wb");
    if (arquivoTemp == NULL) {
        fclose(arquivoOriginal);
        return;
    }

    Livro livroTemp;
    while (fread(&livroTemp, sizeof(Livro), 1, arquivoOriginal) == 1) {
        if (livroTemp.id == id) {
            printf("\n--- ATUALIZANDO DADOS DO LIVRO '%s' ---\n", livroTemp.titulo);
            Livro *livroEditado = criarLivro(id);
            if (livroEditado != NULL) {
                fwrite(livroEditado, sizeof(Livro), 1, arquivoTemp);
                free(livroEditado);
            }
        } else {
            fwrite(&livroTemp, sizeof(Livro), 1, arquivoTemp);
        }
    }
    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    remove(nomeArquivo);
    rename("temp_livros.bin", nomeArquivo);
    printf("-> Sucesso: Livro atualizado!\n");
}

void excluirLivro(int id, const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb");
    if (arquivoOriginal == NULL) return;

    FILE *arquivoTemp = fopen("temp_livros.bin", "wb");
    if (arquivoTemp == NULL) {
        fclose(arquivoOriginal);
        return;
    }

    Livro livroTemp;
    while (fread(&livroTemp, sizeof(Livro), 1, arquivoOriginal) == 1) {
        if (livroTemp.id != id) {
            fwrite(&livroTemp, sizeof(Livro), 1, arquivoTemp);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    
    remove(nomeArquivo); 
    rename("temp_livros.bin", nomeArquivo); 
    printf("-> Sucesso: Livro com ID %d foi excluido!\n", id);
}


void paraMinusculo(char *str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

int buscarLivroPorTermo(const char *termo, int categoria, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("\n[ERRO] Arquivo nao encontrado ou vazio.\n");
        return 0; 
    }

    Livro livroTemp;
    int encontrou = 0;
    
    char termoBusca[100];
    strcpy(termoBusca, termo);
    paraMinusculo(termoBusca);

    printf("\n=== RESULTADOS DA BUSCA ===\n");
    
    while (fread(&livroTemp, sizeof(Livro), 1, arquivo) == 1) {
        char textoComparacao[100];

        if (categoria == 1) strcpy(textoComparacao, livroTemp.titulo);
        else if (categoria == 2) strcpy(textoComparacao, livroTemp.autor);
        else if (categoria == 3) strcpy(textoComparacao, livroTemp.genero);

        paraMinusculo(textoComparacao);

        if (strstr(textoComparacao, termoBusca) != NULL) {
            encontrou = 1;
            printf("ID: %d | Titulo: %s | Autor: %s | Genero: %s | Ano: %d | Disponivel: %s\n",
                   livroTemp.id, livroTemp.titulo, livroTemp.autor, livroTemp.genero, livroTemp.ano,
                   livroTemp.disponivel == 1 ? "Sim" : "Nao");
        }
    }

    if (!encontrou) {
        printf("Nenhum livro encontrado contendo: '%s'\n", termo);
    }
    printf("===========================\n");
    fclose(arquivo);
    
    return encontrou; 
}