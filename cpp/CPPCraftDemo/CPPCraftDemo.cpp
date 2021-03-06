#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <chrono>
#include <iostream>
#include <ratio>

/**
    Represents a Record Object
*/
struct QBRecord
{
    int recordId;
    std::string stringValue;
};

/**
Represents a Record Collections
*/
typedef std::vector<QBRecord> QBRecordCollection;

/**
    Return records that contains a string in the StringValue field
    records - the initial set of records to filter
    matchString - the string to search for
*/
QBRecordCollection QBFindMatchingRecords(QBRecordCollection records, std::string matchString)
    {
    QBRecordCollection result;
    std::copy_if(records.begin(), records.end(), std::back_inserter(result), [matchString](QBRecord rec){return rec.stringValue.find(matchString) != std::string::npos; });
    return result;
    }

/**
    Utility to populate a record collection
    prefix - prefix for the string value for every record
    numRecords - number of records to populate in the collection
*/
QBRecordCollection populateDummyData(const std::string& prefix, int numRecords)
    {
    QBRecordCollection data;
    data.reserve(numRecords);
    for (int i = 0; i < numRecords; i++)
        {
        QBRecord rec = { i, prefix + std::to_string(i) };
        data.emplace_back(rec);
        }
    return data;
    }



int main(int argc, _TCHAR* argv[])
{
    using namespace std::chrono;
    // populate a bunch of data
    auto data = populateDummyData("testdata", 1000);
    // Find a record that contains and measure the perf
    auto startTimer = steady_clock::now();
    auto filteredSet = QBFindMatchingRecords(data, "testdata500");
    std::cout << "profiler: " << double((steady_clock::now() - startTimer).count()) * steady_clock::period::num / steady_clock::period::den << std::endl;

    // make sure that the function is correct
    assert(filteredSet.size() == 1);
	return 0;
}

