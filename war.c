//Aluno: Carlos Fillipe Soares de Sousa
//Matrícula: 202501072909
//OBS: Tive dificuldades em finalizar o projeto. Consegui fazer até o nível aventureiro por conta propria. 
//O nível mestre eu tive que recorer a revisão do CHATGPT.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define MAX_STRING 50


struct territorio {
    char nome[MAX_STRING];
    char cordoexercito[MAX_STRING];
    int numerodetropas;
};

struct batalha {
    int atacante[3];
    int defesa[2];
};


void limparBufferEntrada(void);
void cadastrarTerritorio(struct territorio *t);
void exibirMapa(const struct territorio *mapa, int tamanho);
void ordenar(int *v, int tamanho);
void realizarBatalha(struct territorio *atacante, struct territorio *defensor);
void exibirMissao(void);


void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarTerritorio(struct territorio *t) {
    printf("\nNome do Território: ");
    fgets(t->nome, MAX_STRING, stdin);
    t->nome[strcspn(t->nome, "\n")] = 0;

    printf("Cor do Exército: ");
    fgets(t->cordoexercito, MAX_STRING, stdin);
    t->cordoexercito[strcspn(t->cordoexercito, "\n")] = 0;

    printf("Número de Tropas: ");
    scanf("%d", &t->numerodetropas);
    limparBufferEntrada();
}

void exibirMapa(const struct territorio *mapa, int tamanho) {
    printf("\n*** MAPA ATUAL ***\n");
    printf("--------------------------------------------------\n");
    printf("| %-15s | %-15s | %-10s |\n", "Território", "Cor do Exército", "Nº Tropas");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("| %-15s | %-15s | %-10d |\n",
               mapa[i].nome, mapa[i].cordoexercito, mapa[i].numerodetropas);
    }
    printf("--------------------------------------------------\n");
}

void ordenar(int *v, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (v[j] > v[i]) {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

void realizarBatalha(struct territorio *atacante, struct territorio *defensor) {
    struct batalha b;
    int numDadosAtaque = atacante->numerodetropas > 3 ? 3 : atacante->numerodetropas;
    int numDadosDefesa = defensor->numerodetropas > 2 ? 2 : defensor->numerodetropas;

    // Gerar números aleatórios de 1 a 6
    for (int i = 0; i < numDadosAtaque; i++) b.atacante[i] = rand() % 6 + 1;
    for (int i = 0; i < numDadosDefesa; i++) b.defesa[i] = rand() % 6 + 1;

    ordenar(b.atacante, numDadosAtaque);
    ordenar(b.defesa, numDadosDefesa);

    printf("\n🪖 %s (ATAQUE) vs %s (DEFESA)\n", atacante->nome, defensor->nome);
    printf("Dados do ataque: ");
    for (int i = 0; i < numDadosAtaque; i++) printf("[%d] ", b.atacante[i]);
    printf("\nDados da defesa: ");
    for (int i = 0; i < numDadosDefesa; i++) printf("[%d] ", b.defesa[i]);
    printf("\n");

    int comparacoes = (numDadosAtaque < numDadosDefesa) ? numDadosAtaque : numDadosDefesa;
    for (int i = 0; i < comparacoes; i++) {
        if (b.atacante[i] > b.defesa[i]) {
            defensor->numerodetropas--;
            printf("✅ Ataque venceu o duelo %d! %s perde 1 tropa.\n", i + 1, defensor->nome);
        } else {
            atacante->numerodetropas--;
            printf("❌ Defesa venceu o duelo %d! %s perde 1 tropa.\n", i + 1, atacante->nome);
        }
    }

    printf("\nResultado final: %s = %d tropas | %s = %d tropas\n\n",
           atacante->nome, atacante->numerodetropas,
           defensor->nome, defensor->numerodetropas);
}

void exibirMissao(void) {
    printf("\n--- SUA MISSÃO (Exército Azul) ---\n");
    printf("Destruir o Exército Verde!\n");
}

// ---------------------- FUNÇÃO PRINCIPAL ----------------------
int main() {
    srand(time(NULL));

    struct territorio *mapa = calloc(NUM_TERRITORIOS, sizeof(struct territorio));
    if (!mapa) {
        printf("Erro: Falha ao alocar memória.\n");
        return 1;
    }

    printf("*** CADASTRO DOS TERRITÓRIOS ***\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nCadastrando Território %d:\n", i + 1);
        cadastrarTerritorio(&mapa[i]);
    }

    int acao;
    do {
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Ver Missão\n");
        printf("3 - Ver Mapa\n");
        printf("0 - Sair\n");
        printf("Escolha sua ação: ");
        scanf("%d", &acao);
        limparBufferEntrada();

        switch (acao) {
            case 1: {
                int iAtacante, iDefensor;
                printf("\nEscolha o território atacante (1-%d): ", NUM_TERRITORIOS);
                scanf("%d", &iAtacante);
                limparBufferEntrada();
                printf("Escolha o território defensor (1-%d): ", NUM_TERRITORIOS);
                scanf("%d", &iDefensor);
                limparBufferEntrada();

                if (iAtacante < 1 || iAtacante > NUM_TERRITORIOS ||
                    iDefensor < 1 || iDefensor > NUM_TERRITORIOS ||
                    iAtacante == iDefensor) {
                    printf("⚠️ Escolha inválida.\n");
                    break;
                }

                realizarBatalha(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
                break;
            }
            case 2:
                exibirMissao();
                break;
            case 3:
                exibirMapa(mapa, NUM_TERRITORIOS);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Ação inválida.\n");
                break;
        }
    } while (acao != 0);

    free(mapa);
    return 0;
}
