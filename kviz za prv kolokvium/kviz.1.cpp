#include <iostream>
#include <cstring>
using namespace std;

enum tip{
pop,
rap,
rok
};

class Pesna{
private:
    char *ime;
    int vreme;
    tip Tip;
    void copy (const Pesna &other){
        this->ime = new char [strlen(other.ime)+1];
        strcpy(this->ime, other.ime);
        this->vreme=other.vreme;
        this->Tip=other.Tip;
    }
public:
    Pesna(char *ime="", int vreme=0, tip Tip=pop){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vreme=vreme;
        this->Tip=Tip;
    };
    Pesna (const Pesna &other){
        copy(other);
    }
    Pesna &operator =(const Pesna &other){
        if (this!=&other){
            delete [] ime;
            copy(other);
        }
        return *this;
    }
    ~Pesna(){};
    int get_vreme(){
        return vreme;}
    tip get_tip(){
        return Tip;}
    void pecati(){
        cout<<"\""<<ime<<"\"-"<<vreme<<"min"<<endl;
    }
};
class CD{
private:
    Pesna pesni[10];
    int brpesni;
    int maxvreme;
public:
    CD(){};
    CD(int _maxvreme){
        maxvreme=_maxvreme;
    };
    ~CD(){};
    Pesna getPesna(int i){
        return pesni[i];
    }
    int getBroj(){
        return brpesni;}
    void dodadiPesna (Pesna p){
        int vkupno=0;
        if (brpesni<10){
            for (int i=0; i<brpesni; i++)
                vkupno+=pesni[i].get_vreme();
                if (vkupno+p.get_vreme()<=maxvreme)
                    pesni[brpesni++]=p;
        }
    }
    void pecatiPesniPoTip(tip t){
        for (int i=0; i<brpesni; i++){
            if ((tip)pesni[i].get_tip()==(tip)t)
                pesni[i].pecati();
        }
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
