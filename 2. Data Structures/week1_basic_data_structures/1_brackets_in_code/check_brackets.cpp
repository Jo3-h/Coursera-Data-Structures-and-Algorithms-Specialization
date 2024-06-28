#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    int exit = -1;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(Bracket(next, position + 1));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.size() == 0){
                exit = position + 1;
                break;
            }
            Bracket temp = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (temp.Matchc(next) == false){
                //std::cout<<"pos: "<<position<<std::endl;
                exit = position + 1;
                break;
            }
            
        }
    }
    //std::cout<<"stack size: "<<opening_brackets_stack.size()<<std::endl;
    //std::cout<<"exit: "<<exit<<std::endl;


    // Printing answer, write your code here
    if (exit != -1){
        std::cout<<exit;
    } else if (opening_brackets_stack.size() > 0){
        std::cout<<opening_brackets_stack.top().position;
    } else {
        std::cout<<"Success";
    }

    return 0;
}
