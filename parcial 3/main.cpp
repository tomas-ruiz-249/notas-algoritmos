#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int NUM_USERS = 1000;
const int MAX_CONNECTIONS = 30;
const int MAX_CONTENTS = 500;
const int MAX_RATINGS = 50;

class Valoracion {
public:
    int userId;
    int score; // [1, 10]
    Valoracion(int userId, int score) : userId(userId), score(score) {}
};

class Contenido {
public:
    int creatorId;
    vector<Valoracion> valoraciones;

    Contenido(int creatorId) : creatorId(creatorId) {}
};

class Usuario {
public:
    int id;
    vector<int> conexiones;
    vector<Contenido> contenidos;

    Usuario(int id) : id(id) {}
};

class MediaNest {
private:
    vector<vector<bool>> grafo;
    vector<Usuario> usuarios;

public:
    MediaNest() {
        grafo.resize(NUM_USERS, vector<bool>(NUM_USERS, false));
        usuarios.reserve(NUM_USERS);
        srand(time(0));

        // Crear usuarios
        for (int i = 0; i < NUM_USERS; ++i) {
            usuarios.emplace_back(i);
        }

        // Generar conexiones aleatorias
        for (int i = 0; i < NUM_USERS; ++i) {
            int numConex = rand() % MAX_CONNECTIONS + 1;
            unordered_set<int> conexiones;
            while (conexiones.size() < numConex) {
                int j = rand() % NUM_USERS;
                if (j != i && !grafo[i][j]) {
                    grafo[i][j] = grafo[j][i] = true;
                    usuarios[i].conexiones.push_back(j);
                    usuarios[j].conexiones.push_back(i);
                    conexiones.insert(j);
                }
            }
        }

        // Generar contenidos y valoraciones
        for (int i = 0; i < NUM_USERS; ++i) {
            int numContenidos = rand() % MAX_CONTENTS + 1;
            for (int j = 0; j < numContenidos; ++j) {
                Contenido contenido(i);
                int numValoraciones = rand() % MAX_RATINGS + 1;
                for (int k = 0; k < numValoraciones; ++k) {
                    int userVal = rand() % NUM_USERS;
                    int score = rand() % 10 + 1;
                    contenido.valoraciones.emplace_back(userVal, score);
                }
                usuarios[i].contenidos.push_back(contenido);
            }
        }
    }

    void most_connected() {
        int maxUser = 0, maxConnections = -1;

        for (auto &u : usuarios) {
            if ((int)u.conexiones.size() > maxConnections) {
                maxConnections = u.conexiones.size();
                maxUser = u.id;
            }
        }

        int height = graphHeightDFS(maxUser);
        cout << "El usuario con más conexiones es " << maxUser << " con " << maxConnections << " conexiones\n";
        cout << "La altura del grafo desde el nodo " << maxUser << " es " << height << "\n";
    }

    int graphHeightDFS(int start) {
        vector<bool> visited(NUM_USERS, false);
        stack<pair<int, int>> s;
        s.push({start, 0});
        int maxDepth = 0;

        while (!s.empty()) {
            auto [node, depth] = s.top(); s.pop();
            if (visited[node]) continue;
            visited[node] = true;
            maxDepth = max(maxDepth, depth);
            for (int i = 0; i < NUM_USERS; ++i) {
                if (grafo[node][i] && !visited[i]) {
                    s.push({i, depth + 1});
                }
            }
        }
        return maxDepth;
    }

    void mostPositiveRaters() {
        vector<int> positiveCount(NUM_USERS, 0);

        for (auto &u : usuarios) {
            for (auto &c : u.contenidos) {
                for (auto &v : c.valoraciones) {
                    if (v.score >= 7) {
                        positiveCount[v.userId]++;
                    }
                }
            }
        }

        int maxUser = 0, maxCount = 0;
        for (int i = 0; i < NUM_USERS; ++i) {
            if (positiveCount[i] > maxCount) {
                maxCount = positiveCount[i];
                maxUser = i;
            }
        }

        cout << "El usuario que más valoraciones positivas ha dado es " << maxUser
             << " con " << maxCount << " valoraciones >= 7\n";
    }

    void farthestNeighbor(int A) {
        vector<int> dist(NUM_USERS, -1);
        queue<int> q;
        dist[A] = 0;
        q.push(A);
        int farthest = A;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < NUM_USERS; ++v) {
                if (grafo[u][v] && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (dist[v] > dist[farthest]) farthest = v;
                    q.push(v);
                }
            }
        }

        cout << "El vecino más lejano del usuario " << A << " está a " << dist[farthest] << " saltos\n";
    }

    void pathWithIntermediate(int A, int B, int C) {
        struct Estado {
            int nodo;
            int contieneC; // 0 = false, 1 = true
            int saltos;
        };

        queue<Estado> q;
        q.push({A, (A == C) ? 1 : 0, 0});

        vector<vector<bool>> visited(NUM_USERS, vector<bool>(2, false));
        visited[A][(A == C) ? 1 : 0] = true;

        while (!q.empty()) {
            Estado actual = q.front();
            q.pop();

            if (actual.saltos > 7) continue;

            if (actual.nodo == B && actual.contieneC == 1) {
                cout << "Existe un camino entre " << A << " y " << B
                    << " pasando por " << C << " con distancia de "
                    << actual.saltos << " saltos\n";
                return;
            }

            for (int vecino = 0; vecino < NUM_USERS; ++vecino) {
                if (vecino != actual.nodo && grafo[actual.nodo][vecino]) {
                    int nuevoContieneC = actual.contieneC || (vecino == C) ? 1 : 0;
                    if (!visited[vecino][nuevoContieneC]) {
                        visited[vecino][nuevoContieneC] = true;
                        q.push({vecino, nuevoContieneC, actual.saltos + 1});
                    }
                }
            }
        }

        cout << "No existe un camino entre " << A << " y " << B
            << " pasando por " << C << " con max 7 saltos\n";
    }




};


int main() {
    MediaNest mn;
    cout << "Se crearon 1000 usuarios\n";
    mn.most_connected();
    mn.mostPositiveRaters();
    mn.farthestNeighbor(47); // ejemplo
    // Elección aleatoria de A, B, C
    int A, B, C;
    do {
        A = rand() % NUM_USERS;
        B = rand() % NUM_USERS;
        C = rand() % NUM_USERS;
    } while (A == B || A == C || B == C);

    mn.pathWithIntermediate(A, B, C);

    return 0;
}
