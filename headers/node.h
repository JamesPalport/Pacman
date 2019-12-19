#ifndef NODE_H
#define NODE_H

#include <vector>
#include <QPoint>
using namespace std;

class Node
{
private:
	int		m_x;
	int		m_y;
	int		m_value;
	int		m_dist;
	int		m_cost;
	bool		m_visited;
	int		m_size[2];
	vector<Node *>	*m_neighbours;
	vector<Node *>	*m_map;

public:
	Node(int x, int y, int value, Node *dest);
	~Node();
	int		distance(int x, int y);
	void		calcCost();
	void		setValue(int value);
	void		setNeighbours();
	void		setMap(vector<Node *> *map, int *size);
	int		Value()		{return (m_value);}
	int		Cost()		{return (m_cost);}
	vector<Node *>	*Neihbours()	{m_visited = true;
									 return (m_neighbours);}
	bool	Visited()	{return (m_visited);}
	int		X()			{return (m_x);}
	int		Y()			{return (m_y);}
};

int				*reach(QPoint *posIni, QPoint *dest,
					   int **matrice, int *size);
#endif // NODE_H
