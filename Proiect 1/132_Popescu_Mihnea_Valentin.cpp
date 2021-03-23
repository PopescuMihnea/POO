#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

class numar_complex
{
    double re,im;
public:
    numar_complex(double,double);
    numar_complex();
    numar_complex(const numar_complex&);
    ~numar_complex();
    void set_im(double);
    void set_re(double);
    double get_im() const;
    double get_re() const;
    void afisare() const;
    double modul() const;
    friend istream & operator>>(istream &,numar_complex&);
    friend ostream & operator<<(ostream &,const numar_complex&);
    numar_complex operator+(const numar_complex&) const;
    numar_complex& operator+=(const numar_complex&);
    numar_complex operator-(const numar_complex&) const;
    numar_complex& operator-=(const numar_complex&);
    numar_complex operator*(const numar_complex&) const;
    numar_complex& operator*=(const numar_complex&);
    numar_complex operator/(const numar_complex&) const;
    numar_complex& operator/=(const numar_complex&);
    friend class matrice_complexa;
};

class matrice_complexa
{
    numar_complex **matrice;
    int n,m;
public:
    matrice_complexa();
    matrice_complexa(int,int);
    matrice_complexa(numar_complex,int,int);
    matrice_complexa(const matrice_complexa&);
    ~matrice_complexa();
    int get_n() const;
    int get_m() const;
    numar_complex get_element(int,int) const;
    void set_n(int);
    void set_m(int);
    void citire_n();
    void set_matrix_elements(numar_complex);
    void set_matrix(int,int,numar_complex);
    void set_element(int,int,numar_complex);
    matrice_complexa& operator=(const matrice_complexa&);
    friend istream & operator>>(istream &,matrice_complexa&);
    friend ostream & operator<<(ostream &,const matrice_complexa&);
    matrice_complexa operator+(const matrice_complexa&);
    matrice_complexa& operator+=(const matrice_complexa&);
    matrice_complexa operator*(const matrice_complexa&);
    matrice_complexa& operator*=(const matrice_complexa&);
};

vector<matrice_complexa> matrix_vector;
int x;

matrice_complexa::matrice_complexa(): n(0),m(0)
{

}

matrice_complexa::matrice_complexa(int linii,int coloane): n(linii),m(coloane)
{
    int i;
    this->matrice=new numar_complex*[linii];
    for (i=0; i<linii; i++)
        this->matrice[i]=new numar_complex[coloane];
}

matrice_complexa::matrice_complexa(numar_complex numar,int linii,int coloane): n(linii),m(coloane)
{
    int i,j;
    this->matrice=new numar_complex *[linii];
    for (i=0; i<linii; i++)
    {
        this->matrice[i]=new numar_complex[coloane];
        for(j=0; j<coloane; j++)
            this->matrice[i][j]=numar;
    }
}

matrice_complexa::matrice_complexa(const matrice_complexa &mat): n(mat.n),m(mat.m)
{
    int i,j;
    this->matrice=new numar_complex*[mat.n];
    for (i=0; i<mat.n; i++)
    {
        this->matrice[i]=new numar_complex[mat.m];
        for (j=0; j<mat.m; j++)
            this->matrice[i][j]=mat.matrice[i][j];
    }
}

matrice_complexa::~matrice_complexa()
{
    int i;
    for (i=0; i<this->n; i++)
        delete [] this->matrice[i];
    delete [] this->matrice;
}

int matrice_complexa::get_n() const
{
    return this->n;
}

int matrice_complexa::get_m() const
{
    return this->m;
}

void matrice_complexa::set_n(int linii)
{
    int i;
    this->matrice=new numar_complex*[linii];
    for (i=0; i<linii; i++)
        this->matrice[i]=new numar_complex[this->m];
    this->n=linii;
}

void matrice_complexa::set_m(int coloane)
{
    int i;
    for (i=0; i<this->n; i++)
        this->matrice[i]=new numar_complex [coloane];
    this->m=coloane;
}

void matrice_complexa::citire_n()
{
    int i;
    cout<<"n=";
    cin>>x;
    matrix_vector.resize(x);
    for (i=0; i<x; i++)
    {
        system("CLS");
        cout<<"matricea "<<i+1<<"\n";
        cin>>matrix_vector[i];
    }
    system("CLS");
    for (i=0; i<x; i++)
        cout<<matrix_vector[i]<<"\n\n";
}

