#include "node.h"
#include <QPoint>
#include	 <vector>
#include <iostream>

using namespace std;

static Node	*minNode(vector<Node *> *map)
{
	Node		*min = nullptr;
	vector<Node *>::iterator	it;

	for (it = map->begin(); it != map->end(); it++)
	{
		if (*it != nullptr && !(*it)->Visited() && (*it)->Value() != -1
			&& (min == nullptr || min->Cost() > (*it)->Cost()
				|| (min->Cost() == (*it)->Cost()
					&& min->Value() > (*it)->Value())))
			min = (*it);
	}
	return (min);
}

static Node	*minValue(Node *n)
{
	Node				*min = nullptr;
	vector<Node *>	*neighs = n->Neihbours();
	vector<Node *>::iterator	it;

	for (it = neighs->begin(); it != neighs->end(); it++)
	{
		if ((*it) != nullptr && (*it)->Visited()
			&& (min == nullptr || min->Value() > (*it)->Value()))
			min = *it;
	}
	return (min);
}

void			dispMat(int **map, int *size)
{
	cout << "matrice" << endl;
	for (int j(0); j < size[1]; j++)
	{
		for (int i(0); i < size[0]; i++)
			cout << " " << map[j][i];
		cout << endl;
	}
}

void			dispMap(vector<Node *> *map, int *size)
{
	vector<Node *>::iterator	it;
	int							count(0);

	cout << "map" << endl;
	for (it = map->begin(); it != map->end(); it++)
	{
		count++;
		if (*it == nullptr)
			cout << " 1";
		else if ((*it)->Visited())
			cout << " v";
		else
			cout << " 0";
		if (count == size[0])
		{
			count = 0;
			cout << endl;
		}
	}
}

void		deleteMap(vector<Node *> map, int *size)
{
	for (int i(0); i < size[0] * size[1]; i++)
		delete map[static_cast<size_t>(i)];
}

int			*reach(QPoint *posIni, QPoint *dest, int **matrice, int *size)
{
	Node			*end = new	Node(dest->x(), dest->y(), -1, nullptr);
	Node			*start = new Node(posIni->x(), posIni->y(), 0, end);
	Node			*min = nullptr;
	vector<Node *>	map(static_cast<size_t>(size[0] * size[1]));
	vector<Node *>	*Neighbours = nullptr;
	vector<Node *>::iterator	it;

	if (posIni->x() == dest->x() && posIni->y() == dest->y())
		return (nullptr);
	for (int j(0); j < size[1]; j++)
	{
		for (int i(0); i < size[0]; i++)
		{
			if (matrice[j][i] != 1)
			{
				if (static_cast<int>(i) == posIni->x()
					&& static_cast<int>(j) == posIni->y())
					map[static_cast<size_t>(j * size[0] + i)] = start;
				else if (static_cast<int>(i) == dest->x()
						 && static_cast<int>(j) == dest->y())
					map[static_cast<size_t>(j * size[0] + i)] = end;
				else
					map[static_cast<size_t>(j * size[0] + i)] =
							new Node(static_cast<int>(i),
									 static_cast<int>(j), -1, end);
				map[static_cast<size_t>(j * size[0] + i)]->setMap(&map, size);
			}
		}
	}
	for_each(map.begin(), map.end(), [](Node *n){if (n) n->setNeighbours();});
	start->setValue(0);
	min = minNode(&map);
	while (end->Value() == -1 && min != nullptr)
	{
		Neighbours = min->Neihbours();
		for (it = Neighbours->begin(); it != Neighbours->end(); it++)
		{
			if ((*it) != nullptr
				&& (*it)->Visited() && (*it)->Value() > min->Value() + 1)
				(*it)->setValue(min->Value() + 1);
			else if ((*it) != nullptr && !(*it)->Visited())
				(*it)->setValue(min->Value() + 1);
		}
		min = minNode(&map);
	}
	if (end->Value() > 0)
	{
		min = minValue(end);
		Node		*prev = end;
		while (min != nullptr && min != start)
		{
			prev = min;
			min = minValue(prev);
		}
		int	*vect = new int[2]();
		vect[0] = -start->X() + prev->X();
		vect[1] = -start->Y() + prev->Y();
		deleteMap(map, size);
		return (vect);
	}
	deleteMap(map, size);
	return (nullptr);
}
