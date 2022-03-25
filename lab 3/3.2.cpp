#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
private:
	char *ime;
	char *prezime;
	char *embg;
public:
    Potpisuvac (){
        ime=nullptr;
        prezime=nullptr;
        embg=nullptr;
    }
    Potpisuvac(char *ime, char *prezime, char *embg){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->prezime=new char[strlen(prezime)+1];
        strcpy(this->prezime,prezime);
        this->embg=new char[strlen(embg)+1];
        strcpy(this->embg,embg);
    }
    ~Potpisuvac(){}
    char *getembg(){return this->embg;}
};
class Dogovor{
private:
    int broj;
    char *kategorija;
    Potpisuvac potpisuvaci[3];
public:
    Dogovor(){};
    Dogovor (int broj, char *kategorija, Potpisuvac *potpisuvaci){
        this->broj=broj;
        this->kategorija=new char [strlen(kategorija)+1];
        strcpy(this->kategorija, kategorija);
        for (int i=0; i<3; i++)
            this->potpisuvaci[i]=potpisuvaci[i];
    }
    bool proverka(){
        for (int i=0; i<3; i++)
            for (int j=i+1; j<3; j++)
                if(!(strcmp(this->potpisuvaci[i].getembg(),this->potpisuvaci[j].getembg())))
                    return true;
        return false;
        }
};


//ne smee da se menuva main funkcijata
int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p1(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p2(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p3(ime, prezime, embg);
    	cin >> broj >> kategorija;
    	Potpisuvac p[3];
    	p[0] = p1; p[1] = p2; p[2] = p3;
    	Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
    	if(d.proverka() == true)
    	    cout << "Postojat potpishuvaci so ist EMBG" << endl;
    	else
    	    cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
