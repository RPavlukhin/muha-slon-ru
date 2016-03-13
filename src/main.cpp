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
    setlocale(LC_ALL, "rus");

   if (argc!=4) {
        cout << "Заданы неверные параметры! Верный синтаксис: [имя бинарника] [путь к словарю] [первое слово] [последнее слово]" << endl;
        return EXIT_FAILURE;
    }    

    set <string> dict;
    ifstream dictfile;

    // открываем файл со словарем
    dictfile.open (argv[1], std::ios::in);
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

    // считываем из консоли заданное первое и последнее слово
    string startword = argv[2];
    string finword = argv[3];

	// проверяем, есть ли начальное и конечное слова в словаре
	if (dict.find(startword)==dict.end()) cerr << "Начального слова нет в словаре!" << endl;
	if (dict.find(finword)==dict.end()) cerr << "Конечного слова нет в словаре!" << endl;


    WordRouter wr(dict);
   // строим маршрут
   std::list <string> route;
   int res = wr.CreateRoute(startword,finword,route);

    // выводим его на экран
   for (auto it = route.begin(); it !=route.end(); ++it)
    {
        cout << *it << endl;
    }
	
   if (route.empty()) cout << "В словаре не найдено корректной цепочки между словами"<<endl;

    return res;
}

