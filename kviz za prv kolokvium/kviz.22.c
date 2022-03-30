#include <stdio.h>
#include <string.h>

typedef struct Proizvod{
char kod[20];
int cena;
int dostapni;
}Proizvod;
typedef struct Narachka{
char ime[15];
Proizvod proizvodi[10];
int naracani[10];
int n;
}Narachka;

void pecatiFaktura(Narachka n){
printf("Faktura za %s\n", n.ime);
for (int i=0; i<n.n; i++)
    for (int j=0; j<n.n-i-1; j++)
    if(strcmp(n.proizvodi[j].kod, n.proizvodi[j+1].kod) > 0){
                Proizvod tmp = n.proizvodi[j];
                n.proizvodi[j] = n.proizvodi[j+1];
                n.proizvodi[j+1] = tmp; }
int vkupno=0;
for (int i=0; i<n.n; i++){
    if (n.proizvodi[i].dostapni<n.naracani[i]){
        printf("Fakturata ne moze da se izgotvi\n");
        return  ;}
    else{
    printf("%s %d %d %d\n", n.proizvodi[i].kod, n.proizvodi[i].cena, n.naracani[i], n.naracani[i]*n.proizvodi[i].cena);
    vkupno+=n.naracani[i]*n.proizvodi[i].cena;}}
printf("Vkupnata suma na fakturata e %d",vkupno);
}

int main() {

    Narachka narachka;
    scanf("%s",&narachka.ime);
    scanf("%d",&narachka.n);

    for (int i = 0; i < narachka.n; ++i) {
        scanf("%s",&narachka.proizvodi[i].kod);
        scanf("%d",&narachka.proizvodi[i].cena);
        scanf("%d",&narachka.proizvodi[i].dostapni);
    }

    for (int j = 0; j < narachka.n; ++j) {
       scanf("%d",&narachka.naracani[j]);
    }

    pecatiFaktura(narachka);

    return 0;
}
