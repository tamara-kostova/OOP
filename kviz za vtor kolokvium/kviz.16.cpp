#include <iostream>
#include <cstring>
using namespace std;

class Transport{
protected:
    char destinacija[20];
    int osnovnacena;
    int rastojanie;
public:
    Transport(char *destinacija="", int osnovnacena=0, int rastojanie=0){
        strcpy(this->destinacija, destinacija);
        this->osnovnacena=osnovnacena;
        this->rastojanie=rastojanie;
    }
    virtual float cenaTransport()=0;
    bool operator<(Transport &t){
        return rastojanie<t.rastojanie;
    }
    friend ostream &operator<<(ostream &o, Transport &t){
        return o<<t.destinacija<<" "<<t.rastojanie<<" "<<t.cenaTransport()<<endl;
    }
    int getrastojanie(){
        return rastojanie;
    }
};
class AvtomobilTransport : public Transport{
    bool sofer;
public:
    AvtomobilTransport(char *destinacija="", int osnovnacena=0, int rastojanie=0, bool sofer=0) : Transport(destinacija,osnovnacena,rastojanie){
        this->sofer=sofer;
    }
    float cenaTransport(){
        if (sofer) return 1.2*osnovnacena;
        return osnovnacena;
    }
};
class KombeTransport : public Transport{
    int patnici;
public:
    KombeTransport(char *destinacija="", int osnovnacena=0, int rastojanie=0, int patnici=0) : Transport(destinacija,osnovnacena,rastojanie){
        this->patnici=patnici;
    }
    float cenaTransport(){
        return osnovnacena-200*patnici;
    }
};
void pecatiPoloshiPonudi (Transport **ponudi, int n, Transport &t){
    Transport *tmp;
    for (int i=0; i<n; i++)
        for (int j=i; j<n; j++)
    if (ponudi[i]->getrastojanie()>ponudi[j]->getrastojanie()){
            tmp=ponudi[i];
            ponudi[i]=ponudi[j];
            ponudi[j]=tmp;
    }
    for (int i=0; i<n; i++)
        if (ponudi[i]->cenaTransport()>t.cenaTransport())
            cout<<*ponudi[i];
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
