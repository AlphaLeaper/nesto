#include "game.h"
#include <iostream>

game::game()
    :
    xTurn(true),
    isRunning(true)
{
    for (int i = 0; i < 3; i++)
    for (int i2 = 0; i2 < 3; i2++)
    grid[i][i2] = 0;
}

game::game(bool xTurn)
    :
    xTurn(xTurn),
    isRunning(true)
{
    for (int i = 0; i < 3; i++)
    for (int i2 = 0; i2 < 3; i2++)
    grid[i][i2] = 0;
}

bool game::cell_is_empty(int i, int i2)
{
    return (grid[i][i2] == 0);
}

bool game::horizontal_check(int y)
{
    return (grid[y][0] == grid[y][1] and grid[y][1] == grid[y][2] and grid[y][0] != 0);
}

bool game::vertical_check(int x)
{
    return (grid[0][x] == grid[1][x] and grid[1][x] == grid[2][x] and grid[0][x] != 0);
}

bool game::diagonal_check_lr()
{
    return (grid[0][0] == grid[1][1] and grid[1][1] == grid[2][2] and grid[1][1] != 0);
}

bool game::diagonal_check_rl()
{
    return (grid[0][2] == grid[1][1] and grid[1][1] == grid[2][0] and grid[1][1] != 0);
}

void game::draw_grid()
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            std::cout << grid[y][x] << " ";
        }
        std::cout << '\n';
    }
}

void game::take_turn()
{
    int sym;

    if (xTurn)
        sym = 1;
    else
        sym = 2;

    int x;
    int y;
    std::cout << "y coordinate: ";
    std::cin >> y;
    std::cout << "x coordinate: ";
    std::cin >> x;

    if (x < 0 || x > 2 || y < 0 || y > 2)
    {
        std::cout << "range 0 to 2" << '\n';
        take_turn();
        return;
    }

    if (cell_is_empty(y,x))
    {
        grid[y][x] = sym;
        xTurn = !xTurn;
    }
    else
    {
        std::cout << "spot is already taken" << '\n';
        take_turn();
        return;
    }
}

void game::check_win()
{
    for (int i = 0; i < 3; i++)
    {
        if (horizontal_check(i) || vertical_check(i))
        {
            isRunning = false;
            std::cout << "gg gamers, someone won\n\n";
        }
    }

    if (diagonal_check_lr() || diagonal_check_rl())
    {
        isRunning = false;
        std::cout << "gg gamers, someone won\n\n";
    }
}

void game::run()
{
    while (isRunning)
    {
    	take_turn();
        draw_grid();
        std::cout << '\n';
        check_win();
    }
}
