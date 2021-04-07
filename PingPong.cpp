//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mmsystem.h"
#include "PingPong.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TGame *Game;

//---------------------------------------------------------------------------
__fastcall TGame::TGame(TComponent* Owner)
        : TForm(Owner)
{
    racketSpeed = 10;
}
//---------------------------------------------------------------------------

void TGame::displayRoundSummary()
{
// Procedura wyswietlajaca podsumowanie rundy.
    NewGameButton->Visible = true;
    NewRoundButton->Visible = true;
    WinnerPointer->Visible = true;
    Settings->Enabled = true;
    ScoreBoard->Caption = IntToStr( leftPlayerPoints ) + " : " + IntToStr( rightPlayerPoints );
    ScoreBoard->Visible = true;
    BounceCounter->Caption = "Number of Bounds: " + IntToStr( bounceCounter );
    BounceCounter->Visible = true;
}
//---------------------------------------------------------------------------

void TGame::resetGame()
{
// Procedura resetuj¹ca elementy gry po rundzie.
    roundTime = 0;
    lastBounceTime = 0;
    bounceCounter = 0;
    setInitialElementPosition();
    ballSpeed = checkDifficultyLevel();
    ball_x = randomBallGenerator() * ballSpeed;
    ball_y = randomBallGenerator() * ballSpeed;
    NewRoundButton->Visible = false;
    NewGameButton->Visible = false;
    BounceCounter->Visible = false;
    ScoreBoard->Visible = false;
    WinnerPointer->Visible = false;
    Settings->Enabled = false;
    countingDown();
    Ball->Visible = true;
    BallMovement->Enabled = true;
}
//---------------------------------------------------------------------------

void TGame::setInitialElementPosition()
{
// Procedura ustawiajaca pozycje wszystkich elementow na ekranie gry.
    WelcomeWindow->Top = 50;
    WelcomeWindow->Left = GameBackGround->Width / 2 - WelcomeWindow->Width / 2;
    WinnerPointer->Top = 110;
    WinnerPointer->Left = GameBackGround->Width / 2 - WinnerPointer->Width / 2;
    Counter->Top = 120;
    Counter->Left = GameBackGround->Width / 2 - Counter->Width / 2;
    ScoreBoard->Top = 160;
    ScoreBoard->Left = GameBackGround->Width / 2 - ScoreBoard->Width / 2;
    BounceCounter->Top = 210;
    BounceCounter->Left = GameBackGround->Width / 2 - BounceCounter->Width / 2;
    NewRoundButton->Top = GameBackGround->Height- 200;
    NewRoundButton->Left = GameBackGround->Width / 2 - NewRoundButton->Width / 2;
    NewGameButton->Top = GameBackGround->Height - 100;
    NewGameButton->Left = GameBackGround->Width / 2 - NewGameButton->Width / 2;
    LeftRacket->Left = GameBackGround->Left + 30;
    RightRacket->Left = GameBackGround->Width -  RightRacket->Width - 30;
    LeftRacket->Top = GameBackGround->Height / 2 - Ball->Height / 2;
    RightRacket->Top = GameBackGround->Height / 2 - Ball->Height / 2;
    Ball->Top = GameBackGround->Height / 2 - Ball->Height / 2;
    Ball->Left = GameBackGround->Width / 2 - Ball->Width / 2;
}
//---------------------------------------------------------------------------

void TGame::countingDown()
{
    Counter->Caption = "3";
    Counter->Visible = true;
    PlaySound("BEEP1", HInstance, SND_ASYNC | SND_RESOURCE);
    Application->ProcessMessages();
    Sleep(1000);
    Counter->Caption = "2";
    Application->ProcessMessages();
    Sleep(1000);
    Counter->Caption = "1";
    Application->ProcessMessages();
    Sleep(1000);
    Counter->Visible = false;
}
//---------------------------------------------------------------------------

int TGame::checkDifficultyLevel()
{
    if (Hard->Checked == true)
        return 6;
    else if (Medium->Checked == true)
        return 5;
    else
        return 4;
}
//---------------------------------------------------------------------------

int TGame::randomBallGenerator()
{
// Funkcja generuj¹ca losowy start pi³ki.
    Randomize();
    if (random(2))
        return 1;
    else
        return -1;
}
//---------------------------------------------------------------------------

void TGame::accelerateBounce()
{
    if (ball_x < 0)
        ball_x = abs(ball_x) + 0.5 * ballSpeed;
    else
        ball_x = -(abs(ball_x) + 0.5 * ballSpeed);

    bounceCounter++;
    lastBounceTime = roundTime;
    PlaySound("BOUNCE", HInstance, SND_ASYNC | SND_RESOURCE);
}

void TGame::normalBounce()
{
    if (ball_x < 0)
        ball_x = ballSpeed;
    else
        ball_x = -ballSpeed;

    bounceCounter++;
    lastBounceTime = roundTime;
    PlaySound("BOUNCE", HInstance, SND_ASYNC | SND_RESOURCE);
}
//---------------------------------------------------------------------------

