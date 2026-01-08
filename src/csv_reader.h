#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>

struct CsvRow {
    double feature = 0.0;
    double target = 0.0;
};

struct Dataset {
    std::vector<CsvRow> rows;
};

class CsvReader {
public:
    Dataset read(const std::string &filePath) const;
};

#endif // CSV_READER_H
