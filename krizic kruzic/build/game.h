#pragma once

class game
{
public:
    game();
    game(bool xTurn);
public:
    bool cell_is_empty(int index1, int index2);
    bool horizontal_check(int y);
    bool vertical_check(int x);
    bool diagonal_check_lr();
    bool diagonal_check_rl();
public:
    void draw_grid();
    void take_turn();
    void check_win();
    void run();
private:
    int grid[3][3];
    bool xTurn;
    bool isRunning;
};