void TGame::gameOver()
{
    BallMovement->Enabled = false;
    Ball->Visible = false;
    leftPlayerPoints++;
    WinnerPointer->Caption = "<<< Left player won this round!!!";
    displayRoundSummary();
    PlaySound("GAMEOVER", HInstance, SND_ASYNC | SND_RESOURCE);
}
//---------------------------------------------------------------------------

void __fastcall TGame::LeftRacketUpTimer(TObject *Sender)
{
// Funckja odpowiadajaca za ruch w górê lewej paletki.
    if (LeftRacket->Top > 0)
        LeftRacket->Top -= racketSpeed;
}
//---------------------------------------------------------------------------

void __fastcall TGame::LeftRacketDownTimer(TObject *Sender)
{
// Funckja odpowiadajaca za ruch w dó³ lewej paletki.
    if (LeftRacket->Top + LeftRacket->Height < GameBackGround->Height)
        LeftRacket->Top += racketSpeed;
}
//---------------------------------------------------------------------------

void __fastcall TGame::RightRacketUpTimer(TObject *Sender)
{
// Funckja odpowiadajaca za ruch w górê prawej paletki.
    if (RightRacket->Top > 0)
        RightRacket->Top -= racketSpeed;
}
//---------------------------------------------------------------------------

void __fastcall TGame::RightRacketDownTimer(TObject *Sender)
{
// Funckja odpowiadajaca za ruch w dó³ prawej paletki.
    if (RightRacket->Top + RightRacket->Height < GameBackGround->Height)
        RightRacket->Top += racketSpeed;
}
//---------------------------------------------------------------------------

void __fastcall TGame::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
// Funkcja odpowiadaj¹ca za sterowanie paletkami przy wcisnieciu klawisza A,Z(lewej) lub Up,Down(prawej).
    if (Key == 0x41)
        LeftRacketUp->Enabled = true;
    if (Key == 0x5A)
        LeftRacketDown->Enabled = true;

    if (Key == VK_UP)
        RightRacketUp->Enabled = true;
    if (Key == VK_DOWN)
        RightRacketDown->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TGame::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
