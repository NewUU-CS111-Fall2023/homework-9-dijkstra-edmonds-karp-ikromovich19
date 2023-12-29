#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int dx[4] = {0, 1, 0, -1};  
const int dy[4] = {1, 0, -1, 0};

struct Point {
    int x, y, dist;
};

bool isValid(const vector<string>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] != '#';
}

int shortestPath(const vector<string>& maze) {
    int rows = maze.size(), cols = maze[0].size();
    queue<Point> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int startX, startY, endX, endY;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
            } else if (maze[i][j] == 'E') {
                endX = i;
                endY = j;
            }
        }
    }

    q.push({startX, startY, 0});
    visited[startX][startY] = true;

    while (!q.empty()) {
        Point p = q.front();
        q.pop();

        if (p.x == endX && p.y == endY) {
            return p.dist;
        }

        for (int i = 0; i < 4; i++) {
            int x = p.x + dx[i];
            int y = p.y + dy[i];

            if (isValid(maze, x, y) && !visited[x][y]) {
                q.push({x, y, p.dist + 1});
                visited[x][y] = true;
            }
        }
    }

    return -1;  
}

int main() {
    vector<string> maze = {"S..#...", "...#...", "###....", "...#...", "...#..E"};
    int shortest = shortestPath(maze);

    if (shortest != -1) {
        cout << "Shortest path from S to E: " << shortest << " steps" << endl;
    } else {
        cout << "No path found from S to E" << endl;
    }

    return 0;
}
