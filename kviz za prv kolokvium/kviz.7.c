#include <stdio.h>
#include <string.h>

struct Vozenje{
char ime[100];
int traenje;
float cena;
int daliPopust;
};
typedef struct Vozenje Vozenje;

struct ZabavenPark{
char ime[100];
char lokacija[100];
Vozenje niza[100];
int n;
};
typedef struct ZabavenPark ZabavenPark;

void pecati(ZabavenPark *niza, int n){
for (int j=0; j<n; j++){
printf("%s %s\n",niza[j].ime,niza[j].lokacija);
for (int i=0; i<niza[j].n; i++)
    printf("%s %d %.2f\n", niza[j].niza[i].ime, niza[j].niza[i].traenje,niza[j].niza[i].cena);
}
}
void najdobar_park(ZabavenPark *niza, int n){
int maxpopust=0, maxvreme=0, indeks=0;
for (int i=0; i<n; i++){
    int brojac=0, vreme=0;
    for (int j=0; j<niza[i].n; j++){
        if (niza[i].niza[j].daliPopust)
            brojac++;
        vreme+=niza[i].niza[j].traenje;
    }
if (brojac>maxpopust){
    maxpopust=brojac;
    maxvreme=vreme;
    indeks=i;
}
if (brojac==maxpopust&&vreme>maxvreme){
    maxvreme=vreme;
    indeks=i;
}
}
printf("Najdobar park: %s %s\n",niza[indeks].ime,niza[indeks].lokacija);
}

int main()
{
	int i, j, n, broj;
	//kreiraj niza od maksimum 100 zabavni parkovi
	ZabavenPark ff[100];
	scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
		//ime na festivalot
		scanf("%s", ff[i].ime);
        //mesto
		scanf("%s", ff[i].lokacija);
		//broj na filmovi
		scanf("%d", &ff[i].n);

		for (j = 0; j < ff[i].n; j++){
			scanf("%s", ff[i].niza[j].ime);  			/* Ime na filmot */
			scanf("%d", &ff[i].niza[j].traenje); 		/* Vremetraenje   */
			scanf("%f", &ff[i].niza[j].cena); 	/* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);	/* Popust */

		}


			}
    pecati(ff,n);
    najdobar_park(ff,n);

	return 0;
}
