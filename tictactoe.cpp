#include <stdio.h>
#include <bits/stdc++.h>
#define ll long long int
#define f(i, a, b) for (long long int i = a; i < b; i++)
#define pb push_back
#define mk make_pair
#define ub upper_bound
#define lb lower_bound
#define ss second
#define ff first
#define endl "\n"
using namespace std;
const ll mod = 1000000007;
const ll inf = -1000000001;

bool humanwin(vector<vector<char>> &grid)
{
    // CHECK COLUMNS
    for (int i = 0; i < 3; i++)
    {
        int cnt=0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[j][i]=='o') cnt++;
        }

        if (cnt==3) return true;
    }

    // CHECKROWS
    for (int i = 0; i < 3; i++)
    {
        int cnt=0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == 'o') cnt++;
        }

        if (cnt==3) return true;
    }

    // CHECK DIAGONALS
    // FIRST DIAGONAL
    int d=0;
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][i] == 'o') d++;
    }

    if (d==3) return true;

    // SECOND DIAGONAL
    d=0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i + j == 2 and grid[i][j] == 'o') d++;
        }
    }

    if (d==3) return true;

    return false;
}

void show(vector<vector<char>> &grid)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++) cout<<grid[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

bool check(vector<vector<char>> &grid, char c)
{
    // CHECK COLUMNS
    for (int i = 0; i < 3; i++)
    {
        int col = 0, b = 0, o = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[j][i] == c) col++;
            else if (grid[j][i] == '.') b++;
            else o++;
        }

        if (col == 2 and b==1)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[j][i] == '.')
                {
                    grid[j][i] = 'x';
                    return true;
                }
            }
        }

        if (col==3) return true;
    }

    // CHECKROWS
    for (int i = 0; i < 3; i++)
    {
        int row = 0, b = 0, o = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == c) row++;
            else if (grid[i][j] == '.') b++;
            else o++;
        }

        if (row == 2 and b==1)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == '.')
                {
                    grid[i][j] = 'x';
                    return true;
                }
            }
        }

        if (row==3) return true;
    }

    // CHECK DIAGONALS
    // FIRST DIAGONAL
    int d1 = 0, b = 0, o = 0;
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][i] == c) d1++;
        else if (grid[i][i] == '.') b++;
        else o++;
    }

    if (d1 == 2 and b==1)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[j][j] == '.')
            {
                grid[j][j] = 'x';
                return true;
            }
        }
    }

    // SECOND DIAGONAL
    d1 = 0, b = 0, o = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i + j == 2)
            {
                if (grid[i][j] == c) d1++;
                else if (grid[i][j] == '.') b++;
                else o++;
            }
        }
    }

    if (d1 == 2 and b==1)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i + j == 2 and grid[i][j]=='.')
                {
                    grid[i][j]='x';
                    return true;
                }
            }
        }
        
    }

    return false;
}

bool play(vector<vector<char>> &grid, int corner)
{
    // CHECK OWN WIN CONDITION
    bool compwin = check(grid, 'x');
    if (compwin == true) return true;

    // STOP HUMAN FROM WINNING
    if (check(grid, 'o'))
        return false;

    // IF AVAILABLE FILL CORNER FIRST
    if (corner < 4)
    {
        if (grid[0][0] == '.') grid[0][0] = 'x';
        else if (grid[0][2] == '.') grid[0][2] = 'x';
        else if (grid[2][0] == '.') grid[2][0] = 'x';
        else if (grid[2][2] == '.') grid[2][2] = 'x';
        corner++;
        return false;
    }

    // FILL ANY RANDOM AVAILABLE POSITION
    int row = rand() % 3, col = rand() % 3;
    while (grid[row][col] == 'x' or grid[row][col] == 'o')
    {
        row = rand() % 3;
        col = rand() % 3;
    }

    grid[row][col] = 'x';
    return false;
}

void solve()
{
    vector<vector<char>> grid(3, vector<char>(3, '.'));
    int s;
    cout << "Who starts? 0.Human 1.Computer?: ";
    cin >> s;
    int r, c;
    int corner = 0;
    int chances=0;

    // IF COMPUTER STARTS IT FILLS THE CORNER 
    if (s == 1)
    {
        cout<<"COMPUTER: "<<endl;
        grid[0][0] = 'x';
        corner++;
        chances++;
        s++;
        show(grid);
    }
   
    for (int i = s ; chances < 9; i++)
    {
        if (i % 2 == 0)
        {
            cout << "Enter row and column: ";
            cin >> r >> c;
            r--; c--;
            grid[r][c] = 'o';
            if ((r == 0 and c == 2) or (r == 0 and c == 0) or (r == 2 and c == 0) or (r == 2 and c == 2)) corner++;
            cout<<"YOU: "<<endl;
            show(grid);

            if (humanwin(grid)) 
            {
                show(grid);
                cout<<"YOU WON!"<<endl;
                return;
            }
        }

        else
        {
            bool out = play(grid, corner);
            if (out == true)
            {
                cout<<"COMPUTER: "<<endl; 
                show(grid);
                cout<<"COMPUTER WON!"<<endl;
                return;
            }
            cout<<"COMPUTER: "<<endl;  
            show(grid);
        }

        chances++;
    }

    cout<<"ITS A TIE!"<<endl;
    
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    solve();
}