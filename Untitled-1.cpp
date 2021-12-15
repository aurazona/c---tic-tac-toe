//tic tac toe

#include <iostream>
#include <string>
#include <ios>
#include <limits>

//prototype classes (whatever happened to the prototype game? that was pretty fun.)
void menu();
void help();
void settings();
void exit();
void playerState();
void aiState();
void intermissionState();
void winCheckState();
void drawBoard();
void boardCheckState();

//define and initialise the game board
char board[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
//turn tracker, player goes on odd turns whilst AI goes on even turns.
int gameTurn = 1;
//used to store the player's selected space
int plrChoice;
//used to store the AI's selected space
int aiChoice;
//used to check if the player's choice is valid
bool plrVer;
//used to check if the AI's choice is valid
bool aiVer;


void menu()
{
    std::string choice;
    int ichoice = 0;
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
    std::cout << "@~~~~~~~~~~~~~~~~~~~~~~@" << std::endl;
    std::cout << "|TIC TAC TOE: MAIN MENU|" << std::endl;
    std::cout << "|1. Play               |" << std::endl;
    std::cout << "|2. Settings           |" << std::endl;
    std::cout << "|3. Help               |" << std::endl;
    std::cout << "|4. Quit               |" << std::endl;
    std::cout << "@~~~~~~~~~~~~~~~~~~~~~~@" << std::endl;

    try
    {
        std::cin >> choice;
        ichoice = std::floor(std::stof(choice));
    }
    catch (std::exception ex)
    {
        std::cout << "Please Enter An Integer Value" << std::endl;
        return;
    }

    switch (ichoice)
    {
    case 1:
        std::cout << "You have chosen play." << std::endl;
        system("pause");
        intermissionState();
        break;
    case 2:
        settings();
        break;
    case 3:
        help();
        break;
    case 4:
        exit();
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }


}

void settings()
{
    int choice = 0;
    std::cout << "TIC TAC TOE: SETTINGS MENU \n \n \n" << std::endl;
    std::cout << "1. Settings Option" << std::endl;
    std::cout << "2. Return to main menu" << std::endl;

    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Setting adjusted." << std::endl;
        system("pause");
        settings();
    }
    else if (choice == 2)
    {
        menu();
    }
    else
    {
        std::cout << "Invalid choice, returning to main menu..." << std::endl;
        system("pause");
    }
}

void help()
{
    int choice = 0;
    std::cout << "TIC TAC TOE: HELP MENU \n \n \n" << std::endl;
    std::cout << "1. Help" << std::endl;
    std::cout << "2. Return to main menu" << std::endl;

    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "get good lol." << std::endl;
        system("pause");
        help();
    }
    else if (choice == 2)
    {
        menu();
    }
    else
    {
        std::cout << "Invalid choice, returning to main menu..." << std::endl;
        system("pause");
    }
}

void exit()
{
    char choice;
    std::cout << "You are attempting to exit. Are you sure? Y/N" << std::endl;
    std::cin >> choice;

    if (choice == 'y' || 'Y')
    {
        std::cout << "Exiting application..." << std::endl;
        system("pause");
        exit(0);
    }
    else if (choice == 'n' || 'N')
    {
        std::cout << "Returning to menu..." << std::endl;
        system("pause");
        menu();
    }
    else
    {
        std::cout << "Invalid choice, returning to main menu..." << std::endl;
        system("pause");
    }
}

void drawBoard()
{
    std::cout << "Turn Number " << gameTurn << "\n \n \n" << std::endl;
    std::cout << board[1] << " | " << board[2] << " | " << board[3] << std::endl;
    std::cout << board[4] << " | " << board[5] << " | " << board[6] << std::endl;
    std::cout << board[7] << " | " << board[8] << " | " << board[9] << std::endl;
}

bool boardCheckState(char toCheck)
{
    int arrayPos = 0; //keeps track of where we are in the array
    char boardMem = 'n'; //keeps hold of what's actually in the board array
    bool isClear = false; //switched on if the space is eligible to be taken

    while(toCheck != boardMem)
    {
        if (arrayPos > 10)
        {
            isClear = false;
            break;
        }
        boardMem = board[arrayPos];
        if (boardMem == toCheck)
        {
            isClear = true;
            break;
        }
        else
        {
            arrayPos++;
        }
    }

    return isClear;

}

void aiState()
{
    aiVer = false; //set the verification to false to avoid skipping the selection loop
    std::cout << "Opponent is thinking..." << std::endl;
    while (aiVer == false) //this keeps the loop going until a valid placement has been selected.
    {
        aiChoice = std::rand() % 9 + 1; //choose a number between 1 and 9
        if (boardCheckState(aiChoice) == false) //if the space does not contain X or O...
        {
            aiVer = true; //verify the placement, breaking the while loop
            board[aiChoice] = 'O'; //replace the chosen array member with an O
        }
    }
    gameTurn++; //increment game counter
    intermissionState(); //return to intermission state
}

void playerState()
{
    while (plrVer == false)
    {
        system("CLS");
        std::cout << "Your turn!" << "\n\n\n" << std::endl;
        drawBoard();
        std::cout << "\n\n\n" << "Please select a number:" << std::endl;
        std::cin >> plrChoice;
        if (boardCheckState(plrChoice) == false)
        {
            plrVer = true;
            board[plrChoice] = 'X';
            
        }
        else
        {
            std::cout << "Invalid placement. Please try again." << std::endl;
        }
    }
    gameTurn++;
    intermissionState();

}

void winCheckState() //checks every possible combination for wins. Need to find a better way than if statements.
{
//this function checks the board for any wins. prepare yourself for a lot of 'if' statements.
    if ((board[1]) == (board[2])) //across top row
    {
        if ((board[1] == board[3]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
    }
    if ((board[1]) == (board[4])) //down left column
    {
        if ((board[1] == board[7]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
    }
    if ((board[1]) == (board[5])) //diagonal heading right
    {
        if ((board[1] == board[9]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
    }
    if ((board[2]) == (board[5])) //down middle column
    {
        if ((board[2] == board[8]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
    }
    if ((board[3]) == (board[6])) //down right column
    {
        if ((board[3] == board[9]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
    }
    if ((board[3]) == (board[5])) //diagonal heading left
    {
        if ((board[3] == board[7]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
    }
    if ((board[4]) == (board[5])) //across middle row
    {
        if ((board[4] == board[6]))
        {
            std::cout << "Winner!" << std::endl;
            drawBoard();
            std::cin;
            menu();
        }
        if ((board[7]) == (board[8])) //across top row
        {
            if ((board[7] == board[9]))
            {
                std::cout << "Winner!" << std::endl;
                drawBoard();
                std::cin;
                menu();
            }
        }
    }
}

void intermissionState()
{
    system("CLS"); //clear the screen for aesthetics
    winCheckState(); //check to see if 
    drawBoard();
    if (gameTurn % 2 == 1) //player always goes on odd turns
    {
        std::cout << "\n\n\n" << "It's your turn next!" << "\n\n" << "Press [ENTER] to continue!" << std::endl;
        std::cin;
        playerState();
    }
    else //otherwise it's the AI's turn
    {
        std::cout << "\n\n\n" << "It's the opponent's turn next!" << "\n\n" << "Press [ENTER] to continue!" << std::endl;
        std::cin;
        aiState();
    }
}

int main()
{
    while (1)
        menu();
}