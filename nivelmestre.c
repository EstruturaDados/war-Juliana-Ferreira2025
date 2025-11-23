#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MISSOES 5
#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Protótipos
void cadastrarTerritorios(Territorio **mapa, int qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void atribuirMissao(char **missao, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho);
void liberarMemoria(Territorio *mapa, char *missao);

int main() {
    Territorio *mapa = NULL;
    char *missao = NULL;
    char *missoes[MAX_MISSOES] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor Vermelha",
        "Ter 10 tropas no total",
        "Conquistar 2 territorios com cor Azul",
        "Perder menos de 5 tropas"
    };
    int qtd, i, rodadas = 0;

    srand(time(NULL));

    printf("Quantos territórios (max %d)? ", MAX_TERRITORIOS);
    scanf("%d", &qtd);
    getchar();
    if (qtd > MAX_TERRITORIOS) qtd = MAX_TERRITORIOS;

    mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
    if (!mapa) {
        printf("Erro de alocação!\n");
        return 1;
    }

    cadastrarTerritorios(&mapa, qtd);
    exibirTerritorios(mapa, qtd);

    // Missão
    missao = (char *)malloc(100 * sizeof(char));
    atribuirMissao(&missao, missoes, MAX_MISSOES);
    printf("\n🧭 Sua missão: %s\n", missao);

    while (1) {
        int atacante, defensor;
        printf("\n--- RODADA %d ---\n", ++rodadas);
        printf("0. Sair | 1-%d Escolher territorios\n", qtd);

        printf("Território atacante: ");
        scanf("%d", &atacante);
        if (atacante == 0) break;

        printf("Território defensor: ");
        scanf("%d", &defensor);
        getchar();

        if (atacante < 1 || defensor < 1 || atacante > qtd || defensor > qtd ||
            strcmp(mapa[atacante-1].cor, mapa[defensor-1].cor) == 0) {
            printf("❌ Ataque inválido!\n");
            continue;
        }

        atacar(&mapa[atacante-1], &mapa[defensor-1]);
        exibirTerritorios(mapa, qtd);

        if (verificarMissao(missao, mapa, qtd)) {
            printf("\n🏆 MISSÃO CUMPRIDA! Você venceu!\n");
            break;
        }
    }

    liberarMemoria(mapa, missao);
    return 0;
}

void cadastrarTerritorios(Territorio **mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\nNome: ", i+1);
        fgets((*mapa)[i].nome, MAX_NOME, stdin);
        (*mapa)[i].nome[strcspn((*mapa)[i].nome, "\n")] = '\0';

        printf("Cor: ");
        fgets((*mapa)[i].cor, MAX_COR, stdin);
        (*mapa)[i].cor[strcspn((*mapa)[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &(*mapa)[i].tropas);
        getchar();
    }
}

void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | %s | %d tropas\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;
    printf("\n🎲 %s (%s) [%d] -> %s (%s) [%d]\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);
    printf("Dado A: %d | Dado D: %d\n", dadoA, dadoD);

    if (dadoA > dadoD && atacante->tropas > 1) {
        printf("✅ Vitória! %s conquistado.\n", defensor->nome);
        defensor->cor[0] = '\0';
        strcat(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("❌ Derrota! Atacante perde tropas.\n");
        atacante->tropas--;
    }
}

void atribuirMissao(char **missao, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    *missao = (char *)realloc(*missao, strlen(missoes[idx]) + 1);
    strcpy(*missao, missoes[idx]);
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    // Lógica simples: conquistar 3 territórios (mesma cor)
    int cont = 0;
    char corAlvo[MAX_COR] = "Azul"; // Exemplo fixo
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corAlvo) == 0) cont++;
    }
    if (strstr(missao, "3 territorios") && cont >= 3) return 1;

    return 0;
}

void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
    printf("\nMemória liberada. Até mais!\n");
}
