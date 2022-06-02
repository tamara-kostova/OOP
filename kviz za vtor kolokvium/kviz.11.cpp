#include<iostream>
#include<string.h>
using namespace std;

class Delo{
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime="", int godina=0, char *zemja=""){
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }
    bool operator == (Delo &d){
        if (strcmp(ime,d.ime)==0) return true;
        return false;
    }
    char *getzemja(){
        return zemja;
    }
    char *getIme(){
        return ime;
    }
};
class Pretstava{
protected:
    Delo d;
    int karti;
    char data[15];
public:
    Pretstava(Delo d, int karti, char *data){
            this->d = d;
            this->karti=karti;
            strcpy(this->data, data);
    }
    virtual int cena(){
        int n, m;
        if ((data[6]=='1'&&data[7]=='9')||(data[6]=='2'&&data[7]=='0')) m=50;
        else if (data[6]=='1'&&data[7]=='8') m=75;
        else m=100;
        if (!strcmp(d.getzemja(),"Italija")) n=125;
        else if (!strcmp(d.getzemja(),"Rusija")) n=150;
        else n=130;
        return m+n;
    }
    Delo getDelo(){
        return d;
    }
    int getkarti(){
        return karti;
    }
};
class Opera : public Pretstava{
public:
    Opera(Delo d, int karti, char *data) : Pretstava(d, karti, data){
    }

};
class Balet : public Pretstava{
static int cenabalet;
public:
    Balet(Delo d, int karti, char *data) : Pretstava(d, karti, data){
    }
    static int setCenaBalet(int cenaBalet){
        Balet::cenabalet=cenaBalet;
    }
    int cena(){
        return Pretstava::cena()+cenabalet;
    }
};
int Balet::cenabalet=150;
int prihod(Pretstava **pretstavi, int n){
    int suma=0;
    for (int i=0; i<n; i++)
        suma+=pretstavi[i]->cena()*pretstavi[i]->getkarti();
    return suma;
}
int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo &delo){
    int vkupno=0;
    for (int i=0; i<n; i++)
        if (pretstavi[i]->getDelo()==delo)
            vkupno++;
    return vkupno;
}

Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
