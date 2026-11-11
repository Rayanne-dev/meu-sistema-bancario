/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
using namespace std;

int main()
{
    //Variaveis
    const int MAX_CONTAS = 150;
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];
    
    const int MAX_MOVIMENTACOES = 150;
    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];
    double valorMovimentacao[MAX_MOVIMENTACOES];
    
    int quantidade_contas = 0;
    int quantidadeMovimentacoes = 0;
    int opcao;
    int numBusca, numOrigem, numDestino;
    double valorTransacao;
    bool achou;
    bool achouOrigem;
    bool achouDestino;
    bool teveMovimentacao;
    
    //MENU
    do{
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
        
        switch (opcao){
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

                achou = false; // Reseta o interruptor para falso

                for (int i = 0; i <quantidade_contas; i++) {
                    if (numeroConta[i] == numBusca && contaAtiva[i]) {
                        // Exibe os dados diretamente usando a posição 'i' encontrada
                        cout << "Conta ativa encontrada!" << endl;
                        cout << "Cliente: " << nomeCliente[i] << "\n";
                        cout << "CPF: " << cpf[i] << "\n";
                        cout << "Saldo atual: R$ " << saldo[i] << "\n";
                        
                        achou = true; 
                        break; // Primeiro break: Interrompe o laço 'for'
                    }
                }

                if (!achou) {
                    cout << "Erro: Conta nao encontrada.\n";
                }
                break; // Segundo break: Finaliza o case 3
                
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
                                // Realiza a operação direto no saldo da posição 'i'
                                saldo[i] = saldo[i] + valorTransacao;

                                // Salva no histórico (Seção 2.4 do PDF)
                                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                                tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                                valorMovimentacao[quantidadeMovimentacoes] = valorTransacao;
                                quantidadeMovimentacoes++;

                                cout << "Deposito realizado! Novo saldo de " << nomeCliente[i] << ": R$ " << saldo[i] << "\n";
                            } else {
                                cout << "Erro: Limite de historico cheio!\n";
                            }
                        } else {
                            cout << "Erro: O valor deve ser maior que zero.\n";
                        }
                        achou = true;
                        break; // Para o laço 'for'
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
                        // Validação obrigatória de saldo direto na posição 'i'
                        if (saldo[i] >= valorTransacao) {
                            if (quantidadeMovimentacoes < MAX_MOVIMENTACOES) {
                                saldo[i] = saldo[i] - valorTransacao;

                                // Salva no histórico como 'S' (Saque)
                                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                                tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                                valorMovimentacao[quantidadeMovimentacoes] = valorTransacao;
                                quantidadeMovimentacoes++;

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
                        break; // Para o laço 'for'
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

                // Primeiro passo: Procurar se a conta de origem existe e está ativa
                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numOrigem && contaAtiva[i]) {
                        achouOrigem = true;
                        
                        cout << "Valor a transferir: R$ ";
                        cin >> valorTransacao;

                        // Verifica se o valor é positivo e se a origem tem saldo suficiente
                        if (valorTransacao > 0 && saldo[i] >= valorTransacao) {
                            
                            // Segundo passo: Procurar a conta de destino ativa
                            for (int j = 0; j < quantidade_contas; j++) {
                                if (numeroConta[j] == numDestino && contaAtiva[j]) {
                                    achouDestino = true;

                                    // Seção 2.5: Verifica se há espaço para duas novas movimentações (+2)
                                    if (quantidadeMovimentacoes + 2 <= MAX_MOVIMENTACOES) {
                                        
                                        // Realiza a transferência direto nos saldos de 'i' (origem) e 'j' (destino)
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

                                        cout << "Transferencia realizada com sucesso!\n";
                                        cout << "Origem (" << nomeCliente[i] << ") - Novo Saldo: R$ " << saldo[i] << "\n";
                                        cout << "Destino (" << nomeCliente[j] << ") - Novo Saldo: R$ " << saldo[j] << "\n";
                                    } else {
                                        cout << "Erro: Limite de memoria do historico cheio!\n";
                                    }
                                    break; // Para o for do 'j' (destino)
                                }
                            }
                        } else {
                            cout << "Erro: Saldo insuficiente ou valor inválido na conta de origem.\n";
                            achouDestino = true; // Evita mostrar a mensagem de erro de destino não encontrado
                        }
                        break; // Para o for do 'i' (origem)
                    }
                }

                // Mensagens de erro caso não encontre as contas
                if (!achouOrigem) {
                    cout << "Erro: Conta de origem nao encontrada ou inativa.\n";
                } else if (!achouDestino) {
                    cout << "Erro: Conta de destino nao encontrada ou inativa.\n";
                }
                break; // Fim do case 6      
                
                
         case 7:
                cout << "\n--- EXIBIR EXTRATO ---\n";
                cout << "Digite o numero da conta: ";
                cin >> numBusca;

                achou = false;
                teveMovimentacao = false;

                // Passo 1: Verificar se a conta existe e está ativa
                for (int i = 0; i < quantidade_contas; i++) {
                    if (numeroConta[i] == numBusca && contaAtiva[i]) {
                        achou = true;
                        break;
                    }
                }

                // Passo 2: Se a conta existe, varre o histórico mostrando apenas as movimentações dela
                if (achou) {
                    cout << "Movimentacoes encontradas para a conta " << numBusca << ":\n";
                    
                    // Seção 2.6: Passa por todo o histórico acumulado
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
                break; // Fim do case 7
                
        case 8:
            cout << "\nSaindo do sistema... Obrigado por utilizar!\n";
            break;        
                
                
        }
        
        
        
    }while (opcao != 8);
    

    return 0;
}