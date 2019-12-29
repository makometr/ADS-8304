#include "tree.h"

/*!
 * @brief Конструктор
 * @details Создаёт словарь <char, std::string>, другими словами алфавит,
 * который будут использовать кодировщик и декодировщик.
 */
Tree::Tree() {
	special_code['a'] = "00000";
	special_code['b'] = "00001";
	special_code['c'] = "00010";
	special_code['d'] = "00011";
	special_code['e'] = "00100";
	special_code['f'] = "00101";
	special_code['g'] = "00110";
	special_code['h'] = "00111";
	special_code['i'] = "01000";
	special_code['j'] = "01001";
	special_code['k'] = "01010";
	special_code['l'] = "01011";
	special_code['m'] = "01100";
	special_code['n'] = "01101";
	special_code['o'] = "01110";
	special_code['p'] = "01111";
	special_code['q'] = "10000";
	special_code['r'] = "10001";
	special_code['s'] = "10010";
	special_code['t'] = "10011";
	special_code['u'] = "1010";
	special_code['v'] = "1011";
	special_code['w'] = "1100";
	special_code['x'] = "1101";
	special_code['y'] = "1110";
	special_code['z'] = "1111";
}

/*!
 * @brief Осуществляет всатвку структуры Node в дерево
 * @details Есть три возможных случая вставки элемента в дерево. Когда дерево полностью пустое,
 * когда дерево не пустое и текущего символа в дереве нет, и когда дерево не пустое и текущий
 * символ в дереве есть.
 * @param symbol очередной символ, который необходимо вставить в структуру дерева с размеченными
 * листьями
 */
void Tree::insert(char symbol) {
    if (root == nullptr) {
        root = std::make_shared<Node>();
        root->left = std::make_shared<Node>();
        root->right = std::make_shared<Node>();
        for_new = std::make_shared<Node>();

        root->parent = nullptr;
        root->weight = 1;
        root->symbol = '\0';

        root->left->parent = root;
        root->left->weight = 0;
        root->left->symbol = '\0';
        for_new = root->left;

        root->right->parent = root;
        root->right->weight = 1;
        root->right->symbol = symbol;
        symbol_ptr[symbol] = root->right;

        code_string += special_code[symbol];
    } else {
    	auto place_to_insert = symbol_ptr.find(symbol);
		if (place_to_insert == symbol_ptr.end()) {
			for_new->left = std::make_shared<Node>();
			for_new->right = std::make_shared<Node>();

			for_new->weight = 1;
			for_new->symbol = '\0';

			for_new->right->parent = for_new;
			for_new->right->weight = 1;
			for_new->right->symbol = symbol;
			symbol_ptr[symbol] = for_new->right;

            code_string += get_path_by_ptr(for_new);
			code_string += special_code[symbol];

			for_new->left->parent = for_new;
			for_new->left->weight = 0;
			for_new->left->symbol = '\0';
			for_new = for_new->left;

			std::shared_ptr<Node> k = for_new->parent->parent;
			while (k != nullptr) {
                k->weight++;
                k = k->parent;
            }
		} else {
			(*place_to_insert).second->weight++;
            std::shared_ptr<Node> k = (*place_to_insert).second->parent;
			while (k != nullptr) {
				k->weight++;
				k = k->parent;
			}
			code_string += get_path_by_ptr((*place_to_insert).second);
		}
    }
}

/*!
 * @brief Возвращает строку-путь до элемента в дереве с поданным в качестве аргумента значением
 * @param ptr указатель на узел, до которого необходимо узнать путь
 * @return строка-путь до переданного элемента
 */
std::string Tree::get_path_by_ptr(std::shared_ptr<Node> ptr) {
    std::string path = {};
    if (ptr != nullptr) {
        while (ptr->parent != nullptr) {
            if (ptr == ptr->parent->right) {
                path = '1' + path;
            } else {
                path = '0' + path;
            }
            ptr = ptr->parent;
        }
    } else {
        return "";
    }
    return path;
}

/*!
 * @brief Генерация последовательности хранения элементов в дереве
 * @details С помощью обхода в ширину (справа налево) генерируем вектор из указателей на элементы
 * в дереве.
 * @return вектор типа std::pair<int, std::shared_ptr<Node>>, где первый элемент это вес, а второй
 * ссылка на этот элемент
 */
