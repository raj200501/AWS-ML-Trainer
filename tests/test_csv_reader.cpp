#include "csv_reader.h"
#include "test_framework.h"
#include "test_paths.h"

TEST_CASE(CsvReaderReadsDataset) {
    CsvReader reader;
    Dataset dataset = reader.read(TestPaths::fixture("linear-data.csv"));
    REQUIRE(dataset.rows.size() >= 5);
    REQUIRE_NEAR(dataset.rows.front().feature, 1.0, 1e-6);
    REQUIRE_NEAR(dataset.rows.front().target, 3.0, 1e-6);
}
