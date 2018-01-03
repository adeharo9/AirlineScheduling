#include "Node.h"

Node::Node() = default
{

}

Node::Node(int c, int h)
{
	ciutat = c;
	hora = h;
	demanda = 0;
}