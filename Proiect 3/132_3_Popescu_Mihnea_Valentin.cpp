#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
using namespace std;

class masina
{
protected:
    int an_fabricatie;
    float cc;
    static int nr_masini;
    int cai_putere;
    string marca;
    string tip_motor;
    vector<string> dotari;
public:
    masina(int an_fabricatie=0,float cc=0,int cai_putere=0,string marca="",string tip_motor="",vector<string> dotari= {}):an_fabricatie(an_fabricatie),cc(cc),cai_putere(cai_putere),marca(marca),tip_motor(tip_motor),dotari(dotari)
    {
        ++nr_masini;
    }
    masina(int an_fabricatie,float cc,int cai_putere,string marca,string tip_motor,std::initializer_list<string> dotari):an_fabricatie(an_fabricatie),cc(cc),cai_putere(cai_putere),marca(marca),tip_motor(tip_motor),dotari(dotari)
    {
        ++nr_masini;
    }
    masina(masina & m):an_fabricatie(m.an_fabricatie),cc(m.cc),cai_putere(m.cai_putere),marca(m.marca),tip_motor(m.tip_motor),dotari(m.dotari)
    {
        ++nr_masini;
    }
    virtual ~masina()
    {
        --nr_masini;
        this->an_fabricatie=this->cc=this->cai_putere=0;
        this->marca=this->tip_motor="";
        this->dotari.clear();
    }
    void set_an_fabricatie(const int);
    int get_an_fabricatie() const;
    void set_cc(const float);
    float get_cc() const;
    void set_cai_putere(const int);
    int get_cai_putere() const;
    void set_marca(const string);
    string get_marca() const;
    void set_motor(const string);
    string get_motor() const;
    void insert_dotare(const string);
    void delete_dotare(const unsigned int);
    string get_dotari(int) const;
    masina & operator=(const masina &);
    friend istream & operator >> (istream &,masina &);
    friend ostream & operator<< (ostream & out,const masina &);
    virtual void citire();
    virtual void afisare();
};

int masina::nr_masini=0;

void masina::set_an_fabricatie(const int an)
{
    this->an_fabricatie=an;
}

int masina::get_an_fabricatie() const
{
    return this->an_fabricatie;
}

void masina::set_cc(const float cc)
{
    this->cc=cc;
}

float masina::get_cc() const
{
    return this->cc;
}

void masina::set_cai_putere(const int cp)
{
    this->cai_putere=cp;
}

int masina::get_cai_putere() const
{
    return this->cai_putere;
}

void masina::set_marca(const string marca)
{
    this->marca=marca;
}


string masina::get_marca() const
{
    return this->marca;
}

void masina::set_motor(const string motor)
{
    this->tip_motor=motor;
}

string masina::get_motor() const
{
    return this->tip_motor;
}

void masina::insert_dotare(const string dotare)
{
    this->dotari.push_back(dotare);
}

void masina::delete_dotare(const unsigned int index)
{
    try
    {
        if (index>=dotari.size())
            throw "index invalid\n";
        this->dotari.erase(this->dotari.begin()+index);
    }
    catch (char const* s)
    {
        cout<<s;
    }
}

string masina::get_dotari(int index=-1) const
{
    if (index==-1)
        return get_dotari(0);
    if (index<this->dotari.size())
        return this->dotari[index]+","+get_dotari(index+1);
    return "";
}

masina & masina::operator=(const masina & m)
{
    this->an_fabricatie=m.an_fabricatie;
    this->cc=m.cc;
    this->cai_putere=m.cai_putere;
    this->marca=m.marca;
    this->tip_motor=m.tip_motor;
    this->dotari=m.dotari;
    return *this;
}

istream & operator >> (istream & in,masina & m)
{
    cout<<"an_fabricatie= ";
    in>>m.an_fabricatie;
    cout<<"\ncapacitate cilindrica= ";
    in>>m.cc;
    cout<<"\ncai putere= ";
    in>>m.cai_putere;
    cout<<"\nmarca= ";
    in>>m.marca;
    cout<<"\ntip motor= ";
    in>>m.tip_motor;
    cout<<"\nnumar dotari= ";
    unsigned short nr_dotari;
    in>>nr_dotari;
    string dotare;
    for (unsigned short i=0; i<nr_dotari; ++i)
    {
        cout<<"\n\tdotarea "<<i<<"= ";
        in>>dotare;
        m.dotari.push_back(dotare);
    }
    return in;
}

