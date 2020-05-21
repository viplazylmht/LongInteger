#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"
#include "RWFile.h"

using namespace std;


int main()
{
    
    //RWFile rw("input.txt", "output.txt");
    //rw.Start();

    //rw.WriteFile();
    
    QInt t1("0", 16);
    QInt t2 = 17;
    QInt t3 = 0;
    
    cout << t3.exportData(HEX) << endl;
    cout << t3.exportData(BIN) << endl;
    return 0;
}