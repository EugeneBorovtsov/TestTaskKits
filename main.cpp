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
    cout << kitsHandler.isKitInDocument(documentName, kitName) << endl;

    cout << argc << endl;
    return 0;
}