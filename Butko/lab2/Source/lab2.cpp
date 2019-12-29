#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct BinaryScales {
    BinaryScales(int atomNumber_, int atomLeftNumber_, int atomRightNumber_, int atomArmLength_, int atomKey_) :
            atomNumber(atomNumber_), atomLeftNumber(atomLeftNumber_), atomRightNumber(atomRightNumber_), atomArmLength(atomArmLength_), atomKey(atomKey_),
            isBalanced(true), isChecked(false), prevAtom(nullptr), leftAtom(nullptr), rightAtom(nullptr){};
    int atomNumber,
        atomRightNumber,
        atomLeftNumber,
        atomArmLength,
        atomKey;
    bool isBalanced, isChecked;
   BinaryScales *prevAtom, *leftAtom, *rightAtom;
};

bool balance(BinaryScales *&binaryScales) {
    if (binaryScales->leftAtom->leftAtom != nullptr && !binaryScales->leftAtom->isChecked) {
        binaryScales =  binaryScales->leftAtom;
        balance(binaryScales);
    }
    else if (binaryScales->rightAtom->rightAtom != nullptr && !binaryScales->rightAtom->isChecked) {
        binaryScales = binaryScales->rightAtom;
        balance(binaryScales);
    }
    else{
        binaryScales->leftAtom->isChecked = binaryScales->rightAtom->isChecked = true;
        int torqueLeft = binaryScales->leftAtom->atomArmLength * binaryScales->leftAtom->atomKey;
        int torqueRight = binaryScales->rightAtom->atomArmLength * binaryScales->rightAtom->atomKey;
        binaryScales->atomKey = binaryScales->leftAtom->atomKey + binaryScales->rightAtom->atomKey;
        binaryScales->isBalanced = torqueLeft == torqueRight && binaryScales->rightAtom->isBalanced && binaryScales->leftAtom->isBalanced;
        binaryScales->isChecked = true;
        if (binaryScales->atomNumber == 0 && binaryScales->leftAtom->isChecked && binaryScales->rightAtom->isChecked) return binaryScales->isBalanced;
        binaryScales = binaryScales->prevAtom;
        balance(binaryScales);
    }
}

auto backToZeroAtom(BinaryScales *&binaryScales){
    if (binaryScales->atomNumber == 0) return binaryScales;
    else {
        binaryScales = binaryScales->prevAtom;
        backToZeroAtom(binaryScales);
    }
}

int printDepth(BinaryScales *&binaryScales, int i){
    if(binaryScales->leftAtom == nullptr && binaryScales->rightAtom == nullptr){
        for(int j=0;j<i;j++) std::cout <<"-";
        std::cout<<binaryScales->atomNumber<<std::endl;
        return 0;
    }
    for(int j=0;j<i;j++) std::cout <<"-";
    std::cout<<binaryScales->atomNumber<<std::endl;
    i++;
    printDepth(binaryScales->leftAtom, i);
    printDepth(binaryScales->rightAtom, i);
}

int deleteAtoms(BinaryScales *&binaryScales){
    if(binaryScales->leftAtom == nullptr && binaryScales->rightAtom == nullptr) {
        delete binaryScales;
        return 0;
    }
    deleteAtoms(binaryScales->leftAtom);
    deleteAtoms(binaryScales->rightAtom);
    delete binaryScales;
}

int addAtom(int atomNumber, int atomLeftNumber, int atomRightNumber, int atomArmLenght, int atomKey,  BinaryScales *&binaryScales) {
    auto *tmpBinaryScales = new BinaryScales{atomNumber, atomLeftNumber, atomRightNumber, atomArmLenght, atomKey};
    if (binaryScales->atomLeftNumber == tmpBinaryScales->atomNumber) {
        tmpBinaryScales->prevAtom = binaryScales;
        std::cout << "pointer left" << std::endl;
        std::cout << "pointer on atom # " << tmpBinaryScales->atomNumber << std::endl;
        std::cout << std::endl;
        binaryScales->leftAtom = tmpBinaryScales;
        binaryScales = binaryScales->leftAtom;
        return 0;
    }
    else if (binaryScales->atomRightNumber == tmpBinaryScales->atomNumber) {
        tmpBinaryScales->prevAtom = binaryScales;
        std::cout << "pointer right" << std::endl;
        std::cout << "pointer on atom # " << tmpBinaryScales->atomNumber << std::endl;
        std::cout << std::endl;
        binaryScales->rightAtom = tmpBinaryScales;
        binaryScales = binaryScales->rightAtom;
        return 0;
    }
    else {
        binaryScales = binaryScales->prevAtom;
        if (binaryScales->prevAtom == nullptr && (binaryScales->atomLeftNumber != tmpBinaryScales->atomNumber && binaryScales->atomRightNumber != tmpBinaryScales->atomNumber)){
            std::cout << "error: incorrect data order" << std::endl;
            return 1;
        }
        std::cout << "pointer back" << std::endl;
        std::cout << "pointer on atom # " << binaryScales->atomNumber << std::endl;
        std::cout << std::endl;
        addAtom(atomNumber, atomLeftNumber, atomRightNumber, atomArmLenght, atomKey, binaryScales);
    }
    return 0;
}

