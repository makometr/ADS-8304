#include "btree.h"

using namespace std;

void generateArr(vector<int> &nodes){

	int n = 1 + rand()%20;

	for (int i = 0; i < n; i++){

		int node = 1 + rand()%100;
		nodes.push_back(node);

	}
			
}

void tasksGenerating(std::ofstream &file, std::ofstream &answ, BinTreeSearch MyBinTree, int &i){
	
	vector<int> arr;
	generateArr(arr);
	
	file << i << ")Дан дискретный набор узлов БДП: ";
	
	for (auto k: arr) {
	
			file << k << ' ';
			MyBinTree = randInsert(MyBinTree, k);

	}

	file << "\nИзображение рандомизированного БДП:\n";
	display(MyBinTree, 1, file);
	
	int n = rand()%100;
	for( auto m: arr){
			if( m == n) 
				n = rand()%100;
	}
				
	file << "\n\nЗадание: вставка с рандомизацией узла с весом " << n;
	float sized = arr.size();
	float chance = 1/ (sized + 1);
	file << "\nУкажите вероятность, с которой выполнится вставка в корень. Напишите скобочное представление БДП с этом случае.";
	answ << chance << endl; 
	MyBinTree = insertroot(MyBinTree, n);
	printKLP(answ, MyBinTree);

	MyBinTree = remove(MyBinTree, n);
	chance = 1 - chance;
	file << "\nУкажите вероятность, с которой выполнится рекурсивная вставка в одно из поддерьвев. Напишите скобочное представление БДП с этом случае.";
	answ << "\n" << chance << endl;
	MyBinTree = simpleInsert(MyBinTree, n);
	printKLP(answ, MyBinTree);
	answ << std::endl;
	
	file << "\n\n\n";
	arr.clear();
	
		
}

int main(int argc, char* argv[]){

	srand(time(0));

	std::ofstream file;
	file. open(argv[1], std::ios::app);
	if(!file.is_open()){return 0;}

	std::ofstream answ;
	answ. open(argv[2],  std::ios::app);
	if(!answ.is_open()){return 0;}

	for (int i = 1; i < 4; i++){

		BinTreeSearch MyBinTree = nullptr;
		tasksGenerating(file, answ, MyBinTree, i);
		destroy(MyBinTree);
	}
	
	answ.close();
	file.close();

	
	cout << "Введите свою фамилию\n";
	string surname;
	getline(cin, surname);
	std::ofstream testfile;
	testfile. open(surname + ".txt", std::ios::app);
	testfile.close();

	cout << "\n Задания сгенерированы. Для прохождения ТК перейдите в файл " << surname + ".txt" << ", введите ответы построчно и нажмите \"Сохранить\".\n Для проверки введите любой символ и нажмите enter.";
	char a;
	cin >> a;
	if (a){
	
		std::ifstream test(surname + ".txt");
		std::ifstream ans(argv[2]);

		std::string s1;
		int correct = 0;
		while (std::getline(ans,s1)){

			std::string s2;
			getline(test, s2);
			if (s1 == s2) correct++;	
		
		}
	
		std::ofstream result;
		result.open("rating.txt", std::ios::app);
	
		result <<  surname << ":" << correct << "\\12\n";

		result.close();
		test.close();
		ans.close();

	}
	return 0;
}
