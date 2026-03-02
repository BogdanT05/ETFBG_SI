#ifndef PROJEKAT2526_EXECUTION_ERROR_H
#define PROJEKAT2526_EXECUTION_ERROR_H
#include "Error.h"


class Execution_Error : public Error{
private:
    std::string message_;
public:
    explicit Execution_Error(std::string message_);
    [[nodiscard]]std::string message() const override;
};


#endif //PROJEKAT2526_EXECUTION_ERROR_H