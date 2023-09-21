#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

// ��������� ��� ������������� ��������� ��������
struct FiniteAutomaton {
    set<int> states;  // ��������� ���������
    int initial_state; // �������� ���������
    set<int> final_states; // ��������� ��������� ���������
    map<pair<int, char>, int> transitions; // ������� ��������� (���������, ������) -> ��������� ���������
};

// ������� ��� ��������, ��������� �� ������� ����� w
bool acceptsWord(const FiniteAutomaton& automaton, const string& w) {
    int current_state = automaton.initial_state;

    // ��������� w
    for (char c : w) {
        auto transition = automaton.transitions.find({ current_state, c });
        if (transition == automaton.transitions.end()) {
            return false; // ��� �������� ��� ������� c
        }
        current_state = transition->second;
    }

    return automaton.final_states.count(current_state) > 0; // �������� ���������� ���������
}

int main() {
    setlocale(LC_ALL, "Russian");
    FiniteAutomaton automaton;

    // ����� ������� ���� ������������� ����� "w0"
    string w0 = "moloko";

    // ���������� ������ � �������� �������� �� �����
    ifstream input("automaton.txt");
    if (!input.is_open()) {
        cout << "�� ������� ������� ����." << endl;
        return 1;
    }

    // ���������� ||A||
    int alphabet_size;
    input >> alphabet_size;

    // ���������� ||S||
    int num_states;
    input >> num_states;

    // ���������� ��������� ��������� s0
    input >> automaton.initial_state;

    // ���������� ||F|| � ��������� ���������
    int num_final_states;
    input >> num_final_states;
    for (int i = 0; i < num_final_states; i++) {
        int final_state;
        input >> final_state;
        automaton.final_states.insert(final_state);
    }

    // ���������� ������� ���������
    int s, s_next;
    char a;
    while (input >> s >> a >> s_next) {
        automaton.transitions[{s, a}] = s_next;
    }

    input.close();

    // ������ � ������������ ����� ����� "w1"
    cout << "������� ����� w1: ";
    string w1;
    cin >> w1;

    // �������� ����� "w0 + w1"
    string w = w0 + w1;
    bool result = acceptsWord(automaton, w);

    if (result) {
        cout << "�������� ������� ��������� ����� w = " << w << endl;
    }
    else {
        cout << "�������� ������� �� ��������� ����� w = " << w << endl;
    }

    return 0;
}
