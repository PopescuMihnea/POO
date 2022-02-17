#include <iostream>
#include <string.h>
#include <typeinfo>
using namespace std;

class Locuinta
{
protected:
    string numeClient;
    int suprafataUtila;
    float discount;
    static int nrLocuinte;
public:
    Locuinta(string nume="",int suprafata=0,float discount=0): numeClient(nume),suprafataUtila(suprafata),discount(discount)
    {
        ++nrLocuinte;
    }
    Locuinta (Locuinta& loc): numeClient(loc.numeClient),suprafataUtila(loc.suprafataUtila),discount(loc.discount)
    {
        ++nrLocuinte;
    }
    virtual ~Locuinta()
    {
        --nrLocuinte;
        this->numeClient=this->suprafataUtila=this->discount=0;
    }
    void setNumeClient(const string);
    static int getNrLocuinte();
    string getNumeClient() const;
    void setSuprafata(const int);
    int getSuprafata() const;
    void setDiscount(const float);
    float getDiscount() const;
    virtual int calculChirie(const int,const int) const=0;
    Locuinta& operator =(const Locuinta &);
    friend istream& operator>>(istream &,Locuinta &);
    friend ostream& operator<<(ostream &,const Locuinta &);
};

int Locuinta::nrLocuinte=0;

int Locuinta::getNrLocuinte()
{
    return nrLocuinte;
}

void Locuinta::setNumeClient(const string nume)
{
    this->numeClient=nume;
}

string Locuinta::getNumeClient() const
{
    return this->numeClient;
}

void Locuinta::setSuprafata(const int suprafata)
{
    this->suprafataUtila=suprafata;
}

int Locuinta::getSuprafata() const
{
    return this->suprafataUtila;
}

void Locuinta::setDiscount(const float discount)
{
    this->discount=discount;
}

float Locuinta::getDiscount() const
{
    return this->discount;
}

Locuinta& Locuinta::operator =(const Locuinta &loc)
{
    this->numeClient=loc.numeClient;
    this->suprafataUtila=loc.suprafataUtila;
    this->discount=loc.discount;
    return *this;
}

istream & operator>>(istream &in,Locuinta &loc)
{
    ++Locuinta::nrLocuinte;
    cout<<"Nume client: ";
    in.get();
    getline(in,loc.numeClient);
    cout<<"\nSuprafata utila: ";
    in>>loc.suprafataUtila;
    cout<<"\nDiscount: ";
    in>>loc.discount;
    return in;
}

ostream & operator<<(ostream &out,const Locuinta & loc)
{
    cout<<"Nume client: "<<loc.numeClient;
    cout<<"\nSuprafata utila: "<<loc.suprafataUtila;
    cout<<"\nDiscount: "<<loc.discount;
    return out;
}

class Apartament: public Locuinta
{
    int etaj;
    static int nrApartamente;
public:
    Apartament(string nume="",int suprafata=0,float discount=0,int etaj=-1):Locuinta(nume,suprafata,discount), etaj(etaj)
    {
        ++nrApartamente;
    }
    Apartament(Apartament & ap):Locuinta(ap),etaj(ap.etaj)
    {
        ++nrApartamente;
    }
    ~Apartament()
    {
        --nrApartamente;
        etaj=-1;
    }
    void setEtaj(const int);
    static int getNrApartamente();
    int getEtaj() const;
    int calculChirie(const int, const int) const;
    Apartament & operator=(const Apartament &);
    friend istream & operator>>(istream &,Apartament&);
    friend ostream & operator<<(ostream &,Apartament &);
};

int Apartament::nrApartamente=0;

void Apartament::setEtaj(const int etaj)
{
    this->etaj=etaj;

}
int Apartament::getNrApartamente()
{
    return nrApartamente;
}

int Apartament::getEtaj() const
{
    return this->etaj;
}

int Apartament::calculChirie(const int X,const int Y=0) const
{
    return X*this->getSuprafata()*(1-Y*this->getDiscount()/100.0);
}

Apartament & Apartament::operator=(const Apartament& ap)
{
    this->numeClient=ap.numeClient;
    this->suprafataUtila=ap.suprafataUtila;
    this->discount=ap.discount;
    this->etaj=ap.etaj;
    return *this;
}

