#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


class cmd{
    public:
        std::vector<char *> args;
        std::string out;
        std::string in;


        cmd(std::vector<std::string>& sep);

        void run();

        void redirect();

        void print_args();
};