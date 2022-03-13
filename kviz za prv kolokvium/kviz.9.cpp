#include<iostream>
#include <cstring>
using namespace std;

struct Laptop{
    char firma[100];
    float golemina;
    bool touch;
    float cena;
    void printlap(){
        cout<<firma<<" "<<golemina<<" "<<cena<<endl;
    }
};

struct ITStore{
    char ime[100];
    char lokacija[100];
    Laptop laptopi[100];
    int brlaptopi;
    void printits(){
        cout<<ime<<" "<<lokacija<<endl;
        for (int i=0; i<brlaptopi; i++)
            laptopi[i].printlap();
    }
};

void najeftina_ponuda (ITStore *itstores, int n){
    int min=1000000, indi=0, indj=0;
    for (int i=0; i<n; i++){
        for (int j=0; j<itstores[i].brlaptopi; j++)
        if (itstores[i].laptopi[j].touch){
            if (itstores[i].laptopi[j].cena<min){
                min=itstores[i].laptopi[j].cena;
                indi=i;
                indj=j;
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata:"<<endl<<itstores[indi].ime<<" "<<itstores[indi].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<itstores[indi].laptopi[indj].cena<<endl;
}

int main() {
    ITStore s[100];
    int n;
    cin >> n;
    for (int i=0; i<n; i++){
        cin>>s[i].ime>>s[i].lokacija>>s[i].brlaptopi;
        for (int j=0; j<s[i].brlaptopi; j++)
            cin>>s[i].laptopi[j].firma>>s[i].laptopi[j].golemina>>s[i].laptopi[j].touch>>s[i].laptopi[j].cena;
    }
    for(int i = 0; i<n; i++)
    	s[i].printits();
    najeftina_ponuda(s,n);
    return 0;
}
