#pragma once

struct Operation {
    int serial_num;  
    int amount;      
    int source;      
    int destination; 


    Operation(int serialNum, int amt, int src, int dest)
        : serial_num(serialNum), amount(amt), source(src), destination(dest) {}
};
