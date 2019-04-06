#pragma once
#include "MainForm.h"
#include "MessageControl.h"

namespace ChatTest1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NameForm
	/// </summary>
	public ref class NameForm : public System::Windows::Forms::Form
	{
	public:
		NameForm(void)
		{
			InitializeComponent();
			messageControl = new MessageControl();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NameForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		MessageControl *messageControl;
		System::Windows::Forms::Label^  labelName;
		System::Windows::Forms::TextBox^  nameInput;
		System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Label^  labelInfo;
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
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->nameInput = (gcnew System::Windows::Forms::TextBox());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->labelInfo = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// labelName
			// 
			this->labelName->AutoSize = true;
			this->labelName->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelName->Location = System::Drawing::Point(12, 9);
			this->labelName->Name = L"labelName";
			this->labelName->Size = System::Drawing::Size(129, 28);
			this->labelName->TabIndex = 0;
			this->labelName->Text = L"Your name";
			// 
			// nameInput
			// 
			this->nameInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->nameInput->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameInput->Location = System::Drawing::Point(17, 40);
			this->nameInput->MaxLength = 127;
			this->nameInput->Name = L"nameInput";
			this->nameInput->Size = System::Drawing::Size(253, 34);
			this->nameInput->TabIndex = 1;
			// 
			// buttonOK
			// 
			this->buttonOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonOK->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonOK->Location = System::Drawing::Point(171, 80);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(99, 36);
			this->buttonOK->TabIndex = 2;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &NameForm::buttonOK_Click);
			// 
			// labelInfo
			// 
			this->labelInfo->AutoSize = true;
			this->labelInfo->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelInfo->Location = System::Drawing::Point(14, 80);
			this->labelInfo->Name = L"labelInfo";
			this->labelInfo->Size = System::Drawing::Size(0, 28);
			this->labelInfo->TabIndex = 3;
			// 
			// NameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 123);
			this->Controls->Add(this->labelInfo);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->nameInput);
			this->Controls->Add(this->labelName);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"NameForm";
			this->Text = L"Ybhoo messenger";
			this->Closed += gcnew System::EventHandler(this, &NameForm::NameForm_Close);
			this->Load += gcnew System::EventHandler(this, &NameForm::NameForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
			String^ name = nameInput->Text;
			if (name->Length < 1 || name->Length > 127) name = "Bunny";
			messageControl->sendMessage(getSTDString(name), "/VERIFY");
			std::string msg = messageControl->receiveMessage();
			int msglen = msg.length();
			if (msglen < 4) {
				labelInfo->Text = "Bad name!";
			} else {
				ChatTest1::MainForm mainForm(messageControl);
				mainForm.setName(name);
				this->Hide();
				mainForm.ShowDialog();
			}
		}
		System::Void NameForm_Load(System::Object^  sender, System::EventArgs^  e) {
			buttonOK->Enabled = false;
			std::string connectStatus = messageControl->connectToServer();
			if (connectStatus == "Connected.\n") {
				buttonOK->Enabled = true;
			}
		}
		System::Void NameForm_Close(System::Object^  sender, System::EventArgs^  e) {
			exit(0);
		}
		std::string getSTDString(String ^s) {
			return msclr::interop::marshal_as<std::string>(s);
		}
		String^ getManagedString(std::string s) {
			return gcnew String(s.c_str());
		}
	};
}
