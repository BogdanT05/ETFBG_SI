#ifndef PROJEKAT2526_SEMATIC_ERROR_H
#define PROJEKAT2526_SEMATIC_ERROR_H
#include "Error.h"


class Semantic_Error : public Error{
private:
    std::string message_;
public:
    explicit Semantic_Error(std::string message_);
    [[nodiscard]] std::string message() const override;
};


#endif //PROJEKAT2526_SEMATIC_ERROR_H