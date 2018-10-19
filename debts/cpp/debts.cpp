/*******************************************************************************
 *                                                                             *
 *  Filename    : debts.cpp                                                    *
 *  Project     : Debts                                                        *
 *  Version     : 1.0                                                          *
 *  Author      : Spiros Dontas                                                *
 *  Email       : spirosdontas@gmail.com                                       *
 *                                                                             *
 *  Description : ICPC NTUA                                                    *
 *                                                                             *
 *******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

class pay {

    public:
        int p, t;

        pay() {
            p = -1;
            t = -1;
        }

        pay(int p, int t) {
            this->p = p;
            this->t = t;
        }

        friend bool operator < (const pay &p1, const pay &p2) {
            if (p1.t == p2.t)
                return p1.p > p2.p;
            return p1.t < p2.t;
        }

};

using namespace std;

typedef vector<pay>::iterator payIter;

int main(int argc, char *argv[]) {

    int i, j;
    int N, M;

    cin >> N >> M;

    vector<vector<pay>> needed(N);

    for (i = 0; i < M; i++) {
        int P, X1, T1, X2, T2;
        cin >> P >> X1 >> T1 >> X2 >> T2;
        needed[X1 - 1].push_back(pay(-P, T1));
        needed[X2 - 1].push_back(pay(P, T2));
    }

    for (i = 0; i < N; i++) {
        sort(needed[i].begin(), needed[i].end());
    }

    for (i = 0; i < N; i++) {
        int start = 0;
        int current = 0;
        for (payIter j = needed[i].begin(); j != needed[i].end(); ++j) {
            current += j->p;
            if (current < 0) {
                start += -current;
                current = 0;
            }
        }
        cout << start << " ";
    }
    cout << endl;

    return 0;

}
