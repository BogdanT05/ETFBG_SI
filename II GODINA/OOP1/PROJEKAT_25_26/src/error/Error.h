#ifndef PROJEKAT2526_ERROR_H
#define PROJEKAT2526_ERROR_H
#include <iostream>
#include <string>


class Error {
public:
    virtual std::string message() = 0;
    virtual int position() {return -1;}
    virtual int length() {return 0;}
    virtual void print(const std::string &line);

    virtual ~Error() = default;
};

#endif //PROJEKAT2526_ERROR_H