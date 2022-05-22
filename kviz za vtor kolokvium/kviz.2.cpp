#include <iostream>
#include <cstring>
using namespace std;
class Vozac{
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool veteran;
public:
    Vozac(const char *ime="", int vozrast=0, int trki=0, bool veteran=false){
        strcpy(this->ime, ime);
        this->vozrast=vozrast;
        this->trki=trki;
        this->veteran=veteran;
    }
    friend ostream &operator<<(ostream &o, Vozac &v){
        o<<v.ime<<endl<<v.vozrast<<endl<<v.trki<<endl;
        if (v.veteran) cout<<"VETERAN"<<endl;
    }
    virtual float zarabotuvacka()=0;
    virtual float danok () = 0;
    bool operator ==(Vozac &v){
        return (zarabotuvacka()==v.zarabotuvacka());
    }
};
class Avtomobilist : public Vozac{
    float cena;
public:
    Avtomobilist(const char *ime="", int vozrast=0, int trki=0, bool veteran=false, float cena=0) : Vozac(ime, vozrast,trki,veteran){
        this->cena=cena;
    }
    float zarabotuvacka(){
        return cena/5;
    }
    float danok(){
        if (trki>10)
            return 0.15*zarabotuvacka();
        return 0.1*zarabotuvacka();
    }
};
class Motociklist: public Vozac{
    int moknost;
public:
    Motociklist(const char *ime="", int vozrast=0, int trki=0, bool veteran=false, int moknost=0) : Vozac(ime, vozrast,trki,veteran){
        this->moknost=moknost;
    }
    float zarabotuvacka(){
        return moknost*20;
    }
    float danok(){
        if (veteran)
            return 0.25*zarabotuvacka();
        return 0.2*zarabotuvacka();
    }
};
int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v){
    int isti=0;
    for (int i=0; i<n; i++)
        if (vozaci[i]->zarabotuvacka()==v->zarabotuvacka())
            isti++;
    return isti;
}

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
