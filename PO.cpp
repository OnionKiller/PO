// PO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ListMatrix.h"
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <array>

#define MaxTmpMem 100000
#define MaxConflict 64
#define delimiter ','


ListMatrix *connections = new ListMatrix(9, 5);
ListMatrix *blocks = new ListMatrix(9, 5);
int loadDataMatrix(string source, ListMatrix *data,int maxx,int maxy);
float h(xy s, xy goal);
list<xy> createRoute(list<xy> startend, ListMatrix *tabou);

int main()
{
	string input = "C:\\Users\\tomi\\Desktop\\datamatrix";
	string input2 = "C:\\Users\\tomi\\Desktop\\blockmatrix";
	cout << loadDataMatrix(input, connections,9,5) <<","<< loadDataMatrix(input2, blocks,9,5) << endl;
	list<xy> tmp;
	list<int> conn = connections->getAssigned();
	for each (int i in conn)
	{
		tmp = connections->find(i);
		if (tmp.size() < 2)continue;
		else if (tmp.size() == 2)
		{
			list<xy> route = createRoute(tmp, blocks);
		}
		else
		{

		}
	}
	cin >> input;
	if (input == "\n")cin >> input;
    return 0;
}


int loadDataMatrix(string source, ListMatrix *data, int maxx, int maxy)
{
	int currentPosX, currentPosY;
	ifstream file;
	string tmp;
	file.open(source, ios::in);
	currentPosX = 0;
	currentPosY = 0;
	//currentLintNumber = 0;
	while (!file.eof())
	{
		file >> tmp;
		int pos = 0;
		currentPosY = 0;
		do
		{
			string subtmp;
			pos += tmp.substr(pos + 1).find(delimiter) + 1;
			subtmp = tmp.substr(pos - 1, 1);

			int tmpnumb = stoi(subtmp);
			//int tmpnumb = 0;
			if (tmpnumb != 0)
			{
				data->set(currentPosX, currentPosY, tmpnumb);
			}
			currentPosY++;
		} while (tmp.substr(pos + 1).find(delimiter) != -1);
		int tmpnumb = stoi(tmp.substr(pos + 1));
		//int tmpnumb = 0;
		if (tmpnumb != 0)
		{
			data->set(currentPosX, currentPosY, tmpnumb);
		}
		currentPosX++;
	}
	//clearup sequence
	file.close();
	//delete[] tmpData;

	return data->number();
}
list<xy> createRoute(list<xy> startend,ListMatrix *tabou)
{
	if (startend.size() > 2)return list<xy>();
	auto it= startend.begin();
	xy start = *it;
	it++;
	xy end = *it;
	xy local = start;
	//xy stepback;
	list<xy> tmplist;
	ListMatrix *localtabou = new ListMatrix(255, 255);
	localtabou->set(start.x, start.y, 1);
	bool alternative = false;

	while (true)
	{
		tmplist.push_back(local);
		if (local.x == end.x&&local.y == end.y) break;
		list<xy> *poptions = new list<xy>();
		list<xy> options;
		bool ok = false;
		xy t;
		//up
		t.x = local.x;
		t.y = local.y + 1;
		
		if (tabou->get(t.x, t.y) == 0 && (t.x >= 0) && (t.y >= 0)) {
			if (t.x == end.x&&t.y == end.y) { tmplist.push_back(t); break; }
			//if in conn, also tabou
			if (connections->get(t.x, t.y) == 0)options.push_back(t);
		}
		//left
		t.x = local.x - 1;
		t.y = local.y;
		if (tabou->get(t.x, t.y) == 0 && (t.x >= 0) && (t.y >= 0)) {
			if (t.x == end.x&&t.y == end.y) { tmplist.push_back(t); break; }
			//if in conn, also tabou
			if (connections->get(t.x, t.y) == 0)options.push_back(t);
		}
		//down
		t.x = local.x;
		t.y = local.y - 1;
		if (tabou->get(t.x, t.y) == 0 && (t.x >= 0) && (t.y >= 0)) {
			if (t.x == end.x&&t.y == end.y) { tmplist.push_back(t); break; }
			//if in conn, also tabou
			if (connections->get(t.x, t.y) == 0)options.push_back(t);
		}
		//right
		t.x = local.x + 1;
		t.y = local.y;
		if (tabou->get(t.x, t.y) == 0 && (t.x >= 0) && (t.y >= 0)) {
			if (t.x == end.x&&t.y == end.y) { tmplist.push_back(t); break; }
			//if in conn, also tabou
			if (connections->get(t.x, t.y) == 0)options.push_back(t);
		}
		//sumup
		//I know, kill me for this
		options.sort([end](const xy &A, const xy &B) {return h(A, end) > h(B, end); });
		//options ascending in h
		auto opIt = options.begin();
		while (opIt!=options.end())
		{
			if (h(*opIt, end) < h(local, end)) 
			{
				if (localtabou->get(opIt->x, opIt->y) == 0)
				{
					//ok, és optimális
					//eredeti hely tabu
					localtabou->set(local.x, local.y, 1);
					//új hely berak
					local = *opIt;
					ok = true;
					break;
				}
			}
			opIt++;
		}
		if (!ok)
		{
			opIt = options.begin();
			while (opIt != options.end())
			{
				if (localtabou->get(opIt->x, opIt->y) == 0)
				{
						//ok, nem optimális
						localtabou->set(local.x, local.y, 1);
						local = *opIt;
						ok = true;
						alternative = false;
				}
				opIt++;
			}
			if (!ok)
			{
				//locked
				localtabou->set(local.x, local.y, 1);
				//tmplist.pop_back();
				tmplist.pop_back();
				auto tit = tmplist.end();
				local = *(--tmplist.end());
			}
		}
	}
	return tmplist;
}
float h(xy s, xy goal)
{
	return sqrt(pow((goal.x - s.x),2) + pow((goal.y - s.y),2));
};
list<xy> options(xy local)
{

}