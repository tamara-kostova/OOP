#include<stdio.h>

typedef struct Pacient{
char ime[100];
int zdravstveno;
int pregledi;
}Pacient;

typedef struct MaticenDoktor{
char ime[100];
int br_pac;
Pacient niza[200];
float cena;
}doktor;

void najuspesen_doktor(doktor *doktori, int n){
float max=0.0;
int ind=0, osigurani, privatni, maxpregledi=0;
for (int i=0; i<n; i++){
    float zarabotka=0, osigurani=0, privatni=0;
    for (int j=0; j<doktori[i].br_pac; j++){
        if (!doktori[i].niza[j].zdravstveno)
            privatni+=doktori[i].niza[j].pregledi;
        else
            osigurani+=doktori[i].niza[j].pregledi;
    }
    zarabotka+=privatni*doktori[i].cena;
        if ((zarabotka>max)||(zarabotka==max&&privatni+osigurani>maxpregledi)){
            max=zarabotka;
            maxpregledi=privatni+osigurani;
            ind=i;
        }
}
printf("%s %.2f %d", doktori[ind].ime, max, maxpregledi);
}
int main()
{
	int i, j, n, broj;
	doktor md[200];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		//ime na doktor
		scanf("%s", &md[i].ime);
		//broj na pacienti
		scanf("%d", &md[i].br_pac);
		//cena na pregled
		scanf("%f", &md[i].cena);

		for (j = 0; j < md[i].br_pac; j++){
			scanf("%s", &md[i].niza[j].ime);
			scanf("%d", &md[i].niza[j].zdravstveno);
			scanf("%d", &md[i].niza[j].pregledi);
		}
	}
	najuspesen_doktor(md, n);

	return 0;
}
