#include <stdio.h>
#include <stdbool.h>

struct Laptop{
char firma[100];
float golemina;
bool touch;
int cena;
};
typedef struct Laptop Laptop;

struct ITStore{
char ime[100];
char lokacija[100];
Laptop laptopi[100];
int brlaptopi;
};
typedef struct ITStore ITStore;

void print(ITStore *itstores, int n){
for (int j=0; j<n; j++){
printf("%s %s\n", itstores[j].ime, itstores[j].lokacija);
for (int i=0; i<itstores[j].brlaptopi; i++){
    printf("%s ", itstores[j].laptopi[i].firma);
    if(itstores[j].laptopi[i].golemina-(int)itstores[j].laptopi[i].golemina==0)
        printf("%d",(int)itstores[j].laptopi[i].golemina);
    else printf("%.1f",itstores[j].laptopi[i].golemina);
    printf(" %d\n",itstores[j].laptopi[i].cena);}
}
}

void najeftina_ponuda(ITStore *itstores, int n){
int min=999999, indeks=0;
    for (int i=0; i<n; i++){
        for (int j=0; j<itstores[i].brlaptopi; j++){
            if (itstores[i].laptopi[j].touch){
                if (itstores[i].laptopi[j].cena<min){
                    min=itstores[i].laptopi[j].cena;
                    indeks=i;
                }
            }
        }
    }
printf("Najeftina ponuda ima prodavnicata:\n%s %s\n", itstores[indeks].ime, itstores[indeks].lokacija);
printf("Najniskata cena iznesuva: %d\n", min);
}


int main() {
    ITStore s[100];
    int n;
    scanf("%d",&n); //broj na IT prodavnici
    for (int i=0; i<n; i++){
        scanf("%s %s %d", s[i].ime, s[i].lokacija, &s[i].brlaptopi);
        for (int j=0; j<s[i].brlaptopi; j++){
            scanf("%s %f %d %d", s[i].laptopi[j].firma, &s[i].laptopi[j].golemina, &s[i].laptopi[j].touch, &s[i].laptopi[j].cena);
        }
    }

    //pecatenje na site prodavnici
    print (s, n);

    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}
