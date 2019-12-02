#include "Tree.h"

int main(int argc, char* argv[]) {
    if(argc <= 2)
    {
        std::cout<<"Не введены аргументы командной строки - название файла для считывания дерева и файла с содержимым, которое нужно удалить из дерева!\n";
        exit(1);
    }
    else
    {
        std::unique_ptr<BinaryTree<double>> tree(new BinaryTree<double>());
        std::ifstream inputFile(argv[1]);
        std::ifstream inputToDeleteFile(argv[2]);
        if (!inputFile.is_open())
        {
            std::cout << "ERROR: file isn't open" << std::endl;
            return 0;
        }
        if (!inputToDeleteFile.is_open())
        {
            std::cout << "ERROR: file isn't open" << std::endl;
            return 0;
        }
        if (inputFile.eof())
        {
            std::cout << "ERROR: file is empty" << std::endl;
            return 0;
        }
        tree->makeFromFile(inputFile, tree);
        inputFile.close();
        
        std::ofstream outputFile1("ReadTree.txt");
        tree->WriteToFile(outputFile1, tree);
        outputFile1.close();

        double elem;
        int s =0;
        while (inputToDeleteFile >> elem) tree->SearchAndDelete(s, elem, tree); 
        
        std::ofstream outputFile2("TreeAfterDelete.txt");
        tree->WriteToFile(outputFile2, tree);
        outputFile2.close();

        return 0;
    }
}
