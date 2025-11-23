#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos
void cadastrarTerritorios(Territorio **mapa, int qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

int main() {
    int qtd, opcao;
    Territorio *mapa = NULL;

    srand(time(NULL)); // Seed para rand()

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar(); // Limpa o buffer

    // Alocação dinâmica
    mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(&mapa, qtd);
    exibirTerritorios(mapa, qtd);

    do {
        int atacante, defensor;
        printf("\n--- MENU DE ATAQUE ---\n");
        printf("0. Sair\n");
        printf("Escolha o território atacante (1 a %d): ", qtd);
        scanf("%d", &atacante);
        if (atacante == 0) break;

        printf("Escolha o território defensor (1 a %d): ", qtd);
        scanf("%d", &defensor);
        getchar(); // Limpa buffer

        if (atacante < 1 || atacante > qtd || defensor < 1 || defensor > qtd) {
            printf("Escolha inválida!\n");
            continue;
        }

        if (strcmp(mapa[atacante-1].cor, mapa[defensor-1].cor) == 0) {
            printf("Não pode atacar um território da mesma cor!\n");
            continue;
        }

        atacar(&mapa[atacante-1], &mapa[defensor-1]);
        exibirTerritorios(mapa, qtd);

    } while (1);

    liberarMemoria(mapa);
    return 0;
}

void cadastrarTerritorios(Territorio **mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: ");
        fgets((*mapa)[i].nome, 30, stdin);
        (*mapa)[i].nome[strcspn((*mapa)[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets((*mapa)[i].cor, 10, stdin);
        (*mapa)[i].cor[strcspn((*mapa)[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &(*mapa)[i].tropas);
        getchar();
    }
}

void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n--- Territórios Cadastrados ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n\n", mapa[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Ataque: %s (%s) [%d tropas] -> %s (%s) [%d tropas]\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ Ataque bem-sucedido!\n");
        defensor->tropas -= 1;
        atacante->tropas -= 1;
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf("❲X❳ Ataque falhou!\n");
        atacante->tropas -= 1;
    }

    if (defensor->tropas <= 0) {
        printf("%s foi conquistado!\n", defensor->nome);
        defensor->tropas = 0;
    }
    if (atacante->tropas <= 0) {
        printf("%s não tem mais tropas!\n", atacante->nome);
        atacante->tropas = 0;
    }
}

void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada. Tchau!\n");
}
