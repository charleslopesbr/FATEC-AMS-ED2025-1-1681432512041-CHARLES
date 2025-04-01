#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo estrutura do pedido
typedef struct Pedido {
    int numero;               // Número do pedido (gerado automaticamente)
    char cliente[50];
    char descricao[100];
    int quantidade;
    int contadorStatus;       // Contador de status: 1=pendente, 2=em preparo, 3=pronto, 4=entregue
    struct Pedido *proximo;
} Pedido;

// Função para criar um novo pedido
Pedido* criarPedido(int numero, const char *cliente, const char *descricao, int quantidade) {
    Pedido *novo = (Pedido*)malloc(sizeof(Pedido));
    if (!novo) {
        printf("Erro ao alocar memória para o novo pedido.\n");
        return NULL;
    }
    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    novo->contadorStatus = 1;  // Status inicial é "pendente"
    novo->proximo = NULL;
    return novo;
}

// Função para empilhar um pedido (inserir no topo da pilha)
void empilharPedido(Pedido **topo, Pedido *novo) {
    novo->proximo = *topo;  // O topo da pilha passa a ser o novo pedido
    *topo = novo;  // Agora o novo pedido é o topo da pilha
}

// Função para desempilhar um pedido (remover do topo da pilha)
Pedido* desempilharPedido(Pedido **topo) {
    if (*topo == NULL) {
        printf("A pilha está vazia.\n");
        return NULL;
    }
    Pedido *pedidoRemovido = *topo;
    *topo = pedidoRemovido->proximo;  // O próximo pedido agora será o topo
    return pedidoRemovido;  // Retorna o pedido removido
}

// Função para buscar um pedido pelo número
Pedido* obterPedido(Pedido *topo, int numero) {
    while (topo != NULL) {
        if (topo->numero == numero) {
            return topo;
        }
        topo = topo->proximo;
    }
    return NULL;
}

// Função para atualizar o status de um pedido
void atualizarStatus(Pedido *pedido) {
    if (pedido->contadorStatus < 4) {
        pedido->contadorStatus++; // Incrementa o contador de status
        switch (pedido->contadorStatus) {
            case 2:
                printf("Status do pedido %d atualizado para: Em Preparo\n", pedido->numero);
                break;
            case 3:
                printf("Status do pedido %d atualizado para: Pronto\n", pedido->numero);
                break;
            case 4:
                printf("Status do pedido %d atualizado para: Entregue\n", pedido->numero);
                break;
        }
    } else {
        printf("O status do pedido %d não pode ser alterado, pois já foi marcado como 'Entregue'.\n", pedido->numero);
    }
}

// Função para liberar toda a pilha
void liberarPilha(Pedido **topo) {
    Pedido *temp;
    while (*topo != NULL) {
        temp = *topo;
        *topo = temp->proximo;
        free(temp);
    }
    printf("Pilha liberada com sucesso!\n");
}

// Função para exibir um pedido
void exibirPedido(Pedido *pedido) {
    if (pedido != NULL) {
        printf("Pedido Nº: %03d\nCliente: %s\nPrato: %s\nQuantidade: %d\nStatus: ", 
               pedido->numero, pedido->cliente, pedido->descricao, pedido->quantidade);
        switch (pedido->contadorStatus) {
            case 1:
                printf("Pendente\n");
                break;
            case 2:
                printf("Em Preparo\n");
                break;
            case 3:
                printf("Pronto\n");
                break;
            case 4:
                printf("Entregue\n");
                break;
        }
    } else {
        printf("Pedido não encontrado.\n");
    }
}

// Função para exibir todos os pedidos (na ordem da pilha)
void exibirTodosPedidos(Pedido *topo) {
    if (topo == NULL) {
        printf("Nenhum pedido registrado.\n");
    } else {
        Pedido *temp = topo;
        while (temp != NULL) {
            exibirPedido(temp);
            temp = temp->proximo;
        }
    }
}

int main() {
    Pedido *pilhaPedidos = NULL;
    int opcao, quantidade, numero;
    char cliente[50], descricao[100];

    do {
        printf("\nMenu de Opções:\n");
        printf("1. Inserir Pedido\n");
        printf("2. Atualizar Status do Pedido\n");
        printf("3. Remover Pedido (Desempilhar)\n");
        printf("4. Exibir Pedido\n");
        printf("5. Exibir Todos os Pedidos\n");
        printf("6. Liberar a Pilha\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: // Inserir pedido
                // Gerar número automaticamente com base no número de pedidos na pilha
                int numero = 1;
                if (pilhaPedidos != NULL) {
                    Pedido *temp = pilhaPedidos;
                    while (temp->proximo != NULL) {
                        temp = temp->proximo;
                        numero++;
                    }
                }
                
                printf("Digite o nome do cliente: ");
                getchar(); // Para limpar o buffer do enter
                fgets(cliente, sizeof(cliente), stdin);
                cliente[strcspn(cliente, "\n")] = '\0';  // Remover o \n do fgets
                
                printf("Digite a descrição do prato: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0'; // Remover o \n do fgets
                
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                // Criando e empilhando o pedido
                Pedido *novoPedido = criarPedido(numero, cliente, descricao, quantidade);
                empilharPedido(&pilhaPedidos, novoPedido);
                break;

            case 2: // Atualizar status
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                Pedido *pedido = obterPedido(pilhaPedidos, numero);
                if (pedido != NULL) {
                    atualizarStatus(pedido);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;

            case 3: // Remover pedido
                Pedido *pedidoRemovido = desempilharPedido(&pilhaPedidos);
                if (pedidoRemovido != NULL) {
                    printf("Pedido Nº %d removido com sucesso.\n", pedidoRemovido->numero);
                    free(pedidoRemovido); // Libera a memória do pedido removido
                }
                break;

            case 4: // Exibir pedido
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                exibirPedido(obterPedido(pilhaPedidos, numero));
                break;

            case 5: // Exibir todos os pedidos
                exibirTodosPedidos(pilhaPedidos);
                break;

            case 6: // Liberar a pilha
                liberarPilha(&pilhaPedidos);
                break;

            case 7: // Sair
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
