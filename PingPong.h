//---------------------------------------------------------------------------

#ifndef PingPongH
#define PingPongH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TGame : public TForm
{
__published:	// IDE-managed Components
        TShape *GameBackGround;
        TMainMenu *MainMenu;
    TMenuItem *Settings;
    TMenuItem *Colors;
    TMenuItem *Backgroundscolor;
        TImage *LeftRacket;
        TImage *RightRacket;
        TImage *Ball;
        TTimer *LeftRacketDown;
        TTimer *LeftRacketUp;
        TTimer *RightRacketDown;
        TTimer *RightRacketUp;
        TTimer *BallMovement;
        TLabel *WelcomeWindow;
        TButton *NewGameButton;
        TButton *NewRoundButton;
        TLabel *WinnerPointer;
        TLabel *ScoreBoard;
        TLabel *BounceCounter;
        TMenuItem *SkyBlue;
        TMenuItem *White;
        TMenuItem *MoneyGreen;
    TMenuItem *Level;
        TMenuItem *Easy;
        TMenuItem *Hard;
    TMenuItem *Medium;
    TLabel *Counter;
        void __fastcall LeftRacketUpTimer(TObject *Sender);
        void __fastcall LeftRacketDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall RightRacketUpTimer(TObject *Sender);
        void __fastcall RightRacketDownTimer(TObject *Sender);
        void __fastcall BallMovementTimer(TObject *Sender);
        void __fastcall NewGameButtonClick(TObject *Sender);
        void __fastcall NewRoundButtonClick(TObject *Sender);
        void __fastcall MoneyGreenClick(TObject *Sender);
        void __fastcall WhiteClick(TObject *Sender);
        void __fastcall SkyBlueClick(TObject *Sender);
        void __fastcall EasyClick(TObject *Sender);
        void __fastcall HardClick(TObject *Sender);
    void __fastcall MediumClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
        unsigned int roundTime;
        unsigned int lastBounceTime;
        unsigned int bounceCounter;
        float ball_x;
        float ball_y;
        float ballSpeed;
        int racketSpeed;
        int leftPlayerPoints;
        int rightPlayerPoints;

        void resetGame();
        void setInitialElementPosition();
        void countingDown();
        void displayRoundSummary();
        int checkDifficultyLevel();
        int randomBallGenerator();
        void accelerateBounce();
        void normalBounce();
        void gameOver();
public:		// User declarations
        __fastcall TGame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGame *Game;
//---------------------------------------------------------------------------
#endif
