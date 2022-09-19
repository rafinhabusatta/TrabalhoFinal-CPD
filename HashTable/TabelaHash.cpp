#include "TabelaHash.h"

#include <iostream>
#include <algorithm>

//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////
int Mapeamento_Hash(std::string s, int M)
{
    int hash = 0;
    for (int i = 0; i < s.length(); i++) // comparação entre inteiros com e sem sinal aqui (verificar)
        hash = (128 * hash + s[i]) % M;
    return hash;
}
TabelaHash_EndAberto::TabelaHash_EndAberto(unsigned int m) : M(m)
{
    tabela.resize(M);
    for (unsigned int i = 0; i < M; i++)
    {
        tabela[i].ocupado = false;
        tabela[i].registro = NULL;
    }

    totalColisoes = 0;
}

TabelaHash_EndFechado::TabelaHash_EndFechado(unsigned int m, unsigned int t) : M(m), TamanhoBucket(t)
{
    tabelaChaining.resize(M);

    tabelaBuckets.resize(M);
    for (unsigned int i = 0; i < M; i++)
        tabelaBuckets[i].resize(TamanhoBucket);

    totalColisoes = 0;
}

TabelaHash_EndAberto::~TabelaHash_EndAberto()
{
}

TabelaHash_EndFechado::~TabelaHash_EndFechado()
{
}

////////////////////////////
/// ENDERECAMENTO ABERTO ///
////////////////////////////

bool TabelaHash_EndAberto::insereEABL(std::string chave, Registro *reg)
{
    int colisoes = 0;
    bool inseriu = false;

    /// TODO: Completar funcao de insercao em tabela de enderecamento aberto com busca linear
    int e = -1;
    int marca = -1;
    int c = Mapeamento_Hash(chave, M);
    int endc = (c % M);
    int endlivre = endc;

    do
    {
        if (tabela[endlivre].usado == true)
        {
            if (tabela[endlivre].ocupado == true)
            {

                if (tabela[endlivre].chave == chave) /* chave j� existe: encerra */
                {
                    e = endlivre;
                }
                else /* passa para o pr�ximo */
                {
                    endlivre = (endlivre % M) + 1;
                    colisoes += 1;
                }
            }
            else
            {
                if (marca == -1)
                {
                    marca = endlivre;
                }
                endlivre = (endlivre % M) + 1;
            }
        }
        else
        {
            if (marca == -1)
                marca = endlivre;

            break;
        }
    } while ((endlivre != endc) || (e == -1));
    // std::cout << "testeee" << std::endl;
    if ((e == -1) && marca != -1) /* insere no endece�o 'marca' */
    {
        tabela[marca].registro = reg;
        tabela[marca].chave = chave;
        tabela[marca].ocupado = true;
        tabela[marca].usado = true;
        inseriu = true;
    }

    totalColisoes += colisoes;

    return inseriu;
}

Registro *TabelaHash_EndAberto::buscaEABL(std::string chave)
{
    Registro *r = NULL;

    /// TODO: Completar funcao de busca em tabela de enderecamento aberto com busca linear
    int e = -1; // sa�da - posi��o do elemento, retorna -1 se n�o encontrou
    int colisoes = 0;
    int c = Mapeamento_Hash(chave, M);
    int endc = (c % M);
    int endlivre = endc;

    do
    {
        if (tabela[endlivre].ocupado == true)
        {
            // std::cout << "alo" << std::endl;
            // std::cout << ">>>>>>>" << tabela[endlivre].chave << std::endl;
            if ((tabela[endlivre].ocupado == true) && (tabela[endlivre].chave == chave))
            {

                e = endlivre;
                endc = endlivre; /* condi��o de parada do do-while */
                r = tabela[endlivre].registro;
            }
            else
            {
                endlivre = (endlivre % M) + 1; /* vai para o pr�ximo - circular */
            }
        }
        else
        {
            break;
        }
    } while ((endlivre != endc) || (e == -1));

    totalColisoes += colisoes;

    return r;
}

bool TabelaHash_EndAberto::insereDoubleHashing(std::string chave, Registro *reg)
{
    int colisoes = 0;
    bool inseriu = false;

    /// TODO: Completar funcao de insercao em tabela de enderecamento aberto com double hashing
    int e = -1;
    int marca = -1;
    int c = Mapeamento_Hash(chave, M);
    int j = 0;
    int f2 = c % 7;
    int endc = (c % M) + j * f2;
    int endlivre = endc;

    do
    {
        if (tabela[endlivre].usado == true)
        {
            if (tabela[endlivre].ocupado == true)
            {
                if (tabela[endlivre].chave == chave) /* chave j� existe: encerra */
                    e = endlivre;
                else /* passa para o pr�ximo */
                {
                    j += 1;
                    endlivre = (endlivre % M) + j * f2;
                    colisoes += 1;
                }
            }
            else
            {
                if (marca == -1)
                    marca = endlivre;
                endlivre = (endlivre % M) + 1;
            }
        }
        else
        {
            if (marca == -1)
                marca = endlivre;
            break;
        }
    } while ((endlivre != endc) || (e == -1));

    if ((e == -1) && marca != -1) /* insere no endece�o 'marca' */
    {
        tabela[marca].registro = reg;
        tabela[marca].chave = chave;
        tabela[marca].ocupado = true;
        tabela[marca].usado = true;
        inseriu = true;
    }

    totalColisoes += colisoes;

    return inseriu;
}

