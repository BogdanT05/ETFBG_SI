#ifndef PROJEKAT2526_ERROR_H
#define PROJEKAT2526_ERROR_H
#include <iostream>
#include <string>


class Error : public std::exception{
public:
    [[nodiscard]] virtual std::string message() const = 0;
    [[nodiscard]] virtual int position() const {return -1;}
    [[nodiscard]] virtual int length() const {return 0;}
    void print(const std::string &line, std::ostream &os = std::cerr) const;

};

#endif //PROJEKAT2526_ERROR_H