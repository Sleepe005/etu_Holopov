#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>

// Функция проверки валидности вводимых даннх
bool isSample(char strData[11]){
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

// Функция распарсирования строки
void Split(char data[11], int *value){
    char element[5] = "";
    int pos = 0;
    int j = 0;
    for(int i = 0; i < strlen(data); ++i){
        if(ispunct(data[i])){
            value[j] = atoi(element);
            j++;
            strcpy(element, "");
            pos = 0;
        }else{
            element[pos] = data[i];
            pos++;
        }
    }
    value[j] = atoi(element);
}

// Функция определения високосного года
bool visokosYear(int year){
    bool res;

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        res = true;
    }
    else{
        res = false;
    }

    return res;
}

// Функция подсчёта количества дней в месяце
int valDayInMonth(int year, int month){
    bool vis = visokosYear(year);

    int res;
    month%=12;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        res = 31;
    }
    else{
        if (month == 2){
            if (vis){
                res = 29;
            }
            else{
                res = 28;
            }
        }
        else{
            res = 30;
        }
    }

    return res;
}

// Функция проверки валидность даты
bool isValidDate(char strDate[11]){
    int dateValues[3] = {0};
    Split(strDate, dateValues);

    bool goodDate = false;
    if(dateValues[1] <= 12 && dateValues[0] <= valDayInMonth(dateValues[2], dateValues[1])){
        goodDate = true;
    }

    return goodDate;
}

int main(){
    // Установка языка, инициализация окна и цветов
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
    bkgd(COLOR_PAIR(2));
    attrset(COLOR_PAIR(1));
    clear();

    printw("Введите вашу дату рождения (ДД:ММ:ГГГГ): ");

    char birthDay[11];
    bool haveBirthDay = false;

    // считываем дату рождения, пока не получим валидные данные
    while(!haveBirthDay){
        scanw("%s\n", &birthDay);

        bool isSamle = true;    
        bool isValid = true;    
        if(!(isSample(birthDay) && isValidDate(birthDay))){
            clear();
            printw("Неверный формат ввод данных :(\nВведите вашу дату рождения снова: ");
            strcpy(birthDay, "");
            isSamle = false;
        }else{haveBirthDay = true;}
    }

    // Суммируем все цифры полученной даты
    int numbersSum = 0;
    for(int i = 0; i != strlen(birthDay); ++i){
        if(isdigit(birthDay[i])){
            numbersSum += birthDay[i]-'0';
        }
    }

    // Высчитываем старший аркан
    if(numbersSum > 22){numbersSum -= 22*(numbersSum/22);}

    clear();
    printw("Номер вашего старшего аркана - %d\n", numbersSum);
    getch();

    return 0;
}