/*******************************************************************************
 *                                                                             *
 *  Filename    : speedlimit.cpp                                               *
 *  Project     : SpeedLimit                                                   *
 *  Version     : 1.0                                                          *
 *  Author      : Spiros Dontas                                                *
 *  Email       : spirosdontas@gmail.com                                       *
 *                                                                             *
 *  Description : ICPC NTUA                                                    *
 *                                                                             *
 *******************************************************************************/

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

#define MAXV 500

class state {
    public :
        int from, to, v, l;
        double cost;
        state *previous;

        state() {
            from = -1;
            to = -1;
            v = -1;
            l = -1;
            cost = numeric_limits<double>::max();
            previous = nullptr;
        }

        state(int from, int to, int v, int l, double cost, state *previous) {
            this->from = from;
            this->to = to;
            this->v = v;
            this->l = l;
            this->cost = cost;
            this->previous = previous;
        }

        state(const state &other) {
            this->from = other.from;
            this->to = other.to;
            this->v = other.v;
            this->l = other.l;
            this->cost = other.cost;
            this->previous = other.previous;
        }

        void print() {
            cout << from << " " << to << " " << v << " " << l << " " << cost << endl;
        }

};

struct compareState {
    bool operator () (const state &a, const state &b) {
        return a.cost > b.cost;
    }
};

typedef vector<state>::iterator stateIt;
typedef priority_queue<state, vector<state>, compareState> prioq;

int main() {

    int i, j;
    int N, M, D;

    cin >> N >> M >> D;

    vector<vector<double>> best(N);
    for (i = 0; i < N; i++) {
        best[i] = vector<double>(MAXV + 1, numeric_limits<double>::max());
    }

    vector<vector<state>> neighbors(N);

    for (i = 0; i < M; i++) {
        int from, to, v, l;
        cin >> from >> to >> v >> l;
        neighbors[from].push_back(state(from, to, v, l, numeric_limits<double>::max(), nullptr));
    }

    int start = 0;
    int end = D;
    double minimum = numeric_limits<double>::max();

    state *final;

    prioq remaining;

    for (stateIt it = neighbors[start].begin(); it != neighbors[start].end(); ++it) {
        int v = it->v;
        if (v == 0)
            v = 70;
        best[it->to][v] = 1.0 * it->l / v;
        remaining.push(state(it->from, it->to, v, it->l, 1.0 * it->l / v, nullptr));
    }

    while (!(remaining.empty())) {
        state current = remaining.top();
        remaining.pop();
        if (current.to == end) {
            if (current.cost < minimum) {
                minimum = current.cost;
                final = new state(current);
            }
            continue;
        }
        for (stateIt it = neighbors[current.to].begin(); it != neighbors[current.to].end(); ++it) {
            int v = it->v;
            if (v == 0)
                v = current.v;
            double c = 1.0 * it->l / v;
            c += current.cost;
            if (c < best[it->to][v]) {
                best[it->to][v] = c;
                remaining.push(state(it->from, it->to, v, it->l, c, new state(current)));
            }
        }
    }

    vector<int> previous;
    while (final != nullptr) {
        previous.push_back(final->to);
        final = final->previous;
    }
    previous.push_back(start);

    for (i = previous.size() - 1; i > 0; i--) {
        cout << previous[i] << " ";
    }
    cout << previous[0] << endl;

    return 0;
}
