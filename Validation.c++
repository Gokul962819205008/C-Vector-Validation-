#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

int N;
vector<vector<char>> grid;
vector<pii> portals;

bool isValid(int x, int y, vector<vector<bool>>& visited) {
    return x >= 0 && x < N && y >= 0 && y < N && !visited[x][y] && grid[x][y] != '#';
}

pii getNextPortal(pii current) {
    for (int i = 0; i < portals.size(); i++) {
        if (portals[i] == current) {
            return portals[(i + 1) % portals.size()];
        }
    }
    return current;
}

int shortestPathWithPortals() {
    pii start, end;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'S') start = {i, j};
            else if (grid[i][j] == 'E') end = {i, j};
            else if (grid[i][j] == 'P') portals.push_back({i, j});
        }
    }

    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<pair<pii, int>> q;

    q.push({start, 0});
    visited[start.first][start.second] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pii curr = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (curr == end) return steps;

        for (int d = 0; d < 4; d++) {
            int nx = curr.first + dx[d];
            int ny = curr.second + dy[d];

            if (isValid(nx, ny, visited)) {
                if (grid[nx][ny] == 'P') {
                    pii tele = getNextPortal({nx, ny});
                    if (!visited[tele.first][tele.second]) {
                        visited[tele.first][tele.second] = true;
                        q.push({tele, steps + 1});
                    }
                } else {
                    visited[nx][ny] = true;
                    q.push({{nx, ny}, steps + 1});
                }
            }
        }
    }

    return -1;
}

int main() {
    cin >> N;
    grid = vector<vector<char>>(N, vector<char>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid[i][j];

    cout << shortestPathWithPortals() << endl;
    return 0;
}
