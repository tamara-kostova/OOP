#include <iostream>
#include <cstring>
using namespace std;

class NBAPlayer{
protected:
    char *ime;
    char tim[40];
    double points;
    double assists;
    double rebounds;
    void copy(const NBAPlayer &p){
        this->ime=new char [strlen(p.ime)+1];
        strcpy(this->ime, p.ime);
        strcpy(this->tim, p.tim);
        points=p.points;
        assists=p.assists;
        rebounds=p.rebounds;
    }
public:
    NBAPlayer(){
        ime = new char [0];
        ime=nullptr;
    }
    NBAPlayer(char *ime, char *tim, double points, double assists, double rebounds){
        this->ime=new char [strlen(ime)+1];
        strcpy(this->ime, ime);
        strcpy(this->tim, tim);
        this->points=points;
        this->assists=assists;
        this->rebounds=rebounds;
    }
    NBAPlayer (const NBAPlayer &n){
        copy(n);
    }
    NBAPlayer &operator=(const NBAPlayer &n){
        if (this!=&n){
            delete[]ime;
            copy(n);
        }
        return *this;
    }
    ~NBAPlayer (){
        delete [] ime;
    }
    double rating(){
        return 0.45*points+0.3*assists+0.25*rebounds;
    }
    void print(){
        cout<<ime<<" - "<<tim<<endl<<"Points: "<<points<<endl<<"Assists: "<<assists<<endl<<"Rebounds: "<<rebounds<<endl<<"Rating: "<<rating()<<endl;
    }
};
class AllStarPlayer:public NBAPlayer{
private:
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;
    void copy(const AllStarPlayer &p){
        allStarAssists=p.allStarAssists;
        allStarPoints=p.allStarPoints;
        allStarRebounds=p.allStarRebounds;
    }
public:
    AllStarPlayer(): NBAPlayer(){}
    AllStarPlayer(const NBAPlayer &igrac, double allStarPoints, double allStarAssists, double allStarRebounds): NBAPlayer(igrac){
        this->allStarAssists=allStarAssists;
        this->allStarPoints=allStarPoints;
        this->allStarRebounds=allStarRebounds;
    }
    AllStarPlayer(char * ime, char * tim, double points, double assists, double rebounds, double allStarPoints, double allStarAssists, double allStarRebounds)
    : NBAPlayer(ime, tim, points, assists, rebounds){
        this->allStarAssists=allStarAssists;
        this->allStarPoints=allStarPoints;
        this->allStarRebounds=allStarRebounds;
    }
    AllStarPlayer (const AllStarPlayer &p):NBAPlayer(p){
        copy(p);
    }
    AllStarPlayer &operator = (const AllStarPlayer &p){
        if (this!=&p){
            delete [] ime;
            NBAPlayer::copy(p);
            copy(p);
        }
        return *this;
    }
    ~AllStarPlayer(){
    }
    double allStarRating(){
        return 0.3*allStarPoints+0.4*allStarAssists+0.3*allStarRebounds;
    }
    double rating (){
        return (NBAPlayer::rating()+allStarRating())/2;
    }
    void print (){
        NBAPlayer::print();
        cout<<"All Star Rating: "<<allStarRating()<<endl<<"New Rating: "<<rating()<<endl;
    }
};

int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
