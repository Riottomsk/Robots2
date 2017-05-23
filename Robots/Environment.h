#pragma once
#include <vector>

namespace ModelOFEnvironment
{
	class Object
	{
	protected:
		std::vector<int> coord;
		int weight;
		Object() {}; // Each object must have its parameters while initialized
		std::vector<std::pair<std::vector<int>, Object *>> appliedForce;

	public:
		Object(int weight, std::vector<int> location);
		int ApplyForce(int direction, int amount, Object *object);
		void Move(int direction);
		bool operator==(Object object)
		{
			if (this->coord == object.coord && this->weight == object.weight)
				return true;
			return false;
		}
		std::vector<int> GetCoord()
		{
			return coord;
		}
		int GetWeight()
		{
			return weight;
		}
	};

	class Collision
	{
		static Collision *m_pinstance;
		//std::atomic<std::vector<std::vector<int>>> objs;
		//std::vector<std::vector<int>> objects;
		std::vector<ModelOFEnvironment::Object*> objects;
		static Collision * p_instance;
		Collision() {}



	public:
		static Collision *instance();

		Collision(const Collision&) = delete;
		Collision& operator=(Collision&) = delete;

		void Acquire_new_object(Object *object);

		std::vector<ModelOFEnvironment::Object*> getObjects()
		{
			return objects;
		}


		int TryToMove(Object *, int);
		void MoveForcibly(Object *, int);
	};
}