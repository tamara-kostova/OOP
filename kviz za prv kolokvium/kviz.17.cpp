#include <iostream>
#include <cstring>
using namespace std;

enum Tip{LINUX=1, UNIX, WINDOWS};

class OperativenSistem{
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
    void copy(const OperativenSistem &other){
        this->ime = new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->verzija=other.verzija;
        this->tip=other.tip;
        this->golemina=other.golemina;
    }
public:
    OperativenSistem(char *ime="", float verzija=0.0, Tip tip=LINUX, float golemina=0.0){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->tip=tip;
        this->golemina=golemina;
    }
    OperativenSistem(const OperativenSistem &other){
        copy(other);
    }
    OperativenSistem &operator=(const OperativenSistem &other){
        if (this!=&other){
            delete [] ime;
            copy(other);
        }
        return *this;
    }
    ~OperativenSistem(){
        delete [] ime;
    }
    void pecati(){
        cout<<"Ime: "<<this->ime<<" Verzija: "<<this->verzija<<" Tip: "<<this->tip<<" Golemina:"<<this->golemina<<"GB"<<endl;
    }
        bool ednakviSe(const OperativenSistem &os){
        return sporediVerzija(os) && istaFamilija(os) && this->golemina == os.golemina;
    }
    int sporediVerzija(const OperativenSistem &os){
        return this->verzija==os.verzija;
    }
    bool istaFamilija(const OperativenSistem &sporedba){
        return strcmp(this->ime, sporedba.ime)==0 && this->tip==sporedba.tip;
    }
    float getverzija(){
        return verzija;
    }
};
class Repozitorium{
    char ime [20];
    OperativenSistem *os;
    int broj=0;
    void copy(const Repozitorium & r){
        this->broj=r.broj;
        strcpy(this->ime, r.ime);
        this->os=new OperativenSistem[this->broj];
        for(int i=0;i<this->broj;i++)
            this->os[i]=r.os[i];
    }
public:
    Repozitorium(char *ime=""){
        strcpy(this->ime,ime);
        this->broj=0;
        this->os=nullptr;
    }
    Repozitorium & operator = (const Repozitorium & r){
        if(&r!=this){
            delete [] os;
            copy(r);
        }
        return *this;
    }
    ~Repozitorium(){
        delete [] os;
    }
    void pecatiOperativniSistemi(){
            cout<<"Repozitorium: "<<this->ime<<endl;
            for (int i=0; i<this->broj; i++)
                os[i].pecati();
    }
    void izbrishi(const OperativenSistem &operativenSistem){
        for (int i=0; i<broj; i++){
            if (os[i].ednakviSe(operativenSistem)){
                broj--;
                for (int j=i; j<broj; j++)
                    os[j]=os[j+1];
                break;
            }
    }
    }
    void dodadi(OperativenSistem &nov){
        int flag=0;
        OperativenSistem *tmp = new OperativenSistem [broj+1];
        for (int i=0; i<broj; i++){
            if (os[i].istaFamilija(nov)&&nov.getverzija()>os[i].getverzija()){
                tmp[i]=nov;
                flag=1;}
            else tmp[i]=os[i];
        }
        if (!flag){
            tmp[broj++]=nov;
        }
        delete [] os;
        os=tmp;
    }
};


int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
