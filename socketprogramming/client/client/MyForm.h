#pragma once


#include <msclr\marshal_cppstd.h>

#include "clientFuncs.h"

namespace Client {

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
	private: System::Windows::Forms::TextBox^ hostIP;
	private: System::Windows::Forms::TextBox^ tcpPort;
	protected:

	protected:

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ msgSnd;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ msgRcv;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ ConStatus;

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;





	protected:


	protected:



	protected:

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
			this->hostIP = (gcnew System::Windows::Forms::TextBox());
			this->tcpPort = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->msgSnd = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->msgRcv = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ConStatus = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// hostIP
			// 
			this->hostIP->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hostIP->Location = System::Drawing::Point(68, 94);
			this->hostIP->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->hostIP->Name = L"hostIP";
			this->hostIP->Size = System::Drawing::Size(136, 30);
			this->hostIP->TabIndex = 0;
			this->hostIP->Text = L"127.0.0.1";
			// 
			// tcpPort
			// 
			this->tcpPort->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tcpPort->Location = System::Drawing::Point(261, 94);
			this->tcpPort->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->tcpPort->Name = L"tcpPort";
			this->tcpPort->Size = System::Drawing::Size(68, 30);
			this->tcpPort->TabIndex = 1;
			this->tcpPort->Text = L"7000";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(66, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 23);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Server IP";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(260, 60);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 23);
			this->label2->TabIndex = 3;
			this->label2->Text = L"TCP Port";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(441, 42);
			this->button1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(118, 42);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::connect_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Control;
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
			this->button2->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button2->Location = System::Drawing::Point(441, 108);
			this->button2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(118, 42);
			this->button2->TabIndex = 5;
			this->button2->Text = L"DisConnect";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::disconnect_Click);
			// 
			// msgSnd
			// 
			this->msgSnd->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msgSnd->Location = System::Drawing::Point(68, 202);
			this->msgSnd->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->msgSnd->Name = L"msgSnd";
			this->msgSnd->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->msgSnd->Size = System::Drawing::Size(823, 30);
			this->msgSnd->TabIndex = 6;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(65, 173);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(130, 23);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Message Send";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(65, 257);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(157, 23);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Message Receive";
			// 
			// msgRcv
			// 
			this->msgRcv->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msgRcv->Location = System::Drawing::Point(68, 280);
			this->msgRcv->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->msgRcv->Multiline = true;
			this->msgRcv->Name = L"msgRcv";
			this->msgRcv->ReadOnly = true;
			this->msgRcv->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->msgRcv->Size = System::Drawing::Size(937, 252);
			this->msgRcv->TabIndex = 8;
			this->msgRcv->TextChanged += gcnew System::EventHandler(this, &MyForm::msgRcv_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(626, 16);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(163, 23);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Connection Status";
			// 
			// ConStatus
			// 
			this->ConStatus->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ConStatus->Location = System::Drawing::Point(629, 42);
			this->ConStatus->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->ConStatus->Multiline = true;
			this->ConStatus->Name = L"ConStatus";
			this->ConStatus->ReadOnly = true;
			this->ConStatus->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->ConStatus->Size = System::Drawing::Size(376, 116);
			this->ConStatus->TabIndex = 10;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Control;
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
			this->button3->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button3->Location = System::Drawing::Point(918, 196);
			this->button3->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(87, 42);
			this->button3->TabIndex = 12;
			this->button3->Text = L"Send";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::send_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1066, 564);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->ConStatus);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->msgRcv);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->msgSnd);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tcpPort);
			this->Controls->Add(this->hostIP);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MyForm";
			this->Text = L"Socket Client";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void splitContainer1_Panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void connect_Click(System::Object^ sender, System::EventArgs^ e) {
		int port = System::Convert::ToInt32(tcpPort->Text);
		msclr::interop::marshal_context context;
		std::string host = context.marshal_as<std::string>(hostIP->Text);
		std::string errormsg;

		bool status = tcp_connect(host, port, errormsg);

		ConStatus->Text += ">> ";
		ConStatus->Text += gcnew System::String(errormsg.c_str());;
		ConStatus->Text += Environment::NewLine;

		ConStatus->SelectionStart = ConStatus->TextLength;
		ConStatus->ScrollToCaret();

	}
	private: System::Void disconnect_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string errormsg;
		tcp_disconnect(errormsg);
		ConStatus->Text += ">> ";
		ConStatus->Text += gcnew System::String(errormsg.c_str());;
		ConStatus->Text += Environment::NewLine;
		ConStatus->SelectionStart = ConStatus->TextLength;
		ConStatus->ScrollToCaret();
	}
	private: System::Void send_Click(System::Object^ sender, System::EventArgs^ e) {
		msclr::interop::marshal_context context;
		std::string msg = context.marshal_as<std::string>(msgSnd->Text);
		std::string errormsg;
		tcp_send(msg, errormsg);
		ConStatus->Text += ">> ";
		ConStatus->Text += gcnew System::String(errormsg.c_str());;
		ConStatus->Text += Environment::NewLine;
		ConStatus->SelectionStart = ConStatus->TextLength;
		ConStatus->ScrollToCaret();

		msgSnd->Text = "";	// clear msg field
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		std::string msg;
		std::string errormsg;
		bool isConnected = tcp_status();
		bool rcv_status = tcp_recv(msg, errormsg);

		if (isConnected) {
			button1->ForeColor = Color::Gray;	// highlight "Connect" Button
			button2->ForeColor = Color::Black;
		}
		else {
			button1->ForeColor = Color::Black;
			button2->ForeColor = Color::Gray;	// highlight "DisConnect" Button
		}

		if (rcv_status) {
			msgRcv->Text += gcnew System::String(msg.c_str());;
			msgRcv->Text += Environment::NewLine;

			msgRcv->SelectionStart = msgRcv->TextLength;
			msgRcv->ScrollToCaret();
		}
		else {
			if (errormsg.size() > 0) {
				ConStatus->Text += ">> ";
				ConStatus->Text += gcnew System::String(errormsg.c_str());;
				ConStatus->Text += Environment::NewLine;
				ConStatus->SelectionStart = ConStatus->TextLength;
				ConStatus->ScrollToCaret();
			}
		}
	}
private: System::Void msgRcv_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
