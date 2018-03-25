#include<cctype>
#include<iostream>
//#include<map>
#include <sstream>

using namespace std;
enum input_value
{
    //NAME用来支持定义字符的数学值 例如 pi=3.1416926
//    NAME,
            NUMBER, END,
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
    PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
};

// 数值表达式 计算器 支持 + - * / (  ) 按符号优先级 计算
// 一个数值间不能有空格,比如数字十 10 不能为 1  0,只能为10
// 数值与操作符直接可以有任意空格,比如 10  +  2  *  5

class Calculator
{
private:
    stringstream strin;//输入流
    input_value current_value;
//    map<string, double> table;
    double number_value;
    string string_value;
    int number_of_errors;

    double error(const string &s);

    double fun_1(bool get);

    double fun_2(bool get);

    double fun_3(bool get);

    input_value get_value();

    void CalculatorInit();

public:

    double calculateString(const string &strs);
};

double Calculator::error(const string &s)
{
    ++number_of_errors;
    cerr << "错误:" << s << endl;
    return 0;
}

input_value Calculator::get_value()
{
    char ch = 0;
    strin >> ch;
    switch (ch)
    {
        case 0:
            return current_value = END;
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return current_value = input_value(ch);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            strin.putback(ch);
            strin >> number_value;
            return current_value = NUMBER;
        default:
//            if (isalpha(ch))
//            {
//                strin.putback(ch);
//                strin >> string_value;
//                return current_value = NAME;
//            }
            error("非法输入！");
            return current_value = PRINT;
    }
}

double Calculator::fun_3(bool get)
{
    if (get) get_value();
    switch (current_value)
    {
        case NUMBER:
        {
            double v = number_value;
            get_value();
            return v;
        }
//        case NAME:
//        {
//            double &v = table[string_value];
//            if (get_value() == ASSIGN)
//            {
//                v = fun_1(true);
//            }
//            return v;
//        }
        case MINUS:
            return -fun_3(true);
        case LP:
        {
            double e = fun_1(true);
            if (current_value != RP)
            {
                return error(") 缺失");
            }
            get_value();
            return e;
        }
        default:
        {
            return error("输入错误！");
        }
    }
}

double Calculator::fun_2(bool get)
{
    double left = fun_3(get);
    for (;;)
        switch (current_value)
        {
            case MUL:
                left *= fun_3(true);
                break;
            case DIV:
                if (double d = fun_3(true))
                {
                    left /= d;
                    break;
                }
                {
                    return error("除数不能为0!");
                }
            default:
                return left;
        }
}

double Calculator::fun_1(bool get)
{
    double left = fun_2(get);
    for (;;)
        switch (current_value)
        {
            case PLUS:
                left += fun_2(true);
                break;
            case MINUS:
                left -= fun_2(true);
                break;
            default:
                return left;
        }
}

void Calculator::CalculatorInit()
{
    current_value = PRINT;
    number_value = 0;
    number_of_errors = 0;
//    table["pi"] = 3.1415926535897932385;
//    table["e"] = 2.718284590452354;
    string_value = "";
    strin.clear();
    strin.str("");
}


double Calculator::calculateString(const string &strs)
{
    CalculatorInit();
    strin << strs << "=";
    while (strin)
    {
        get_value();
        if (current_value == END) break;
        if (current_value == PRINT) continue;
        return fun_1(false);
    }
    return 0;
}


int main()
{
    string line;
    Calculator calculator;
    while (getline(cin, line))
    {
        cout << calculator.calculateString(line) << endl;
    }
    return 0;
}