#include "Ant.h"
#include <ctime>
#include <random>
#include <thread>


Ant::Ant()
{
}

void Ant::addRobot(Robots::Robot * robot)
{
	robots.push_back(robot);
}

int Ant::makeAnt(ModelOFEnvironment::Object * object)
{
	std::vector<int> obj_coor = object->GetCoord();
	//int perimetr = (obj_coor[2] + obj_coor[3]) * 2;
	int volume = obj_coor[2] * obj_coor[3];
	if (robots.empty())
		return 0;

	if (robots[0]->GetCoord()[2] * robots[0]->GetCoord()[2] * robots.size() < volume) //we should cover full body //we assume that robots are square shape
		return 0;

	int x_size = obj_coor[2];
	int y_size = obj_coor[3];
	bool flag = true;

	int curr_robot = 0;
	int curr_x_pos = obj_coor[0] + x_size + 1; // start creating ant from right edge of the object  TODO: Possibility to create on a different edges
	int curr_y_pos = obj_coor[1];
	while (flag)
	{
		while (x_size > 0)//simulating top side
		{
			robots[curr_robot]->MoveTo(curr_x_pos, curr_y_pos);
			x_size -= robots[curr_robot]->GetCoord()[2]; //TODO: optimize to constant
			if (x_size > 0) 
				curr_x_pos += robots[curr_robot]->GetCoord()[2];
			curr_robot++;			
		}
		
		y_size -= robots[curr_robot-1]->GetCoord()[3];//robots should be equal, but if they not - that code should still be accurate
		curr_y_pos += robots[curr_robot-1]->GetCoord()[3];
		
		while (y_size > 0)//simulating right side
		{
			robots[curr_robot]->MoveTo(curr_x_pos, curr_y_pos);
			y_size -= robots[curr_robot]->GetCoord()[3]; //TODO: optimize to constant
			if (y_size > 0)
				curr_y_pos += robots[curr_robot]->GetCoord()[3];
			curr_robot++;
		}

		x_size = obj_coor[2];
		y_size = obj_coor[3];

		curr_x_pos -= robots[curr_robot-1]->GetCoord()[2];
		x_size -= robots[curr_robot-1]->GetCoord()[2];
		while (x_size > 0)//simulating bottom side
		{
			robots[curr_robot]->MoveTo(curr_x_pos, curr_y_pos);
			x_size -= robots[curr_robot]->GetCoord()[2]; //TODO: optimize to constant
			if (x_size > 0)
				curr_x_pos -= robots[curr_robot]->GetCoord()[2];
			curr_robot++;
		}

		y_size -= robots[curr_robot - 1]->GetCoord()[3] + robots[0]->GetCoord()[3];//robots should be equal, but if they not - that code should still be accurate
		curr_y_pos -= robots[curr_robot - 1]->GetCoord()[3];

		while (y_size > 0)//simulating left side
		{
			robots[curr_robot]->MoveTo(curr_x_pos, curr_y_pos);
			y_size -= robots[curr_robot]->GetCoord()[3]; //TODO: optimize to constant
			curr_y_pos -= robots[curr_robot]->GetCoord()[3];
			curr_robot++;
		}
		flag = false;
		usedRobots = curr_robot;

	}
	return 1;
}

int oppositeDirection(int direction)
{
	//magic numbers incoming // 0 - up, 1 - left, 2 - right, 3 - down
	if (direction == 0)
		return 3;
	if (direction == 1)
		return 2;
	if (direction == 2)
		return 1;
	if (direction == 3)
		return 0;
	return -1; //mistake!
}

