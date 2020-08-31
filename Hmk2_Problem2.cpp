/*Ciprian Alex Cornila
ECE 4122
09/22/2018
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

/*struct that holds neighbors to check
 * relative to a particular data location
*/
struct Neighbors
{
    double product;
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int n6;
    int n7;
    int n8;
};

int main()
{
  
    //input file request
    string fileName;
    cout << "enter the file name: ";
    cin >> fileName;
    ifstream infile;
    infile.open(fileName);
    if (!infile)
    {
        cerr << "err file";
        exit(1);
    }

    int rows;
    int cols;
    infile >> rows >> cols;
    //2D array that will store data from file
    double** data = new double*[rows];
    for(int i = 0; i < rows; ++i)
    {
        data[i] = new double[cols];
    }

    int j = 0; // Count the number of values we've retrieved
    while (!infile.eof())
    {
        /*read data from file into the matrix structure*/
        infile >> data[j/cols][j%cols];
        j++;
    }
    //init maxProduct
    double maxProduct = 0;
    /*struct that refrences neighbors relative to data point
    to the left and right*/
    Neighbors Horizontal;
    Horizontal.n1=0;
    Horizontal.n2=1;
    Horizontal.n3=2;
    Horizontal.n4=3;
    Horizontal.n5=0;
    Horizontal.n6=0;
    Horizontal.n7=0;
    Horizontal.n8=0;

    /*struct that refrences neighbors
    up and down relative to a point */
    Neighbors Vertical;
    Vertical.n1 = 0;
    Vertical.n2 = 0;
    Vertical.n3 = 0;
    Vertical.n4 = 0;
    Vertical.n5 = 0;
    Vertical.n6 = 1;
    Vertical.n7 = 2;
    Vertical.n8 = 3;

    /*neighbors on the main diagonal */
    Neighbors mainDiag;
    mainDiag.n1 = 0;
    mainDiag.n2 = 1;
    mainDiag.n3 = 2;
    mainDiag.n4 = 3;
    mainDiag.n5 = 0;
    mainDiag.n6 = 1;
    mainDiag.n7 = 2;
    mainDiag.n8 = 3;

    /*neighbors on the anti diagonal */
    Neighbors antiDiag;
    antiDiag.n1 = 3;
    antiDiag.n2 = 2;
    antiDiag.n3 = 1;
    antiDiag.n4 = 0;
    antiDiag.n5 = 0;
    antiDiag.n6 = 1;
    antiDiag.n7 = 2;
    antiDiag.n8 = 3;



    //check neighbors allong the horizontal
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols - 3; j++)
        {
            //find product of the neighbors and update maxProduct
            Horizontal.product =
            data[i + Horizontal.n5][j + Horizontal.n1] * data[i + Horizontal.n6][j + Horizontal.n2] *
            data[i + Horizontal.n7][j + Horizontal.n3] * data[i + Horizontal.n8][j + Horizontal.n4];

            maxProduct = max(maxProduct, Horizontal.product);
        }
        //std::cout << "Horizontal largest product = " << maxProduct << endl;
    }



     //check neighbors along vertical
    for (int i=0; i<rows-3; i++)
    {
        for (int j=0; j<cols; j++)
        {
            //find neighbors product and update maxProduct
            Vertical.product =
            data[i+Vertical.n5][j+Vertical.n1] * data[i+Vertical.n6][j+Vertical.n2] *
            data[i+Vertical.n7][j+Vertical.n3] * data[i+Vertical.n8][j+Vertical.n4];

            maxProduct = max(maxProduct, Vertical.product);
        }
        //std::cout << "Vertical largest product = " << maxProduct << endl;
    }


    //check neighbors along main diagonal
    for (int i=0; i<rows-3; i++)
    {
        for (int j=0; j<cols-3; j++)
        {
            //find product and update maxProduct;
            mainDiag.product =
            data[i+mainDiag.n5][j+mainDiag.n1] * data[i+mainDiag.n6][j+mainDiag.n2] *
            data[i+mainDiag.n7][j+mainDiag.n3] * data[i+mainDiag.n8][j+mainDiag.n4];

            maxProduct = max(maxProduct, mainDiag.product);
        }

    }

    //check neighbors along anti diagonal
    for (int i=0; i<rows-3; i++)
    {
        for (int j=0; j<cols-3; j++)
        {
            //find product and update maxProduct
            antiDiag.product =
            data[i+antiDiag.n5][j+antiDiag.n1] * data[i+antiDiag.n6][j+antiDiag.n2] *
            data[i+antiDiag.n7][j+antiDiag.n3] * data[i+antiDiag.n8][j+antiDiag.n4];

            maxProduct = max(maxProduct, antiDiag.product);
        }
    }

    //output results to file
    ofstream outfile;
    outfile.open("output2.txt");

    outfile <<std::scientific  << std::setprecision(8) << maxProduct;

    return 0;
}
