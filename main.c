#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 10
#define TAMANHO_STRING 50

typedef struct {
    char marca[TAMANHO_STRING];
    char modelo[TAMANHO_STRING];
    int ano;
    int kilometragem;
    float preco;
} Carro;

int ler_dados_carros(Carro carros[], int max_carros);
void ordenar_carros_por_preco(Carro carros[], int n);
void exibir_carros(Carro carros[], int n);
void exibir_carros_por_marca(Carro carros[], int n, char marca[]);
void exibir_carros_por_preco(Carro carros[], int n, float min_preco, float max_preco);
int inserir_novo_carro(Carro carros[], int *n);
void remover_carros_por_kilometragem(Carro carros[], int *n, int max_km);

int main() {
    Carro carros[MAX_CARROS];
    int num_carros = ler_dados_carros(carros, MAX_CARROS);

    // Ordena os carros por preço após a leitura
    ordenar_carros_por_preco(carros, num_carros);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Exibir todos os registros\n");
        printf("2. Exibir registros de uma marca específica\n");
        printf("3. Exibir registros dentro de uma faixa de preço\n");
        printf("4. Inserir um novo registro de carro\n");
        printf("5. Remover registros com kilometragem superior a um valor\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        char marca[TAMANHO_STRING];
        float min_preco, max_preco;
        int max_km;

        switch(opcao) {
            case 1:
                exibir_carros(carros, num_carros);
                break;
            case 2:
                printf("Digite a marca: ");
                scanf("%s", marca);
                exibir_carros_por_marca(carros, num_carros, marca);
                break;
            case 3:
                printf("Digite o preco minimo e maximo: ");
                scanf("%f %f", &min_preco, &max_preco);
                exibir_carros_por_preco(carros, num_carros, min_preco, max_preco);
                break;
            case 4:
                if (inserir_novo_carro(carros, &num_carros)) {
                    printf("Carro inserido com sucesso.\n");
                } else {
                    printf("Erro ao inserir carro. Limite de carros atingido.\n");
                }
                break;
            case 5:
                printf("Digite a kilometragem maxima: ");
                scanf("%d", &max_km);
                remover_carros_por_kilometragem(carros, &num_carros, max_km);
                break;
            case 6:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 6);

    return 0;
}

// Le dados do arquivo 
int ler_dados_carros(Carro carros[], int max_carros) {
    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    int i = 0;
    while (i < max_carros && fscanf(arquivo, "%s %s %d %d %f",
           carros[i].marca, carros[i].modelo, &carros[i].ano,
           &carros[i].kilometragem, &carros[i].preco) == 5) {
        i++;
    }
    fclose(arquivo);
    return i;
}

// Ordena carros por preço
void ordenar_carros_por_preco(Carro carros[], int n) {
    Carro temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (carros[i].preco > carros[j].preco) {
                temp = carros[i];
                carros[i] = carros[j];
                carros[j] = temp;
            }
        }
    }
}

// Todos os carros
void exibir_carros(Carro carros[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Kilometragem: %d\n", carros[i].kilometragem);
        printf("Preco: %.2f\n\n", carros[i].preco);
    }
}

// Marca específica
void exibir_carros_por_marca(Carro carros[], int n, char marca[]) {
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(carros[i].marca, marca) == 0) {
            printf("Marca: %s\n", carros[i].marca);
            printf("Modelo: %s\n", carros[i].modelo);
            printf("Ano: %d\n", carros[i].ano);
            printf("Kilometragem: %d\n", carros[i].kilometragem);
            printf("Preco: %.2f\n\n", carros[i].preco);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum carro encontrado para a marca %s\n", marca);
    }
}

// Faixa de Preço
void exibir_carros_por_preco(Carro carros[], int n, float min_preco, float max_preco) {
    int encontrado = 0;
    for (int i = 0; i < n; i++) {
        if (carros[i].preco >= min_preco && carros[i].preco <= max_preco) {
            printf("Marca: %s\n", carros[i].marca);
            printf("Modelo: %s\n", carros[i].modelo);
            printf("Ano: %d\n", carros[i].ano);
            printf("Kilometragem: %d\n", carros[i].kilometragem);
            printf("Preco: %.2f\n\n", carros[i].preco);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum carro encontrado na faixa de preco R$%.2f - R$%.2f\n", min_preco, max_preco);
    }
}

// Insere novo carro no vetor
int inserir_novo_carro(Carro carros[], int *n) {
    if (*n >= MAX_CARROS) return 0;

    Carro novo_carro;
    printf("Digite a marca: ");
    scanf("%s", novo_carro.marca);
    printf("Digite o modelo: ");
    scanf("%s", novo_carro.modelo);
    printf("Digite o ano: ");
    scanf("%d", &novo_carro.ano);
    printf("Digite a kilometragem: ");
    scanf("%d", &novo_carro.kilometragem);
    printf("Digite o preco: ");
    scanf("%f", &novo_carro.preco);

    int pos = *n;
    while (pos > 0 && carros[pos - 1].preco > novo_carro.preco) {
        carros[pos] = carros[pos - 1];
        pos--;
    }
    carros[pos] = novo_carro;
    (*n)++;
    return 1;
}

// Km superior 
void remover_carros_por_kilometragem(Carro carros[], int *n, int max_km) {
    int i = 0;
    while (i < *n) {
        if (carros[i].kilometragem > max_km) {
            for (int j = i; j < *n - 1; j++) {
                carros[j] = carros[j + 1];
            }
            (*n)--;
        } else {
            i++;
        }
    }
}
