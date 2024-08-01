#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Transacao {
protected:
    double montante;
    string descricao;

public:
    Transacao(double amt, const string &des) {
        montante = amt;
        descricao = des;
    }

    virtual void display() {
        cout << setw(15) << montante << setw(20) << descricao << endl;
    }
};

class Entrada : public Transacao {
public:
    Entrada(double amt, const string &des) : Transacao(amt, des) {}

    void display() override {
        cout << setw(15) << "Entrada" << setw(20);
        Transacao::display();
    }
};

class Despesa : public Transacao {
public:
    Despesa(double amt, const string &des) : Transacao(amt, des) {}

    void display() override {
        cout << setw(15) << "Despesa" << setw(20);
        Transacao::display();
    }
};

class Investimento {
protected:
    double montante;
    int duracao;

public:
    Investimento(double amt, int dur) {
        montante = amt;
        duracao = dur;
    }

    virtual void display() {
        cout << setw(15) << montante << setw(15) << duracao;
    }

    virtual double andamentoMontante() {
        return montante;
    }
};

class Poupanca : public Investimento {
private:
    double mensal;

public:
    Poupanca(double amt, int dur, double monAmt) : Investimento(amt, dur) {
        mensal = monAmt;
    }

    void display() override {
        cout << setw(15) << "Poupanca";
        Investimento::display();
        cout << setw(20) << mensal << endl;
    }

    double andamentoMontante() override {
        double final = montante * pow(1 + (0.096 / 12), duracao * 12);
        return final + (mensal * 12 * duracao);
    }
};

class CC : public Investimento {
public:
    CC(double amt, int dur) : Investimento(amt, dur) {}

    void display() override {
        cout << setw(15) << "CC";
        Investimento::display();
        cout << endl;
    }

    double andamentoMontante() override {
        return montante * pow((1 + 0.071), duracao);
    }
};

class Gerenciador {
public:
    Transacao *Transacoes[100];
    Investimento *investimentos[50];
    int tcount;
    int icount;

    Gerenciador() {
        tcount = 0;
        icount = 0;
    }

    void addTransacao(Transacao *t) {
        Transacoes[tcount++] = t;
    }

    void addInvestimento(Investimento *i) {
        investimentos[icount++] = i;
    }

    void displayRecord(double Balanco) {
        cout << "-----------------------------------\n";
        cout << "|        Finanças Pessoais        |\n";
        cout << "-----------------------------------\n";

        cout << "\n||--Balanco--: " << Balanco << "||" << endl;

        cout << "\n--Fluxo de caixa--: \n";
        cout << setw(15) << "Tipo" << setw(15) << "Montante" << setw(20) << "Descricao" << endl;
        for (int i = 0; i < tcount; i++) {
            Transacoes[i]->display();
        }

        cout << "\n--Investimentos--\n";
        cout << setw(15) << "Tipo" << setw(15) << "Montante" << setw(15) << "Duracao" << setw(30) << "Montante mensal investido" << endl;
        for (int i = 0; i < icount; i++) {
            investimentos[i]->display();
        }
    }
};

class User {
public:
    Gerenciador manager;
    double Balanco;

    User() {
        int numMembros;
        cout << "Digite quantas pessoas tem no seu núcleo familiar: ";
        cin >> numMembros;
        double rendafamiliar = 0.0;
        for (int i = 0; i < numMembros; i++) {
            double renda;
            cout << "Digite a renda da pessoa " << i + 1 << ": ";
            cin >> renda;
            rendafamiliar += renda;
        }
        Balanco = rendafamiliar;
    }

