#include "cmd.hpp"


class cmd_list{
    public:
        std::vector<cmd> cmds;
        cmd_list(std::vector<std::vector<std::string> > parsed);
        void run();
};