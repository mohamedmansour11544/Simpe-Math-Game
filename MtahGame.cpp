#include <iostream>
#include <windows.h> 
using namespace std;
// Function to read a positive number of questions
int ReadQuestions(const string& message)
{
    int numberOfQuestions;
    while (true)
    {
        cout << message << endl;
        cin >> numberOfQuestions;
        if (numberOfQuestions > 0)
            break;
        cout << "Please enter a positive number." << endl;
    }
    return numberOfQuestions;
}
string MessageHappyOrSad(bool CorrecrWnswer)
{
    return CorrecrWnswer ? ":-)" : ":-(";
}
string RigthWrongAnswerForEveryAnswer(bool correcr)
{
    return correcr ? "Correct Answer" + MessageHappyOrSad(true) : "Wrong Answer" + MessageHappyOrSad(false);
}

// Enum for difficulty levels
enum DifficultyLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};

// Enum for operation types
enum OperationType
{
    op_Add = 1,
    op_Sub = 2,
    op_Multiply = 3,
    op_Mix = 4
};

// Structure to hold game results
struct ResultOfGame
{
    int numberOfQuestions;
    DifficultyLevel difficulty;
    OperationType opType;
    int trueAnswers = 0;
    int wrongAnswers = 0;
};

// Function to reset the console
void Reset()
{
    system("cls");
    system("color 0F");
}

// Function to generate a random number between 'from' and 'to'
int RandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

// Function to generate a random number based on difficulty level
int RandomQuestionsNumbers(DifficultyLevel level)
{
    switch (level)
    {
    case Easy:
        return RandomNumber(1, 10);
    case Med:
        return RandomNumber(10, 50);
    case Hard:
        return RandomNumber(50, 100);
    case Mix:
        return RandomNumber(1, 100);
    default:
        return 1; // Default case
    }
}

// Function to return a random operation type as a character
char RandomOperationType(OperationType opType)
{
    switch (opType)
    {
    case op_Add:
        return '+';
    case op_Sub:
        return '-';
    case op_Multiply:
        return '*';
    case op_Mix:
        switch (RandomNumber(1, 3))
        {
        case 1:
            return '+';
        case 2:
            return '-';
        case 3:
            return '*';
        }
    default:
        return '+'; // Default case
    }
}

// Function to print a question
void PrintQuestion(int number1, int number2, char opType)
{
    cout << number1 << " " << opType << " " << number2;
}

// Function to compute the result of a game question
int ComputeResult(int number1, int number2, OperationType opType, char op)
{
    switch (opType)
    {
    case op_Add:
        return number1 + number2;
    case op_Sub:
        return number1 - number2;
    case op_Multiply:
        return number1 * number2;
    case op_Mix:
        switch (op)
        {
        case '+':
            return number1 + number2;
        case '-':
            return number1 - number2;
        case '*':
            return number1 * number2;
        }
    default:
        return 0;
    }
}

// Function to set console color based on correctness
void SetConsoleColor(bool correct)
{
    system(correct ? "color 2F" : "color 4F");
}

// Function to process the game logic
ResultOfGame Process(int numberOfQuestions, OperationType opType, DifficultyLevel difficulty)
{
    ResultOfGame result; // to return struct fill of the results to print .
    result.numberOfQuestions = numberOfQuestions;
    result.opType = opType;
    result.difficulty = difficulty;

    for (int i = 1; i <= numberOfQuestions; ++i)
    {
        int number1 = RandomQuestionsNumbers(difficulty);
        int number2 = RandomQuestionsNumbers(difficulty);
        char op = RandomOperationType(opType);

        cout << "Question [" << i << "/" << numberOfQuestions << "]" << endl;
        PrintQuestion(number1, number2, op);
        cout << endl;
        cout << "=========================" << endl;

        int answer;
        cin >> answer;

        if (answer == ComputeResult(number1, number2, opType, op))
        {
            cout << RigthWrongAnswerForEveryAnswer(true) << endl;
            result.trueAnswers++;
            SetConsoleColor(true);
        }
        else
        {
            cout << RigthWrongAnswerForEveryAnswer(false) << endl;
            cout << "Rigth Answer Is:" << ComputeResult(number1, number2, opType, op) << endl;
            result.wrongAnswers++;
            SetConsoleColor(false);
        }
        cout << endl;
        if (i == numberOfQuestions)
        {
            Sleep(500);
        }
    }
    // system("color 0F"); // Reset color after each question
    return result;
}

// Function to print the results of the game
string Tab(int number)
{
    string tab;
    for (int i = 1; i <= number; i++)
    {
        tab += "\t";
    }
    return tab;
}
void PrintResult(const ResultOfGame& result)
{
    if (result.trueAnswers > result.wrongAnswers || result.trueAnswers == result.wrongAnswers)
    {
        cout << Tab(6) << "The Result Is Pass " + MessageHappyOrSad(true) << endl;
        SetConsoleColor(true);
    }
    else
    {
        cout << Tab(6) << "The Result Is Fail" + MessageHappyOrSad(false) << endl;
        SetConsoleColor(false);
    }
    cout << Tab(6) << "Number Of Questions: " << result.numberOfQuestions << endl;
    cout << Tab(6) << "Difficulty Level: " << result.difficulty << endl;

    cout << Tab(6) << "Operation Type: " << result.opType << endl;
    cout << Tab(6) << "True Answers: " << result.trueAnswers << endl;
    cout << Tab(6) << "Wrong Answers: " << result.wrongAnswers << endl;
}

// Function to read operation type from user
OperationType ReadOperationType()
{
    int opType;
    while (true)
    {
        cout << "Enter Operation Type: [1]Add, [2]Sub, [3]Multiply, [4]Mix?" << endl;
        cin >> opType;
        if (opType >= 1 && opType <= 4)
            break;
        cout << "Invalid option. Please enter a number between 1 and 4." << endl;
    }
    return static_cast<OperationType>(opType);
}

// Function to read difficulty level from user
DifficultyLevel ReadQuestionsLevel()
{
    int level;
    while (true)
    {
        cout << "Enter Questions Level: [1]Easy, [2]Med, [3]Hard, [4]Mix?" << endl;
        cin >> level;
        if (level >= 1 && level <= 4)
            break;
        cout << "Invalid option. Please enter a number between 1 and 4." << endl;
    }
    return static_cast<DifficultyLevel>(level);
}

// Function to start the game
void StartGame()
{
    char choice = 'Y';
    while (toupper(choice) == 'Y')
    {
        Reset();
        int numberOfQuestions = ReadQuestions("Enter Number Of Questions");
        OperationType opType = ReadOperationType();
        DifficultyLevel level = ReadQuestionsLevel();
        ResultOfGame result = Process(numberOfQuestions, opType, level);
        PrintResult(result);
        cout << Tab(9) << "Do You Want To Play Again? [Y/N]?" << endl;
        cin >> choice;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
