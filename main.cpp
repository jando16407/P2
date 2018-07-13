#include <fstream>          // File manipulation
#include <iostream>         // Input and output
#include <sstream>          // String steam for reading file contents
#include <stdio.h>          // Standart input and output
#include <stdlib.h>         // Standard library
#include <string>           // String related functions
#include <vector>           // For storing matricies
#include <unordered_map>    // HashTable

// Function prototypes
double calculateDeterminant(
    std::vector<std::vector<int>> inputMatrix, 
    int rowStartIndex, int rowEndIndex, int colStartIndex, int colEndIndex, 
    std::unordered_map<std::string, double> &determinantStore
);
std::string hashFunction(int rowStart, int rowEnd, int colStart, int colEnd);
std::vector<std::vector<int>> readFileMatrix();
void writeResult(double computedDeterminant);

// Main application
int main() {

    // Read the input file and store the generated matrix
    // in the 2D inputMatrix vector
    std::vector<std::vector<int>> inputMatrix = readFileMatrix();
    int matrixSize = inputMatrix.size();

    // HashTable for storage
    std::unordered_map<std::string, double> determinantStore;

    // Calculate the determinant of the input matrix
    double finalDeterminant = calculateDeterminant(
        inputMatrix,
        0, matrixSize - 1,
        0, matrixSize - 1,
        determinantStore
    );

    // Write the computed determinant to the output file
    writeResult(finalDeterminant);

    // Exit the progrom
    exit(EXIT_SUCCESS);

}

/* Function: Calculate Determinant
 * Description: Calculates the determinant for the submatrix of the inputMatrix
 *              starting at rowStartIndex and colStartIndex, and ending at
 *              rowEndIndex and colEndIndex
 * 
 * @input   std::vector<std::vector<int>> inputMatrix   The matrix generated from input.txt
 * @input   int rowStartIndex   The index at which rows start for the submatrix 
 * @input   int rowEndIndex     The index at which rows end for the submatrix
 * @input   int colStartIndex   The index at which columns start for the submatrix
 * @input   int colEndIndex     The index at which columns end for the submatrix
 * @input   std::unordered_map<std::string, double> &determinantStore   The (HashTable) storage for calculated determinants 
 * @returns double  The calculated determinant       
 */
