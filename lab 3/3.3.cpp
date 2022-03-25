#include<iostream>
#include<cstring>
using namespace std;

class Category{
private:
    char *ime="unnamed";
public:
    Category(){}
    Category (char *ime){
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime, ime);
    }
    ~Category(){}
    void print(){
    cout<<"Category: "<<ime<<endl;
    }
};

class NewsArticle{
private:
    Category kategorija;
    char *title="untitled";
public:
    NewsArticle(){};
    NewsArticle(Category kategorija, char *title){
        this->kategorija=kategorija;
        this->title=new char [strlen(title)+1];
        strcpy(this->title, title);
    }
    NewsArticle(Category kategorija){
        this->kategorija=kategorija;
    }
    ~NewsArticle(){}
    void print(){
        cout<<"Article title: "<<title<<endl;
        kategorija.print();
    }
};

class FrontPage{
private:
    NewsArticle article;
    float price=0;
    int editionNumber=0;
public:
    FrontPage(){}
    FrontPage(NewsArticle article, float price, int editionNumber){
        this->article=article;
        this->price=price;
        this->editionNumber=editionNumber;
    }
    FrontPage(NewsArticle article, float price){
        this->article=article;
        this->price=price;
    }
    ~FrontPage(){};
    void print(){
        cout<<"Price: "<<price<<", Edition number: "<<editionNumber<<endl;
        article.print();
    }
};

int main() {
	char categoryName[20];
	char articleTitle[30];
	float price;
	int editionNumber;

	int testCase;
	cin >> testCase;


	if (testCase == 1) {
		int iter;
		cin >> iter;
		while (iter > 0) {
			cin >> categoryName;
			cin >> articleTitle;
			cin >> price;
			cin >> editionNumber;
			Category category(categoryName);
			NewsArticle article(category, articleTitle);
			FrontPage frontPage(article, price, editionNumber);
			frontPage.print();
			iter--;
		}
	}
	else if (testCase == 2) {
		cin >> categoryName;
		cin >> price;
		cin >> editionNumber;
		Category category(categoryName);
		NewsArticle article(category);
		FrontPage frontPage(article, price, editionNumber);
		frontPage.print();
	}// test case 3
	else if (testCase == 3) {
		cin >> categoryName;
		cin >> articleTitle;
		cin >> price;
		Category category(categoryName);
		NewsArticle article(category, articleTitle);
		FrontPage frontPage(article, price);
		frontPage.print();
	}
    else {
    	FrontPage frontPage = FrontPage();
        frontPage.print();
    }
	return 0;
}
