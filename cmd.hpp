#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>


class cmd{
    public:
        char ** args;
        std::string out;
        std::string in;


        cmd(std::vector<std::string> sep);

        void run();

};