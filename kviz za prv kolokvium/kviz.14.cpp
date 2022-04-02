#include<iostream>
#include<cstring>

using namespace std;

enum Extension {pdf, txt, exe};
class File{
private:
    char *ime;
    Extension ext;
    char *sopstvenik;
    int golemina;
    void copy(const File &other){
        this->ext=other.ext;
        this->golemina=other.golemina;
        this->ime=new char[strlen(other.ime)+1];
        strcpy(this->ime,other.ime);
        this->sopstvenik=new char[strlen(other.sopstvenik)+1];
        strcpy(this->sopstvenik,other.sopstvenik);
    }
public:
    File (char *ime="", char *sopstvenik="", int golemina=0, Extension ext=pdf){
        this->golemina=golemina;
        this->ext=ext;
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->sopstvenik=new char[strlen(sopstvenik)+1];
        strcpy(this->sopstvenik,sopstvenik);
    }
    File (const File &other){
        copy(other);
    }
    const File & operator =(const File &other){
        if (this!=&other){
            delete[] ime;
            delete[] sopstvenik;
            copy(other);
        }
        return *this;
    }
    ~File(){
        delete [] ime;
        delete [] sopstvenik;
    }
    void print(){
        cout<<"File name: "<<this->ime;
        switch (this->ext){
            case 0: cout<<".pdf"<<endl;
                break;
            case 1: cout<<".txt"<<endl;
                break;
            case 2: cout<<".exe"<<endl;
                break;
        }
        cout<<"File owner: "<<this->sopstvenik<<endl<<"File size: "<<this->golemina<<endl;
    }
    bool equalsType(const File &f){
        return ((strcmp(this->ime,f.ime)==0)&&(this->ext==f.ext));
    }
    bool equals(const File &f){
        return (equalsType(f)&&(strcmp(this->sopstvenik,f.sopstvenik)==0));
    }
};

class Folder{
private:
    char *name;
    int brojdat=0;
    File *datoteki;
    void copy(const Folder &other){
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name, other.name);
        this->brojdat=other.brojdat;
        this->datoteki = new File[brojdat];
        for (int i=0; i<brojdat; i++)
            this->datoteki[i]=other.datoteki[i];
    }
public:
    Folder(char *name=""){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        datoteki=new File[this->brojdat];
    }
    Folder (const Folder &other){
        copy(other);
    }
    Folder &operator=(const Folder &other){
        if (this!=&other){
            delete [] name;
            delete [] datoteki;
            copy(other);
        }
        return *this;
    }
    ~Folder(){
        delete [] name;
        delete [] datoteki;
    };
    void print(){
        cout<<"Folder name: "<<this->name<<endl;
        for(int i=0; i<brojdat; i++)
            datoteki[i].print();
    }
    void remove(const File & file){
        for(int i=0; i<brojdat; i++){
            if (datoteki[i].equals(file)){
                brojdat--;
                for (int j=i; j<brojdat; j++)
                    datoteki[j]=datoteki[j+1];
                break;
            }
        }
    }
    void add(const File & file){
        File *tmp = new File [brojdat+1];
        for (int i=0; i<brojdat; i++){
            tmp[i]=datoteki[i];
        }
        tmp[brojdat++]=file;
        delete [] datoteki;
        datoteki=tmp;
    }
};

int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}
