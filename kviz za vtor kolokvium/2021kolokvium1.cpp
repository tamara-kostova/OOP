#include<string.h>
#include<iostream>

using namespace std;

class User {
    char *username;
    char *companyName;
    int position;

    void copy(const User &u) {
        this->username = new char[strlen(u.username) + 1];
        strcpy(this->username, u.username);
        this->companyName = new char[strlen(u.companyName) + 1];
        strcpy(this->companyName, u.companyName);
        this->position = u.position;
    }

public:
    User(char *username = "", char *companyName = "", int position = 0) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
        this->position = position;
    }

    User(const User &u) {
        copy(u);
    }

    User &operator=(const User &u) {
        if (this != &u) {
            delete[] username;
            delete[] companyName;
            copy(u);
        }
        return *this;
    }

    ~User() {
        delete[] username;
        delete[] companyName;
    }

    char *getUsername() const {
        return username;
    }

    void setUsername(char *username) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
    }

    char *getCompanyName() const {
        return companyName;
    }

    void setCompanyName(char *companyName) {
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
    }

    int getPosition() const {
        return position;
    }

    void setPosition(int position) {
        this->position = position;
    }


    friend ostream &operator<<(ostream &os, const User &user) {
        return os << "Username: " << user.username
                  << " Company name: " << user.companyName
                  << " Position: " << user.position;
    }

    friend istream &operator>>(istream &in, User &user) {
        return in >> user.username >> user.companyName >> user.position;
    }

    bool operator==(User &u) {
        return strcmp(this->username, u.username) == 0;
    }
};

class OperationNotSupported{
    char poraka[50];
public:
    OperationNotSupported(char * poraka = "test") {
        strcpy(this->poraka, poraka);
    }
    void showMessage(){
        cout<<poraka<<endl;
    }
};

class Group{
protected:
    User *users;
    int n;
    char ime[50];
    void copy(const Group &g) {
        strcpy(ime, g.ime);
        n=g.n;
        users = new User [n];
        for (int i=0; i<n; i++)
            users[i]=g.users[i];
    }
public:
    Group(char ime[50]=""){
        strcpy(this->ime, ime);
        n=0;
        users = new User [n];
    }
    Group (const Group &g){
        copy(g);
    }
    Group &operator =(const Group &g){
        if (this!=&g){
            delete [] users;
            copy(g);
        }
        return *this;
    }
    ~Group(){
        delete [] users;
    }
    friend ostream &operator<<(ostream &os, Group &g) {
        os<<"Group: "<<g.ime<<endl<<"Members: "<<g.n<<endl<<"Rating: "<<g.rating()<<endl<<"Members list:"<<endl;
        if (g.n==0)
            return os<<"EMPTY"<<endl;
        for (int i =0; i<g.n; i++)
            os<<i+1<<". "<<g.users[i]<<endl;
        return os;
    }

    virtual void addMember (User & u){
        for (int i=0; i<n;i ++)
            if (users[i]==u)
                throw OperationNotSupported("Username already exists");
        User *tmp = new User [n+1];
        for (int i=0; i<n;i ++)
            tmp[i]=users[i];
        tmp[n++]=u;
        delete [] users;
        users=tmp;
    }
    double prosek(){
        double prosek=0;
        for (int i=0; i<n; i++)
                prosek+=users[i].getPosition();
            prosek/=n;
    }
    virtual double rating(){
        if (!n) return 0;
        return (10-prosek())*n/100.0;
    }
};

class PrivateGroup: public Group{
    static int kapacitet;
    const static float koeficient;

public:
    PrivateGroup (char ime[50]="") : Group (ime){
    }
    void addMember (User & u){
        if (n==kapacitet)
            throw (OperationNotSupported("The group’s capacity has been exceeded."));
        Group::addMember(u);
    }
    double rating(){
        if (!n) return 0;
        return (10-prosek())*((double)n/kapacitet)*koeficient;
    }
    friend ostream &operator<<(ostream &os, PrivateGroup &pg) {
        os<<"Private ";
        Group g (pg);
        return os<<g;
    }
    static void setCapacity(int capacity){
        kapacitet=capacity;
    }
    static int getCapacity(){
        return kapacitet;
    }
};
const float PrivateGroup::koeficient=0.8;
int PrivateGroup::kapacitet=10;

int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR AND OPERATOR <<" << endl;
        Group g("test");
        cout << g;
    } else if (testCase == 2) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR AND OPERATOR <<" << endl;
        PrivateGroup pg("private test");
        cout << pg;
    } else if (testCase == 3) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND OPERATOR <<" << endl;
        Group *g = new Group("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try{
                g->addMember(u);
            }
            catch (OperationNotSupported o)
            {
                o.showMessage();
            }
        }
        cout << *g;
        delete g;
    } else if (testCase == 4) {
        cout << "TESTING CLASS PRIVATE_GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND OPERATOR <<" << endl;
        Group *g = new PrivateGroup("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try{
            g->addMember(u);
            }
            catch (OperationNotSupported e) {
                e.showMessage();
            }
        }
        cout << *g;
        delete g;
    } else if (testCase == 5) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<" << endl;
        Group *g = new Group("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported e) {
                e.showMessage();
            }
        }
        cout << *g;
        delete g;
    } else if (testCase == 6) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<" << endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported e) {
                e.showMessage();
            }
        }
        cout << *g;
        delete g;
    } else if (testCase == 7) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND CHANGE OF STATIC MEMBER"
             << endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << "RATING BEFORE CHANGE" << endl;
        cout << g->rating();
        PrivateGroup::setCapacity(20);
        cout << "RATING AFTER CHANGE" << endl;
        cout << g->rating();
        delete g;
    }
    else if (testCase==8) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND CHANGE OF STATIC MEMBER"
             << endl;

        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported & e) {
                int capacity = PrivateGroup::getCapacity();
                cout<<"Increasing capacity from "<<capacity<<" to "<<capacity+1<<endl;
                PrivateGroup::setCapacity(capacity+1);
                g->addMember(u);
                cout<<g->rating()<<endl;
            }
        }

    }else {
        cout<<"INTEGRATION TEST"<<endl;
        char name [50];
        int nGroups;
        cin>>nGroups;
        Group ** groups = new Group * [nGroups];
        for (int i=0;i<nGroups;i++) {
            int type;
            cin>>type;
            cin>>name;
            if (type==1) { //normal group
                groups[i] = new Group(name);
            } else { //private group
                groups[i] = new PrivateGroup(name);
            }
            int nUsers;
            cin>>nUsers;
            for (int j=0;j<nUsers;j++) {
                User u;
                cin>>u;
                try {
                    groups[i]->addMember(u);
                } catch (OperationNotSupported e) {
                    e.showMessage();
                }
            }
        }

        cout<<"BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT"<<endl;
        for (int i = 0; i < nGroups; ++i) {
            cout<<*groups[i];
        }
        PrivateGroup::setCapacity(15);
        cout<<"AFTER CHANGE OF PRIVATE GROUP COEFFICIENT"<<endl;
        for (int i = 0; i < nGroups; ++i) {
            cout<<*groups[i];
        }
    }
}
