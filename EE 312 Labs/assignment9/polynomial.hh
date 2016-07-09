class Node{
	
public:
	double value;
	Node* next;
    Node();
	Node(double v, Node* n);

};

class Poly{
private:
    Node* head;
    Node* temp;
    
public:
	Node* getHead();
	Poly();
    Poly(const Poly &obj);
    ~Poly();
    Poly& operator= (const Poly&);
	void print();
	void append(double v);
    int getListLength();
    void clear();
    void removeFromHead();
};
