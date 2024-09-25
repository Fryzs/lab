#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Перевірка на межі матриці
bool Cheking(int x, int y, int N) {
    return x >= 0 && y >= 0 && x < N && y < N;
}

// Заповнення матриці
void FillingMatrix(int** matrix, int N) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            matrix[r][c] = rand() % 10;
        }
    }
}

// Виведення матриці
void Cout(int** matrix, int N) {
    cout << "Matrix: " << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int findMaxSumSnake(int** matrix, int T, int N) {
    int x = 0;
    int y = 0;

    int maxSum = 0;
    int help = 0;
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (Cheking(nx, ny, N)) {
                if (help < matrix[nx][ny]) {
                    help = matrix[nx][ny];
                }
                x = nx;
                y = ny;
            }
        }
        maxSum += help;
    }
    return maxSum;
}

int findMaxSumRowCol(int** matrix, int& T, int N) {
    int x = 0;
    int y = 0;

    int maxSum = matrix[x][y];

    while (T > 0) {
        if (T == 0) break;

        int rowSum = 0;
        int colSum = 0;

        if (x + 1 < N) {
            for (int i = 0; i < N; ++i) {
                rowSum += matrix[x + 1][i];
            }
        }

        if (y + 1 < N) {
            for (int i = 0; i < N; ++i) {
                colSum += matrix[i][y + 1];
            }
        }

        if (rowSum > colSum && x + 1 < N && T > 0) {
            x++;
            maxSum += matrix[x][y];
            T--;
        }
        else if (y + 1 < N && T > 0) {
            y++;
            maxSum += matrix[x][y];
            T--;
        }
    }

    return maxSum;
}

int main() {
    int T, N;

    cout << "Enter size matrix: ";
    cin >> N;
    cout << "Enter steps: ";
    cin >> T;

    
    int** matrix = new int* [N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    FillingMatrix(matrix, N);
    Cout(matrix, N);
    cout << "Max sum by snake method: " << findMaxSumSnake(matrix, T, N) << endl;
    cout << "Max sum by Row-Col method: " << findMaxSumRowCol(matrix, T, N) << endl;


    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
