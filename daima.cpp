#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>

using namespace std;

// 计算RPN表达式的函数
double calculateRPN(const string& expression) {
    stack<double> stk;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        // 如果是数字，入栈
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            stk.push(stod(token));
        } 
        // 如果是运算符，出栈计算后入栈
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            if (stk.size() < 2) {
                throw invalid_argument("表达式格式错误：运算符数量多于操作数");
            }
            double b = stk.top(); stk.pop();
            double a = stk.top(); stk.pop();
            double result;

            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") {
                if (b == 0) throw runtime_error("错误：除以零");
                result = a / b;
            }
            else if (token == "^") result = pow(a, b);

            stk.push(result);
        } 
        // 未知符号
        else {
            throw invalid_argument("未知符号：" + token);
        }
    }

    if (stk.size() != 1) {
        throw invalid_argument("表达式格式错误：操作数数量多于运算符");
    }
    return stk.top();
}

int main() {
    cout << "=== RPN计算器 ===" << endl;
    cout << "说明：输入逆波兰表达式（元素以空格分隔，支持+、-、*、/、^）" << endl;
    cout << "示例：3 4 + 5 * （对应普通表达式：(3+4)*5）" << endl;
    cout << "输入'exit'退出程序" << endl << endl;

    string input;
    while (true) {
        cout << "请输入RPN表达式：";
        getline(cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        try {
            double result = calculateRPN(input);
            cout << "计算结果：" << result << endl << endl;
        } catch (const exception& e) {
            cout << "错误：" << e.what() << endl << endl;
        }
    }

    cout << "程序已退出" << endl;
    return 0;
}
