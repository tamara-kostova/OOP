#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char trener[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *trener="", int *golovi=nullptr){
        strcpy(this->trener, trener);
        for (int i=0; i<10; i++)
            this->golovi[i]=golovi[i];
    }
    virtual int uspeh () = 0;
    virtual char *getchar() = 0;
    bool operator > (FudbalskaEkipa &f){
        return uspeh()>f.uspeh();
    }
    friend ostream &operator<<(ostream &o, FudbalskaEkipa &f){
        o<<f.getchar()<<endl<<f.trener<<endl<<f.uspeh()<<endl;
        return o;
    }
    FudbalskaEkipa &operator +=(int n){
        int tmp[10];
        tmp[9]=n;
        for(int i=8; i>=0; i--)
            tmp[i]=golovi[i+1];
        for (int i=0; i<10; i++)
            golovi[i]=tmp[i];
        return *this;
    }
};
class Klub : public FudbalskaEkipa{
    char ime[50];
    int tituli;
public:
    Klub(char *trener="", int *golovi=nullptr, char *ime="", int tituli=0) : FudbalskaEkipa(trener, golovi){
        strcpy(this->ime, ime);
        this->tituli=tituli;
    }
    int uspeh(){
        int zbir=0;
        for (int i=0; i<10; i++)
            zbir+=golovi[i];
        return zbir*3+tituli*1000;
    }
    char *getchar(){
        return ime;
    }
};
class Reprezentacija : public FudbalskaEkipa{
    char drzava[50];
    int megunarodninastapi;
public:
    Reprezentacija(char *trener="", int *golovi=nullptr, char *drzava="", int megunarodninastapi=0) : FudbalskaEkipa(trener, golovi){
        strcpy(this->drzava, drzava);
        this->megunarodninastapi=megunarodninastapi;
    }
    int uspeh(){
        int zbir=0;
        for (int i=0; i<10; i++)
            zbir+=golovi[i];
        return zbir*3+megunarodninastapi*50;
    }
    char *getchar(){
        return drzava;
    }
};
void najdobarTrener(FudbalskaEkipa **ekipi, int n){
    FudbalskaEkipa *najdobra = ekipi[0];
    for (int i=1; i<n; i++)
        if (*ekipi[i]>*najdobra)
            najdobra=ekipi[i];
    cout<<*najdobra;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
