#include "Visualization.h"
#include "Ant.h"
//#include <chrono>
//#include <thread>



/*void Visualization::itemsToVis(std::vector<Robots::Object*> objects)
{
	//std::thread t(&Draw, objects);
	System::Threading::Thread^ oThread = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(Visualization::Draw));
	oThread->Start(objects);

}

void Draw(System::Object^ data)
{

}*/

/*void Visualization::Vis(std::vector<ModelOFEnvironment::Object*, std::allocator<ModelOFEnvironment::Object*>> objects)
{
	std::thread t(&Visualization::Draw, objects);
	t.join();
}*/

void Visualization::Draw(std::vector<ModelOFEnvironment::Object*, std::allocator<ModelOFEnvironment::Object*>> objects)
{
	if (panel)
	{
		System::Drawing::Graphics^ g = panel->CreateGraphics();
		System::Drawing::Pen ^p = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 2);
		g->Clear(System::Drawing::Color::White);
		for (auto val : objects)
		{
			g->DrawRectangle(p, val->GetCoord()[0], val->GetCoord()[1], val->GetCoord()[2], val->GetCoord()[3]);
		}
	}
}

void Visualization::drawInThread()
{
	System::Drawing::Graphics^ g = Visualization::Instance()->getPanel()->CreateGraphics();
	System::Drawing::Pen ^p = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 2);
	System::Drawing::Pen ^p2;
	//g->Clear(System::Drawing::Color::White);
	std::vector<ModelOFEnvironment::Object*, std::allocator<ModelOFEnvironment::Object*>> objects;
	while (g)
	{
		objects = ModelOFEnvironment::Collision::instance()->getObjects();
		g->Clear(System::Drawing::Color::White);
		//g->Clear(System::Drawing::Color::FromArgb(245, System::Drawing::Color::Yellow));

		std::vector<std::vector<int>> feromones = Feromones::instance()->getValue();

		for(int i = 0; i < feromones.size(); i++)
			for (int j = 0; j < feromones[0].size(); j++)
			{
				int curr_val = feromones[i][j];
				if (curr_val > 1) {
					//System::Drawing::Color baseColor = System::Drawing::Color::FromArgb(255,0,0);
					System::Drawing::Color myColor = System::Drawing::Color::FromArgb((curr_val*2), System::Drawing::Color::Yellow);

					p2 = gcnew System::Drawing::Pen(myColor, 1);
					g->DrawRectangle(p2, i, j, 1, 1);
				}
				/*if (curr_val > 2)
				{
					bool flag = true;
				}*/


			}



		for (auto val : objects)
		{
			g->DrawRectangle(p, val->GetCoord()[0], val->GetCoord()[1], val->GetCoord()[2], val->GetCoord()[3]);
		}



		System::Threading::Thread::Sleep(500);
	}
	//throw gcnew System::NotImplementedException();
}

//void Visualization::ThreadProc(System::Windows::Forms::Panel^ panel)
/*void ThreadExample::ThreadProc(System::Windows::Forms::Panel^ panel)
{
	System::Drawing::Graphics^ g = panel->CreateGraphics();
	System::Drawing::Pen ^p = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 2);
	//g->Clear(System::Drawing::Color::White);
	std::vector<ModelOFEnvironment::Object*, std::allocator<ModelOFEnvironment::Object*>> objects;
	while (true)
	{
		objects = ModelOFEnvironment::Collision::instance()->getObjects();
		g->Clear(System::Drawing::Color::White);
		for (auto val : objects)
		{
			g->DrawRectangle(p, val->GetCoord()[0], val->GetCoord()[1], val->GetCoord()[2], val->GetCoord()[3]);
		}
		System::Threading::Thread::Sleep(1000);
	}
	//throw gcnew System::NotImplementedException();
}*/
