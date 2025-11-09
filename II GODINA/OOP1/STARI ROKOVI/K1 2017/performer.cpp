#include "performer.h"

string Performer::genres[4] = {"pop", "rep", "rok"};
void Performer::write_performer() const {
    cout << "\t\t"<< this->name << "(" << genres[this->genre] << ")" << endl;
}


