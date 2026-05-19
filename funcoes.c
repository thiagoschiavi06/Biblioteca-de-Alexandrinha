#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include <ctype.h>

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int verificarId(int id, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    
    if (arquivo == NULL) {
        return 0; 
    }

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

Livro* criarLivro(int id) {
    Livro *novoLivro = (Livro*) malloc(sizeof(Livro));
    if (novoLivro == NULL) return NULL;

    novoLivro->id = id; 

    do {
        printf("Titulo: ");
        fgets(novoLivro->titulo, sizeof(novoLivro->titulo), stdin);
        novoLivro->titulo[strcspn(novoLivro->titulo, "\n")] = '\0'; // Remove o "Enter" do final
        
        if (strlen(novoLivro->titulo) == 0) {
            printf("[ERRO] O titulo nao pode ser vazio!\n");
        }
    } while (strlen(novoLivro->titulo) == 0);

    do {
        printf("Autor: ");
        fgets(novoLivro->autor, sizeof(novoLivro->autor), stdin);
        novoLivro->autor[strcspn(novoLivro->autor, "\n")] = '\0';
        
        if (strlen(novoLivro->autor) == 0) {
            printf("[ERRO] O autor nao pode ser vazio!\n");
        }
    } while (strlen(novoLivro->autor) == 0);

    do {
        printf("Genero: ");
        fgets(novoLivro->genero, sizeof(novoLivro->genero), stdin);
        novoLivro->genero[strcspn(novoLivro->genero, "\n")] = '\0';
        
        if (strlen(novoLivro->genero) == 0) {
            printf("[ERRO] O genero nao pode ser vazio!\n");
        }
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
            printf("[ERRO] Entrada invalida! Digite apenas 1 para Sim ou 0 para Nao.\n");
            limparBuffer();
            novoLivro->disponivel = -1; 
        }
    } while (novoLivro->disponivel != 0 && novoLivro->disponivel != 1);

    limparBuffer(); 

    return novoLivro;
}

//append binario
void salvarLivro(Livro *livro, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "ab"); 
    //ap de append binary
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    
    fwrite(livro, sizeof(Livro), 1, arquivo);
    fclose(arquivo);
    printf("-> Livro salvo com sucesso no arquivo '%s'!\n", nomeArquivo);
}

void carregarLivros(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); 
    //rb de read binary
    if (arquivo == NULL) {
        printf("\nNenhum dado encontrado. O arquivo ainda nao existe ou esta vazio.\n");
        return;
    }

    Livro livroTemp; 
    printf("\n=== LIVROS CADASTRADOS NO SISTEMA ===\n");
    
    int encontrou = 0;
    while (fread(&livroTemp, sizeof(Livro), 1, arquivo) == 1) {
        encontrou = 1;
        printf("ID: %d | Titulo: %s | Autor: %s | Ano: %d | Disponibilidade: %s\n", 
               livroTemp.id, 
               livroTemp.titulo, 
               livroTemp.autor, 
               livroTemp.ano,
               livroTemp.disponivel == 1 ? "Sim" : "Nao");
    }
    
    if (!encontrou) {
        printf("O arquivo existe, mas nao ha livros cadastrados.\n");
    }
    
    printf("=====================================\n");
    fclose(arquivo);
}

int idInt(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1; 
}

void excluirLivro(int id, const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb");
    
    if (arquivoOriginal == NULL) {
        printf("\n[ERRO] Nenhum dado encontrado. O arquivo ainda nao existe.\n");
        return;
    }

    FILE *arquivoTemp = fopen("temp.bin", "wb");
    if (arquivoTemp == NULL) {
        printf("\n[ERRO] Nao foi possivel criar o arquivo temporario!\n");
        fclose(arquivoOriginal);
        return;
    }

    Livro livroTemp;
    int encontrou = 0;

    while (fread(&livroTemp, sizeof(Livro), 1, arquivoOriginal) == 1) {
        if (livroTemp.id != id) {
            fwrite(&livroTemp, sizeof(Livro), 1, arquivoTemp);
        } else {
            encontrou = 1;
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    if (encontrou) {
        remove(nomeArquivo); 
        rename("temp.bin", nomeArquivo); 
        printf("\n-> Sucesso: Livro com ID %d foi excluido do sistema!\n", id);
    } else {
        remove("temp.bin"); 
        printf("\n-> Aviso: Nenhum livro com o ID %d foi encontrado.\n", id);
    }
}