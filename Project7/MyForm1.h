//#pragma once
//#include"MyForm.h"
//namespace Project7 {
//
//	using namespace System;
//	using namespace System::ComponentModel;
//	using namespace System::Collections;
//	using namespace System::Windows::Forms;
//	using namespace System::Data;
//	using namespace System::Drawing;
//
//	/// <summary>
//	/// Сводка для MyForm1
//	/// </summary>
//    ref class StartForm : public Form
//    {
//    private:
//        ComboBox^ gameModeComboBox;
//        ComboBox^ boardSizeComboBox;
//        ComboBox^ colorComboBox;
//        Button^ startButton;
//        GameForm^ gameForm;
//
//    public:
//        StartForm()
//        {
//            this->ClientSize = Drawing::Size(250, 200);
//            this->Text = "Start Form";
//
//            gameModeComboBox = gcnew ComboBox();
//            gameModeComboBox->Location = Drawing::Point(20, 20);
//            gameModeComboBox->Size = Drawing::Size(200, 20);
//            gameModeComboBox->Items->Add("Player vs. AI");
//            gameModeComboBox->Items->Add("Player vs. Player");
//            gameModeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnGameModeChanged);
//            this->Controls->Add(gameModeComboBox);
//
//            boardSizeComboBox = gcnew ComboBox();
//            boardSizeComboBox->Location = Drawing::Point(20, 60);
//            boardSizeComboBox->Size = Drawing::Size(200, 20);
//            boardSizeComboBox->Items->Add("10x10");
//            boardSizeComboBox->Items->Add("15x15");
//            boardSizeComboBox->Items->Add("20x20");
//            boardSizeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnBoardSizeChanged);
//            this->Controls->Add(boardSizeComboBox);
//
//            colorComboBox = gcnew ComboBox();
//            colorComboBox->Location = Drawing::Point(20, 100);
//            colorComboBox->Size = Drawing::Size(200, 20);
//            colorComboBox->Items->Add("Black");
//            colorComboBox->Items->Add("White");
//            colorComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnColorChanged);
//            this->Controls->Add(colorComboBox);
//
//            startButton = gcnew Button();
//            startButton->Location = Drawing::Point(20, 140);
//            startButton->Size = Drawing::Size(200, 30);
//            startButton->Text = "Start Game";
//            startButton->Enabled = false;
//            startButton->Click += gcnew EventHandler(this, &StartForm::OnStartButtonClick);
//            this->Controls->Add(startButton);
//        }
//        //вибір режиму гри
//        void OnGameModeChanged(Object^ sender, EventArgs^ e)
//        {
//            if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
//            {
//                startButton->Enabled = true;
//            }
//            else
//            {
//                startButton->Enabled = false;
//            }
//        }
//        //зміна розміру поля
//        void OnBoardSizeChanged(Object^ sender, EventArgs^ e)
//        {
//            if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
//            {
//                startButton->Enabled = true;
//            }
//            else
//            {
//                startButton->Enabled = false;
//            }
//        }
//        //зміна теми гри
//        void OnColorChanged(Object^ sender, EventArgs^ e)
//        {
//            if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
//            {
//                startButton->Enabled = true;
//            }
//            else
//            {
//                startButton->Enabled = false;
//            }
//        }
//        //події при натисканні на кнопку
//        void OnStartButtonClick(Object^ sender, EventArgs^ e)
//        {
//            int boardSize = 0;
//            if (boardSizeComboBox->SelectedIndex == 0)
//            {
//                boardSize = 10;
//            }
//            else if (boardSizeComboBox->SelectedIndex == 1)
//            {
//                boardSize = 15;
//            }
//            else if (boardSizeComboBox->SelectedIndex == 2)
//            {
//                boardSize = 20;
//            }
//
//            bool twoPlayerMode = (gameModeComboBox->SelectedIndex == 1);
//
//            gameForm = gcnew GameForm(boardSize, twoPlayerMode);
//
//            if (colorComboBox->SelectedIndex == 0)
//            {
//                gameForm->BackColor = Drawing::Color::Black;
//            }
//            else if (colorComboBox->SelectedIndex == 1)
//            {
//                gameForm->BackColor = Drawing::Color::White;
//            }
//
//            gameForm->Show();
//        }
//    private: System::Void InitializeComponent() {
//        this->SuspendLayout();
//        // 
//        // StartForm
//        // 
//        this->ClientSize = System::Drawing::Size(282, 253);
//        this->Name = L"StartForm";
//        this->Load += gcnew System::EventHandler(this, &StartForm::StartForm_Load);
//        this->ResumeLayout(false);
//    }
//private: System::Void StartForm_Load(System::Object^ sender, System::EventArgs^ e) {
//    }
//};
//}
