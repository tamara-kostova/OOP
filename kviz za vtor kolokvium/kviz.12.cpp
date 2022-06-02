#include <iostream>
#include <cstring>

using namespace std;
enum tip{smartphone, computer};

class InvalidProductionDate{
public:
    InvalidProductionDate(){
    }
    void showmessage(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class Device{
    char model[100];
    tip type;
    static float proverka;
    int godina;
    void copy(Device &d){
        strcpy(model,d.model);
        type=d.type;
        godina=d.godina;
    }
public:
    Device(char *model="", int type=0, float godina=0){
        strcpy(this->model,model);
        this->type=(tip)type;
        this->godina=godina;
    }
    Device (Device &d){
        copy(d);
    }
    Device &operator=(Device &d){
        if (this!=&d)
            copy(d);
        return *this;
    }
    friend ostream &operator<<(ostream &o, Device &d){
        o<<d.model<<endl;
        if (d.type==smartphone) {
                o<<"Mobilen ";
                if (d.godina>2015)
                    o<<d.proverka+2<<endl;
                else
                    o<<d.proverka<<endl;
        }
        else {
            o<<"Laptop ";
            if (d.godina>2015)
                o<<d.proverka+4<<endl;
            else
                o<<d.proverka+2<<endl;
        }
        return o;
    }
    static void setPocetniCasovi(int s){
        Device::proverka=s;
    }
    int getgodina(){
        return godina;
    }
};
float Device::proverka=1;

class MobileServis{
    char adresa[100];
    Device *uredi;
    int n;
public:
    MobileServis(char *adresa=""){
        strcpy(this->adresa, adresa);
        this->n=n;
        this->uredi = new Device[n];
    }
    MobileServis &operator+=(Device &nov){
        if (nov.getgodina()>2019||nov.getgodina()<2000)
            throw (InvalidProductionDate());
        Device *tmp = new Device[n+1];
        for (int i=0; i<n; i++)
            tmp[i]=uredi[i];
        tmp[n++]=nov;
        delete [] uredi;
        uredi=tmp;
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for (int i=0; i<n; i++)
            cout<<uredi[i];
    }
};
int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch (InvalidProductionDate id){
                id.showmessage();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch (InvalidProductionDate id){
                id.showmessage();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch (InvalidProductionDate id){
                id.showmessage();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
            t+=tmp;
            }
            catch (InvalidProductionDate id){
                id.showmessage();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch (InvalidProductionDate id){
                id.showmessage();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}

