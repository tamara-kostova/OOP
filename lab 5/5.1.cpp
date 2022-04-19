#include <iostream>
#include <cstring>

using namespace std;

class Automobile{
    char *marka;
    int *registracija;
    int brzina;
void copy(const Automobile &a){
        marka=new char[strlen(a.marka)+1];
        strcpy(marka, a.marka);
        registracija=new int [5];
        for (int i=0; i<5; i++)
            registracija[i]=a.registracija[i];
        brzina=a.brzina;
}
public:
    Automobile(){
        this->marka=new char[1];
        this->registracija=new int [5];
        brzina=0;
    }
    Automobile(char *marka, int *registracija, int brzina){
        this->marka=new char[strlen(marka)+1];
        strcpy(this->marka, marka);
        this->registracija=new int [5];
        for (int i=0; i<5; i++)
            this->registracija[i]=registracija[i];
        this->brzina=brzina;
    }
    Automobile (const Automobile &a){
        copy(a);
    }
    Automobile &operator=(const Automobile &a){
        if (this!=&a){
            delete [] marka;
            delete [] registracija;
            copy(a);
        }
        return *this;
    }
    friend ostream & operator<<(ostream & o, Automobile &a) {
    o<<"Marka\t"<<a.marka[i];
    o<<"\\tRegistracija[ ";
    for (int i = 0; i < 5; ++i)
        o<<a.registracija[i]<<" ";
    o << "]"<<endl;
    return o;
    }
    bool operator ==(Automobile &a){
        for (int i=0; i<5; i++){
            if (registracija[i]!=a.registracija[i])
                return false;
        }
        return true;
    }
    ~Automobile(){
        delete [] marka;
        delete [] registracija;
    }
    int getBrzina(){
        return brzina;
    }
};
class RentACar{
    char ime[100];
    Automobile *avtomobili;
    int broj=0;
public:
    RentACar (char ime[]){
        strcpy(this->ime, ime);
        this->avtomobili = new Automobile[this->broj];
    }
    RentACar &operator+=(Automobile &nov){
        Automobile *tmp = new Automobile[broj+1];
        for (int i=0; i<broj; i++)
            tmp[i]=this->avtomobili[i];
        delete [] avtomobili;
        avtomobili=tmp;
        avtomobili[broj++]=nov;
        return *this;
    }
    RentACar &operator-=(Automobile &a){
        for (int i=0, j=0; i<broj; i++){
            if (avtomobili[i]==a){
                broj--;
                for (int j=i; j<broj; j++)
                    avtomobili[j]=avtomobili[j+1];
                break;
            }
        }
        return *this;
    }
    ~RentACar(){
        delete [] avtomobili;
    }
    void pecatiNadBrzina(int max){
        cout<<ime<<endl;
        for (int i=0; i<broj; i++)
            if (avtomobili[i].getBrzina()>max)
                cout<<avtomobili[i];
    }
};


int main()
{
   RentACar agencija("FINKI-Car");
   int n;
   cin>>n;

   for (int i=0;i<n;i++)
   {
    	char marka[100];
    	int regisracija[5];
    	int maximumBrzina;

       	cin>>marka;

       	for (int i=0;i<5;i++)
    		cin>>regisracija[i];

    	cin>>maximumBrzina;

       	Automobile nov=Automobile(marka,regisracija,maximumBrzina);

    	//dodavanje na avtomobil
       	agencija+=nov;

   }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
    cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
