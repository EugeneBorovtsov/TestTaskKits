#include <iostream>

#include "src/kitshandler.h"

using namespace std;

int main(int argc, char* argv[]) {
    if ((argc - 1) < 2) { // -1 для вычета названия файла
        cout << "ПЕРЕДАНО НЕДОСТАТОЧНО АРГУМЕНТОВ" << endl;
        return 1;
    }

    string documentName = argv[1];
    string kitName = argv[2];

    KitsHandler kitsHandler;
    if (!kitsHandler.isKitInDocument(documentName, kitName)) {
        cout << "НАБОР НЕ ВХОДИТ В ДОКУМЕНТ" << endl;
    }

    return 0;
}