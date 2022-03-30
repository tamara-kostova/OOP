#include<iostream>
#include <cstring>
using namespace std;


class Avtomobil{
private:
    char boja[20];
    char brend[20];
    char model[20];
    void copy(const Avtomobil &other){
        strcpy(this->boja, other.boja);
        strcpy(this->brend, other.brend);
        strcpy(this->model, other.model);
    }
public:
    Avtomobil(){}
    Avtomobil(char *boja, char *brend, char *model){
        strcpy(this->boja, boja);
        strcpy(this->brend, brend);
        strcpy(this->model, model);
    }
    Avtomobil (const Avtomobil &other){
        copy(other);
    }
    Avtomobil &operator=(const Avtomobil &other){
        if (this!=&other)
            copy(other);
        return *this;
    }
    ~Avtomobil(){}
    char *getBoja (){
        return this->boja;
    }
    char *getBrend (){
        return this->brend;
    }
    char *getModel (){
        return this->model;
    }
};

class ParkingPlac{
private:
    char adresa[20];
    char *id;
    int cena;
    int zarabotka=0;
    Avtomobil *avtomobili;
    int parkirani;
    void copy(const ParkingPlac &other){
        strcpy(this->adresa, other.adresa);
        this->id=new char[strlen(other.id)+1];
        strcpy(this->id, other.id);
        this->cena=other.cena;
        this->zarabotka=other.zarabotka;
        this->parkirani=other.parkirani;
        this->avtomobili=new Avtomobil[parkirani];
        for (int i=0; i<parkirani;i++)
            this->avtomobili[i]=other.avtomobili[i];
    }
public:
    ParkingPlac (char *adresa="", char *id="", int cena=0){
        strcpy(this->adresa, adresa);
        this->id=new char[strlen(id)+1];
        strcpy(this->id, id);
        this->cena=cena;
    }
    ParkingPlac(const ParkingPlac &other){
        copy(other);
    }
    ParkingPlac &operator=(const ParkingPlac &other){
        if (this!=&other){
            delete [] id;
            delete [] avtomobili;
            copy(other);
        }
        return *this;
    }
    ~ParkingPlac(){
        //delete [] id;
        //delete [] avtomobili;
    }
    char *getId (){
        return this->id;
    }
    void platiCasovi (int casovi){
        this->zarabotka+=casovi*this->cena;
    }
    bool daliIstaAdresa(ParkingPlac p){
        return strcmp(this->adresa, p.adresa)==0;
    }
    void parkirajVozilo(Avtomobil novoVozilo){
        Avtomobil *tmp = new Avtomobil[this->parkirani+1];
        for (int i=0; i<parkirani; i++)
            tmp[i]=avtomobili[i];
        tmp[parkirani++]=novoVozilo;
        delete [] avtomobili;
        avtomobili=tmp;
    }
    void pecatiParkiraniVozila(){
    cout<<"Vo parkingot se parkirani slednite vozila:"<<endl;
    for(int i=0; i<this->parkirani; i++)
            cout<<i+1<<"."<<this->avtomobili[i].getBoja()<<" "<<this->avtomobili[i].getBrend()<<" "<<this->avtomobili[i].getModel()<<endl;
    }
    void pecati(){
        cout<<this->id<<" "<<this->adresa;
        if (this->zarabotka)
            cout<<" - "<<this->zarabotka<<" denari";
        cout<<endl;
    }
};

int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;

			ParkingPlac edna(adresa,id,cenacas);

	        p[i]=edna;
		}

		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;

	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++)
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
	    	Avtomobil novAvtomobil(boja, brend, model);
	    	najdobarPlac.parkirajVozilo(novAvtomobil);
	    }
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}
}
