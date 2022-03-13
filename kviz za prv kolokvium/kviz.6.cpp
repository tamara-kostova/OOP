/*Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци),
предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).
Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од
возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).
Треба да се направи функција со потпис
void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од
железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри,
да се испечати релацијата на последниот таков.*/
#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
char relacija[50];
float km;
int brpatnici;
};

struct ZeleznickaStanica{
char grad[20];
Voz vozovi[30];
int brvozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
    float najkratka=100000;
    int indeksi, indeksj;
    for(int i=0, flag=0; i<n; i++)
        for(int j=0; j<zs[i].brvozovi; j++){
         if(!(strncmp(zs[i].vozovi[j].relacija, grad, strlen(grad)))){
             if (flag){
                najkratka=zs[i].vozovi[i].km;
                flag=0;
                indeksi=i;
                indeksj=j;
             }
             else {
                if (zs[i].vozovi[j].km<=najkratka){
                    najkratka=zs[i].vozovi[j].km;
                    indeksi=i;
                    indeksj=j;}
             }}
    }
    cout<<"Najkratka relacija: "<<"-"<<zs[indeksi].vozovi[indeksj].relacija<<" ("<<zs[indeksi].vozovi[indeksj].km<<" km)"<<endl;
}
int main(){

    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        char grad[20];
        int brvozovi;
        cin>>zStanica[i].grad>>zStanica[i].brvozovi;
        for(int j=0; j<zStanica[i].brvozovi; j++){
                char relacija[50];
                int km, brpatnici;
                cin>>zStanica[i].vozovi[j].relacija>>zStanica[i].vozovi[j].km>>zStanica[i].vozovi[j].brpatnici;
        }
    }

    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
