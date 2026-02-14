#include <sys/wait.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "cmd.hpp"


std::vector<std::string> parse(std::string s);
void run(std::string input);
int main() {
    run("cat shell.cpp");
    run("ls -l");

    return 0;
}

void run(std::string input) {

    std::vector<std::string> separated = parse(input);
    cmd my_cmd(separated);
    my_cmd.run();
}

std::vector<std::string> parse(std::string s) {
    s += " ";
    std::vector<std::string> res;
    std::string curr = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            if (curr.length() > 0) {
                res.push_back(curr);
            }
            curr = "";
        } else {
            curr += s[i];
        }
    }
    return res;
}
