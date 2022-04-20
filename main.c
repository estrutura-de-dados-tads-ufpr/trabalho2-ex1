#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pilha
{
    int row;
    int col;
    struct Pilha *next;
} Pilha;

// 0 - livre
// 1 - parede
// 2 - visitada
// 3 - beco

// colunas [x][0], [x][30] -> Paredes
// linhas  [0][x], [30][x] -> Paredes

Pilha *alocate_node()
{
    Pilha *node;
    node = (Pilha *)malloc(sizeof(Pilha));
    if (!node)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return node;
}

void insert_stack(Pilha **N, int row, int col)
{
    Pilha *new;
    Pilha *aux = *N;
    new = alocate_node();

    if (*N == NULL)
    {
        new->row = row;
        new->col = col;
        new->next = NULL;
        *N = new;
    }
    else
    {
        new->row = row;
        new->col = col;
        new->next = *N;
        *N = new;
    }
}

int *read_stack(Pilha **N)
{
    Pilha *aux = *N;
    int *array = malloc(2 * sizeof(int));
    array[0] = aux->row;
    array[1] = aux->col;
    return array;
}

int remove_stack(Pilha **N)
{
    printf("REMOVING STACK \n");
    Pilha *aux = *N;
    Pilha *tmp;
    if (*N == NULL)
    {
        printf("\n!!!!STACK UNDERFLOW!!!!!\n");
        return 1;
    }
    if (aux->next == NULL)
    {
        printf("\nNULLIFIED\n");
        *N = NULL;
        return 1;
    }
    else
    {
        tmp = aux;
        *N = aux->next;
        free(tmp);
        return 0;
    }
}

int **generateMap()
{
    // int map[30][30];
    int **map;
    map = malloc(sizeof(int *) * 30);
    for (int i = 0; i < 30; i++)
    {
        map[i] = malloc(sizeof(int *) * 30);
    }

    srand(time(NULL));
    // Gera paredes
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (i == 0 || i == 29)
            {
                map[i][j] = 1;
            }
            else if (j == 0 || j == 29)
            {
                map[i][j] = 1;
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }
    // Abre Saida
    map[28][29] = 0;
    // Randomiza Mapa
    for (int i = 0; i < 100; i++)
    {
        int row = (rand() % 28) + 1;
        int col = (rand() % 28) + 1;

        map[row][col] = 1;
    }
    return map;
}

void renderScreen(Pilha **pos, int **map)
{
    system("clear");
    int br = 0;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            int *now = read_stack(pos);
            if (br == 30)
            {
                br = 0;
                printf("\n");
            }
            if (now[0] == i && now[1] == j)
            {
                printf("O");
                map[i][j] = 2;
            }
            else if (map[i][j] == 0)
            {
                printf(" ");
            }
            else if (map[i][j] == 1)
            {
                printf("█");
            }
            else if (map[i][j] == 2)
            {
                printf(".");
            }
            else if (map[i][j] == 3)
            {
                printf("░");
            }

            br++;
        }
    }
}

int move(Pilha **pos, int **map)
{

    int row = read_stack(pos)[0];
    int col = read_stack(pos)[1];

    if (row == 28 && col == 29)
    {
        return 1;
    }
    else if (map[row][col + 1] == 0)
    {
        insert_stack(pos, row, col + 1);
    }
    else if (map[row][col - 1] == 0)
    {
        insert_stack(pos, row, col - 1);
    }
    else if (map[row + 1][col] == 0)
    {
        insert_stack(pos, row + 1, col);
    }
    else if (map[row - 1][col] == 0)
    {
        insert_stack(pos, row - 1, col);
    }
    else
    {

        int res = remove_stack(pos);
        map[row][col] = 3;
        if (res == 1)
        {
            pos = NULL;
            return 1;
        }
        else
        {
            row = read_stack(pos)[0];
            col = read_stack(pos)[1];
            map[row][col] = 0;
        }
    }
    return 0;
}

// 0 - livre
// 1 - parede
// 2 - visitada
// 3 - beco

// colunas [x][0], [x][30] -> Paredes
// linhas  [0][x], [30][x] -> Paredes

int main()
{

    Pilha *pos = NULL;
    int win = 0;
    int **map = generateMap();
    insert_stack(&pos, 2, 2);
    int won = 0;
    while (won == 0)
    {
        // int row = read_stack(&pos)[0];
        // int col = read_stack(&pos)[1];
        // printf("[%d][%d]\n", row, col);

        renderScreen(&pos, map);
        won = move(&pos, map);
        if (!pos)
        {
            printf("\n---------------------NO EXIT---------------------\n");
            won = 1;
            break;
        }
        printf("\n");
    }
}