#include <iostream>
#include <cstring>
using namespace std;
class Book{
protected:
    char isbn[20];
    char naslov[50];
    char avtor[30];
    float cena;
public:
    Book(char *isbn="", char *naslov="", char *avtor="", float cena=0){
        strcpy(this->isbn, isbn);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->cena=cena;
    }
    virtual float bookPrice()=0;
    bool operator > (Book &b){
            return (this->bookPrice()>b.bookPrice());
    }
    friend ostream &operator <<(ostream &o, Book &b){
        o<<b.isbn<<": "<<b.naslov<<", "<<b.avtor<<" "<<b.bookPrice()<<endl;
        return o;
    }
    void setISBN (char *isbn){
        strcpy(this->isbn, isbn);
    }
};
class OnlineBook : public Book{
    char *url;
    int golemina;
public:
    OnlineBook(char *isbn="", char *naslov="", char *avtor="", float cena=0, char *url="", int golemina=0) : Book(isbn,naslov,avtor,cena){
        this->url = new char [100];
        strcpy(this->url,url);
        this->golemina=golemina;
    }
    float bookPrice(){
        if (golemina>20)
            return 1.2*cena;
        return cena;
    }
};
class PrintBook : public Book{
    int masa;
    bool dostapnost;
public:
    PrintBook(char *isbn="", char *naslov="", char *avtor="", float cena=0, int masa=0, bool dostapnost=false) : Book(isbn,naslov,avtor,cena){
        this->masa=masa;
        this->dostapnost=dostapnost;
    }
    float bookPrice(){
        if (masa>0.7)
            return 1.15*cena;
        return cena;
    }
};
void mostExpensiveBook(Book **books, int n){
    Book *najskapa=books[0];
    int online=0, pecateni=0;
    for (int i=0; i<n; i++){
        OnlineBook *o= dynamic_cast<OnlineBook*>(books[i]);
        if (o!=0) {
            online++;
            if (o->bookPrice()>najskapa->bookPrice())
                najskapa=o;
        }
        else{
            PrintBook *p = dynamic_cast<PrintBook*>(books[i]);
            if(p!=0){
                pecateni++;
                if (p->bookPrice()>najskapa->bookPrice())
                najskapa=p;
            }
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<pecateni<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*najskapa;
}

int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
