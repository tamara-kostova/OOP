#include <iostream>
#include <cstring>
using namespace std;

class Masa{
private:
    int dolzina;
    int sirina;
public:
    Masa(){};
    Masa(int sirina, int dolzina){
        this->dolzina=dolzina;
        this->sirina=sirina;
    }
    ~Masa(){};
    void pecati(){
    cout<<" Masa: "<<this->sirina<<" "<<this->dolzina<<endl;
    }
};
class Soba{
private:
    Masa masa;
    int dolzina;
    int sirina;
public:
    Soba(){}
    Soba(int sirina, int dolzina, Masa masa){
        this->masa=masa;
        this->dolzina=dolzina;
        this->sirina=sirina;
    }
    ~Soba(){}
    void pecati(){
    cout<<"Soba: "<<this->sirina<<" "<<this->dolzina;
    masa.pecati();
    }
};
class Kukja{
private:
    Soba soba;
    char *adresa;
public:
    Kukja(){}
    Kukja(Soba soba, char *adresa){
        this->soba=soba;
        this->adresa=new char [strlen(adresa)+1];
        strcpy(this->adresa,adresa);
    }
    ~Kukja(){}
    void pecati(){
    cout<<"Adresa: "<<this->adresa<<" ";
    soba.pecati();
    }
};

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}

    return 0;
}
