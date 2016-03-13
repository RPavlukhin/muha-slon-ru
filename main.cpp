#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <list>
#include <queue>
#include <fstream>

#include "branch.h"
#include "wordrouter.h"


using namespace std;

int main(int argc, char *argv[])
{
    setlocale(0, "");

   if (argc!=3) {
        cout << "Заданы неверные параметры! Верный синтаксис: muhoslon [путь к файлу настроек] [путь к словарю]" << endl;
        return EXIT_FAILURE;
    }    

    set <string> dict;
    string startword, finword;
    ifstream dictfile, conffile;

    // открываем файл с начальным и конечным словами
    conffile.open (argv[1],ios::in);
    if(!conffile) {
        std::cerr<<"Ошибка при открытии файла"<< conffile << endl;
        return EXIT_FAILURE;
    }
    // заносим значенияв переменные
    std::getline (conffile,startword);
    std::getline (conffile,finword);
    conffile.close();

    // открываем файл со словарем
    dictfile.open (argv[2], std::ios::in);
    if(!dictfile) {
        std::cerr<<"Ошибка при открытии файла"<< dictfile <<endl;
        return EXIT_FAILURE;
    }

    string tmp;
    while (!dictfile.eof())
        {
         std::getline(dictfile,tmp);
         //добавляем в словарь
         if (!tmp.empty()) dict.insert(tmp);
        }
    dictfile.close();




    WordRouter wr(dict);
   // строим маршрут
   list <string> route;
   int res = wr.CreateRoute(startword,finword,route);

    // выводим его на экран
    for (string & elem: route)
    {
        cout << elem << endl;
    }
    return res;
}

