#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(char *boja, int gustina){
        strcpy(this->boja, boja);
        this->gustina=gustina;
    }
};
class Kocka : public Igrachka, public Forma{
    int visina;
    int sirina;
    int dlabocina;
public:
    Kocka (char *boja="", int gustina=0, int visina=0, int sirina=0, int dlabocina=0) : Forma(boja,gustina){
        this->visina=visina;
        this->sirina=sirina;
        this->dlabocina=dlabocina;
    }
    float getMasa() {
        return getVolumen()*gustina;
    }
    float getVolumen(){
        return visina*sirina*dlabocina;
    }
    float getPlostina(){
        return 2*(visina*sirina + visina*dlabocina + dlabocina*sirina);
    }
};
class Topka : public Igrachka, public Forma{
    int radius;
public:
    Topka(char *boja="", int gustina=0, int radius=0) : Forma(boja, gustina){
        this->radius=radius;
    }
    float getMasa() {
        return getVolumen()*gustina;
    }
    float getVolumen(){
        return radius*radius*radius*3.14*4/3;
    }
    float getPlostina(){
        return radius*radius*3.14*4;
    }
};

int main(){
    int n, vkupno=0;
    cin>>n;
    Igrachka **kupche = new Igrachka*[n];
    int k, gustina, visina, sirina, dlabocina, radius;
    char boja[100];
    for (int i=0; i<n; i++){
        cin>>k;
        if (k==1){
            cin>>boja;
            cin>>gustina>>radius;
            kupche[i]=new Topka(boja,gustina,radius);
        }
        if (k==2){
            cin>>boja;
            cin>>gustina>>visina>>sirina>>dlabocina;
            kupche[i]=new Kocka(boja,gustina,visina, sirina, dlabocina);
        }
        vkupno+=kupche[i]->getMasa();
    }
    cin>>boja>>gustina>>visina>>sirina>>dlabocina;
    Kocka petra(boja,gustina,visina,sirina,dlabocina);
    if(vkupno > petra.getMasa())
        cout<<"DA"<<endl;
    else
        cout<<"NE"<<endl;

    float maxvolumen=kupche[0]->getVolumen(), minplostina=kupche[0]->getPlostina();
    for (int i=1; i<n; i++){
        if (kupche[i]->getVolumen()>maxvolumen)
            maxvolumen=kupche[i]->getVolumen();
        if (kupche[i]->getPlostina()<minplostina)
            minplostina=kupche[i]->getPlostina();
    }

    cout<<"Razlikata e: "<<abs(maxvolumen-petra.getVolumen())<<endl;
    cout<<"Razlikata e: "<<abs(minplostina-petra.getPlostina())<<endl;

	return 0;
}
