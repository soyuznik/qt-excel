#ifndef LAYASGRID_H
#define LAYASGRID_H
#include <vector>
#include <iostream>
using namespace std;
class LayAsGrid
{
private:
    int totalelements;
    int rows;
    int columns;
    vector<string> defvec;
public:
    LayAsGrid(vector<string> argvec , int _column);
    string GetGridCell(int column, int row);
};

#endif // LAYASGRID_H
