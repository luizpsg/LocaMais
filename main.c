#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "biblioteca.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar veiculo\n");
        printf("3. Cadastrar locacao\n");
        printf("4. Dar baixa em locacao\n");
        printf("5. Pesquisar cliente\n");
        printf("6. Pesquisar veiculo\n");
        printf("7. Listar locacoes de um cliente\n");
        printf("8. Calcular pontos de fidelidade de um cliente\n");
        printf("9. Pesquisar clientes premiados\n");
        printf("10. Calcular Receita Total (Funcao extra)\n");
        printf("11. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarVeiculo();
                break;
            case 3:
                cadastrarLocacao();
                break;
            case 4:
                darBaixaLocacao();
                break;
            case 5:
                pesquisarCliente();
                break;
            case 6:
                pesquisarVeiculo();
                break;
            case 7:
                listarLocacoesCliente();
                break;
            case 8:
                mostrarPontosFidelidade();
                break;
            case 9:
                pesquisarClientesPremiados();
                break;
            case 10:
                gerarRelatorioReceita();
                break;
            case 11:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 11);

    return 0;
}

