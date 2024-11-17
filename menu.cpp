#include <ncurses.h>
#include <fstream>
#include <chrono>
#include "workWithDate.h"
#include "workWithData.h"

void printMenu(int cursePosition, bool isBirthDay, char birthDay[11]){
    char menu[4][75] = {
        "1. Ввести дату   ",
        "2. Узнать аркан  ",
        "3. Вывести лог   ",
        "4. Выход (esc x2)"
    };

    for(int i = 1; i <= 4; i++){
        printw("%s", menu[i-1]);
        
        if(isBirthDay && i == 1){
            printw("    %s", birthDay);
        }
        if(i == cursePosition){
            printw("   <--");
        }
        printw("\n");
    }
}

void doSomething(int doing, char* birthDay, bool* isBirthDay){
    switch (doing)
    {
    case 1:
    {
        clear();
        *isBirthDay = false;

        printw("Введите вашу дату рождения (ДД:ММ:ГГГГ): ");

        // считываем дату рождения, пока не получим валидные данные
        while(!*isBirthDay){
            scanw("%s\n", birthDay);

            bool isSamle = true;    
            bool isValid = true;    
            if(!(isSample(birthDay) && isValidDate(birthDay))){
                clear();
                printw("Неверный формат ввод данных :(\nВведите вашу дату рождения снова: ");
                strcpy(birthDay, "");
                isSamle = false;
            }else{*isBirthDay = true;}
        }

        std::ofstream datesLog("log.txt", std::ios_base::out || std::ios_base::ate);
        datesLog << birthDay << '\n';
        datesLog.close();

        // Суммируем все цифры полученной даты
        int numbersSum = 0;
        for(int i = 0; i != strlen(birthDay); ++i){
            if(isdigit(birthDay[i])){
                numbersSum += birthDay[i]-'0';
            }
        }
        break;
    }

    case 2:
    {
        clear();

        if(!(*isBirthDay)){
            printw("Вы не ввели дату рождения\n");
            printw("\nДля выхода в главное меню нажмите любую кнопку\n");
            getch();
            break;
        }

        auto begin = std::chrono::steady_clock::now();

        // Суммируем все цифры полученной даты
        int numbersSum = 0;
        for(int i = 0; i != strlen(birthDay); ++i){
            if(isdigit(birthDay[i])){
                numbersSum += birthDay[i]-'0';
            }
        }

        // Высчитываем старший аркан
        if(numbersSum > 22){numbersSum -= 22*(numbersSum/22);}

        printw("Номер вашего старшего аркана - %d\n", numbersSum);

        char line[500];
        std::ifstream arkan_text("info.txt");

        for(int i = 0; i < numbersSum - 1; i++){
            arkan_text.getline(line, 500);
        }
        arkan_text.getline(line, 500);
        arkan_text.close();

        printw("Описание вашего аркана: %s\n", line);

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        printw("Время работы алгоритма составило: %lld ns\n", elapsed_ms.count());

        printw("\nДля выхода в главное меню нажмите любую кнопку\n");
        getch();

        break;
    }

    case 3:
    {
        clear();
        
        char line[500];
        std::ifstream log_text("log.txt");

        while (!log_text.eof())
        { 
            log_text.getline(line, 500);
            printw("%s\n", line);
        }

        printw("\nДля выхода в меню нажмите любую кнопку");
        getch();

        break;
    }
    
    default:
        break;
    }
}

void menuFunc(){
    bool isExit = false;
    int cursePosition = 1;
    bool isBirthDay = false;
    char birthDay[11];


    while(!isExit){
        printMenu(cursePosition, isBirthDay, birthDay);

        int key;
        key = getch();
        if(key == 27){
            key = getch();
            if(key == 91){
                key = getch();
                if(key == 65){
                    cursePosition--;
                    if(cursePosition < 1){
                        cursePosition = 4;
                    }
                }
                if(key == 66){
                    cursePosition++;
                    if(cursePosition > 4){
                        cursePosition = 1;
                    }
                }
            }
            if (key == 27){
                isExit = true;
            }
        }else if(key == 10){
            doSomething(cursePosition, birthDay, &isBirthDay);
        }else if(key == 49){
            cursePosition = 1;
            doSomething(cursePosition, birthDay, &isBirthDay);
        }else if(key == 50){
            cursePosition = 2;
            doSomething(cursePosition, birthDay, &isBirthDay);
        }else if(key == 51){
            cursePosition = 3;
            doSomething(cursePosition, birthDay, &isBirthDay);
        }else if(key == 52){
            cursePosition = 4;
            isExit = true;
        }
        clear();
    }
}