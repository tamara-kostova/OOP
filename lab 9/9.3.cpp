#include<iostream>
#include<cstring>
using namespace std;

class InvalidRegistration{
public:
    void message(){
        cout<<"Pogresno vnesena registracija"<<endl;
    }
};

class ImaMasa{
public:
    virtual double vratiMasa()=0;
    virtual void pecati()=0;
};
class PaketPijalok{
protected:
    double volumenEden;
    int kolicina;
    static double gustina;
    static double masaambalaza;
public:
    PaketPijalok(double volumenEden=0, int kolicina=0){
        this->volumenEden=volumenEden;
        this->kolicina=kolicina;
    }
    double vratiMasa(){
        return (gustina*volumenEden+masaambalaza)*kolicina;
    }
    static double getGustina(){
        return gustina;
    }
    double getVolumen(){
        return volumenEden;
    }
    void pecati(){
        cout<<"kolicina "<<kolicina;
    }
    int getKolicina(){
        return kolicina;
    }
};
double PaketPijalok::gustina=0.8;
double PaketPijalok::masaambalaza=0.2;

class PaketSok : public ImaMasa, public PaketPijalok{
    bool daliGaziran;
public:
    PaketSok(double volumenEden=0, int kolicina=0, bool daliGaziran=0) : PaketPijalok(volumenEden,kolicina){
        this->daliGaziran=daliGaziran;
    }
    double vratiMasa(){
        if (!daliGaziran) return PaketPijalok::vratiMasa()+0.1*kolicina;
        return PaketPijalok::vratiMasa();
    }
    void pecati(){
        cout<<"Paket sok"<<endl<<"kolicina "<<kolicina<<", so po "<<getVolumen()*getGustina()<<" l(dm3)"<<endl;
    }
};
class PaketVino : public ImaMasa, public PaketPijalok{
    double procentAlkohol;
public:
    PaketVino(double volumenEden=0, int kolicina=0, double procentAlkohol=0) : PaketPijalok(volumenEden,kolicina){
        this->procentAlkohol=procentAlkohol;
    }
    double vratiMasa(){
        return PaketPijalok::vratiMasa()*(0.9+procentAlkohol);
    }
    void pecati(){
        cout<<"Paket vino"<<endl<<"kolicina "<<kolicina<<", "<<procentAlkohol*100<<"% alkohol od po "<<getVolumen()*getGustina()<<" l(dm3)"<<endl;
    }
    double getProcentAlkohol(){
        return procentAlkohol;
    }
};
class Kamion{
    char registracija[50];
    char vozac[50];
    ImaMasa **elementi;
    int broj;
public:
    Kamion(char* vozac) {
        strcpy(this->vozac, vozac);
        broj=0;
        elementi = new ImaMasa * [broj];
    }
    Kamion(char* registracija, char *vozac) {
        if (!isalpha(registracija[0])||!isalpha(registracija[1])||!isalpha(registracija[6])||!isalpha(registracija[7]))
            throw InvalidRegistration();
        strcpy(this->vozac, vozac);
        strcpy(this->registracija,registracija);
        broj=0;
        elementi = new ImaMasa * [broj];
    }
    ~Kamion(){
        delete [] elementi;
    }
    void registriraj(char* registracija) {
        strcpy(this->registracija,registracija);
    }
    void dodadiElement(ImaMasa *nov) {
        ImaMasa **tmp = new ImaMasa *[broj+1];
        for (int i=0; i<broj; i++)
            tmp[i]=elementi[i];
        tmp[broj++]=nov;
        delete [] elementi;
        elementi=tmp;
    }
    double vratiVkupnaMasa() {
        double vkupno=0;
        for (int i=0; i<broj; i++)
            vkupno+=elementi[i]->vratiMasa();
        return vkupno;
    }
    void pecati() {
        cout<<"Kamion so registracija "<<registracija<<" i vozac "<<vozac<<" prenesuva:"<<endl;
        for (int i=0; i<broj; i++)
            elementi[i]->pecati();
    }
    Kamion pretovar(char* registracija, char* vozac) {
        Kamion tmp(registracija, vozac);
        double maxmasa=0, indeks=0;
        for (int i=0; i<broj; i++)
            if (elementi[i]->vratiMasa()>maxmasa){
                maxmasa=elementi[i]->vratiMasa();
                indeks=i;
            }
        for (int i=0; i<broj; i++)
            if (i!=indeks)
                tmp.dodadiElement(elementi[i]);
        return tmp;
    }
};

int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

            cin>>reg;
            cin>>ime;
            try{
            Kamion A(reg, ime);
            ImaMasa **d = new ImaMasa*[5];
            cin>>vol>>kol;
            cin>>g;
            d[0] = new PaketSok(vol, kol, g);
            cin>>vol>>kol;
            cin>>proc;
            d[1] = new PaketVino(vol, kol, proc);
            cin>>vol>>kol;
            cin>>proc;
            d[2] = new PaketVino(vol, kol, proc);
            cin>>vol>>kol;
            cin>>g;
            d[3] = new PaketSok(vol, kol, g);
            cin>>vol>>kol;
            cin>>proc;
            d[4] = new PaketVino(vol, kol, proc);

            A.dodadiElement(d[0]);
            A.dodadiElement(d[1]);
            A.dodadiElement(d[2]);
            A.dodadiElement(d[3]);
            A.dodadiElement(d[4]);
            A.pecati();
            cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;
            cin>>reg;
            cin>>ime;
            Kamion B = A.pretovar(reg, ime);
            B.pecati();
            cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;
            }
            catch(InvalidRegistration &ir){
                ir.message();
            }
}