// Funkcja odpowiadaj¹ca za sterowanie paletkami przy puszczeniu klawisza A,Z(lewej) lub Up,Down(prawej).
    if (Key == 0x41)
        LeftRacketUp->Enabled = false;
    if (Key == 0x5A)
        LeftRacketDown->Enabled = false;

    if (Key == VK_UP)
        RightRacketUp->Enabled = false;
    if (Key == VK_DOWN)
        RightRacketDown->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TGame::BallMovementTimer(TObject *Sender)
{
    roundTime += BallMovement->Interval;

// Warunki przyspieszania pileczki z czasem gry.
    if (roundTime % 1000 == 0 && roundTime < 20000)
    {
        if (ball_x < 0 && ball_y < 0)
        {
            ball_x -= 0.1;
            ball_y -= 0.1;
        }
        else if (ball_x < 0 && ball_y > 0)
        {
            ball_x -= 0.1;
            ball_y += 0.1;
        }
        else if (ball_x > 0 && ball_y < 0)
        {
            ball_x += 0.1;
            ball_y -= 0.1;
        }
        else if (ball_x > 0 && ball_y > 0)
        {
            ball_x += 0.1;
            ball_y += 0.1;
        }

        ballSpeed += 0.1;
    }

// Warunki odpowiadaj¹ce za ruch pi³ki.
    Ball->Left += ball_x;
    Ball->Top += ball_y;

// Warunki odbijania siê pi³ki od krawêdzi górnej i dolnej.
    if (Ball->Top <= 0 || Ball->Top + Ball->Height >= GameBackGround->Height)
        ball_y = -ball_y;

// Instrukcja odpowiadajaca za przegrana i odbijanie gracza lewego.
    if (roundTime > lastBounceTime + 3 * BallMovement->Interval)
    {
    // Warunek przegranej gracza lewego.
        if (Ball->Left < LeftRacket->Left + LeftRacket->Width - abs(ball_x))
        {
            gameOver();
        }
    // Warunek odbicia siê pi³ki od paletki lewej.
        else
        {
        // Warunek przyspieszenia pi³ki przy odbiciu od srodka paletki lewej.
            if (Ball->Top > LeftRacket->Top + LeftRacket->Height / 3 - Ball->Height / 2 - abs(ball_y) &&
                Ball->Top + Ball->Height < LeftRacket->Top + LeftRacket->Height - LeftRacket->Height / 3 + Ball->Height / 2 + abs(ball_y) &&
                Ball->Left <= LeftRacket->Left + LeftRacket->Width)
            {
                accelerateBounce();
            }
        // Warunek normalnego odbicia które przywraca prêdkosc pilki do normal.
            else if (Ball->Top >= LeftRacket->Top - Ball->Height / 2 - abs(ball_y) &&
                Ball->Top <= LeftRacket->Top + LeftRacket->Height - Ball->Height / 2 + abs(ball_y) &&
                Ball->Left <= LeftRacket->Left + LeftRacket->Width)
            {
                normalBounce();
            }
        }
    }

// Instrukcja odpowiadajaca za przegrana i odbijanie gracza prawego.
    if ( roundTime > lastBounceTime + 3 * BallMovement->Interval)
    {
    // Warunek przegranej gracza prawego.
        if (Ball->Left + Ball->Width > RightRacket->Left + abs(ball_x))
        {
            gameOver();
        }
    // Warunek odbicia siê pi³ki od paletki prawej.
        else
        {
        // Warunek przyspieszenia pi³ki przy odbiciu od srodka paletki prawej.
            if (Ball->Top > RightRacket->Top + RightRacket->Height / 3 - Ball->Height / 2 - abs(ball_y) &&
                Ball->Top + Ball->Height < RightRacket->Top + RightRacket->Height - RightRacket->Height / 3 + Ball->Height / 2 + abs(ball_y) &&
                Ball->Left + Ball->Width >= RightRacket->Left)
            {
                accelerateBounce();
            }
        // Warunek normalnego odbicia które przywraca prêdkosc pilki do normal.
            else if (Ball->Top >= RightRacket->Top - Ball->Height / 2 - abs(ball_y) &&
                Ball->Top <= RightRacket->Top + RightRacket->Height - Ball->Height / 2 + abs(ball_y) &&
                Ball->Left + Ball->Width >= RightRacket->Left)
            {
                normalBounce();
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TGame::NewGameButtonClick(TObject *Sender)
{
// Funkcja odpowiadajaca za dzialania po kliknieciu w przycisk New Game.
    if (WelcomeWindow->Visible == true)
    {
        resetGame();
        leftPlayerPoints = 0;
        rightPlayerPoints = 0;
        WelcomeWindow->Visible = false;
    }
    else
    {
        if (Application->MessageBox( "Are you sure?? You will loss present point score.", "Please confirm your choice.", MB_YESNO | MB_ICONQUESTION) == IDYES )
        {
            resetGame();
            leftPlayerPoints = 0;
            rightPlayerPoints = 0;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TGame::NewRoundButtonClick(TObject *Sender)
{
// Funkcja odpowiadajaca za dzialania po kliknieciu w przycisk New Round.
    resetGame();
}
//---------------------------------------------------------------------------

void __fastcall TGame::MoneyGreenClick(TObject *Sender)
{
// Funkcja zmiany koloru t³a na zielony przy klikniêciu w opcjach.
    GameBackGround->Brush->Color = clMoneyGreen;
    SkyBlue->Checked = false;
    White->Checked = false;
    MoneyGreen->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TGame::WhiteClick(TObject *Sender)
{
// Funkcja zmiany koloru t³a na bia³y przy klikniêciu w opcjach.
    GameBackGround->Brush->Color = clWhite;
    SkyBlue->Checked = false;
    White->Checked = true;
    MoneyGreen->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TGame::SkyBlueClick(TObject *Sender)
{
// Funkcja zmiany koloru t³a na niebieski przy klikniêciu w opcjach.
    GameBackGround->Brush->Color = clMoneyGreen;
    SkyBlue->Checked = true;
    White->Checked = false;
    MoneyGreen->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TGame::EasyClick(TObject *Sender)
{
// Funkcja zmiany trudnosci gry na latwa.
    ballSpeed = 4;
    Easy->Checked = true;
    Medium->Checked = false;
    Hard->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TGame::MediumClick(TObject *Sender)
{
// Funkcja zmiany trudnosci gry na srednia.
     ballSpeed = 5;
     Easy->Checked = false;
     Medium->Checked = true;
     Hard->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TGame::HardClick(TObject *Sender)
{
// Funkcja zmiany trudnosci gry na trudna.
    ballSpeed = 6;
    Easy->Checked = false;
    Medium->Checked = false;
    Hard->Checked = true;
}
//---------------------------------------------------------------------------


void __fastcall TGame::FormCreate(TObject *Sender)
{
// Funkcja pokazujaca okno wstepne.
    ShowMessage( "Welcome in ping pong game:) \n \n Left player steering buttons A and Z \n Right player steering buttons UP and DOWN \n"
     "\n You can choose 3 difficulty levels in Settings \n And customize background color as well:) \n \n"
     "Bouncing in the middle of the racket will accelerate ball \n and when time is elapsing the ball speed will increase as well." );
}
//---------------------------------------------------------------------------

void __fastcall TGame::FormResize(TObject *Sender)
{
//Funkcja odpowiadajaca za ustawienie wszystkich elementow w zaleznosci od wielkosci okna.
    setInitialElementPosition();
}
//---------------------------------------------------------------------------