std::vector<std::pair<int, std::shared_ptr<Node>>> Tree::get_order() {
    std::shared_ptr<Node> tmp = std::make_shared<Node>();
    std::vector<std::pair<int, std::shared_ptr<Node>>> order;
    std::queue<std::shared_ptr<Node>> q;

    q.push(root);
    while (!q.empty()) {
        tmp = q.front();
        order.emplace_back(std::make_pair(tmp->weight, tmp));
        q.pop();

        if (tmp->right != nullptr) {
            q.push(tmp->right);
        }

        if (tmp->left != nullptr) {
            q.push(tmp->left);
        }
    }
    return order;
}

/*!
 * @brief Проверка на не возрастание полученной последовательности
 * @details Проверяем, существует ли нарушение в нашей последовательности. Все веса должны стоять в
 * порядке невозрастания. Если порядок нарушен, переменным Tree::first и Tree:second присваивается
 * значение указателей на эти переменные.
 * @param order сгенерированный в Tree::get_order() вектор обхода дерева с размеченными листьями
 * @return true если порядок не нарушен, false - в противном случае
 */
bool Tree::check_ascending(std::vector<std::pair<int, std::shared_ptr<Node>>> order) {
    for (int i = 0; i < order.size() - 2; i++) {
        for (int j = i + 1; j < order.size() - 1; j++) {
            if (order[i].first < order[j].first) {
                first = std::make_shared<Node>();
                second = std::make_shared<Node>();
                first = order[i].second;
                second = order[j].second;
                return false;
            }
        }
	}
	return true;
}

/*!
 * @brief Перестроение дерева
 * @details Меняем местами указатели на родителей найденных элементов, а также обновляем указатели
 * на детей этих родителей. Тут же сразу пересчитываем веса, после всех замен.
 */
void Tree::restructure() {
    if (first == first->parent->left) {
        // если а это левый ребёнок
        if (second == second->parent->left) {
            // если b левый ребёнок
            std::swap(first->parent->left, second->parent->left);
        } else {
            // если b - правый
            std::swap(first->parent->left, second->parent->right);
        }
    } else {
        // если а правый ребёнок
        if (second == second->parent->left) {
            // если b - левый ребёнок
            std::swap(first->parent->right, second->parent->left);
        } else {
            // если b - правый ребёнок
            std::swap(first->parent->right, second->parent->right);
        }
    }
    std::swap(first->parent, second->parent);

    while (first->parent != nullptr) {
        first->parent->weight = first->parent->left->weight + first->parent->right->weight;
        first = first->parent;
    }

    while (second->parent != nullptr) {
        second->parent->weight = second->parent->left->weight + second->parent->right->weight;
        second = second->parent;
    }
}

/*!
 * @brief Декодирование данных
 * @details Идея заключается в постепенном построении такого же как и закодированное дерево дерева.
 * Пока закодированная строка не пуста будем сравнивать её начало с путём до листа: в случае, если
 * она не начинается с путя до листа мы идём по новому дереву, постепенно удаляя в закодированной
 * строке символы, пока не встретим элемент со значением символа отличным от \0, иначе ищем эту букву
 * в алфавите, который предоставлен и кодировщику и декодировщику. В любом случае, мы получим букву,
 * которую следует добавить в новое дерево, для кодировщика и повторить итерацию, пока закодированная
 * строка не окажется пустой.
 */
void Tree::decode() {
    Tree decode_tree;
    std::vector<std::pair<int, std::shared_ptr<Node>>> tmp;
    std::string path_to_leaf = {};
    while (!code_string.empty()) {
        path_to_leaf = get_path_by_ptr(decode_tree.for_new);
        if (code_string.find(path_to_leaf) == 0) {
            code_string.erase(0, path_to_leaf.size());
            // начинаем искать букву в словаре
            for (const auto& pair : special_code) {
                if (code_string.find(pair.second) == 0) {
                    decode_string += pair.first;
                    code_string.erase(0, pair.second.size());
                    decode_tree.insert(pair.first);
                    tmp = decode_tree.get_order();
                    break;
                }
            }
        } else {
            // идём по дереву и ищем букву
            std::shared_ptr<Node> tmp_root = decode_tree.root;
            while (tmp_root->symbol == '\0') {
                if (code_string[0] == '0') {
                    tmp_root = tmp_root->left;
                } else {
                    tmp_root = tmp_root->right;
                }
                code_string.erase(0, 1);
            }
            decode_string += tmp_root->symbol;
            decode_tree.insert(tmp_root->symbol);
            tmp = decode_tree.get_order();
        }
        path_to_leaf = get_path_by_ptr(decode_tree.for_new);

        while (!decode_tree.check_ascending(tmp)) {
            decode_tree.restructure();
            tmp = decode_tree.get_order();
        }
    }
}
