#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
// Structures
typedef struct {
    int codigo;
    char nome[80];
    char endereco[100];
    char telefone[20];
    int pontos_fidelidade;
} Cliente;

typedef struct {
    int codigo;
    char descricao[200];
    char modelo[50];
    char cor[30];
    char placa[10];
    float valor_diaria;
    int quantidade_ocupantes;
    int status; // 0 - Disponível, 1 - Alugado, 2 - Manutenção
} Veiculo;

struct data
{
    int dia;
    int mes;
    int ano;
};

typedef struct {
    int codigo_locacao;
    int seguro;
    int quantidade_dias;
    int codigo_cliente;
    int codigo_veiculo;
    int quantidade_ocupantes;
    float valor_total;
    int status; // 0 - Finalizada, 1 - Em andamento
    struct data data_inicio;
    struct data data_termino;
} Locacao;

struct tm converterParaTm(struct data data) {
    struct tm tmData = {0};
    tmData.tm_year = data.ano - 1900; // Ano desde 1900
    tmData.tm_mon = data.mes - 1;     // Mês de 0 a 11
    tmData.tm_mday = data.dia;        // Dia do mês
    return tmData;
}

// Function prototypes
void cadastrarCliente();
int clienteExists(int );
void cadastrarVeiculo();
int veiculoExists(int );
void cadastrarLocacao();
int locacaoExists(int );
int calcularDiferencaDias(struct data, struct data);
void darBaixaLocacao();
void pesquisarCliente();
void pesquisarVeiculo();
void listarLocacoesCliente();
void calcularPontos();
void mostrarPontosFidelidade();
void pesquisarClientesPremiados();
void funcaoExtra();


void cadastrarCliente() {

    FILE *file = fopen("clientes.bin", "ab");

    if (file != NULL) {
        Cliente cliente;

        printf("Digite o código do cliente: ");
        scanf("%d", &cliente.codigo);

            // Check if the vehicle with the same code already exists
        if (clienteExists(cliente.codigo)) 
        {
            printf("Já existe um veículo com o mesmo código.\n");
            fclose(file);
        }

        else
        {
            getchar();
            printf("Digite o nome do cliente: ");
            fgets(cliente.nome, 50, stdin);

            printf("Digite o endereço do cliente: ");
            fgets(cliente.endereco, 100, stdin);

            printf("Digite o telefone do cliente: ");
            scanf("%s", cliente.telefone);
            
            cliente.pontos_fidelidade = 0;

            fwrite(&cliente, sizeof(Cliente), 1, file);

            fclose(file);
        }
    }

    else 
    {
        printf("Erro ao abrir o arquivo.\n");
    }

}