void matrice_complexa::set_matrix_elements(numar_complex nrc)
{
    int i,j;
    for (i=0; i<this->n; i++)
        for (j=0; j<this->m; j++)
            this->matrice[i][j]=nrc;
}

void matrice_complexa::set_element(int linie,int coloana,numar_complex nrc)
{
    if (linie<this->n && coloana<this->m)
        this->matrice[linie][coloana]=nrc;
}

void matrice_complexa::set_matrix(int linii,int coloane,numar_complex nrc)
{
    int i,j;
    this->matrice=new numar_complex*[linii];
    for (i=0; i<linii; i++)
    {
        this->matrice[i]=new numar_complex [coloane];
        for (j=0; j<coloane; j++)
            this->matrice[i][j]=nrc;
    }
    this->n=linii;
    this->m=coloane;
}

numar_complex matrice_complexa::get_element(int linie,int coloana) const
{
    numar_complex x;
    try
    {
        if (linie>=this->n || coloana>=this->m)
            throw " elementul nu exista";
        return this->matrice[linie][coloana];
    }
    catch(string s)
    {
        cout<<"Eroare:"<<s<<"\n";
    }
}

matrice_complexa matrice_complexa::operator+(const matrice_complexa &mat)
{
    matrice_complexa temp (*this);
    try
    {
        if (temp.n!=mat.n || temp.m!=mat.m)
            throw " dimensiuni incorecte";
        int i,j;
        for (i=0; i<mat.n; i++)
            for (j=0; j<mat.m; j++)
                temp.matrice[i][j]+=mat.matrice[i][j];
        return temp;
    }
    catch (char const *s)
    {
        cout<<"Eroare:"<<s<<"\n";
    }
}

matrice_complexa& matrice_complexa::operator+=(const matrice_complexa &mat)
{
    try
    {
        if (this->n!=mat.n || this->m!=mat.m)
            throw " dimensiuni incorecte";
        int i,j;
        for (i=0; i<mat.n; i++)
            for (j=0; j<mat.m; j++)
                this->matrice[i][j]+=mat.matrice[i][j];
        return *this;
    }
    catch (char const * s)
    {
        cout<<"Eroare:"<<s<<"\n";
    }

}

matrice_complexa matrice_complexa::operator*(const matrice_complexa& mat)
{
    matrice_complexa temp (*this);
    matrice_complexa aux(temp.n,mat.m);
    numar_complex x;
    try
    {
        if (temp.m!=mat.n)
            throw " nr de coloane m1!=nr de linii m2";
        int i,j,k;
        for (i=0; i<temp.n; i++) //liniile din matrice stanga
            for (j=0; j<mat.m; j++) //coloanele din matrice dreapta
                for (k=0; k<temp.m; k++) //index pt inmultire
                {
                    x=temp.matrice[i][k]*mat.matrice[k][j];
                    aux.matrice[i][j]+=x;
                }
        return aux;
    }
    catch (char const * s)
    {
        cout<<"Eroare:"<<s<<"\n";
    }
}

matrice_complexa& matrice_complexa::operator*=(const matrice_complexa& mat)
{
    matrice_complexa aux(this->n,mat.m);
    numar_complex x;
    try
    {
        if (this->m!=mat.n)
            throw " nr de coloane m1!=nr de linii m2";
        int i,j,k;
        for (i=0; i<this->n; i++) //liniile din matrice stanga
            for (j=0; j<mat.m; j++) //coloanele din matrice dreapta
                for (k=0; k<this->m; k++) //index pt inmultire
                {
                    x=this->matrice[i][k]*mat.matrice[k][j];
                    aux.matrice[i][j]+=x;
                }
        *this=aux;
        return *this;
    }
    catch (char const * s)
    {
        cout<<"Eroare:"<<s<<"\n";
    }

}

