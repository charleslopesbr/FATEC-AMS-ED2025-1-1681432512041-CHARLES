#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero;
    char cliente[50];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido* proximo;
} Pedido;

Pedido* criarLista() {
    return NULL;
}

Pedido* inserirPedido(Pedido* lista, int numero, char* cliente, char* descricao, int quantidade, char* status) {
    Pedido* novoPedido = (Pedido*)malloc(sizeof(Pedido));
    if (!novoPedido) {
        printf("Erro de alocacao de memoria!\n");
        return lista;
    }
    novoPedido->numero = numero;
    strcpy(novoPedido->cliente, cliente);
    strcpy(novoPedido->descricao, descricao);
    novoPedido->quantidade = quantidade;
    strcpy(novoPedido->status, status);
    novoPedido->proximo = lista;
    return novoPedido;
}

Pedido* obterPedido(Pedido* lista, int numero) {
    while (lista != NULL) {
        if (lista->numero == numero) {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL;
}

void atualizarStatus(Pedido* lista, int numero, char* novoStatus) {
    Pedido* pedido = obterPedido(lista, numero);
    if (pedido) {
        strcpy(pedido->status, novoStatus);
        printf("Status do pedido %d atualizado para %s.\n", numero, novoStatus);
    } else {
        printf("Pedido nao encontrado!\n");
    }
}

Pedido* deletarPedido(Pedido* lista, int numero) {
    Pedido* atual = lista;
    Pedido* anterior = NULL;

    while (atual != NULL && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Pedido nao encontrado!\n");
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Pedido %d removido com sucesso!\n", numero);
    return lista;
}

void liberarLista(Pedido* lista) {
    Pedido* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proximo;
        free(temp);
    }
    printf("Lista de pedidos liberada!\n");
}

void exibirPedidos(Pedido* lista) {
    if (lista == NULL) {
        printf("Nenhum pedido na lista.\n");
        return;
    }
    printf("\nLista de Pedidos:\n");
    while (lista != NULL) {
        printf("Numero: %d | Cliente: %s | Descricao: %s | Quantidade: %d | Status: %s\n",
               lista->numero, lista->cliente, lista->descricao, lista->quantidade, lista->status);
        lista = lista->proximo;
    }
}

int main() {
    Pedido* listaPedidos = criarLista();
    int opcao, numero, quantidade;
    char cliente[50], descricao[100], status[20];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Pedido\n");
        printf("2. Atualizar Status\n");
        printf("3. Exibir Pedidos\n");
        printf("4. Deletar Pedido\n");
        printf("5. Obter Pedido Específico\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Por favor, insira um numero.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Numero do pedido: ");
                scanf("%d", &numero);
                while (getchar() != '\n');
                printf("Nome do cliente: ");
                fgets(cliente, sizeof(cliente), stdin);
                cliente[strcspn(cliente, "\n")] = 0;
                printf("Descricao do prato: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                printf("Quantidade: ");
                if (scanf("%d", &quantidade) != 1) {
                    printf("Entrada invalida! Quantidade deve ser um numero.\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                printf("Status (pendente/em preparo/pronto/entregue): ");
                fgets(status, sizeof(status), stdin);
                status[strcspn(status, "\n")] = 0;
                listaPedidos = inserirPedido(listaPedidos, numero, cliente, descricao, quantidade, status);
                break;
            case 2:
                printf("Numero do pedido a atualizar: ");
                scanf("%d", &numero);
                while (getchar() != '\n');
                printf("Novo status: ");
                fgets(status, sizeof(status), stdin);
                status[strcspn(status, "\n")] = 0;
                atualizarStatus(listaPedidos, numero, status);
                break;
            case 3:
                exibirPedidos(listaPedidos);
                break;
            case 4:
                printf("Numero do pedido a deletar: ");
                scanf("%d", &numero);
                listaPedidos = deletarPedido(listaPedidos, numero);
                break;
            case 5:
                printf("Numero do pedido a buscar: ");
                scanf("%d", &numero);
                Pedido* pedidoEncontrado = obterPedido(listaPedidos, numero);
                if (pedidoEncontrado) {
                    printf("\nPedido encontrado:\n");
                    printf("Numero: %d | Cliente: %s | Descricao: %s | Quantidade: %d | Status: %s\n",
                           pedidoEncontrado->numero, pedidoEncontrado->cliente,
                           pedidoEncontrado->descricao, pedidoEncontrado->quantidade,
                           pedidoEncontrado->status);
                } else {
                    printf("Pedido nao encontrado!\n");
                }
                break;
            case 6:
                liberarLista(listaPedidos);
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
