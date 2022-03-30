#include <iostream>
using namespace std;
class List{
private:
    int *broevi;
    int broj;
    void copy (const List &other){
        this->broj=other.broj;
        this->broevi=new int [broj];
        for (int i=0; i<broj; i++)
            this->broevi[i]=other.broevi[i];
    }
public:
    List(){
    }
    List(int *broevi, int broj){
        this->broj=broj;
        this->broevi=new int [broj];
        for (int i=0; i<broj; i++)
            this->broevi[i]=broevi[i];
    }
    List (const List &other){
        copy(other);
    }
    List & operator =(const List &other){
        if (this!=&other){
            delete [] broevi;
            copy(other);
        }
        return *this;
    }
    ~List(){
        delete [] broevi;
    }
    int sum(){
    int suma=0;
    for (int i=0; i<this->broj; i++) suma+=this->broevi[i];
    return suma;
    }
    double average(){
    return (double)sum()/this->broj;
    }
    int getbroj(){
        return broj; }
    void print(){
        cout<<this->broj<<": ";
        for (int i=0; i<this->broj; i++)
            cout<<broevi[i]<<" ";
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
};

class ListContainer {
private:
    List *listi;
    int broj=0;
    int obidi=0;
    void copy(const ListContainer &other){
        this->broj=other.broj;
        this->obidi=other.obidi;
        this->listi = new List[broj];
        for (int i=0; i<broj; i++)
            this->listi[i]=other.listi[i];
    }
public:
    ListContainer(){
        listi = new List[0];
    };
    ListContainer(const ListContainer &other){
        copy(other);
    }
    ListContainer &operator = (const ListContainer &other){
        if (this!=&other){
            delete [] listi;
            copy(other);
        }
        return *this;
    }
    ~ListContainer(){
        delete [] listi;
    }
    void addNewList(List l){
        List *tmp = new List [this->broj+1];
        for (int i=0; i<this->broj; i++){
            if (this->listi[i].sum()==l.sum()) {
                obidi++;
                return ;}
            tmp[i]=this->listi[i];}
            tmp[broj++]=l;
            delete [] this->listi;
            this->listi=tmp;

    }
    int sum(){
        int suma=0;
        for (int i=0; i<this->broj; i++)
            suma+=this->listi[i].sum();
    return suma;
    }
    double average(){
        double prosek=0.00;
        int vkupno=0;
        for(int i=0; i<this->broj; i++){
            vkupno+=this->listi[i].getbroj();
            prosek+=this->listi[i].sum(); }
        return prosek/vkupno;
    }
    void print(){
        if (this->broj==0) {
                cout<<"The list is empty"<<endl;
                return ;}
        for (int i=0; i<this->broj; i++){
        cout<<"List number: "<<i+1<<" List info: ";
        listi[i].print();}
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<this->broj<<" Failed attempts: "<<this->obidi<<endl;
    }
};

int main() {

	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
