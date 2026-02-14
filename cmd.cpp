#include "cmd.hpp"


cmd::cmd(std::vector<std::string> sep){
    this->args = new char* [sep.size() + 1];

    for(int i = 0;i < sep.size();i++){
        this->args[i] = new char [sep[i].length() + 1];
        strcpy(this->args[i], sep[i].c_str());
        this->args[i][sep[i].length()] = '\0';
    }
    this->args[sep.size()] = NULL;
}
void cmd::run(){
    pid_t pid = fork();

    if(pid == 0){
        execvp(args[0], args);
    }else{
        wait(NULL);
    }
    
}