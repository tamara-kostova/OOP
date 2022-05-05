#include<cstring>
#include<iostream>
using namespace std;

class Secret{
public:
    virtual double simpleEntropy()  = 0;
    virtual int total() = 0;
};

bool operator ==(Secret &s1, Secret &s2){
    return (s1.simpleEntropy()==s2.simpleEntropy()&&s1.total()==s2.total());
}
bool operator !=(Secret &s1, Secret &s2){
    return !(s1.simpleEntropy()==s2.simpleEntropy()&&s1.total()==s2.total());
}

class DigitSecret : public Secret{
    private:
    int niza[100];
    int n;
    public:
    DigitSecret(){}

    DigitSecret(int *niza, int n){
        this->n=n;
        for (int i=0; i<n; i++)
            this->niza[i]=niza[i];
    }
    double simpleEntropy() {
        int vkupno=0;
        for (int i=0; i<n; i++){
            int isti=0;
            for (int j=0; j<n; j++)
                if (niza[i]==niza[j])
                    isti++;
            if (isti==1)
                vkupno++;
        }
        return (vkupno*1.0)/n;
    }
    int total() {
        return n;
    }
    friend ostream &operator <<(ostream &o, DigitSecret &ds){
        for (int i=0; i<ds.n; i++)
            o<<ds.niza[i];
        o<<" Simple entropy: "<<ds.simpleEntropy()<<" Total: "<<ds.total();
        return o;
    }

};

class CharSecret : public Secret{
    private:
    char niza[100];

    public:
    CharSecret(){}

    CharSecret(char *niza){
        strcpy(this->niza, niza);
    }

    double simpleEntropy() {
        int vkupno=0;
        for (int i=0; i<strlen(niza); i++){
            int isti=0;
            for (int j=0; j<strlen(niza); j++)
                if (niza[i]==niza[j])
                    isti++;
            if (isti==1)
                vkupno++;
        }
        return (vkupno*1.0)/strlen(niza);
    }
    int total() {
        return strlen(niza);
    }

    friend ostream &operator <<(ostream &o, CharSecret &cs){
        o<<cs.niza<<" Simple entropy: "<<cs.simpleEntropy()<<" Total: "<<cs.total();
        return o;
    }
};

void process(Secret ** secrets, int n){
    double maxentropy=secrets[0]->simpleEntropy();
    int indeks=0;
    for(int i=0; i<n; i++)
        if (secrets[i]->simpleEntropy()>maxentropy){
            maxentropy=secrets[i]->simpleEntropy();
            indeks=i;}
    DigitSecret *ds = dynamic_cast<DigitSecret*>(secrets[indeks]);
    if (ds)
        cout<<*ds;
    else{
        CharSecret *cs = dynamic_cast<CharSecret*>(secrets[indeks]);
        cout<<*cs;}
}

void printAll (Secret ** secrets, int n) {
    for (int i=0; i<n; i++){
        DigitSecret *ds=dynamic_cast<DigitSecret*>(secrets[i]);
        if(ds)
            cout<<*ds<<endl;
        CharSecret *cs=dynamic_cast<CharSecret*>(secrets[i]);
        if(cs)
        cout<<*cs<<endl;
    }
}


int main() {
    int n;
    cin >> n;
    if(n == 0) {
		cout << "Constructors" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
  		cout << "operator <<" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
  		cout << "== and !=" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
  		cout << "Secret processor" << endl;
		int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
		int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }

    return 0;
}
