#ifndef PROJEKAT2526_IOERROR_H
#define PROJEKAT2526_IOERROR_H
#include "Execution_Error.h"


class IOError : public Execution_Error{
public:
    explicit IOError(std::string& message_);
};


#endif //PROJEKAT2526_IOERROR_H