#ifndef PROJEKAT2526_UNKNOWN_COMMAND_ERROR_H
#define PROJEKAT2526_UNKNOWN_COMMAND_ERROR_H
#include "Semantic_Error.h"


class Unknown_Command_Error : public Semantic_Error{
private:
    std::string command;
    int position_;
public:
    Unknown_Command_Error(std::string &command, int position_);
    [[nodiscard]] std::string message() const override;
    [[nodiscard]] int position() const override;
    [[nodiscard]] int length() const override;
};


#endif //PROJEKAT2526_UNKNOWN_COMMAND_ERROR_H