#include <stdio.h>  // Para usar printf e scanf
#include <stdlib.h> // Para malloc, calloc, free, rand
#include <string.h> // Para copiar e manipular textos
#include <time.h>   // Para gerar números aleatórios diferentes a cada execução

// Aqui definimos a estrutura de um território
typedef struct
{
    char nome[30]; // Nome do território, tipo "Brasil"
    char cor[10];  // Cor do exército que controla, tipo "vermelho"
    int tropas;    // Quantas tropas tem nesse território
} Territorio;

// Função que cadastra territórios
void cadastrarTerritorios(Territorio *mapa, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        // Lemos o nome, permitindo espaços
        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // Tiramos o Enter que vem do teclado

        // Lemos a cor do exército
        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0; // Tiramos o Enter

        // Lemos a quantidade de tropas
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Tiramos o Enter que ficou no buffer
    }
}

// Função que mostra todos os territórios na tela
void exibirTerritorios(Territorio *mapa, int n)
{
    printf("\n=== Estado Atual dos Territórios ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d - Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor)
{
    // Cada lado "rola um dado" de 1 a 6
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (Atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        // Atacante vence
        printf("%s vence o ataque!\n", atacante->nome);
        strcpy(defensor->cor, atacante->cor);    // Defensor muda de cor
        defensor->tropas = atacante->tropas / 2; // Defensor recebe metade das tropas do atacante
    }
    else
    {
        // Defensor vence
        printf("%s defende com sucesso!\n", defensor->nome);
        atacante->tropas -= 1; // Atacante perde uma tropa
        if (atacante->tropas < 0)
            atacante->tropas = 0; // Nunca fica negativo
    }
}

// Função que libera a memória que usamos para os territórios
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}

int main()
{
    srand(time(NULL)); // Faz os números aleatórios mudarem a cada execução

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);
    getchar(); // Tiramos o Enter que ficou no teclado

    // Alocamos dinamicamente a memória para os territórios
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (!mapa)
    {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastramos os territórios
    cadastrarTerritorios(mapa, n);

    // Mostramos todos os territórios para o jogador
    exibirTerritorios(mapa, n);

    // Exemplo simples de ataque
    int atk, def;
    printf("\nEscolha o território atacante (1 a %d): ", n);
    scanf("%d", &atk);
    printf("Escolha o território defensor (1 a %d): ", n);
    scanf("%d", &def);

    // Evita que o jogador ataque o próprio território
    if (atk != def)
    {
        atacar(&mapa[atk - 1], &mapa[def - 1]);
        exibirTerritorios(mapa, n); // Mostramos o resultado
    }
    else
    {
        printf("Atacante e defensor não podem ser o mesmo território.\n");
    }

    // Liberamos a memória antes de sair do programa
    liberarMemoria(mapa);

    return 0;
}
