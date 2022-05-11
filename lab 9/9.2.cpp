#include <iostream>
#include <cstring>
using namespace std;

class ArithmeticException {
public:
    void message (){
        cout<<"Division by zero is not allowed"<<endl;
    }
};
class NumbersNotDivisibleException {
int n;
public:
    NumbersNotDivisibleException(int n=0){
        this->n=n;
    }
    void message (){
        cout<<"Division by "<<n<<" is not supported"<<endl;
    }
};
class ArrayFullException {
public:
    void message (){
        cout<<"The array is full. Increase the capacity"<<endl;
    }
};
class IndexOutOfBoundsException {
    int n;
public:
    IndexOutOfBoundsException(int n=0){
        this->n=n;
    }
    void message (){
        cout<<"Index "<<n<<" is out of bounds"<<endl;
    }
};
class NumberIsNotPositiveException {
    int n;
public:
    NumberIsNotPositiveException(int n=0){
        this->n=n;
    }
    void message (){
        cout<<"Number "<<n<<" is not positive integer"<<endl;
    }
};


class PositiveIntegers{
    int *broevi;
    int broj;
    int kapacitet;
    void copy(const PositiveIntegers &p){
        broj=p.broj;
        kapacitet=p.kapacitet;
        broevi = new int[broj];
        for(int i=0; i<broj; i++)
            broevi[i]=p.broevi[i];
    }
public:
    PositiveIntegers(int kapacitet=0){
        this->kapacitet=kapacitet;
        broj=0;
        broevi = new int [broj];
    }
    PositiveIntegers(const PositiveIntegers &p){
        copy(p);
    }
    PositiveIntegers &operator =(const PositiveIntegers &p){
        if(this!=&p)
        {
            delete [] broevi;
            copy(p);
        }
        return *this;
    }
    void increaseCapacity(int c){
        kapacitet+=c;
    }
    PositiveIntegers &operator +=(int n){
        if (broj==kapacitet)
            throw (ArrayFullException());
        if (n<=0)
            throw (NumberIsNotPositiveException(n));
        int *tmp = new int [broj+1];
        for (int i=0; i<broj; i++)
            tmp[i]=broevi[i];
        tmp[broj++]=n;
        delete [] broevi;
        broevi=tmp;
        return *this;
    }
    PositiveIntegers operator *(int number)
    {
        PositiveIntegers p(*this);
        for(int i=0;i<broj;i++)
            p.broevi[i]*=number;
        return p;
    }
    PositiveIntegers operator /(int number)
    {
        if(number == 0)
            throw (ArithmeticException());
        for(int i=0;i<broj;i++)
            if(broevi[i]%number != 0)
                throw (NumbersNotDivisibleException(number));
        PositiveIntegers p(*this);
        for(int i=0;i<broj;i++)
            p.broevi[i]/=number;
        return p;
    }
    int&operator[](int index){
        if(index<0 || index>broj)
            throw(IndexOutOfBoundsException(index));
        return broevi[index];
    }
    void print(){
        cout<<"Size: "<<broj<<" Capacity: "<<kapacitet<<" Numbers: ";
        for (int i=0; i<broj; i++)
            cout<<broevi[i]<<" ";
        cout<<endl;
    }
};

int main() {

	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
		try{
		    pi+=number;
		}
		catch(ArrayFullException &a){
		    a.message();
		}
		catch(NumberIsNotPositiveException & n){
		    n.message();
		}
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();

	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		try{
		    pi+=number;
		}
		catch(ArrayFullException &a){
		    a.message();
		}
		catch(NumberIsNotPositiveException & n){
		    n.message();
		}
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
	PositiveIntegers pi1;

	cout<<"===TESTING DIVISION==="<<endl;

	try{
        pi1 = pi/0;
        pi1.print();
	}
	catch(ArithmeticException &a){
        a.message();
    }
    catch(NumbersNotDivisibleException &n){
        n.message();
    }
	try{
        pi1 = pi/1;
        pi1.print();
	}
    catch(ArithmeticException &a){
        a.message();
    }
    catch(NumbersNotDivisibleException &n){
        n.message();
    }
	try{
	    pi1 = pi/2;
        pi1.print();
	}
    catch(ArithmeticException &a){
        a.message();
    }
    catch(NumbersNotDivisibleException &n){
        n.message();
    }
	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print();


	cout<<"===TESTING [] ==="<<endl;
	try{
	    cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
	}
	catch(IndexOutOfBoundsException &i){
	    i.message();
	}
	try{
	    cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
	}
	catch(IndexOutOfBoundsException &i){
	    i.message();
	}
	try{
	    cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
	}
	catch(IndexOutOfBoundsException &i){
	    i.message();
	}
	try{
	    cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
	}
	catch(IndexOutOfBoundsException &i){
	    i.message();
	}
	return 0;
}
