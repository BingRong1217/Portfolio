#pragma once

#include <msclr\marshal_cppstd.h>

#include "serverFuncs.h"

namespace server {

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
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ tcpPort;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ serverStatus;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ nConnections;
	private: System::Windows::Forms::Label^ label3;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tcpPort = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->serverStatus = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->nConnections = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(51, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(148, 23);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Listen TCP Port";
			// 
			// tcpPort
			// 
			this->tcpPort->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tcpPort->Location = System::Drawing::Point(55, 82);
			this->tcpPort->Name = L"tcpPort";
			this->tcpPort->Size = System::Drawing::Size(98, 30);
			this->tcpPort->TabIndex = 1;
			this->tcpPort->Text = L"7000";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(51, 172);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 23);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Server Status";
			// 
			// serverStatus
			// 
			this->serverStatus->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->serverStatus->Location = System::Drawing::Point(55, 198);
			this->serverStatus->Multiline = true;
			this->serverStatus->Name = L"serverStatus";
			this->serverStatus->ReadOnly = true;
			this->serverStatus->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->serverStatus->Size = System::Drawing::Size(793, 312);
			this->serverStatus->TabIndex = 3;
			this->serverStatus->TextChanged += gcnew System::EventHandler(this, &MyForm::serverStatus_TextChanged);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(295, 75);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(82, 36);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::start_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(405, 75);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(82, 36);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::stop_Click);
			// 
			// nConnections
			// 
			this->nConnections->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nConnections->Location = System::Drawing::Point(648, 82);
			this->nConnections->Name = L"nConnections";
			this->nConnections->ReadOnly = true;
			this->nConnections->Size = System::Drawing::Size(98, 30);
			this->nConnections->TabIndex = 7;
			this->nConnections->Text = L"0";
			this->nConnections->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(644, 47);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(207, 23);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Number of Connections";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(921, 570);
			this->Controls->Add(this->nConnections);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->serverStatus);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tcpPort);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"Socket Server";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void start_Click(System::Object^ sender, System::EventArgs^ e) {
		int port = System::Convert::ToInt32(tcpPort->Text);

		server_start(port);
	}

	private: System::Void stop_Click(System::Object^ sender, System::EventArgs^ e) {
		int port = System::Convert::ToInt32(tcpPort->Text);

		server_stop(port);
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		std::string msg;
		int num;
		bool isServerStarted;
		bool rcv_status = server_status(num, msg, isServerStarted);

		nConnections->Text = num.ToString();

		if (isServerStarted) {
			button1->ForeColor = Color::Gray;	// highlight "Start" Button
			button2->ForeColor = Color::Black;
		}
		else {
			button1->ForeColor = Color::Black;
			button2->ForeColor = Color::Gray;	// highlight "Stop" Button
		}

		if (rcv_status) {
			System::String^ myString = msclr::interop::marshal_as<System::String^>(msg);
			myString = myString->Replace("\n", Environment::NewLine);
			serverStatus->Text += myString;
			serverStatus->SelectionStart = serverStatus->TextLength;
			serverStatus->ScrollToCaret();
		}
	}

private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void serverStatus_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
