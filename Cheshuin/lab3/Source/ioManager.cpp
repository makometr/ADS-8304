#include "ioManager.h"

IoManager::IoManager(int argc, char** argv)
{
    argc_ = argc;
    argv_ = argv;

    if(argc_ < 2)
    {
        curInStream_ = &std::cin;
        curOutStream_ = &std::cout;
    }
}

void IoManager::openNextStream()
{
    if(curInStream_ == nullptr){
        curInStream_ = new std::ifstream();
        curOutStream_ = new std::ofstream();
    }

    if(curArgNum_ >= argc_)
    {
        if(curInStream_ != &std::cin)
        {
            delete curInStream_;
            delete curOutStream_;
        }

        curInStream_ = nullptr;
        curOutStream_ = nullptr;

        return;
    }

    std::ifstream* inFileStream = static_cast<std::ifstream*>(curInStream_);
    if(inFileStream->is_open())
    {
        inFileStream->close();
    }
    std::ofstream* outFileStream = static_cast<std::ofstream*>(curOutStream_);
    if(outFileStream->is_open())
    {
        outFileStream->close();
    }

    while(curArgNum_ < argc_ && !inFileStream->is_open())
    {
        std::cout << "Try to open file - ";
        std::cout << argv_[curArgNum_] << std::endl;

        inFileStream->open(argv_[curArgNum_]);

        if(inFileStream->is_open())
        {
            std::string outFile(argv_[curArgNum_]);
            outFile += " - results";
            outFileStream->open(outFile);

            std::cout << "File opened." << std::endl << std::endl;
        }
        else
        {
            std::cout << "Can't open - file not founded" << std::endl << std::endl;
        }

        curArgNum_ += 1;
    }
}

std::istream* IoManager::nextStream()
{
    if(curInStream_ == nullptr)
    {
        openNextStream();

        if(curInStream_ == nullptr)
        {
            return nullptr;
        }
    }

    while(curInStream_->peek() == EOF)
    {
        openNextStream();

        if(curInStream_ == nullptr)
        {
            return nullptr;
        }
    }

    std::string buffer;

    std::getline(*curInStream_, buffer);
    if(buffer == "")
    {
        return nullptr;
    }

    std::stringstream* sstream = new std::stringstream();
    *sstream << buffer;

    return sstream;
}

void IoManager::writeLine(std::string line)
{
    *curOutStream_ << line << std::endl;
}

IoManager::~IoManager()
{
    if(curInStream_ != nullptr && curInStream_ != &std::cin)
    {
        delete  curInStream_;
        delete  curOutStream_;
    }
}
