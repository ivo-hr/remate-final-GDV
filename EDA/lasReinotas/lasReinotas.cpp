//enjuga


#include <iostream>
#include <vector>
using namespace std;
int resolver(int N, vector<bool>& fC, vector<bool>& dL, vector<bool>& dR, int fila = 0) {
    //Caso base: llegamos al final de la fila
    if (fila == N)
        return 1;

    int soluc = 0;

    for (int col = 0; col < N; col++) {
        //Índices de las diagonales
        int idL = fila - col + (N - 1);
        int idR = fila + col;

        if (!fC[col] && !dL[idL] && !dR[idR]) {
            fC[col] = true;
            dL[idL] = true;
            dR[idR] = true;

            soluc += resolver(N, fC, dL, dR, fila + 1);

            //Backtracking
            fC[col] = false;
            dL[idL] = false;
            dR[idR] = false;

        }
    }

    return soluc;
}

int main() {
    int M;
    cin >> M;

    for (int i = 0; i < M; i++) {
        int N;
        cin >> N;

        //Si bloqueamos la fila 1, la columna 1 tb está bloqueada
        vector<bool> filCol(N, false);
        //Diagonales "\"
        vector<bool> diagL((2 * N) - 1, false);
        //Diagonales "/"
        vector<bool> diagR((2 * N) - 1, false);

        cout << resolver(N, filCol, diagL, diagR) << endl;
    }

    return 0;
    }
