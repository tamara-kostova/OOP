#include <iostream>
#include <cstring>
using namespace std;
enum typeC{standard, loyal, vip};
#define MAX 50

class UserExistsException{
public:
    void message(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

class Customer{
    char ime[50];
    char email[50];
    typeC type;
    int osnovenpopust=0;
    static int dopolnitelenpopust;
    int kupeni;
    void copy(Customer &c){
        strcpy(ime,c.ime);
        strcpy(email,c.email);
        type=c.type;
        kupeni=c.kupeni;
    }
public:
    Customer(){}
    Customer(char *ime, char *email, typeC type, int kupeni){
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->type=type;
        this->kupeni=kupeni;
        if(type==loyal || type==vip)
            osnovenpopust=10;
    }
    friend ostream &operator<<(ostream &o, Customer &c){
        o<<c.ime<<endl<<c.email<<endl<<c.kupeni<<endl;
        if (c.type==standard) o<<"standard "<<c.osnovenpopust<<endl;
        else if(c.type==loyal) o<<"loyal "<<c.osnovenpopust<<endl;
        else if(c.type==vip) o<<"vip "<<c.osnovenpopust+dopolnitelenpopust<<endl;
        return o;
    }
    char *getemail(){
        return email;
    }
    typeC gettype(){
        return type;
    }
    int getkupeni(){
        return kupeni;
    }
    void setDiscount1(int n){
        osnovenpopust=n;
    }
    void settype(typeC tip){
        type=tip;
        if (type==loyal)
            osnovenpopust=10;
    }

};
int Customer::dopolnitelenpopust=20;

class FINKI_bookstore{
    Customer *customers;
    int n;
public:
    FINKI_bookstore(){
        n=0;
        customers=new Customer[n];
    }
    FINKI_bookstore &operator+=(Customer &c){
        for (int i=0; i<n; i++)
        if (!strcmp(c.getemail(), customers[i].getemail()))
                throw UserExistsException();
        Customer *tmp = new Customer[n+1];
        for (int i=0; i<n; i++)
            tmp[i]=customers[i];
        tmp[n++]=c;
        delete [] customers;
        customers=tmp;
        return *this;
    }
    void update(){
        for (int i=0; i<n; i++){
            if (customers[i].gettype()==standard&&customers[i].getkupeni()>5)
                customers[i].settype(loyal);
            else
                if (customers[i].gettype()==loyal&&customers[i].getkupeni()>10)
                customers[i].settype(vip);
        }
    }
    friend ostream &operator<<(ostream &os, FINKI_bookstore &fb){
        for (int i=0; i<fb.n; i++)
            os<<fb.customers[i];
        return os;
    }
    void setCustomers(Customer *customers, int n){
        delete [] this->customers;
        this->n=n;
        this->customers = new Customer[n];
        for (int i=0; i<n; i++)
            this->customers[i]=customers[i];
    }
};

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    try{
        fc+=c;
    }
    catch (UserExistsException ue){
            ue.message();
        }

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    Customer cs;
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
      cs=c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    try{
    fc+=cs;
    }
    catch (UserExistsException ue){
        ue.message();
    }
    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
