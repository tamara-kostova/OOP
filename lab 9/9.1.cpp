#include <iostream>
#include <cstring>
using namespace std;

class InvalidPasswordException{
    char poraka[50];
public:
    InvalidPasswordException(const char *poraka=""){
        strcpy(this->poraka, poraka);
    }
    void message(){
        cout<<poraka<<endl;
    }
};
class InvaidEmailException{
    char poraka[50];
public:
    InvaidEmailException(const char *poraka=""){
        strcpy(this->poraka,poraka);
    }
    void message(){
        cout<<poraka<<endl;
    }
};
class MaximumSizeLimitException{
    int n;
public:
    MaximumSizeLimitException(int n=0){
        this->n=n;
    }
    void message(){
        cout<<"You can't add more than "<<n<<" users."<<endl;
    }
};

class User{
protected:
    char username [50];
    char password [50];
    char email [50];
public:
    User(const char *username="",const char *password="",const char *email=""){
        if(!validpassword(password))
            throw InvalidPasswordException("Password is too weak.");
        else
            strcpy(this->password,password);
        if (!validemail(email))
            throw InvaidEmailException("Mail is not valid.");
        else
            strcpy(this->username,username);
        strcpy(this->email,email);
    }
    virtual double popularity() = 0;
    bool validpassword(const char *password){
        bool mala=0, golema=0, broj=0;
        for (int i=0; i<strlen(password);i++){
            if (password[i]>='a'&&password[i]<='z')
                mala=1;
            else if (password[i]>='A'&&password[i]<='Z')
                golema=1;
            else if (password[i]>='0'&&password[i]<='9')
                broj=1;
        }
        if (!mala||!golema||!broj)
            return 0;
        return 1;
    }
    bool validemail(const char *email){
        int atsign=0;
        for (int i=0; i<strlen(email);i++)
            if (email[i]=='@')
                atsign++;
        if (atsign!=1)
            return 0;
        return 1;
    }
};
class FacebookUser : public User{
private:
    int prijateli;
    int lajkovi;
    int komentari;
public:
    FacebookUser(const char *username="",const char *password="",const char *email="", int prijateli=0, int lajkovi=0, int komentari=0)
     : User(username,password,email){
        this->prijateli=prijateli;
        this->lajkovi=lajkovi;
        this->komentari=komentari;
    }
    double popularity(){
        return 0.1*lajkovi+0.5*komentari+prijateli;
    }
};
class TwitterUser : public User{
private:
    int sledaci;
    int tvitovi;
public:
    TwitterUser(const char *username="",const char *password="",const char *email="", int sledaci=0, int tvitovi=0)
     : User(username,password,email){
        this->sledaci=sledaci;
        this->tvitovi=tvitovi;
    }
    double popularity(){
        return 0.5*tvitovi+sledaci;
    }
};
class SocialNetwork{
    User **korisnici;
    int tekovnikorisnici;
    int maxkorisnici=5;
public:
    SocialNetwork(){
        tekovnikorisnici=0;
        this->korisnici = new User *[tekovnikorisnici];
    }
    ~SocialNetwork(){
        delete [] korisnici;
    }
    SocialNetwork &operator = (const SocialNetwork &sn){
        if (this!=&sn){
            tekovnikorisnici=sn.tekovnikorisnici;
            maxkorisnici=sn.maxkorisnici;
            korisnici = new User *[tekovnikorisnici];
            for (int i=0; i<tekovnikorisnici;i++)
                this->korisnici[i]=sn.korisnici[i];
        }
    }
    SocialNetwork &operator +=(User *nov){
        if (maxkorisnici==tekovnikorisnici)
            throw MaximumSizeLimitException(maxkorisnici);
        User **tmp = new User *[tekovnikorisnici+1];
        for (int i=0; i<tekovnikorisnici; i++)
            tmp[i]=korisnici[i];
        tmp[tekovnikorisnici++]=nov;
        delete korisnici;
        korisnici=tmp;
        return *this;
    }
    double avgPopularity(){
        double average=0.0;
        for (int i=0; i<tekovnikorisnici; i++)
            average+=korisnici[i]->popularity();
        return average/tekovnikorisnici;
    }
    void changeMaximumSize(int number){
        maxkorisnici=number;
    }
};

int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;

        try{
            User * u = new FacebookUser(username,password,email,friends,likes,comments);
            network += u;
        }
        catch(InvalidPasswordException &p){
            p.message();
        }
        catch (InvaidEmailException &e){
            e.message();
        }
        catch (MaximumSizeLimitException &s){
            s.message();
        }

      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;

        try{
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
        }
        catch(InvalidPasswordException &p){
            p.message();
        }
        catch (InvaidEmailException &e){
            e.message();
        }
        catch (MaximumSizeLimitException &s){
            s.message();
        }
      }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    try{
    User * u= new TwitterUser(username,password,email,followers,tweets);
    network += u;
    }
    catch(InvalidPasswordException &p){
            p.message();
        }
    catch (InvaidEmailException &e){
        e.message();
    }
    catch (MaximumSizeLimitException &s){
        s.message();
    }
    cout << network.avgPopularity();

}