istream & operator>>(istream &in,Apartament &ap)
{
    ++Apartament::nrApartamente;
    in>>dynamic_cast<Locuinta&>(ap);
    cout<<"\nEtaj: ";
    in>>ap.etaj;
    return in;
}

ostream & operator<<(ostream &out,Apartament &ap)
{
    out<<dynamic_cast<Locuinta&>(ap);
    cout<<"\nEtaj: ";
    out<<ap.etaj;
    return out;
}

class Casa:public Locuinta
{
    int suprafataCurte;
    static int nrCase;
public:
    Casa(string nume="",int suprafataUtila=0,float discount=0,int suprafataCurte=0):Locuinta(nume,suprafataUtila,discount),suprafataCurte(suprafataCurte)
    {
        ++nrCase;
    }
    Casa (Casa & c):Locuinta(c),suprafataCurte(c.suprafataCurte)
    {
        ++nrCase;
    }
    ~Casa()
    {
        --nrCase;
        suprafataCurte=0;
    }
    Casa & operator=(Casa&);
    friend istream & operator>>(istream &,Casa &);
    friend ostream & operator<<(ostream &,Casa &);
    void setSuprafataCurte(const int);
    int calculChirie(const int,const int) const;
    int getSuprafataCurte() const;
    static int getNrCase();
};

int Casa::nrCase=0;

Casa & Casa::operator=(Casa& ca)
{
    this->numeClient=ca.numeClient;
    this->suprafataUtila=ca.suprafataUtila;
    this->discount=ca.discount;
    this->suprafataCurte=ca.suprafataCurte;
    return *this;
}

istream & operator >> (istream &in,Casa &ca)
{
    in>>dynamic_cast<Locuinta&>(ca);
    cout<<"\nSuprafata curte: ";
    in>>ca.suprafataCurte;
    return in;
}

ostream & operator<<(ostream &out,Casa &ca)
{
    ++Casa::nrCase;
    out<<dynamic_cast<Locuinta&>(ca);
    out<<"\nSuprafata curte: "<<ca.suprafataCurte;
    return out;
}

void Casa::setSuprafataCurte(const int suprafata)
{
    this->suprafataCurte=suprafata;
}

int Casa::calculChirie(const int X,const int Y=0) const
{
    return X*(this->getSuprafata()+0.2*this->suprafataCurte)*(1-Y*this->getDiscount()/100.0);
}

int Casa::getSuprafataCurte() const
{
    return this->suprafataCurte;
}

int Casa::getNrCase()
{
    return nrCase;
}

class agentieImobiliara
{
    Locuinta **v;
    static int nrLocuinteAgentie;
    int nrLocuinte;
    int alocate;
public:
    agentieImobiliara(int nr=0,string nume="",int suprafata=0,float discount=0,int opt=1)
    {
        this->v=new Locuinta*[nr];
        nrLocuinteAgentie+=nr;
        this->nrLocuinte=nr;
        this->alocate=nr;
        if (opt==1)
            for (int i=0; i<nr; ++i)
                v[i]=new Casa(nume,suprafata,discount);
        else
            for (int i=0; i<nr; ++i)
                v[i]=new Apartament(nume,suprafata,discount);
    }
    agentieImobiliara(agentieImobiliara& ag):nrLocuinte(ag.nrLocuinte),alocate(ag.alocate)
    {
        nrLocuinteAgentie+=ag.nrLocuinte;
        this->v=new Locuinta*[ag.alocate];
        for (int i=0; i<this->nrLocuinte; ++i)
        {
            try
            {
                this->v[i]=new Casa(dynamic_cast<Casa&>(*ag.v[i]));
            }
            catch (std::bad_cast)
            {
                this->v[i]=new Apartament(dynamic_cast<Apartament&>(*ag.v[i]));
            }
        }
    }
    Locuinta &operator[](const unsigned) const;
    ~agentieImobiliara()
    {
        for (int i=0; i<this->nrLocuinte; ++i)
        {
            delete v[i];
        }
        delete []v;
    }
    void insertElement(Locuinta*);
    void insertElement(Locuinta &);
    void removeElement(const unsigned);
    int getSize() const;
    agentieImobiliara & operator=(const agentieImobiliara&);
    friend istream& operator>>(istream &,agentieImobiliara &);
    friend ostream& operator<<(ostream &,agentieImobiliara&);
    static int getNrLocuinteAgentie();
};

