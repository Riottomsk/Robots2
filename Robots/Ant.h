#pragma once
#include "Robots.h"
#include <math.h>

int antAlgorithm(ModelOFEnvironment::Object * object, int x_dest, int y_dest, std::vector<Robots::Robot*> robots);

class Ant
{
	std::vector<Robots::Robot*> robots;	
	int usedRobots;
public:
	Ant();
	void addRobot(Robots::Robot* robot);
	int makeAnt(ModelOFEnvironment::Object* object);
	int moveAnt(int direction, int distance);

	std::vector<int> getPosition();
	int algorithm(int x_dest, int y_dest);	

	void moveAntThread(int x_dest, int y_dest);
};

double chooseWay(int x_curr, int y_curr, int x_dest, int y_dest);

class Feromones
{
	std::vector<std::vector<int>> feromones; 

	static Feromones *m_pinstance;
	static Feromones *p_instance;
	Feromones() {}

public:
	static Feromones *instance();

	Feromones(const Feromones&) = delete;
	Feromones& operator=(Feromones&) = delete;

	int initialize(int x_limit, int y_limit);

	std::vector<std::vector<int>> getValue()
	{
		return feromones;
	}

	void addFermone(int x, int y);
};
