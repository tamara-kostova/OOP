#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

struct RabotnaNedela{
int casovi[DENOVI];
int brnaned;
};
typedef struct RabotnaNedela RN;

struct Rabotnik{
char ime[50];
RN nedeli[NEDELI];
};
typedef struct Rabotnik R;

int maxNedela(R *r){
    int max=0, ind, s=0;
    for (int i=0; i<NEDELI; i++){
            int s=0;
            for (int j=0; j<DENOVI; j++)
                s+=r[0].nedeli[i].casovi[j];
            if (s>max){
                max=s;
                ind=i;
            }
    }
    return ind+1;
}

void table(R *r, int n){
printf("Rab\t1\t2\t3\t4\tVkupno\n");
for (int i=0; i<n; i++){
    int vkupno=0;
    printf("%s\t",r[i].ime);
    for (int j=0;j<NEDELI; j++){
        int s=0;
        for (int k=0; k<DENOVI; k++)
            s+=r[i].nedeli[j].casovi[k];
    printf("%d\t", s);
    vkupno+=s;
    }
printf("%d\n",vkupno);
}
}

int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
