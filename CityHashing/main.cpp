//
//  main.cpp
//  CityHashing
//
//  Created by David Thacker on 3/13/13.
//  Copyright (c) 2013 David Argyle Thacker. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include "FileReader.cpp"

using namespace std;

int main(int argc, const char * argv[])
{

    FileReader file;
    file.textToByte();
    file.hashFromBinary();
    
    return 0;
    
}



