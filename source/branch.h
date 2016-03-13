// Author: Roman Pavlukhin

#ifndef BRANCH_H
#define BRANCH_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <list>
#include <queue>
#include <fstream>


/**
 * @brief Класс для хранения ветвей (истории изменения слова)
 * В данном классе при помощи list<string> реализовано хранения истории
 * преобразования слова из стартового в текущее.
 */
class Branch{
 public:
    /**
     * @brief Применяется для создания новой, чистой ветви. Используется лишь однажды - для создания главной, родительской ветви.
     * @param[in] startName - первое слово в ветви.
     */
    Branch(std::string startName);
    /**
     * Применяется для создания нового ответвления, в которое заносится история изменений слова из класса
     * \param[in] br - Ссылка на класс, из которого должна быть скопирована история изменений слова.
     */
    Branch(const Branch & br);

    /**
     * \brief Возвращает последнее(текущее) полученное слово в ветви
     */
    std::string getHead();

    /**
     * @brief Получаем историю всех изменений в текущей ветви
     * @return Возвращает ссылку на list<string> со всеми изменениями от начального до текущего.
     */
    std::list<std::string> & getHistory();

    /**
     * @brief AddtoHistory добавляет новое слово в историю изменений ветви.
     * @param str - слово, которое необходимо добавить.
     */
    int AddToHistory(std::string& str);

    /**
     * @brief isUsed устанавливает, есть ли в истории изменений данной ветви указанное слово.
     * @param str - слово для поиска
     * @return true - если уже использовалось, false - еще нет
     */
    bool isUsed(std::string &str);

private:
    std::list<std::string> _history;
};

#endif // BRANCH_H
