#include <iostream>
#include <cstring>

//структура для элемента списка
typedef struct list {
	struct list* parent;
	struct list* child;
	struct list* next;
	char elem;
}list;

/*рекурсивная функция создания списка*/
list* createlist(char* str, int* i, list* parent);
//функция удаления заданного элемента из списка
list* CheckAndDelete(list* head, char x);
//функция вывода на экра обработанного списка
void PrintList(list* head);

int main(int argc, char* argv[]) {
	char* str = (char*)calloc(200, sizeof(char)); 
	char c;
	// если не указана папка с тестами, то пользователь вводи строку
	if (argc == 1){ 
		printf("Введите иерархический список: ");
		std::cin >> str;
		std::cout << "Введите эллемент для удаления" << std::endl;
		std::cin >> c;
	}
	else {
		char* path = (char*)calloc(strlen(argv[1]) + 8, sizeof(char)); // строка для открытия файла
		char* estr; // указатель для отслеживания конца файла
		strcat(path, "Tests/");  
		strcat(path, argv[1]); 
		FILE* fileTests = fopen(path, "r"); // открываем файл
		if (!fileTests){ 
			printf("Ошибка открытия файла\n");
			return 0;
		}
		estr = fgets(str, 199, fileTests); // считываем строку из файла
		// если указатель NULL то проверяем на ошибку или конец файла
		if (estr == NULL){ 
			if (feof(fileTests) != 0){
				printf("Конец файла\n");
			}
			else {
				printf("Ошибка чтения файла\n");
			}
		}
		//считываем символ, который необходимо удалить из списка
		c = getc(fileTests);
		free(path);
		fclose(fileTests);
	}
	int i = 0;
	list* Ierlist = createlist(str, &i, NULL);
	Ierlist = CheckAndDelete(Ierlist, c);
	std::cout << "Список после удаления\n";
	PrintList(Ierlist);
	std::cout << std::endl;
	free(str);
	return 0;
}
/*функция принимает указатель на строку, указатель на индекс 
(был выбран во избежание глобальной переменной) 
элемент списка которым были порождены создаваемые*/
list* createlist(char* str, int* i, list* parent) {
	list* head = (list*)malloc(sizeof(list));
	list* cur = head;
	//пока не конец строки обрабатываем её
	while (str[*i] != '\0' && str[*i] != '\n') {
// заходим на уровень ниже, создаём порождаемый список 		
		if (str[*i] == '(') {
			(*i)++;
			cur->child = createlist(str, i, cur);
// для определённости обозначим в "указательном" элементе значение хранящегося символа			
			cur->elem = '\0';
		}
// выходим из данного уровня рекурсии		
		else if (str[*i] == ')') {
			(*i)++;
			cur->next = NULL;
			return head;
		}
// добавляем элемент в список		
		else {
			cur->elem = str[*i];
			cur->child = NULL;
			cur->parent = parent;
			(*i)++;
		}
// доп. проверка для выделения памяти.		
		if (str[*i] != '\0' && str[*i] != ')' && str[*i] != '\n') {
			cur->next = (list*)malloc(sizeof(list));
			cur = cur->next;
		}
	}
// обозначения конца списка		
	cur->next = NULL;
// возвращаем указатель на 1й элемент
	return head;
}

/*функция принимаем указатель на первый элемент в списке,
и символ для удаления*/
list* CheckAndDelete(list* head, char x) {
// вспомогательный указатель	
	list* ptr;
	list* cur = head;
// пока не конец списка	
	while (cur != NULL) {
		if (cur->elem == x) {
// удаления 1го элемента списка			
			if (cur == head) {
				cur = cur->next;
				free(head);
				head = cur;
				continue;
			}
// удаления элемента			
			else {
				ptr = head;
				while (ptr->next != cur) {
					ptr = ptr->next;
				}
				ptr->next = cur->next;
				free(cur);
				cur = ptr;
			}
		}
// если от элемент является "указательным"		
		else if (cur->child != NULL) {
			cur->child = CheckAndDelete(cur->child, x);
		}
		cur = cur->next;
	}
// возвращаем указатель на 1й элемент
	return head;
}

// выводим список
void PrintList(list* head) {
	list* cur = head;
	while (cur != NULL) {
		if (cur->child != NULL) {
			std::cout << '(';
			PrintList(cur->child);
			std::cout << ')';
			cur = cur->next;
		}
		else {
			std::cout << cur->elem;
			cur = cur->next;
		}
	}
}