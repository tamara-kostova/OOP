#include <iostream>
#include <cstring>
using namespace std;

class Gitara{
private:
    char seriski[25];
    double nabavna;
    int godina;
    char tip[40];
public:
    Gitara(){};
    Gitara(char *_tip, char *_seriski, int _godina, double _nabavna){
        strcpy(seriski,_seriski);
        nabavna=_nabavna;
        godina=_godina;
        strcpy(tip,_tip);
    };
    ~Gitara(){};
    char *getSeriski(){
        return seriski;}
    int getGodina(){
        return godina;}
    char *getTip(){
        return tip;}
    double getNabavna(){
        return nabavna;}
    void pecati(){
       cout<<seriski<<" "<<tip<<" "<<nabavna<<endl;
    }
    bool daliIsti(Gitara &g){
         return strcmp(this->seriski,g.seriski)==0;
        }
};
class Magacin{
private:
    char ime[30];
    char lokacija[60];
    Gitara *gitari;
    int n;
    int godina;
public:
    Magacin(char *_ime="", char *_lokacija="", int _godina=0){
        godina=_godina;
        strcpy(ime,_ime);
        gitari=NULL;
        n=0;
        strcpy(lokacija,_lokacija);
    }
    Magacin(const Magacin & m)
        {
            strcpy(this->lokacija,m.lokacija);
            strcpy(this->ime,m.ime);
            this->godina = m.godina;
            gitari = new Gitara[m.n];
            for(int i =0;i<m.n;i++)
                gitari[i] = m.gitari[i];
            n= m.n;
        }

        Magacin & operator=(const Magacin & m)
        {
            delete [] gitari;
            strcpy(this->lokacija,m.lokacija);
            strcpy(this->ime,m.ime);
            this->godina= m.godina;
            gitari = new Gitara[m.n];
            for(int i =0;i<m.n;i++)
                gitari[i] = m.gitari[i];
            n= m.n;
            return *this;
        }
    ~Magacin(){}
    double vrednost(){
        double vkupno;
        for (int i=0, vkupno=0; i<n; i++, vkupno+=gitari[i].getNabavna())
        return vkupno;
    }
    void dodadi(Gitara d){
        Gitara * tmp = new Gitara[n+1];
            for(int i=0;i<n;i++)
                tmp[i]=gitari[i];
            tmp[n++]=d;
            delete [] gitari;
            gitari=tmp;
    }
    void prodadi(Gitara g){
        int novbroj=0;
            for(int i=0;i<n;i++)
                if(!gitari[i].daliIsti(g))
                    novbroj++;
            Gitara *tmp=new Gitara[novbroj];
            int j=0;
            for(int i=0;i<n;i++)
            {
                if(!gitari[i].daliIsti(g))
                {
                   tmp[j]=gitari[i];
                   j++;
                }
            }
            delete [] gitari;
            gitari=tmp;
            n=novbroj;
    }
    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        for(int i=0;i<n;i++)
            {
                if(daliNovi&&gitari[i].getGodina()>godina)
                    gitari[i].pecati();
                else if(!daliNovi)
                   gitari[i].pecati();
            }
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, godina;
	float cena;
	char seriski[50],tip[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
		cout<<g.getTip()<<endl;
		cout<<g.getSeriski()<<endl;
		cout<<g.getGodina()<<endl;
		cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
		Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
		cin>>n;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;
                Gitara g(tip,seriski, godina,cena);
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
   else if(testCase ==6)
        {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
				kb.dodadi(g);
			}
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
        }
    return 0;
}