Registro *TabelaHash_EndAberto::buscaDoubleHashing(std::string chave)
{
    Registro *r = NULL;

    /// TODO: Completar funcao de busca em tabela de enderecamento aberto com double hashing
    int e = -1; // sa�da - posi��o do elemento, retorna -1 se n�o encontrou
    int colisoes = 0;
    int c = Mapeamento_Hash(chave, M);
    int j = 0;
    int f2 = c % 7;
    int endc = (c % M) + j * f2;
    int endlivre = endc;

    do
    {
        if ((tabela[endlivre].ocupado == true) && (tabela[endlivre].chave == chave))
        {
            e = endlivre;
            endc = endlivre; /* condi��o de parada do do-while */
            r = tabela[endlivre].registro;
        }
        else
        {
            // j +=1;
            // endlivre = (endlivre%M) + j*f2;
            endlivre = (endlivre % M) + 1; /* vai para o pr�ximo - circular */
        }

    } while ((endlivre != endc) || (e == -1));

    return r;
}

int TabelaHash_EndAberto::colisoesOcorridas()
{
    return totalColisoes;
}

/////////////////////////////
/// ENDERECAMENTO FECHADO ///
/////////////////////////////

bool TabelaHash_EndFechado::insereChaining(std::string chave, Registro *reg)
{
    int colisoes = 0;
    bool inseriu = false;

    /// TODO: Completar funcao de insercao em tabela de enderecamento fechado com encadeamento (chaining)
    int e = -1;
    int marca = -1;
    int c = Mapeamento_Hash(chave, M);
    int endc = (c % 10);
    // std::cout <<  ">>>>" << endc << "<<<<<" << std::endl;
    int endlivre = endc;
    Elemento aux;
    aux.registro = reg;
    aux.chave = chave;
    aux.ocupado = true;
    aux.usado = true;
    // std::cout << tabelaChaining[endlivre].size() << std::endl;
    int tamprev = tabelaChaining[endlivre].size();
    if (tabelaChaining[endlivre].size() >= 1)
    {
        colisoes += 1;
    }
    tabelaChaining[endlivre].push_back(aux);
    // std::cout << tabelaChaining[endlivre].size() << std::endl;
    if (tamprev < tabelaChaining[endlivre].size()) // comparação entre inteiros com e sem sinal aqui
    {
        inseriu = true;
    }

    // std::cout << tabelaChaining[endlivre].end() << std::endl;

    totalColisoes += colisoes;

    return inseriu;
}

Registro *TabelaHash_EndFechado::buscaChaining(std::string chave)
{
    Registro *r = NULL;
    std::cout << "teste" << std::endl;
    /// TODO: Completar funcao de busca em tabela de enderecamento fechado com encadeamento (chaining)

    int c = Mapeamento_Hash(chave, M);

    // find the key in (index)th list
    std::list<Elemento>::iterator i;

    for (i = tabelaChaining[c].begin();
         i != tabelaChaining[c].end(); i++)
    {
        if ((*i).chave == chave)
            break;
    }

    Elemento aux;
    aux.registro = (*i).registro;
    r = aux.registro;
    // aux.ocupado = true;
    // aux.usado = true;
    // aux.chave = (*i).chave;
    /*int j=0;
    bool flag = false;
    while(j<tabelaChaining[c].size() || !flag){
      aux = tabelaChaining[c].front();
      tabelaChaining[c].pop_front();
      tabelaChaining[c].push_back(aux);
      if(aux.chave == chave){
          r = aux.registro;
          flag=true;
      }
      j++;
    }*/

    return r;
}

bool TabelaHash_EndFechado::insereBuckets(std::string chave, Registro *reg)
{
    int colisoes = 0;
    bool inseriu = false;

    /// TODO: Completar funcao de insercao em tabela de enderecamento fechado com blocos de tamanho fixo (buckets) e area de overflow
    int e = -1;
    int marca = -1;
    int c = Mapeamento_Hash(chave, M);
    int endc = (c % M);
    int endlivre = endc;
    Elemento aux;
    aux.registro = reg;
    aux.chave = chave;
    aux.ocupado = true;
    aux.usado = true;
    if (tabelaBuckets[endlivre].size() > 0)
    {
        colisoes++;
    }
    if (tabelaBuckets[endlivre].size() > 7)
    {
        overflow.push_back(aux);
        inseriu = true;
    }
    else
    {
        tabelaBuckets[endlivre].push_back(aux);
        inseriu = true;
    }

    totalColisoes = overflow.size();
    return inseriu;
}

Registro *TabelaHash_EndFechado::buscaBuckets(std::string chave)
{
    Registro *r = NULL;

    /// TODO: Completar funcao de busca em tabela de enderecamento fechado com blocos de tamanho fixo (buckets) e area de overflow
    int c = Mapeamento_Hash(chave, M);
    // if (std::find(tabelaBuckets[c].begin(), tabelaBuckets[c].end(), chave) != tabelaBuckets[c].end())
    // if(std::find(vec.begin(), vec.end(), item) != vec.end())
    bool achoulocal = false, achouover = false;
    std::vector<Elemento>::iterator it;

    for (it = tabelaBuckets[c].begin();
         it != tabelaBuckets[c].end(); it++)
    {
        if ((*it).chave == chave)
        {
            achoulocal = true;
            break;
        }
    }
    if (!achoulocal)
    {
        for (it = overflow.begin();
             it != overflow.end(); it++)
        {
            if ((*it).chave == chave)
            {
                achouover = true;
                break;
            }
        }
    }
    if (achoulocal || achouover)
    {
        Elemento aux;
        aux.registro = (*it).registro;
        r = aux.registro;
    }

    return r;
}

int TabelaHash_EndFechado::colisoesOcorridas()
{
    return totalColisoes;
}