int Ant::moveAnt(int direction, int distance)
{
	int res = 1, i;
	int oppDir = oppositeDirection(direction);
	while (distance > 0 && res == 1)
	{
		for (i = 0; i < usedRobots && res == 1; i++)
			res = robots[i]->Move(direction, 1);
		if (res == 1)
			distance--;
		else
			for (int j = 0; j < i - 1; j++)
				robots[j]->Move(oppDir, 1);
	}

	if (distance == 0)
		return 1; //success

	return 0; //collision
}
std::vector<int> Ant::getPosition()
{	
	return robots[0]->GetCoord();
}
double calculateL(int x_curr, int y_curr, int x_dest, int y_dest, int i)
{
	double result = -1;
	double d;
	d = sqrt(pow(x_curr - x_dest, 2) + pow(y_curr - y_dest, 2));
	switch (i)
	{
	case 0:
		if (y_curr - y_dest < 0)
		{
			result = abs(x_curr - x_dest) / d;
		}
		else
		{
			result = 1 + abs(y_curr - y_dest) / d;
		}
		break;
	case 1:
		if (x_curr - x_dest < 0)
		{
			result = abs(y_curr - y_dest) / d;
		}
		else
		{
			result = 1 + abs(x_curr - x_dest) / d;
		}
		break;
	case 2:
		if (x_curr - x_dest > 0)
		{
			result = abs(y_curr - y_dest) / d;
		}
		else
		{
			result = 1 + abs(x_curr - x_dest) / d;
		}
		break;
	case 3:
		if (y_curr - y_dest > 0)
		{
			result = abs(x_curr - x_dest) / d;
		}
		else
		{
			result = 1 + abs(y_curr - y_dest) / d;
		}
		break;
	}
	return result;
}

double calculateF(int x_curr, int y_curr, int i)
{
	double result;
	switch (i)
	{
	case 0:
		result = Feromones::instance()->getValue()[x_curr][y_curr - 1];
		break;
	case 1:
		result = Feromones::instance()->getValue()[x_curr - 1][y_curr];
		break;
	case 2:
		result = Feromones::instance()->getValue()[x_curr + 1][y_curr];
		break;
	case 3:
		result = Feromones::instance()->getValue()[x_curr][y_curr + 1];
		break;
	}
	result = result / 10;
	return result;
}


int Ant::algorithm(int x_dest, int y_dest)
{

	return 0;
}

void Ant::moveAntThread(int x_dest, int y_dest)
{
	int x_limit = Feromones::instance()->getValue().size();
	int y_limit = Feromones::instance()->getValue()[0].size();
	std::vector<std::vector<bool>> curr_feromones(x_limit);	
	for (int i = 0; i < x_limit; i++)
	{
		curr_feromones[i].resize(y_limit);
		for (int j = 0; j < y_limit; j++)
			curr_feromones[i][j] = false;
	}

	int res = 1;
	int amount = this->robots.size();
	int way;
	bool flag = true;
	bool keepWay = false;
	int keepWayCounter;
	int counter = 0;
	int counter2 = 0;
	std::vector<int> position = this->getPosition();
	int x_pos = position[0], y_pos = position[1], size = position[2];
		

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	int max_dist_on_way = 10;
	std::uniform_int_distribution<> dis(0, max_dist_on_way);
	int dow = 0; // distance on way

	while ((x_pos != x_dest || y_pos != y_dest) && counter < 10000)
	{
		curr_feromones[x_pos][y_pos] = true;
		if (counter > 5000)
		{
			way = 4;
		}
		if (flag)
		{
			if (!keepWay)
			{
				way = chooseWay(x_pos, y_pos, x_dest, y_dest);
				keepWay = true;
				dow = dis(gen) + 1;

				res = this->moveAnt(way, 1);
				if (res == 1)
				{
					switch (way)
					{
					case 0:
						y_pos--;
						break;
					case 1:
						x_pos--;
						break;
					case 2:
						x_pos++;
						break;
					case 3:
						y_pos++;
						break;
					}
				}
				counter++;
				counter2--;
				dow--;
				if (dow == 0)
					keepWay = false;

				if (((x_pos - x_dest) * (x_pos - x_dest) + (y_pos - y_dest) * (y_pos - y_dest)) < size * size * amount && counter2 < 0) //not sure about last part of relation - should be more precise
				{
					flag = false;
					keepWay = false;
				}
			}
			else
			{
				res = this->moveAnt(way, 1);
				if (res == 1)
				{
					switch (way)
					{
					case 0:
						y_pos--;
						break;
					case 1:
						x_pos--;
						break;
					case 2:
						x_pos++;
						break;
					case 3:
						y_pos++;
						break;
					}
				}
				else
					keepWay = false;
				counter++;
				counter2--;
				dow--;
				if (dow == 0)
					keepWay = false;

				if (((x_pos - x_dest) * (x_pos - x_dest) + (y_pos - y_dest) * (y_pos - y_dest)) < size * size * amount && counter2 < 0) //not sure about last part of relation - should be more precise
				{
					flag = false;
					keepWay = false;
				}
			}
		}
		else
		{
			//way = - 1;
			if (x_pos - x_dest == 0)
			{				
				if (y_pos - y_dest < 0)
					way = 3;
				else
					way = 0;
			}
			else
			{
				if (x_pos - x_dest < 0)
					way = 2;
				else
					way = 1;
			}

			res = this->moveAnt(way, 1);
			counter++;

			if (res == 0)
			{
				flag = true;
				counter2 = 100;
			}
			else
			{
				switch (way)
				{
				case 0:
					y_pos--;
					break;
				case 1:
					x_pos--;
					break;
				case 2:
					x_pos++;
					break;
				case 3:
					y_pos++;
					break;
				}
			}
		}
	}
	
	if (counter < 10000)
	{
		for (int i = 0; i < x_limit; i++)
			for (int j = 0; j < y_limit; j++)
				if (curr_feromones[i][j])
					Feromones::instance()->addFermone(i, j);
	}
}


