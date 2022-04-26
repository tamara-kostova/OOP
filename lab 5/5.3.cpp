#include <iostream>
using namespace std;

class Matrica{
    float matrica[10][10];
    int dimenzija=0;
public:
    Matrica(int n=0){
        dimenzija=10;
        for(int i=0;i<dimenzija;i++){
            for(int j=0;j<dimenzija;j++){
                matrica[i][j]=n;
            }
        }
    }
    Matrica &operator+(const Matrica &m){
        for (int i=0; i<dimenzija; i++)
            for (int j=0; j<dimenzija; j++)
                matrica[i][j]+=m.matrica[i][j];
        return *this;
    }
    Matrica &operator-(const Matrica &m){
        for (int i=0; i<dimenzija; i++)
            for (int j=0; j<dimenzija; j++)
                matrica[i][j]-=m.matrica[i][j];
        return *this;
    }
    Matrica &operator*(const Matrica &m){
        int rezultat[dimenzija][dimenzija];
        for(int i=0;i<dimenzija;i++)
            for(int j=0;j<dimenzija;j++){
                rezultat[i][j]=0;
                    for(int k=0;k<dimenzija;k++)
                        rezultat[i][j]+=(matrica[i][k]*m.matrica[k][j]);
                }
        for (int i=0; i<dimenzija; i++)
            for (int j=0; j<dimenzija; j++)
                matrica[i][j]=rezultat[i][j];
        return *this;
    }
    friend istream &operator >> (istream &is, Matrica &m){
        int broj;
        is>>broj;
        is>>broj;
        m.dimenzija=broj;
        float b;
        for (int i=0; i<m.dimenzija; i++)
            for (int j=0; j<m.dimenzija; j++){
                is>>b;
                m.matrica[i][j]=b;}
        return is;
    }
    friend ostream &operator << (ostream &o, const Matrica &m){
        for (int i=0; i<m.dimenzija; i++){
            for (int j=0; j<m.dimenzija; j++)
                o<<m.matrica[i][j]<<" ";
            o<<endl;}
        return o;
    }
};

int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout<<R;
    return 0;
}
