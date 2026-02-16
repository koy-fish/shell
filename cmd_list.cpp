#include "cmd_list.hpp"

cmd_list::cmd_list(std::vector<std::vector<std::string> > parsed) {
    for (int i = 0; i < parsed.size(); i++) {
        this->cmds.push_back(cmd(parsed[i]));
    }
}

void cmd_list::run() {
    // setup pipes;
    int pipes[this->cmds.size() - 1][2];
    for (int i = 0; i < this->cmds.size() - 1; i++) {
        pipe(pipes[i]);
    }

    for (int i = 0; i < cmds.size(); i++) {
        pid_t pid = fork();
        if(pid < 0){
            std::cerr << "[ERROR] fork";
        }
        //child
        if (pid == 0) {
            //redirect pipes
            /*
            cmd1 |
            cmd2 |
            cmd3 |
            cmd4
            */
            if (i < cmds.size() - 1) {
                if(dup2(pipes[i][1], STDOUT_FILENO)){
                    std::cerr << "[ERROR] dup\n";
                }
            }
            if (i > 0) {
                if(dup2(pipes[i - 1][0], STDIN_FILENO)){
                    std::cerr << "[ERROR] dup\n";
                }
            }

            //close all the pipes
            for (int i = 0; i < this->cmds.size() - 1; i++) {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            //run the command
            cmds[i].redirect();
            cmds[i].run();
        }
    }

    //parent: closed all pipes
    for (int i = 0; i < this->cmds.size() - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    //parent: wait for children
    for (int i = 0; i < this->cmds.size(); i++) {
        wait(NULL);
    }
}