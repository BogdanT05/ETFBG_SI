#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 20

typedef struct time {
    int hours, minutes;
} Time;

typedef struct patient {
    char forename[MAX_LENGTH + 1], surname[MAX_LENGTH + 1];
    int severity;
    Time sanitationTime;
} Patient;

typedef struct node {
    Patient patient;
    struct node *next;
} Node;

Patient *read_patient(FILE *input) {
    // memorija
    Patient *patient = malloc(sizeof(*patient));
    int c;
    //Ako je kraj fajla vracamo null
    if ((c = fgetc(input)) == EOF) {
        free(patient);
        return NULL;
    }
    // ako nam treba taj karakter vracamo ga
    if (c != '\n') ungetc(c, input);

    // skeniramo sve potrebne podatke
    fscanf(input, "%20s %20s %d %d:%d",
        patient->forename,
        patient->surname,
        &patient->severity,
        &patient->sanitationTime.hours,
        &patient->sanitationTime.minutes);

    return patient;
}

Node *read_patients() {
    FILE *input = fopen("pacijenti.txt", "r");
    Node *head = NULL;
    Node *last = NULL;

    while (1) {
        Node *node = malloc(sizeof(*node));
        node->next = NULL;
        Patient *patient = read_patient(input);
        // ako smo stigli do kraja fajla
        if (patient == NULL) {
            free(node);
            break;
        }
        // brisemo pomocni pokazivac
        node->patient = *patient;
        free(patient);

        // pravimo ulancanu listu
        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }
    fclose(input);
    return head;
}

void sort_patients(Node *head) {
    // sortiramo bubble sort malo cudno ima ponavljanja ali boze moj
    // prvo soriramo po prioritetu onda po vremenu izvrsavanja
    for (Node *current = head; current != NULL; current = current->next) {
        for (Node *sub_current = current->next; sub_current != NULL; sub_current = sub_current->next) {
            if (current->patient.severity < sub_current->patient.severity) {
                Patient temp = current->patient;
                current->patient = sub_current->patient;
                sub_current->patient = temp;
            }
            if (current->patient.severity == sub_current->patient.severity) {
                if (current->patient.sanitationTime.hours > sub_current->patient.sanitationTime.hours) {
                    Patient temp = current->patient;
                    current->patient = sub_current->patient;
                    sub_current->patient = temp;

                }else if (current->patient.sanitationTime.hours == sub_current->patient.sanitationTime.hours) {
                    if (current->patient.sanitationTime.minutes > sub_current->patient.sanitationTime.minutes) {
                        Patient temp = current->patient;
                        current->patient = sub_current->patient;
                        sub_current->patient = temp;
                    }
                }
            }
        }
    }
}

// pomocna funkcija za sabiranje vremena
Time add_time(Time time1, Time time2) {
    Time sum_time;
    sum_time.hours = time1.hours + time2.hours;
    if (time1.minutes + time2.minutes > 59) {
        sum_time.hours += 1;
        sum_time.minutes = (time1.minutes + time2.minutes)%60;
    }else {
        sum_time.minutes = time1.minutes + time2.minutes;
    }
    return sum_time;
}

// pomocna funckija za poredenje dva vremena
int compare_time(Time time1, Time time2) {
    if (time1.hours > time2.hours) return 1;
    if (time1.hours == time2.hours) {
        if (time1.minutes >= time2.minutes) {
            return 1;
        }else {
            return -1;
        }
    }
    return -1;
}

void match_and_write(Node *head, Time start_time, Time end_time) {
    FILE *output = fopen("raspored.txt", "w");
    Time passed_time = start_time;
    Time elapsed_time = start_time;

    for (Node *current = head; current != NULL; current = current->next) {
        // ako radno vreme nije isteklo i nece isteci nakon sto obavimo operaciju mozemo da prihvatimo pacijenta
       if (compare_time(end_time, passed_time) == 1 && compare_time(end_time, add_time(passed_time, current->patient.sanitationTime)) == 1) {
           passed_time = add_time(passed_time, current->patient.sanitationTime);

           fprintf(output, "%s %s %02d:%02d-%02d:%02d\n",
               current->patient.forename,
               current->patient.surname,
               elapsed_time.hours,
               elapsed_time.minutes,
               passed_time.hours,
               passed_time.minutes);

           elapsed_time = passed_time;
       }
    }
    fclose(output);
}

void deallocate_list(Node *head) {
    for (Node *current = head; current != NULL;) {
        Node *removal = current;
        current = current->next;
        free(removal);
    }
}

int main() {
    Node *patients = read_patients();
    Time start_time, end_time;

    scanf("%2d:%2d-%2d:%2d",
        &start_time.hours,
        &start_time.minutes,
        &end_time.hours,
        &end_time.minutes);

    sort_patients(patients);
    match_and_write(patients, start_time, end_time);
    deallocate_list(patients);
    return 0;
}