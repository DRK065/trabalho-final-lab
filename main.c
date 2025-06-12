#include <stdio.h>
#include <string.h>

struct Cliente {
    int id;
    char nome[50];
    char cpf[15];
};

struct Produto {
    int id;
    char nome[50];
    float preco;
    int estoque;
};

struct ItemVenda {
    int id_produto;
    int quantidade;
    float valor_unitario;
};

struct Venda {
    int id_venda;
    int id_cliente;
    int total_itens;
    struct ItemVenda itens[10];
    float total;
};

struct Cliente clientes[10];
int total_clientes = 0;

struct Produto produtos[10];
int total_produtos = 0;

struct Venda vendas[10];
int total_vendas = 0;

void cadastrar_cliente() {
    if (total_clientes >= 10) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    struct Cliente novo_cliente;
    novo_cliente.id = total_clientes + 1;

    printf("Digite o nome do cliente: ");
    scanf("%s", novo_cliente.nome);

    printf("Digite o CPF do cliente: ");
    scanf("%s", novo_cliente.cpf);

    clientes[total_clientes++] = novo_cliente;

    printf("Cliente %s cadastrado com sucesso! ID: %d\n", novo_cliente.nome, novo_cliente.id);
}

void cadastrar_produtos() {
    if (total_produtos >= 10) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    struct Produto novo_produto;
    novo_produto.id = total_produtos + 1;

    printf("Digite o nome do produto: ");
    scanf("%s", novo_produto.nome);

    printf("Digite o preco do produto: ");
    scanf("%f", &novo_produto.preco);

    printf("Digite a quantidade em estoque (opcional, 0 se não deseja informar): ");
    scanf("%d", &novo_produto.estoque);

    produtos[total_produtos++] = novo_produto;

    printf("Produto %s cadastrado com sucesso! ID: %d\n", novo_produto.nome, novo_produto.id);
}

void listar_clientes() {
    if (total_clientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("Clientes:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("ID: %d | Nome: %s | CPF: %s\n", clientes[i].id, clientes[i].nome, clientes[i].cpf);
    }
}

void listar_produtos() {
    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Produtos:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("ID: %d | Nome: %s | Preço: R$ %.2f | Estoque: %d\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

void cadastrar_venda() {
    if (total_vendas >= 10) {
        printf("Limite de vendas atingido.\n");
        return;
    }

    struct Venda nova_venda;
    nova_venda.id_venda = total_vendas + 1;
    nova_venda.total_itens = 0;
    nova_venda.total = 0.0;

    printf("Digite o ID do cliente: ");
    scanf("%d", &nova_venda.id_cliente);

    int qtd_itens;
    printf("Quantos itens na venda? ");
    scanf("%d", &qtd_itens);

    for (int i = 0; i < qtd_itens; i++) {
        struct ItemVenda item;
        printf("Item %d - Digite o ID do produto: ", i + 1);
        scanf("%d", &item.id_produto);

        printf("Quantidade: ");
        scanf("%d", &item.quantidade);

        if (item.id_produto > 0 && item.id_produto <= total_produtos) {
            item.valor_unitario = produtos[item.id_produto - 1].preco;
            nova_venda.itens[i] = item;
            nova_venda.total += item.valor_unitario * item.quantidade;
            nova_venda.total_itens++;
        } else {
            printf("Produto inválido. Item ignorado.\n");
        }
    }

    vendas[total_vendas++] = nova_venda;

    printf("Venda cadastrada com sucesso! ID da Venda: %d | Total: R$ %.2f\n",
           nova_venda.id_venda, nova_venda.total);
}

void listar_vendas() {
    if (total_vendas == 0) {
        printf("Nenhuma venda cadastrada.\n");
        return;
    }

    for (int i = 0; i < total_vendas; i++) {
        struct Venda v = vendas[i];
        printf("\nVenda ID: %d\n", v.id_venda);
        printf("Cliente ID: %d\n", v.id_cliente);
        printf("Itens:\n");

        for (int j = 0; j < v.total_itens; j++) {
            struct ItemVenda item = v.itens[j];
            printf("  Produto ID: %d | Quantidade: %d | Valor Unitário: R$ %.2f\n",
                   item.id_produto, item.quantidade, item.valor_unitario);
        }

        printf("Total da venda: R$ %.2f\n", v.total);
    }
}

int main() {
    int opcao = -1;

    do {
        printf("\nMENU\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Cadastrar Venda\n");
        printf("4. Listar Clientes\n");
        printf("5. Listar Produtos\n");
        printf("6. Listar Vendas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar_cliente(); break;
            case 2: cadastrar_produtos(); break;
            case 3: cadastrar_venda(); break;
            case 4: listar_clientes(); break;
            case 5: listar_produtos(); break;
            case 6: listar_vendas(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

