#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <cstdlib>

class RPNCalculator {
public:
    void clear() { while (!st_.empty()) st_.pop(); }

    bool empty() const { return st_.empty(); }

    void push(double value) { st_.push(value); }

    double pop() {
        if (empty()) throw std::runtime_error("stack underflow");
        double v = st_.top();
        st_.pop();
        return v;
    }

    void calculate(const std::string& op) {
        if (op == "+" || op == "-" || op == "*" || op == "/") {
            if (st_.size() < 2)
                throw std::runtime_error("operator '" + op + "' needs two operands");
            double b = pop();
            double a = pop();
            if (op == "+")      push(a + b);
            else if (op == "-") push(a - b);
            else if (op == "*") push(a * b);
            else {              // division
                if (b == 0) throw std::runtime_error("division by zero");
                push(a / b);
            }
        } else {
            throw std::runtime_error("unknown operator '" + op + "'");
        }
    }

    double evaluate(const std::string& line) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            char* end = nullptr;
            double val = std::strtod(token.c_str(), &end);
            if (end != token.c_str() && *end == '\0') {
                push(val);                 // number
            } else {
                calculate(token);          // operator
            }
        }
        if (empty()) throw std::runtime_error("empty expression");
        double result = pop();
        if (!empty()) throw std::runtime_error("extra operands left on stack");
        return result;
    }

private:
    std::stack<double> st_;
};

/* ---------------- interactive driver ---------------- */
int main() {
    RPNCalculator calc;
    std::cout << "C++  Calculator\n"
                 "Enter expression (e.g. '5 5 +'), or 'q' to quit.\n";
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line == "q" || line == "Q") break;
        try {
            double res = calc.evaluate(line);
            std::cout << "Result: " << res << '\n';
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << '\n';
            calc.clear();          // recover clean state
        }
    }
    std::cout << "Good-bye!\n";
    return 0;
}
