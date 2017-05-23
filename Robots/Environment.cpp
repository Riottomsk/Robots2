#include "Environment.h"
#include "Visualization.h"

using namespace ModelOFEnvironment;
Object::Object(int weight, std::vector<int> location)
{
	this->weight = weight;
	coord = location;
	Collision::instance()->Acquire_new_object(this);
	//std::vector<int> appf(4, 0);
	//appliedForce = appf;
}

void Object::Move(int direction)
{
	//Collision::instance()->MoveForcibly(coord, direction);
	//Visualization^ vis = Visualization::Instance();
	//std::vector<ModelOFEnvironment::Object*> obj =	Collision::instance()->getObjects();
	//std::vector<ModelOFEnvironment::Object*> *obj1 = obj;
	//vis->Draw(obj);
	//Visualization::Instance()->Draw(Collision::instance()->getObjects());
	switch (direction)
	{
	case 0:
		coord[1]--;
		break;
	case 1:
		coord[0]--;
		break;
	case 2:
		coord[0]++;
		break;
	case 3:
		coord[1]++;
		break;
	}
}


int Object::ApplyForce(int direction, int amount, Object *object)
{
	bool flag = false;
	//std::mutex appf_mutex;//wtf am i doing?
	//std::lock_guard<std::mutex> guard(appf_mutex);
	for (auto &val : appliedForce)
	{
		if (std::get<1>(val) == object)
		{
			for (auto &val2 : std::get<0>(val))
				val2 = 0;
			std::get<0>(val)[direction] = amount;
			flag = true;
			break;
		}
	}

	if (!flag)
	{
		std::vector<int> appf(4, 0);
		appf[direction] = amount;
		appliedForce.push_back(std::make_pair(appf, object));

	}
	int currForce = 0;
	for (auto val : appliedForce)
	{
		currForce += std::get<0>(val)[direction];
	}

	if (currForce > weight)
	{
		this->Move(direction);
		for (int i = 0; i < appliedForce.size(); i++)
			if (std::get<0>(appliedForce[i])[direction] > 0)
				appliedForce.erase(appliedForce.begin() + i);
		return 1;
	}

	return 0;
}


int Collision::TryToMove(Object *object, int direction)// direction: 0 - Up, 1- Left, 2 - Right, 3 - Down
{
	int moving_obj = -1;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i] == object)
		{
			moving_obj = i;
			break;
		}

	//it looks like object and object[moving_obj] are equal

	if (direction < 0 || direction > 3 || moving_obj == -1)
	{
		return 0; // error in parameters
	}
	//mutex must be somewhere here
	for (auto val0 : objects)
	{
		if (val0->GetWeight() > 0)
		{
			auto val = val0->GetCoord();
			auto coord = object->GetCoord();
			if (direction == 0)
			{
				if (coord[1] - 1 == val[1] + val[3])//y2-- == y1 + h1
				{
					if ((val[0] < coord[0] && coord[0] < val[0] + val[2]) || (val[0] < coord[0] + coord[2] && coord[0] + coord[2] < val[0] + val[2]) \
						|| (coord[0] < val[0] && val[0] < coord[0] + coord[2]) || (coord[0] < val[0] + val[2] && val[0] + val[2] < coord[0] + coord[2]))

					{
						val0->ApplyForce(direction, object->GetWeight(), object);
						return 2;//collision - can't move;
					}
				}
				//need something?
				//objects[moving_obj][1]--;
				//objects[moving_obj].Move(direction);

			}
			if (direction == 1)
			{
				if (coord[0] - 1 == val[0] + val[2])
				{
					if ((val[1] < coord[1] && coord[1] < val[1] + val[3]) || (val[1] < coord[1] + coord[3] && coord[1] + coord[3] < val[1] + val[3]) || (coord[1] < val[1] && val[1] < coord[1] + coord[3]) \
						|| (coord[1] < val[1] + val[3] && val[1] + val[3] < coord[1] + coord[3]))
					{
						val0->ApplyForce(direction, object->GetWeight(), object);
						return 2;
					}
				}
			}
			if (direction == 2)
			{
				if (coord[0] + coord[2] + 1 == val[0])
				{
					if ((val[1] < coord[1] && coord[1] < val[1] + val[3]) || (val[1] < coord[1] + coord[3] && coord[1] + coord[3] < val[1] + val[3]) || (coord[1] < val[1] && val[1] < coord[1] + coord[3]) \
						|| (coord[1] < val[1] + val[3] && val[1] + val[3] < coord[1] + coord[3]))
					{
						val0->ApplyForce(direction, object->GetWeight(), object);
						return 2;
					}
				}
			}
			if (direction == 3)
			{
				if (coord[1] + coord[3] + 1 == val[1])
				{
					if ((val[0] < coord[0] && coord[0] < val[0] + val[2]) || (val[0] < coord[0] + coord[2] && coord[0] + coord[2] < val[0] + val[2]) || (coord[0] < val[0] && val[0] < coord[0] + coord[2]) \
						|| (coord[0] < val[0] + val[2] && val[0] + val[2] < coord[0] + coord[2]))
					{
						val0->ApplyForce(direction, object->GetWeight(), object);
						return 2;//collision - can't move;
					}
				}
			}
		}
	}
	object->Move(direction);
	return 1;//everything fine;
}

Collision* Collision::m_pinstance = 0;

Collision* Collision::instance()
{
	if (m_pinstance == 0)
		m_pinstance = new Collision;
	return m_pinstance;
}

void Collision::Acquire_new_object(Object *object)
{
	objects.push_back(object);
}

void Collision::MoveForcibly(Object *object, int direction)
{
	for (auto val : objects)
	{
		if (val == object)
		{
			val->Move(direction);
			break;
		}
	}
}