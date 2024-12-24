#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "menu.h"
#include "workWithData.h"
#include "workWithDate.h"
#include "fstream"

TEST_CASE("Valid format input data", "[isSample]"){
    SECTION("Проверить корректность обработки допустимых значений ввода"){
        REQUIRE(isSample("01.02.2006"));
        REQUIRE(isSample("01,02,2006"));
        REQUIRE(isSample("02;05;2006"));
        REQUIRE(isSample("02[05[2006"));
    }
    
    REQUIRE_FALSE(isSample("qw.er.dfgh"));
}

TEST_CASE("Valid input date", "[isValidDate]"){
    SECTION("Проверить поведение при некорректных значениях (например, несуществующие даты или символы вместо чисел)."){
        REQUIRE_FALSE(isValidDate("02.13.2006"));
        REQUIRE_FALSE(isValidDate("29.02.2021"));
    }

    SECTION("Проверить граничные значения диапазона (минимальные и максимальные допустимые значения)."){
        REQUIRE(isValidDate("31.12.2008"));
        REQUIRE(isValidDate("29.02.2024"));
    }

    REQUIRE(isValidDate("02.05.2006"));
    REQUIRE_FALSE(isValidDate("32.06.2006"));
}

TEST_CASE("Valid arcan calculate", "[calculateArcan]"){
    SECTION("Проверить правильность расчетов в зависимости от входных данных."){
        REQUIRE(calculateArcan("02.05.2006") == 15);
        REQUIRE_FALSE(calculateArcan("02.05.2006") != 15);

        REQUIRE(calculateArcan("01]01]1990") == 21);
        REQUIRE_FALSE(calculateArcan("01[01]1990") != 21);

        REQUIRE(calculateArcan("31.12.9999") == 21);
        REQUIRE_FALSE(calculateArcan("31.12.9999") != 21);
    }
}

TEST_CASE("Write in file", "[writeLogInFile]"){
    SECTION("Проверить, что данные корректно записываются в файл."){
        writeLogInFile("test", "test_log.txt");
        
        char fline[500];
        std::ifstream file("test_log.txt");
        file.getline(fline, 500);
        REQUIRE(std::string(fline) == "test");
        file.close();
    }
}