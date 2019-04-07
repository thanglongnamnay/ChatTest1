#pragma once
#include "MessageControl.h"
namespace ChatTest1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(MessageControl *mc)
		{
			InitializeComponent();
			messageControl = mc;
		}
		void setName(String^ name) {
			this->name = name;
		}
		void sendMessage() {
			String^ message = this->inputMessage->Text;
			if (message->Length < 1 || message->Length > 511) return;
			messageControl->sendMessage(getSTDString(name), getSTDString(message));
		}
		void receiveMessage() {
			while (1) {
				std::string rm = messageControl->receiveMessage();
				message = getManagedString(rm);
				appendText();
			}
		}
		void appendText() {
			if (messageList->InvokeRequired) {
				appendTextCallback^ d = gcnew appendTextCallback(this, &MainForm::appendText);
				this->Invoke(d);
			} else {
				this->messageList->AppendText(message);
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: 
		delegate void appendTextCallback();
		String^ message = "";
		String^ name = "VC++";
		MessageControl* messageControl;
		System::Windows::Forms::RichTextBox^  messageList;
		System::Windows::Forms::TextBox^  inputMessage;
		System::Windows::Forms::Button^  SendButton;

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
			this->messageList = (gcnew System::Windows::Forms::RichTextBox());
			this->inputMessage = (gcnew System::Windows::Forms::TextBox());
			this->SendButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// messageList
			// 
			this->messageList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->messageList->BackColor = System::Drawing::Color::White;
			this->messageList->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->messageList->CausesValidation = false;
			this->messageList->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->messageList->DetectUrls = false;
			this->messageList->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->messageList->Location = System::Drawing::Point(12, 12);
			this->messageList->Name = L"messageList";
			this->messageList->ReadOnly = true;
			this->messageList->Size = System::Drawing::Size(258, 268);
			this->messageList->TabIndex = 2;
			this->messageList->TabStop = false;
			this->messageList->Text = L"";
			this->messageList->TextChanged += gcnew System::EventHandler(this, &MainForm::messageList_TextChanged);
			// 
			// inputMessage
			// 
			this->inputMessage->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->inputMessage->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->inputMessage->Location = System::Drawing::Point(12, 286);
			this->inputMessage->MaxLength = 511;
			this->inputMessage->Name = L"inputMessage";
			this->inputMessage->Size = System::Drawing::Size(180, 34);
			this->inputMessage->TabIndex = 0;
			this->inputMessage->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::inputMessage_Keyup);
			// 
			// SendButton
			// 
			this->SendButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SendButton->Location = System::Drawing::Point(198, 286);
			this->SendButton->Name = L"SendButton";
			this->SendButton->Size = System::Drawing::Size(72, 34);
			this->SendButton->TabIndex = 2;
			this->SendButton->Text = L"Send";
			this->SendButton->UseVisualStyleBackColor = true;
			this->SendButton->Click += gcnew System::EventHandler(this, &MainForm::SendButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(282, 326);
			this->Controls->Add(this->SendButton);
			this->Controls->Add(this->inputMessage);
			this->Controls->Add(this->messageList);
			this->Name = L"MainForm";
			this->Text = L"Ybhoo Messenger";
			this->Closed += gcnew System::EventHandler(this, &MainForm::MainForm_Close);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		System::Void inputMessage_Keyup(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (e->KeyValue == 13)  {
				sendMessage();
				inputMessage->Text = "";
			}
		}
		System::Void SendButton_Click(System::Object^  sender, System::EventArgs^  e) {
			sendMessage();
			inputMessage->Text = "";
		}
		std::string getSTDString(String ^s) {
			return msclr::interop::marshal_as<std::string>(s);
		}
		String^ getManagedString(std::string s) {
			return gcnew String(s.c_str());
		}
		System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
			Thread^ receiveThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::receiveMessage));
			receiveThread->Start();
		}
		System::Void MainForm_Close(System::Object^  sender, System::EventArgs^  e) {
			messageControl->closeSocket();
			exit(0);
		}
	private: System::Void messageList_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
