#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include "binaryTree.h"


int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "RU");
    std::istringstream inputF("(1 (2 ( 4 (5) (6) ) ) ( 3 #( 90 ) ) )");
  //  std::cout << argc << "aaaa\n";
   // if (argc > 1)
   //     inputF.open(argv[1]);
   // else
    //    inputF.open("input.txt");

  //  if (!inputF.is_open()) {
  //      std::cerr << "111Невозможно открыть файл со входными данными";
  //      return 0;
  //  }


  //  std::ofstream outputF("output.txt");
   // if (!outputF.is_open()) {
  //      std::cerr << "2222222Невозможно открыть файл вывода";
   //     return 0;
  //  }

    BinaryTree<int> bt;
    bt.readTree(inputF);

    //BinaryTree<int> bt;
    //bt.setRoot(1);
   // bt.setLeft(2);
   // bt.setRight(3);
   // std::cout << "Root: " << bt.getRoot()<<"\n";
  //  std::cout << "Left: " << bt.getLeftTree().getRoot()<<"\n";
  //  std::cout << "Left left: " << bt.getLeftTree().getLeftTree().getRoot()<<"\n";
  //  std::cout << "Left left left: " << bt.getLeftTree().getLeftTree().getLeftTree().getRoot()<<"\n";
  //  std::cout << "Left left right: " << bt.getLeftTree().getLeftTree().getRightTree().getRoot()<<"\n";
   // std::cout << "Right: " << bt.getRightTree().getRoot()<<"\n";
   // std::cout << "Right right: " << bt.getRightTree().getRightTree().getRoot()<<"\n";
   // bt.getRightTree().setLeft(4);
   // bt.getRightTree().setRight(5);
  //  bt.getLeftTree().setLeft(6);
  //  bt.getLeftTree().getLeftTree().setLeft(7);
    std::cout << bt.calcHeight()<<"\n";
    std::cout << bt.countNodesOnLevel(3) << "\n";
    std::cout<<bt.pathLength()<<"\n";
    bt.printLeaves();
    //bt.printTree();
    //std::cout << "\n";
    //::cout << "1111111122";

    //inputF.close();
  //  outputF.close();

    return 0;
}