ostream & operator <<(ostream & out,masina & m)
{
    out<<"an_fabricatie= "<<m.get_an_fabricatie();
    out<<"\ncapacitate cilindrica= "<<m.get_cc();
    out<<"\ncai putere= "<<m.get_cai_putere();
    out<<"\nmarca= "<<m.get_marca();
    out<<"\ntip motor= "<<m.get_motor();
    out<<"\nDotari:\n";
    out<<m.get_dotari();
    return out;
}

void masina::citire()
{
    cin>>*this;
}

void masina::afisare()
{
    cout<<*this;
}

class hot_hatch: public masina
{
    static int nr_hot_hatch;
    string model_de_baza;
public:
    hot_hatch(int an_fabricatie=0,float cc=0,int cai_putere=0,string marca="",string tip_motor="",vector<string> dotari= {},string model_de_baza=""):masina(an_fabricatie,cc,cai_putere,marca,tip_motor,dotari),model_de_baza(model_de_baza)
    {
        ++nr_hot_hatch;
    }
    hot_hatch(int an_fabricatie,float cc,int cai_putere,string marca,string tip_motor,std::initializer_list<string> dotari,string model_de_baza):masina(an_fabricatie,cc,cai_putere,marca,tip_motor,dotari),model_de_baza(model_de_baza)
    {
        ++nr_hot_hatch;
    }
    hot_hatch(hot_hatch & h):masina(h),model_de_baza(h.model_de_baza)
    {
        ++nr_hot_hatch;
    }
    ~hot_hatch()
    {
        --nr_hot_hatch;
        this->model_de_baza="";
    }
    void set_model_de_baza(const string);
    string get_model_de_baza() const;
    hot_hatch & operator=( hot_hatch &);
    friend istream & operator>>(istream &,hot_hatch &);
    friend ostream & operator<<(ostream &,hot_hatch &);
    void citire();
    void afisare();
};

int hot_hatch::nr_hot_hatch=0;

void hot_hatch::set_model_de_baza(const string model)
{
    this->model_de_baza=model;
}

string hot_hatch::get_model_de_baza() const
{
    return this->model_de_baza;
}
hot_hatch & hot_hatch::operator=(hot_hatch & h)
{
    dynamic_cast<masina&>(*this)=dynamic_cast<masina&>(h);
    this->model_de_baza=h.model_de_baza;
    return *this;
}

istream & operator>>(istream & in,hot_hatch &h)
{
    in>>dynamic_cast<masina &>(h);
    cout<<"Model de baza: ";
    in>>h.model_de_baza;
    return in;
}

ostream & operator<<(ostream &out,hot_hatch &h)
{
    out<<dynamic_cast<masina &>(h);
    out<<"Model de baza: ";
    out<<h.model_de_baza;
    return out;
}

void hot_hatch::citire()
{
    cin>>*this;
}

void hot_hatch::afisare()
{
    cout<<*this;
}

class cabrio:public masina
{
    static int nr_cabrio;
    string tip_acoperis;
public:
    cabrio(int an_fabricatie=0,float cc=0,int cai_putere=0,string marca="",string tip_motor="",vector<string> dotari= {},string tip_acoperis=""):masina(an_fabricatie,cc,cai_putere,marca,tip_motor,dotari),tip_acoperis(tip_acoperis)
    {
        ++nr_cabrio;
    }
    cabrio(int an_fabricatie,float cc,int cai_putere,string marca,string tip_motor,std::initializer_list<string> dotari,string tip_acoperis):masina(an_fabricatie,cc,cai_putere,marca,tip_motor,dotari),tip_acoperis(tip_acoperis)
    {
        ++nr_cabrio;
    }
    cabrio(cabrio & c):masina(c),tip_acoperis(c.tip_acoperis)
    {
        ++nr_cabrio;
    }
    ~cabrio()
    {
        --nr_cabrio;
        this->tip_acoperis="";
    }
    void set_tip_acoperis(const string);
    string get_tip_acoperis() const;
    cabrio & operator=( cabrio &);
    friend istream & operator>>(istream &,cabrio &);
    friend ostream & operator<<(ostream &,cabrio &);
    void citire();
    void afisare();
};

int cabrio::nr_cabrio=0;

void cabrio::set_tip_acoperis(const string acoperis)
{
    this->tip_acoperis=acoperis;
}

string cabrio::get_tip_acoperis() const
{
    return this->tip_acoperis;
}
cabrio & cabrio::operator=(cabrio & c)
{
    dynamic_cast<masina&>(*this)=dynamic_cast<masina&>(c);
    this->tip_acoperis=c.tip_acoperis;
    return *this;
}

