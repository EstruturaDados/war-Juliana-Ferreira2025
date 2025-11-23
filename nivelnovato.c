#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Declaração de um vetor de structs para armazenar 5 territórios
    Territorio territorios[5];
    int i;

    printf("=== Cadastro de 5 Territórios ===\n\n");

    // Loop para preencher os dados dos territórios
    for (i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);

        // Lendo nome do território
        printf("Nome: ");
        scanf("%s", territorios[i].nome);
        // Limpa buffer (caso use fgets, cuidado com '\n')
        // fgets(territorios[i].nome, 30, stdin);

        // Lendo cor do exército
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Lendo número de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibindo dados cadastrados
    printf("=== Territórios Cadastrados ===\n\n");
    for (i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
