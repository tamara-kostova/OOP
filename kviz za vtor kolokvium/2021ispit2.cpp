#include <iostream>
#include <cstring>
using namespace std;

enum mehanizam{RNA,DNA};
enum sostojka{DMG, PEG, SM_102, DPSC};

class CovidVaccine{
protected:
    char proizvoditel[100];
    char *ime;
    float koeficient;
public:
    CovidVaccine(char *proizvoditel="", char *ime="", float koeficient=0){
        strcpy(this->proizvoditel, proizvoditel);
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime, ime);
        this->koeficient=koeficient;
    }
    virtual float calculateVaccineEfficiency(){
        return koeficient;
    }
    bool operator <=(CovidVaccine &v){
        return calculateVaccineEfficiency()<=v.calculateVaccineEfficiency();
    }
};
class GeneticVaccine : public CovidVaccine{
    mehanizam tip;
public:
    GeneticVaccine(char *proizvoditel="", char *ime="", float koeficient=0, int tip=0) : CovidVaccine(proizvoditel,ime,koeficient){
        this->tip=(mehanizam)tip;
    }
    float calculateVaccineEfficiency(){
        if (tip==RNA) return 1.35*koeficient;
        return 1.55*koeficient;
    }
    friend ostream &operator<<(ostream &o, GeneticVaccine &gv){
        o<<"Vaccine info: "<<gv.ime<<" - "<<gv.proizvoditel<<" - "<<gv.calculateVaccineEfficiency()<<endl;
        o<<"Mechanism for storing genetic information: ";
        if  (gv.tip==RNA) o<<"RNA"<<endl;
        else o<<"DNA"<<endl;
        return o;
    }
};
class InactivatedVaccine : public CovidVaccine{
    sostojka s;
public:
    InactivatedVaccine(char *proizvoditel="", char *ime="", float koeficient=0, int s=0) : CovidVaccine(proizvoditel,ime,koeficient){
        this->s=(sostojka) s;
    }
    float calculateVaccineEfficiency(){
        if (s==DMG) return 0.9*koeficient;
        if (s==PEG) return 1.12*koeficient;
        if (s==SM_102) return 0.85*koeficient;
        if (s=DPSC) return 1.2*koeficient;
    }
    friend ostream &operator<<(ostream &o, InactivatedVaccine &iv){
        o<<"Vaccine info: "<<iv.ime<<" - "<<iv.proizvoditel<<" - "<<iv.calculateVaccineEfficiency()<<endl;
        o<<"The vaccine consists of the following ingredient: ";
        if  (iv.s==DMG) o<<"DMG"<<endl;
        if (iv.s==PEG) o<<"PEG"<<endl;
        if (iv.s==SM_102) o<<"SM_102"<<endl;
        if (iv.s==DPSC) o<<"DPSC"<<endl;
        return o;
    }
};

void  mostEffectiveInactivatedVaccine(CovidVaccine **vakcini, int n){
    int max=0, indeks;
    InactivatedVaccine *najefektivna;
    for (int i=0; i<n; i++){
        InactivatedVaccine *iv = dynamic_cast<InactivatedVaccine *>(vakcini[i]);
        if (iv){
            if (vakcini[i]->calculateVaccineEfficiency()>=max){
                najefektivna=iv;
                max=najefektivna->calculateVaccineEfficiency();
            }
        }
    }
    cout<<*najefektivna;
}

