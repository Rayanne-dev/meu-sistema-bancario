/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Constantes e Arrays Globais para acesso pelas funções de arquivo
const int MAX_CONTAS = 100;
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];

const int MAX_MOVIMENTACOES = 500;
int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];
double valorMovimentacao[MAX_MOVIMENTACOES];

int quantidade_contas = 0;
int quantidadeMovimentacoes = 0;

// --- FUNÇÕES DE PERSISTÊNCIA EM ARQUIVOS (ETAPA 3) ---

void salvarContas() {
    ofstream arquivo("contas.txt");
    if (arquivo.is_open()) {
        for (int i = 0; i < quantidade_contas; i++) {
            arquivo << numeroConta[i] << ";"
                    << nomeCliente[i] << ";"
                    << cpf[i] << ";"
                    << tipoConta[i] << ";"
                    << saldo[i] << ";"
                    << contaAtiva[i] << endl;
        }
        arquivo.close();
    }
}

void carregarContas() {
    ifstream arquivo("contas.txt");
    if (!arquivo.is_open()) {
        return; // Se o arquivo ainda não existir, inicia normalmente com 0 contas
    }

    string linha;
    quantidade_contas = 0;

    while (getline(arquivo, linha) && quantidade_contas < MAX_CONTAS) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string campo;

        getline(ss, campo, ';');
        numeroConta[quantidade_contas] = stoi(campo);

        getline(ss, nomeCliente[quantidade_contas], ';');
        getline(ss, cpf[quantidade_contas], ';');

        getline(ss, campo, ';');
        tipoConta[quantidade_contas] = stoi(campo);

        getline(ss, campo, ';');
        saldo[quantidade_contas] = stod(campo);

        getline(ss, campo, ';');
        contaAtiva[quantidade_contas] = (stoi(campo) == 1);

        quantidade_contas++;
    }
    arquivo.close();
}

void salvarMovimentacoes() {
    ofstream arquivo("movimentacoes.txt");
    if (arquivo.is_open()) {
        for (int i = 0; i < quantidadeMovimentacoes; i++) {
            arquivo << contaMovimentacao[i] << ";"
                    << tipoMovimentacao[i] << ";"
                    << valorMovimentacao[i] << endl;
        }
        arquivo.close();
    }
}

void carregarMovimentacoes() {
    ifstream arquivo("movimentacoes.txt");
    if (!arquivo.is_open()) {
        return; // Se o arquivo ainda não existir, inicia normalmente com 0 movimentações
    }

    string linha;
    quantidadeMovimentacoes = 0;

    while (getline(arquivo, linha) && quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string campo;

        getline(ss, campo, ';');
        contaMovimentacao[quantidadeMovimentacoes] = stoi(campo);

        getline(ss, campo, ';');
        tipoMovimentacao[quantidadeMovimentacoes] = campo[0];

        getline(ss, campo, ';');
        valorMovimentacao[quantidadeMovimentacoes] = stod(campo);

        quantidadeMovimentacoes++;
    }
    arquivo.close();
}

// --- PROGRAMA PRINCIPAL ---

