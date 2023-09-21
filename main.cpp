#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

// Структура для представления конечного автомата
struct FiniteAutomaton {
    set<int> states;  // Множество состояний
    int initial_state; // Исходное состояние
    set<int> final_states; // Множество финальных состояний
    map<pair<int, char>, int> transitions; // Функция переходов (состояние, символ) -> следующее состояние
};

// Функция для проверки, допускает ли автомат слово w
bool acceptsWord(const FiniteAutomaton& automaton, const string& w) {
    int current_state = automaton.initial_state;

    // Обработка w
    for (char c : w) {
        auto transition = automaton.transitions.find({ current_state, c });
        if (transition == automaton.transitions.end()) {
            return false; // Нет перехода для символа c
        }
        current_state = transition->second;
    }

    return automaton.final_states.count(current_state) > 0; // Проверка финального состояния
}

int main() {
    setlocale(LC_ALL, "Russian");
    FiniteAutomaton automaton;

    // Здесь задайте ваше фиксированное слово "w0"
    string w0 = "moloko";

    // Считывание данных о конечном автомате из файла
    ifstream input("automaton.txt");
    if (!input.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }

    // Считывание ||A||
    int alphabet_size;
    input >> alphabet_size;

    // Считывание ||S||
    int num_states;
    input >> num_states;

    // Считывание исходного состояния s0
    input >> automaton.initial_state;

    // Считывание ||F|| и финальных состояний
    int num_final_states;
    input >> num_final_states;
    for (int i = 0; i < num_final_states; i++) {
        int final_state;
        input >> final_state;
        automaton.final_states.insert(final_state);
    }

    // Считывание функции переходов
    int s, s_next;
    char a;
    while (input >> s >> a >> s_next) {
        automaton.transitions[{s, a}] = s_next;
    }

    input.close();

    // Запрос у пользователя ввода слова "w1"
    cout << "Введите слово w1: ";
    string w1;
    cin >> w1;

    // Проверка слова "w0 + w1"
    string w = w0 + w1;
    bool result = acceptsWord(automaton, w);

    if (result) {
        cout << "Конечный автомат допускает слово w = " << w << endl;
    }
    else {
        cout << "Конечный автомат не допускает слово w = " << w << endl;
    }

    return 0;
}
