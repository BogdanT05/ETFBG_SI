#include <stdlib.h>
#include <stdio.h>

int **read_users() {
    int **users = NULL;
    int n;
    int i = 0;
    int j = 0;

    // unosimo proizvoljan broj i vrsta i kolona zato dupla while petlja
    while (1) {
        j = 0;
        // prvo proveravamo da li je zavrsen unos ako nije alociramo prostor
        scanf("%d", &n);
        if (n == -1) break;
        users = realloc(users, (i+2)*sizeof(*users));
        users[i] = NULL;
        // petlja za unos elemenata u vrsti
        while (1) {
            // alociramo memoriju za jedan vise nego sto nam je potrebno zato sto
            // cemo dodati jos jedan element (broj el) u vrstu
            users[i] = realloc(users[i], (j+2)*sizeof(*users[i]));
            if (j == 0) users[i][j] = n;
            else scanf("%d", &users[i][j]);
            char c;
            // vracamo char ako nije \n
            if ((c = getchar()) == '\n') break;
            ungetc(c, stdin);
            j++;
        }
        j++;

        // umecemo element tako sto sve elemnete pomerimo za jedan u desno
        // tako pravimo prostor tj dupliranje elementa na odg poziciji
        for (int k = j; k > 0;k--) {
            users[i][k] = users[i][k-1];
        }
        // duzina pratilaca ce biti j-1 zato sto ne zelimo citavu duzinu liste vec samo posle id koji se pojavljuju
        users[i][1] = j-1;
        users[i+1] = NULL;
        i++;
    }
    return users;
}

int *remove_el (int *user, int n) {
    // brisemo element tako sto sabijemo listu i realociramo je
    for (int i = n; i <= user[1]; i++) {
        user[i] = user[i+1];
    }

    user[1] = user[1] - 1;
    user = realloc(user, (user[1]+2)*sizeof(*user));
    return user;
}

void remove_non_existent_users(int **users) {
    int len = 0;
    // prvo lista elemenata koji treba da ostanu i broj vrsta matrice
    while (users[len] != NULL) len++;
    int correct_followers[len];

    for (int i = 0; i < len; i++) {
        correct_followers[i] = users[i][0];
    }

    for (int i = 0; i < len; i++) {
        for (int j = 2; j <= users[i][1]+1;) {
            int remove = 1;
            for (int k = 0; k < len; k++) {
                // ako se element pojavi u odgovarajucim followerima necemo da ga obrisemo
                if (correct_followers[k] == users[i][j]) {
                    remove = 0;
                }
            }
            // ako smo obrisali element ne zelimo da predjemo na sl element zato sto smo sabili listu pa mozda preskocimo element koji treba da obrisemo
            if (remove) users[i] = remove_el(users[i], j);
            else j++;
        }
    }
}

void print_users(int **users) {
    for (int i = 0; users[i] != NULL; i++) {
        printf("%d;", users[i][0]);
        for (int j = 2; j <= users[i][1]+1; j++) {
            printf("%d%c", users[i][j],   (j == users[i][1]+1)?'\n':' ');
        }
    }
}

void free_users(int **users) {
    for (int i = 0; users[i] != NULL; i++) {
        free(users[i]);
    }
    free(users);
}

int main() {
    int **users = read_users();
    remove_non_existent_users(users);
    print_users(users);
    free_users(users);
    return 0;
}