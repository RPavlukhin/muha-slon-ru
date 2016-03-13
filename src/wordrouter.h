#ifndef WORDROUTER_H
#define WORDROUTER_H

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

using namespace std;

class WordRouter
{
public:

    /**
     * @brief WordRouter
     * @param dict
     */
    WordRouter(set<string> & dict);

    /**
     * @brief Предикат, устанавливающий, отличается ли первое слово от второго лишь на один символ.
     * @param firstWord - первое слово для сравнения
     * @param secondWord - второе слово для сравнения
     * @return true - если слова отличаются лишь на один символ и их длина одинакова, в остальных случаях false.
     */
    static bool isDiffOneLetter(string  firstWord, string  secondWord);

    /**
     * @brief Cоздает оптимальный маршрут изменений слова от одного заданного до другого.
     * @param originDict[in] - ????
     * @param stword[in] - слово, из которого начинается преобразование
     * @param fword[in] - слово, в которое необходимо преобразовать stword
     * @param words[out] - ????
     * @return Возвращает список преобразований от stword к fword включая их самих.
     */
    int CreateRoute(set<string> &originDict, string stword, string fword, std::list<string> & words);

    /**
     * @brief  обертка для CreateRoute, использующая приватный член originDict_
     * @param stword
     * @param fword
     * @param words
     * @return
     */
    int CreateRoute(string stword, string fword, std::list<string> & words);

    /**
     * @brief initDictionary Устанавливает, какой словарь необходимо использовать
     * @param dict - ссылка на множество
     * @return
     */
    int initDictionary(set<string> & dict);

private:
    /**
     * \brief FindAllVariants Находит в словаре все слова, отличающиеся от заданного лишь на 1 символ.
     * \param word - слово, относительно которого совершается поиск
     * \return множество полученных слов.
     */
    std::set <string> FindAllVariants(std::string word);

    /**
     * @brief DictWithSameSize Получает из множества слов новое множество со словами лишь заданной длины.
     * @param dictOrigin[in] - ссылка на множество слов
     * @param len[in] - необходимая длина слова
     * @return
     */
    std::set <string> DictWithSameSize(std::set <string> & dictOrigin, const unsigned int len);

    /**
     * \brief Mutate - функция для создания новых версий слова.
     * Для слова, которое находится в "голове" ветви, т.е. являющегося текущим, мы находим все возможные мутации.
     * При этом проверяется, что новая версия слова не использовалась ранее (чтобы не допустить закольцовывания).
     * \return возвращает вектор новых ветвей, полученных из текущей ветви.
     */
    std::vector<Branch> Mutate(Branch & inbranch);

    /**
     * @brief dictTemp_ - временное множество. В него вносятся лишь слова, равные по длине стартовому в цепочке.
     */
    set <string> dictTemp_;

    /**
     * @brief dictOrigin_ - ссылка на первоначальное множество, содержащее все слова.
     */
    set <string> dictOrigin_;

};

#endif // WORDROUTER_H
