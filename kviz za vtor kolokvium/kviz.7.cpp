#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundsException{
    public:
        void showmessage(){
            cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
        }
};

class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
   public:
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
     ~Karticka(){}
     virtual int tezinaProbivanje(){
        int cifri=0, k = pin;
        while(k!=0){
            k/=10;
            cifri++;
        }
        return cifri;
     }
     bool getDopolnitelenPin(){
        return povekjePin;
     }
     char *getsmetka(){
        return smetka;
     }
     friend ostream &operator<<(ostream &o, Karticka &k){
        o<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
        return o;
     }
};

class SpecijalnaKarticka : public Karticka{
    int *pinkodovi;
    int n;
    static int P;
public:
    SpecijalnaKarticka(char* smetka="",int pin=0, int *pinkodovi=nullptr, int n=0) : Karticka(smetka,pin){
        this->n=n;
        pinkodovi = new int [n];
        for (int i=0; i<n;i++)
            this->pinkodovi[i]=pinkodovi[i];
    }
    ~SpecijalnaKarticka(){
        delete [] pinkodovi;
    }
    int tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+n;
    }
    SpecijalnaKarticka &operator+=(int novPin){
        if (n>=P)
            throw (OutOfBoundsException());
        int *tmp=new int [n+1];
        for (int i=0; i<n; i++)
            tmp[i]=pinkodovi[i];
        tmp[n++]=novPin;
        delete [] pinkodovi;
        pinkodovi=tmp;
        return *this;
    }
};
int SpecijalnaKarticka::P=4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLIMIT(int lim){
        LIMIT=lim;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for (int i=0; i<broj; i++)
            if (karticki[i]->tezinaProbivanje()<=LIMIT)
                cout<<*karticki[i];
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for (int i=0; i<broj; i++)
        if (!strcmp(smetka, karticki[i]->getsmetka())){
                SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
                if (sk){
                    try{
                        sk+=novPin;
                    }
                    catch (OutOfBoundsException e){
                        e.showmessage();
                    }
                }
        }
    }

};
int Banka::LIMIT=7;

int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;
try{
   komercijalna.dodadiDopolnitelenPin(smetka,pin);
}
catch (OutOfBoundsException &oe){
    oe.showmessage();
}
}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