    void operacoes() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n--OPCOES--\n";
            cout << "1. ENTRADAS\n";
            cout << "2. DESPESAS\n";
            cout << "3. INVESTIMENTOS\n";
            cout << "4. INFORMACOES FINANCEIRAS\n";
            cout << "5. INFORMACOES DE INVESTIMENTO\n";
            cout << "0. Sair\n";
            cout << "Escolha : ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amt;
                    string desc;
                    cout << "Qual o valor adquirido? ";
                    cin >> amt;
                    cout << "Qual descrição gostaria de atribuir a esse ganho? ";
                    cin.ignore();
                    getline(cin, desc);
                    cout << "Saldo atual: " << Balanco << endl;
                    Balanco += amt;
                    manager.addTransacao(new Entrada(amt, desc));
                    cout << "Novo saldo: " << Balanco << endl;
                    break;
                }

                case 2: {
                    double amt;
                    string desc;
                    cout << "Digite o valor da despesa: ";
                    cin >> amt;
                    cout << "\nEm qual categoria pertence a despesa?\n";
                    cout << "1. Contas e Habitação\n";
                    cout << "2. Feira e Alimentação\n";
                    cout << "3. Transporte e Passagens\n";
                    cout << "4. Saúde e Higiene Pessoal\n";
                    cout << "5. Educação e Assinaturas\n";
                    cout << "6. Lazer e Restaurantes\n";
                    cout << "7. Compras, Utensílios e Variedades\n";
                    cout << "8. Outros\n";
                    cout << "0. Sair\n";
                    cout << "Escolha: ";
                    int opcao;
                    cin >> opcao;
                    switch (opcao) {
                        case 1:
                            desc = "Contas e Habitação"; // Contempla alugueis, contas da casa e gastos de infraestrutura.
                            break;
                        case 2:
                            desc = "Feira e Alimentação"; // Contempla mercado e similares.
                            break;
                        case 3:
                            desc = "Transporte e Passagens"; // Contempla gastos com combustivel, transporte público, ubers ou até mesmo passagens aéreas.
                            break;
                        case 4:
                            desc = "Saúde e Higiene Pessoal"; // Contempla gastos médicos, procedimentos de cuidados, academia, barbeiro, pedicure/manicure e afins.
                            break;
                        case 5:
                            desc = "Educação e Assinaturas";  // Contempla escola, cursos, universidade ou até mesmo assinaturas de streamings e afins, estão na mesma categoria porque são mensalidades. 
                            break;
                        case 6:
                            desc = "Lazer e Restaurantes"; // Contempla gastos de cinemas, bares, estabelecimentos de comer fora e outras modalidades de entretenimento.
                            break;
                        case 7:
                            desc = "Compras, Utensílios e Variedades"; // Contempla de modo geral gastos com lojas e todas suas vertentes.
                            break;
                        case 8:
                            desc = "Outros"; // Tudo aquilo que não se encaixar nos citados anteriormente.
                            break;
                        case 0:
                            continue;
                        default:
                            cout << "Opção inválida!" << endl;
                            continue;
                    }
                    cout << "Saldo atual: " << Balanco << endl;
                    Balanco -= amt;
                    manager.addTransacao(new Despesa(amt, desc));
                    cout << "Novo saldo: " << Balanco << endl;
                    break;
                }

                case 3: {
                    makeInvestimento();
                    break;
                }

                case 4: {
                    manager.displayRecord(Balanco);
                    break;
                }

                case 5: {
                    cout << "--Total montante--||\n";
                    for (int i = 0; i < manager.icount; i++) {
                        Investimento *inv = manager.investimentos[i];
                        cout << "\nInvestimento " << i + 1 << " : " << inv->andamentoMontante() << " R$" << endl;
                        cout << setw(15) << "Tipo" << setw(15) << "Montante" << setw(20) << "Duração" << setw(30) << "Montante mensal investido" << endl;
                        inv->display();
                    }
                    break;
                }

                case 0:
                    break;

                default:
                    cout << "\nSem opção disponível :(";
                    break;
            }
        }
    }

    void makeInvestimento() {
        int sub = -1;
        while (sub != 0) {
            cout << "\nQual das opções:\n";
            cout << "1. Poupanca\n";
            cout << "2. CC\n";
            cout << "0. Voltar\n";
            cout << "Digite sua escolha : ";
            cin >> sub;

            switch (sub) {
                case 1: {
                    double amt, mensal;
                    int dur;
                    cout << "Digite montante : ";
                    cin >> amt;
                    if (Balanco - amt < 1000) {
                        cout << "Erro: Min Balanco = 1000";
                        return;
                    }
                    cout << "Digite a duração em anos : ";
                    cin >> dur;
                    cout << "Digite o investimento mensal : ";
                    cin >> mensal;
                    manager.addInvestimento(new Poupanca(amt, dur, mensal));
                    Balanco -= amt;
                    break;
                }

                case 2: {
                    double amt;
                    int dur;
                    cout << "Digite montante : ";
                    cin >> amt;
                    if (Balanco - amt < 1000) {
                        cout << "Erro: Min Balanco = 1000";
                        return;
                    }
                    cout << "Digite a duração em anos : ";
                    cin >> dur;
                    manager.addInvestimento(new CC(amt, dur));
                    Balanco -= amt;
                    break;
                }

                case 0:
                    break;

                default:
                    cout << "Escolha inválida.";
                    break;
            }
        }
    }
};

int main() {
    cout << "---Bem vindo(a) ao Sistema de Gerenciamento Financeiro!!---\n";
    User user;
    user.operacoes();

    return 0;
}
