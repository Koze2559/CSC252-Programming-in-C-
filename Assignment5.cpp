#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ----------------------------------------------------
// Function headers required by assignment
// ----------------------------------------------------
bool binary_search_recursive(int* values, int key, int start, int end);
bool binary_search(int* values, int key, int size);
void createBinaryFile(string filename);
void selection_sort(int* values, int size);
void writeBinary(string filename, int* values, int length);

// ----------------------------------------------------
// Binary search recursive function
// ----------------------------------------------------
bool binary_search_recursive(int* values, int key, int start, int end)
{
    if (start > end)
    {
        return false;
    }

    int middle = start + (end - start) / 2;

    if (values[middle] == key)
    {
        return true;
    }
    else if (key < values[middle])
    {
        return binary_search_recursive(values, key, start, middle - 1);
    }
    else
    {
        return binary_search_recursive(values, key, middle + 1, end);
    }
}

// ----------------------------------------------------
// Binary search helper function
// ----------------------------------------------------
bool binary_search(int* values, int key, int size)
{
    return binary_search_recursive(values, key, 0, size - 1);
}

// ----------------------------------------------------
// Selection sort
// ----------------------------------------------------
void selection_sort(int* values, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < size; j++)
        {
            if (values[j] < values[min_index])
            {
                min_index = j;
            }
        }

        if (min_index != i)
        {
            int temp = values[i];
            values[i] = values[min_index];
            values[min_index] = temp;
        }
    }
}

// ----------------------------------------------------
// Writes integer array to binary file
// ----------------------------------------------------
void writeBinary(string filename, int* values, int length)
{
    ofstream outFile(filename, ios::binary);

    if (!outFile)
    {
        cout << "Error opening file for writing." << endl;
        return;
    }

    outFile.write(reinterpret_cast<char*>(values), length * sizeof(int));
    outFile.close();
}

// ----------------------------------------------------
// Creates binary file with random values
// ----------------------------------------------------
void createBinaryFile(string filename)
{
    const int SIZE = 1000;
    int values[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        values[i] = rand() % 1000;
    }

    writeBinary(filename, values, SIZE);
}

// ----------------------------------------------------
// BinaryReader class
// ----------------------------------------------------
class BinaryReader
{
private:
    int* values;
    int size;

public:
    BinaryReader(string filename)
    {
        values = nullptr;
        size = 0;
        readValues(filename);
    }

    ~BinaryReader()
    {
        delete[] values;
    }

    int* getValues()
    {
        return values;
    }

    int getSize()
    {
        return size;
    }

    void readValues(string filename)
    {
        ifstream inFile(filename, ios::binary);

        if (!inFile)
        {
            cout << "Error opening file for reading." << endl;
            return;
        }

        inFile.seekg(0, ios::end);
        int bytes = static_cast<int>(inFile.tellg());
        inFile.seekg(0, ios::beg);

        size = bytes / sizeof(int);

        values = new int[size];

        inFile.read(reinterpret_cast<char*>(values), bytes);
        inFile.close();
    }
};

// ----------------------------------------------------
// Analyzer superclass
// ----------------------------------------------------
class Analyzer
{
protected:
    int* values;
    int size;

public:
    Analyzer(int* values, int size)
    {
        this->values = cloneValues(values, size);
        this->size = size;
    }

    virtual ~Analyzer()
    {
        delete[] values;
    }

    int* cloneValues(int* source, int sourceSize)
    {
        int* copy = new int[sourceSize];

        for (int i = 0; i < sourceSize; i++)
        {
            copy[i] = source[i];
        }

        return copy;
    }

    virtual string analyze() = 0;
};

// ----------------------------------------------------
// DuplicatesAnalyzer
// Counts total duplicated values
// ----------------------------------------------------
class DuplicatesAnalyzer : public Analyzer
{
public:
    DuplicatesAnalyzer(int* values, int size)
        : Analyzer(values, size)
    {
    }

