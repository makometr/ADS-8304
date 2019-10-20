#ifndef IER_LIST
#define IER_LIST

class  IerList;
enum class balanceBeamStatuses {noErrors, noShoulder, noLength, excessValues, noMass};

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

	IerList():tag(false), head(nullptr), tail(nullptr) {}
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
	balanceBeamStatuses goRoundBalanceBeam(bool isInShoulder) const;
	
};

#endif
