#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <conio.h> 
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>

std::string generate_hex(size_t length) 
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << hex_digits[dis(gen)];
    }

    return ss.str();
}

int random(int ott, int doo)
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(ott, doo); 
    int a = 0;
    for(int n=0; n<40; ++n)
        a = distr(gen);
    return a;
}

std::string int_to_string(int num) {
    std::ostringstream ss;
    ss << num;
    return ss.str();
}


int main() {
    printf("\x1B[31mATTENTION! \nIf you run the program not as Administrator, close it and run as Administrator.\033[0m\t\t\n");
    //setlocale(LC_ALL, "Russian");
    std::cout << "Choose your provider:\n"
    << "1 - MGTS(Moscow)              " << "2 - Rostelecom(Moscow)\n"
    << "3 - Beeline/Corbina(Tula)     " << "4 - Sibirskie Seti(Novokuznetsk)\n"
    << "5 - Beeline(Sochi)            " << "6 - P.a.k.t LLC(Saint Petersburg)\n"
    << "7 - ubsnet.ru(Sevastopol)     " << "8 - Park Telecom(Krasnotur'insk)\n"
    << "9 - Annet(Tver)               " << "10 - Weba(Saint Petersburg)\n" 
    << "To close unchanged, press - 0" << std::endl
    ;;
    int action;
    std::string arguments1;
    std::cin >> action;
    switch (action)
    {
    case 1:
    arguments1 = "-5 -e1 -f1";
        break;
    case 6:
    arguments1 = "-6";
        break;
    case 8:
    arguments1 = "-5";
        break;
    case 9:
    arguments1 = "-6 -e1";
        break;
    default:
        arguments1 = "-5 -e1";
        break;
    }
    system("cls");

    std::stringstream arguments_ss;
    arguments_ss << arguments1 << " --fake-gen " << int_to_string(random(1, 30))
                 << " --blacklist ..\\russia-blacklist.txt --blacklist ..\\russia-youtube.txt --fake-from-hex "
                 << generate_hex(116);

    std::string arguments = arguments_ss.str();

    std::replace(arguments.begin(), arguments.end(), '\n', ' ');

    std::cout << "arguments:" << arguments << std::endl;

    std::ofstream batch_file("script.bat");
    if (batch_file.is_open()) {
        batch_file << "@ECHO OFF\n";
        batch_file << "PUSHD \"%~dp0\"\n";
        batch_file << "set _arch=x86\n";
        batch_file << "IF \"%PROCESSOR_ARCHITECTURE%\"==\"AMD64\" (set _arch=x86_64)\n";
        batch_file << "IF DEFINED PROCESSOR_ARCHITEW6432 (set _arch=x86_64)\n";
        batch_file << "PUSHD \"%_arch%\"\n";
        batch_file << "\n";
        batch_file << "start \"\" goodbyedpi.exe " << arguments << "\n";
        batch_file << "\n";
        batch_file << "POPD\n";
        batch_file << "POPD\n";
        batch_file.close();
        std::cout << "Batch the file was created successfully." << std::endl;
    } else {
        std::cout << "Failed to create a batch file." << std::endl;
        return 1;
    }

    system("script.bat");
    Sleep(1000);
    system("service_install_russia_blacklist.cmd");
    return 0;
}
