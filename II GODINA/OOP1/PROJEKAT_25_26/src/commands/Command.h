#ifndef PROJEKAT2526_COMMAND_H
#define PROJEKAT2526_COMMAND_H


class Command {
protected:
    std::string name;
    std::vector<std::string> arguments;
    std::vector<std::string> options;

    std::istream *is;
    std::ostream *os;
public:
    Command(std::string name, std::vector<std::string> arguments, std::vector<std::string> options, std::istream *is = &std::cin, std::ostream *os = &std::cout):
        name(std::move(name)), arguments(std::move(arguments)), options(std::move(options)), is(is), os(os)
    {}

    virtual void set_input(std::istream *is_) = 0;
    virtual void set_output(std::ostream *os_) = 0;

    virtual void execute() = 0;
    virtual ~Command() = default;
};


#endif //PROJEKAT2526_COMMAND_H