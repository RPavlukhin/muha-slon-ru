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
        std::wcerr << "Заданы неверные параметры! Верный синтаксис: [имя бинарника] [путь к словарю] [первое слово] [последнее слово]" << endl;
        return EXIT_FAILURE;
    }    

    set <string> dict;
    ifstream dictfile;

    // открываем файл со словарем
    dictfile.open (argv[1], std::ios::in);
    if(!dictfile) {
        std::wcerr<<"Ошибка при открытии файла"<< dictfile <<endl;
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

	//проверяем, одинаковой ил длины слова
	if (startword.length()!=finword.length()) 
	{
        wcerr << "Слова различной длины!" << endl;
		return EXIT_FAILURE;
	}

	// проверяем, есть ли начальное и конечное слова в словаре
	if (dict.find(startword)==dict.end()) {
        wcerr << "ПЕРВОГО слова НЕТ в словаре!" << endl;
		return EXIT_FAILURE;
	}
	if (dict.find(finword)==dict.end()) 
	{
        wcerr << "ВТОРОГО слова НЕТ в словаре!" << endl;
		return EXIT_FAILURE;
	}


    WordRouter wr(dict);
   // строим маршрут
   std::list <string> route;
   int res = wr.CreateRoute(startword,finword,route);
   

    // выводим его на экран
   for (auto it = route.begin(); it !=route.end(); ++it)
    {
        cout << *it << endl;
    }
	
   if (route.empty()) wcout << "В словаре не найдено корректной цепочки между словами"<<endl;

    return res;
}

