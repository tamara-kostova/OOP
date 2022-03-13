#include <iostream>
#include <cstring>
using namespace std;

struct Igrac{
    char korisnickoIme[15];
    int nivo;
    int poeni;
};

struct KompjuterskaIgra{
    char ime[20];
    Igrac lista[30];
    int n;
};

void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int max=lista[0].n;
    KompjuterskaIgra najpopularna=lista[0];
    for (int i=1; i<n; i++)
        if (lista[i].n>max){
            max=lista[i].n;
            najpopularna=lista[i];
        }
    int maxpoeni=najpopularna.lista[0].poeni, maxnivo=najpopularna.lista[0].nivo, indeks;
    for (int i=1; i<najpopularna.n; i++){
        if (najpopularna.lista[i].poeni>maxpoeni){
            indeks=i;
            maxpoeni=najpopularna.lista[i].poeni;
            maxnivo=najpopularna.lista[i].nivo;
        }
        if (najpopularna.lista[i].poeni==maxpoeni){
            if (najpopularna.lista[i].nivo>maxnivo){
                indeks=i;
                maxpoeni=najpopularna.lista[i].poeni;
                maxnivo=najpopularna.lista[i].nivo;
            }
        }
    }
cout<<"Najdobar igrac e igracot so korisnicko ime "<<najpopularna.lista[indeks].korisnickoIme<<" koj ja igra igrata "<<najpopularna.ime<<endl;

}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
