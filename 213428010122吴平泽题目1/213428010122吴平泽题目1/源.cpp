#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 生成随机数
float generateRandomFloat(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

int generateRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 生成题目
void generateExercise(int numQuestions, int maxOperand, char operators[], int numOperators, int allowDecimal, int allowParentheses, int outputToFile) {
    ofstream outFile;
    srand(time(NULL));

    if (outputToFile) {
        outFile.open("exercise.txt");
        if (!outFile.is_open()) {
            cout << "无法打开文件！" << endl;
            return;
        }
    }

    for (int i = 0; i < numQuestions; i++) {
        // 随机生成操作数
        int operand1, operand2;
        if (allowDecimal) {
            operand1 = generateRandomFloat(0, maxOperand);
            operand2 = generateRandomFloat(0, maxOperand);
        }
        else {
            operand1 = generateRandomInt(0, maxOperand);
            operand2 = generateRandomInt(0, maxOperand);
        }

        // 随机选择运算符
        char oper = operators[rand() % numOperators];

        // 避免除数为零
        if (oper == '/' && operand2 == 0) {
            i--; // 重新生成
            continue;
        }

        // 输出题目
        if (outputToFile) {
            if (allowParentheses && rand() % 2 == 0) {
                outFile << "(" << operand1 << " " << oper << " " << operand2 << ") = " << endl;
            }
            else {
                outFile << operand1 << " " << oper << " " << operand2 << " = " << endl;
            }
        }
        else {
            if (allowParentheses && rand() % 2 == 0) {
                cout << "(" << operand1 << " " << oper << " " << operand2 << ") = " << endl;
            }
            else {
                cout << operand1 << " " << oper << " " << operand2 << " = " << endl;
            }
        }
    }

    if (outputToFile) {
        outFile.close();
        cout << "题目已保存到 exercise.txt 文件中。" << endl;
    }
}

int main() {
    int numQuestions, maxOperand, numOperators, allowDecimal, allowParentheses, outputToFile;
    char operators[4];

    cout << "请输入题目数量：";
    cin >> numQuestions;

    cout << "请输入操作数的最大值：";
    cin >> maxOperand;

    cout << "是否允许小数？（是：1，否：0）：";
    cin >> allowDecimal;

    cout << "是否允许括号？（是：1，否：0）：";
    cin >> allowParentheses;

    cout << "是否输出到文件？（是：1，否：0）：";
    cin >> outputToFile;

    cout << "请输入希望使用的运算符数量（最多4个）：";
    cin >> numOperators;

    if (numOperators > 4) {
        cout << "运算符数量最多为4个，请重新输入。" << endl;
        return 1;
    }

    cout << "请输入希望使用的运算符（例如+ - * /）：";
    cin >> operators;

    generateExercise(numQuestions, maxOperand, operators, numOperators, allowDecimal, allowParentheses, outputToFile);

    return 0;
}
