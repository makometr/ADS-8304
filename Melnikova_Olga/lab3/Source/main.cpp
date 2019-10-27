#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <regex.h>
#include "Queue.cpp"

#define SIZE 1000

unsigned char IsStringOK(char* str){
	unsigned char i = 0;
	for(i = 0; i<strlen(str); i++){
		if(!isalpha(str[i])) return 0;
	}
	return 1;
}

int GetManID(std::string name, std::vector<std::string>* people, int peopleCount)
{
	for (int i = 0; i < peopleCount; i++)
		if ((*people)[i] == name)
			return i;
	//в цикле по people сравниваем name c people[i]. если равно, то возвращаем i
	return -1;
}

void ConsoleReadAndWritePeople(std::vector<std::string>* people, std::vector<int>* parents, std::vector<int>* children, int* peopleCount, int* relationsCount, Queue* queue)
{
	// в цикле считываем строки
	std::cout<<"Введите пары родственников, для завершения\n";
	std::string str;

	while(str!="-")
	{
		getline(std::cin, str, '\n');
		if(str=="-") continue;
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
	std::cout<<"Введите имя, для которого совершать поиск";
	std::string name1;
	std::cin>>name1;  // если не удалось - выход
	queue->push(GetManID(name1, people, *peopleCount));
	if(GetManID(name1, people, *peopleCount)==-1) exit;

}

void ReadAndWritePeople(std::vector<std::string>* people, std::vector<int>* parents, std::vector<int>* children, int* peopleCount, int* relationsCount, Queue* queue, char* argv1)
{
	// в цикле считываем строки
	std::ifstream fin;
	std::string str;
	regex_t regex;
	int reti1;
	reti1 = regcomp(&regex, ".\\.txt", 0);
	reti1 = regexec(&regex, argv1, 0, NULL, 0);
	if (!reti1){
		fin.open(argv1);
	}else{
			std::cout<<"Некорректные названия файла (расширение txt)"<<std::endl;
			exit(0);
	}
	while(str!="-")
	{
		getline(fin, str);
		if(str==""){
       		 exit(1);
		}
		if(str=="-") continue;
		char* cstr = new char[str.length()+1];
		strcpy(cstr, str.c_str());
		char* name = new char[20];
		name = strtok (cstr, " ");

		int flagChild = 0;
 		std::string parentName;
 		int parentID;

		// ищем имена в people[]
		// если имени нет - добавить

		while ((name != NULL) && (IsStringOK(name)) && (flagChild<2))
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
			flagChild++;
		}
	}
	std::string name1;
	getline(fin, name1);  // если не удалось - выход
	queue->push(GetManID(name1, people, *peopleCount));
	if(GetManID(name1, people, *peopleCount)==-1) exit;

}


int func1(std::vector<std::string> people, std::vector<int> parents, std::vector<int> children, int relationsCount, std::ofstream& fout, Queue* prev_queue, int k){

	Queue *queue = new Queue;
	for(int i = 0; i<(prev_queue->size()); i++){
		for(int j = 0; j<relationsCount; j++){
			if((prev_queue->get_elem(i))==parents[j]){
				queue->push(children[j]);
			}
		}
	}
	//если  massive пуст, то return 0;
	if(queue->isEmpty()){
        fout<<"";
        return 0;
    }

	if(k==0) fout<<"\nДети:"<<std::endl;
	else if(k==1) fout<<"\nВнуки:"<<std::endl;
	else{
		fout<<"\nПра";
		for(int a=0; a<k-2; a++){
			fout<<"пра";
		}
		fout<<"внуки:"<<std::endl;
	}
	for(int s=0; s<(queue->size()); s++){
		fout<<people[queue->get_elem(s)]<<std::endl;
	}
	k++;
	func1(people, parents, children, relationsCount, fout, queue, k);
}


int main(int argc, char *argv[])
{
    int flag=1;
	std::vector<std::string> people;
	Queue *queue = new Queue;
	std::vector<int> parents;   //индексы имен из people в двух массивах показывают родство
	std::vector<int> children;
	int peopleCount = 0;  //количество жителей
	int relationsCount = 0;  //количество связей


	if(argv[1]!=NULL){
		ReadAndWritePeople(&people, &parents, &children, &peopleCount, &relationsCount, queue, argv[1]);
	}else{
		std::cout<<"\nВы не ввели или ввели неправильно аргумент командной строки.\nПервый аргумент командной строки - файл с расширением txt, из которого считывается список.\nДля продолжения введите 1, иначе 0."<<std::endl;

		std::cin>>flag;
		if(flag==0) return 0;

		ConsoleReadAndWritePeople(&people, &parents, &children, &peopleCount, &relationsCount, queue);
	}

	std::ofstream fout("result.txt", std::ios::out);
	if(parents.empty()){
        fout<<"";
        return 0;
    }
	func1(people, parents, children, relationsCount, fout, queue, 0);


	return 0;
}

