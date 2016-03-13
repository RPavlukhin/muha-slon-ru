#include "wordrouter.h"


WordRouter::WordRouter(set<string> & dict)
{
    initDictionary(dict);
}


int WordRouter::initDictionary(set<string> & dict)
{
        dictOrigin_ = dict;

    return dict.size();
}


 // Предикат, устанавливающий, отличается ли первое слово от второго лишь на один символ.
bool WordRouter::isDiffOneLetter(string  firstWord, string  secondWord)
{
    //Проверяем, что оба слова одинаковой длины
    if (firstWord.length()==secondWord.length())
    {
        //Каждый символ из первого слова сравниваем с соотвествующим ему из второго слова.
        int pos = 0;
        int ndiff = 0;
		for (auto i = firstWord.begin(); i!=firstWord.end(); ++i)
        {
            if ((*i)!=secondWord[pos])
            {
                ndiff++;
            }
            if (ndiff>1) return false;
            pos++;
        }
        if (ndiff==1) return true; // возвращаем true лишь при одном и только одном отличии.
    }
    return false;
}

// Находит в словаре все слова, отличающиеся от заданного лишь на 1 символ.
std::set <string> WordRouter::FindAllVariants(std::string word)
{
    std::set<string> results;

    //Заносим в массив srerults все слова, отличающиеся на 1 символ.
    std::set<string>::iterator it = results.begin();
    copy_if(dictTemp_.begin(),dictTemp_.end(), std::inserter(results,it),[word](const string & elem) {return isDiffOneLetter(word,elem);});

    return results;
}

// Получает из множества слов новое множество со словами лишь заданной длины.
std::set <string> WordRouter::DictWithSameSize(std::set <string> & dictOrigin, const unsigned int len){

    std::set <string> s;

    std::set<string>::iterator it = s.begin();
    // Копируем во временный словарь лишь элементы с длиной, равной len
    std::copy_if(dictOrigin.begin(),dictOrigin.end(),std::inserter(s,it),[len](string str){return str.length()==len;} );
    return s;
}


// Функция для создания новых версий слова.
std::vector<Branch> WordRouter::Mutate( Branch & inbranch)
{
    std::vector<Branch> brs; // вектор для хранения полученных новых ветвей

    // находим все варианты изменений текущего слова
    std::set<string> allvar = FindAllVariants(inbranch.getHead());


    //Обходим все полученные варианты
	std::string str_tmp;
	for (auto it = allvar.begin(); it != allvar.end(); ++it)
    {
       //Проверяем, что слово еще не использовалось
		str_tmp = (*it);
		if (!inbranch.isUsed(str_tmp))
       {
          //создаем новую ветвь
          Branch tmp(inbranch);
          //добавляем в "голову" истории изменений новой ветви это слово
          tmp.AddToHistory(str_tmp);
          // добавляем новую ветвь в вектор
          brs.push_back(tmp);
       }
    }
    return brs;
}

// CreateRoute создает оптимальный маршрут изменений слова от одного заданного до другого.
int WordRouter::CreateRoute(set<string> & originDict, string stword, string fword, std::list<string> & words)
{
    // заносим из оригинального словаря во временное множество dictTemp_ все слова с длиной как у stword (чтобы не перебирать все)
    if (originDict.empty()) return -2; // исходный словарь пуст.
    dictTemp_.clear();
    dictTemp_ = DictWithSameSize(originDict,stword.length());
    if (dictTemp_.empty()) return -3; // в словаре нет слов с такой же длиной.
    if (stword.empty()||fword.empty()) return -4; // начальное и/или конечное слово не указано


    std::queue <Branch> mainquery; // Очередь, в которой хранятся все еще не обработанные ветви
    //Создаем самую первую ветку и заносим ее в очередь на обработку
    Branch tmpbranch(stword);
    mainquery.push(tmpbranch);

    // Пока не обработали все элементы в очереди, последовательно создаем из них новые ветки.
    while (!mainquery.empty())
       {
          // берем первый элемент из очереди и проверяем, не является ли она искомым словом
          tmpbranch = mainquery.front();
          if (tmpbranch.getHead()== fword){
             words = tmpbranch.getHistory(); // возвращаем историю
             return EXIT_SUCCESS;
            }
          /// Ищем для текущего слова возможные мутации, добавляем их в конец очереди, а первый элемент из очереди удаляем.
          vector<Branch> tmp = Mutate(tmpbranch);
          std::for_each(tmp.begin(),tmp.end(),[&mainquery](const Branch & elem){ mainquery.push(elem); } );
          mainquery.pop();

       }

    return -1;
}

// Обертка для CreateRoute без обязательного указания словаря (используется ссылка dictOrigin_)
int WordRouter::CreateRoute(string stword, string fword, std::list<string> & words)
{
    return CreateRoute(this->dictOrigin_,stword,fword,words);
}
