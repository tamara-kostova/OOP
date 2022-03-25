#include<iostream>
#include<cstring>
using namespace std;

class Person{
private:
    char *name;
    char *lastName;
public:
    Person(char *name, char *lastName){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->lastName=new char[strlen(lastName)+1];
        strcpy(this->lastName, lastName);
    }
    Person (){
        name = nullptr;
        lastName = nullptr;
    }
    ~Person(){
    }
    void print(){
        cout<<name<<" "<<lastName<<endl;
    }
};

class Date{
private:
    int year;
    int month;
    int day;
public:
    Date (int year, int month, int day){
        this->year=year;
        this->month=month;
        this->day=day;
    }
    Date(){}
    Date (const Date &other){
        this->year=other.year;
        this->month=other.month;
        this->day=other.day;
    }
    void print(){
        cout<<this->year<<"."<<this->month<<"."<<this->day<<endl;
    }
};

class Car{
private:
    Person sopstvenik;
    Date datum;
    float cena=0;
public:
    Car(){
        this->cena=0;
    }
    Car (Person sopstvenik, Date datum, float cena){
        this->sopstvenik = sopstvenik;
        this->datum=datum;
        this->cena=cena;
    }
    ~Car(){};
    float getPrice(){
        return this->cena;
    }
    void print(){
    sopstvenik.print();
    datum.print();
    cout<<"Price: "<<cena;
    }
};

void cheaperThan(Car* cars, int numCars, float price){
for (int i=0; i<numCars; i++){
    if (cars[i].getPrice()<price)
        cars[i].print();
}
}

int main() {
	char name[20];
	char lastName[20];
	int year;
	int month;
	int day;
	float price;

	int testCase;
	cin >> testCase;

	if (testCase == 1) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(year, month, day);

		cin >> price;
		Car car(lik, date,  price);

		car.print();
	}
	else if (testCase == 2) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(Date(year, month, day));

		cin >> price;
		Car car(lik, date,  price);
		car.print();
	}
	else {
		int numCars;
		cin >> numCars;

		Car cars[10];
		for (int i = 0; i < numCars; i++) {
			cin >> name;
			cin >> lastName;
			Person lik(name, lastName);

			cin >> year;
			cin >> month;
			cin >> day;
			Date date(year, month, day);

			cin >> price;
			cars[i] = Car(lik, date,  price);
		}
        float priceLimit;
        cin >> priceLimit;
		cheaperThan(cars, numCars, priceLimit);
	}


	return 0;
}
