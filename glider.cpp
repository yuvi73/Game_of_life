#include <raylib.h>


const int ROWS = 20;
const int COLS = 40;
const int CELL_SIZE = 20;
const int SCREEN_WIDTH = COLS * CELL_SIZE;
const int SCREEN_HEIGHT = ROWS * CELL_SIZE;

// Count live neighbours
int countNeighbours(int grid[ROWS][COLS], int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int ni = x + i;
            int nj = y + j;
            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS)
            {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

void updateGrid(int grid[ROWS][COLS])
{
    int temp[ROWS][COLS] = {};
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int neighbours = countNeighbours(grid, i, j);
            if (grid[i][j] == 1 && (neighbours == 2 || neighbours == 3))
            {
                temp[i][j] = 1;
            }
            else if (grid[i][j] == 0 && neighbours == 3)
            {
                temp[i][j] = 1;
            }
            else
            {
                temp[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = temp[i][j];
}

int main()
{
    int grid[ROWS][COLS] = {};

    // Glider pattern
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
    SetTargetFPS(10); // 10 updates per second

    while (!WindowShouldClose())
    {
        updateGrid(grid);

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid[i][j])
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, GREEN);
                else
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, DARKGRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
