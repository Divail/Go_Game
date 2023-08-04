# Go_game
Originally uploaded on GitLab https://gitlab.com/Divail/go_game/-/tree/develop/Go_game
Current programm is not finished, but runs and can be played with IA. All code was made by Dmyto Levytskyi exept of the AI Engine.
The game is played on a 19x19 grid board. Here's a description of the main components:

    Board.cpp and Board.h:
        The Board class represents the Go board and holds information about the stones and their positions.
        draw_board(): Draws the grid lines of the Go board.
        draw_stone(): Draws the stones (black and white) on the board.
        The board has a 19x19 array to represent the stones (BLACK and WHITE) and uses the SFML library to draw the graphical representation.

    Game.cpp and Game.h:
        The Game class handles the overall game logic and graphics using SFML.
        Game initializes the window, loads textures for black and white stones, applies smoothness, and sets their scale.
        It has methods to update the game state, remove dead stones, and make moves by communicating with an external engine (gnugo.exe) for AI moves.
        It has a method Tests() to run a series of tests using MyTests.h for testing various aspects of the game.

    Menu.cpp and Menu.h:
        The Menu class represents a simple menu screen with options to Play, Options, and Exit.
        It uses SFML to display the menu options and handle user input.

    MyTests.cpp and MyTests.h:
        MyTests contains functions for logging test results and displaying test statistics.

    TestMyGame.cpp:
        Contains specific test cases for the game logic and components.

Overall, the program uses the Game class to run the Go game and provides a simple menu interface for the player to start the game, access options, or exit the program. The AI opponent for the game is integrated with an external engine (gnugo.exe) that provides moves for the computer player. The code is organized into separate classes for better modularity and readability.

The program have a testing mechanism in place (MyTests.cpp) to ensure that the game logic is working correctly. The tests check the behavior of the Board class and its related functions. The test results are logged into a file named "MyTestsLog.txt."