int antAlgorithm(ModelOFEnvironment::Object * object, int x_dest, int y_dest, std::vector<Robots::Robot*> robots)
{
	std::vector<Ant*> ants;
	int usedRobots = 0;
	int robots_left = robots.size();
	int size_of_robot = robots[0]->GetCoord()[2]; // we assume that robots are square shape

	std::vector<int> obj_coor = object->GetCoord();
	int volume = obj_coor[2] * obj_coor[3];
	int neededRobots = volume / (size_of_robot * size_of_robot);
	if (volume % size_of_robot != 0)
		neededRobots++;
	int totalAnts = robots_left / neededRobots;
	int curr_robots = 0;
	for (int i = 0; i < totalAnts; i++)
	{
		ants.push_back(new Ant());
		for (int j = 0; j < neededRobots; j++)
		{
			ants[i]->addRobot(robots[curr_robots]);
			curr_robots++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		std::vector<std::thread*> antThreads;

		for (auto ant : ants)
		{
			int res = ant->makeAnt(object);

			if (res)
			{
				antThreads.push_back(new std::thread(&Ant::moveAntThread, ant, x_dest, y_dest));
			}
		}

		for (auto t : antThreads)
			t->join();
	}
	return 0;
}
double chooseWay(int x_curr, int y_curr, int x_dest, int y_dest)
{
	const int N = 4;
	const double p = 0.5, q = 1 - p;
	std::vector<double> P(N);
	std::vector<double> l(N);
	std::vector<double> f(N);

	double devisor = 0;
	double test;
	for (int i = 0; i < N; i++)
	{
		l[i] = calculateL(x_curr, y_curr, x_dest, y_dest, i);		
		f[i] = calculateF(x_curr, y_curr, i);		
		devisor += pow(l[i], p) * pow(f[i], q);
	}

	for (int i = 0; i < N; i++)
	{
		P[i] = pow(l[i], p)*pow(f[i], q) / devisor;
		test = P[i];
		//std::cout << P[i];
	}
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	int local_rand_max = 1000;
	std::uniform_int_distribution<> dis(0, local_rand_max);
	double result = (double)dis(gen) / local_rand_max;
	double tmp = 0;
	for (int i = 0; i < 4; i++)
	{
		tmp += P[i];
		if (result < tmp)
			return i;
	}

	return result;
}

Feromones* Feromones::m_pinstance = 0;

Feromones* Feromones::instance()
{
	if (m_pinstance == 0)
		m_pinstance = new Feromones;
	return m_pinstance;
}

int Feromones::initialize(int x_limit, int y_limit)
{
	std::vector<std::vector<int>> tmp(x_limit);	
	for (int i = 0; i < x_limit; i++)
	{
		tmp[i].resize(y_limit);
		for (int j = 0; j < y_limit; j++)
			tmp[i][j] = 1;
	}
	feromones = tmp;
	return 0;
}

void Feromones::addFermone(int x, int y)
{
	feromones[x][y]++;
}
