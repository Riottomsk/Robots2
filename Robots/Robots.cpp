#pragma once
#include "Robots.h"
#include <thread>
#include <chrono>
#include <mutex>
#include "Ant.h"
//#include "MyForm.h"

using namespace Robots;


int Robot::Move(int direction, int distance)
{	
	int collision, counter = 0;
	while (counter < 10 && distance > 0)
	{
		collision = ModelOFEnvironment::Collision::instance()->TryToMove(this, direction);
		if (collision == 1)
		{			
			counter = 0;
			distance--;
		}
		if (collision == 2)
		{
			counter++;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}	
	if (distance > 0)
		return 0;
	return 1;
}

int Robot_set_2::MoveSync(int n_robots, int direction, int distance, ModelOFEnvironment::Object *object)
{		
	std::vector<int> prev_coord(4, 0);
	int collision;
	bool flag = false;
	for (int i = 0; i < object->GetCoord().size(); i++)
	{
		prev_coord[i] = object->GetCoord()[i];
	}
	while (distance > 0)
	{
		for (int i = 0; i < n_robots; i++)
		{
			collision = ModelOFEnvironment::Collision::instance()->TryToMove(robots[i], direction);
			if (collision == 2)
				flag = true;
		}
		if (object->GetCoord() == prev_coord && flag)
		{			
			break;
		}
		else
		{
			if(flag)
				distance--;
			flag = false;
		}
		for (int i = 0; i < object->GetCoord().size(); i++)
		{
			prev_coord[i] = object->GetCoord()[i];
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	if (distance > 0)
		return 0;
	else
		return 1;
}

int Robots::Robot_set_2::AntAlgorithm(ModelOFEnvironment::Object * object, int x_dest, int y_dest)
{
	return antAlgorithm(object, x_dest, y_dest, robots);	
}

void Robot::MoveTo(int x, int y)
{
	coord[0] = x;
	coord[1] = y;
}

int Robot_set_2::ApplyForce(int x, int y, int radius, int direction, int distance, ModelOFEnvironment::Object *object)
{
	int n_robots = robots.size();
	int interval=0;
	float tmp;
	int x1, y1;
	if (direction < 0 || direction>3)
		return 0;	
	//std::thread *t;
	//typedef void (Robot::*MethodPtr)();
	//typedef int (Robot::*P)(int direction, int distance);// = &Robot::Move;
	//P fun = &Robot::Move;
	switch (direction)
	{
	case 0:
		tmp = robots[0]->GetCoord()[2];//x size		
		interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		while (interval <= 0)
		{
			n_robots--;
			interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		}
		for (int i = 0; i < n_robots; i++)
		{
			x1 = x + tmp*i - radius + interval*(1 + i);
			y1 = y + 1;
			robots[i]->MoveTo(x1, y1);
		}		

		/*t = new std::thread[n_robots];
		for (int i=0; i < n_robots; i++)
		{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);//test and doesnt work

			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);//function works but leads to crust due to no mutex

		}

		for (int i=0; i < n_robots; i++)
		{
			if (t[i].joinable())
			{
				t[i].join();
			}
		}*/

		break;
	case 1:
		tmp = robots[0]->GetCoord()[3];//y size		
		interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		while (interval <= 0)
		{
			n_robots--;
			interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		}
		for (int i = 0; i < n_robots; i++)
		{
			y1 = y + tmp*i - radius + interval*(1 + i);
			x1 = x + 1;
			robots[i]->MoveTo(x1, y1);
		}

		/*t = new std::thread[n_robots];
		for (int i=0; i < n_robots; i++)
		{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
		}
		for (int i=0; i < n_robots; i++)
		{
			if (t[i].joinable())
			{
				t[i].join();
			}
		}*/
		break;
	case 2:
		tmp = robots[0]->GetCoord()[3];//y size		
		interval = (2 * radius - tmp * n_robots) / (1 + n_robots);//trust me - i'm an engineer
		while (interval <= 0)
		{
			n_robots--;
			interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		}
		for (int i = 0; i < n_robots; i++)
		{
			y1 = y + tmp*i - radius + interval*(i+1);
			x1 = x - 1 - robots[0]->GetCoord()[2];
			robots[i]->MoveTo(x1, y1);
		}

		/*t = new std::thread[n_robots];
		for (int i=0; i < n_robots; i++)
		{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
		}
		for (int i=0; i < n_robots; i++)
		{
			if (t[i].joinable())
			{
				t[i].join();
			}
		}*/
		break;
	case 3:
		tmp = robots[0]->GetCoord()[2];//x size		
		interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		while (interval <= 0)
		{
			n_robots--;
			interval = (2 * radius - tmp * n_robots) / (1 + n_robots);
		}
		for (int i = 0; i < n_robots; i++)
		{
			x1 = x + tmp*i - radius + interval*(1 + i);
			y1 = y - 1 - robots[0]->GetCoord()[3];
			robots[i]->MoveTo(x1, y1);
		}

		/*t = new std::thread[n_robots];
		for (int i=0; i < n_robots; i++)
		{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
		}
		for (int i=0; i < n_robots; i++)
		{
			if (t[i].joinable())
			{
				t[i].join();				
			}
		}*/
		break;
	}
	return MoveSync(n_robots, direction, distance, object);
	
}

/*void Robot::MoveUp(int distance)
{	
	std::vector<int> prev_coord = coord;
	int collision, counter = 0;
	while (counter < 10 && distance > 0)
	{
		//int collision = Collision::instance()->TryToMove(coord, 0);
		//coord[1] -= distance;
		
		//if (Collision::instance()->TryToMove(coord, 0) == 1)
			//break;

		//Collision::instance()->MoveForcibly(coord, 0);//temporary measures, while collision isnt working

		collision = Collision::instance()->TryToMove(this, 0);
		if (collision == 1)
		{
			coord[1]--;
			distance--;
			counter = 0;
		}
		if (collision == 2)
		{
			counter++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));		
		
	}
}
void Robot::MoveLeft(int distance)
{	
	for (; distance > 0; distance--)
	{
		//if (Collision::instance()->TryToMove(coord, 1) == 1)
			//break;
		//Collision::instance()->MoveForcibly(coord, 1);
		coord[0]--;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));		
			
	}
}
void Robot::MoveRight(int distance)
{
	
	for (; distance > 0; distance--)
	{
		//if (Collision::instance()->TryToMove(coord, 2) == 1)
		//break;
		//Collision::instance()->MoveForcibly(coord, 2);
		coord[0]++;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
void Robot::MoveDown(int distance)
{	
	for (; distance > 0; distance--)
	{
		//if (Collision::instance()->TryToMove(coord, 3) == 1)
		//break;
		//Collision::instance()->MoveForcibly(coord, 3);
		coord[1]++;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}*/

int Robot_set_3::MoveObject(ModelOFEnvironment::Object *object, int x, int y)
{
	std::vector<int> prev_coord = object->GetCoord();
	int direction_x, direction_y, distance_x, distance_y;
	distance_x = x - object->GetCoord()[0];
	if ( distance_x > 0)
		direction_x = 2;
	else
	{
		direction_x = 1;
		distance_x *= -1;
	}

	distance_y = y - object->GetCoord()[1];
	if ( distance_y > 0)
		direction_y = 3;
	else
	{
		direction_y = 0;
		distance_y *= -1;
	}


	int n_robots = robots_set_2.size();
	int radius = 0;
	float tmp;
	int x1, y1;	
	
	if (distance_x)
	{
		switch (direction_x)
		{

		case 1:
			radius = object->GetCoord()[3] / (2 * n_robots);
			for (int i = 0; i < n_robots; i++)
			{
				y1 = object->GetCoord()[1] + (2 * i + 1) * radius;
				x1 = object->GetCoord()[0] + object->GetCoord()[2];
				robots_set_2[i]->ApplyForce(x1, y1, radius, direction_x, distance_x, object);//should be a thread
			}

			/*t = new std::thread[n_robots];
			for (int i=0; i < n_robots; i++)
			{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
			}
			for (int i=0; i < n_robots; i++)
			{
			if (t[i].joinable())
			{
			t[i].join();
			}
			}*/
			break;
		case 2:
			radius = object->GetCoord()[3] / (2 * n_robots);
			for (int i = 0; i < n_robots; i++)
			{
				y1 = object->GetCoord()[1] + (2 * i + 1) * radius;
				x1 = object->GetCoord()[0];
				robots_set_2[i]->ApplyForce(x1, y1, radius, direction_x, distance_x, object);//should be a thread
			}

			/*t = new std::thread[n_robots];
			for (int i=0; i < n_robots; i++)
			{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
			}
			for (int i=0; i < n_robots; i++)
			{
			if (t[i].joinable())
			{
			t[i].join();
			}
			}*/
			break;
		}
	}

	if (distance_y)
	{
		switch (direction_y)
		{

		case 0:
			radius = object->GetCoord()[2] / (2 * n_robots);
			for (int i = 0; i < n_robots; i++)
			{
				x1 = object->GetCoord()[0] + (2 * i + 1) * radius;
				y1 = object->GetCoord()[1] + object->GetCoord()[3];
				robots_set_2[i]->ApplyForce(x1, y1, radius, direction_y, distance_y, object);//should be a thread
			}

			/*t = new std::thread[n_robots];
			for (int i=0; i < n_robots; i++)
			{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
			}
			for (int i=0; i < n_robots; i++)
			{
			if (t[i].joinable())
			{
			t[i].join();
			}
			}*/
			break;
		case 3:
			radius = object->GetCoord()[2] / (2 * n_robots);
			for (int i = 0; i < n_robots; i++)
			{
				x1 = object->GetCoord()[0] + (2 * i + 1) * radius;
				y1 = object->GetCoord()[1];
				robots_set_2[i]->ApplyForce(x1, y1, radius, direction_y, distance_y, object);//should be a thread
			}

			/*t = new std::thread[n_robots];
			for (int i=0; i < n_robots; i++)
			{
			//t[i] = std::thread(robots[i]->*fun, direction, distance);
			t[i] = std::thread(&Robot::Move, robots[i], direction, distance);
			}
			for (int i=0; i < n_robots; i++)
			{
			if (t[i].joinable())
			{
			t[i].join();
			}
			}*/
			break;
		}
	}
	return (prev_coord[0] == x && prev_coord[1] == y);

}