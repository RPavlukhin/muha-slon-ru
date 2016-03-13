#include "branch.h"

using namespace std;

    // Применяется для создания новой, чистой ветви. Используется лишь однажды - для создания главной, родительской ветви..
    Branch::Branch(std::string startName)
    {
        _history.push_back(startName);
    }


    // Применяется для создания нового ответвления, в которое заносится история изменений слова из класса
    Branch::Branch(const Branch & br)
    {
        _history = br._history;
    }

    // Возвращает последнее(текущее) полученное слово в ветви
    std::string Branch::getHead()
    {
        return _history.back();
    }

    // Получаем историю всех изменений в текущей ветви
    std::list<string> & Branch::getHistory()
    {
        return _history;
    }


    // добавляет новое слово в историю изменений ветви.
    int Branch::AddToHistory(string& str)
    {
     _history.push_back(str);
        return 0;
    }

    // isUsed устанавливает, есть ли в истории изменений данной ветви указанное слово.
    bool Branch::isUsed(string &str)
    {
        list <string> * hlist = &getHistory();
        return ( std::find (hlist->begin(),hlist->end(),str) != hlist->end() );
    }
