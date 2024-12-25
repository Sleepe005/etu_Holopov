#include "workWithData.h"

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
    // month%=12;

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