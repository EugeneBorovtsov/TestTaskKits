#ifndef KITSHANDLER_H
#define KITSHANDLER_H

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct DocumentRow {
    int position;
    int amount;
    vector<string> catalogs;
};

struct KitRow {
    string catalog;
    int amount;
};

class KitsHandler {
    public:
        bool isKitInDocument(string documentPath, string kitPath);

    protected:
        vector<DocumentRow> parseDocument(string filePath);
        vector<KitRow> parseKit(string filePath);
        map<string, int> kitVectorToMap(vector<KitRow> kitVector);
};

#endif // KITSHANDLER_H