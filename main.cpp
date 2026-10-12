#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Direction arrays for moving in 4 directions (up, down, left, right)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// Function to perform BFS and return the sum of fish in the connected water region
int bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    int m = grid.size();
    int n = grid[0].size();
    int fish_count = 0;
    
    // Queue for BFS
    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    fish_count += grid[x][y];
    
    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        
        // Check all 4 adjacent cells
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            
            // Check if the new position is within bounds and is unvisited water
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] > 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                fish_count += grid[nx][ny];
                q.push({nx, ny});
            }
        }
    }
    
    return fish_count;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    // Read the grid
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    // Create a visited array to keep track of visited water cells
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    int max_fish = 0;
    
    // Iterate through all cells in the grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // If we find an unvisited water cell, start BFS from there
            if (grid[i][j] > 0 && !visited[i][j]) {
                int current_fish = bfs(grid, visited, i, j);
                max_fish = max(max_fish, current_fish);
            }
        }
    }
    
    cout << max_fish << endl;
    
    return 0;
}