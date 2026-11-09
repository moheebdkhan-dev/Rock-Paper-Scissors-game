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

/*
              Teacher's Code
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

// Enumeration: enWinner
// Purpose: Defines possible winners for a round or game.
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// Structure: stRoundInfo
// Purpose: Stores details of a single round of the game.
struct stRoundInfo
{
    short RoundNumber = 0;          // Round number.
    enGameChoice Player1Choice;     // Player's choice.
    enGameChoice ComputerChoice;    // Computer's choice.
    enWinner Winner;                // Stores the winner of the round.
    string WinnerName;               // Stores the winner's name.
};

// Structure: stGameResults
// Purpose: Stores overall game results after all rounds are played.
struct stGameResults
{
    short GameRounds = 0;        // Number of rounds played.
    short Player1WinTimes = 0;   // Count of Player1's wins.
    short ComputerWinTimes = 0;  // Count of Computer's wins.
    short DrawTimes = 0;         // Number of rounds that ended in a draw.
    enWinner GameWinner;         // Stores the overall game winner.
    string WinnerName = "";      // Name of the game winner.
};

// Function: RandomNumber
// Purpose: Generates a random number within the given range [From, To].
// Parameters:
//   - From: Lower bound of the random range.
//   - To: Upper bound of the random range.
// Returns: A random integer between From and To.
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Function: GetComputerChoice
// Purpose: Randomly selects the computer's choice.
// Returns: An enGameChoice value representing the computer's move.
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

// Function: WhoWonTheRound
// Purpose: Determines the winner of a round based on player and computer choices.
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    // If both choices are the same, it's a draw.
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    // Determine the winner based on game rules.
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
}

// Function: WhoWonTheGame
// Purpose: Determines the final game winner based on win counts.
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

// Function: ChoiceName
// Purpose: Converts an enGameChoice enum to a string representation.
string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

// Function: WinnerName
// Purpose: Converts an enWinner enum to a string representation.
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

// Function: ReadPlayer1Choice
// Purpose: Prompts the player to input their choice.
enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

// Function: PrintRoundResults
// Purpose: Displays the results of a single round.
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}

// Function: PlayGame
// Purpose: Runs the game for a given number of rounds and determines the final winner.
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return { HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, ComputerWinTimes)) };
}

// Function: StartGame
// Purpose: Controls the game loop, allowing players to replay the game.
void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");  // Clear the screen before starting a new game.
        stGameResults GameResults = PlayGame(3); // Play 3 rounds.
        cout << "\nGame Over! Winner: " << GameResults.WinnerName << endl;

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// Main Function
int main()
{
    srand((unsigned)time(NULL));  // Seed random number generator.
    StartGame();  // Start the game.
    return 0;  // Return 0 to indicate successful execution.
}
*/