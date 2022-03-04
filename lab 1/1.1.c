/*Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N
производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума*/
#include <stdio.h>
#include <stdlib.h>

struct Proizvod
{
char ime[20];
float cena;
float kolicina;
};
typedef struct Proizvod Proizvod;

void read(Proizvod *p){
scanf("%s %f %f", p->ime, &p->cena, &p->kolicina);
}
void print(Proizvod p){
printf("%s\t%.2f x %.1f = %.2f\n", p.ime, p.cena, p.kolicina, p.cena*p.kolicina);
}

int main()
{
    int n;
    float total=0;
    scanf("%d", &n);
    Proizvod proizvodi[n];
    for (int i=0; i<n; i++){
        read(proizvodi+i);
        total+=(proizvodi[i].cena*proizvodi[i].kolicina);}
    for (int i=0; i<n; i++)
    {
        printf("%d. ", i+1);
        print(proizvodi[i]);
    }
    printf("Total: %.2f",total);
    return 0;
}