void agentieImobiliara::insertElement(Locuinta* loc)
{
    if (this->nrLocuinte==this->alocate)
    {
        agentieImobiliara aux(*this);
        this->alocate+=10;
        cout<<alocate<<" ";
        this->v=new Locuinta *[alocate];
        for (int i=0; i<this->nrLocuinte; ++i)
            this->v[i]=aux.v[i];
    }
    try
    {
        this->v[nrLocuinte++]=new Casa(dynamic_cast<Casa &>(*loc));
    }
    catch (std::bad_cast)
    {
        this->v[nrLocuinte++]=new Apartament(dynamic_cast<Apartament &>(*loc));
    }
}

void agentieImobiliara::insertElement(Locuinta& loc)
{
    if (this->nrLocuinte==this->alocate)
    {
        agentieImobiliara aux(*this);
        this->alocate+=10;
        this->v=new Locuinta *[alocate];
        for (int i=0; i<this->nrLocuinte; ++i)
            this->v[i]=aux.v[i];
    }
    try
    {
        this->v[this->nrLocuinte++]=new Casa(dynamic_cast<Casa &>(loc));
    }
    catch (std::bad_cast)
    {
        this->v[this->nrLocuinte++]=new Apartament(dynamic_cast<Apartament &>(loc));
    }
}


void agentieImobiliara::removeElement(const unsigned poz)
{
    try
    {
        if (poz>=(unsigned)nrLocuinte)
            throw "adresa incorecta\n";
        *this->v[poz]=*this->v[nrLocuinte-1];
        delete this->v[nrLocuinte-1];
        --nrLocuinte;
    }
    catch (const char* e)
    {
        cout<<e;
    }
}

Locuinta& agentieImobiliara::operator[](const unsigned rang) const
{
    try
    {
        if (rang>=(unsigned)this->nrLocuinte)
            throw "adresa incorecta\n";
        return *this->v[rang];
    }
    catch (const char* x)
    {
        cout<<x;
        return *this->v[0];
    }
}

int agentieImobiliara::getSize() const
{
    return this->nrLocuinte;
}

agentieImobiliara & agentieImobiliara::operator=(const agentieImobiliara& ag)
{
    agentieImobiliara *aux=new agentieImobiliara;
    aux->nrLocuinte=ag.nrLocuinte;
    aux->alocate=ag.alocate;
    aux->v=new Locuinta*[ag.alocate];
    for (int i=0; i<ag.nrLocuinte; ++i)
        aux->v[i]=ag.v[i];
    return *aux;
}

istream &operator>>(istream &in,agentieImobiliara &ag)
{
    Locuinta *aux;
    int n,opt;
    cout<<"nr de locuinte :";
    cin>>n;
    for (int i=0; i<n; ++i)
    {
        cout<<"\nApartament(1)/Casa(2): ";
        cin>>opt;
        if (opt==1)
        {
            aux=new Apartament;
            cin>>dynamic_cast<Apartament &>(*aux);
        }
        else
        {
            aux=new Casa;
            cin>>dynamic_cast<Casa &>(*aux);
        }
        ag.insertElement(aux);
    }
}

ostream &operator<<(ostream &out,agentieImobiliara &ag)
{
    for (int i=0; i<ag.nrLocuinte; ++i)
    {
        cout<<ag.nrLocuinte;
        try
        {
            out<<dynamic_cast<Casa&>(ag[i]);
        }
        catch(std::bad_cast)
        {
            out<<dynamic_cast<Apartament&>(ag[i]);
        }
        out<<"\n\n";
    }
    cout<<"----------------------\n\n";
    return out;
}

int agentieImobiliara::nrLocuinteAgentie=0;

int agentieImobiliara::getNrLocuinteAgentie()
{
    return nrLocuinteAgentie;
}

int main()
{
    agentieImobiliara x(3);
    agentieImobiliara y;
    Locuinta *lp=new Casa("Ion",2,2,2);
    cout<<x;
    x.insertElement(lp);
    cout<<x;
    x.insertElement(lp);
    x.insertElement(lp);
    x.insertElement(lp);
    //y=x;
    //elete lp;
    //cout<<x;
}