matrice_complexa& matrice_complexa::operator=(const matrice_complexa &mat)
{
    this->n=mat.n;
    this->m=mat.m;
    int i,j;
    this->matrice=new numar_complex* [this->n];
    for (i=0; i<this->n; i++)
    {
        this->matrice[i]=new numar_complex[this->m];
        for (j=0; j<this->m; j++)
            this->matrice[i][j]=mat.matrice[i][j];
    }
    return *this;
}

istream & operator>>(istream &in,matrice_complexa& mat)
{

    cout<<"n=";
    in>>mat.n;
    cout<<"m=";
    in>>mat.m;
    int i,j;
    mat.matrice=new numar_complex* [mat.n];
    for (i=0; i<mat.n; i++)
        mat.matrice[i]=new numar_complex[mat.m];
    for (i=0; i<mat.n; i++)
        for (j=0; j<mat.m; j++)
        {
            cout<<"mat ["<<i<<"]["<<j<<"]:"<<"\n";
            in>>mat.matrice[i][j];
        }
    return in;
}

ostream & operator<<(ostream& out,const matrice_complexa &mat)
{
    int i,j;
    for (i=0; i<mat.n; i++)
    {
        for (j=0; j<mat.m; j++)
            out<<mat.matrice[i][j]<<" ";
        out<<"\n";
    }
    return out;
}

numar_complex::numar_complex():re(0),im(0)
{

}

numar_complex::numar_complex(double real,double imaginar): re(real),im(imaginar)
{

}
numar_complex::numar_complex(const numar_complex& nr): re(nr.re),im(nr.im)
{

}
numar_complex::~numar_complex()
{

}
void numar_complex::set_im(double imaginar)
{
    this->im=imaginar;
}
void numar_complex::set_re(double real)
{
    this->re=real;
}

double numar_complex::get_im() const
{
    return (*this).im;
}
double numar_complex::get_re() const
{
    return this->re;
}
void numar_complex::afisare() const
{
    if (this->re)
        if (this->im)
            cout<<this->re<<"+"<<this->im<<"*i\n";
        else
            cout<<this->re;
    else if (this->im)
    {
        cout<<this->im<<"*i";
    }
}



istream & operator>>(istream &in,numar_complex& nrc)
{
    numar_complex temp;
    cout<<"Re(x):";
    in>>nrc.re;
    cout<<"Im(x):";
    in>>nrc.im;
    return in;
}

ostream & operator<<(ostream &out,const numar_complex &nrc)
{
    out<<nrc.re;
    if (nrc.im>=0)
        out<<"+";
    out<<nrc.im<<"*i";
    return out;
}

double numar_complex::modul() const
{
    return sqrt(this->re*this->re+this->im*this->im);
}

numar_complex numar_complex::operator+(const numar_complex & nrc) const
{
    numar_complex temp (*this);
    temp.re+=nrc.re;
    temp.im+=nrc.im;
    return temp;
}

numar_complex& numar_complex::operator+=(const numar_complex & nrc)
{
    this->re+=nrc.re;
    this->im+=nrc.im;
    return *this;
}

numar_complex numar_complex::operator-(const numar_complex &nrc) const
{
    numar_complex temp(*this);
    temp.re-=nrc.re;
    temp.im-=nrc.im;
    return temp;
}

numar_complex& numar_complex::operator-=(const numar_complex&nrc)
{
    this->re+=nrc.re;
    this->im+=nrc.im;
    return *this;
}

numar_complex numar_complex::operator*(const numar_complex &nrc) const
{
    numar_complex temp(*this);
    int aux=temp.re;
    temp.re=temp.re*nrc.re-temp.im*nrc.im;
    temp.im=temp.im*nrc.re+aux*nrc.im;
    return temp;
}

numar_complex& numar_complex::operator*=(const numar_complex &nrc)
{
    int aux=this->re;
    this->re=this->re*nrc.re-this->im*nrc.im;
    this->im=this->im*nrc.re+aux*nrc.im;
    return *this;
}

numar_complex numar_complex::operator/(const numar_complex &nrc) const
{
    numar_complex temp(*this);
    numar_complex aux(nrc.re,-nrc.im),divizor;
    temp*=aux;
    divizor.re=aux.re*nrc.re-aux.im*nrc.im;
    divizor.im=aux.im*nrc.re+aux.re*nrc.im;
    temp.re/=divizor.re;
    temp.im/=divizor.re;
    return temp;
}

