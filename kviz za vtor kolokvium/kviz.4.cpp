#include <cstring>
#include <iostream>
using namespace std;
enum Size{mala, golema,familijarna};

class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float cena;
public:
    Pizza (char ime[20], char sostojki[100], float cena){
        strcpy(this->ime, ime);
        strcpy(this->sostojki, sostojki);
        this->cena=cena;
    }
    virtual float price () = 0;
    bool operator < (Pizza &p){
        return (price()<p.price());
    }
};
class FlatPizza : public Pizza{
    Size golemina;
public:
    FlatPizza (char ime[20], char sostojki[100], float cena, Size golemina=mala) : Pizza(ime, sostojki, cena){
        this->golemina=golemina;
    }
    float price(){
        if (golemina==golema)
            return 1.5*cena;
        if (golemina==mala)
            return 1.1*cena;
        return 1.3*cena;
    }
    friend ostream &operator <<(ostream &o, FlatPizza &flat){
        o<<flat.ime<<": "<<flat.sostojki<<", ";
        if(flat.golemina==mala) o<<"small - ";
        if(flat.golemina==golema) o<<"big - ";
        if(flat.golemina==familijarna) o<<"family - ";
        o<<flat.price()<<endl;
        return o;
    }
};
class FoldedPizza : public Pizza{
    bool brasno;
public:
    FoldedPizza (char ime[20], char sostojki[100], float cena, bool brasno=true) : Pizza(ime, sostojki, cena){
        this->brasno=brasno;
    }
    float price(){
        if (brasno)
            return 1.1*cena;
        return 1.3*cena;
    }
    friend ostream &operator <<(ostream &o, FoldedPizza &folded){
        o<<folded.ime<<": "<<folded.sostojki<<", ";
        if (folded.brasno)
            o<<"wf - ";
        else
            o<<"nwf - ";
        o<<folded.price()<<endl;
        return o;
    }
    void setWhiteFlour(bool brasno){
        this->brasno=brasno;
    }
};
void expensivePizza(Pizza **pici, int n){
    Pizza *najskapa=pici[0];
    for (int i=0; i<n; i++){
        if (najskapa->price()<pici[i]->price())
            najskapa=pici[i];
    }
    FlatPizza *flat = dynamic_cast<FlatPizza *>(najskapa);
    if (flat!=0) cout<<*flat;
    else {
        FoldedPizza *folded = dynamic_cast<FoldedPizza*>(najskapa);
        cout<<*folded;
    }
}

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
