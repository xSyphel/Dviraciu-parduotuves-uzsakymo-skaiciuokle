#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 100;

int nuskaitytiDuomenis(string failas, string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[])
{
    ifstream fin(failas);
    if (!fin)
    {
        cout << "Nepavyko atidaryti failo " << failas << endl;
        return 0;
    }

    int n;
    fin >> n;
    if (fin.fail())
    {
        cout << "Pirmoje eiluteje turi buti irasu skaicius" << endl;
        return 0;
    }
    if (n < 1 || n > MAX)
    {
        cout << "Irasu skaicius turi buti nuo 1 iki " << MAX << endl;
        return 0;
    }
    fin.ignore(1000, '\n');

    for (int i = 0; i < n; i++)
    {
        getline(fin, kategorijos[i], ';');
        getline(fin, pavadinimai[i], ';');
        if (fin.fail())
        {
            cout << "Faile nurodyta " << n << " irasu, bet rasta tik " << i << endl;
            return 0;
        }

        if (kategorijos[i] != "Dviraciai" && kategorijos[i] != "Dalys" && kategorijos[i] != "Aksesuarai")
        {
            cout << "Netinkama kategorija " << i + 1 << " irase: " << kategorijos[i] << endl;
            return 0;
        }

        fin >> kainos[i];
        if (fin.fail() || kainos[i] <= 0)
        {
            cout << "Netinkama kaina " << i + 1 << " irase" << endl;
            return 0;
        }
        fin.ignore();

        double kiekis;
        fin >> kiekis;
        if (fin.fail() || kiekis <= 0 || kiekis != (int)kiekis)
        {
            cout << "Netinkamas kiekis " << i + 1 << " irase" << endl;
            return 0;
        }
        kiekiai[i] = (int)kiekis;
        fin.ignore(1000, '\n');
    }

    fin.close();
    return n;
}

int main()
{
    string kategorijos[MAX];
    string pavadinimai[MAX];
    double kainos[MAX];
    int kiekiai[MAX];

    int n = nuskaitytiDuomenis("uzsakymas.txt", kategorijos, pavadinimai, kainos, kiekiai);
    if (n == 0)
    {
        cout << "Programa daro stop" << endl;
        return 0;
    }
    cout << "Nuskaityta prekiu: " << n << endl;

    for (int i = 0; i < n; i++)
        cout << kategorijos[i] << " | " << pavadinimai[i] << " | " << kainos[i] << " | " << kiekiai[i] << endl;

    return 0;
}
