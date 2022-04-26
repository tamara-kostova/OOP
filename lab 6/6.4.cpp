#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina{
protected:
    char *adresa;
    int kvadratura;
    int cenak;
    void copy (const Nedviznina &n){
        adresa=new char [strlen(n.adresa)+1];
        strcpy(adresa, n.adresa);
        kvadratura=n.kvadratura;
        cenak=n.cenak;
    }
public:
    Nedviznina(){
        adresa = new char [0];
    }
     Nedviznina (const Nedviznina &n){
        copy(n);
    }
    Nedviznina&operator=(const Nedviznina &n){
        if(this!=&n)
        {
            delete[]adresa;
            copy(n);
        }
        return *this;
    }
    ~Nedviznina(){
        delete [] adresa;
    }
    int cena(){
        return kvadratura*cenak;
    }
    void pecati(){
        cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<cenak<<endl;
    }
    double danokNaImot(){
        return 0.05*cena();
    }
    friend istream &operator>>(istream &is, Nedviznina &n){
        is>>n.adresa>>n.kvadratura>>n.cenak;
        return is;
    }
    char *getAdresa(){
        return adresa;
    }
};
class Vila : public Nedviznina{
    int danok;
public:
    double danokNaImot(){
        return ((danok+5)*cena())/100.0;
    }
    void pecati(){
        cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<cenak<<", Danok na luksuz: "<<danok<<endl;
    }
    friend istream &operator >>(istream &is, Vila &v){
        is>>v.adresa>>v.kvadratura>>v.cenak>>v.danok;
        return is;
    }
    char *getAdresa(){
        return adresa;
    }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
