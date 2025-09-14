#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[31];
    int team_id;
    unsigned time;
    char country_code[4];
} runner_t;

typedef struct runner_node {
    runner_t *runner;
    struct runner_node *next;
} runner_node_t;

typedef struct {
    int team_id;
    unsigned time;
    char country_code[4];
} team_t;

typedef struct team_node {
    team_t *team;
    struct team_node *next;
} team_node_t;

runner_node_t* read_node(FILE *input) {
    int c;
    // prostor
    runner_node_t *node = malloc(sizeof(*node));
    node->next = NULL;
    node->runner = malloc(sizeof(*node->runner));

    // uzimamo karakter ako je kraj fajla vracamo null
    if ((c = fgetc(input)) == EOF) {
        free(node->runner);
        free(node);
        return NULL;
    }
    // ako karakter koji smo uzeli je slovo to nam treba tako da ga vracamo
    if (c != '\n') ungetc(c, input);

    // unos prema formatu
    fscanf(input, "%30[^|]|%d %d %3s",
        node->runner->name,
        &node->runner->team_id,
        &node->runner->time,
        node->runner->country_code);

    return node;
}

runner_node_t *read_list(FILE *input) {
    runner_node_t *head = NULL;
    runner_node_t *last = NULL;
    runner_node_t *node;

    // standardno ulancana lista
    while (1) {
        node = read_node(input);
        if (node == NULL) break;
        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }

    return head;
}

team_node_t *reversed(team_node_t *head) {
    team_node_t *previous = NULL;
    team_node_t *next = NULL;
    // obrcemo ulancanu listu tako sto kazemo svakom da gleda onog pre sebe
    for (team_node_t *current = head; current != NULL; current = next) {
        next = current->next; // pamtimo koji je sledeci elemnt koji treba da obrnemo
        current->next = previous;
        previous = current;
    }
    return previous;
}

team_node_t *create_teams(runner_node_t *runners) {
    team_node_t *head = NULL;
    team_node_t *last = NULL;

    for (runner_node_t *current = runners; current != NULL; current = current->next) {
        team_node_t *node = malloc(sizeof(*node));
        node->next = NULL;
        node->team = malloc(sizeof(*node->team));

        runner_node_t *start = current;
        int unsigned time = start->runner->time;

        // kako su timovi sortirani idemo redom dok smo na jednom timu i sabiramo za njega
        while (current->next != NULL && current->next->runner->team_id == start->runner->team_id) {
            time = time + current->next->runner->time;
            current = current->next;
        }

        // stavljamo podatke u node i pravimo ulancanu listu
        node->team->team_id = start->runner->team_id;
        strcpy(node->team->country_code, start->runner->country_code);
        node->team->time = time;

        if (head == NULL) head = node;
        else last->next = node;
        last = node;
    }

    head = reversed(head);
    return head;
}

void sort(team_node_t *teams) {
    // sortiramo leksikografski i po vremenu, bubble sort
    for (team_node_t *current = teams; current != NULL; current = current->next) {
        for (team_node_t *sub_current = current->next; sub_current != NULL; sub_current = sub_current->next) {
            if (strcmp(current->team->country_code, sub_current->team->country_code) > 0) {
                team_t *tmp = current->team;
                current->team = sub_current->team;
                sub_current->team = tmp;
            }
            if (strcmp(current->team->country_code, sub_current->team->country_code) == 0) {
                if (current->team->time > sub_current->team->time) {
                    team_t *tmp = current->team;
                    current->team = sub_current->team;
                    sub_current->team = tmp;
                }
            }
        }
    }
}

void print_top_teams(team_node_t *teams, FILE *output) {
    sort(teams);
    for (team_node_t *current = teams; current != NULL;) {
        int counter = 0;
        team_node_t *start = current;
        // ispisujemo redom najbrza 3 tima iz svake drzve po istom principu kao kad smo pravili timove
        while ((current != NULL) && (counter < 3) && (strcmp(current->team->country_code, start->team->country_code) == 0)){
            fprintf(output, "Team: %d Country: %s Time: %u\n", current->team->team_id,
                current->team->country_code, current->team->time);
            counter++;
            current = current->next;
        }

        // ako postoji jos timova koji nisu u top 3 zelimo da ih preskocimo
        while(current && strcmp(current->team->country_code, start->team->country_code) == 0) current = current->next;
    }
}

void free_runners(runner_node_t *runners) {
    for (runner_node_t *current = runners; current != NULL;) {
        runner_node_t *removal = current;
        current = current->next;
        free(removal->runner);
        free(removal);
    }
}

void free_teams(team_node_t *runners) {
    for (team_node_t *current = runners; current != NULL;) {
        team_node_t *removal = current;
        current = current->next;
        free(removal->team);
        free(removal);
    }
}

int main() {
    const char* in_file_name = "trka.txt";
    const char* out_file_name = "izlaz.txt";
    FILE *in_file = fopen(in_file_name, "r");
    FILE *out_file = fopen(out_file_name, "w");

    runner_node_t *runners = read_list(in_file);
    team_node_t *teams = create_teams(runners);
    print_top_teams(teams, out_file);

    fclose(in_file);
    fclose(out_file);

    free_runners(runners);
    free_teams(teams);
    return 0;
}