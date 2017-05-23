#pragma once
#include <vector>
#include "Environment.h"

namespace Robots
{
	class Robot : public ModelOFEnvironment::Object
	{

		//int set;
		//std::vector<int> coord;

	public:

		Robot(std::vector<int> location, int weight = 0) :ModelOFEnvironment::Object(weight, location)
		{
			//this->set = set;
			//coord = location;
			//this->weight = weight;		
		}

		int Move(int direction, int distance);

		void MoveTo(int x, int y);

		

		/*void MoveUp(int distance = 1);
		void MoveLeft(int distance = 1);
		void MoveRight(int distance = 1);
		void MoveDown(int distance = 1);*/
	};

	class Robot_set_2 : public Robot
	{
	protected:
		std::vector<Robot*> robots;
	public:
		Robot_set_2(std::vector<int> location, int weight = 0) :Robot(location, weight) {}
		void AddRobot(Robot *robot)
		{
			robots.push_back(robot);
		}
		int ApplyForce(int x, int y,int radius,int direction, int distance, ModelOFEnvironment::Object *object);
		int MoveSync(int n_robots, int direction, int distance, ModelOFEnvironment::Object *object);
		int AntAlgorithm(ModelOFEnvironment::Object *object, int x_dest, int y_dest);
	};

	class Robot_set_3 : protected Robot_set_2
	{
		std::vector<Robot_set_2 *> robots_set_2;
	public:
		Robot_set_3(std::vector<int> location, int weight = 0) : Robot_set_2(location, weight) {}
		void AddRobot(Robot_set_2 *robot)
		{
			robots_set_2.push_back(robot);
		}
		int MoveObject(ModelOFEnvironment::Object *object, int x, int y);
		int AntAlgorithm(ModelOFEnvironment::Object *object, int x_dest, int y_dest);
	};


}
