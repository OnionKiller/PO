#include "stdafx.h"
#include "ListMatrix.h"


ListMatrix::ListMatrix(int x, int y)
{
	datas = new list<_ld>;
	maxsize = x*y*3;
}

ListMatrix::~ListMatrix()
{
	free(datas);
}

int ListMatrix::getMaxSize()
{
	return maxsize;
}

int ListMatrix::Size()
{
	if (datas == nullptr)return 0;
	return datas->size()*3+3;
}

int ListMatrix::number()
{
	return datas->size();
}

bool ListMatrix::set(int x, int y, int data)
{
	if (data == 0)return false;
	auto it = datas->begin();
	_ld tmp;
	tmp.x = x; tmp.y = y; tmp.ld = data;
	if (it == datas->end()) { datas->push_back(tmp); return true; assignedValues.push_back(data); }
	do
	{
		if ((it->x == x)&&(it->y == y)) { it->ld = data; return true; }
	} while (++it != datas->end());
	datas->push_back(tmp);
	assignedValues.push_back(data);
	return true;
}

int ListMatrix::get(int x, int y)
{
	list<_ld>::iterator it = datas->begin();
	if (it == datas->end())return 0;
	do
	{
		if ((it->x == x) && (it->y == y)) return it->ld;
	} while (++it != datas->end());
	if (it == datas->end())return 0;
	else return -1;
}

list<int> ListMatrix::getAssigned()
{
	return assignedValues;
}

list<xy> ListMatrix::find(int assigned)
{
	list<xy> ltmp;
	xy tmp;
	auto it = datas->begin();
	do
	{
		if (it->ld == assigned)
		{
			tmp.x = it->x;
			tmp.y = it->y;
			ltmp.push_back(tmp);
		}
	} while (++it != datas->end());
	return ltmp;
}
