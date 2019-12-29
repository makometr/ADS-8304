#include "tree.hpp"

MyBinaryTree::MyBinaryTree(){
    rootPointer = std::make_shared<Node>();
}

bool MyBinaryTree::startTree(std::string const& inputString){
    
    if(isCorrectStr(inputString)){
        construcTree(inputString, rootPointer);
        return true;
    }
    return false;
}

bool MyBinaryTree::construcTree(std::string const& inputString,std::shared_ptr<Node>& rootPointer){
    // the first character is ' ( ' , there is no need to consider it
    size_t stringIndex = 1;

    std::string rootStringValue;
    while (stringIndex < inputString.size() && (inputString[stringIndex] != '(' && inputString[stringIndex] != ')'))
    {
        rootStringValue += inputString[stringIndex];
        stringIndex++;
    }
    if (rootStringValue.empty())
        return false;

    rootPointer->data = stoi(rootStringValue);
    
    //if the end of the line is encountered, the left and right subtree = empty
    if (inputString[stringIndex] == ')')
        return true;

    rootPointer->left  = std::make_shared<Node>();
    std::string bracketsValue = subString(inputString, &stringIndex);

    bool formLeftResult = construcTree(bracketsValue, rootPointer->left);
    if (!formLeftResult)
        return false;

    //if the end of the line is encountered, the right subtree = empty
    if (inputString[stringIndex] == ')')
        return true;
 

    rootPointer->right = std::make_shared<Node>();
    bracketsValue = subString(inputString, &stringIndex);

    bool formRightResult = construcTree(bracketsValue, rootPointer->right);
    if (!formRightResult)
        return false;

    //check for correctness of end symbols
    if (inputString[stringIndex] != ')' || stringIndex + 1 != inputString.size())
        return false;

    return true;
}

std::string MyBinaryTree::subString(std::string const& indexString, size_t* stringIndexPointer){
    size_t tmp_ind = *stringIndexPointer;
    int error = 0;
    std::string bracketsValue;

    while (1)
    {
        //write the next character
        bracketsValue += indexString[tmp_ind];
        tmp_ind++;

        if (indexString[tmp_ind] == '(')
            error++;
        if (indexString[tmp_ind] == ')')
            error--;
        if (error < 0)
            break;
    }

    //write )
    bracketsValue += indexString[tmp_ind];
    //shift index for the expression in parentheses to read the second argument
    *stringIndexPointer = tmp_ind + 1;
    return bracketsValue;
}

bool MyBinaryTree::isBalanceBracket(std::string const& str){
    size_t openBracketCnt = 0;
    size_t closeBracketCnt = 0;

    for (char symb : str){
        if (symb == '(')
            openBracketCnt++;

        if (symb == ')')
            closeBracketCnt++;

        if (closeBracketCnt > openBracketCnt)
            return false;
    }
    
    return closeBracketCnt == openBracketCnt;
}

bool MyBinaryTree::isCorrectStr(std::string const& str){
       
//   Checking the input string (tree in a simplified bracket representation) for correctness
      
    if(!isBalanceBracket(str))
    {
        std::cout << "Brackets of the tree is not balanced!\n";
        return false;
        
    }

       bool isElem = false;
       bool flagIsCorrect = true;
       if (str[0] != '(') {
           std::cout << "Bracket representation of Binary Tree must start and end with brackets!\n";
           return false;
       }
       if (str[str.length() - 1] != ')') {
          std::cout << "Bracket representation of Binary Tree must start and end with brackets!\n";
           return false;
       }
    
       size_t indexStart;
       size_t numBrackets = 0;
       for (indexStart = 1; indexStart < str.length() - 1; indexStart++) {
           
           if (str[indexStart] != ' ' && str[indexStart] != '(' && str[indexStart] != ')') {
               if (!isElem) {
                   while (str[indexStart] != '(' && str[indexStart] != ')') {
                       if(!isdigit(str[indexStart])){
                           std::cout << "Only Numbers are allowed!\n";
                           return false;
                       }
                       indexStart++;
                   }
                   isElem = true;
               }
           }

           if (str[indexStart] == '(') {
               if (!isElem) {
                   std::cout << "No element was added as root!\n";
                   return false;
               }
               numBrackets++;
               if (numBrackets > 2) {
                   std::cout << "More than 2 branches!\n";
                   return false;
               }
               size_t indexEnd = indexStart;
               int openB = 1;
               int closeB = 0;
               while (openB > closeB) {
                   indexEnd++;
                   if (indexEnd >= str.length()) {
                       std::cout << "Incorrect input!\n";
                       return false;
                   }
                   if (str[indexEnd] == '(') {
                       openB++;
                   }
                   else if (str[indexEnd] == ')') {
                       closeB++;
                   }
               }
                flagIsCorrect = flagIsCorrect && isCorrectStr(str.substr(indexStart, indexEnd - indexStart + 1));
                indexStart = indexEnd;
           }
       }

       if (str[indexStart] == ')') {
           if (!isElem) {
               std::cout<< "No element was added as root!\n";
               return false;
           }
           if (indexStart == str.length() - 1) {
               return flagIsCorrect;
           }
           else {
               std::cout << "Incorrect input!\n";
               return false;
           }
       }
       
       return true;
}