istream & operator>>(istream & in,cabrio &c)
{
    in>>dynamic_cast<masina &>(c);
    cout<<"tip acoperis: ";
    in>>c.tip_acoperis;
    return in;
}

ostream & operator<<(ostream &out,cabrio &c)
{
    out<<dynamic_cast<masina &>(c);
    out<<"tip acoperis: ";
    out<<c.tip_acoperis;
    return out;
}

void cabrio::citire()
{
    cin>>*this;
}

void cabrio::afisare()
{
    cout<<*this;
}

class supersport:public masina
{
    int viteza_maxima;
    static int nr_supersport;
    const int taxa_vanzare=100;
    unsigned int nr_km;
public:
    supersport(int an_fabricatie=0,float cc=0,int cai_putere=0,string marca="",string tip_motor="",vector<string> dotari= {},unsigned int km=0,int viteza_maxima=0):masina(an_fabricatie,cc,cai_putere,marca,tip_motor,dotari),nr_km(km)
    {
        ++nr_supersport;
    }
    supersport(int an_fabricatie,float cc,int cai_putere,string marca,string tip_motor,std::initializer_list<string> dotari,unsigned int km,int viteza_maxima):masina(an_fabricatie,cc,cai_putere,marca,tip_motor,dotari),nr_km(km)
    {
        ++nr_supersport;
    }
    supersport(supersport & s):masina(s),nr_km(s.nr_km),viteza_maxima(s.viteza_maxima)
    {
        ++nr_supersport;
    }
    ~supersport()
    {
        --nr_supersport;
    }
    int get_taxa() const;
    unsigned int get_km() const;
    int get_viteza_maxima() const;
    void set_viteza_maxima(const unsigned int);
    void set_km(const unsigned int);
    supersport & operator=( supersport &);
    friend istream & operator>>(istream &,supersport &);
    friend ostream & operator<<(ostream &,supersport &);
    void citire();
    void afisare();
};

int supersport::nr_supersport=0;


int supersport::get_taxa() const
{
    return this->taxa_vanzare;
}

unsigned int supersport::get_km() const
{
    return this->nr_km;
}

int supersport::get_viteza_maxima() const
{
    return this->viteza_maxima;
}
void supersport::set_viteza_maxima(const unsigned int vmax)
{
    this->viteza_maxima=vmax;
}

void supersport::set_km(const unsigned int km)
{
    this->nr_km=km;
}

supersport & supersport::operator=(supersport & s)
{
    dynamic_cast<masina&>(*this)=dynamic_cast<masina&>(s);
    this->nr_km=s.nr_km;
    this->viteza_maxima=s.viteza_maxima;
    return *this;
}

istream & operator>>(istream & in,supersport &s)
{
    in>>dynamic_cast<masina &>(s);
    cout<<"\nnumar kilometrii: ";
    in>>s.nr_km;
    cout<<"\nviteza maxima: ";
    in>>s.viteza_maxima;
    return in;
}

ostream & operator<<(ostream &out,supersport &s)
{
    out<<dynamic_cast<masina &>(s);
    out<<"\ntaxa_vanzare: ";
    out<<s.taxa_vanzare;
    out<<"\nnumar kilometrii: ";
    out<<s.nr_km;
    cout<<"\nviteza maxima: ";
    out<<s.viteza_maxima;
    return out;
}

void supersport::citire()
{
    cin>>*this;
}

void supersport::afisare()
{
    cout<<*this;
}

template<typename tip_masina>
class expozitie
{
    static unsigned int nr_masini;
    vector <tip_masina> masini;
public:
    expozitie(vector<tip_masina> v= {}):masini(v)
    {
        nr_masini+=v.size();
    }
    expozitie(std::initializer_list<tip_masina> l):masini(l)
    {
        nr_masini+=l.size();
    }
    expozitie(expozitie<tip_masina> & e):masini(e.masini)
    {
        nr_masini+=e.nr_masini;
    }
    ~expozitie()
    {
        nr_masini-=this->masini.size();
        for (auto &x:masini)
            delete x;
        this->masini.clear();
    }
    void insert_car(const tip_masina & );
    tip_masina get_car(const unsigned int) const;
    void delete_car(const unsigned int);
    unsigned int get_nr_masini() const;
    expozitie<tip_masina> operator=(const expozitie<tip_masina> &);
    template <typename U>
    friend istream & operator>>(istream &,expozitie<U> &);
    template <typename U>
    friend ostream & operator<<(ostream &, const expozitie<U> &);
};

template<typename tip_masina>
unsigned int expozitie<tip_masina>::nr_masini = 0;

template <typename tip_masina>
void expozitie<tip_masina>::insert_car(const tip_masina & m)
{
    ++this->nr_masini;
    this->masini.push_back(m);
}

template <typename tip_masina>
tip_masina expozitie<tip_masina>::get_car(const unsigned int index) const
{
    try
    {
        if (index>=this->masini.size())
            throw "index invalid\n";
        return this->masini[index];
    }
    catch (char const* s)
    {
        cout<<s;
    }
}


template <typename tip_masina>
void expozitie<tip_masina>::delete_car(const unsigned int index)
{
    try
    {
        if (index>=this->masini.size())
            throw "index invalid\n";
        delete this->masini[index];
        this->masini.erase(this->masini.begin()+index);
        --this->nr_masini;
    }
    catch (char const * s)
    {
        cout<<s;
    }
}

template <typename tip_masina>
unsigned int expozitie<tip_masina>::get_nr_masini() const
{
    return expozitie<tip_masina>::nr_masini;
}

template <typename tip_masina>
expozitie<tip_masina> expozitie<tip_masina>::operator=(const expozitie<tip_masina> &m)
{
    this->nr_masini-=this->masini.size();
    this->nr_masini+=m.masini.size();
    this->masini=m.masini;
    return *this;
}

template <typename U>
istream & operator>>(istream & in,expozitie<U> & exp)
{
    cout<<"Nr masini";
    int nr;
    in>>nr;
    exp.masini.resize(nr);
    cout<<typeid(U).name();
    return in;
}

template <typename U>
ostream & operator<<(ostream & out,const expozitie<U>& exp)
{
    for (int i=0; i<exp.masini.size(); ++i)
        out<<*exp.masini[i]<<"\n\n";
    return out;
}

template<>
class expozitie <supersport>
{
    static unsigned int nr_masini;
    static unsigned int nr_vandute;
    vector <supersport*> masini;
    vector <pair<supersport*,int>> vandute;
public:
    expozitie(vector<supersport> v= {})
    {
        nr_masini+=v.size();
        for (auto & x:v)
            this->masini.push_back(new supersport(x));
    }
    expozitie(std::initializer_list<supersport*> l)
    {
        nr_masini+=l.size();
        for (auto & x:l)
            this->masini.push_back(new supersport(*x));
    }
    expozitie(expozitie<supersport> & e)
    {
        nr_masini+=e.nr_masini;
        for (auto & x:e.masini)
            this->masini.push_back(new supersport(*x));
        for (auto & y:e.vandute)
            this->vandute.push_back(make_pair(new supersport(*y.first),y.second));
    }
    ~expozitie()
    {
        nr_masini-=this->masini.size();
        for (int i=0; i<this->masini.size(); ++i)
            delete this->masini[i];
        for (int i=0; i<this->vandute.size(); ++i)
            delete this->vandute[i].first;
        this->masini.clear();
        this->vandute.clear();
    }
    void insert_car( supersport & );
    supersport & get_car(const unsigned int) const;
    void delete_car(const unsigned int);
    unsigned int get_nr_masini() const;
    expozitie<supersport> & operator=(const expozitie<supersport> &);
    friend istream & operator>>(istream &in,expozitie<supersport> &);
    friend ostream & operator<<(ostream &,const expozitie<supersport> &);
    expozitie<supersport> & operator-=(const unsigned int &);
};

unsigned int expozitie<supersport>::nr_masini = 0;
unsigned int expozitie<supersport>::nr_vandute = 0;

void expozitie<supersport>::insert_car(supersport & m)
{
    ++this->nr_masini;
    this->masini.push_back(new supersport(m));
}

supersport & expozitie<supersport>::get_car(const unsigned int index) const
{
    try
    {
        if (index>=this->masini.size())
            throw "index invalid\n";
        return *this->masini[index];
    }
    catch (char const* s)
    {
        cout<<s;
    }
}


void expozitie<supersport>::delete_car(const unsigned int index)
{
    try
    {
        if (index>=this->masini.size())
            throw "index invalid\n";
        delete this->masini[index];
        this->masini.erase(this->masini.begin()+index);
        --this->nr_masini;
    }
    catch (char const * s)
    {
        cout<<s;
    }
}

unsigned int expozitie<supersport>::get_nr_masini() const
{
    return expozitie<supersport>::nr_masini;
}

expozitie<supersport> & expozitie<supersport>::operator=(const expozitie<supersport> &m)
{
    this->nr_masini-=this->masini.size();
    this->nr_masini+=m.masini.size();
    this->nr_vandute-=this->vandute.size();
    this->nr_vandute+=m.vandute.size();
    for (int i=0; i<this->masini.size(); ++i)
        delete this->masini[i];
    this->masini.resize(0);
    for (int i=0; i<this->vandute.size(); ++i)
        delete this->vandute[i].first;
    this->vandute.resize(0);
    for (int i=0; i<m.masini.size(); ++i)
        this->masini.push_back(new supersport(*m.masini[i]));
    for (int i=0; i<m.vandute.size(); ++i)
        this->vandute.push_back(make_pair(new supersport(*m.vandute[i].first),m.vandute[i].second));
    return *this;
}

istream & operator>>(istream & in,expozitie<supersport> & exp)
{
    cout<<"Nr masini";
    int nr;
    in>>nr;
    for (int i=0; i<exp.masini.size(); ++i)
        delete exp.masini[i];
    exp.masini.resize(nr);
    for (int i=0; i<exp.vandute.size(); ++i)
        delete exp.vandute[i].first;
    exp.vandute.resize(0);
    for (int i=0; i<nr; ++i)
        in>>*exp.masini[i];
    return in;
}

ostream & operator<<(ostream & out,const expozitie<supersport>& exp)
{
    for (int i=0; i<exp.masini.size(); ++i)
        out<<*exp.masini[i]<<"\n\n";
    out<<"Vandute: \n";
    for (int i=0; i<exp.vandute.size(); ++i)
    {
        out<<*exp.vandute[i].first<<"\n";
        out<<"pret: "<<exp.vandute[i].second;
    }
    return out;
}

int calcul_pret(supersport aux,int pret)
{
    return max(0,int(2000-aux.get_taxa()*aux.get_km()))+pret;
}

expozitie <supersport> & expozitie<supersport>::operator-=(const unsigned int & index)
{
    cout<<"pret=";
    int pret;
    cin>>pret;
    ++this->nr_vandute;
    this->vandute.push_back(make_pair(new supersport(*this->masini[index]),calcul_pret(*this->masini[index],pret)));
    this->delete_car(index);
}

int main()
{
    expozitie<cabrio*> a;
    expozitie<hot_hatch*> b;
    expozitie<supersport> c;
    char opt[1];
    while (opt!="q")
    {
        system("CLS");
        cout<<"1) inserare cabrio\n";
        cout<<"2) inserare hot_hatch\n";
        cout<<"3) inserare supersport\n";
        cout<<"4) afisare cabrio\n";
        cout<<"5) afisare hot_hatch\n";
        cout<<"6) afisare supersport\n";
        cout<<"7) stergete cabrio\n";
        cout<<"8) stergere hot_hatch\n";
        cout<<"9) stergete supersport\n";
        cout<<"0) vindere supersport\n";
        cout<<"q) iesire\n";
        cin>>opt;
        switch (int(opt[0]-'0'))
        {
        case 1:
        {
            cabrio aux;
            cin>>aux;
            a.insert_car(new cabrio(aux));
            system("CLS");
            break;
        }
        case 2:
        {
            hot_hatch aux;
            cin>>aux;
            b.insert_car(new hot_hatch(aux));
            system("CLS");
            break;
        }
        case 3:
        {
            supersport aux;
            cin>>aux;
            c.insert_car(aux);
            system("CLS");
            break;
        }
        case 4:
        {
            system("CLS");
            cout<<a<<"\n";
            cout<<"Apasati o tasta ";
            cin.get();
            cin.get();
            break;
        }
        case 5:
        {
            system("CLS");
            cout<<b<<"\n";
            cout<<"Apasati o tasta ";
            cin.get();
            cin.get();
            break;
        }
        case 6:
        {
            system("CLS");
            cout<<c<<"\n";
            cout<<"Apasati o tasta ";
            cin.get();
            cin.get();
            break;
        }
        case 7:
        {
            unsigned int index;
            cout<<"index: ";
            cin>>index;
            a.delete_car(index);
            system("CLS");
            break;
        }
        case 8:
        {
            unsigned int index;
            cout<<"index: ";
            cin>>index;
            b.delete_car(index);
            system("CLS");
            break;

        }
        case 9:
        {
            unsigned int index;
            cout<<"index: ";
            cin>>index;
            c.delete_car(index);
            system("CLS");
            break;

        }
        case 0:
        {
            unsigned int index;
            cout<<"index: ";
            cin>>index;
            c-=index;
            break;
        }
        }
    }
}
