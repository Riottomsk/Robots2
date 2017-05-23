#pragma once
#include <vector>
#include "Environment.h"


public ref class Visualization
{
	static Visualization ^p_instance;
	bool run = false;
	System::Windows::Forms::Panel^ panel;	
	Visualization() {}
public:
	//static Visualization^ instance();
	static Visualization^ Instance()
	{
		if (!p_instance)
			p_instance = gcnew Visualization();		
		return p_instance;
	}
		

	

	//void itemsToVis(std::vector<Robots::Object*> objects);
	//static void Draw(System::Object^ data);
	
	void addPanel(System::Windows::Forms::Panel ^p1)
	{
		panel = p1;
	}

	System::Windows::Forms::Panel^ getPanel()
	{
		return panel;
	}


	
	//void addToVis(System::Windows::Forms::Panel^ p1);
	//void Vis(std::vector<ModelOFEnvironment::Object*, std::allocator<ModelOFEnvironment::Object*>> objects);
	void Draw(std::vector<ModelOFEnvironment::Object*, std::allocator<ModelOFEnvironment::Object*>> objects);
	void Start()
	{
		run = true;
	}
	void Finish()
	{
		run = false;
	}
	void StartThreads()
	{
		// Start a thread that calls a parameterized static method.
		System::Threading::Thread^ newThread = gcnew
			System::Threading::Thread(gcnew System::Threading::ThreadStart(Visualization::drawInThread));
		newThread->Start();
	}
	static void drawInThread();
};

/*public ref class ThreadExample
{
public:
	static void ThreadProc(System::Windows::Forms::Panel^ panel);
};*/

//using namespace System;
//using namespace System::Threading;

namespace SystemThreadingExample
{
	public ref class Work
	{
		System::Windows::Forms::Panel^ panel;
	public:
		void StartThreads(System::Windows::Forms::Panel^ panel)
		{
			// Start a thread that calls a parameterized static method.
			System::Threading::Thread^ newThread;/* = gcnew
				Thread(gcnew ParameterizedThreadStart(Work::DoWork));
			newThread->Start(panel);*/
			
			// Start a thread that calls a parameterized instance method.
			Work^ someWork = gcnew Work;
			newThread = gcnew System::Threading::Thread(
				gcnew System::Threading::ParameterizedThreadStart(someWork,
					&Work::DoMoreWork));
			newThread->Start("The answer.");			
			
		}

		static void DoWork(int data)
		{
			
		}

		void addPanel(System::Windows::Forms::Panel ^p1)
		{
			panel = p1;
		}

		void DoMoreWork(Object^ data)
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
		}
	};
}