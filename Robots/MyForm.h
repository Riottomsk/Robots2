#pragma once
#include "Environment.h"
#include "Robots.h"
#include "Visualization.h"
#include "Ant.h"


namespace Robots {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(13, 13);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->panel1->Location = System::Drawing::Point(98, 41);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(530, 270);
			this->panel1->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(98, 331);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(529, 92);
			this->textBox1->TabIndex = 2;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(13, 43);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(701, 454);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		std::vector<ModelOFEnvironment::Object*> *objects;

		void drawObjects(std::vector<ModelOFEnvironment::Object*> objects)
		{
			System::Drawing::Graphics^ g = this->panel1->CreateGraphics();
			Pen ^p = gcnew Pen(Color::Black, 2);
			g->Clear(System::Drawing::Color::White);
			for (auto val : objects)
			{
				g->DrawRectangle(p, val->GetCoord()[0], val->GetCoord()[1], val->GetCoord()[2], val->GetCoord()[3]);
			}

			textBox1->Clear();
			std::vector<char> param = { 'x','y','w','h' };
			for (auto val : objects)
			{
				//for (auto val2 : val->GetCoord())
				for (int i = 0; i<val->GetCoord().size(); i++)
				{
					textBox1->Text += wchar_t(param[i]);
					textBox1->Text += " = ";
					textBox1->Text += val->GetCoord()[i];
					textBox1->Text += "  ";
				}
				textBox1->Text += "\r\n";
			}

			/*System::Threading::Thread^ oThread = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(ThreadExample::ThreadProc));

			// Start ThreadProc.  Note that on a uniprocessor, the new 
			// thread does not get any processor time until the main thread 
			// is preempted or yields.  Uncomment the Thread::Sleep that 
			// follows oThread->Start() to see the difference.
			oThread->Start();*/


		}

		void drawInThread()
		{
			Visualization::Instance()->StartThreads();
			/*SystemThreadingExample::Work^ samplework;
			samplework->addPanel(this->panel1);
			samplework =
				gcnew SystemThreadingExample::Work();
			samplework->StartThreads(this->panel1);*/
		}

		Robots::Robot *robot;
		ModelOFEnvironment::Object *obj, *obst, *edge, *goal;
		Robots::Robot_set_2 *robot110;
		Robots::Robot_set_3 *robot100;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Visualization::Instance()->addPanel(this->panel1);
		drawInThread();
		std::vector<int> coord({ 100, 200, 10, 10 });
		
		coord = { 100,220,90,30 };
		
		robot110 = new Robots::Robot_set_2(coord);

		coord = { 0,0,0,0 };
		robot100 = new Robots::Robot_set_3(coord);


		coord = { 50,50,30,20 };
		
		obj = new ModelOFEnvironment::Object(2, coord);


		coord = { 120,50,50,40 };

		obst = new ModelOFEnvironment::Object(3, coord);

		coord = { 0,0,530,0 };
		edge = new ModelOFEnvironment::Object(100, coord);
		coord = { 530,0,0,270 };
		edge = new ModelOFEnvironment::Object(100, coord);
		coord = { 0,270,530,0 };
		edge = new ModelOFEnvironment::Object(100, coord);
		coord = { 0,0,0,270 };
		edge = new ModelOFEnvironment::Object(100, coord);

		



		for (int i = 0; i < 24; i++)
		{
			coord = { 100 + 20 * i,200,10,10 };
			//coord = { 305 + 15*i,139,10,10 };
			robot = new Robots::Robot(coord, 0);
			robot110->AddRobot(robot);
		}

		robot100->AddRobot(robot110);

		//System::Collections::Generic::List<Robots::Object>^ dinosaurs = gcnew System::Collections::Generic::List<String^>();

		//drawObjects(ModelOFEnvironment::Collision::instance()->getObjects());
		//Visualization::Instance()->addPanel(this->panel1);


		
		coord = { 250,50,1,1 };
		goal = new ModelOFEnvironment::Object(0, coord);

		int test = 1;
		//test = robot110->ApplyForce(50, 100, 50, 2, 200, obj);

		//test = robot100->MoveObject(obj, 450, 150);
		Feromones::instance()->initialize(530, 270);
		test = robot110->AntAlgorithm(obj, 250, 50);
		//drawObjects(ModelOFEnvironment::Collision::instance()->getObjects());

		/*
		for (int i = 0; i < 100; i++)
		{
			textBox1->Text += System::Convert::ToString(chooseWay(50, 50, 450, 200));
		}*/
		
		//test = robot001.Move(2, 50);
		textBox1->Text += System::Convert::ToString(test);
		


		//*objects = Collision::instance()->getObjects();

		//drawObjects(ModelOFEnvironment::Collision::instance()->getObjects());
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		drawObjects(ModelOFEnvironment::Collision::instance()->getObjects());
	}
};
}