int clienteExists(int codigo) {
    FILE *file = fopen("clientes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    Cliente cliente;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.codigo == codigo) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void pesquisarCliente() {

    FILE *file = fopen("clientes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int codigo;
    printf("Digite o código do cliente: ");
    scanf("%d", &codigo);

    Cliente cliente;
    int found = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.codigo == codigo) {
            printf("Cliente encontrado:\n");
            printf("Código: %d\n", cliente.codigo);
            printf("Nome: %s", cliente.nome);
            printf("Endereço: %s", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Cliente não encontrado.\n");
    }

    fclose(file);
}

void cadastrarVeiculo() {
    FILE *file = fopen("veiculos.bin", "ab");
    if (file != NULL) {

        Veiculo veiculo;

        printf("Digite o código do veículo: ");
        scanf("%d", &veiculo.codigo);

        // Check if the vehicle with the same code already exists
        if (veiculoExists(veiculo.codigo)) {
            printf("Já existe um veículo com o mesmo código.\n");
            fclose(file);
            return;
        }

        getchar();
        printf("Digite o modelo do veículo: \n");
        fgets(veiculo.modelo, 50, stdin);

        printf("Digite a descrição do veículo: \n");
        fgets(veiculo.descricao, 200, stdin);

        printf("Digite a cor do veículo: \n");
        fgets(veiculo.cor, 30, stdin);

        printf("Digite a placa do veículo: \n");
        fgets(veiculo.placa, 10, stdin);

        printf("Digite o valor da diária do veículo: usar virgula para separar os centavos!\n");
        scanf("%f", &veiculo.valor_diaria);

        printf("Digite a quantidade de ocupantes do veículo: \n");
        scanf("%d", &veiculo.quantidade_ocupantes);

        printf("Digite o status do veículo: 0 - Disponível, 1 - Alugado, 2 - Manutenção\n");
        scanf("%i", &veiculo.status);

        fwrite(&veiculo, sizeof(Veiculo), 1, file);

        fclose(file);
    }
    else
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
}

int veiculoExists(int codigo) {
    FILE *file = fopen("veiculos.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    Veiculo veiculo;

    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.codigo == codigo) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void pesquisarVeiculo() {
    FILE *file = fopen("veiculos.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int codigo;
    printf("Digite o código do veículo: ");
    scanf("%d", &codigo);

    Veiculo veiculo;
    int found = 0;

    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.codigo == codigo) {
            printf("Veículo encontrado:\n");
            printf("Código: %d\n", veiculo.codigo);
            printf("Modelo: %s", veiculo.modelo);
            printf("Descrição: %s", veiculo.descricao);
            printf("Cor: %s", veiculo.cor);
            printf("Placa: %s", veiculo.placa);
            printf("Valor da diária: %.2f\n", veiculo.valor_diaria);
            printf("Quantidade de ocupantes: %d\n", veiculo.quantidade_ocupantes);
            printf("Status: %i\n", veiculo.status);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Veículo não encontrado.\n");
    }

    fclose(file);
}

void cadastrarLocacao() {
    FILE *file = fopen("locacoes.bin", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Locacao locacao;

     printf("Digite o código da locação: ");
    scanf("%d", &locacao.codigo_locacao);

    if (locacaoExists(locacao.codigo_locacao)) {
        printf("Já existe uma locação com o mesmo código.\n");
        fclose(file);
    return;
    }

    printf("Digite o código do cliente: ");
    scanf("%d", &locacao.codigo_cliente);

    printf("Digite a data de início da locação (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &locacao.data_inicio.dia, &locacao.data_inicio.mes, &locacao.data_inicio.ano);

    printf("Digite a data de término da locação (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &locacao.data_termino.dia, &locacao.data_termino.mes, &locacao.data_termino.ano);

    printf("Digite o numero de ocupantes: ");
    scanf("%i", &locacao.quantidade_ocupantes);

    // Find an available vehicle
    int vehicleFound = 0;
    Veiculo veiculo;

    FILE *vehicleFile = fopen("veiculos.bin", "rb+");
    if (vehicleFile == NULL) {
        printf("Erro ao abrir o arquivo de veículos.\n");
        return;
    }

    while (fread(&veiculo, sizeof(Veiculo), 1, vehicleFile))
    {
        if (veiculo.status == 0 && veiculo.quantidade_ocupantes >= locacao.quantidade_ocupantes)
        {
            vehicleFound = 1;
            locacao.codigo_veiculo = veiculo.codigo;
            veiculo.status = 1; // Set vehicle status to available
            fseek(vehicleFile, -(long)sizeof(Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(Veiculo), 1, vehicleFile);
            break;
        }
    }
    


    fclose(vehicleFile);

    if (!vehicleFound) {
        printf("Nenhum veículo disponível.\n");
        return;
    }

    int rentalDays = calcularDiferencaDias(locacao.data_inicio, locacao.data_termino);

    float totalAmount = veiculo.valor_diaria * (float)rentalDays;
    printf("Gostarias tu de seguro por 50 reais ? 1 - Sim, 0 - Não\n");
    scanf("%i", &locacao.seguro);

    if (locacao.seguro == 1)
    {
    totalAmount += 50.0; // Insurance cost
    }

    printf("Valor total da locação: %.2f\n", totalAmount);

    // Fill in the remaining data of the rental
    locacao.valor_total = totalAmount;

    locacao.status = 1; // Set locacao status to ongoing

    fwrite(&locacao, sizeof(Locacao), 1, file);

    fclose(file);
}

int locacaoExists(int codigo) {
    FILE *file = fopen("locacoes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    Locacao locacao;

    while (fread(&locacao, sizeof(Locacao), 1, file)) {
        if (locacao.codigo_locacao == codigo) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int calcularDiferencaDias(struct data inicio, struct data termino) {
struct tm tmInicio = converterParaTm(inicio);
struct tm tmTermino = converterParaTm(*(struct data *)&termino);

time_t tInicio = mktime(&tmInicio);
time_t tTermino = mktime(&tmTermino);

double diferenca = difftime(tTermino, tInicio);
return diferenca / (60.00 * 60.00 * 24.00); // Convertendo segundos em dias
}

void darBaixaLocacao() {

    // TODO: Implementar a função de dar baixa em locacao
        FILE *file = fopen("locacoes.bin", "rb+");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de locações.\n");
            return;
        }

        int codigo;
        printf("Digite o código da locação: ");
        scanf("%d", &codigo);

        Locacao locacao;
        int found = 0;

        while (fread(&locacao, sizeof(Locacao), 1, file)) {
            if (locacao.codigo_locacao == codigo) {
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Locação não encontrada.\n");
            fclose(file);
            return;
        }

        if (locacao.status == 0) {
            printf("Locação já foi finalizada.\n");
            fclose(file);
            return;
        }

        // Calculate total amount
        int rentalDays = calcularDiferencaDias(locacao.data_inicio, locacao.data_termino);
        float totalAmount = locacao.valor_total;

        // Check if the vehicle is returned on time
        struct data dataEntrega;
        printf("Digite a data de entrega do veículo (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &dataEntrega.dia, &dataEntrega.mes, &dataEntrega.ano);

        struct tm tmDataEntrega = converterParaTm(dataEntrega);
        time_t tDataEntrega = mktime(&tmDataEntrega);

        struct tm tmDataTermino = converterParaTm(locacao.data_termino);
        time_t tDataTermino = mktime(&tmDataTermino);

        if (tDataEntrega > tDataTermino) {
            // Calculate late fee
            double diferencaDias = difftime(tDataEntrega, tDataTermino) / (60.00 * 60.00 * 24.00);
            float multa = (totalAmount * 0.05) + (30.0 * diferencaDias);
            totalAmount += multa;
            printf("Multa por atraso: R$ %.2f\n", multa);
        }

        printf("Valor total a ser pago: R$ %.2f\n", totalAmount);

        // Update vehicle status
        FILE *vehicleFile = fopen("veiculos.bin", "rb+");
        if (vehicleFile == NULL) {
            printf("Erro ao abrir o arquivo de veículos.\n");
            fclose(file);
            return;
        }

        Veiculo veiculo;
        int vehicleFound = 0;

        while (fread(&veiculo, sizeof(Veiculo), 1, vehicleFile)) {
            if (veiculo.codigo == locacao.codigo_veiculo) {
                veiculo.status = 0; // Set vehicle status to available
                fseek(vehicleFile, -(long)sizeof(Veiculo), SEEK_CUR);
                fwrite(&veiculo, sizeof(Veiculo), 1, vehicleFile);
                vehicleFound = 1;
                break;
            }
        }

        fclose(vehicleFile);

        if (!vehicleFound) {
            printf("Erro ao atualizar o status do veículo.\n");
            fclose(file);
            return;
        }

        // Update locacao status
        locacao.status = 0; // Set locacao status to finished
        fseek(file, -(long)sizeof(Locacao), SEEK_CUR);
        fwrite(&locacao, sizeof(Locacao), 1, file);

        fclose(file);
}

void listarLocacoesCliente() {
    // Implementação da função de listagem de locacoes de um cliente
    FILE *file = fopen("locacoes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de locações.\n");
        return;
    }

    int codigoCliente;
    printf("Digite o código do cliente: ");
    scanf("%d", &codigoCliente);

    Locacao locacao;
    int found = 0;

    while (fread(&locacao, sizeof(Locacao), 1, file)) {
        if (locacao.codigo_cliente == codigoCliente) {
            printf("Código da locação: %d\n", locacao.codigo_locacao);
            printf("Código do veículo: %d\n", locacao.codigo_veiculo);
            printf("Data de início: %d/%d/%d\n", locacao.data_inicio.dia, locacao.data_inicio.mes, locacao.data_inicio.ano);
            printf("Data de término: %d/%d/%d\n", locacao.data_termino.dia, locacao.data_termino.mes, locacao.data_termino.ano);
            printf("Valor total: R$ %.2f\n", locacao.valor_total);
            printf("Status: %s\n", locacao.status == 1 ? "Em andamento" : "Finalizada");
            printf("\n");
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("Nenhuma locação encontrada para o cliente de código %d.\n", codigoCliente);
    }
}

void calcularPontos() {
    // Implementation of the calcularPontosFidelidade function
    FILE *file = fopen("locacoes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de locações.\n");
        return;
    }

    Locacao locacao;
    int found = 0;
    int rentalDays;

    FILE *clientFile = fopen("clientes.bin", "rb+");
    if (clientFile == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        fclose(file);
        return;
    }

    Cliente cliente;

    while (fread(&cliente, sizeof(Cliente), 1, clientFile)) 
    {    
        cliente.pontos_fidelidade = 0;
        fseek(clientFile, -(long)sizeof(Cliente), SEEK_CUR);
        fwrite(&cliente, sizeof(Cliente), 1, clientFile);
        found = 1;
        break;
    }

    while (fread(&locacao, sizeof(Locacao), 1, file)) 
    {
        fseek(clientFile, 0, SEEK_SET); // Move the file pointer to the beginning of the client file
        
        while (fread(&cliente, sizeof(Cliente), 1, clientFile)) {
            if (cliente.codigo == locacao.codigo_cliente) {
                rentalDays = calcularDiferencaDias(locacao.data_inicio, locacao.data_termino);
                cliente.pontos_fidelidade += rentalDays * 10;
                fseek(clientFile, -(long)sizeof(Cliente), SEEK_CUR);
                fwrite(&cliente, sizeof(Cliente), 1, clientFile);
                found = 1;
                break;
            }
        }
    }

    fclose(file);
    fclose(clientFile);

    if (found) {
        printf("Pontos de fidelidade atualizados para todos os clientes.\n");
    } else {
        printf("Nenhuma locação encontrada para os clientes.\n");
    }
}

void mostrarPontosFidelidade() {
    
    calcularPontos();

    FILE *file = fopen("clientes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;
    int codigo;
    printf("Digite o código do cliente: ");
    scanf("%d", &codigo);

    int found = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.codigo == cliente.codigo) {
            printf("Pontos de fidelidade: %d\n", cliente.pontos_fidelidade);
            found = 1;
            break;
        }
    }
}

void pesquisarClientesPremiados() {
    calcularPontos();

    FILE *file = fopen("clientes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;

    int found = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.pontos_fidelidade >= 500) {
            printf("Código: %d\n", cliente.codigo);
            printf("Nome: %s", cliente.nome);
            printf("Endereço: %s", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Pontos de fidelidade: %d\n", cliente.pontos_fidelidade);
            printf("\n");
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("Nenhum cliente premiado encontrado.\n");
    }
}

float calcularTotalReceita() {
    calcularPontos();

    FILE *file = fopen("locacoes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de locações.\n");
        return 0.0;
    }

    Locacao locacao;
    float totalRevenue = 0.0;

    while (fread(&locacao, sizeof(Locacao), 1, file)) {
        if (locacao.status == 0) {
            totalRevenue += locacao.valor_total;
        }
    }

    fclose(file);

    return totalRevenue;
}

void gerarRelatorioReceita() {
    float totalRevenue = calcularTotalReceita();

    printf("Receital total dos aluguéis: $%.2f\n", totalRevenue);
}

#endif // BIBLIOTECA_H