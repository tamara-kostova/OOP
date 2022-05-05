#include<iostream>
using namespace std;

class Vozilo{
protected:
    float masa;
    int sirina;
    int visina;
public:
    Vozilo(float masa=0, int sirina=0, int visina=0){
        this->masa=masa;
        this->sirina=sirina;
        this->visina=visina;
    }
    virtual int vratiDnevnaCena() = 0;
    float getMasa(){
        return masa;
    }
    int getSirina(){
        return sirina;
    }
    int getVisina(){
        return visina;
    }
};
class Avtomobil : public Vozilo{
    int vrati;
public:
    Avtomobil(float masa, int sirina, int visina,int vrati) : Vozilo (masa,sirina,visina){
        this->vrati= vrati;
    }
    int vratiDnevnaCena(){
        if (vrati<5) return 100;
        else return 130;
    }
};
class Avtobus : public Vozilo{
    int patnici;
public:
    Avtobus(float masa, int sirina, int visina, int patnici) : Vozilo (masa,sirina,visina){
        this->patnici= patnici;
    }
    int vratiDnevnaCena(){
        return 5*patnici;
    }
};
class Kamion :public Vozilo{
    float nosivost;
public:
    Kamion(float masa, int sirina, int visina, float nosivost) : Vozilo (masa,sirina,visina){
        this->nosivost = nosivost;
    }
    int vratiDnevnaCena(){
        return (masa+nosivost)*0.02;
    }
    float getNosivost(){
        return nosivost;
    }
};
class ParkingPlac{
    Vozilo ** vozila;
    int broj;
public:
    ParkingPlac(){
        vozila = new Vozilo *[0];
        broj=0;
    }
    ~ParkingPlac(){
        delete [] vozila;
    }
    ParkingPlac &operator+= (Vozilo *v){
        Vozilo **tmp = new Vozilo*[broj+1];
        for (int i=0; i<broj; i++)
            tmp[i]=vozila[i];
        tmp[broj++]=v;
        delete [] vozila;
        vozila=tmp;
        return *this;
    }
    float presmetajVkupnaMasa(){
        float vkupno=0;
        for (int i=0; i<broj; i++)
            vkupno+=vozila[i]->getMasa();
        return vkupno;
    }
    int brojVozilaPoshirokiOd(int l){
        int vkupno=0;
        for (int i=0; i<broj; i++)
            if (vozila[i]->getSirina()>l)
            vkupno++;
        return vkupno;
    }
    void pecati(){
        int avtomobili=0, avtobusi=0, kamioni=0;

        for (int i=0; i<broj; i++){
            Avtomobil *a=dynamic_cast<Avtomobil *>(vozila[i]);
            if (a!=0) avtomobili++;
            Avtobus *av=dynamic_cast<Avtobus *>(vozila[i]);
            if (av!=0) avtobusi++;
            Kamion *k =dynamic_cast<Kamion *>(vozila[i]);
            if (k!=0) kamioni++;
        }
        cout<<"Brojot na avtomobili e "<<avtomobili<<", brojot na avtobusi e "<<avtobusi<<" i brojot na kamioni e "<<kamioni<<"."<<endl;
    }
    int pogolemaNosivostOd(Vozilo& v){
        int vkupno=0;
        for (int i=0; i<broj; i++){
            Kamion *k = dynamic_cast<Kamion *>(vozila[i]);
            if (k!=0)
                if (k->getNosivost()>v.getMasa())
            vkupno++;
        }
        return vkupno;
    }
    int vratiDnevnaZarabotka(){
        int vkupno=0;
        for (int i=0; i<broj; i++)
            vkupno+=vozila[i]->vratiDnevnaCena();
        return vkupno;
    }
};

int main(){
ParkingPlac p;

int n;
cin>>n;
int shirina,visina, broj;
float masa,nosivost;
for (int i=0;i<n;i++){
    int type;
    cin>>type;
    if(type==1){
        cin>>masa>>shirina>>visina>>broj;
        Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
        p+=a;
    }
    if(type==2){
        cin>>masa>>shirina>>visina>>broj;
        p+=new Avtobus(masa,shirina,visina,broj);
    }
    if(type==3){
        cin>>masa>>shirina>>visina>>nosivost;
        p+=new Kamion(masa,shirina,visina,nosivost);
    }
}

p.pecati();

cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
Avtomobil a(1200,4,3,5);
cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;
}
