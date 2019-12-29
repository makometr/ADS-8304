#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cctype>


int GetRoot(int x, std::vector<int>* sets)  //для нахождения представителя, подняться вверх по родительским ссылкам до тех пор, пока не наткнемся на корень
//для каждой вершины по пути от X к корню изменим предка на этого самого представителя
{
	return ((*sets)[x] == x) ? x : (*sets)[x] = GetRoot((*sets)[x], sets);
}

void UnionBranch(int x, int y, std::vector<int>* sets, std::vector<int>* ranks)
{
    if ( (x = GetRoot(x, sets)) == (y = GetRoot(y, sets)) )
        return;

    if ( (*ranks)[x] < (*ranks)[y] )  //подвешиваем более низкое дерево к более высокому
        (*sets)[x] = y;
    else
    {
        (*sets)[y] = x;
        if ( (*ranks)[x] == (*ranks)[y] )
            (*ranks)[x]++;
    }
}


int GetManID(std::string name, std::vector<std::string>* people, int peopleCount)
{
	for (int i = 0; i < peopleCount; i++)
		if ((*people)[i] == name)
			return i;
	//в цикле по people сравниваем name c people[i]. если равно, то возвращаем i
}

unsigned char IsStringOK(char* str){
	unsigned char i = 0;
	for(i = 0; i<strlen(str); i++){
		if(!isalpha(str[i])) return 0;
	}
	return 1;
}

void ReadAndWritePeople(std::vector<std::string>* people, std::vector<int>* parents, std::vector<int>* children, int* peopleCount, int* relationsCount)
{
	// в цикле считываем строки
	std::string str;
	std::ifstream file("relations.txt", std::ios::in);
	while(!file.eof())
	{
		std::getline(file, str);
		char* cstr = new char[str.length()+1];
		strcpy(cstr, str.c_str());
		char* name = new char[20];
		name = strtok (cstr, " ");

		int flagChild = 0;
 		std::string parentName;
 		int parentID;

		// ищем имена в people[]
		// если имени нет - добавить

		while ((name != NULL) && (IsStringOK(name)))
		{
			int flag = 1;
			for(int i = 0; i < *peopleCount; i++){
				if(strcmp(name, (*people)[i].c_str()) == 0) { flag = 0;	break; }
			}
			if(flag){
				people->push_back(name);
				//people[*peopleCount] = name;
				(*peopleCount)++;
			}

			if(flagChild){      // если считали второе и последующие имена в строке, то добавляем отношение
				parents->push_back(parentID);   //(индекс первого имени в строке - индекс считанного имени)
				children->push_back(GetManID(name, people, *peopleCount));
				(*relationsCount)++;
			}
			else
			{
				parentName = name;
				parentID = GetManID(parentName, people, *peopleCount);  //функция поиска индекса имени в массиве имен
			}

			name = new char[20];
			name = strtok (NULL, " ");
			flagChild = 1;
		}
	}

	std::cout << "\nСписок всех жителей:" << std::endl;
	for (int i = 0; i < *peopleCount; i++){
        std::cout << i << " " << (*people)[i] << std::endl;
    }

    std::cout << "\nТаблица отношений в индексах жителей:" << std::endl;
	for (int i = 0; i < *relationsCount; i++){
        std::cout << (*parents)[i] << " " << (*children)[i] << std::endl;
    }

}

void PrintAllRelatives(std::vector<std::string>* people, std::vector<int>* peopleSets, int peopleCount)
{
	std::cout << "\nРезультат работы алгоритма поиска непересекающихся множеств:" << std::endl;

	for (int i = 0; i < peopleCount; i++)
        std::cout << (*peopleSets)[i] << " " + (*people)[i] << std::endl;

	std::cout << "\nВсе пары родственников:" << std::endl;

	for (int i = 0; i < peopleCount-1; i++)
	{
		for (int j = i+1; j < peopleCount; j++)
		{
			if ((*peopleSets)[i] == (*peopleSets)[j])
				std::cout << (*people)[i] + " - " + (*people)[j] << std::endl;
		}
	}

}

int main()
{
	//string* people = new string[SIZE]; //список всех имен

	std::vector<std::string> people;

	std::vector<int> peopleSets;  //массив, хранящий для каждой вершины дерева её непосредственного предка
	std::vector<int> peopleSetsRanks;  // для каждого дерева будет храниться верхняя граница его высоты

	std::vector<int> parents;   //индексы имен из people в двух массивах показывают родство
	std::vector<int> children;
	int peopleCount = 0;  //количество жителей
	int relationsCount = 0;  //количество связей

	ReadAndWritePeople(&people, &parents, &children, &peopleCount, &relationsCount);  //считывание имен и заполнение связей родства

    for (int i = 0; i < peopleCount; i++)  //для каждого элемента X, создать множество размера 1 из самого себя.
    {
        peopleSets.push_back(i);
        peopleSetsRanks.push_back(0);
    }

	for (int i = 0; i < relationsCount; i++)  //объединить два множества, в которых лежат элементы X и Y, в одно новое
	{
		UnionBranch(parents[i], children[i], &peopleSets, &peopleSetsRanks);
    }
    for (int i = 0; i < peopleCount; i++) //возвратить идентификатор множества, которому принадлежит элемент X (обновляем)
	{
		peopleSets[i] = GetRoot(i, &peopleSets);
    }

	PrintAllRelatives(&people, &peopleSets, peopleCount); //печать пар родственников

	return 0;
}

