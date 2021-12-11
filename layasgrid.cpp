#include "layasgrid.h"



LayAsGrid::LayAsGrid(vector<string> argvec , int _column){
    totalelements = (int)argvec.size();

    columns = _column;
    rows = totalelements / rows;
    //checking if we need a more row or not
    if(totalelements % 2 == 0){
        rows++; // adding one more row for the remaining elements
    }

    defvec = argvec;


}
string LayAsGrid::GetGridCell(int column , int row){
    int index = row * columns + column - columns - 1;
    return defvec[index];
}
