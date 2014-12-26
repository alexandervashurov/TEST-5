// Created by Alexander Vashurov
// 2014
// Test 5
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void read(string filename, vector<string>& text){
    char simvol;
    string stroka;
    ifstream R(filename);
    while (!(R.eof()))				//заполнение текста
    {
        R.get(simvol);
        if (simvol != '\n'&& !R.eof())
        {
            stroka.push_back(simvol);
        }
        else
        {
            text.push_back(stroka);
            stroka.clear();
        }
    }
}

void opredelitel(const vector<string>& text, vector<int>& probeli, vector<char>& tip){
    int flagprobel = 0;				//определяет нужно ли считать пробелы
    int flag = 0;					//считает пробелы
    probeli.resize(text.size() + 1);
    tip.resize(text.size() + 1);
    for (int j = 0; j < text.size(); j++){
        tip[j] = ' ';
        for (int i = 0; (i < text[j].size()) && flagprobel == 0; i++){
            if (text[j][i] == ' ')
                flag += 1;
            if ((text[j][i] == '*') || ((i + 1 < text[j].size()) && (((text[j][i] <= '9'&& text[j][i] >= '0') && text[j][i + 1] == '.')))){
                flagprobel = 1;
                tip[j] = text[j][i];
            }
        }
        probeli[j] = flag;
        flag = 0;
        flagprobel = 0;
    }
}

void zavorotli(vector<string>& text, vector<char>& tip){
    
    for (int i = 0; i < text.size(); i++){
        if (tip[i] != ' '){
            text[i] = "<li>" + text[i] + "</li>";
        }
    }
}

void redaktor(vector<string>& text, vector<int>& probeli, vector<char>& tip){
    for (int i = 0; i < text.size(); i++){
        if (tip[i] == '*'){
            if (i == 0)
                text[i] = "<ul>" + text[i];
            else
                if (probeli[i - 1] < probeli[i])
                    text[i] = "<ul>" + text[i];
                else
                    if (tip[i - 1] != tip[i] && probeli[i] == probeli[i - 1])
                        text[i] = "<ul>" + text[i];
                    else
                        if (probeli[i + 1] < probeli[i])
                            text[i] = text[i] + "</ul>";
                        else
                            if (tip[i + 1] != tip[i] && probeli[i] == probeli[i + 1])
                                text[i] = text[i] + "</ul>";
            
        }
        else
            if (tip[i] != ' '){
                if (i == 0)
                    text[i] = "<ol>" + text[i];
                else
                    if (probeli[i - 1] < probeli[i])
                        text[i] = "<ol>" + text[i];
                    else
                        if ((tip[i - 1] == '*' || tip[i - 1] == ' ') && probeli[i] == probeli[i - 1])
                            text[i] = "<ol>" + text[i];
                        else
                            if (probeli[i + 1] < probeli[i])
                                text[i] = text[i] + "</ol>";
                            else
                                if ((tip[i + 1] == '*' || tip[i - 1] == ' ') && probeli[i] == probeli[i + 1])
                                    text[i] = text[i] + "</ol>";
            }
        
    }
}

void clear(vector<string>& text, vector<int>& probeli, vector<char>& tip){
    
    for (int i = 0; i < text.size(); i++){
        if (tip[i] == '*')
            text[i].erase(text[i].find('*') - probeli[i], probeli[i] + 1);
        else
            if (tip[i] != ' ')
                text[i].erase(text[i].find('.') - probeli[i], probeli[i] + 2);
    }
}

void write(string filename, vector<string>& text){
    ofstream out(filename);
    out << "<html>" << endl << "<body>" << endl;
    
    for (int i = 0; i < text.size(); i++){
        for (int j = 0; j < text[i].size(); j++)
            out << text[i][j];
        out << endl;
    }
    out << "</body>" << endl << "</html>" << endl;
}

int main(int argc, char* argv[])
{
    string input = "in.txt", output = "out.txt";
    
    if (argc >= 2){
        input = argv[1];
    }
    if (argc >= 3){
        output = argv[2];
    }
    
    vector<string> text;              ////содержит исходный текст
    
    read(input, text);
    
    vector<int>probeli;				//хранит колво пробелов  в каждой строке
    
    vector<char>tip;				//хранит тип списка
    
    opredelitel(text, probeli, tip);
    
    zavorotli(text, tip);
    
    redaktor(text, probeli, tip);
    
    clear(text, probeli, tip);
    
    write(output, text);
    
    system("pause");
    return 0;
    
}