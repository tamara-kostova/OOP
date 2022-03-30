#include <iostream>
#include <cstring>
using namespace std;
enum zanr {akcija, komedija, drama};
class Film{
private:
    char *ime;
    int memorija;
    zanr kojzanr;
    void copy(const Film &f){
        this->ime=new char[strlen(f.ime)+1];
        strcpy(this->ime, f.ime);
        this->memorija=f.memorija;
        this->kojzanr=f.kojzanr;
    }
public:
    Film(char *ime="", int memorija=0, zanr kojzanr=akcija){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->memorija=memorija;
        this->kojzanr=kojzanr;
    }
    Film (const Film &f){
        copy (f);
    }
    Film &operator=(const Film &f){
        if (this!=&f){
            delete [] ime;
            copy(f);
        }
        return *this;
    }
    ~Film(){
        delete [] ime;
    }
    int getmemorija(){
        return this->memorija;
    }
    zanr getzanr(){
        return kojzanr;
    }
    void pecati(){
        cout<<ime<<endl;
        cout<<this->memorija<<"MB-"<<"\""<<ime<<"\""<<endl;
    }
};
class DVD{
private:
    Film filmovi[5];
    int broj;
    int kapacitet;
public:
    DVD(){
    }
    DVD(int kapacitet){
        this->kapacitet=kapacitet;
    }
    ~DVD(){}
    int getBroj(){
        return broj;
    }
    Film getFilm (int i){
        return filmovi[i];
    }
    void dodadiFilm (Film f){
        if (this->broj<5){
            int vkupno=0;
            for (int i=0; i<this->broj; i++)
                vkupno+=filmovi[i].getmemorija();
            if (vkupno+f.getmemorija()<=kapacitet){
                filmovi[broj++]=f;
            }
        }
    }
    void pecatiFilmoviDrugZanr(zanr z){
        for (int i=0; i<broj; i++){
            if (filmovi[i].getzanr()!=z)
                filmovi[i].pecati();
        }
    }
    float procentNaMemorijaOdZanr(zanr z){
        int vkupno=0, p=0;
        for (int i=0; i<broj; i++){
            vkupno+=filmovi[i].getmemorija();
            if (filmovi[i].getzanr()==z)
                p+=filmovi[i].getmemorija();
        }
    return p*100.0/vkupno;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
		cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
		DVD omileno(40);
		cin >> n;
		for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

	}

    return 0;
}
