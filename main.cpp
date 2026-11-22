#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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

double eilutesSuma(double kaina, int kiekis)
{
    return kaina * kiekis;
}

double nuolaida(double suma, int kiekis)
{
    if (kiekis >= 10)
        return suma * 0.1;
    else
        return 0;
}

void spausdintiPrekes(ostream &out, string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[], int n, string kategorija)
{
    out << fixed << setprecision(2);
    out << left << setw(12) << "Kategorija" << setw(47) << "Pavadinimas"
        << right << setw(10) << "Kaina" << setw(8) << "Kiekis" << setw(12) << "Suma"
        << setw(11) << "Nuolaida" << setw(12) << "Moketi" << endl;
    out << string(112, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        if (kategorija == "" || kategorijos[i] == kategorija)
        {
            double suma = eilutesSuma(kainos[i], kiekiai[i]);
            double nuol = nuolaida(suma, kiekiai[i]);
            out << left << setw(12) << kategorijos[i] << setw(47) << pavadinimai[i]
                << right << setw(10) << kainos[i] << setw(8) << kiekiai[i] << setw(12) << suma
                << setw(11) << nuol << setw(12) << suma - nuol << endl;
        }
    }
    out << string(112, '-') << endl;
}

int ivestiPasirinkima(int nuo, int iki)
{
    int x;
    while (true)
    {
        cout << "Pasirinkite (" << nuo << "-" << iki << "): ";
        cin >> x;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Reikia ivesti skaiciu!" << endl;
        }
        else if (x < nuo || x > iki)
        {
            cin.ignore(1000, '\n');
            cout << "Tokio pasirinkimo nera!" << endl;
        }
        else
        {
            cin.ignore(1000, '\n');
            return x;
        }
    }
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
        cout << "Programa baigia darba" << endl;
        return 0;
    }
    cout << "Nuskaityta prekiu: " << n << endl;

    int pasirinkimas;
    do
    {
        cout << endl;
        cout << "1. Perziureti visas uzsakymo prekes" << endl;
        cout << "2. Perziureti pasirinktos kategorijos prekes" << endl;
        cout << "3. Perziureti viso uzsakymo sumas" << endl;
        cout << "4. Perziureti sumas pagal kategorijas" << endl;
        cout << "5. Parodyti visa uzsakymo ataskaita" << endl;
        cout << "6. Issaugoti visa ataskaita i faila" << endl;
        cout << "7. Iseiti" << endl;
        pasirinkimas = ivestiPasirinkima(1, 7);
        cout << endl;

        switch (pasirinkimas)
        {
        case 1:
            spausdintiPrekes(cout, kategorijos, pavadinimai, kainos, kiekiai, n, "");
            break;
        case 2:
            cout << "Dar nepadaryta" << endl;
            break;
        case 3:
            cout << "Dar nepadaryta" << endl;
            break;
        case 4:
            cout << "Dar nepadaryta" << endl;
            break;
        case 5:
            cout << "Dar nepadaryta" << endl;
            break;
        case 6:
            cout << "Dar nepadaryta" << endl;
            break;
        case 7:
            cout << "iseiti" << endl;
            break;
        }
    } while (pasirinkimas != 7);

    return 0;
}
