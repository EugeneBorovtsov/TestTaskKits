#include "kitshandler.h"

using namespace std;

bool KitsHandler::isKitInDocument(string documentPath, string kitPath) {
    auto documentsRows = parseDocument(documentPath) ;
    auto kitsRows = parseKit(kitPath) ;
    auto kitsMap = kitVectorToMap(kitsRows);

    if (documentsRows.empty() || kitsRows.empty()) {
        cout << "ОДИН ИЗ ПАРАМЕТРОВ ПУСТ" << endl;
        return false;
    }

    vector<DocumentRow> checkoutOutput;

    for (auto document : documentsRows) {
        string kit = document.catalogs.back(); // Выбор последнего каталога из записи
        if (kitsMap.count(kit) && kitsMap[kit] > 0) {
            kitsMap[kit] -= document.amount;
            checkoutOutput.push_back(document);
        }
    }

    for (auto kitsResult : kitsMap) { // Проверка условия наличия набора в чеке
        if (kitsResult.second > 0) { 
            return false;
        }
    }

    cout << "Набор содержиться в документе." << endl;
    cout << "Состав набора" << endl;
    cout << "Поз. Кол-во Каталог" << endl;

    for (auto includedDocument : checkoutOutput) {
        cout << includedDocument.position << " " << includedDocument.amount + kitsMap[includedDocument.catalogs.back()] << " " << includedDocument.catalogs.back() << endl;
    }

    return true;
}
vector<DocumentRow> KitsHandler::parseDocument(string filePath) {
    vector<DocumentRow> rows;
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "FILE IS NOT OPEN" << endl;
        return rows;
    }

    string line;

    getline(file, line); // Пропуск первой строки
    
    while (getline(file, line)) {
        istringstream issDocument(line);
        DocumentRow row;

        issDocument >> row.position >> row.amount;
        
        string catalogsPart;
        getline(issDocument, catalogsPart);

        if (!catalogsPart.empty()) {
            istringstream issCatalogs(catalogsPart);
            string catalogName;
            while (getline(issCatalogs, catalogName, ',')) { // Сбор данных о каталогах
                catalogName.erase(0, catalogName.find_first_not_of(" "));
                catalogName.erase(catalogName.find_last_not_of(" ") + 1); // Удаление лишних пробелов
                row.catalogs.push_back(catalogName);
            }
        }

        rows.push_back(row);
    }

    return rows;
}

vector<KitRow> KitsHandler::parseKit(string filePath) {
    vector<KitRow> rows;
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "FILE IS NOT OPEN" << endl;
        return rows;
    }
    string line;

    getline(file, line); // Пропуск первой строки
    
    while (getline(file, line)) {
        istringstream iss(line);
        KitRow row;

        iss >> row.catalog >> row.amount;
        
        rows.push_back(row);
    }

    return rows;
}

map<string, int> KitsHandler::kitVectorToMap(vector<KitRow> kitVector) {
    map<string, int> kitMap; 

    for (auto kit : kitVector) {
        kitMap.insert({kit.catalog, kit.amount});     
    }

    return kitMap;
}