numar_complex& numar_complex::operator/=(const numar_complex &nrc)
{
    numar_complex aux(nrc.re,-nrc.im),divizor;
    *this*=aux;
    divizor.re=aux.re*nrc.re-aux.im*nrc.im;
    divizor.im=aux.im*nrc.re+aux.re*nrc.im;
    this->re/=divizor.re;
    this->im/=divizor.re;
    return *this;
}


int main()
{
    char opt;
    numar_complex img_aux;
    matrice_complexa A,B,C;
    int linii,coloane,i,n=0,x;
    bool copiat=false;
    do
    {
        cout<<"1.Citire matrice(1 sau n matrice)\n";
        cout<<"2.Setare numar linii(goleste matricea)\n";
        cout<<"3.Setare numar coloane(goleste matricea)\n";
        cout<<"4.Setare element specific\n";
        cout<<"5.Setare toate elementele\n";
        cout<<"6.Copiere matrice\n";
        cout<<"7.Restaurare instanta veche\n";
        cout<<"8.Adunare\n";
        cout<<"9.Inumltire\n";
        cout<<"0.Afisare\n";
        cout<<"q.Iesire\n";
        cout<<"Optiune: ";
        cin>>opt;
        system("CLS");
        switch (int(opt-'0'))
        {
        case 1:
        {
            cout<<"\t 1.O matrice\n";
            cout<<"\t 2.N matrice\n";
            cout<<"\t Optiune:";
            cin>>opt;
            system("CLS");
            switch (int(opt-'0'))
            {
            case 1:
            {
                cout<<"Introduceti matricea:\n";
                cin>>A;
                cout<<"\n"<<A;
                break;
            }
            case 2:
            {
                matrice_complexa temp;
                temp.citire_n();
                n=x;
                break;
            }
            default:
            {
                cout<<"Optiune invalida \n";
                break;
            }
            }
            break;
        }
        case 2:
        {
            cout<<"Numar linii: ";
            cin>>linii;
            A.set_n(linii);
            cout<<A;
            break;
        }
        case 3:
        {
            cout<<"Setare coloane: ";
            cin>>coloane;
            A.set_m(coloane);
            cout<<A;
            break;
        }
        case 4:
        {
            cout<<"i: ";
            cin>>linii;
            cout<<"j: ";
            cin>>coloane;
            cout<<"Valoare element: \n";
            cin>>img_aux;
            A.set_element(linii,coloane,img_aux);
            cout<<A;
            break;

        }
        case 5:
        {
            cout<<"Valoare elemente: \n";
            cin>>img_aux;
            A.set_matrix_elements(img_aux);
            cout<<A;
            break;
        }
        case 6:
        {
            C=A;
            copiat=true;
            cout<<"Copiat!";
            break;
        }
        case 7:
        {
            if (!copiat)
                cout<<"Nu exista copie\n";
            else
            {
                A=C;
                cout<<"Restaurat!\n";
            }
            break;
        }
        case 8:
        {
            cout<<"Introduceti matricea care va fi adunata: \n";
            cin>>B;
            A+=B;
            cout<<A;
            break;
        }
        case 9:
        {
            cout<<"Introduceti matricea care va fi inmultita: \n";
            cin>>B;
            A*=B;
            cout<<A;
            break;
        }
        case 0:
        {
            cout<<"\t 1.Matricea\n";
            cout<<"\t 2.Vectorul de matrici\n";
            cout<<"\t Optiunea:";
            cin>>opt;
            system("CLS");
            switch (int(opt-'0'))
            {
            case 1:
            {
                cout<<A;
                break;
            }
            case 2:
            {
                if (n)
                    for (i=0; i<n; i++)
                        cout<<matrix_vector[i]<<"\n\n";
                break;
            }
            default:
            {
                cout<<"Optiune invalida \n";
                break;
            }
            }
            break;
        }
        default:
        {
            if (opt!='q')
                cout<<"Optiune invalida \n";
            break;
        }
        }
        if (opt!='q')
        {
            cout<<"\nApasati enter";
            cin.get();
            cin.get();
            system("CLS");
        }
    }
    while(opt!='q');
}
