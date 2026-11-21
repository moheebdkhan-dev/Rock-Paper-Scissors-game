#include <iostream>
#include <string>
using namespace std;

int ReadIntegerInRange(string Message, int From, int To) {
    int Num;
    do {
        cout << Message << endl;
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

int RandomNumber(int From, int To) {
    // function to generate random numbers in the range From, To.
    //srand((unsigned)time(NULL)); if i uncomment this line, then the result will be equal.
    int random = rand() % (To - From + 1) + From;
    return random;
    // Ex : From = 10, To = 20;
    // random = rand() % 11
}

enum enRockPaperScissors { Rock = 1, Paper = 2, Scissors = 3 };

enum enWinner { Computer, Player, NoWinner };

struct stFinalResult {
    unsigned short GameRounds = 0;
    unsigned short PlayerWinningTimes=0;
    unsigned short ComputerWinningTimes=0;
    unsigned short DrawTimes=0;
    enWinner FinalWinner;
};

struct stRoundResult {
    unsigned short RoundNumber;
    enRockPaperScissors PlayerChoice;
    enRockPaperScissors ComputerChoice;
    enWinner RoundWinner;
};

enRockPaperScissors GetComputerChoice() {
    return (enRockPaperScissors) RandomNumber(1, 3);
}

enRockPaperScissors GetPlayerChoice() {
    return (enRockPaperScissors)ReadIntegerInRange("Your choice : [1]: rock, [2]: paper, [3]: Scissorss?", 1, 3);
}

string ChoicesAsString(enRockPaperScissors choice) {
    switch (choice) {
    case enRockPaperScissors::Paper:
        return "Paper";
    case enRockPaperScissors::Rock:
        return "Rock";
    case enRockPaperScissors::Scissors:
        return "Scissors";
    }
}

string WinnersAsString(enWinner winner) {
    switch (winner) {
    case enWinner::Computer:
        return "Computer";
    case enWinner::Player:
        return "Player";
    case enWinner::NoWinner:
        return "No Winner";
    }
}

enWinner CompareChoices(enRockPaperScissors ComputerChoice, enRockPaperScissors PlayerChoice) {
    if (ComputerChoice == PlayerChoice) return enWinner::NoWinner;
    else if (ComputerChoice == enRockPaperScissors::Paper && PlayerChoice == enRockPaperScissors::Rock) return enWinner::Computer;
    else if (ComputerChoice == enRockPaperScissors::Rock && PlayerChoice == enRockPaperScissors::Scissors) return enWinner::Computer;
    else if (ComputerChoice == enRockPaperScissors::Scissors && PlayerChoice == enRockPaperScissors::Paper) return enWinner::Computer;
    else return enWinner::Player;
}

stRoundResult GetRoundResult(enRockPaperScissors ComputerChoice, enRockPaperScissors PlayerChoice) {
    stRoundResult Result;
    Result.ComputerChoice = ComputerChoice;
    Result.PlayerChoice = PlayerChoice;
    Result.RoundWinner = CompareChoices(ComputerChoice, PlayerChoice);
    return Result;
}

void ConsoleInteractions(enWinner winner) {
    if (winner == enWinner::Computer) {
        system("color 4F");
        cout << '\a';
    }
    else if (winner == enWinner::Player) {
        system("color 2F");
    }
    else {
        system("color 6F");
    }
}

enWinner GetFinalWinner(unsigned short ComputerWinningTimes, unsigned short PlayerWinningTimes) {
    if (PlayerWinningTimes > ComputerWinningTimes) return enWinner::Player;
    else if (ComputerWinningTimes > PlayerWinningTimes) return enWinner::Computer;
    else return enWinner::NoWinner;
}

void PrintRoundResult(stRoundResult Result) {
    
    cout << "-------------------Round[" << Result.RoundNumber << "]-------------------" << endl;
    cout << "Player Choice : " << ChoicesAsString(Result.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoicesAsString(Result.ComputerChoice) << endl;
    cout << "Round Winner : " << WinnersAsString(Result.RoundWinner) << endl;
    cout << "----------------------------------------------" << endl;

    
}

void CalculateFinalResult(stFinalResult& FinalResult, enWinner winner) {
    FinalResult.GameRounds++;
    if (winner == enWinner::Player) FinalResult.PlayerWinningTimes++;
    else if (winner == enWinner::Computer) FinalResult.ComputerWinningTimes++;
    else FinalResult.DrawTimes++;
}

void PlayRound(unsigned short RoundNumber, stFinalResult& FinalResult) {
    cout << "Round [" << RoundNumber << "] begins" << endl;
    stRoundResult RoundResult;
    enRockPaperScissors ComputerChoice, PlayerChoice;
    PlayerChoice = GetPlayerChoice();
    ComputerChoice = GetComputerChoice();
    RoundResult = GetRoundResult(ComputerChoice, PlayerChoice);
    RoundResult.RoundNumber = RoundNumber;
    CalculateFinalResult(FinalResult, RoundResult.RoundWinner);
    ConsoleInteractions(RoundResult.RoundWinner);
    PrintRoundResult(RoundResult);
}

void clearScreen() {
    // \033[2J clears the screen, \033[1;1H moves the cursor to row 1, column 1
    system("cls");
    system("color 0F");
}

void PrintFinalResult(stFinalResult FinalResult) {
    cout << "\t\t\t-----------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t***[Game Over]***" << endl ;
    cout << "\t\t\t-----------------------------------------------------------" << endl ;
    cout << "\t\t\t------------------------Game Result------------------------" << endl ;
    cout << "\t\t\tGame Rounds : " << FinalResult.GameRounds << endl;
    cout << "\t\t\tPlayer Winning Times : " << FinalResult.PlayerWinningTimes << endl;
    cout << "\t\t\tComputer Winning Times : " << FinalResult.ComputerWinningTimes << endl;
    cout << "\t\t\tDraw Times : " << FinalResult.DrawTimes << endl;
    cout << "\t\t\tFinal Winner : " << WinnersAsString(FinalResult.FinalWinner) << endl;
    cout << "\t\t\t-----------------------------------------------------------" << endl;
}

void StartGame() {

    bool PlayAgain;
    do {
        stFinalResult FinalResult;
        int Rounds = ReadIntegerInRange("How many rounds 1 to 10 ?", 1, 10);
        for (int i = 1; i <= Rounds; i++) {
            PlayRound(i, FinalResult);
        }
        FinalResult.FinalWinner = GetFinalWinner(FinalResult.ComputerWinningTimes, FinalResult.PlayerWinningTimes);
        PrintFinalResult(FinalResult);
        PlayAgain = ReadIntegerInRange("Do you want to play again? No : 0, Yes : 1", 0, 1);
        if (PlayAgain) clearScreen();
    } while (PlayAgain);
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}
