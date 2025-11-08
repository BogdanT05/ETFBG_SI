#include "jmbg.h"

int compare_jmbg(Jmbg j1, Jmbg j2) {
    return strcmp(j1.jmbg, j2.jmbg);
}

void Jmbg::write_jmbg() const {
    cout << this->jmbg;
}
