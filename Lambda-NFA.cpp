#include <iostream>
#include<fstream>
#include <cstring>
using namespace std;
struct nod {
    int lung;
    int v[100];
};
int n, m, q0, k, l, a, b, lcurente, nrcuvinte;
char alfabet[100], c, cuvant[100], cuvinte[100][100];
int finale[100], stari_curente[100];
nod tranzitii[100][100];

int gaseste_poz(char c, char alfabet[], int m)
{
    for (int i=0;  i<m; i++)
        if (alfabet[i] == c)
            return i;
    return -1;
}
int main() {
    ifstream f("NFA.in");
    ofstream g("NFA.out");
    f >> n >> m;

    for (int i = 0; i < m; i++)
        f >> alfabet[i];
    f >> q0 >> k;

    for (int i = 0; i < k; i++)
    {   int x;
        f >> x;
        finale[i]=x;
    }
    f >> l;

    for (int i = 0; i < l; i++)
    {
        f >> a >> c >> b;
        int s = gaseste_poz(c,alfabet,m);
        if (c!='$')
        {
            int lungime = tranzitii[a][s+1].lung;
            tranzitii[a][s+1].v[lungime]= b;
            tranzitii[a][s+1].lung++;
        }
        else
        {
            int lungime = tranzitii[a][0].lung;
            tranzitii[a][0].v[lungime] = b;
            tranzitii[a][0].lung++;
        }
    }

    f >> nrcuvinte;
    for(int it = 0; it <= nrcuvinte; it++)
    {
        f.getline(cuvant, 100);
        strcpy(cuvinte[it], cuvant);
    }

    for (int it = 1; it <= nrcuvinte;it++)
    {   strcpy(cuvant, cuvinte[it]);
        int p = 0;
        lcurente = 1;
        stari_curente[0] = q0;
        while ( p < strlen(cuvant)-1)
        {
            int aux[100], laux=0; int lambdaux[100],lambda=0;
            int s = gaseste_poz(cuvant[p],alfabet,m);
            for (int j = 0; j < lcurente; j++)
            {
                for (int i = 0; i < tranzitii[stari_curente[j]][s + 1].lung; i++)
                {
                    aux[laux] = tranzitii[stari_curente[j]][s+ 1].v[i];
                    laux++;
                }
                for (int i = 0; i< tranzitii[stari_curente[j]][0].lung; i++)
                {
                    lambdaux[lambda] = tranzitii[stari_curente[j]][0].v[i];
                    lambda++;
                }
            }
            for(int i = 0; i < laux; i++)
                stari_curente[i] = aux [i];
            lcurente = laux;

            while (lambda)
            {    int add = lambda;

                for(int i = 0; i< lambda; i++)
                {
                    for (int j = 0; j < tranzitii[lambdaux[i]][s + 1].lung; j++)
                    {
                        stari_curente[lcurente] = tranzitii[lambdaux[i]][s + 1].v[j];
                        lcurente++;
                    }
                    for (int j = 0; j < tranzitii[lambdaux[i]][0].lung; j++)
                    {
                        lambdaux[add] = tranzitii[lambdaux[i]][0].v[j];
                        add++;

                    }

                }
                if(lambda != add)
                {
                    for(int i = lambda; i < add; i++)
                        lambdaux[i-lambda] = lambdaux[i];
                    lambda = add;}
                else
                    lambda = 0;

            }

            p++;
        }
        int ok = 0;
        for (int i = 0; i < lcurente && ok == 0; i++)
            for(int j = 0; j < k && ok == 0; j++)
                if (finale[j] == stari_curente[i])
                    ok=1;
        if (ok == 1)
            g << cuvant << " True " << '\n';
        else
            g << cuvant << " False" << '\n'; }

    f.close();
    g.close();
    return 0;
}