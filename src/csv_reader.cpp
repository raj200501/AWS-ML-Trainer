#include "csv_reader.h"
#include "utils/file_utils.h"
#include "utils/string_utils.h"
#include "validation.h"
#include <sstream>
#include <stdexcept>

Dataset CsvReader::read(const std::string &filePath) const {
    if (!FileUtils::fileExists(filePath)) {
        throw std::runtime_error("CSV file not found: " + filePath);
    }

    const auto lines = FileUtils::readLines(filePath);
    if (lines.empty()) {
        throw std::runtime_error("CSV file is empty: " + filePath);
    }

    Dataset dataset;
    bool isHeader = true;
    for (const auto &line : lines) {
        const auto trimmed = StringUtils::trim(line);
        if (trimmed.empty() || StringUtils::startsWith(trimmed, "#")) {
            continue;
        }
        if (isHeader) {
            Validation::validateCsvHeader(trimmed);
            isHeader = false;
            continue;
        }

        const auto parts = StringUtils::split(trimmed, ',');
        if (parts.size() < 2) {
            throw std::runtime_error("CSV row has fewer than 2 columns: " + trimmed);
        }
        CsvRow row;
        row.feature = Validation::parseDouble(parts[0], "feature");
        row.target = Validation::parseDouble(parts[1], "target");
        dataset.rows.push_back(row);
    }

    if (dataset.rows.empty()) {
        throw std::runtime_error("CSV file contains no data rows: " + filePath);
    }

    return dataset;
}
