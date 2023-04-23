#include <iostream>
#include<bits/stdc++.h>

using namespace std;

struct state{
    unsigned int cannibals = 3;
    unsigned int missionaries = 3;
    unsigned int g = 0;
    unsigned int h = 0;
    unsigned int f = 0;
    bool boat = 0;
    struct state* prev = NULL;

    bool operator<(const state& n) const {
        return f > n.f; // for the priority queue to order nodes by lowest f_cost
    }
};

bool IsNegativeCondition(state curState) {
    bool a = false;
    bool b = false;

    if (curState.missionaries > 0 && curState.missionaries < curState.cannibals)
        a = true;
    if (curState.missionaries < 3 && curState.missionaries > curState.cannibals)
        b = true;
    return a + b;
}

state Forward1Cannibal(state curState) {
    // 1 Cannibal move forward
    curState.cannibals -= 1;
    return curState;
}

state Forward2Cannibals(state curState) {
    // 2 Cannibals move forward
    curState.cannibals -= 2;
    return curState;
}

state Forward1Cannibal1Missionary(state curState) {
    // 1 Cannibal move forward and 1 Missionary move forward
    curState.cannibals -= 1;
    curState.missionaries -= 1;
    return curState;
}

state Forward1Missionary(state curState) {
    // 1 Missionary move forward
    curState.missionaries -= 1;
    return curState;
}

state Forward2Missionaries(state curState) {
    // 2 Missionaries move forward
    curState.missionaries -= 2;
    return curState;
}

state Backward1Cannibal(state curState) {
    // 1 Cannibal move backward
    curState.cannibals += 1;
    return curState;
}

state Backward2Cannibals(state curState) {
    // 2 Cannibals move backward
    curState.cannibals += 2;
    return curState;
}

state Backward1Cannibal1Missionary(state curState) {
    // 1 Cannibal move backward and 1 Missionary move backward
    curState.cannibals += 1;
    curState.missionaries += 1;
    return curState;
}

state Backward1Missionary(state curState) {
    // 1 Missionary move backward
    curState.missionaries += 1;
    return curState;
}

state Backward2Missionaries(state curState) {
    // 2 Missionaries move backward
    curState.missionaries += 2;
    return curState;
}

int GetHeuristic(state curState) {
    return curState.missionaries + curState.cannibals; // d[cur(x,y) -> goal(0,0)]
}

state SetF(state curState, state prevState) {
    curState.prev = new state;
    *curState.prev = prevState;
    curState.boat = !prevState.boat;
    curState.g = prevState.g + 1;
    curState.h = GetHeuristic(curState);
    curState.f = curState.g + curState.h;
    return curState;
}

bool IsGoalState(state curState){
    return curState.missionaries + curState.cannibals == 0;
}

bool checkIfExist(priority_queue<state>& pq, const state& node) {
    priority_queue<state> temp_pq = pq;
    while (!temp_pq.empty()) {
        if (temp_pq.top().cannibals == node.cannibals &&
            temp_pq.top().missionaries == node.missionaries &&
            temp_pq.top().boat == node.boat)
            return true;
        temp_pq.pop();
    }
    return false;
}

bool checkIfExist(vector<state> vt, state curState) {
    for (int i = 0; i < vt.size(); i++) {
        if (vt[i].cannibals == curState.cannibals &&
            vt[i].missionaries == curState.missionaries &&
            vt[i].boat == curState.boat)
            return true;
    }
    return false;
}

vector<state> getNeighbors(state curState) {
    vector<state> vt_temp;
    bool boat = curState.boat;
    if (boat == 1) {
        if (curState.cannibals >= 1) {
            state temp = Forward1Cannibal(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.cannibals >= 2) {
            state temp = Forward2Cannibals(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.cannibals >= 1 && curState.missionaries >= 1) {
            state temp = Forward1Cannibal1Missionary(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.missionaries >= 1) {
            state temp = Forward1Missionary(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.missionaries >= 2) {
            state temp = Forward2Missionaries(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
    }
    else {
        if (curState.cannibals < 3) {
            state temp = Backward1Cannibal(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.cannibals < 2) {
            state temp = Backward2Cannibals(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.cannibals < 3 && curState.missionaries < 3) {
            state temp = Backward1Cannibal1Missionary(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.missionaries < 3) {
            state temp = Backward1Missionary(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.missionaries <= 1) {
            state temp = Backward2Missionaries(curState);
            temp = SetF(temp, curState);
            if (!IsNegativeCondition(temp)) {
                vt_temp.push_back(temp);
            }
        }
    }
    return vt_temp;
}

void print(state* goal) {
    cout << goal->cannibals << " " << goal->missionaries << endl;
    do {
        goal = goal->prev;
        cout << goal->cannibals << " " << goal->missionaries << endl;
    } while (goal->prev != NULL);
}

template <typename T>
void astar(T curState, vector<T> (*getNeighbors)(T), bool (*isGoal)(T), void (*print)(T*)) {
    priority_queue <T> open;
    vector<T> close;
    open.push(curState);

    T* goal = new T;
    int isOut = false;

    while(open.size() > 0) {
        curState = open.top();
        open.pop();

        vector<T> vt_temp = getNeighbors(curState);

        for (T i: vt_temp) {
            if (isGoal(i)) {
                goal = &i;
                isOut = true;
                break;
            }
        }

        if (isOut)
            break;

        for (T i: vt_temp) {
            if (!checkIfExist(close, i) && !checkIfExist(open, i)) {
                open.push(i);
            }
        }
        close.push_back(curState);
    }

    print(goal);
}

int main() {
    state curState;
    curState.cannibals = 3;
    curState.missionaries = 3;
    curState.boat = 1;

    astar(curState, &getNeighbors, &IsGoalState, &print);

    return 0;
}