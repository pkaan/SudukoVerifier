#include <iostream>
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
	//Valid solution
    std::string possible_solution1 = "417369825632158947958724316825437169791586432346912758289643571573291684164875293";
    //Incorrect sub-grid
    std::string possible_solution2 = "123456789912345678891234567789123456678912345567891234456789123345678912234567891";
    //Incorrect line
    std::string possible_solution3 = "111111111912345678891234567789123456678912345567891234456789123345678912234567891";
    //Incorrect row
    std::string possible_solution4 = "123456789123456789123456789123456789123456789123456789123456789123456789123456789";
    //Not positive digits
    std::string possible_solution5 = "1234567-9123456789123456789123456789123456789123456789123456789123456789123456789";

    std::cout << "----SUDOKU VERIFIER----" << std::endl
    		<< "Valid solution:      0" << std::endl
			<< "Invalid digits:     -1" << std::endl
    		<< "Incorrect sub-grid: -2" << std::endl
			<< "Incorrect line:     -3" << std::endl
			<< "Incorrect row:      -4" << std::endl
			<< "(See help: verifier.pdf) \r" << std::endl;

    std::cout  << "--------RESULTS--------" << std::endl;
    std::cout << "Solution 1: " << "Number:  "<< verify(possible_solution1) << std::endl;
    std::cout << "Solution 2: " << "Number: "<< verify(possible_solution2) << std::endl;
    std::cout << "Solution 3: " << "Number: "<< verify(possible_solution3) << std::endl;
    std::cout << "Solution 4: " << "Number: "<< verify(possible_solution4) << std::endl;
    std::cout << "Solution 5: " << "Number:  "<< verify(possible_solution5) << std::endl;

    return 0;
}