    string analyze() override
    {
        selection_sort(values, size);

        int duplicateCount = 0;

        for (int i = 1; i < size; i++)
        {
            if (values[i] == values[i - 1])
            {
                duplicateCount++;
            }
        }

        stringstream output;
        output << "There were " << duplicateCount << " duplicated values";

        return output.str();
    }
};

// ----------------------------------------------------
// MissingAnalyzer
// Counts missing values from 0 to 999
// ----------------------------------------------------
class MissingAnalyzer : public Analyzer
{
public:
    MissingAnalyzer(int* values, int size)
        : Analyzer(values, size)
    {
    }

    string analyze() override
    {
        selection_sort(values, size);

        int missingCount = 0;

        for (int i = 0; i < 1000; i++)
        {
            if (!binary_search(values, i, size))
            {
                missingCount++;
            }
        }

        stringstream output;
        output << "There were " << missingCount << " missing values";

        return output.str();
    }
};

// ----------------------------------------------------
// SearchAnalyzer
// Searches for 100 random values from 0 to 999
// ----------------------------------------------------
class SearchAnalyzer : public Analyzer
{
public:
    SearchAnalyzer(int* values, int size)
        : Analyzer(values, size)
    {
        selection_sort(this->values, this->size);
    }

    string analyze() override
    {
        int foundCount = 0;

        for (int i = 0; i < 100; i++)
        {
            int randomValue = rand() % 1000;

            if (binary_search(values, randomValue, size))
            {
                foundCount++;
            }
        }

        stringstream output;
        output << "There were " << foundCount
               << " out of 100 random values found";

        return output.str();
    }
};

// ----------------------------------------------------
// StatisticsAnalyzer
// Finds min, max, mean, median, and mode
// ----------------------------------------------------
class StatisticsAnalyzer : public Analyzer
{
public:
    StatisticsAnalyzer(int* values, int size)
        : Analyzer(values, size)
    {
    }

    string analyze() override
    {
        selection_sort(values, size);

        int minimum = values[0];
        int maximum = values[size - 1];

        double sum = 0;

        for (int i = 0; i < size; i++)
        {
            sum += values[i];
        }

        double mean = sum / size;

        double median;

        if (size % 2 == 0)
        {
            median = (values[size / 2 - 1] + values[size / 2]) / 2.0;
        }
        else
        {
            median = values[size / 2];
        }

        int mode = values[0];
        int modeCount = 1;

        int currentValue = values[0];
        int currentCount = 1;

        for (int i = 1; i < size; i++)
        {
            if (values[i] == currentValue)
            {
                currentCount++;
            }
            else
            {
                if (currentCount > modeCount)
                {
                    mode = currentValue;
                    modeCount = currentCount;
                }

                currentValue = values[i];
                currentCount = 1;
            }
        }

        if (currentCount > modeCount)
        {
            mode = currentValue;
            modeCount = currentCount;
        }

        stringstream output;

        output << "The minimum value is " << minimum << endl;
        output << "The maximum value is " << maximum << endl;
        output << "The mean value is " << mean << endl;
        output << "The median value is " << median << endl;
        output << "The mode value is " << mode
               << " which occurred " << modeCount << " times";

        return output.str();
    }
};

// ----------------------------------------------------
// Main program
// ----------------------------------------------------
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    string filename = "values.bin";

    createBinaryFile(filename);

    BinaryReader reader(filename);

    int* values = reader.getValues();
    int size = reader.getSize();

    StatisticsAnalyzer statisticsAnalyzer(values, size);
    DuplicatesAnalyzer duplicatesAnalyzer(values, size);
    MissingAnalyzer missingAnalyzer(values, size);
    SearchAnalyzer searchAnalyzer(values, size);

    cout << statisticsAnalyzer.analyze() << endl;
    cout << duplicatesAnalyzer.analyze() << endl;
    cout << missingAnalyzer.analyze() << endl;
    cout << searchAnalyzer.analyze() << endl;

    return 0;
}