#include <iostream>
#include "Automata.h"

using namespace std;

class Automata {
private:
    int cash;
    vector<string> menu;
    vector<int> prices;
    STATES state;
    int currentDrink;

public:
    Automata() {
        state = OFF;
        cash = 0;
        currentDrink = -1;

        menu.push_back("Чай");
        menu.push_back("Эспрессо");
        menu.push_back("Латте");

        prices.push_back(15);
        prices.push_back(30);
        prices.push_back(50);
    }

    STATES getState() {
        return state;
    }

    void getMenu() {
        cout << "Меню:" << endl;
        for (int i = 0; i < menu.size(); i++) {
            cout << i << ": " << menu[i] << " - " << prices[i] << endl;
        }
    }

    void on() {
        if (state == OFF) {
            state = WAIT;
            cout << "Автомат включён" << endl;
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void off() {
        if (state == WAIT) {
            state = OFF;
            cout << "Автомат выключен" << endl;
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void coin(int sum) {
        if (state == WAIT || state == ACCEPT) {
            state = ACCEPT;
            cash += sum;
            cout << "Вы внесли " << sum << ", текущий баланс: " << cash << endl;
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void cancel() {
        if (state == ACCEPT || state == CHECK) {
            cout << "Заказ отменён, возврат: " << cash << endl;
            cash = 0;
            state = WAIT;
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void choice(int drinkIndex) {
        if (state == ACCEPT) {
            if (drinkIndex >= 0 && drinkIndex < menu.size()) {
                cout << "Вы выбрали: " << menu[drinkIndex] << endl;
                currentDrink = drinkIndex;
                state = CHECK;
            } else {
                cout << "Неверный индекс напитка" << endl;
            }
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void check() {
        if (state == CHECK) {
            if (cash >= prices[currentDrink]) {
                cout << "Денег достаточно, начинаем приготовление" << endl;
            } else {
                cout << "Недостаточно денег" << endl;
            }
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void cook() {
        if (state == CHECK) {
            state = COOK;
            cout << "Приготовление напитка: " << menu[currentDrink] << endl;
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }

    void finish() {
        if (state == COOK) {
            cout << "Напиток готов" << endl;
            if (cash > prices[currentDrink]) {
                cout << "Сдача: " << cash - prices[currentDrink] << endl;
            }
            cash = 0;
            state = WAIT;
            currentDrink = -1;
        } else {
            cout << "Некорректное состояние" << endl;
        }
    }
};
