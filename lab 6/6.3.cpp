#include <iostream>
#include <cstring>
using namespace std;

class Lekar{
protected:
    int faksimil;
    char ime[11];
    char prezime[11];
    double osnovnaPlata;
public:
    Lekar(int faksimil=0, char *ime="", char *prezime="", double osnovnaPlata=0.0){
        this->faksimil=faksimil;
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->osnovnaPlata=osnovnaPlata;
    }
    Lekar (const Lekar &l){
        faksimil=l.faksimil;
        strcpy(ime, l.ime);
        strcpy(prezime, l.prezime);
        osnovnaPlata=l.osnovnaPlata;
    }
    void pecati(){
        cout<<faksimil<<": "<<ime<<" "<<prezime<<endl;
    }
    double plata(){
        return osnovnaPlata;
    }
};
class MaticenLekar : public Lekar{
    int pacienti;
    double *kotizacii;
    void copy (const MaticenLekar &m){
        strcpy(ime,m.ime);
        strcpy(prezime,m.prezime);
        osnovnaPlata=m.osnovnaPlata;
        faksimil=m.faksimil;
        pacienti=m.pacienti;
        kotizacii=new double[pacienti];
        for (int i=0; i<pacienti; i++)
            kotizacii[i]=m.kotizacii[i];
    }
public:
    MaticenLekar():Lekar(){
        kotizacii = new double [0];
    }
    MaticenLekar(Lekar &l, int pacienti, double *kotizacii):Lekar(l){
        this->pacienti=pacienti;
        this->kotizacii=new double [pacienti];
        for (int i=0; i<pacienti; i++)
            this->kotizacii[i]=kotizacii[i];
    }
    MaticenLekar(const MaticenLekar &m){
        copy(m);
    }
    MaticenLekar &operator=(const MaticenLekar &m){
        if (this!=&m){
            delete [] kotizacii;
            copy(m);
        }
        return *this;
    }
    ~MaticenLekar(){
        delete [] kotizacii;
    }
    double prosek(){
        double p=0;
        for (int i=0; i<pacienti; i++)
            p+=kotizacii[i];
        return p/pacienti;
    }
    void pecati(){
        Lekar::pecati();
        cout<<"Prosek na kotizacii: "<<prosek()<<endl;
    }
    double plata(){
        return osnovnaPlata+0.3*prosek();
    }
};

int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;

	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];

	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
	}

	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
	}

	int testCase;
	cin>>testCase;

	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
		}
	}

	delete [] lekari;
	delete [] maticni;

	return 0;
}
