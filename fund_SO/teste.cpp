#include <iostream>
#include <queue>

using namespace std;

class Processo
{
private:
    int id;
    int tempoRestante;
    int prioridade;

public:
    Processo() : id(-1), tempoRestante(0), prioridade(-1) {}
    
    Processo(int id_) : id(id_), tempoRestante(id_ * 10), prioridade(-1) {}

    int getTempoRestante() const { return tempoRestante; }
    int getId() const { return id; }
    
    void executaProcesso() { tempoRestante -= 10; }
    
    void setPrioridade(int x) { prioridade = x; }
    int getPrioridade() const { return prioridade; }
};

int main()
{
    int tempoTotal = 0;
    int qntProcessos, idProcesso, pAcao;

    queue<Processo> fila;
    cin >> qntProcessos;

    for (int i = 0; i < qntProcessos; i++)
    {
        cin >> idProcesso;
        Processo p(idProcesso);
        fila.push(p);
    }

    while (!fila.empty())
    {
        Processo Patual = fila.front();
        fila.pop();

        if (Patual.getPrioridade() == 1)
        {
            Patual.executaProcesso();
            tempoTotal += 10;
            Patual.setPrioridade(-1);

            if (Patual.getTempoRestante() == 0)
            {
                cout << Patual.getId() << " (" << tempoTotal << ")" << endl;
            }
            else
            {
                fila.push(Patual);
            }
        }
        else
        {
            cin >> pAcao;

            if (pAcao == 1)
            {
                Patual.setPrioridade(1);
                fila.push(Patual);
            }
            else
            {
                Patual.executaProcesso();
                tempoTotal += 10;

                if (Patual.getTempoRestante() == 0)
                {
                    cout << Patual.getId() << " (" << tempoTotal << ")" << endl;
                }
                else
                {
                    fila.push(Patual);
                }
            }
        }
    }

    return 0;
}
