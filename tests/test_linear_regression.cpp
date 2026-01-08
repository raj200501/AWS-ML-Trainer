#include "csv_reader.h"
#include "linear_regression.h"
#include "test_framework.h"
#include "test_paths.h"

TEST_CASE(LinearRegressionFitsExpectedSlope) {
    CsvReader reader;
    Dataset dataset = reader.read(TestPaths::fixture("linear-data.csv"));

    LinearRegression regression;
    RegressionModel model = regression.fit(dataset);
    RegressionMetrics metrics = regression.evaluate(dataset, model);

    REQUIRE_NEAR(model.slope, 2.0, 1e-2);
    REQUIRE_NEAR(model.intercept, 1.0, 1e-2);
    REQUIRE(metrics.r2 > 0.98);
}