int main() {
    int test_case;

    cin >> test_case;

    //For CovidVaccine
    char manufacturer[100];
    char vaccineName[100];
    float basicEfficiencyCoefficient;

    //For GeneticVaccine
    unsigned short geneticMechanism; // 0 -> RNA, 1 -> DNA

    //For InactivatedVaccine
    unsigned short constituentIngredient; //0 -> DMG, 1 -> PEG, 2 -> SM_102, 3 -> DPSC


    if (test_case == 1) {
        // Test Case GeneticVaccine - Constructor, operator <<, calculateVaccineEfficiency
        cout << "Testing class GeneticVaccine, operator<< and calculateVaccineEfficiency" << endl;
        cin.get();
        cin.getline(manufacturer, 100);
        cin.getline(vaccineName, 100);
        cin >> basicEfficiencyCoefficient;
        cin >> geneticMechanism;

        GeneticVaccine gv(manufacturer, vaccineName, basicEfficiencyCoefficient, geneticMechanism);

        cout << gv;
    } else if (test_case == 2) {
        // Test Case InactivatedVaccine - Constructor, operator <<, calculateVaccineEfficiency
        cout << "Testing class InactivatedVaccine, operator<< and calculateVaccineEfficiency" << endl;
        cin.get();
        cin.getline(manufacturer, 100);
        cin.getline(vaccineName, 100);
        cin >> basicEfficiencyCoefficient;
        cin >> constituentIngredient;

        InactivatedVaccine iv(manufacturer, vaccineName, basicEfficiencyCoefficient, constituentIngredient);

        cout << iv;
    } else if (test_case == 3) {
        cout << "Testing operator <=" << endl;

        cin.get();
        cin.getline(manufacturer, 100);
        cin.getline(vaccineName, 100);
        cin >> basicEfficiencyCoefficient;
        cin >> geneticMechanism;

        GeneticVaccine gv(manufacturer, vaccineName, basicEfficiencyCoefficient, geneticMechanism);

        cin.get();
        cin.getline(manufacturer, 100);
        cin.getline(vaccineName, 100);
        cin >> basicEfficiencyCoefficient;
        cin >> constituentIngredient;

        InactivatedVaccine iv(manufacturer, vaccineName, basicEfficiencyCoefficient, constituentIngredient);

        if (gv <= iv) {
            cout << iv;
        } else {
            cout << gv;
        }
    } else if (test_case == 4) {
        cout << "Testing operator <=" << endl;

        cin.get();
        cin.getline(manufacturer, 100);
        cin.getline(vaccineName, 100);
        cin >> basicEfficiencyCoefficient;
        cin >> geneticMechanism;

        GeneticVaccine gv1(manufacturer, vaccineName, basicEfficiencyCoefficient, geneticMechanism);

        cin.get();
        cin.getline(manufacturer, 100);
        cin.getline(vaccineName, 100);
        cin >> basicEfficiencyCoefficient;
        cin >> geneticMechanism;

        GeneticVaccine gv2(manufacturer, vaccineName, basicEfficiencyCoefficient, geneticMechanism);

        if (gv1 <= gv2) {
            cout << gv2;
        } else {
            cout << gv1;
        }
    } else if (test_case == 5) {
        cout << "Testing function: mostEffectiveInactivatedVaccine " << endl;

        //1 - GeneticVaccine
        //2 - InactivatedVaccine
        short vaccineType;

        int number_of_vaccines;
        CovidVaccine **vaccine_array;

        cin >> number_of_vaccines;

        vaccine_array = new CovidVaccine *[number_of_vaccines];

        for (int i = 0; i < number_of_vaccines; ++i) {
            cin >> vaccineType;

            cin.get();
            cin.getline(manufacturer, 100);
            cin.getline(vaccineName, 100);
            cin >> basicEfficiencyCoefficient;

            switch (vaccineType) {
                case 1:
                    cin >> geneticMechanism;
                    vaccine_array[i] = new GeneticVaccine(manufacturer, vaccineName, basicEfficiencyCoefficient,
                                                          geneticMechanism);
                    break;
                case 2:
                    cin >> constituentIngredient;
                    vaccine_array[i] = new InactivatedVaccine(manufacturer, vaccineName, basicEfficiencyCoefficient,
                                                              constituentIngredient);
                    break;
            }

        }

        mostEffectiveInactivatedVaccine(vaccine_array, number_of_vaccines);
        delete[] vaccine_array;
    }

    return 0;
}
