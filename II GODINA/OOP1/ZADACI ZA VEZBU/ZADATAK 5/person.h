#ifndef ZADACI_ZA_VEZBU_PERSON_H
#define ZADACI_ZA_VEZBU_PERSON_H
#include "jmbg.h"

class Person {
private:
    string name;
    Jmbg jmbg;
public:
    friend class Directory;
    Person(): jmbg(Jmbg("")){}
    Person(string name, Jmbg j) : jmbg(j) {
        this->name = name;
    }

    void write_name() const {
        cout << this->name <<"(";
        this->jmbg.write_jmbg();
        cout << ")" << endl;
    }
};

#endif //ZADACI_ZA_VEZBU_PERSON_H