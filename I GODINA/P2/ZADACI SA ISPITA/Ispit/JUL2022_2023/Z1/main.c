#include <stdlib.h>
#include <stdio.h>

double *read_percentages(int *n) {
    *n = 0;
    double *percentages = NULL;
    double d;

    while (1) {
        scanf("%lf", &d);
        percentages = realloc(percentages, (*n+1)*sizeof(*percentages));
        percentages[*n] = d;
        *n = *n + 1;
        if (getchar() == '\n') break; // citamo podatke dok ne unesemo prazan red, alociramo memoriju za broj elemenata niza
    }
    return percentages;
}

double *pass_time(double *percentages, int *n, int time) {
    // po uslovu zadatka smanjujemo procenat bateriju u zavisnosti od vremena
    for (int i = 0; i < *n; i++) {
        if (percentages[i] > 20) {
            percentages[i] = percentages[i] - time;
        }else {
            percentages[i] = percentages[i] - time/2;
        }
        if (percentages[i] < 0) {
            percentages[i] = 0;
        }
    }
    return percentages;
}

void print_percentages(double *percentages, int n) {
    for (int i = 0; i < n; i++) {
        // ispisujemo na 0 decimalnih mesta, ternarni operator za razmak ili prelazak unovi red
        printf("%.0lf%c",percentages[i], (i == n-1)?'\n':' ');
    }
}

int main() {
    int n;
    int time;
    double *percentages = read_percentages(&n);

    while(1){
        // dokle god vreme nije -1 ponavljamo proces
        scanf("%d", &time);
        if (time == -1) break;
        percentages = pass_time(percentages, &n, time);
        print_percentages(percentages, n);
    }

    free(percentages);
    return 0;
}