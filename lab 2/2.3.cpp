/*Да се дефинира класа Film, во која ќе се чуваат информации за:

име низа од 100 знаци
режисер низа од 50 знаци
жанр низа од 50 знаци
година цел број
Сите променливи треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

default конструктор и конструктор со аргументи
метод за печатење на информациите за филмот
Дополнително да се реализира надворешна функција:

void pecati_po_godina(Film *f, int n, int godina) која ќе прима аргумент низа од филмови, вкупниот број на филмови и година,
а треба да ги отпечати само филмовите кои се направени во дадената година.*/
#include <iostream>
#include <cstring>
using namespace std;

class Film{
private:
char ime[100];
char reziser[50];
char zanr[50];
int godina;
public:
    Film(){};
    Film(char i[100],char r[50], char z[50], int g){
    strcpy(ime,i);
    strcpy(reziser,r);
    strcpy(zanr,z);
    godina=g;
    }
    ~Film(){};

void pecati_po_godina(Film *f, int n, int godina){
    for (int i=0; i<n; i++){
        if (f[i].godina==godina){
            cout<<"Ime: "<<f[i].ime<<endl;
            cout<<"Reziser: "<<f[i].reziser<<endl;
            cout<<"Zanr: "<<f[i].zanr<<endl;
            cout<<"Godina: "<<f[i].godina<<endl;
        }
    }
    }
};

int main() {
 	int n;
 	cin >> n;
 	Film filmovi[n];
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		filmovi[i]=Film(ime,reziser,zanr,godina);
 	}
 	int godina;
 	cin >> godina;
 	filmovi[0].pecati_po_godina (filmovi, n, godina);
 	return 0;
 }
