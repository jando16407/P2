#include <fstream>      // File manipulation
#include <iostream>     // Input and output
#include <map>          // For storing computed determinant results
#include <sstream>      // String steam for reading file contents
#include <stdio.h>      // Standart input and output
#include <stdlib.h>     // Standard library
#include <string>       // String related functions
#include <vector>       // For storing matricies

// Function prototypes
double calculateDeterminant(std::vector<std::vector<int>> inputMatrix, int matrixSize, std::map<std::string,int> &determinantStore);

std::vector<std::vector<int>> generateSubmatrix(std::vector<std::vector<int>> inputMatrix, int matrixSize, int removeRow, int removeColumn);

std::vector<std::vector<int>> readFileMatrix();

void writeResult(double computedDeterminant);




int main() {

    // Read the input file and store the generated matrix
    // in the 2D inputMatrix vector
    std::vector<std::vector<int>> inputMatrix = readFileMatrix();
    int matrixSize = inputMatrix.size();

    // Create a map to store the results of previously computed
    // determinants for sub-matrices
    std::map<std::string, int> calculatedDeterminants;

    // Calculate the determinant of the input matrix
    double finalDeterminant = calculateDeterminant(inputMatrix, matrixSize, calculatedDeterminants);

    // Write the computed determinant to the output file
    writeResult(finalDeterminant);

    // Exit the progrom
    exit(EXIT_SUCCESS);

}

/* Function: Calculate the Determinant
 * Description: The function calculates the determinant of the
 *              specified input n x n matrix and stores the re-
 *              sults of computed determinants in the input map.
 * @input   std::vector<std::vector<int>>   inputMatrix
 * @input   int                             matrixSize
 * @input   std::map<std::string, int>&     determinantStore
 * @returns double  The determinant of the input matrix.       
 */
double calculateDeterminant(std::vector<std::vector<int>> inputMatrix, int matrixSize, std::map<std::string,int> &determinantStore) {

    // Handle provided base cases where the matrix size
    // is either 1 x 1, 2 x 2, or 3 x 3
    if (matrixSize == 1) return inputMatrix[0][0];
    else if (matrixSize == 2) return (inputMatrix[0][0] * inputMatrix[1][1]) - (inputMatrix[0][1] * (inputMatrix[1][0]));
    else if (matrixSize == 3) return (inputMatrix[0][0] * inputMatrix[1][1] * inputMatrix[2][2]) - (inputMatrix[0][0] * inputMatrix[1][2] * inputMatrix[2][1]) - (inputMatrix[0][1] * inputMatrix[1][0] * inputMatrix[2][2]) + (inputMatrix[0][1] * inputMatrix[1][2] * inputMatrix[2][0]) + (inputMatrix[0][2] * inputMatrix[1][0] * inputMatrix[2][1]) - (inputMatrix[0][2] * inputMatrix[1][1] * inputMatrix[2][0]);

    // Otherwise, prepare to compute the determinant
    else {

        // Calculate det(M:1..1)
        double numeratorDet1 = calculateDeterminant(
            generateSubmatrix(inputMatrix, matrixSize, 0, 0),
            matrixSize - 1,
            determinantStore
        );

        // Calculate det(M:n..n)
        double numeratorDet2 = calculateDeterminant(
            generateSubmatrix(inputMatrix, matrixSize, matrixSize-1, matrixSize-1),
            matrixSize - 1,
            determinantStore
        );
        
        // Calculate det(M:n..1)
        double numeratorDet3 = calculateDeterminant(
            generateSubmatrix(inputMatrix, matrixSize, 0, matrixSize-1),
            matrixSize - 1,
            determinantStore
        );
        
        // Calculate det(M:1..n)
        double numeratorDet4 = calculateDeterminant(
            generateSubmatrix(inputMatrix, matrixSize, matrixSize-1, 0),
            matrixSize - 1,
            determinantStore
        );

        // Calculate det(M:1..1,n..n)
        double denominatorDet = calculateDeterminant(
            generateSubmatrix(
                generateSubmatrix(
                    inputMatrix,
                    matrixSize,
                    0, 0
                ),
                matrixSize - 1,
                matrixSize - 2, matrixSize - 2
            ),
            matrixSize - 2,
            determinantStore
        );

        // Return the computed determinant
        return ((numeratorDet1 * numeratorDet2) - (numeratorDet3 * numeratorDet4)) / denominatorDet;

    }

}

