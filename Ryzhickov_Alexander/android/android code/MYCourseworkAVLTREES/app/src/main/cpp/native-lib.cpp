#include <jni.h>
#include <string>

const int right_overweight = 2;
const int left_overweight = -2;

struct Node // структура для представления узлов дерева
{
    int key;
    unsigned char height;
    Node *left;
    Node *right;

    Node(int k) {
        key = k;
        left = right = 0;
        height = 1;
    }
};

unsigned char height(Node *p) {
    return p ? p->height : 0;
}

int bFactor(Node *p) {
    return height(p->right) - height(p->left);
}

void fixHeight(Node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

Node *rotateRight(Node *p) // правый поворот вокруг p
{
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

Node *rotateLeft(Node *q) // левый поворот вокруг q
{
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

Node *balance(Node *p) // балансировка узла p
{
    fixHeight(p);
    if (bFactor(p) == right_overweight) {
        if (bFactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bFactor(p) == left_overweight) {
        if (bFactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // балансировка не нужна
}

Node *insert(Node *p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new Node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

Node *findMin(Node *p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? findMin(p->left) : p;
}

Node *removeMin(Node *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

Node *remove(Node *p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
        Node *q = p->left;
        Node *r = p->right;
        delete p;
        if (!r) return q;
        Node *min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void deleteTree(Node *p) {
    if (p->left) {
        deleteTree(p->left);
    }
    if (p->right) {
        deleteTree(p->right);
    }
    delete p;
}

int random(int min, int max) {
    return min + rand() % (max - min);
}


void createRandomArray(int *arrayNumbers, int *arrayOptions, int sizeArray) {
    for (int j = 0; j < sizeArray; ++j) {

        if (arrayNumbers[arrayOptions[j] - 1] != 0) {
            arrayNumbers[arrayOptions[j] - 1] = 0;
        } else {
            int min = 0;
            for (int i = 0; i < sizeArray; ++i) {
                if (arrayNumbers[i] != 0) {
                    min = arrayNumbers[i];
                    break;
                }
            }

            arrayOptions[j] = min;
            arrayNumbers[min - 1] = 0;

        }
    }
}

std::string createString(Node *p) {
    std::string myString;
    myString += "(";
    myString +=std::to_string(p->key);
    if (p->left) {
        myString += createString(p->left);
    }
    if (p->right) {
        myString += createString(p->right);
    }
    myString += ")";
    return myString;
}

std::string createVariant(int complexity) {
    int sizeArray = 0;
    int countDeleteElements = 0;
    std::string myTree;

    if (complexity == 1) {
        sizeArray = 5;
        countDeleteElements = 1;
    }
    if (complexity == 2) {
        sizeArray = 10;
        countDeleteElements = 2;
    }
    if (complexity == 3) {
        sizeArray = 15;
        countDeleteElements = 3;
    }

    int *arrayNumbers = new int[sizeArray];
    int *arrayOptions = new int[sizeArray];
    int *arrayDeleteElements = new int[countDeleteElements];


    for (int i = 0; i < sizeArray; ++i) {
        arrayNumbers[i] = i + 1;
        arrayOptions[i] = random(1, sizeArray + 1);
    }

    createRandomArray(arrayNumbers, arrayOptions, sizeArray);

    for (int i = 0; i < countDeleteElements; ++i) {
        arrayDeleteElements[i] = arrayOptions[i];
        arrayDeleteElements[i] = arrayOptions[arrayDeleteElements[i] - 1];
    }

    auto *avlTree = new Node(arrayOptions[0]);
    for (int j = 1; j < sizeArray; ++j) {
        avlTree = insert(avlTree, arrayOptions[j]);
    }

    for (int k = 0; k < countDeleteElements; ++k) {
        avlTree = remove(avlTree, arrayDeleteElements[k]);
    }

    for (int i = 0; i < sizeArray; ++i) {
        myTree+=std::to_string(arrayOptions[i]);
        if(i!=sizeArray-1){
            myTree+=",";
        }
    }

    myTree+=";";

    for (int i = 0; i < countDeleteElements; ++i) {
        myTree+=std::to_string(arrayDeleteElements[i]);
        if(i!=countDeleteElements-1){
            myTree+=",";
        }
    }

    myTree+=";";

    myTree += createString(avlTree);

    if (avlTree != 0) {
        deleteTree(avlTree);
    }
    delete[] arrayNumbers;
    delete[] arrayOptions;
    delete[] arrayDeleteElements;

    return myTree;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_artex_mycourseworkavltrees_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    //std::string hello = "Hello from C++";
    std::string hello = createVariant(3);
    return env->NewStringUTF(hello.c_str());
}

int hello() {
    createVariant(3);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_artex_mycourseworkavltrees_MainActivity_stringFromJNI2(
        JNIEnv *env,
        jobject /* this */
) {
    int a = 1;
    int b = 2;
    int c = hello();
    return c;
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_artex_mycourseworkavltrees_MainActivity_stringFromJNI3
        (JNIEnv *env, jobject obj, jint complexity)
{
    std::string hello;
    switch (complexity){
        case 1:
            hello = "1";
            break;
        case 2:
            hello = "2";
            break;
        case 3:
            hello = "3";
            break;
        default:
            hello = "0";
            break;
    }
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_artex_mycourseworkavltrees_StudentActivity_createSimpleVariant(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = createVariant(1);
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_artex_mycourseworkavltrees_StudentActivity_createMediumVariant(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = createVariant(2);
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_artex_mycourseworkavltrees_StudentActivity_createHighVariant(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = createVariant(3);
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_artex_mycourseworkavltrees_MainActivity_addArray
        (JNIEnv *env, jclass type, jintArray jarr) {

    jint *arr = env->GetIntArrayElements(jarr, NULL);
    int res=0;
    int size = env->GetArrayLength(jarr);
    for(int i=0;i<size;i++)
        res+=arr[i];

    env->ReleaseIntArrayElements(jarr, arr, 0);
    return res;
}