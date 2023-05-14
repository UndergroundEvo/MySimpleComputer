#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>

using namespace std;

vector<string> variables;
map<int, int>::iterator it;
map<int, int> rows;
string currOperator;
string currLet;

void split(string str, char separator, vector<string>& array) {
    string buffer;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != separator) {
            buffer += str[i];
        }
        else {
            array.push_back(buffer);
            buffer = "";
        }
    }
    array.push_back(buffer);
}
string getAddress(int address) {
    string result = to_string(address);
    if (address <= 9) {
        result = '0' + result;
    }
    return result;
}
string getVariableAddress(string variable) {
    int varAddress = -1;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i] == variable) {
            varAddress = i;
            break;
        }
    }
    if (varAddress == -1) {
        variables.push_back(variable);
        varAddress = variables.size() - 1;
    }

    return getAddress(99 - varAddress);
}
void deleteSpaces(string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            str.erase(i, 1);
            i++;
        }
    }
}
string fromDecToHex(int x) {
    string result;
    string numbers = "0123456789abcdef";
    int num;
    for (int i = 0; i < 4; i++) {
        num = x / pow(16, 3 - i);
        result += numbers[num];
        if (num != 0) {
            x %= static_cast<int>(pow(16, 3 - i));
        }
    }
    return result;
}
string getNewTmp(string& name) {
    int max = 1;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i] == "TMP" + to_string(max)) {
            max += 1;
        }
    }
    name = "TMP" + to_string(max);
    return getVariableAddress("TMP" + to_string(max));
}
string writeMathOperation(string variable1, int& count, ofstream& file, bool isLeft) {
    string assemblerWord;
    string tmpName;
    try {
        int constant = stoi(variable1);
        assemblerWord += getNewTmp(tmpName);
        assemblerWord += " = ";
        string numberStr = to_string(constant);
        while (numberStr.size() < 4) {
            numberStr = "0" + numberStr;
        }
        numberStr = "+" + numberStr;
        assemblerWord += numberStr;
        file << assemblerWord << endl;

        assemblerWord = "";
        assemblerWord += getAddress(count);
        assemblerWord += " LOAD ";
        assemblerWord += getVariableAddress(tmpName);
        file << assemblerWord << endl;
        count++;
    }
    catch (...) {
        assemblerWord += getAddress(count);
        assemblerWord += " LOAD ";
        assemblerWord += getVariableAddress(variable1);
        file << assemblerWord << endl;
        count++;

        tmpName = variable1;
    }

    return tmpName;
}
string writeMathOperation(string variable1, string oper, string variable2, int& count, ofstream& file, bool isLeft) {
    string tmpName;
    tmpName = writeMathOperation(variable1, count, file, isLeft);
    string assemblerWord;


    string varAddress;
    try {
        int constant = stoi(variable2);
        assemblerWord = "";
        assemblerWord += getNewTmp(varAddress);
        assemblerWord += " = ";
        string numberStr = to_string(constant);
        while (numberStr.size() < 4) {
            numberStr = "0" + numberStr;
        }
        numberStr = "+" + numberStr;
        assemblerWord += numberStr;
        file << assemblerWord << endl;
        varAddress = getVariableAddress(varAddress);
    }
    catch (...) {
        varAddress = getVariableAddress(variable2);
    }

    assemblerWord = "";
    assemblerWord += getAddress(count);
    if (oper == "+") {
        assemblerWord += " ADD ";
    }
    else if (oper == "-") {
        assemblerWord += " SUB ";
    }
    else if (oper == "/") {
        assemblerWord += " DIVIDE ";
    }
    else if (oper == "*") {
        assemblerWord += " MUL ";
    }
    assemblerWord += varAddress;
    file << assemblerWord << endl;
    count++;

    if (!isLeft) {
        assemblerWord = "";
        assemblerWord += getAddress(count);
        assemblerWord += " STORE ";
        bool a = false;
        if (currOperator == "LET") {
            for (int i = 0; i < variables.size(); i++) {
                if (currLet == variables[i]) {
                    assemblerWord += getVariableAddress(currLet);
                    a = true;
                    break;
                }
            }
        }
        if (!a) {
            assemblerWord += getNewTmp(tmpName);
        }
        file << assemblerWord << endl;
        count++;
    }
    return tmpName;
}
string recursionMath(vector<string> mathArray, int& count, ofstream& file, bool isLeft) {
    string nameTmp;
    if (mathArray.size() == 1) {
        nameTmp = writeMathOperation(mathArray[0], count, file, isLeft);
        return nameTmp;
    }
    else if (mathArray.size() == 3) {
        nameTmp = writeMathOperation(mathArray[0], mathArray[1], mathArray[2], count, file, isLeft);
        return nameTmp;
    }

    int indexLastOper = 0;
    int isBracket = 0;
    for (int i = mathArray.size() - 1; i > 0; i--) {
        if (mathArray[i][0] == ')') {
            isBracket++;
        }
        if (mathArray[i][0] == '(') {
            isBracket--;
        }
        if (isBracket == 0) {
            if (mathArray[i][0] == '+' || mathArray[i][0] == '-') {
                indexLastOper = i;
                break;
            }
            if (mathArray[i][0] == '*' || mathArray[i][0] == '/') {
                indexLastOper = i;
            }
        }
    }

    vector<string> left;
    int tmp = 0;
    int bracket = 0;
    if (mathArray[0][0] == '(' && mathArray[indexLastOper - 1][0] == ')') {
        tmp = 1;
        for (int i = tmp; i < indexLastOper - tmp; i++) {
            if (mathArray[i][0] == '(') {
                bracket++;
            }
            else if (mathArray[i][0] == ')') {
                bracket--;
            }
            if (bracket < 0) {
                tmp = 0;
                break;
            }
        }
    }
    for (int i = tmp; i < indexLastOper - tmp; i++) {
        left.push_back(mathArray[i]);
    }

    vector<string> right;
    tmp = 0;
    int last = mathArray.size();
    if (mathArray[indexLastOper + 1][0] == '(' && mathArray[mathArray.size() - 1][0] == ')') {
        tmp = 1;
        for (int i = indexLastOper + tmp + 1; i < last - tmp; i++) {
            if (mathArray[i][0] == '(') {
                bracket++;
            }
            else if (mathArray[i][0] == ')') {
                bracket--;
            }
            if (bracket < 0) {
                tmp = 0;
                break;
            }
        }
    }
    for (int i = indexLastOper + tmp + 1; i < last - tmp; i++) {
        right.push_back(mathArray[i]);
    }

    nameTmp = recursionMath(right, count, file, false);
    recursionMath(left, count, file, true);

    string assemblerWord;
    assemblerWord += getAddress(count);
    if (mathArray[indexLastOper][0] == '+') {
        assemblerWord += " ADD ";
    }
    else if (mathArray[indexLastOper][0] == '-') {
        assemblerWord += " SUB ";
    }
    else if (mathArray[indexLastOper][0] == '/') {
        assemblerWord += " DIVIDE ";
    }
    else if (mathArray[indexLastOper][0] == '*') {
        assemblerWord += " MUL ";
    }
    assemblerWord += getVariableAddress(nameTmp);
    file << assemblerWord << endl;
    count++;

    if (!isLeft) {
        assemblerWord = "";
        assemblerWord += getAddress(count);
        assemblerWord += " STORE ";
        bool a = false;
        if (currOperator == "LET") {
            for (int i = 0; i < variables.size(); i++) {
                if (currLet == variables[i]) {
                    assemblerWord += getVariableAddress(currLet);
                    a = true;
                    break;
                }
            }
        }
        if (!a) {
            assemblerWord += getNewTmp(nameTmp);
        }
        file << assemblerWord << endl;
        count++;
    }

    return nameTmp;
}
//Гарантирует что результат в аккумуляторе
string writeMath(string str, int& count, ofstream& file) {
    vector<string> mathArray;
    string buffer = "";
    string operators = "+-*/()";

    for (int i = 0; i < str.size(); i++) {
        if (operators.find(str[i]) == string::npos) {
            buffer += str[i];
        }
        else {
            if (buffer != "") {
                mathArray.push_back(buffer);
                buffer = "";
            }
            buffer += str[i];
            mathArray.push_back(buffer);
            buffer = "";
        }
    }
    if (buffer != "") {
        mathArray.push_back(buffer);
    }

    if (mathArray.size() > 1) {
        return recursionMath(mathArray, count, file, false);
    }

    string assemblerWord = "";
    string varName = writeMathOperation(mathArray[0], count, file, false);
    assemblerWord += getAddress(count);
    assemblerWord += " LOAD ";
    assemblerWord += getVariableAddress(varName);
    file << assemblerWord << endl;
    count++;
    return varName;
}
int findCache(string key) {
    return rows.find(stoi(key))->second;
}
void writeLogic(string str, int& count, ofstream& file, string address) {
    vector<string> logicArray;
    string buffer = "";
    string operators = "<>=";

    for (int i = 0; i < str.size(); i++) {
        if (operators.find(str[i]) == string::npos) {
            buffer += str[i];
        }
        else {
            if (buffer != "") {
                logicArray.push_back(buffer);
                buffer = "";
            }
            buffer += str[i];
            logicArray.push_back(buffer);
            buffer = "";
        }
    }
    logicArray.push_back(buffer);

    writeMath(logicArray[0], count, file);

    string nameTmp;
    string assemblerWord;
    assemblerWord += getAddress(count);
    assemblerWord += " STORE ";
    assemblerWord += getNewTmp(nameTmp);
    file << assemblerWord << endl;
    count++;

    writeMath(logicArray[2], count, file);

    assemblerWord = "";
    assemblerWord += getAddress(count);
    assemblerWord += " SUB ";
    assemblerWord += getVariableAddress(nameTmp);
    file << assemblerWord << endl;
    count++;

    if (logicArray[1] == "<") {
        assemblerWord = "";
        assemblerWord += getAddress(count);
        assemblerWord += " JNS ";
        assemblerWord += getAddress(findCache(address));
        file << assemblerWord << endl;
        count++;
    }
    else if (logicArray[1] == ">") {
        assemblerWord = "";
        assemblerWord += getAddress(count);
        assemblerWord += " JNEG ";
        assemblerWord += getAddress(findCache(address));
        file << assemblerWord << endl;
        count++;
    }
    else if (logicArray[1] == "=") {
        assemblerWord = "";
        assemblerWord += getAddress(count);
        assemblerWord += " JZ ";
        assemblerWord += getAddress(findCache(address));
        file << assemblerWord << endl;
        count++;
    }
}
void cacheRow(string a, int b) {
    rows.insert(pair<int, int>(stoi(a), b));
}
int main(int argc, char* argv[]){
    //char argv[] = "data.vb";
    cout << "Start translator" << endl;
    if (argc < 2) return -1;
    ifstream in(argv[1]); // окрываем файл для чтения
    if (!in.is_open()) return -1;
    ofstream out(argv[2]);
    if (!out.is_open()) return -1;
    string line;
    int count = 0;
    int num;
    vector<string> lineWords;
    while (getline(in, line)) {
        split(line, ' ', lineWords);
        string command = lineWords[1];
        currOperator = lineWords[1];
        string assemblerWord;
        if (command == "REM") {
            lineWords.clear();
            continue;
        }
        else if (command == "INPUT") {
            cacheRow(lineWords[0], count);
            assemblerWord += getAddress(count);
            assemblerWord += " READ ";
            assemblerWord += getVariableAddress(lineWords[2]);
            out << assemblerWord << endl;
            count++;
        }
        else if (command == "PRINT") {
            cacheRow(lineWords[0], count);
            assemblerWord += getAddress(count);
            assemblerWord += " WRITE ";
            assemblerWord += getVariableAddress(lineWords[2]);
            out << assemblerWord << endl;
            count++;
        }
        else if (command == "LET") {
            cacheRow(lineWords[0], count);
            string mathStr;
            bool isMath = false;
            for (int i = 0; i < lineWords.size(); i++) {
                if (isMath) {
                    mathStr += lineWords[i];
                }
                if (lineWords[i] == "=") {
                    isMath = true;
                }
            }
            currLet = lineWords[2];
            string varName = writeMath(mathStr, count, out);
            for (int i = 0; i < variables.size(); i++) {
                if (variables[i] == varName) {
                    variables[i] = lineWords[2];
                }
            }

        }
        else if (command == "IF") {
            cacheRow(lineWords[0], count);
            string logicStr;
            bool isLogic = false;
            for (int i = 0; i < lineWords.size(); i++) {
                if (lineWords[i] == "GOTO") {
                    isLogic = false;
                }
                if (isLogic) {
                    logicStr += lineWords[i];
                }
                if (lineWords[i] == "IF") {
                    isLogic = true;
                }
            }

            writeLogic(logicStr, count, out, lineWords[lineWords.size() - 1]);

        }
        else if (command == "END") {
            cacheRow(lineWords[0], count);
            assemblerWord += getAddress(count);
            assemblerWord += " HALT ";
            assemblerWord += "00";
            out << assemblerWord << endl;
            count++;

        }
        lineWords.clear();
    }
    in.close();     // закрываем файл
    out.close();
    cout << "End Translator" << endl;
    return 0;
}