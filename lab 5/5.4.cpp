#include <iostream>
#include <string.h>
using namespace std;

class PlDrustvo{
    char *ime;
    int turi=0;
    int clenovi=0;
public:
    PlDrustvo(){
        ime = new char [1];
        strcpy(this->ime, "");
    }
    PlDrustvo(char *ime, int turi, int clenovi){
        this->ime=new char [strlen(ime)+1];
        strcpy(this->ime, ime);
        this->turi=turi;
        this->clenovi=clenovi;
    }
    int getClenovi(){
        return clenovi;
    }
    bool operator >(const PlDrustvo &drugo){
        return (this->clenovi>drugo.clenovi);
    }
    bool operator <(const PlDrustvo &drugo){
        return (this->clenovi<drugo.clenovi);
    }
    friend ostream &operator <<(ostream &o, const PlDrustvo &pl){
        o<<"Ime: "<<pl.ime<<" Turi: "<<pl.turi<<" Clenovi: "<<pl.clenovi<<endl;
        return o;
    }
    PlDrustvo operator+(const PlDrustvo &drugo){
        if (this->clenovi>drugo.clenovi){
            PlDrustvo zbir(this->ime, this->turi, this->clenovi+drugo.clenovi);
            return zbir;
        }
            PlDrustvo zbir(drugo.ime, drugo.turi, this->clenovi+drugo.clenovi);
            return zbir;
    }
};
void najmnoguClenovi(PlDrustvo *drustva, int broj){
        int indeks=0, max=0;
        for (int i=0; i<broj; i++){
            if (drustva[i].getClenovi()>max){
                max=drustva[i].getClenovi();
                indeks=i;
            }
        }
        cout<<"Najmnogu clenovi ima planinarskoto drustvo: "<<drustva[indeks]<<endl;
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

   	}
    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
