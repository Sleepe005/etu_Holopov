#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include "workWithDate.h"
#include "menu.h"

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