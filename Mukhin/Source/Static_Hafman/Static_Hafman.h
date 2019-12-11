#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

/*!
 * @brief Функция запускающая процедуру статического кодирования и декодирования
 * @param argс количество аргументов командной строки
 * @param argv массив имён этих элементов
 * @return 0, если всё хорошо, иначе быть не может
 */
int use_static(int argc, char* argv[]);