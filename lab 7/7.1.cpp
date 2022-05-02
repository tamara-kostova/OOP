#include <iostream>
#include <cstring>
using namespace std;

class Employee{
protected:
    char ime[50];
    int godini;
    int iskustvo;
public:
    Employee (char *ime="", int godini=0, int iskustvo=0){
        strcpy(this->ime,ime);
        this->godini=godini;
        this->iskustvo=iskustvo;
    }
    virtual double plata()=0;
    virtual double bonus()=0;
    bool operator==(Employee &e){
        return (godini == e.godini && bonus() == e.bonus());
    }
};
class SalaryEmployee : public Employee{
    int osnovnaplata;
public:
    SalaryEmployee(char *ime="", int godini=0, int iskustvo=0, int osnovnaplata=0) : Employee (ime, godini, iskustvo){
        this->osnovnaplata=osnovnaplata;
    }
    double bonus(){
        return (iskustvo/100.0)*osnovnaplata;
    }
    double plata(){
        return osnovnaplata+bonus();
    }
};
class HourlyEmployee : public Employee{
    int casovi;
    int saatnica;
public:
    HourlyEmployee(char *ime="", int godini=0, int iskustvo=0, int casovi=0, int saatnica=0) : Employee (ime, godini, iskustvo){
        this->casovi=casovi;
        this->saatnica=saatnica;
    }
    double plata(){
        return casovi*saatnica+bonus();
    }
    double bonus(){
        if (casovi>320)
            return 0.5*(casovi-320)*saatnica;
        return 0;
    }
};
class Freelancer : public Employee{
    int proekti;
    double sumi[15];
public:
    Freelancer(char *ime="", int godini=0, int iskustvo=0, int proekti=0, double *sumi=nullptr) : Employee (ime, godini, iskustvo){
        this->proekti=proekti;
        for (int i=0; i<proekti; i++)
            this->sumi[i]=sumi[i];
    }
    double bonus(){
        if (proekti>5)
            return 1000*(proekti-5);
        return 0;
    }
    double plata(){
        int suma=0;
        for (int i=0; i<proekti; i++)
            suma+=sumi[i];
        return suma+bonus();
    }
};
class Company{
    char ime[50];
    int brvraboteni;
    Employee ** vraboteni;
public:
    Company(char *ime=""){
        strcpy(this->ime, ime);
        brvraboteni=0;
        vraboteni = new Employee *[0];
    }
    ~Company(){
        delete [] vraboteni;
    }
    Company &operator+=(Employee *e){
        Employee **tmp=new Employee*[brvraboteni+1];
        for (int i=0; i<brvraboteni; i++)
            tmp[i]=vraboteni[i];
        tmp[brvraboteni++]=e;
        delete [] vraboteni;
        vraboteni=tmp;
        return *this;
    }
    double vkupnaPlata(){
        double suma=0;
        for (int i=0; i<brvraboteni; i++)
            suma+=vraboteni[i]->plata();
        return suma;
    }
    double filtriranaPlata(Employee *emp){
        double suma=0;
        for(int i=0; i<brvraboteni; i++)
            if(*vraboteni[i] == *emp)
                suma+=vraboteni[i]->plata();
        return suma;
    }
    void pecatiRabotnici(){
        int Salarye=0,Hourlye=0,FreeL=0;
        cout<<"Vo kompanijata "<<ime<<" rabotat:"<<endl;
        for(int i=0; i<brvraboteni; i++)
        {
            SalaryEmployee *se = dynamic_cast <SalaryEmployee *>(vraboteni[i]);
            if(se != 0)
            {
                Salarye++;
                continue;
            }
            HourlyEmployee *he = dynamic_cast <HourlyEmployee *>(vraboteni[i]);
            if(he != 0)
            {
                Hourlye++;
                continue;
            }
            Freelancer *fl=dynamic_cast <Freelancer*>(vraboteni[i]);
            if(fl != 0)
            {
                FreeL++;
                continue;
            }

        }
        cout<<"Salary employees: "<<Salarye<<endl;
        cout<<"Hourly employees: "<<Hourlye<<endl;
        cout<<"Freelancers: "<<FreeL<<endl;
    }
};

int main() {

char name[50];
cin >> name;
Company c(name);

int n;
cin >> n;

char employeeName[50];
int age;
int experience;
int type;

for (int i=0; i <n; ++i) {
  cin >> type;
  cin >> employeeName >> age >> experience;

  if (type == 1) {
    int basicSalary;
    cin >> basicSalary;
    c += new SalaryEmployee(employeeName, age, experience, basicSalary);
  }

  else if (type == 2) {
    int hoursWorked;
    int hourlyPay;
    cin >> hoursWorked >> hourlyPay;
    c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
  }

  else {
    int numProjects;
    cin >> numProjects;
    double projects[10];
    for (int i=0; i < numProjects; ++i) {
      cin >> projects[i];
    }
    c += new Freelancer(employeeName, age, experience, numProjects, projects);
  }
}

c.pecatiRabotnici();
cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

delete emp;
}
