// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define NUM_TERRITORIOS 5
#define NUM_MISSOES 2
#define MAX_STRING 20 

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

struct territorio{
    char nome [50];
    char cordoexercito [20];
    int numerodetropas;
};

void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct territorio mapa [NUM_TERRITORIOS];
    int totaldeterritorios = 0;
    int opcao;

    do {
        printf("VAMOS CADASTRAR OS 5 TERRITORIOS INICIAIS DO NOSSO MUNDO!\n\n");
        printf(" --- Cadastro de Territórios ---\n\n");
        printf("1 - Cadastre um território:\n");
        printf("2 - Listar todos os territórios cadastrados\n");
        printf("0 - Sair\n");
        printf("-------------------------------------------------\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário.
        limparbufferentrada(); // Limpa o '\n' deixado pelo scanf.

        switch (opcao) {
            case 1:
                if (totaldeterritorios < NUM_TERRITORIOS) {
                    printf("Digite o nome do território: ");
                    fgets(mapa[totaldeterritorios].nome, MAX_STRING, stdin);
                    mapa[totaldeterritorios].nome[strcspn(mapa[totaldeterritorios].nome, "\n")] = 0; // Remove o '\n' do final.
                    
                    printf("Digite a cor do exército: ");
                    fgets(mapa[totaldeterritorios].cordoexercito, MAX_STRING, stdin);
                    mapa[totaldeterritorios].cordoexercito[strcspn(mapa[totaldeterritorios].cordoexercito, "\n")] = 0; // Remove o '\n' do final.
                    
                    printf("Digite o número de tropas: ");
                    scanf("%d", &mapa[totaldeterritorios].numerodetropas);
                    limparbufferentrada(); // Limpa o '\n' deixado pelo scanf.

                    totaldeterritorios++;
                    printf("Território cadastrado com sucesso!\n");
                } else {
                    printf("Número máximo de territórios cadastrados.\n");
                }
                break;
            case 2:
                printf("----- Lista de Territórios Cadastrados -----\n");
                for (int i = 0; i < totaldeterritorios; i++) {
                    printf("Território %d:\n", i + 1);
                    printf("Nome: %s\n", mapa[i].nome);
                    printf("Cor do Exército: %s\n", mapa[i].cordoexercito);
                    printf("Número de Tropas: %d\n", mapa[i].numerodetropas);
                    printf("---------------------------------------------\n");
                }
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);
    return 0;
}


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar
