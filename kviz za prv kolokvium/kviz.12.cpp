#include <iostream>
#include <cstring>

using namespace std;

class Pica{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int popust;
    void copy(const Pica &other){
        strcpy(this->ime, other.ime);
        this->cena=other.cena;
        this->sostojki=new char[strlen(other.sostojki)+1];
        strcpy(this->sostojki, other.sostojki);
        this->popust=other.popust;
    }
public:
    Pica(){}
    Pica(char *ime, int cena,char *sostojki, int popust){
        strcpy(this->ime, ime);
        this->cena=cena;
        this->sostojki=new char[strlen(sostojki)+1];
        strcpy(this->sostojki, sostojki);
        this->popust=popust;
    }
    Pica (const Pica &other){
        copy(other);
    }
    Pica &operator =(const Pica &other){
        if (this!=&other){
            delete [] sostojki;
            copy(other);
        }
        return *this;
    }
    ~Pica(){
        delete [] sostojki;
    }
    int getpopust(){
        return popust;
    }
    bool istiSe(Pica p){
        return strcmp(sostojki, p.sostojki)==0;
    }
    void pecati(){
        cout<<ime<<" - "<<sostojki<<", "<<cena<<" "<<(0.01*(100-popust))*cena<<endl;
    }
};

class Picerija{
private:
    char ime[15];
    Pica *pici;
    int broj;
    void copy(const Picerija &other){
        strcpy(this->ime, ime);
        this->broj=other.broj;
        this->pici=new Pica[broj];
        for (int i=0; i<broj; i++)
            this->pici[i]=other.pici[i];
    }
public:
    Picerija(){}
    Picerija(char *ime){
        strcpy(this->ime, ime);
    }
    Picerija (const Picerija &other){
        copy(other);
    }
    Picerija &operator =(const Picerija &other){
        if (this!=&other){
            delete [] pici;
            copy(other);
        }
        return *this;
    }
    void setIme(char *i){
        strcpy(ime, i);
    }
    char *getIme(){
        return ime;
    }
    Picerija dodadi (Pica P){
        Pica *tmp = new Pica[broj+1];
        for (int i=0; i<this->broj; i++){
            if (this->pici[i].istiSe(P))
                return *this;
            else
               tmp[i]=pici[i];
            }
    tmp[broj++]=P;
    delete [] pici;
    pici=tmp;
    return *this;
    }
    void piciNaPromocija(){
        for (int i=0; i<this->broj; i++)
            if (pici[i].getpopust())
                pici[i].pecati();
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}
