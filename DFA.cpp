#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int n, m, q0, k, finale[100], l, a, b, tranzitii[100][100], nrcuvinte;
char alfabet[100], c, cuvant[100], cuvinte[100][100];
int gaseste_poz(char c, char alfabet[], int m)
{
    for (int i=0;  i<m; i++)
        if (alfabet[i] == c)
            return i;
    return -1;
}
int main() {
    ifstream f("DFA.in");
    ofstream g("DFA.out");
    f >> n >> m;
    for(int i=0; i<=100; i++)
        for(int j=0; j<=100; j++)
            tranzitii[i][j] = -1;
    for (int i = 0; i < m; i++)
        f >> alfabet[i];

    f >> q0;
    f >> k;
    for(int i = 0; i < k; i++)
        f >> finale[i];
    f >> l;

    for(int i = 0; i < l; i++)
    {
        f >> a;
        f >> c;
        f >> b;
        tranzitii[a][gaseste_poz(c,alfabet,m)] = b;
    }

    f >> nrcuvinte;
    for(int it = 0; it <= nrcuvinte; it++)
    {
        f.getline(cuvant, 100);
        strcpy(cuvinte[it], cuvant);
    }

    for (int it = 1; it <= nrcuvinte;it++)
    {
        strcpy(cuvant, cuvinte[it]);
        int p = 0, stare_curenta = 0;

        while(p < strlen(cuvant)-1 && tranzitii[stare_curenta][gaseste_poz(cuvant[p], alfabet, m)]!=-1)
        {
            stare_curenta = tranzitii[stare_curenta][gaseste_poz(cuvant[p], alfabet, m)];
            p++;
        }

        if (p == strlen(cuvant)-1)
        {
            int ok = 0;
            for(int i = 0; i < k && ok == 0; i++)
                if (stare_curenta == finale[i])
                    ok=1;
            if (ok != 1)
                g << cuvant << "False" << '\n';
            else
                g << cuvant << "True" << '\n';
        } else
            g << cuvant << "False" << '\n';}

    return 0;
}
