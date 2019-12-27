#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <iostream>
#include <stack>
#include <cctype>
using namespace std;
int store[26];

int pri(char op) // 优先级函数
{
    if (op == '(')	return 0;
    if (op == '+' || op == '-')	return 1;
    if (op == '*' || op == '/')	return 2;
    return 3;
}

void do_cal(stack<int>& cal_s,char op) // 在cal_s栈上进行运算
{
    int num1 = cal_s.top();	cal_s.pop();
    int num2 = cal_s.top();	cal_s.pop();
    switch(op)
    {
        case '+' :
            cal_s.push(num2 + num1);	break;
        case '-' :
            cal_s.push(num2 - num1);	break;
        case '*' :
            cal_s.push(num2 * num1);	break;
        case '/' :
            cal_s.push(num2 / num1);	break;
        case '^' :
            cal_s.push(pow(num2,num1));
    }
}

int cal(string exp)
{
    // 预处理，将表达式中的变量名用相应值代替
    int i = 0;
    while(i < exp.length())
    {
        if (exp[i] >= 'a' && exp[i] <= 'z') // 查找到变量名，进行值替换
        {
            int val = store[exp[i] - 'a'];
            exp[i] = '(';
            stringstream ss;
            string s_val;
            ss << val;
            ss >> s_val;
            s_val = s_val + ')';
            exp.insert(i + 1,s_val);
            i = i + s_val.length() + 1;
        }
        else i ++;
    }

    //预处理：在负数前面补零
    i = 0;
    while(i < exp.length())
    {
        if (i == 0 && exp[i] == '-')
            exp.insert(i,"0");
        else
        {
            if (exp[i] == '(' && exp[i + 1] == '-')
                exp.insert(i + 1,"0");
        }
        i ++;
    }

    stack<char> op_s; // 放操作符
    stack<int> cal_s; // 放操作数，并在该栈上进行动态运算

    i = 0; // 用i遍历整个表达式
    int len = exp.length();
    while(i < len)
    {
        char tem = exp[i];
        if (isdigit(tem)) // 操作数直接放
        {
            int sum = tem - '0';
            i ++;
            while(isdigit(exp[i]))
            {
                sum = sum * 10 + exp[i] - '0';
                i ++;
            }
            cal_s.push(sum);
            continue;
        }
        if (tem == '(') // 左括号直接放
        {
            op_s.push(tem);
            i ++;
            continue;
        }
        if (tem == ')') // 右括号将下一个左括号之前的操作数全部出栈
        {
            while(op_s.top() != '(')
            {
                do_cal(cal_s,op_s.top());
                op_s.pop();
            }
            op_s.pop();
            i ++;
            continue;
        }
        if (op_s.empty() || pri(tem) > pri(op_s.top())) // 空栈或优先级大于栈顶操作符，直接放
            op_s.push(tem);
        else
        {
            while(!op_s.empty() && pri(op_s.top()) >= pri(tem))
            {
                do_cal(cal_s,op_s.top());
                op_s.pop();
            }
            op_s.push(tem);
        }
        i ++;
    }

    while(!op_s.empty()) // 最后将op_s中剩下的操作符出栈
    {
        do_cal(cal_s,op_s.top());
        op_s.pop();
    }

    return cal_s.top();
}
