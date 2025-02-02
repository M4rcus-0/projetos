#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#define max 100
#define delay 1
#define cor1 "\033[31m"
#define cor2 "\033[36m"
#define cor3 "\033[33m"
#define reset "\033[0m \e[m"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define sleep(seconds) Sleep((seconds) * 1000)
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#else
#error "Sistema operacional não suportado!"
#endif

typedef struct jogador
{
    char nome[max];
    int pontuacao;
} Jogador;

typedef struct jogo
{
    Jogador *jogador1;
    Jogador *jogador2;
} Jogo;

typedef struct data
{
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
} Data;

void comandos();
void converter(char objeto[], int opcao);
void sortear(char objeto[], int *vitorias, int *derrotas);
void tempo(double duracao);
void resultado(char objeto[], char robo[], int *vitorias, int *derrotas);

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(time(NULL));
    int opcao, vitorias = 0, derrotas = 0;
    char objeto[8];
    time_t inicio, final;
    printf("Pressione qualquer tecla para iniciar o jogo!\n");
    sleep(delay);
    getchar();
    printf("Inciando");
    for (int i = 0; i < 3; i++)
    {
        printf(" .");
        sleep(delay);
    }
    printf("\n");
    time(&inicio);
    while (true)
    {
        comandos();
        scanf("%d", &opcao);
        if (opcao == 0)
            break;
        else if (opcao != 1 && opcao != 2 && opcao != 3)
            continue;
        converter(objeto, opcao);
        sortear(objeto, &vitorias, &derrotas);
        printf("Vitórias: %d\n", vitorias);
        printf("Derrotas: %d\n", derrotas);
    }
    time(&final);
    double duracao = difftime(final, inicio);
    printf("\nPlacar final:\n");
    printf("Vitórias: %d\n", vitorias);
    printf("Derrotas: %d\n", derrotas);
    tempo(duracao);
    printf("Obrigado por jogar!\n");
    return 0;
}

void comandos()
{
    printf("Escolha uma das opções abaixo!\n");
    printf("\t[0] - Sair\t\n");
    sleep(delay);
    printf("\t[1] - Pedra\t\n");
    sleep(delay);
    printf("\t[2] - Papel\t\n");
    sleep(delay);
    printf("\t[3] - Tesoura\t\n");
    sleep(delay);
}

void converter(char vetor[], int opcao)
{
    switch (opcao)
    {
    case 1:
        strcpy(vetor, "pedra");
        break;
    case 2:
        strcpy(vetor, "papel");
        break;
    case 3:
        strcpy(vetor, "tesoura");
        break;
    }
}

void sortear(char objeto[], int *vitorias, int *derrotas)
{
    int opcao = rand() % 3 + 1;
    char robo[8];
    converter(robo, opcao);
    printf("Você escolheu %s\n", objeto);
    printf("Oponente escolheu %s\n", robo);
    resultado(objeto, robo, vitorias, derrotas);
}

void resultado(char objeto[], char robo[], int *vitorias, int *derrotas)
{
    if ((strcmp(objeto, "pedra") == 0 && strcmp(robo, "tesoura") == 0) || (strcmp(objeto, "papel") == 0 && strcmp(robo, "pedra") == 0) || (strcmp(objeto, "tesoura") == 0 && strcmp(robo, "papel") == 0))
    {
        printf("O resultado é " cor2 "vitória!" reset "\n");
        (*vitorias)++;
    }
    else if (strcmp(objeto, robo) == 0)
        printf("O resultado é " cor3 " empate!" reset "\n");
    else
    {
        printf("O resultado é " cor1 "derrota!" reset "\n");
        (*derrotas)++;
    }
}

void tempo(double duracao)
{
    int horas, minutos, segundos;

    horas = (int)(duracao / 3600);
    duracao = (int)duracao % 3600;

    minutos = (int)(duracao / 60);
    segundos = (int)duracao % 60;

    printf("Duração: %dh %dmin %ds\n", horas, minutos, segundos);
}
