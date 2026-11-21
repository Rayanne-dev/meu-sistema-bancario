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
    //Declaração de Variáveis
   int numeroConta, tipoConta, opcao;
   string nomeCliente, cpf, endereco, dataAniversario;
   double saldo;
   bool contaAtiva;
   
   numeroConta = 0;
   saldo = 0;
   tipoConta = 0;
   contaAtiva = false;
   
   //Menu
   do 
   {
   cout << "===========================" << endl;
   cout << "  SISTEMA BANCÁRIO NUBANK  " << endl;
   cout << "===========================" << endl;
   cout << "1 - Cadrastar conta" << endl;
   cout << "2 - Consultar conta" << endl;
   cout << "3 - Verificar saldo" << endl;
   cout << "4 - Alterar tipo da conta" << endl;
   cout << "5 - Ativar/Desativar conta" << endl;
   cout << "6 - sair" << endl;
   
   cout << "\nDigite uma opção: ";
   cin >> opcao;
   
   switch (opcao) {
       case 1:
       cout << "\n********************" << endl;
       cout << "   CADASTRAR CONTA  " << endl;
       cout << "********************" << endl;
       
       cout << " Digite o número da conta: ";
       cin >> numeroConta;
       cin.ignore();
       
       cout << " Digite seu nome completo: ";
       getline(cin, nomeCliente);
      
       
       cout <<" Digite seu cpf: ";
       getline(cin, cpf);
       
       
       cout << " Digite o seu endereço: ";
       getline(cin, endereco);
       
       
       cout << " Digite a data do seu aniversário ultilizando barra: ";
       getline (cin, dataAniversario);
       
       
       cout << " Digite o seu saldo inicial: ";
       cin >> saldo;
       
       cout << " Digite o tipo da sua conta ( 1- Conta Corrente / 2 - Poupança): ";
       cin >> tipoConta;
       
       contaAtiva = true;
       
       cout << " \n Conta cadastrada com sucesso!" << endl;
       break;
       
     case 2:
        cout << "*********************" << endl;
        cout << "    CONSULTAR CONTA  " << endl;
        cout << "*********************" << endl;
        
        cout << " Digite o tipo da sua conta: ";
        cin >> tipoConta;
        
        
        if (tipoConta == 1)
            cout << "Corrente" << endl;
        else
            cout << "Poupança" << endl;
        
        cout << "Status: ";
        
        if (contaAtiva)
            cout << "Ativa" << endl;
        else
            cout << "Inativa" << endl;
        break;
        
    case 3:
        cout << " *****************" << endl;
        cout << "  SALDO BANCÁRIO  " << endl;
        cout << " ***************  " << endl;
        cout << "Saldo atual: R$" << saldo << endl;
    break;
    
    case 4:
        cout << "**************************" << endl;
        cout << " ALTERAR O TIPO DA CONTA  " << endl;
        cout << "**************************" << endl;
        
        cout << "Tipo atual";
        if ( tipoConta == 1 )
            cout << "Corrente" << endl;
        else
            cout <<"Poupança" << endl;
            
        cout << "\nDigite o novo tipo da conta (1 - Corrente / 2 - Poupança): ";
        cin >> tipoConta;
        
        cout << "Tipo da conta alterado com sucesso!" << endl;
        break;
    
    case 5:
    cout << "**************************" << endl;
    cout << "  ATIVAR/DESATIVAR CONTA  " << endl;
    cout << "**************************" << endl;
    
    cout << "1 = Ativar conta" << endl;
    cout << "2 = Desativar Conta" << endl;
    
    int escolha;
    cin >> escolha;
    if (escolha == 1)
    {
        contaAtiva= false;
        cout << "Conta desativada com sucesso!" << endl;
        
    } 
    else if (escolha == 2) {
        contaAtiva = true;
        cout << "Conta ativada com sucesso!" << endl;
    } else {
        cout << "Opção inválida!" << endl;
    }
        
    
    break;
    
    case 6:
    cout <<"\nEncerrando Sistema..." << endl;
    break;
    
   }
   } while (opcao!=6);
 
   
   

    return 0;
}