#include <iostream>
#include <cstring>
using namespace std;

class Rabotnik{
private:
    char *ime;
    char *prezime;
    int plata;
public:
    Rabotnik(){}
    Rabotnik(char *ime, char *prezime, int plata){
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime, ime);
        this->prezime = new char [strlen(prezime)+1];
        strcpy(this->prezime, prezime);
        this->plata=plata;
    }
    ~Rabotnik(){}
    int getPlata(){
    return this->plata;
    }
    void pecati(){
        cout<<this->ime<<" "<<this->prezime<<" "<<this->plata<<endl;
    }
};
class Fabrika{
private:
    Rabotnik *rabotnici;
    int brojVraboteni;
public:
    Fabrika(){
    this->rabotnici=nullptr;
    this->brojVraboteni=0;
    }
    ~Fabrika(){delete []rabotnici;}
    Rabotnik &operator +=(const Rabotnik &nov){
        Rabotnik *tmp=new Rabotnik [this->brojVraboteni+1];
        for (int i=0; i<this->brojVraboteni; i++)
            tmp[i]=this->rabotnici[i];
        tmp[this->brojVraboteni++]=nov;
        delete [] this->rabotnici;
        this->rabotnici=tmp;
    }
    void pecativraboteni(){
        for (int i=0; i<this->brojVraboteni; i++)
            rabotnici[i].pecati();
    }
    void pecatisoplata(int minimalna){
        for (int i=0; i<this->brojVraboteni; i++)
            if (rabotnici[i].getPlata()>minimalna)
            rabotnici[i].pecati();
    }
};

int main(){
    int n, plata, minimalna;
    char ime[30], prezime[30];
    cin>>n;
    Rabotnik rabotnici[n];
    Fabrika f;
    for (int i=0; i<n; i++){
        cin>>ime>>prezime>>plata;
        Rabotnik r(ime,prezime, plata);
        f+=r;
    }
    cin>>minimalna;
    cout<<"Site vraboteni:"<<endl;
    f.pecativraboteni();
    cout<<"Vraboteni so plata povisoka od "<<minimalna<<" :"<<endl;
    f.pecatisoplata(minimalna);
    return 0;
}
