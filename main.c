#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 100
#define TAM_DESCRICAO 100

typedef struct {
    char descricao[TAM_DESCRICAO];
    int concluida;
} Tarefa;

typedef struct {
    Tarefa tarefas[MAX_TAREFAS];
    int total;
} GerenciadorTarefas;

void adicionar_tarefa(GerenciadorTarefas *gerenciador) {
    if (gerenciador->total >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }
    printf("Digite a descrição da tarefa: ");
    getchar(); // Limpa o buffer do input
    fgets(gerenciador->tarefas[gerenciador->total].descricao, TAM_DESCRICAO, stdin);
    gerenciador->tarefas[gerenciador->total].descricao[strcspn(gerenciador->tarefas[gerenciador->total].descricao, "\n")] = 0; // Remove o \n
    gerenciador->tarefas[gerenciador->total].concluida = 0;
    gerenciador->total++;
    printf("Tarefa adicionada com sucesso!\n");
}

void listar_tarefas(GerenciadorTarefas *gerenciador) {
    if (gerenciador->total == 0) {
        printf("Nenhuma tarefa adicionada.\n");
        return;
    }

    for (int i = 0; i < gerenciador->total; i++) {
        printf("%d. %s - %s\n", i + 1, gerenciador->tarefas[i].descricao, gerenciador->tarefas[i].concluida ? "Concluída" : "Pendente");
    }
}

void concluir_tarefa(GerenciadorTarefas *gerenciador) {
    listar_tarefas(gerenciador);
    if (gerenciador->total == 0) return;

    int indice;
    printf("Digite o número da tarefa a ser concluída: ");
    scanf("%d", &indice);

    if (indice > 0 && indice <= gerenciador->total) {
        gerenciador->tarefas[indice - 1].concluida = 1;
        printf("Tarefa '%s' marcada como concluída.\n", gerenciador->tarefas[indice - 1].descricao);
    } else {
        printf("Índice inválido.\n");
    }
}

void remover_tarefa(GerenciadorTarefas *gerenciador) {
    listar_tarefas(gerenciador);
    if (gerenciador->total == 0) return;

    int indice;
    printf("Digite o número da tarefa a ser removida: ");
    scanf("%d", &indice);

    if (indice > 0 && indice <= gerenciador->total) {
        for (int i = indice - 1; i < gerenciador->total - 1; i++) {
            gerenciador->tarefas[i] = gerenciador->tarefas[i + 1];
        }
        gerenciador->total--;
        printf("Tarefa removida com sucesso.\n");
    } else {
        printf("Índice inválido.\n");
    }
}

int main() {
    GerenciadorTarefas gerenciador;
    gerenciador.total = 0;

    int opcao;

    do {
        printf("\nMenu de Gerenciamento de Tarefas\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Concluir Tarefa\n");
        printf("4. Remover Tarefa\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_tarefa(&gerenciador);
                break;
            case 2:
                listar_tarefas(&gerenciador);
                break;
            case 3:
                concluir_tarefa(&gerenciador);
                break;
            case 4:
                remover_tarefa(&gerenciador);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
