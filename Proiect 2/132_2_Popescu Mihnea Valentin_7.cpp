#include <iostream>
#include <string.h>
#include <typeinfo>
#include <cstdlib>
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
    virtual float calculChirie(const int,const int) const=0;
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
    float calculChirie(const int, const int) const;
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

float Apartament::calculChirie(const int X,const int Y=0) const
{
    return 1.0*X*this->getSuprafata()*(1-Y*this->getDiscount()/100.0);
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
    float calculChirie(const int,const int) const;
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

float Casa::calculChirie(const int X,const int Y=0) const
{
    return 1.0*X*(this->getSuprafata()+0.2*this->suprafataCurte)*(1-Y*this->getDiscount()/100.0);
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
    static int nrLocuinteAgentii;
    int nrLocuinte;
    int alocate;
public:
    agentieImobiliara(int nr=0,string nume="",int suprafata=0,float discount=0,int opt=1)
    {
        this->v=new Locuinta*[nr];
        nrLocuinteAgentii+=nr;
        this->nrLocuinte=nr;
        this->alocate=nr;
        if (opt==1)
            for (int i=0; i<nr; ++i)
                this->v[i]=new Casa(nume,suprafata,discount);
        else
            for (int i=0; i<nr; ++i)
                this->v[i]=new Apartament(nume,suprafata,discount);
    }
    agentieImobiliara(agentieImobiliara& ag):nrLocuinte(ag.nrLocuinte),alocate(ag.alocate)
    {
        nrLocuinteAgentii+=ag.nrLocuinte;
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
    agentieImobiliara & operator=(agentieImobiliara&);
    friend istream& operator>>(istream &,agentieImobiliara &);
    friend ostream& operator<<(ostream &,agentieImobiliara&);
    static int getNrLocuinteAgentie();
};

void agentieImobiliara::insertElement(Locuinta* loc)
{
    if (this->nrLocuinte==this->alocate)
    {
        agentieImobiliara aux(*this);
        for (int i=0; i<this->nrLocuinte; ++i)
            delete this->v[i];
        delete []this->v;
        this->alocate+=10;
        this->v=new Locuinta *[alocate];
        for (int i=0; i<this->nrLocuinte; ++i)
        {
            try
            {
                this->v[i]=new Casa(dynamic_cast<Casa &>(*aux.v[i]));
            }
            catch (std::bad_cast)
            {
                this->v[i]=new Apartament(dynamic_cast<Apartament &>(*aux.v[i]));
            }
        }
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
    Locuinta *aux2;
    try
    {
        aux2=new Casa(dynamic_cast<Casa&>(loc));
    }
    catch (std::bad_cast)
    {
        aux2=new Apartament(dynamic_cast<Apartament&>(loc));
    }
    if (this->nrLocuinte==this->alocate)
    {
        agentieImobiliara aux(*this);
        for (int i=0; i<this->nrLocuinte; ++i)
            delete this->v[i];
        delete []this->v;
        this->alocate+=10;
        this->v=new Locuinta *[alocate];
        for (int i=0; i<this->nrLocuinte; ++i)
        {
            try
            {
                this->v[i]=new Casa(dynamic_cast<Casa &>(*aux.v[i]));
            }
            catch (std::bad_cast)
            {
                this->v[i]=new Apartament(dynamic_cast<Apartament &>(*aux.v[i]));
            }
        }
    }
    try
    {
        this->v[this->nrLocuinte++]=aux2;
    }
    catch (std::bad_cast)
    {
        this->v[this->nrLocuinte++]=aux2;
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

agentieImobiliara & agentieImobiliara::operator=(agentieImobiliara& ag)
{
    if (this!=&ag)
    {
        for (int i=0; i<this->nrLocuinte; ++i)
            delete this->v[i];
        delete []this->v;
        this->nrLocuinte=ag.nrLocuinte;
        this->alocate=ag.alocate;
        this->v=new Locuinta*[ag.alocate];
        for (int i=0; i<ag.nrLocuinte; ++i)
        {
            try
            {
                this->v[i]=new Apartament(dynamic_cast<Apartament&>(*ag.v[i]));
            }
            catch(std::bad_cast)
            {
                this->v[i]=new Casa(dynamic_cast<Casa&>(*ag.v[i]));
            }
        }
    }
    return *this;
}

istream &operator>>(istream &in,agentieImobiliara &ag)
{
    Locuinta *aux;
    int n,opt;
    cout<<"nr de locuinte :";
    in>>n;
    for (int i=0; i<ag.nrLocuinte; ++i)
        delete ag.v[i];
    delete []ag.v;
    ag.alocate=n;
    ag.nrLocuinte=n;
    ag.v=new Locuinta* [n];
    for (int i=0; i<n; ++i)
    {
        cout<<"\nApartament(1)/Casa(2): ";
        in>>opt;
        if (opt==1)
        {
            ag.v[i]=new Apartament;
            in>>dynamic_cast<Apartament &>(*ag.v[i]);
        }
        else
        {
            ag.v[i]=new Casa;
            in>>dynamic_cast<Casa &>(*ag.v[i]);
        }
    }
    return in;
}

ostream &operator<<(ostream &out,agentieImobiliara &ag)
{
    for (int i=0; i<ag.nrLocuinte; ++i)
    {
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

int agentieImobiliara::nrLocuinteAgentii=0;

int agentieImobiliara::getNrLocuinteAgentie()
{
    return nrLocuinteAgentii;
}

int main()
{
    agentieImobiliara x;
    char opt;
    float chirie;
    bool discount=false;
    cout<<"Chirie/mp($): ";
    cin>>chirie;
    cout<<"Se va folosi discount?(Y/N)";
    cin>>opt;
    if (opt=='Y')
        discount=true;
    opt='0';
    while (opt!='q')
    {
        system("CLS");
        cout<<"1) Citire locuinte(stergere locuinte precedente)\n";
        cout<<"2) Afisare locuinte\n";
        cout<<"3) Afisare chirii \n";
        cout<<"4) Insereaza locuinta \n";
        cout<<"5) Sterge locuinta \n";
        cout<<"6) Afisare statistici\n";
        cout<<"7) Afiseaza locuinta\n";
        cout<<"8) Modificare informatii locuinta \n";
        cout<<"q) Iesire\n";
        cout<<"opt: ";
        cin>>opt;
        switch(int(opt-'0'))
        {
        case 1:
        {
            cin>>x;
            system("CLS");
            break;
        }
        case 2:
        {
            cout<<x;
            cout<<"\n\n Apasa o tasta";
            cin.get();
            cin.get();
            break;
        }
        case 3:
        {
            for (int i=0; i<x.getSize(); ++i)
            {
                cout<<"Chirie locuinta "<<i<<": ";
                cout<<x[i].calculChirie(chirie,discount)<<"\n";
            }
            cout<<"\n\n Apasa o tasta";
            cin.get();
            cin.get();
            break;
        }
        case 4:
        {
            cout<<"Apartament(1)\Casa(2): ";
            cin>>opt;
            if (int(opt-'0')==1)
            {
                Apartament aux;
                cin>>aux;
                x.insertElement(aux);
            }
            else
            {
                Casa aux;
                cin>>aux;
                x.insertElement(aux);
            }
            break;
        }
        case 5:
        {
            unsigned poz;
            cout<<"Pozitia: ";
            cin>>poz;
            x.removeElement(poz);
            break;
        }
        case 6:
        {
            cout<<"Nr obiecte de tip locuinta: "<<Locuinta::getNrLocuinte();
            cout<<"\nNr obiecte de tip apartament: "<<Apartament::getNrApartamente();
            cout<<"\nNr obiecte de tip casa: "<<Casa::getNrCase();
            cout<<"\nNr obiecte locuinta in cadrul agentiilor: "<<agentieImobiliara::getNrLocuinteAgentie();
            cout<<"\n\nApasa o tasta";
            cin.get();
            cin.get();
            break;
        }
        case 7:
        {
            unsigned poz;
            cout<<"Pozitia: ";
            cin>>poz;
            if (dynamic_cast<Casa*>(&x[poz])!=nullptr)
            {
                cout<<dynamic_cast<Casa&>(x[poz]);
            }
            else cout<<dynamic_cast<Apartament &>(x[poz]);
            cout<<"\n\nApasa o tasta";
            cin.get();
            cin.get();
            break;
        }
        case 8:
        {
            int poz;
            cout<<"Pozitia: ";
            cin>>poz;
            cout<<"1)Modifica nume\n";
            cout<<"2)Modifica suprafata\n";
            cout<<"3)Modifica discount \n";
            if (dynamic_cast<Casa*>(&x[poz])!=nullptr)
                cout<<"4)Modifica suprafata curte \n";
            else
                cout<<"4)Modifica etaj \n";
            cout<<"opt: ";
            cin>>opt;
            system("CLS");
            switch (int(opt-'0'))
            {
            case 1:
            {
                string nume;
                cout<<"nume: ";
                cin>>nume;
                x[poz].setNumeClient(nume);
                break;
            }
            case 2:
            {
                int suprafata;
                cout<<"suprafata: ";
                cin>>suprafata;
                x[poz].setSuprafata(suprafata);
                break;
            }
            case 3:
            {
                float discount;
                cout<<"discount: ";
                cin>>discount;
                x[poz].setDiscount(discount);
                break;
            }
            case 4:
            {
                if (dynamic_cast<Casa*>(&x[poz])!=nullptr)
                {
                    int suprafataCurte;
                    cout<<"Suprafata curte: ";
                    cin>>suprafataCurte;
                    dynamic_cast<Casa&>(x[poz]).setSuprafataCurte(suprafataCurte);
                }
                else
                {
                    int etaj;
                    cout<<"Etaj: ";
                    cin>>etaj;
                    dynamic_cast<Apartament&>(x[poz]).setEtaj(etaj);
                }
                break;
            }
            default:
            {
                break;
            }
            }

        }
        default:
        {
            break;
        }
        }
    }
}
