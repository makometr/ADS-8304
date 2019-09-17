#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SIZE 1000

using namespace std;

int GetRoot(int x, int* sets)  //для нахождения представителя, подняться вверх по родительским ссылкам до тех пор, пока не наткнемся на корень
//для каждой вершины по пути от X к корню изменим предка на этого самого представителя
{
	return (sets[x] == x) ? x : sets[x] = GetRoot(sets[x], sets);
}

void UnionBranch(int x, int y, int* sets, int* ranks)
{
    if ( (x = GetRoot(x, sets)) == (y = GetRoot(y, sets)) )
        return;

    if ( ranks[x] < ranks[y] )  //подвешиваем более низкое дерево к более высокому
        sets[x] = y;
    else
    {
        sets[y] = x;
        if ( ranks[x] == ranks[y] )
            ranks[x]++;
    }
}


int GetManID(string name, string* people, int peopleCount)
{
	for (int i = 0; i < peopleCount; i++)
		if (people[i] == name)
			return i;
	//в цикле по people сравниваем name c people[i]. если равно, то возвращаем i
}

void ReadAndWritePeople(string* people, int* parents, int* children, int* peopleCount, int* relationsCount)
{
	// в цикле считываем строки
	string str;
	ifstream file("relations.txt", ios::in);
	while(!file.eof())
	{
		getline(file, str);
		char* cstr = new char[str.length()+1];
		strcpy(cstr, str.c_str());
		char* name = new char[20];
		name = strtok (cstr, " "); 

		int flagChild = 0;
 		string parentName;
 		int parentID;

		// ищем имена в people[]
		// если имени нет - добавить

		while (name != NULL)                 
		{
			int flag = 1;
			for(int i = 0; i < *peopleCount; i++){
				if(strcmp(name, people[i].c_str()) == 0) { flag = 0;	break; }
			}
			if(flag){
				people[*peopleCount] = name;
				(*peopleCount)++;
			}

			if(flagChild){      // если считали второе и последующие имена в строке, то добавляем отношение 
				parents[*relationsCount] = parentID;   //(индекс первого имени в строке - индекс считанного имени)
				children[*relationsCount] = GetManID(name, people, *peopleCount);
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
	
	cout << "\nСписок всех жителей:\n" << endl;
	for (int i = 0; i < *peopleCount; i++){
        cout << i << " " << people[i] << "\n" << endl;
    }
    
    cout << "\nТаблица отношений в индексах жителей:\n" << endl;
	for (int i = 0; i < *relationsCount; i++){
        cout << parents[i] << " " << children[i] << "\n" << endl;
    }
	
}

void PrintAllRelatives(string* people, int* peopleSets, int peopleCount)
{
	cout << "\nРезультат работы алгоритма поиска непересекающихся множеств:\n" << endl;
	
	for (int i = 0; i < peopleCount; i++)
        cout << peopleSets[i] << " " + people[i] << endl;
        
	cout << "\nВсе пары родственников:\n" << endl;
	
	for (int i = 0; i < peopleCount-1; i++)
	{
		for (int j = i+1; j < peopleCount; j++)
		{
			if (peopleSets[i] == peopleSets[j])
				cout << people[i] + " - " + people[j] << endl;
		}
	}
	
}

int main()
{
	string* people = new string[SIZE]; //список всех имен
	
	int* peopleSets = new int[SIZE];  //массив, хранящий для каждой вершины дерева её непосредственного предка
	int* peopleSetsRanks = new int[SIZE];  // для каждого дерева будет храниться верхняя граница его высоты

	int* parents = new int[SIZE];   //индексы имен из people в двух массивах показывают родство
	int* children = new int[SIZE];
	int peopleCount = 0;  //количество жителей
	int relationsCount = 0;  //количество связей

	ReadAndWritePeople(people, parents, children, &peopleCount, &relationsCount);  //считывание имен и заполнение связей родства

    for (int i = 0; i < relationsCount; i++)  //для каждого элемента X, создать множество размера 1 из самого себя.
    {
        peopleSets[i] = i;
        peopleSetsRanks[i] = 0;
    }

	for (int i = 0; i < relationsCount; i++)  //объединить два множества, в которых лежат элементы X и Y, в одно новое
	{
		UnionBranch(parents[i], children[i], peopleSets, peopleSetsRanks);
    }
    for (int i = 0; i < relationsCount; i++) //возвратить идентификатор множества, которому принадлежит элемент X
	{
		peopleSets[i] = GetRoot(i, peopleSets);
    }

	PrintAllRelatives(people, peopleSets, peopleCount); //печать пар родственников

	return 0;
}

