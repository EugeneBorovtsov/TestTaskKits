#include "kitshandler.h"
#include <sstream>

using namespace std;

bool KitsHandler::isKitInDocument(string documentPath, string kitPath) {
    auto documentsRows = parseDocument(documentPath) ;
    auto kitsRows = parseKit(kitPath) ;

    return true;
}

vector<DocumentRow> KitsHandler::parseDocument(string filePath) {
    vector<DocumentRow> rows;
    ifstream file(filePath);
    string line;

    getline(file, line); // Пропуск первой строки
    
    while (getline(file, line)) {
        istringstream issDocument(line);
        DocumentRow row;

        issDocument >> row.position >> row.amount;
        
        string catalogsPart;
        getline(issDocument, catalogsPart);

        istringstream issCatalogs(catalogsPart);

        if (!catalogsPart.empty()) {
            string catalogName;
            while (getline(issCatalogs, catalogName, ',')) // Сбор данный о каталогах
                row.catalogs.push_back(catalogName);
        }

        rows.push_back(row);
    }

    return rows;
}

vector<KitRow> KitsHandler::parseKit(string filePath) {
    vector<KitRow> rows;
    ifstream file(filePath);
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