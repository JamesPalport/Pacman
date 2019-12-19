#include "node.h"

Node::Node(int x, int y, int value, Node *dest)
{
	m_x = x;
	m_y = y;
	m_value = value;
	if (dest != nullptr)
		m_dist = distance(dest->m_x, dest->m_y);
	else
		m_dist = 0;
	calcCost();
	m_visited = false;
	m_neighbours = new vector<Node *>();
}

Node::~Node()
{
	delete m_neighbours;
}

int		Node::distance(int x, int y)
{
	int	dx = x - m_x;
	int	dy = y - m_y;

	dx = dx > 0? dx: -dx;
	dy = dy > 0? dy: -dy;
	return (dx + dy);
}

void		Node::calcCost()
{
	m_cost = m_value + m_dist;
}

void		Node::setValue(int value)
{
	m_value = value;
	calcCost();
}

void		Node::setMap(vector<Node *> *map, int *size)
{
	m_map = map;
	m_size[0] = static_cast<int>(size[0]);
	m_size[1] = static_cast<int>(size[1]);
}
#include <iostream>
void		Node::setNeighbours()
{
	if (m_x - 1 >= 0)
		m_neighbours->push_back(m_map->at(static_cast<size_t>
										  (m_y * m_size[0] + m_x - 1)));
	else
		m_neighbours->push_back(m_map->at(static_cast<size_t>
										  (m_y * m_size[0] + m_size[0] - 1)));
	if (m_x + 1 < m_size[0])
		m_neighbours->push_back(m_map->at(static_cast<size_t>
										  (m_y * m_size[0] + m_x + 1)));
	else
		m_neighbours->push_back(m_map->at(static_cast<size_t>
										  (m_y * m_size[0]/* + 0*/)));
	if (m_y - 1 >= 0)
		m_neighbours->push_back(m_map->at(static_cast<size_t>
										  ((m_y - 1) * m_size[0] + m_x)));
	if (m_y + 1 < m_size[1])
		m_neighbours->push_back(m_map->at(static_cast<size_t>
										  ((m_y + 1) * m_size[0] + m_x)));
}
