#include<iostream>
#include<time.h>
using std:: cout;
using std:: cin;
using std:: endl;

#define tab "\t"
//#define DEBUG
#define delimeter "\n--------------------------------------------------\n\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element() 
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;

public:
	Element* GetRoot()const{return Root;}
	Tree() :Root(nullptr) 
	{
#ifdef DEBUG
		cout << "TConstructor:\t" << this << endl;
#endif // DEBUG
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)insert(*it, Root);
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
#ifdef DEBUG
		cout << "TDestructor:\t" << this << endl;
#endif // DEBUG
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data) { insert(Data, Root); }
	void erase(int Data) { erase(Data, Root); }
	int minValue()const { return minValue(Root); }
	int maxValue()const { return maxValue(Root); }
	int sum()const { return sum(Root); }
	int count()const { return count(Root); }
	int depth()const { return depth(Root); }
	void print()const
	{
		print(Root);
		cout << endl;
	}
	double avg()const
	{
		if (count(this->Root) == 0) return 0.0;
		return (double)sum(this->Root) / count(this->Root);
	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root -> pLeft);
		erase(Data, Root -> pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return maxValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		return !Root ? 0 : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root) const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	int sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int depth(Element* Root)const
	{
		return
			!Root ? 0 :
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 :
			depth(Root->pRight) + 1;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void clear(Element*& Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if(Data>Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data){insert(Data, Root);}
};

template<typename T>void measure_performanse(const char message[], T(Tree::*function)()const, const Tree& tree)
{
	clock_t start = clock();
	T result = (tree.*function)();
	clock_t end = clock();
	cout << message << result << ", finish in a " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
}

//#define BASE_CHECK
//#define ERASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter to size tree: "; cin >> n;
	Tree tree;
	cout << "min: " << tree.minValue() << endl;
	cout << "max: " << tree.maxValue() << endl;
	cout << "count: " << tree.count() << endl;

	cout << delimeter;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "min: " << tree.minValue() << endl;
	cout << "max: " << tree.maxValue() << endl;
	cout << "count: " << tree.count() << endl;
	cout << "sum: " << tree.sum() << endl;
	cout << "avg: " << tree.avg() << endl;

	cout << delimeter;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "min: " << u_tree.minValue() << endl;
	cout << "max: " << u_tree.maxValue() << endl;
	cout << "count: " << u_tree.count() << endl;
	cout << "sum: " << u_tree.sum() << endl;
	cout << "avg: " << u_tree.avg() << endl;
#endif // BASE_CHECK

#ifdef ERASE_CHECK
	Tree tree =
	{
						50,

				25,				75,

			16,		32,	   	58,		85 , 91,98
	};
	tree.print();

	int value;
	//cout << "Go to delete element: "; cin >> value;
	//tree.erase(value);
	tree.print();
	cout << "depth: " << tree.depth() << endl;
#endif // ERASE_CHECK

	int n;
	cout << "Enter to size tree: "; cin >> n;
	Tree tree;
	//cout << "min: " << tree.minValue() << endl;
	//cout << "max: " << tree.maxValue() << endl;
	//cout << "count: " << tree.count() << endl;

	cout << delimeter;

	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	/*tree.print();
	cout << "min: " << tree.minValue() << endl;
	cout << "max: " << tree.maxValue() << endl;
	cout << "count: " << tree.count() << endl;
	cout << "sum: " << tree.sum() << endl;
	cout << "avg: " << tree.avg() << endl;
	cout << "depth: " << tree.depth() << endl;*/

	measure_performanse("min value in tree: ", &Tree::minValue, tree);
	measure_performanse("max value in tree: ", &Tree::maxValue, tree);
	measure_performanse("sum in tree: ", &Tree::sum, tree);
	measure_performanse("count in tree: ", &Tree::count, tree);
	measure_performanse("avg in tree: ", &Tree::avg, tree);
	
}