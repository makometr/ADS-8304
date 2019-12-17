#include "idealTree.h"
#include "randomTree.h"
#include <ctime>


int main(int argc, char* argv[]) {


    if(argc == 1)
    {
        std::cout<<"Не введен аргумент командной строки - название файла\n";
        exit(1);
    }
    else
    {
        std::unique_ptr<IdealBinaryTree<double>> idealTree(new IdealBinaryTree<double>());
        std::unique_ptr<RandomBinaryTree<double>> randTree(new RandomBinaryTree<double>());
        std::unique_ptr<RandomBinaryTree<double>> badTree(new RandomBinaryTree<double>());
        std::ifstream inputFile(argv[1]);

        std::cout << "For file: " << argv[1] << std::endl;
        if (!inputFile.is_open())
        {
            std::cout << "ERROR: file isn't open" << std::endl;
            return 0;
        }
        if (inputFile.eof())
        {
            std::cout << "ERROR: file is empty" << std::endl;
            return 0;
        }

        long searchCount = atoi(argv[2]);


        randTree->makeFromFile(inputFile, randTree);
        std::vector<double> vect;
        randTree->WriteToVector(vect, randTree);
        idealTree->makeFromVector(vect, idealTree);
        if(atoi(argv[3])) randTree->makeFromVector(vect, badTree);
        inputFile.close();


        double elem; //генерируем много элем
        long steps1 = 0;
        long steps2 = 0;
        long steps3 = 0;
        long i = 0;
        srand(time(0));

        unsigned long start_time = clock();

        while (i++ < searchCount){
            elem = rand();
            randTree->Search(elem, steps1, randTree);
        }
        unsigned long second_time  = clock();
        unsigned long time1  = (second_time - start_time)/searchCount;
        i = 0;
        while (i++ < searchCount){
            elem = rand();
            idealTree->Search(elem, steps2, idealTree);
        }
        unsigned long third_time  = clock();
        unsigned long time2  = (third_time - second_time)/searchCount;
        unsigned long time3;
        if(atoi(argv[3])){
            i = 0;
            while (i++ < searchCount){
                elem = rand();
                randTree->Search(elem, steps3, badTree);
            }
            unsigned long end_time  = clock();
            time3  = (end_time - third_time)/searchCount;
        }

        std::cout << "Высота случайного дерева:                              " << randTree->GetDepth(randTree) << std::endl;
        std::cout << "Высота идеального дерева:                              " << idealTree->GetDepth(idealTree) << std::endl;
        if(atoi(argv[3])) std::cout << "Высота дерева в худшем случае (кол-во):                " << randTree->GetDepth(badTree) << std::endl;
        if(!atoi(argv[3])) std::cout << "Количество элементов:                                  " << vect.size() << std::endl;
        std::cout << "Среднее кол-во сравнений в случайном дереве:           " << (float)steps1/searchCount << std::endl;
        std::cout << "Среднее кол-во сравнений в идеальном дереве:           " << (float)steps2/searchCount << std::endl;
        if(atoi(argv[3])) std::cout << "Среднее кол-во сравнений в худшем случае:              " << (float)steps3/searchCount << std::endl;
        std::cout << "Среднее время поиска элемента в случайном дереве:      " << (float)time1 / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
        std::cout << "Среднее время поиска элемента в идеальном  дереве:     " << (float)time2 / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
        if(atoi(argv[3])) std::cout << "Среднее время поиска элемента в худшем случае (сл.д.): " << (float)time3 / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

        return 0;
    }
}


