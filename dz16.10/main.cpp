#include <iostream>
#include <string>

using namespace std;
class SimpleStack {
private:
    char* arr;
    int capacity;
    int top;

public:
    SimpleStack(int size) : capacity(size), top(-1) {
        arr = new char[capacity];
    }

    ~SimpleStack() {
        delete[] arr;
    }

    void push(char c) {
        if (top < capacity - 1) {
            arr[++top] = c;
        }
    }

    char pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return '\0'; 
    }

    char peek() {
        if (top >= 0) {
            return arr[top];
        }
        return '\0'; 
    }

    bool isEmpty() {
        return top == -1;
    }
};

bool isOpeningBracket(char c) {
    return c == '(' || c == '{' || c == '[';
}

bool isClosingBracket(char c) {
    return c == ')' || c == '}' || c == ']';
}

bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
        (opening == '{' && closing == '}') ||
        (opening == '[' && closing == ']');
}

string checkBrackets(const string& str) {
    SimpleStack bracketStack(str.length());

    for (size_t i = 0; i < str.length(); ++i) {
        char current = str[i];

        if (isOpeningBracket(current)) {
            bracketStack.push(current);
        }
        else if (isClosingBracket(current)) {
            if (bracketStack.isEmpty()) {
                return "Error: No matching opening bracket for " + string(1, current) + " at position " + to_string(i);
            }
            char top = bracketStack.pop();
            if (!isMatchingPair(top, current)) {
                return "Error: Mismatched brackets at position " + to_string(i);
            }
        }
        else if (current == ';') {
            break;
        }
    }
    if (!bracketStack.isEmpty()) {
        return "Error: Unmatched opening bracket found.";
    }
    return "Correctly placed brackets.";
}

int main() {
    string input;
    cout << "Enter a string (end with ';'): ";
    getline(cin, input); 
    if (!input.empty() && input.back() == ';') {
        input.pop_back();
    }
    string result = checkBrackets(input);
    cout << result << endl;
    return 0;
}
