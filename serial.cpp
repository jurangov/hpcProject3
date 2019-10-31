#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class CSVReader
{
    std::string fileName;
    std::string delimeter;

    public:CSVReader(std::string filename, std::string delim = ",") :
                    fileName(filename), delimeter(delim)
    {}

    std::vector<std::vector<std::string> > getData();
};

std::vector<std::vector<std::string> > CSVReader::getData()
{
	std::ifstream file(fileName);
 
	std::vector<std::vector<std::string> > dataList;
 
	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	// Close the File
	file.close();
 
	return dataList;
}

struct SaleData
{
    int store;
    int dept;
    string date;
    int weeklySale;
    bool isHoliday;
};

struct DeptSales
{
    std::vector<SaleData> sales;
};

struct StoreSales
{
    std::vector<DeptSales> sales;
};

struct GlobalSales
{
    std::vector<StoreSales> sales;
};

int main()
{
	// Creating an object of CSVWriter
	CSVReader reader("example.csv");
 
	// Get the data from CSV File
	std::vector<std::vector<std::string> > dataList = reader.getData();
    std::vector<SaleData> deptSales;

    int index = 0;
    int dataElement = 0;
    int deptCounter = 0;
    int storeCounter = 0;

    
 
	for(std::vector<std::string> vec : dataList)
	{
        if (index >= 1)
        {
            dataElement = 0;
            int storeAux = 0;
            int deptAux = 0;
            string dateAux = "";
            int weeklySaleAux = 0;
            bool isHolidayAux = false;

            for(std::string data : vec)
		    {
                switch (dataElement)
                {
                case 0:
                    storeAux = stoi(data);
                    break;
                case 1:
                    deptAux = stoi(data);
                    break;
                case 2:
                    dateAux = data;
                    break;
                case 3:
                    weeklySaleAux = stoi(data);
                    break;
                case 4:
                    istringstream(data) >> std::boolalpha >> isHolidayAux;
                    break;
                default:
                    break;
                }
                dataElement++;
			    //std::cout<<data << " , ";
		    }

            if (storeCounter != storeAux)
            {
                StoreSales store;
                if (deptCounter != deptAux)
                {
                    SaleData dept = {storeAux, deptAux, dateAux, weeklySaleAux, isHolidayAux};
                }
            }
            deptCounter = deptAux;
            storeCounter = storeAux;

            SaleData sale = SaleData(storeAux, deptAux, dateAux, weeklySaleAux, isHolidayAux);
            deptSales.push_back(SaleData);
            std::cout<<std::endl;
        }
        
        index++;
	}
	return 0;
 
}

