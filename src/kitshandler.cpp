#include "kitshandler.h"
#include <sstream>
#include <vector>

using namespace std;

bool KitsHandler::isKitInDocument(string documentPath, string kitPath) {
    auto documentsRows = parseDocument(documentPath) ;
    auto kitsRows = parseKit(kitPath) ;
    auto kitsMap = kitVectorToMap(kitsRows);

    for (auto document : documentsRows) {
        for (auto kit : document.catalogs) {
            cout << kit << endl;
            if (kitsMap.count(kit))
                kitsMap[kit] -= document.amount;
        }
    }

    for (auto kitsResult : kitsMap) {
        cout << kitsResult.second << endl;
        if (kitsResult.second > 0) {
            return false;
        }
    }
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

map<string, int> KitsHandler::kitVectorToMap(vector<KitRow> kitVector) {
    map<string, int> kitMap; 
    for (auto kit : kitVector) {
        kitMap.insert({kit.catalog, kit.amount});     
    }

    return kitMap;
}