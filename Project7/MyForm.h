//#pragma once
//
//namespace Project7 {
//
//	using namespace System;
//	using namespace System::ComponentModel;
//	using namespace System::Collections;
//	using namespace System::Windows::Forms;
//	using namespace System::Data;
//	using namespace System::Drawing;
//
//    ref class GameForm : public Form
//    {
//    private:
//        // std::vector<int> a;
//        int boardSize;
//        const int cellSize = 40;
//        bool* boardAI;
//        bool* boardPlayer;
//        bool isPlayerRed;
//
//        bool isTwoPlayerMode;
//
//    public:
//        GameForm(int size, bool twoPlayerMode)
//        {
//            boardSize = size;
//            boardAI = new bool[boardSize * boardSize];
//            boardPlayer = new bool[boardSize * boardSize];
//            ClearBoards();
//            this->ClientSize = Drawing::Size(boardSize * cellSize, boardSize * cellSize);
//            this->Text = "П'ять у ряд";
//            isPlayerRed = true;
//            isTwoPlayerMode = twoPlayerMode;
//
//            this->Paint += gcnew PaintEventHandler(this, &GameForm::OnPaint);
//            this->MouseDown += gcnew MouseEventHandler(this, &GameForm::OnMouseDown);
//
//
//            this->BackColor = Color::White;
//        }
//
//
//        ~GameForm()
//        {
//            delete[] boardAI;
//            delete[] boardPlayer;
//        }
//        void ClearBoards()
//        {
//            for (int i = 0; i < boardSize * boardSize; i++)
//            {
//                boardAI[i] = false;
//                boardPlayer[i] = false;
//            }
//
//            isPlayerRed = true;
//            this->Invalidate();
//        }
//    private:
//        //малювання об'єктів
//        void OnPaint(Object^ sender, PaintEventArgs^ e)
//        {
//            Graphics^ g = e->Graphics;
//
//            for (int i = 0; i < boardSize; i++)
//            {
//                for (int j = 0; j < boardSize; j++)
//                {
//                    int x = i * cellSize;
//                    int y = j * cellSize;
//
//                    if (boardAI[i + j * boardSize])
//                    {
//                        // Малюємо нолик
//                        g->DrawEllipse(Pens::Blue, x, y, cellSize, cellSize);
//                    }
//                    else if (boardPlayer[i + j * boardSize])
//                    {
//                        // Малюємо хрестик
//                        g->DrawLine(Pens::Red, x, y, x + cellSize, y + cellSize);
//                        g->DrawLine(Pens::Red, x + cellSize, y, x, y + cellSize);
//                    }
//                    else
//                    {
//                        // Малюємо пусту клітинку
//                        g->FillEllipse(Brushes::Gray, x, y, cellSize, cellSize);
//                    }
//                }
//            }
//
//        }
//    private: System::Void InitializeComponent() {
//        this->SuspendLayout();
//        // 
//        // GameForm
//        // 
//        this->ClientSize = System::Drawing::Size(282, 253);
//        this->Name = L"GameForm";
//        this->Load += gcnew System::EventHandler(this, &GameForm::GameForm_Load);
//        this->ResumeLayout(false);
//    }
//    private: System::Void GameForm_Load(System::Object^ sender, System::EventArgs^ e) {
//    }
//    };
//}
