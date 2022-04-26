#include <iostream>
#include <cstring>
using namespace std;

class Ekipa{
protected:
    char ime[15];
    int porazi;
    int pobedi;
public:
    Ekipa(char *ime, int pobedi, int porazi){
        strcpy(this->ime, ime);
        this->pobedi=pobedi;
        this->porazi=porazi;
    }
    void pecati(){
        cout<<"Ime: "<<ime<<" Pobedi: "<<pobedi<<" Porazi: "<<porazi<<endl;
    }
};
class FudbalskaEkipa : public Ekipa{
int crveni;
int zolti;
int nereseni;
public:
    FudbalskaEkipa(char *ime, int pobedi, int porazi, int crveni, int zolti, int nereseni) : Ekipa (ime, pobedi, porazi){
        this->crveni=crveni;
        this->zolti=zolti;
        this->nereseni=nereseni;
    }
    void pecati(){
        cout<<"Ime: "<<ime<<" Pobedi: "<<pobedi<<" Porazi: "<<porazi<<" Nereseni: "<<nereseni<<" Poeni: "<<3*pobedi+nereseni<<endl;
    }
};

int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}
