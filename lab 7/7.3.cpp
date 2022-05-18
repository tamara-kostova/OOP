#include <iostream>
#include <cmath>
using namespace std;


class Shape{
protected:
    int strana;
public:
    Shape(){
        strana=0;
    }
    Shape (int strana){
        this->strana=strana;
    }
    virtual double plostina() = 0;
    virtual void pecati() = 0;
    virtual int getType() = 0;

};

class Square : public Shape{
public:
    Square (int strana) : Shape (strana){
    }
    double plostina(){
        return strana*strana;
    }
    void pecati(){
        cout<<"Kvadrat so plostina = "<<plostina()<<endl;
    }
    int getType(){
        return 1;
    }
};
class Circle : public Shape{
    public:
    Circle (int strana) : Shape (strana){
    }
    double plostina(){
        return strana*strana*3.14;
    }
    void pecati(){
        cout<<"Krug so plostina = "<<plostina()<<endl;
    }
        int getType(){
        return 2;
    }
};
class Triangle : public Shape{
    public:
    Triangle (int strana) : Shape (strana){
    }
    double plostina(){
        return (sqrt(3)/4)*strana*strana;
    }
    void pecati(){
        cout<<"Triagolnik so plostina = "<<plostina()<<endl;
    }
    int getType(){
        return 3;
    }
};

void checkNumTypes(Shape** niza, int n){
    int kvadrati=0,krugovi=0,triagolnici=0;
    for(int i=0;i<n;i++)
    {
        if(niza[i]->getType()==1)
            kvadrati++;
        if(niza[i]->getType()==2)
            krugovi++;
        if(niza[i]->getType() == 3)
            triagolnici++;
    }
    cout<<"Broj na kvadrati vo nizata = "<<kvadrati<<endl;
    cout<<"Broj na krugovi vo nizata = "<<krugovi<<endl;
    cout<<"Broj na triagolnici vo nizata = "<<triagolnici<<endl;
}

int main(){

	int n;
	cin >> n;

	Shape **niza=new Shape*[n];

	int classType;
	int side;

	for(int i = 0; i < n; ++i){

		cin >> classType;
		cin >> side;
		if (classType==1)
            niza[i]=new Square(side);
        if (classType==2)
            niza[i]=new Circle(side);
        if (classType==3)
            niza[i]=new Triangle(side);
	}


	for(int i = 0; i < n; ++i){

		niza[i]->pecati();
	}

	checkNumTypes(niza, n);
    delete [] niza;
	return 0;
}
