#include <Windows.h>
#include <time.h>
#include<cstdlib>
#include"MyForm.h"
#include"MyForm1.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
//створення ігрової форми та її функцій
ref class GameForm : public Form
{
private:
   // std::vector<int> a;
    int boardSize;
    const int cellSize = 40;
    bool* boardAI;
    bool* boardPlayer;
    bool isPlayerRed;

    bool isTwoPlayerMode;

public:
    GameForm(int size, bool twoPlayerMode)
    {
        boardSize = size;
        boardAI = new bool[boardSize * boardSize];
        boardPlayer = new bool[boardSize * boardSize];
        ClearBoards();
        this->ClientSize = Drawing::Size(boardSize * cellSize, boardSize * cellSize);
        this->Text = "П'ять у ряд";
        isPlayerRed = true;
        isTwoPlayerMode = twoPlayerMode;

        this->Paint += gcnew PaintEventHandler(this, &GameForm::OnPaint);
        this->MouseDown += gcnew MouseEventHandler(this, &GameForm::OnMouseDown);

        
        this->BackColor = Color::White;
    }


    ~GameForm()
    {
        delete[] boardAI;
        delete[] boardPlayer;
    }

private:
    //малювання об'єктів
    void OnPaint(Object^ sender, PaintEventArgs^ e)
    {
        Graphics^ g = e->Graphics;

        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                int x = i * cellSize;
                int y = j * cellSize;

                if (boardAI[i + j * boardSize])
                {
                    // Малюємо нолик
                    g->DrawEllipse(Pens::Blue, x, y, cellSize, cellSize);
                }
                else if (boardPlayer[i + j * boardSize])
                {
                    // Малюємо хрестик
                    g->DrawLine(Pens::Red, x, y, x + cellSize, y + cellSize);
                    g->DrawLine(Pens::Red, x + cellSize, y, x, y + cellSize);
                }
                else
                {
                    // Малюємо пусту клітинку
                    g->FillEllipse(Brushes::Gray, x, y, cellSize, cellSize);
                }
            }
        }
    }
    //обробка кліку миші
    void OnMouseDown(Object^ sender, MouseEventArgs^ e)
    {
        int i = e->X / cellSize;
        int j = e->Y / cellSize;

        if (i >= 0 && i < boardSize && j >= 0 && j < boardSize)
        {
            int index = i + j * boardSize;

            if (boardAI[index] || boardPlayer[index])
                return;

            if (isPlayerRed)
            {
                boardPlayer[index] = true;
            }
            else if (isTwoPlayerMode)
            {
                boardAI[index] = true;
            }
            this->Invalidate();

            if (CheckWin(i, j))
            {
                if (isPlayerRed)
                    MessageBox::Show("Перемога червоного гравця!");
                else if (isTwoPlayerMode)
                    MessageBox::Show("Перемога зеленого гравця!");
                else
                    MessageBox::Show("Перемога синього гравця!");

                ClearBoards();
            }
            else if (CheckDraw())
            {
                MessageBox::Show("Гра закінчилася нічиєю!");
                ClearBoards();
            }
            else
            {
                isPlayerRed = !isPlayerRed;
                if (!isPlayerRed && !isTwoPlayerMode)
                {
                    MakeAIMove();
                }
            }
        }
    }
    //перевірка на перемогу
    bool CheckWin(int i, int j)
    {
        int count = 0;
        for (int k = 0; k < boardSize; k++)
        {
            if (boardAI[k + j * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;
        }

        count = 0;
        for (int k = 0; k < boardSize; k++)
        {
            if (boardAI[i + k * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;
        }

        count = 0;
        int startRow = i - min(i, j);
        int startCol = j - min(i, j);
        while (startRow < boardSize && startCol < boardSize)
        {
            if (boardAI[startRow + startCol * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;

            startRow++;
            startCol++;
        }

        count = 0;
        startRow = i + min(boardSize - i - 1, j);
        startCol = j - min(boardSize - i - 1, j);
        while (startRow >= 0 && startCol < boardSize)
        {
            if (boardAI[startRow + startCol * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;

            startRow--;
            startCol++;
        }

        count = 0;
        for (int k = 0; k < boardSize; k++)
        {
            if (boardPlayer[k + j * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;
        }

        count = 0;
        for (int k = 0; k < boardSize; k++)
        {
            if (boardPlayer[i + k * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;
        }

        count = 0;
        startRow = i - min(i, j);
        startCol = j - min(i, j);
        while (startRow < boardSize && startCol < boardSize)
        {
            if (boardPlayer[startRow + startCol * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;

            startRow++;
            startCol++;
        }

        count = 0;
        startRow = i + min(boardSize - i - 1, j);
        startCol = j - min(boardSize - i - 1, j);
        while (startRow >= 0 && startCol < boardSize)
        {
            if (boardPlayer[startRow + startCol * boardSize])
                count++;
            else
                count = 0;

            if (count == 5)
                return true;

            startRow--;
            startCol++;
        }

        return false;
    }
    //перевірка на нічию,не використовуються бо шанс нічиєї майже рівен нулю
    bool CheckDraw()
    {
        for (int i = 0; i < boardSize * boardSize; i++)
        {
            if (!boardAI[i] && !boardPlayer[i])
                return false;
        }

        int aiCount = 0;
        int playerCount = 0;
        for (int i = 0; i < boardSize * boardSize; i++)
        {
            if (boardAI[i])
                aiCount++;
            if (boardPlayer[i])
                playerCount++;
        }

        return (aiCount == 5 && playerCount == 5);
    }
    //логіка ходу штучного інтелекту
    void MakeAIMove()
    {
        int index = MiniMax();
        boardAI[index] = true;
        this->Invalidate();

        int aiRow = index % boardSize;
        int aiCol = index / boardSize;

        if (CheckWin(aiRow, aiCol))
        {
            MessageBox::Show("AI Wins!");
            ClearBoards();
        }
        else
        {
            isPlayerRed = !isPlayerRed;
        }
    }
    //логіка алгоритму штучного інтелекту 
    int MiniMax()
    {
        int bestScore = -1000;
        int bestMove = -1;
        for (int i = 0; i < boardSize * boardSize; i++)
        {
            if (!boardAI[i] && !boardPlayer[i])
            {
                boardAI[i] = true;
                int score = Mini(boardPlayer, boardAI, 0, false);
                boardAI[i] = false;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
        return bestMove;
    }

    int Mini(bool* playerBoard, bool* aiBoard, int depth, bool isMax)
    {
        if (CheckWin(boardSize, boardSize) || depth == 3)
        {
            return Evaluate(playerBoard, aiBoard);
        }

        if (isMax)
        {
            int bestScore = -1000;
            for (int i = 0; i < boardSize * boardSize; i++)
            {
                if (!playerBoard[i] && !aiBoard[i])
                {
                    aiBoard[i] = true;
                    int score = Mini(playerBoard, aiBoard, depth + 1, false);
                    aiBoard[i] = false;
                    bestScore = max(bestScore, score);
                }
            }
            return bestScore;
        }
        else
        {
            int bestScore = 1000;
            for (int i = 0; i < boardSize * boardSize; i++)
            {
                if (!playerBoard[i] && !aiBoard[i])
                {
                    playerBoard[i] = true;
                    int score = Mini(playerBoard, aiBoard, depth + 1, true);
                    playerBoard[i] = false;
                    bestScore = min(bestScore, score);
                }
            }
            return bestScore;
        }
    }

    int Evaluate(bool* playerBoard, bool* aiBoard)
    {
        int aiScore = 0;
        int playerScore = 0;

        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                int index = i + j * boardSize;

                // Check horizontal
                if (i < boardSize - 4)
                {
                    int aiCount = 0;
                    int playerCount = 0;
                    for (int k = 0; k < 5; k++)
                    {
                        if (aiBoard[index + k])
                            aiCount++;
                        if (playerBoard[index + k])
                            playerCount++;
                    }
                    aiScore += GetScore(aiCount, playerCount);
                    playerScore += GetScore(playerCount, aiCount);
                }

                // Check vertical
                if (j < boardSize - 4)
                {
                    int aiCount = 0;
                    int playerCount = 0;
                    for (int k = 0; k < 5; k++)
                    {
                        if (aiBoard[index + k * boardSize])
                            aiCount++;
                        if (playerBoard[index + k * boardSize])
                            playerCount++;
                    }
                    aiScore += GetScore(aiCount, playerCount);
                    playerScore += GetScore(playerCount, aiCount);
                }

                // Check diagonal (top-left to bottom-right)
                if (i < boardSize - 4 && j < boardSize - 4)
                {
                    int aiCount = 0;
                    int playerCount = 0;
                    for (int k = 0; k < 5; k++)
                    {
                        if (aiBoard[index + k + k * boardSize])
                            aiCount++;
                        if (playerBoard[index + k + k * boardSize])
                            playerCount++;
                    }
                    aiScore += GetScore(aiCount, playerCount);
                    playerScore += GetScore(playerCount, aiCount);
                }

                // Check diagonal (top-right to bottom-left)
                if (i >= 4 && j < boardSize - 4)
                {
                    int aiCount = 0;
                    int playerCount = 0;
                    for (int k = 0; k < 5; k++)
                    {
                        if (aiBoard[index - k + k * boardSize])
                            aiCount++;
                        if (playerBoard[index - k + k * boardSize])
                            playerCount++;
                    }
                    aiScore += GetScore(aiCount, playerCount);
                    playerScore += GetScore(playerCount, aiCount);
                }
            }
        }

        return aiScore - playerScore;
    }

    int GetScore(int aiCount, int playerCount)
    {
        if (aiCount == 5)
            return 100;
        else if (aiCount == 4 && playerCount == 0)
            return 10;
        else if (aiCount == 3 && playerCount == 0)
            return 5;
        else if (aiCount == 2 && playerCount == 0)
            return 2;

        if (playerCount == 5)
            return -100;
        else if (playerCount == 4 && aiCount == 0)
            return -10;
        else if (playerCount == 3 && aiCount == 0)
            return -5;
        else if (playerCount == 2 && aiCount == 0)
            return -2;

        return 0;
    }

    void ClearBoards()
    {
        for (int i = 0; i < boardSize * boardSize; i++)
        {
            boardAI[i] = false;
            boardPlayer[i] = false;
        }

        isPlayerRed = true;
        this->Invalidate();
    }
};
//створення початкової форми та її функцій
ref class StartForm : public Form
{
private:
    ComboBox^ gameModeComboBox;
    ComboBox^ boardSizeComboBox;
    ComboBox^ colorComboBox; 
    Button^ startButton;
    GameForm^ gameForm;

public:
    StartForm()
    {
        this->ClientSize = Drawing::Size(250, 200);
        this->Text = "Start Form";

        gameModeComboBox = gcnew ComboBox();
        gameModeComboBox->Location = Drawing::Point(20, 20);
        gameModeComboBox->Size = Drawing::Size(200, 20);
        gameModeComboBox->Items->Add("Player vs. AI");
        gameModeComboBox->Items->Add("Player vs. Player");
        gameModeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnGameModeChanged);
        this->Controls->Add(gameModeComboBox);

        boardSizeComboBox = gcnew ComboBox();
        boardSizeComboBox->Location = Drawing::Point(20, 60);
        boardSizeComboBox->Size = Drawing::Size(200, 20);
        boardSizeComboBox->Items->Add("10x10");
        boardSizeComboBox->Items->Add("15x15");
        boardSizeComboBox->Items->Add("20x20");
        boardSizeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnBoardSizeChanged);
        this->Controls->Add(boardSizeComboBox);

        colorComboBox = gcnew ComboBox();  
        colorComboBox->Location = Drawing::Point(20, 100);
        colorComboBox->Size = Drawing::Size(200, 20);
        colorComboBox->Items->Add("Black");
        colorComboBox->Items->Add("White");
        colorComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnColorChanged);
        this->Controls->Add(colorComboBox);

        startButton = gcnew Button();
        startButton->Location = Drawing::Point(20, 140);
        startButton->Size = Drawing::Size(200, 30);
        startButton->Text = "Start Game";
        startButton->Enabled = false;
        startButton->Click += gcnew EventHandler(this, &StartForm::OnStartButtonClick);
        this->Controls->Add(startButton);
    }
    //вибір режиму гри
    void OnGameModeChanged(Object^ sender, EventArgs^ e)
    {
        if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
        {
            startButton->Enabled = true;
        }
        else
        {
            startButton->Enabled = false;
        }
    }
    //зміна розміру поля
    void OnBoardSizeChanged(Object^ sender, EventArgs^ e)
    {
        if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
        {
            startButton->Enabled = true;
        }
        else
        {
            startButton->Enabled = false;
        }
    }
    //зміна теми гри
    void OnColorChanged(Object^ sender, EventArgs^ e)
    {
        if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
        {
            startButton->Enabled = true;
        }
        else
        {
            startButton->Enabled = false;
        }
    }
    //події при натисканні на кнопку
    void OnStartButtonClick(Object^ sender, EventArgs^ e)
    {
        int boardSize = 0;
        if (boardSizeComboBox->SelectedIndex == 0)
        {
            boardSize = 10;
        }
        else if (boardSizeComboBox->SelectedIndex == 1)
        {
            boardSize = 15;
        }
        else if (boardSizeComboBox->SelectedIndex == 2)
        {
            boardSize = 20;
        }

        bool twoPlayerMode = (gameModeComboBox->SelectedIndex == 1);

        gameForm = gcnew GameForm(boardSize, twoPlayerMode);

        if (colorComboBox->SelectedIndex == 0)
        {
            gameForm->BackColor = Drawing::Color::Black;
        }
        else if (colorComboBox->SelectedIndex == 1)
        {
            gameForm->BackColor = Drawing::Color::White;
        }

        gameForm->Show();
    }
};

int main()
{
    srand(time(NULL));

    Application::EnableVisualStyles();
    Application::Run(gcnew StartForm());

    return 0;
}


















