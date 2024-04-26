#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ���������
float generateRandomFloat(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

int generateRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// ������Ŀ
void generateExercise(int numQuestions, int maxOperand, char operators[], int numOperators, int allowDecimal, int allowParentheses, int outputToFile) {
    ofstream outFile;
    srand(time(NULL));

    if (outputToFile) {
        outFile.open("exercise.txt");
        if (!outFile.is_open()) {
            cout << "�޷����ļ���" << endl;
            return;
        }
    }

    for (int i = 0; i < numQuestions; i++) {
        // ������ɲ�����
        int operand1, operand2;
        if (allowDecimal) {
            operand1 = generateRandomFloat(0, maxOperand);
            operand2 = generateRandomFloat(0, maxOperand);
        }
        else {
            operand1 = generateRandomInt(0, maxOperand);
            operand2 = generateRandomInt(0, maxOperand);
        }

        // ���ѡ�������
        char oper = operators[rand() % numOperators];

        // �������Ϊ��
        if (oper == '/' && operand2 == 0) {
            i--; // ��������
            continue;
        }

        // �����Ŀ
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
        cout << "��Ŀ�ѱ��浽 exercise.txt �ļ��С�" << endl;
    }
}

int main() {
    int numQuestions, maxOperand, numOperators, allowDecimal, allowParentheses, outputToFile;
    char operators[4];

    cout << "��������Ŀ������";
    cin >> numQuestions;

    cout << "����������������ֵ��";
    cin >> maxOperand;

    cout << "�Ƿ�����С�������ǣ�1����0����";
    cin >> allowDecimal;

    cout << "�Ƿ��������ţ����ǣ�1����0����";
    cin >> allowParentheses;

    cout << "�Ƿ�������ļ������ǣ�1����0����";
    cin >> outputToFile;

    cout << "������ϣ��ʹ�õ���������������4������";
    cin >> numOperators;

    if (numOperators > 4) {
        cout << "������������Ϊ4�������������롣" << endl;
        return 1;
    }

    cout << "������ϣ��ʹ�õ������������+ - * /����";
    cin >> operators;

    generateExercise(numQuestions, maxOperand, operators, numOperators, allowDecimal, allowParentheses, outputToFile);

    return 0;
}