/* Function: Generate Specified Submatrix
 * Description: The function removes the specified row and column
 *              from the input matrix, and then returns the resulting
 *              matrix.
 * @input   std::vector<std::vector<int>>   inputMatrix
 * @input   int                             matrixSize
 * @input   int                             removeRow
 * @input   int                             removeColumn
 * @returns std::vector<std::vector<int>>   The generated submatrix.       
 */
std::vector<std::vector<int>> generateSubmatrix(std::vector<std::vector<int>> inputMatrix, int matrixSize, int removeRow, int removeColumn) {

    // Store the resulting matrix after the specified
    // row and column are removed
    std::vector<std::vector<int>> generatedSubmatrix;

    // Loop through the rows in the inputMatrix
    for (int currentRow = 0; currentRow < matrixSize; currentRow++) {
        // If we are not removing the current row,
        // Prepare to add it to the generatedSubmatrix
        if (currentRow != removeRow) {
            // Storage for row with modified column values
            std::vector<int> rowVector;
            // Loop though the elements in the current row
            for (int currentColumn = 0; currentColumn < matrixSize; currentColumn++) {
                // If we are not removing the current column,
                // add it to the rowVector
                if (currentColumn != removeColumn)
                    rowVector.push_back(inputMatrix[currentRow][currentColumn]);
            }
            // Push the finalized rowVector into the 
            // generatedSubmatrix
            generatedSubmatrix.push_back(rowVector);
        }
    }

    // Return the generated submatrix
    return generatedSubmatrix;

}

/* Function: Read File Matrix
 * Description: This function reads the file 'input.txt' and turns the
 *              file contents into a 2D matrix using vectors. 
 * @returns std::vector<std::vector<int>>   The generated submatrix.       
 */
std::vector<std::vector<int>> readFileMatrix() {
    
    // Storage for 2D matrix
    std::vector<std::vector<int>> generatedMatrix;
    int matrixSize;

    // Input file object
    std::ifstream inputFile;
    
    // Open the 'input.txt' file
    inputFile.open("input.txt");
    
    // If 'input.txt' does not exist, display an
    // error message and exit the program citing
    // that there was a failure
    if (!inputFile) {
        std::cout << "Unable to open file" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read the matrixSize from file
    std::string currentLine;
    int currentNumber;
    std::getline(inputFile, currentLine);
    matrixSize = std::stoi(currentLine);

    // Read the rest of the file line by line
    while (std::getline(inputFile, currentLine)) {
        // Vector for the current row
        std::vector<int> rowVector;
        // Parse the current line
        std::stringstream stream(currentLine);
        // Read matrixSize number of integers from the
        // string and store them in the rowVector
        for (int n = 0; n < matrixSize; n++) {
            stream >> currentNumber;
            rowVector.push_back(currentNumber);
        }
        // Push the row into the final 2D vector
        generatedMatrix.push_back(rowVector);
    }

    // Close the file and return the 
    // generated matrix
    inputFile.close();
    return generatedMatrix;

}

/* Function: Write Result
 * Description: This function writes the input to the file 'output.txt'.
 *              The input should be the computed determinant for the 
 *              input matrix.
 * @input   int     computedDeterminant 
 * @returns void       
 */
void writeResult(double computedDeterminant) {
    // Output file to store the result
    std::ofstream outputFile("output.txt");
    // Write the determinant result to file
    outputFile << computedDeterminant;
    // Close the file
    outputFile.close();
}