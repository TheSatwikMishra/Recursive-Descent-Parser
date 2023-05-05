#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Global variables for input and output
string input;
string output;
int index = 0;

// Function prototypes
void expr();
void term();
void factor();

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get the precedence of an operator
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return -1;
}

// Function to convert infix expression to postfix
void infixToPostfix() {
    // Reset the output string and index
    output = "";
    index = 0;

    // Call the top-level expression function
    expr();
}

// Top-level expression function
void expr() {
    // Call the term function
    term();

    // While the current character is an operator
    while (isOperator(input[index])) {
        // Append the operator to the output string
        output += input[index++];

        // Call the term function
        term();
    }
}

// Term function
void term() {
    // Call the factor function
    factor();

    // While the current character is an operator with higher precedence
    while (isOperator(input[index]) && precedence(input[index]) >= precedence(output[output.length() - 1])) {
        // Append the operator to the output string
        output += input[index++];

        // Call the factor function
        factor();
    }
}

// Factor function
void factor() {
    // If the current character is a left parenthesis
    if (input[index] == '(') {
        // Append it to the output string
        output += input[index++];

        // Call the expression function
        expr();

        // If the current character is a right parenthesis
        if (input[index] == ')') {
            // Append it to the output string
            output += input[index++];
        }
        else {
            // Error: expected right parenthesis
            cout << "Error: expected right parenthesis" << endl;
            exit(1);
        }
    }
    // If the current character is a digit or letter
    else if (isdigit(input[index]) || isalpha(input[index])) {
        // Append it to the output string
        output += input[index++];
    }
    // If the current character is a unary minus
    else if (input[index] == '-') {
        // Append it to the output string
        output += input[index++];

        // Call the factor function
        factor();
    }
    else {
        // Error: invalid character
        cout << "Error: invalid character" << endl;
        exit(1);
    }
}

// Main function
int main() {
    // Read input from user
    cout << "Enter infix expression: ";
    cin >> input;

    // Convert infix to postfix
    infixToPostfix();

    // Print the postfix expression
    cout << "Postfix expression: " << output << endl;

    return 0;
}
