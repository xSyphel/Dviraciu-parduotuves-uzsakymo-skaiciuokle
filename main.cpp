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
    fin.ignore(1000, '\n');

    for (int i = 0; i < n; i++)
    {
        getline(fin, kategorijos[i], ';');
        getline(fin, pavadinimai[i], ';');
        fin >> kainos[i];
        fin.ignore();
        fin >> kiekiai[i];
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
        return 0;
    cout << "Nuskaityta prekiu: " << n << endl;

    for (int i = 0; i < n; i++)
        cout << kategorijos[i] << " | " << pavadinimai[i] << " | " << kainos[i] << " | " << kiekiai[i] << endl;

    return 0;
}
