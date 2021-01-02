#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

static char sudoku_grid[9][9];

std::vector<char> split(std::string solution) {
	//Split the string
	std::vector<char> characters(solution.begin(), solution.end());
	return characters;
}

void buildGrid(std::string solution) {
	//Build the grid
    std::vector<char> digits = split(solution);
    int count = 0;
    for (int line = 0; line < 9; line++) {
    	for (int row = 0; row < 9; row++) {
    		sudoku_grid[line][row] = char(digits[count]);
    		count++;
    	}
    }
}

bool verifyDigits(std::string solution) {
	//Verifying the digits. No characters or negative numbers allowed. Length of the solution has to be 81.
	int solution_length = solution.length();
	if (solution_length != 81) {
	//Invalid length
		return false;
	}
	else {
		bool positive_digit = (solution.find_first_not_of( "123456789" ) != std::string::npos);
	    if (positive_digit == true) {
	    	//Incorrect digits
	    	return false;
	    }
	}
	return true;
}

int verifyLines(char sudoku_grid [9][9]) {
	 for (int line = 0; line < 9; line++) {
	    	std::vector<char> list_of_digits;
	    	for (int row = 0; row < 9; row++) {
	    		bool digit_found = std::find(list_of_digits.begin(), list_of_digits.end(), sudoku_grid[line][row]) != list_of_digits.end();
	    		if (digit_found == false) {
	    			//The line so far is valid
	    			char new_digit = char(sudoku_grid[line][row]);
	    			list_of_digits.push_back(new_digit);
	    		}
	    		else {
	    		//Incorrect line
	    			return false;
	    		}
	    	}
	    }
	 return true;
}

bool verifyRows(char sudoku_grid[9][9]) {
    for (int row = 0; row < 9; row++) {
    	std::vector<char> list_of_digits;
    	for (int line = 0; line < 9; line++) {
    		bool digit_found = std::find(list_of_digits.begin(), list_of_digits.end(), sudoku_grid[line][row]) != list_of_digits.end();
    		if (digit_found == false) {
    			//The row so far is valid
    			char new_digit = char(sudoku_grid[line][row]);
    			list_of_digits.push_back(new_digit);
    		}
    		else {
    		//Incorrect row
    			return false;
    		}
    	}
    }
    return true;
}

bool verifySubGrids(char sudoku_grid[9][9]) {
	int lineStart = 0, lineLimit = 3, rowStart = 0, rowLimit = 3;
	for (int line = 0; line < 3; line++) {
		for (int row = 0; row < 3; row++) {
			std::vector<char> list;
			for (int i = lineStart; i < lineLimit; i++) {
				for (int j = rowStart; j < rowLimit; j++) {
			    	bool loytyyko = std::find(list.begin(), list.end(), sudoku_grid[i][j]) != list.end();
					if (loytyyko == false) {
						char x = char(sudoku_grid[i][j]);
						list.push_back(x);
					}
					else {
						//Incorrect sub-grid
						return false;
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
	return true;
}

int verify(std::string solution) {
    //Build grid (9x9)
	buildGrid(solution);

	//Verify Digits. If not valid return -1.
	if (verifyDigits(solution) == false) {
		return -1;
	}

    // Verify lines. If not valid return -3.
    if (verifyLines(sudoku_grid) == false) {
    	return -3;
    }

    // Verify rows. If not valid return -4.
    if (verifyRows(sudoku_grid) == false) {
    	return -4;
    }

	// Verify 3x3 sub-grids. If not valid return -2.
    if (verifySubGrids(sudoku_grid) == false) {
    	return -2;
    }

	// Valid solution. Return 0.
	return 0;
}

void showInfo() {
    std::cout << "----SUDOKU VERIFIER----" << std::endl
    		<< "Valid solution:      0" << std::endl
			<< "Invalid digits:     -1" << std::endl
    		<< "Incorrect sub-grid: -2" << std::endl
			<< "Incorrect line:     -3" << std::endl
			<< "Incorrect row:      -4" << std::endl
			<< "(See help: verifier.pdf) \r" << std::endl;
}

void start() {
	//Show info
	showInfo();
	//Open the file containing the solutions.
	std::ifstream myfile;
	myfile.open("solutions.txt");
	std::string line;
	int line_number = 0;
	//Go through the file line by line. Verify solutions and show the results.
    std::cout  << "--------RESULTS--------" << std::endl;
	while (std::getline(myfile, line)) {
		line_number++;
		if (verify(line) == 0) {
			std::cout << "Solution "<< line_number << ":          " <<  verify(line) << std::endl;;

		} else {
			std::cout << "Solution "<< line_number << ":         " <<  verify(line) << std::endl;;
		}
	}
}

int main() {
	start();
    return 0;
}
