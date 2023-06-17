#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> matrix = {{1, 2, 3},
                                            {4, 5, 6},
                                            {7, 8, 9}};

    std::vector<int> newColumn = {10, 20, 30};

    if (matrix.size() != newColumn.size()) {
        std::cout << "Error: The dimensions of the vectors don't match." << std::endl;
        return 0;
    }

    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].push_back(newColumn[i]);
    }

    // Print the modified 2D vector
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