int main()
{
    // Carrega os dados salvos anteriormente antes de exibir o menu
    carregarContas();
    carregarMovimentacoes();

    // Variaveis locais de controle
    int opcao;
    int numBusca, numOrigem, numDestino;
    double valorTransacao;
    bool achou;
    bool achouOrigem;
    bool achouDestino;
    bool teveMovimentacao;
    
    // MENU
    do {
        cout << "\n=== MENU SISTEMA BANCARIO ===\n";
        cout << "1- Cadastar Conta " << endl;
        cout << "2- Listar Conta Cadastradas " << endl;
        cout << "3- Consultar uma conta pelo número " << endl;
        cout << "4- Realizar depósitos" << endl;
        cout << "5- Realizar saques, verificando saldo suficiente " << endl;
        cout << "6- Realizar transferências entre duas contas " << endl;
        cout << "7- Exibir o extrato de uma conta " << endl;
        cout << "8- Sair " << endl;
        cout << " --Escolha uma opção: ";
        cin >> opcao;
        
        switch (opcao) {
            case 1:
                cout << "\n--- CADASTRAR CONTA ---\n";
                if (quantidade_contas >= MAX_CONTAS) {
                    cout << "Erro: Limite de contas atingido!" << endl;
                } else {
                    cout << "Numero da Conta: ";
                    cin >> numeroConta[quantidade_contas];
                    
                    cin.ignore();
                    cout << "Nome do Cliente: ";
                    getline(cin, nomeCliente[quantidade_contas]);

                    cout << "CPF: ";
                    getline(cin, cpf[quantidade_contas]);

                    cout << "Tipo de Conta (1-Corrente, 2-Poupanca): ";
                    cin >> tipoConta[quantidade_contas];

                    cout << "Saldo Inicial: R$ ";
                    cin >> saldo[quantidade_contas];

                    contaAtiva[quantidade_contas] = true;
                    quantidade_contas++;
                    
                    // Salva a nova conta no arquivo contas.txt
                    salvarContas();
                    
                    cout << "___Conta cadastrada com sucesso!___\n";
                }
                break;
                
            case 2:
                cout << "\n--- LISTA DE CONTAS CADASTRADAS ---\n";
                if (quantidade_contas == 0) {
                    cout << "Nenhuma conta cadastrada.\n";
                } else {
                    for (int i = 0; i < quantidade_contas; i++) {
                        if (contaAtiva[i]) {
                            cout << "Conta: " << numeroConta[i] 
                                 << " | Cliente: " << nomeCliente[i] 
                                 << " | CPF: " << cpf[i] 
                                 << " | Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") 
                                 << " | Saldo: R$ " << saldo[i] << "\n";
                        }
                    }
                }
                break;
                    
            case 3:
                cout << "\n--- CONSULTAR CONTA ---\n";
                cout << "Digite o numero da conta: ";
                cin >> numBusca;

                achou = false;

                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numBusca && contaAtiva[i]) {
                        cout << "Conta ativa encontrada!" << endl;
                        cout << "Cliente: " << nomeCliente[i] << "\n";
                        cout << "CPF: " << cpf[i] << "\n";
                        cout << "Saldo atual: R$ " << saldo[i] << "\n";
                        
                        achou = true; 
                        break;
                    }
                }

                if (!achou) {
                    cout << "Erro: Conta nao encontrada.\n";
                }
                break;
                
            case 4:
                cout << "\n--- REALIZAR DEPOSITO ---\n";
                cout << "Digite o numero da conta: ";
                cin >> numBusca;

                achou = false;

                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numBusca && contaAtiva[i]) {
                        cout << "Valor do deposito: R$ ";
                        cin >> valorTransacao;

                        if (valorTransacao > 0) {
                            if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                                saldo[i] = saldo[i] + valorTransacao;

                                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                                tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                                valorMovimentacao[quantidadeMovimentacoes] = valorTransacao;
                                quantidadeMovimentacoes++;

                                // Atualiza saldo e histórico nos arquivos
                                salvarContas();
                                salvarMovimentacoes();

                                cout << "Deposito realizado! Novo saldo de " << nomeCliente[i] << ": R$ " << saldo[i] << "\n";
                            } else {
                                cout << "Erro: Limite de historico cheio!\n";
                            }
                        } else {
                            cout << "Erro: O valor deve ser maior que zero.\n";
                        }
                        achou = true;
                        break;
                    }
                }

                if (!achou) {
                    cout << "Erro: Conta nao encontrada.\n";
                }
                break;   
                
                        case 5:
                cout << "\n--- REALIZAR SAQUE ---\n";
                cout << "Digite o numero da conta: ";
                cin >> numBusca;

                achou = false;

                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numBusca && contaAtiva[i]) {
                        cout << "Valor do saque: R$ ";
                        cin >> valorTransacao;

                        if (valorTransacao > 0) {
                            if (saldo[i] >= valorTransacao) {
                                if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                                    saldo[i] = saldo[i] - valorTransacao;

                                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                                    valorMovimentacao[quantidadeMovimentacoes] = valorTransacao;
                                    quantidadeMovimentacoes++;

                                    // Atualiza saldo e histórico nos arquivos
                                    salvarContas();
                                    salvarMovimentacoes();

                                    cout << "Saque realizado! Novo saldo de " << nomeCliente[i] << ": R$ " << saldo[i] << "\n";
                                } else {
                                    cout << "Erro: Limite de historico cheio!\n";
                                }
                            } else {
                                cout << "Erro: Saldo insuficiente!\n";
                            }
                        } else {
                            cout << "Erro: O valor deve ser maior que zero.\n";
                        }
                        achou = true;
                        break;
                    }
                }

                if (!achou) {
                    cout << "Erro: Conta nao encontrada.\n";
                }
                break;
                
            case 6:
                cout << "\n--- REALIZAR TRANSFERENCIA ---\n";
                cout << "Numero da conta de ORIGEM (Quem envia): ";
                cin >> numOrigem;
                cout << "Numero da conta de DESTINO (Quem recebe): ";
                cin >> numDestino;

                achouOrigem = false;
                achouDestino = false;

                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numOrigem && contaAtiva[i]) {
                        achouOrigem = true;
                        
                        cout << "Valor a transferir: R$ ";
                        cin >> valorTransacao;

                        if (valorTransacao > 0 && saldo[i] >= valorTransacao) {
                            for (int j = 0; j < quantidade_contas; j++) {
                                if (numeroConta[j] == numDestino && contaAtiva[j]) {
                                    achouDestino = true;

                                    if (quantidadeMovimentacoes + 2 <= MAX_MOVIMENTACOES) {
                                        saldo[i] = saldo[i] - valorTransacao;
                                        saldo[j] = saldo[j] + valorTransacao;

                                        // Grava Histórico da Conta Origem (Saída 'S')
                                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                                        tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                                        valorMovimentacao[quantidadeMovimentacoes] = valorTransacao;
                                        quantidadeMovimentacoes++;

                                        // Grava Histórico da Conta Destino (Entrada 'D')
                                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[j];
                                        tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                                        valorMovimentacao[quantidadeMovimentacoes] = valorTransacao;
                                        quantidadeMovimentacoes++;

                                        // Atualiza saldos e histórico nos arquivos
                                        salvarContas();
                                        salvarMovimentacoes();

                                        cout << "Transferencia realizada com sucesso!\n";
                                        cout << "Origem (" << nomeCliente[i] << ") - Novo Saldo: R$ " << saldo[i] << "\n";
                                        cout << "Destino (" << nomeCliente[j] << ") - Novo Saldo: R$ " << saldo[j] << "\n";
                                    } else {
                                        cout << "Erro: Limite de memoria do historico cheio!\n";
                                    }
                                    break;
                                }
                            }
                        } else {
                            cout << "Erro: Saldo insuficiente ou valor inválido na conta de origem.\n";
                            achouDestino = true;
                        }
                        break;
                    }
                }

                if (!achouOrigem) {
                    cout << "Erro: Conta de origem nao encontrada ou inativa.\n";
                } else if (!achouDestino) {
                    cout << "Erro: Conta de destino nao encontrada ou inativa.\n";
                }
                break;
                
            case 7:
                cout << "\n--- EXIBIR EXTRATO ---\n";
                cout << "Digite o numero da conta: ";
                cin >> numBusca;

                achou = false;
                teveMovimentacao = false;

                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numBusca && contaAtiva[i]) {
                        achou = true;
                        break;
                    }
                }

                if (achou) {
                    cout << "Movimentacoes encontradas para a conta " << numBusca << ":\n";
                    
                    for (int k = 0; k < quantidadeMovimentacoes; k++) {
                        if (contaMovimentacao[k] == numBusca) {
                            teveMovimentacao = true;
                            
                            if (tipoMovimentacao[k] == 'D') {
                                cout << " [+] Deposito: R$ " << valorMovimentacao[k] << "\n";
                            } else if (tipoMovimentacao[k] == 'S') {
                                cout << " [-] Saque/Saida: R$ " << valorMovimentacao[k] << "\n";
                            }
                        }
                    }
                    
                    if (!teveMovimentacao) {
                        cout << "Nenhuma movimentacao registrada para esta conta ate o momento.\n";
                    }
                } else {
                    cout << "Erro: Conta nao encontrada ou inativa.\n";
                }
                break;
                
            case 8:
                cout << "\nSaindo do sistema... Obrigado por utilizar!\n";
                break;        
        }
        
    } while (opcao != 8);

    return 0;
}

                                    
