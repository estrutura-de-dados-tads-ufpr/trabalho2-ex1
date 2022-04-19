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
        new->next = NULL;
        aux->next = new;
    }
}

int *read_stack(Pilha **N)
{
    Pilha *aux = *N;
    Pilha *prev;
    while (aux->next)
    {
        prev = aux;
        aux = aux->next;
    }
    int *array = malloc(2 * sizeof(int));
    array[0] = aux->row;
    array[1] = aux->col;
    return array;
}

void remove_stack(Pilha **N)
{
    Pilha *aux = *N;
    Pilha *prev;
    while (aux->next)
    {
        prev = aux;
        aux = aux->next;
    }
    prev->next = NULL;
}

int main()
{

    Pilha *pos = NULL;
    int win = 0;
    int map[30][30];
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
    map[28][29] = 0;
    for (int i = 0; i < 100; i++)
    {
        int row = (rand() % 28) + 1;
        int col = (rand() % 28) + 1;
        map[row][col] = 1;
    }

    insert_stack(&pos, 2, 2);
    for (int c = 0; c < 2; c++)
    {
        system("clear");
        int br = 0;
        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                int *now = read_stack(&pos);
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

                // printf("%s", " ");
                br++;
            }
        }
        insert_stack(&pos, 2, 3);
        printf("\n");
    }
}