#include <iostream>
#include <cstring>
using namespace std;

class Rabotnik{
private:
    char ime[30];
    char prezime[30];
    int plata;
public:
    Rabotnik(){}
    Rabotnik(char *ime="", char *prezime="", int plata=0){
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->plata=plata;
    }
    Rabotnik &operator=(const Rabotnik &r){
        strcpy(this->ime, r.ime);
        strcpy(this->prezime, r.prezime);
        this->plata=r.plata;
    }
    ~Rabotnik(){}
    int getPlata(){
        return this->plata;
    }
    void setIme(char *ime){
        strcpy(this->ime,ime);
    }
    void setPrezime(char *prezime){
        strcpy(this->prezime,prezime);
    }
    void setPlata(int plata){
        this->plata=plata;
    }
    void pecati(){
        cout<<this->ime<<" "<<this->prezime<<" "<<this->plata<<endl;
    }
};
class Fabrika{
private:
    Rabotnik rabotnici[100];
    int brojVraboteni;
public:
    Fabrika(Rabotnik *rabotnici=nullptr, int brojVraboteni=0){
        this->brojVraboteni=brojVraboteni;
        for (int i=0; i<brojVraboteni; i++)
            this->rabotnici[i]=rabotnici[i];
    }
    ~Fabrika(){}
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
    for (int i=0; i<n; i++){
        cin>>ime>>prezime>>plata;
        rabotnici[i].setIme(ime);
        rabotnici[i].setPrezime(prezime);
        rabotnici[i].setPlata(plata);
    }
    Fabrika f(rabotnici, n);
    cin>>minimalna;
    cout<<"Site vraboteni:"<<endl;
    f.pecativraboteni();
    cout<<"Vraboteni so plata povisoka od "<<minimalna<<" :"<<endl;
    f.pecatisoplata(minimalna);
    return 0;
}
