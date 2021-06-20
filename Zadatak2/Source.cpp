// C++ program to find path
// between two cell in matrix
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;
#define ROW 20
#define COLLUM 40

//Directions
int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, 1, 0, -1 };

void display2DMatrix(char M[][COLLUM])
{
    for (unsigned i = 0; i < ROW; i++)
    {
        for (unsigned j = 0; j < COLLUM; j++)
        {
            cout << M[i][j];
        }
        cout << endl;
    }
}

class QItem {
public:
    int row;
    int col;
    int dist;
    QItem(int x, int y, int w)
        : row(x), col(y), dist(w)
    {
    }
};

int minDistance(char M[ROW][COLLUM], int rowA, int collumA, int rowB, int collumB)
{
    QItem source(0, 0, 0);
    //Finding walls and source
    bool visited[ROW][COLLUM];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLLUM; j++)
        {
            if (M[i][j] == '#')
                visited[i][j] = true;
            else
                visited[i][j] = false;

            // Finding source
            if (M[i][j] == 'A')
            {
                source.row = i;
                source.col = j;
            }
        }
    }

    //BFS Start
    queue<QItem> q;
    q.push(source);
    visited[source.row][source.col] = true;
    while (!q.empty()) {
        QItem p = q.front();
        q.pop();

        // Destination found;
        if (M[p.row][p.col] == 'B')
            return p.dist;

        // moving up
        if (p.row - 1 >= 0 &&
            visited[p.row - 1][p.col] == false) {
            q.push(QItem(p.row - 1, p.col, p.dist + 1));
            visited[p.row - 1][p.col] = true;

        }

        // moving down
        if (p.row + 1 < ROW &&
            visited[p.row + 1][p.col] == false) {
            q.push(QItem(p.row + 1, p.col, p.dist + 1));
            visited[p.row + 1][p.col] = true;

        }

        // moving left
        if (p.col - 1 >= 0 &&
            visited[p.row][p.col - 1] == false) {
            q.push(QItem(p.row, p.col - 1, p.dist + 1));
            visited[p.row][p.col - 1] = true;

        }

        // moving right
        if (p.col + 1 < COLLUM &&
            visited[p.row][p.col + 1] == false) {
            q.push(QItem(p.row, p.col + 1, p.dist + 1));
            visited[p.row][p.col + 1] = true;
        }
        
        M[rowA - 1][collumA - 1] = 'A';
        M[rowB - 1][collumB - 1] = 'B';
        M[p.row][p.col] = '*';
        display2DMatrix(M);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
    }
    return -1;
}

void userInput(int& rowA, int& collumA, int& rowB, int& collumB)
{
    cout << "A Row (1 - 20): ";
    cin >> rowA;
    cout << "A Collum (1 - 40): ";
    cin >> collumA;

    cout << "B Row (1 - 20): ";
    cin >> rowB;
    cout << "B Collum (1 - 40): ";
    cin >> collumB;
}


int main()
{
    int rowA, collumA, rowB, collumB;
    userInput(rowA, collumA, rowB, collumB);

    char M[ROW][COLLUM];
    for (unsigned i = 0; i < ROW; i++)
    {
        for (unsigned j = 0; j < COLLUM; j++)
        {
            M[i][j] = '-';
        }
    }
    //Set A and B
    M[rowA - 1][collumA - 1] = 'A';
    M[rowB - 1][collumB - 1] = 'B';
    //Init Walls
    M[0][10] = '#';
    M[1][10] = '#';
    M[2][10] = '#';
    M[3][10] = '#';
    M[4][10] = '#';
    M[5][10] = '#';
    M[6][10] = '#';

    cout << "Shortest path: " << minDistance(M, rowA, collumA, rowB, collumB) << endl;
    display2DMatrix(M);

    return 0;
}