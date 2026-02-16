#include <sys/wait.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "cmd.hpp"


std::vector<std::string> tokenize(std::string s);
void run(std::string input);
int main() {
    run("cat < shell.cpp > other_shell.cpp");
    return 0;
}


void run(std::string input) {
    std::vector<std::string> tokens = tokenize(input);
    
    cmd my_cmd(tokens);
    my_cmd.run();
}


std::vector<std::string> tokenize(std::string s) {
    s += " ";
    std::vector<std::string> res;
    std::string curr = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            if (curr.length() > 0) {
                res.push_back(curr);
            }
            curr = "";
        }else {
            curr += s[i];
        }
    }
    return res;
}
