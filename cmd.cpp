#include "cmd.hpp"

cmd::cmd(std::vector<std::string>& tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].compare(">") == 0) {
            this->out = tokens[i + 1];
            i += 1;
        } else if (tokens[i].compare("<") == 0) {
            this->in = tokens[i + 1];
            i += 1;
        } else {
            char* new_str = new char[tokens[i].length() + 1];
            strcpy(new_str, tokens[i].c_str());
            new_str[tokens[i].length()] = '\0';
            this->args.push_back(new_str);
        }
    }
    this->args.push_back(NULL);
}

void cmd::redirect() {
    if (this->in.length() > 0) {
        int i = open(this->in.c_str(), O_RDONLY);
        dup2(i, STDIN_FILENO);
        close(i);
    }
    if (this->out.length() > 0) {
        int o = open(this->out.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(o, STDOUT_FILENO);
        close(o);
    }
}
void cmd::run() {
    execvp(args[0], args.data());
}

void cmd::print_args() {
    for (int i = 0; i < this->args.size(); i++) {
        if(this->args[i] == NULL){
            std::cout << "[null]";
        }else{
            std::cout << "[" << args[i] << "]";
        }
        
    }
    std::cout << std::endl;
}