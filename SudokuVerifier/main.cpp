#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


std::vector<char> splitSolutionToChars(std::string possible_solution) {
	std::vector<char> characters(possible_solution.begin(), possible_solution.end());
	return characters;
}

int verify(std::string solution) {
    std::vector<char> characters = splitSolutionToChars(solution);
    int k = 0;
    char numbers[9][9];
    for (int i = 0; i < 9; i++) {
    	for (int j = 0; j < 9; j++) {
    		numbers[i][j] = char(characters[k]);
    		k++;
    	}
    }

    //Testing the digits
    int solution_length = solution.length();
    if (solution_length != 81) {
    	return -1;
    }
    else {
    	bool positive_digit = (solution.find_first_not_of( "123456789" ) != std::string::npos);
    		if (positive_digit == true) {
    			//Incorrect digits
    			return -1;
    		}
    }

    // Testing the lines
    for (int i = 0; i < 9; i++) {
    	std::vector<char> list;
    	for (int j = 0; j < 9; j++) {
    		bool found = std::find(list.begin(), list.end(), numbers[i][j]) != list.end();
    		if (found == false) {
    			char x = char(numbers[i][j]);
    			list.push_back(x);
    		}
    		else {
    		//Incorrect line. Return -3.
    			return -3;
    		}
    	}
    }

    // Testing the rows
    for (int j = 0; j < 9; j++) {
    	std::vector<char> list;
    	for (int i = 0; i < 9; i++) {
    		bool found = std::find(list.begin(), list.end(), numbers[i][j]) != list.end();
    		if (found == false) {
    			char x = char(numbers[i][j]);
    			list.push_back(x);
    		}
    		else {
    		//Incorrect row. Return -4.
    			return -4;
    		}
    	}
    }

	// Testing the 3x3 sub-grids
	int lineStart = 0;
	int lineLimit = 3;
	int rowStart = 0;
	int rowLimit = 3;
	for (int g = 0; g < 3; g++) {
		for (int h = 0; h < 3; h++) {
			std::vector<char> list;
			for (int i = lineStart; i < lineLimit; i++) {
				for (int j = rowStart; j < rowLimit; j++) {
			    	bool loytyyko = std::find(list.begin(), list.end(), numbers[i][j]) != list.end();
					if (loytyyko == false) {
						char x = char(numbers[i][j]);
						list.push_back(x);
					}
					else {
						//Incorrect sub-grid. Return -2.
						return -2;
					}
				}
			}
			rowStart = rowStart+3;
			rowLimit = rowLimit+3;
		}
		lineStart = lineStart +3;
		lineLimit = lineLimit+3;
		rowStart = 0;
		rowLimit = 3;
	}

	// Valid solution. Return 0.
	return 0;
}

int main() {
    std::cout << "----SUDOKU VERIFIER----" << std::endl
    		<< "Valid solution:      0" << std::endl
			<< "Invalid digits:     -1" << std::endl
    		<< "Incorrect sub-grid: -2" << std::endl
			<< "Incorrect line:     -3" << std::endl
			<< "Incorrect row:      -4" << std::endl
			<< "(See help: verifier.pdf) \r" << std::endl;

    std::cout  << "--------RESULTS--------" << std::endl;
	std::ifstream myfile;
	myfile.open("solutions.txt");
	std::string line;
	int line_number = 0;
	while (std::getline(myfile, line)) {
		line_number++;
		if (verify(line) == 0) {
			std::cout << "Solution "<< line_number << ":          " <<  verify(line) << std::endl;;

		} else {
		std::cout << "Solution "<< line_number << ":         " <<  verify(line) << std::endl;;
		}
	}
    return 0;
}
