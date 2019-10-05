#ifndef IER_LIST
#define IER_LIST

class  IerList;

class  IerList{
	
private:
	bool tag; // true: atom, false: pair
	int  atom;
	IerList  *head;
	IerList  *tail;
	
	void readData( IerList*& listToMerge, std::string str, int& iter);
	void readSequence(IerList*& listToMerge, std::string str, int& iter);
	void printSymbol() const;
	void writeSequence() const;
	
public:

	IerList();
	~IerList();
	
	bool isNull() const;
	
	IerList* getHead() const;
	IerList* getTail() const;
	IerList* getTrueTail() const;
	
	int getAtom() const;
	bool isAtom() const;
	void makeAtom(const int x);
	
	void merge(IerList* head, IerList* tail);

	void readList(IerList*& listForMerge, std::string str);
	void print() const;
	
	bool isBalanceBeam() const;
	int goRoundBalanceBeam(bool isInShoulder) const;
	
};

#endif