bool checkAtomData(std::vector<int>& dataAtom){
    std::cout << dataAtom[0] << std::endl;
    bool check = true;
    if (dataAtom[0] != 0 && dataAtom.size() == 3) {
        std::cout << "error: wrong zero atom data" << std::endl;
        check = false;
    }
    else if (dataAtom.size()!= 3 && dataAtom.size()!=5){
        std::cout << "error: incomplete data" << std::endl;
        check = false;
    }
    else if ((dataAtom[1] == 0 && dataAtom[2] != 0) || (dataAtom[2] == 0 && dataAtom[1] != 0)) {
        std::cout << "error: breaking ties" << std::endl;
        check = false;
    }
    else if (dataAtom[1] == 0 && dataAtom[2] == 0 &&  dataAtom[4] <= 0 && dataAtom[0] != 0) {
        std::cout << "error: zero load weight" << std::endl;
        check = false;
    }
    else if (dataAtom[3] <= 0 && dataAtom[0] != 0) {
        std::cout << "error: zero arm length" << std::endl;
        check = false;
    }
    return check;
}

int main() {
    std::string testFileName, resultFileName, line, number;
    std::cout << " Enter test-file location: " << std::endl;
    std::cin >> testFileName;
    std::ifstream testFile;
    testFile.open(testFileName);
    if (!testFile.is_open()) {
        std::cout << "error: test file is not open" << std::endl;
        return 0;
    }
    std::cout << " Enter where to save results (location with <name>.txt): " << std::endl;
    std::cin >> resultFileName;
    std::ofstream resultFile(resultFileName);
    if (!resultFile.is_open()) {
        std::cout << "error: result file is not open" << std::endl;
        return 0;
    }
    int lineCounter = 0;
    while (!testFile.eof()) {
        getline(testFile, line);
        lineCounter ++;
    }
    if ((lineCounter - 1) % 2 != 0) {
        std::cout << "error: wrong hierarchical list!" << std::endl;
        return 0;
    }
    testFile.close();
    testFile.open(testFileName);
    getline(testFile, line);
    std::istringstream issZero(line);
    std::vector<int> dataAtomZero;
    dataAtomZero.clear();
    while (issZero >> number)
        dataAtomZero.push_back(std::stoi(number));
    if (!checkAtomData(dataAtomZero)) return 0;
    auto *binaryScales = new BinaryScales{dataAtomZero[0], dataAtomZero[1], dataAtomZero[2], 0, 0};
    while (!testFile.eof()) {
        getline(testFile, line);
        std::istringstream iss(line);
        std::vector<int> dataAtom;
        while (iss >> number)
            dataAtom.push_back(std::stoi(number));
        if (!checkAtomData(dataAtom)) return 0;
        else {
            addAtom(dataAtom[0], dataAtom[1], dataAtom[2], dataAtom[3], dataAtom[4], binaryScales);
         }
        resultFile << line << std::endl;
    }
    backToZeroAtom(binaryScales);
    if (balance(binaryScales)){
        std::cout << "balanced" << std::endl;
        resultFile << "balanced" << std::endl;
    }
    else{
        std::cout << "not balanced" << std::endl;
        resultFile << "not balanced" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "depth of atoms" << std::endl;
    printDepth(binaryScales, 0);
    backToZeroAtom(binaryScales);
    deleteAtoms(binaryScales);
    resultFile.close();
    return 0;
}