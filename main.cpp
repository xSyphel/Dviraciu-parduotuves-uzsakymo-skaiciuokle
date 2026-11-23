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

double sumaPriesNuolaidas(double kainos[], int kiekiai[], int n)
{
    double suma = 0;
    for (int i = 0; i < n; i++)
        suma += eilutesSuma(kainos[i], kiekiai[i]);
    return suma;
}

double visosNuolaidos(double kainos[], int kiekiai[], int n)
{
    double suma = 0;
    for (int i = 0; i < n; i++)
        suma += nuolaida(eilutesSuma(kainos[i], kiekiai[i]), kiekiai[i]);
    return suma;
}

double kategorijosSuma(string kategorijos[], double kainos[], int kiekiai[], int n, string kategorija)
{
    double suma = 0;
    for (int i = 0; i < n; i++)
    {
        if (kategorijos[i] == kategorija)
        {
            double s = eilutesSuma(kainos[i], kiekiai[i]);
            suma += s - nuolaida(s, kiekiai[i]);
        }
    }
    return suma;
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

void spausdintiSumas(ostream &out, double kainos[], int kiekiai[], int n)
{
    double pries = sumaPriesNuolaidas(kainos, kiekiai, n);
    double nuol = visosNuolaidos(kainos, kiekiai, n);

    out << fixed << setprecision(2);
    out << left << setw(30) << "Suma pries nuolaidas:" << right << setw(12) << pries << " Eur" << endl;
    out << left << setw(30) << "Nuolaidu suma:" << right << setw(12) << nuol << " Eur" << endl;
    out << left << setw(30) << "Moketina suma:" << right << setw(12) << pries - nuol << " Eur" << endl;
}

void spausdintiKategorijuSumas(ostream &out, string kategorijos[], double kainos[], int kiekiai[], int n)
{
    string pav[3] = {"Dviraciai", "Dalys", "Aksesuarai"};

    out << fixed << setprecision(2);
    for (int k = 0; k < 3; k++)
    {
        out << left << setw(30) << pav[k] + ":" << right << setw(12)
            << kategorijosSuma(kategorijos, kainos, kiekiai, n, pav[k]) << " Eur" << endl;
    }
}

void spausdintiAtaskaita(ostream &out, string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[], int n)
{
    out << "========== UZSAKYMO ATASKAITA ==========" << endl << endl;
    out << "Prekes:" << endl;
    spausdintiPrekes(out, kategorijos, pavadinimai, kainos, kiekiai, n, "");
    out << endl << "Viso uzsakymo sumos:" << endl;
    spausdintiSumas(out, kainos, kiekiai, n);
    out << endl << "Sumos pagal kategorijas (po nuolaidu):" << endl;
    spausdintiKategorijuSumas(out, kategorijos, kainos, kiekiai, n);
}

void issaugotiAtaskaita(string failas, string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[], int n)
{
    ofstream fout(failas);
    if (!fout)
    {
        cout << "Nepavyko sukurti failo " << failas << endl;
        return;
    }

    spausdintiAtaskaita(fout, kategorijos, pavadinimai, kainos, kiekiai, n);
    fout.close();

    if (fout.fail())
        cout << "Nepavyko irasyti ataskaitos i faila" << endl;
    else
        cout << "Ataskaita issaugota faile " << failas << endl;
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

void rodytiKategorija(string kategorijos[], string pavadinimai[], double kainos[], int kiekiai[], int n)
{
    string pav[3] = {"Dviraciai", "Dalys", "Aksesuarai"};

    cout << "1. Dviraciai" << endl;
    cout << "2. Dalys" << endl;
    cout << "3. Aksesuarai" << endl;
    string kategorija = pav[ivestiPasirinkima(1, 3) - 1];
    cout << endl;

    int kiek = 0;
    for (int i = 0; i < n; i++)
    {
        if (kategorijos[i] == kategorija)
            kiek++;
    }

    if (kiek == 0)
    {
        cout << "Kategorijoje " << kategorija << " prekiu nera" << endl;
        return;
    }

    spausdintiPrekes(cout, kategorijos, pavadinimai, kainos, kiekiai, n, kategorija);
    cout << fixed << setprecision(2);
    cout << "Kategorijos " << kategorija << " moketina suma: "
         << kategorijosSuma(kategorijos, kainos, kiekiai, n, kategorija) << " Eur" << endl;
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
            rodytiKategorija(kategorijos, pavadinimai, kainos, kiekiai, n);
            break;
        case 3:
            spausdintiSumas(cout, kainos, kiekiai, n);
            break;
        case 4:
            spausdintiKategorijuSumas(cout, kategorijos, kainos, kiekiai, n);
            break;
        case 5:
            spausdintiAtaskaita(cout, kategorijos, pavadinimai, kainos, kiekiai, n);
            break;
        case 6:
            issaugotiAtaskaita("ataskaita.txt", kategorijos, pavadinimai, kainos, kiekiai, n);
            break;
        case 7:
            cout << "Bye bye" << endl;
            break;
        }
    } while (pasirinkimas != 7);

    return 0;
}
