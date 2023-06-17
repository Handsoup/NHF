#include "crossSections.h"
#include "csv.h"
#include <iostream>
#include <vector>
#include <sstream>

void processCrossSections(double rho, const std::string& csvFilePath, std::vector<std::vector<double>>& data) {
  io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'> > in(csvFilePath);
  in.read_header(io::ignore_extra_column, "column1", "column2", "column3", "column4");

  double column1;
  double column2;
  double column3;
  double column4;

  while (in.read_row(column1, column2, column3, column4)) {
    // Store the values in a row vector
    std::vector<double> row;
    row.push_back(column1);
    row.push_back(column2);
    row.push_back(column3);
    row.push_back(column4);

    // Add the row vector to the 2D vector
    data.push_back(row);

    // Process the rest of the data
    // Modify this section to perform the desired operations on the data
  /*  // For example, you can print the values or perform calculations
    std::cout << "Column 1: " << column1 << std::endl;
    std::cout << "Column 2: " << column2 << std::endl;
    std::cout << "Column 3: " << column3 << std::endl;
    std::cout << "Column 4: " << column4 << std::endl;
    std::cout << std::endl;*/
  }

  for (int i = 0; i < data.size(); i++) {
    for (int j = 1; j < data[i].size(); j++) {
      data[i][j] = data[i][j] * rho;
    }
  }

  std::vector<double> newColumn;

  for (int i = 0; i < data.size(); i++) {
    newColumn.push_back(data[i][1] + data[i][2] + data[i][3]);
  }

  if (data.size() != newColumn.size()) {
    std::cout << "Error: The dimensions of the vectors don't match." << std::endl;
    return;
  }

  for (size_t i = 0; i < data.size(); i++) {
    data[i].push_back(newColumn[i]);
  }

/*  // Print the 2D vector
  std::cout << "Data in the 2D vector:" << std::endl;
  for (const auto& row : data) {
    for (const auto& value : row) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }*/
}

