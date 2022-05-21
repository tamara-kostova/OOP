#include<iostream>
#include<cstring>

using namespace std;
class InvalidDateException{
    int den;
    int mesec;
    int godina;
public:
    InvalidDateException(int den, int mesec, int godina){
        this->den = den;
        this->mesec=mesec;
        this->godina=godina;
    }
    void message(){
        cout<<"Invalid Date "<<den<<"/"<<mesec<<"/"<<godina<<endl;
    }
};
class NotSupportedCurrencyException{
    char currency[4];
public:
    NotSupportedCurrencyException(char *currency){
        strcpy(this->currency, currency);
    }
    void message(){
        cout<<currency<<" is not a supported currency"<<endl;
    }
};

class Transakcija{
protected:
    int den;
    int mesec;
    int godina;
    double iznos;
    static double eur;
    static double usd;
public:
    Transakcija(int den=0, int mesec=0, int godina=0, double iznos=0){
        if (den<1||den>31||mesec<1||mesec>12)
            throw (InvalidDateException(den,mesec,godina));
        else{
        this->den=den;
        this->mesec=mesec;
        this->godina=godina;
        this->iznos=iznos;
        }
    }
    virtual double voDenari() = 0;
    virtual void pecati() = 0;
    static double getusd(){
        return usd;
    }
    static  double geteur(){
        return Transakcija::eur;
    }
    static void setEUR(double newEUR){
        eur=newEUR;
    }
    static void setUSD(double newUSD){
        usd=newUSD;
    }
};
double Transakcija::eur = 61;
double Transakcija::usd = 50;
class DenarskaTransakcija : public Transakcija{
    public:
    DenarskaTransakcija(int den, int mesec, int godina, double iznos) : Transakcija(den,mesec,godina,iznos){
    }
    double voDenari(){
        return iznos;
    }
    void pecati(){
         cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<iznos<<" MKD"<<endl;
    }
};
class DeviznaTransakcija : public Transakcija{
    char valuta[4];
public:
    DeviznaTransakcija(int den, int mesec, int godina, double iznos, char *valuta) : Transakcija(den,mesec,godina,iznos){
        if(strcmp(valuta,"EUR") != 0 && strcmp(valuta,"USD") != 0)
            throw NotSupportedCurrencyException(valuta);
        else
            strcpy(this->valuta, valuta);
    }
    double voDenari(){
        if (strcmp(valuta, "EUR")==0)
            return 1.0*iznos*Transakcija::eur;
        return 1.0*iznos*Transakcija::usd;
    }
    void pecati(){
        cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<iznos<<" "<<valuta<<endl;
    }
};
class Smetka{
    Transakcija **transakcii;
    int brojtransakcii;
    char smetka[15];
    double pocetnosaldo;
    void copy(const Smetka &s){
        brojtransakcii=s.brojtransakcii;
        transakcii=new Transakcija*[brojtransakcii];
        for(int i=0;i<brojtransakcii;i++)
            transakcii[i]=s.transakcii[i];
        strcpy(smetka,s.smetka);
        pocetnosaldo=s.pocetnosaldo;
    }
public:
    Smetka(char *smetka="", double pocetnosaldo=0){
        brojtransakcii=0;
        transakcii = new Transakcija*[brojtransakcii];
        strcpy(this->smetka, smetka);
        this->pocetnosaldo=pocetnosaldo;
    }
    Smetka (const Smetka &s){
        copy(s);
    }
    Smetka &operator = (const Smetka &s){
        if (this!=&s){
            delete [] transakcii;
            copy(s);
        }
        return *this;
    }
    ~Smetka (){
        delete [] transakcii;
    }
    Smetka &operator +=(Transakcija *nova){
        Transakcija **tmp = new Transakcija*[brojtransakcii+1];
        for (int i=0; i<brojtransakcii; i++)
            tmp[i]=transakcii[i];
        tmp[brojtransakcii++]=nova;
        delete [] transakcii;
        transakcii=tmp;
        return *this;
    }
    double vkupnosaldo(){
        double vkupno=pocetnosaldo;
        for (int i=0; i<brojtransakcii; i++)
            vkupno+=transakcii[i]->voDenari();
        return vkupno;
    }
    void izvestajVoDenari() {
        double vkupno = vkupnosaldo();
        cout<<"Korisnikot so smetka: "<<smetka<<" ima momentalno saldo od "<<vkupno<<" MKD"<<endl;
    }
    void pecatiTransakcii() {
        for (int i=0; i<brojtransakcii; i++)
            transakcii[i]->pecati();
    }
};
int main () {

	Smetka s ("300047024112789",1500);

	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];

	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;
		if (tip==2){
			cin>>valuta;
			try{
			Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
			s+=t;}
            catch(InvalidDateException &d){
                d.message();
            }
            catch(NotSupportedCurrencyException &s){
                s.message();
            }
		}
		else {
            try{
			Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
			s+=t;}
            catch(InvalidDateException &d){
                d.message();
            }
            catch(NotSupportedCurrencyException &s){
                s.message();
            }
		}

	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();


    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();




	return 0;
}
