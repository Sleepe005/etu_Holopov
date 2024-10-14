#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>

// Функция проверки валидности вводимых даннх
bool isSample(char strData[12]){
    bool allDigIsDig = true;
    bool hasSep = true; // __.__.____ данные должны поступать в этом формате
    for(int i = 0; i < strlen(strData); ++i){
        if(i == 2 || i == 5){
            if(!ispunct(strData[i])){
                hasSep = false;
            }
        }else if(!isdigit(strData[i]))
            allDigIsDig = false;
        }
    return allDigIsDig && hasSep;
}

int main(){
    // Установка языка, инициализация окна и цветов
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    attrset(COLOR_PAIR(1));

    printw("Введите вашу дату рождения (ДД:ММ:ГГГГ): ");

    char birthDay[11];
    bool haveBirthDay = false;

    // считываем дату рождения, пока не получим валидные данные
    while(!haveBirthDay){
        scanw("%s\n", &birthDay);
        if(!isSample(birthDay)){
            clear();
            printw("Неверный формат ввод данных :(\nВведите вашу дату рождения снова: ");
        }else{
            haveBirthDay = true;
        }
    }

    // Суммируем все цифрв полученной даты
    int numbersSum = 0;
    for(int i = 0; i != strlen(birthDay); ++i){
        if(isdigit(birthDay[i])){
            numbersSum += birthDay[i]-'0';
        }
    }

    // Высчитываем старший аркан
    if(numbersSum > 22){numbersSum -= 22;}

    clear();
    printw("Номер вашего старшего аркана - %d\n", numbersSum);
    getch();
}