double calculateDeterminant(std::vector<std::vector<int>> inputMatrix, 
    int rowStartIndex, 
    int rowEndIndex,
    int colStartIndex,
    int colEndIndex,
    std::unordered_map<std::string, double> &determinantStore
    ) {
    
    // Compute the size of the matrix
    int matrixSize = (rowEndIndex - rowStartIndex) + 1;
    // Stores a generated hash
    std::string generated_hash;

    // Base cases
    if (matrixSize == 1) return inputMatrix[rowStartIndex][colStartIndex];
    if (matrixSize == 2) return (inputMatrix[rowStartIndex][colStartIndex] * inputMatrix[rowEndIndex][colEndIndex]) - 
        (inputMatrix[rowStartIndex][colEndIndex] * inputMatrix[rowEndIndex][colStartIndex]);
    
    // Check if the hash table has a copy of the determinant
    std::unordered_map<std::string, double>::const_iterator hash = 
        determinantStore.find(hashFunction(rowStartIndex, rowEndIndex, colStartIndex, colEndIndex));
    // If it is found, return the stored determinant
    if (hash != determinantStore.end()){
        // std::cout << "Cache hit for " << hash->first << " at main" << std::endl;
        return hash->second;
    } 

    // Calculate the determinant of M(1..1)
    double numDet1;
    // Check if the hash table has a copy of the determinant
    hash = determinantStore.find(hashFunction(rowStartIndex + 1, rowEndIndex, colStartIndex + 1, colEndIndex));
    if (hash != determinantStore.end()){
        numDet1 = hash->second;
        // std::cout << "Cache hit for " << hash->first << " at numDet1" << std::endl;
    }
    // Otherwise we need to calculate it from scratch
    else {
        numDet1 = calculateDeterminant(inputMatrix, rowStartIndex + 1, rowEndIndex, colStartIndex + 1, colEndIndex, determinantStore);
        generated_hash = hashFunction(rowStartIndex + 1, rowEndIndex, colStartIndex + 1, colEndIndex);
        determinantStore[generated_hash] = numDet1;
        // std::cout << "Cache STORE for " << generated_hash << " at numDet1" << std::endl;
    }
    
    // Calculate the determinant of M(n..n)
    double numDet2;
    // Check if the hash table has a copy of the determinant
    hash = determinantStore.find(hashFunction(rowStartIndex, rowEndIndex - 1, colStartIndex, colEndIndex - 1));
    if (hash != determinantStore.end()){
        numDet2 = hash->second;
        // std::cout << "Cache hit for " << hash->first << " at numDet2" << std::endl;
    }
    // Otherwise we need to calculate it from scratch
    else {
        numDet2 = calculateDeterminant(inputMatrix, rowStartIndex, rowEndIndex - 1, colStartIndex, colEndIndex - 1, determinantStore);
        generated_hash = hashFunction(rowStartIndex, rowEndIndex - 1, colStartIndex, colEndIndex - 1);
        determinantStore[generated_hash] = numDet2;
        // std::cout << "Cache STORE for " << generated_hash << " at numDet2" << std::endl;
    }
    
    // Calculate the determinant of M(n..1)
    double numDet3;
    // Check if the hash table has a copy of the determinant
    hash = determinantStore.find(hashFunction(rowStartIndex + 1, rowEndIndex, colStartIndex, colEndIndex - 1));
    if (hash != determinantStore.end()){
        numDet3 = hash->second;
        // std::cout << "Cache hit for " << hash->first << " at numDet3" << std::endl;
    }
    // Otherwise we need to calculate it from scratch
    else {
        numDet3 = calculateDeterminant(inputMatrix, rowStartIndex + 1, rowEndIndex, colStartIndex, colEndIndex - 1, determinantStore);
        generated_hash = hashFunction(rowStartIndex + 1, rowEndIndex, colStartIndex, colEndIndex - 1);
        determinantStore[generated_hash] = numDet3;
        // std::cout << "Cache STORE for " << generated_hash << " at numDet3" << std::endl;
    }
    
    // Calculate the determinant of M(1..n)
    double numDet4;
    // Check if the hash table has a copy of the determinant
    hash = determinantStore.find(hashFunction(rowStartIndex, rowEndIndex - 1, colStartIndex + 1, colEndIndex));
    if (hash != determinantStore.end()){
        numDet4 = hash->second;
        // std::cout << "Cache hit for " << hash->first << " at numDet4" << std::endl;
    }
    // Otherwise we need to calculate it from scratch
    else {
        numDet4 = calculateDeterminant(inputMatrix, rowStartIndex, rowEndIndex - 1, colStartIndex + 1, colEndIndex, determinantStore);
        generated_hash = hashFunction(rowStartIndex, rowEndIndex - 1, colStartIndex + 1, colEndIndex);
        determinantStore[generated_hash] = numDet4;
        // std::cout << "Cache STORE for " << generated_hash << " at numDet4" << std::endl;
    }
    
    // Calculate the determinant of M(1..1, n..n)
    double denDet1;
    // Check if the hash table has a copy of the determinant
    hash = determinantStore.find(hashFunction(rowStartIndex + 1, rowEndIndex - 1, colStartIndex + 1, colEndIndex - 1));
    if (hash != determinantStore.end()){
        denDet1 = hash->second;
        // std::cout << "Cache hit for " << hash->first << " at denDet1" << std::endl;
    }
    // Otherwise we need to calculate it from scratch
    else {
        denDet1 = calculateDeterminant(inputMatrix, rowStartIndex + 1, rowEndIndex - 1, colStartIndex + 1, colEndIndex - 1, determinantStore);
        generated_hash = hashFunction(rowStartIndex + 1, rowEndIndex - 1, colStartIndex + 1, colEndIndex - 1);
        determinantStore[generated_hash] = denDet1;
        // std::cout << "Cache STORE for " << generated_hash << " at denDet1" << std::endl;
    }

    // Return the calculated value
    return ((numDet1 * numDet2) - (numDet3 * numDet4)) / denDet1;
}

/* Function: Read File Matrix
 * Description: This function reads the file 'input.txt' and turns the
 *              file contents into a 2D matrix using vectors. 
 * 
 * @returns std::vector<std::vector<int>>   The generated submatrix.       
 */
std::vector<std::vector<int>> readFileMatrix() {
    // Debug message
    // std::cout << "Reading input file... ";
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
    // Debug message
    // std::cout << "Done" << std::endl;
    // Return the generated matrix
    return generatedMatrix;

}

/* Function: Hash Function
 * Description: A hash function that generates a string key for a
 *              matrix located at a certain position and is of a 
 *              certain size
 * 
 * @input   int     rowStart    Starting index of the row
 * @input   int     rowEnd      Ending index of the row
 * @input   int     colStart    Starting index of the column
 * @input   int     colEnd      Ending index of the column 
 * @returns std::string The generated hash key
 */
std::string hashFunction(int rowStart, int rowEnd, int colStart, int colEnd) {
    return std::to_string(rowStart) + std::to_string(rowEnd) + std::to_string(colStart) + std::to_string(colEnd);
}

/* Function: Write Result
 * Description: This function writes the input to the file 'output.txt'.
 *              The input should be the computed determinant for the 
 *              input matrix.
 * 
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