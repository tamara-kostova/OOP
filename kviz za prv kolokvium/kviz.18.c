#include<stdio.h>
#include<string.h>
typedef struct  SkiLift{
    char ime[15];
    int korisnici;
    int funkcija;

}SkiLift;
typedef struct SkiCenter{
    char ime[20];
    char drzava[20];
    SkiLift skiliftovi[20];
    int brojsl;
}SkiCenter;

void najgolemKapacitet(SkiCenter *sc, int n){
int kapacitet[n], max=0, ind=0;
    for (int i=0; i<n; i++){
        kapacitet[i]=0;
        for (int j=0; j<sc[i].brojsl; j++)
            if (sc[i].skiliftovi[j].funkcija)
                kapacitet[i]+=sc[i].skiliftovi[j].korisnici;
        if (kapacitet[i]>max||(kapacitet[i]==max&&sc[i].brojsl>sc[ind].brojsl)){
            max=kapacitet[i];
            ind=i;
        }
    }
    printf("%s\n%s\n%d",sc[ind].ime,sc[ind].drzava,max);
}
int main()
{
    int n;
	scanf("%d", &n);
	SkiCenter skicentar[n];
	for (int i = 0; i < n; i++){
		scanf("%s",&skicentar[i].ime);
		scanf("%s",&skicentar[i].drzava);
		scanf("%d",&skicentar[i].brojsl);
            for (int j=0; j<skicentar[i].brojsl; j++){
			scanf("%s",&skicentar[i].skiliftovi[j].ime);
            scanf("%d",&skicentar[i].skiliftovi[j].korisnici);
            scanf("%d",&skicentar[i].skiliftovi[j].funkcija);
            }
	}

    najgolemKapacitet(skicentar,n);
	return 0;
}
