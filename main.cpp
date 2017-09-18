//
//  main.cpp
//  MoutainPaths
//
//  Created by Darrell L. Hayden Jr. on 9/7/17.
//  Copyright © 2017 ITCS3122. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int *getMtn();
void createPPMFile(int, int* pMtnArray);
int findMax(int * pMtnArray);
int* greedyPath(int ** p2DMtnArray,int* pMtnArray, int);
int** convert1DArray(int * pMtnArray);
int convert2DArray(int,int);
void createPPMFileOutput(int, int* pLowPathArray, int* pMtnArray);

const int MAX = 230402;

int main(int argc, const char * argv[]) {
    cout << "Programming Assignment 2" << endl;
    
    
    int maxPixel = 0;
    int * mtnArray;
    int ** mtn2DArray;
    int * pLowPathArray;
    
    // Call to file
    mtnArray = getMtn();
    
    // Find the max pixel value in image
    maxPixel = findMax(mtnArray);
    
    // Create a ppm file of original image
    createPPMFile(maxPixel,mtnArray);
    
    // Converts original 1D array to 2D
    mtn2DArray = convert1DArray(mtnArray);
    cout << mtn2DArray[0][3] << endl;
    // Use greedy search alg. to find path
    pLowPathArray = greedyPath(mtn2DArray,mtnArray, maxPixel);
    
    createPPMFileOutput(maxPixel,pLowPathArray,mtnArray);
    return 0;
}



int* greedyPath(int ** p2DMtnArray, int* pMtnArray, int maxPixel){
    int x = 480/2;
    int y = 0;
    int count = 0;
    int value = 0;
    
    
    static int lowpath [MAX-2];
    
    for(int i = 0; i < 480; i++){
        lowpath[i] = pMtnArray[i];
    }

    int topRight = p2DMtnArray[x][y+1];
    int centerRight = p2DMtnArray[x][y+1];
    int bottomRight = p2DMtnArray[x+1][y+1];
    
    // Greedy alg.
    do{
    if(topRight <= centerRight && topRight <= bottomRight){
        x -= 1;
        y += 1;
        
        value = convert2DArray(x, y);
        
        lowpath[value] = -1;
        
        topRight = p2DMtnArray[x][y+1];
        centerRight = p2DMtnArray[x][y+1];
        bottomRight = p2DMtnArray[x+1][y+1];
    }
        
    else if(centerRight <= topRight && topRight <= bottomRight){
        x = x;
        y += 1;
        
        value = convert2DArray(x, y);
        
        lowpath[value] = -1;
        
        topRight = p2DMtnArray[x][y+1];
        centerRight = p2DMtnArray[x][y+1];
        bottomRight = p2DMtnArray[x+1][y+1];
    }
        
    else if(bottomRight < topRight &&  bottomRight < centerRight){
        x += 1;
        y += 1;
        
        value = convert2DArray(x, y);
        lowpath[value] = -1;
        
        topRight = p2DMtnArray[x][y+1];
        centerRight = p2DMtnArray[x][y+1];
        bottomRight = p2DMtnArray[x+1][y+1];
    }
    else{
        x = x;
        y += 1;
        
        value = convert2DArray(x, y);
        
        lowpath[value] = -1;
        
        topRight = p2DMtnArray[x][y+1];
        centerRight = p2DMtnArray[x][y+1];
        bottomRight = p2DMtnArray[x+1][y+1];
    }
        count++;
    }while(count < 480);
    
    return lowpath;
    
}

int *getMtn(){
    ifstream dataFile;
    
    static int myArray[MAX];
    
    // Read file data into array
    ifstream file("c1.txt");
    if(file.is_open())
    {
        
        for(int i = 0; i < MAX; ++i)
        {
            file >> myArray[i];//stores file contents in 1D array
        }
    }
    
    
    dataFile.close();
    
    return myArray;
}

// Creates a file in PPM image format
void createPPMFile(int maxPixel, int* pMtnArray){
    ofstream outputFile;
    
    string fileName = "ppmData.ppm";
    outputFile.open(fileName);
    
    // File header
    outputFile << "P3 " << endl;
    
    outputFile << "480 480 # Image height and width" << endl;
    outputFile << maxPixel << " # Image Max Pixel Value " << endl;
    
    for (int i = 2; i < MAX; i++) {
        outputFile << pMtnArray[i] << " " << pMtnArray[i] << " " << pMtnArray[i] << " ";
    }
    
    outputFile.close();
}

void createPPMFileOutput(int maxPixel, int* pLowPathArray,int* pMtnArray){
    ofstream outputFile;
    string fileName = "output.ppm";
    
    outputFile.open(fileName);
    
    // Output file header
    outputFile << "P3 " << endl;
    
    outputFile << "480 480 # Image height and width" << endl;
    outputFile << maxPixel << " # Image Max Pixel Value " << endl;

    // image data: loops over all the pixels and sets them all to red if on path
    for (int i = 0; i < MAX; i++) {
        if(pLowPathArray[i] == -1){
            outputFile << maxPixel << " " << 0 << " " << 0 << " ";
        }
        else{
            outputFile << pMtnArray[i] << " " << pMtnArray[i] << " " << pMtnArray[i] << " ";
        }
    }
    
    outputFile.close();
}


// Find the the max pixel value in array
int findMax(int* pMtnArray){
    int temp = 0;
    
    for(int i = 2; i < MAX; i++){
        if(pMtnArray[i] > temp){
            temp = pMtnArray[i];
        }
    }
    
    return temp;
    
}

// Converts 2D coord to 1D
int convert2DArray(int row, int col)
{
    return 480 * row + col;
}

int **convert1DArray(int* pMtnArray){
    //int * pMtnArray2;
    int** array2D = 0;
    array2D = new int*[480];
    int counter = 2;
    
    for(int i = 0; i < 480; ++i )
    {
        array2D[i] = new int[480];
        for(int j = 0; j < 480; ++j ) {
            array2D[i][j] = pMtnArray[counter];
            counter++;
        }
    }
    
    return array2D;
}
