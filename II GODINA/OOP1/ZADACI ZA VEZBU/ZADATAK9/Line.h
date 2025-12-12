#ifndef ZADACI_ZA_VEZBU_LINE_H
#define ZADACI_ZA_VEZBU_LINE_H
#include <iostream>

class Line {
    static int id_counter;
    int id = id_counter++;

protected:
    virtual void write(std::ostream &os) const;
    virtual Line* copy() const = 0;

public:
    Line() = default;
    Line(const Line &line){}
    Line& operator=(const Line &line) {return *this;}


    virtual double length() const = 0;
    friend std::ostream& operator << (std::ostream &os, const Line &line);

    virtual ~Line() = default;
};


#endif //ZADACI_ZA_VEZBU_LINE_H