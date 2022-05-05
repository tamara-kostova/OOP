#include <iostream>
#include <cstring>
using namespace std;
class ZicanInstrument{
protected:
    char ime[20];
    int zici;
    float osnovnacena;
public:
    ZicanInstrument(char *ime, int zici, float osnovnacena){
        strcpy(this->ime, ime);
        this->zici=zici;
        this->osnovnacena=osnovnacena;
    }
    virtual float cena() = 0;
    int getzici(){
        return zici;
    }
    friend bool operator==(ZicanInstrument *z1, ZicanInstrument &z2){
        if(z1->getzici()==z2.getzici()) return true;
        return false;
    }
};
class Mandolina : public ZicanInstrument{
    char forma[20];
public:
    Mandolina (char *ime, int zici, float osnovnacena, char *forma) : ZicanInstrument(ime, zici, osnovnacena){
        strcpy(this->forma, forma);
    }
    float cena(){
        if (!strcmp(forma, "Neapolitan"))
            return 1.15*osnovnacena;
        else return osnovnacena;
    }
    friend ostream &operator <<(ostream &o, Mandolina &m){
        o<<m.ime<<" " <<m.zici<<" " <<m.cena()<<" " <<m.forma<<endl;
        return o;
    }
};
class Violina : public ZicanInstrument{
    float golemina;
public:
    Violina (char *ime, int zici, float osnovnacena, float golemina) : ZicanInstrument(ime, zici, osnovnacena){
        this->golemina=golemina;
    }
    float cena(){
        if (golemina==1.00)
            return 1.2*osnovnacena;
        if (golemina==0.25)
            return 1.1*osnovnacena;
        else return osnovnacena;
    }
    friend ostream &operator <<(ostream &o, Violina &v){
        o<<v.ime<<" " <<v.zici<<" " <<v.cena()<<" " <<v.golemina<<endl;
        return o;
    }
};
void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **ins, int n){
    for (int i=0; i<n; i++){
        if (ins[i]==zi)
            cout<<ins[i]->cena()<<endl;
    }
}

int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}
