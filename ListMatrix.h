#pragma once
#include <list>
using namespace std;
struct xy
{
	int x;
	int y;
};
class ListMatrix
	//special class, stores a matrix, but if 0 it doesnt
	//also uses std::list
{
private:
	struct _ld
	{
		unsigned int x;
		unsigned int y;
		int ld;
	};
	list<_ld> *datas;
	list<int> assignedValues;
	int xmax;
	int ymax;
	int maxsize;
public:
	ListMatrix(int x,int y);
	~ListMatrix();
	int getMaxSize();
	int Size();
	int number();
	//overload [][] operator
	class Proxy {
	private:
		int _localx;
		list<_ld> *localList;
	public:
		Proxy(int _array,list<_ld>*local) : _localx(_array),localList(local){ }
		int operator[](int index) {
			list<_ld>::iterator it = localList->begin();
			do
			{
				if ((it->x == _localx)&&(it->y == index)) return it->ld;
			} while (++it != localList->end());
			if (it == localList->end())return 0;
			else return -1;
		}
	};
	//overload [][] operator
	Proxy operator[](int index) {
		return Proxy(index,datas);
	}
	bool set(int x, int y, int data);
	int get(int x, int y);
	list<int> getAssigned();
	list<xy> find(int assigned);
};

