//
//  textToByte.cpp
//  FileReader
//
//  Created by David Thacker on 2/25/13.
//  Copyright (c) 2013 David Argyle Thacker. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <HashFunctions.cpp>
using namespace std;

class FileReader {
    
public:
    struct countyData {
        char city [25];
        char county [25];
        int population;
    };
    
    FileReader(){
        
    }
    
    void textToByte ()
    {
        string inFilename;
        
        cout << "Enter text file name ";
        cin >> inFilename;
        
        fstream inputCountyFile(inFilename.c_str());
        
        if (!inputCountyFile)
        {
            cout << "text file could not be opened" << endl;
            return;
        }
        
        ofstream outputCountyFile ("records.dat", ios::binary | ios::app);
        
        if (!outputCountyFile) {
            cout << "data file could not be opened" << endl;
            return;
        }
        
        int count = 0;
        readCounty(inputCountyFile, "");
        
// NEW CODE HERE
//        char buffer[25];
//        string stringA;
//        string stringB;
        
        
        while (!inputCountyFile.eof())	{
           
            count++;
            
            // NEW CODE HERE
//            
//            inputCountyFile >> buffer;
//            stringB = buffer;
//            
//            
            //
            
            outputCountyFile.write(reinterpret_cast<const char *>( &data ),
                                   sizeof( countyData ));
            cout << data.city << "    " << data.county << "    " << data.population << endl;
            
            readCounty(inputCountyFile, "");
        }
        
        // is pointer at the end of the file
        if (inputCountyFile.eof())
        {
            cout << "Number of cities listed = " << count << endl;
            cout << "Last city in list " << data.city << endl;
            cout << endl;
        }
        
        else
        {
            cout << "error in input file at city " << data.city << endl;
            cout << data.county << "  " << data.population << endl;
        }
        
        outputCountyFile.close();
        inputCountyFile.close();
    }
    
    // Recursive method to that reads each individual record from the fstream
    void readCounty(fstream &inStream, string prevIn){
        char buffer[25];
        string stringA = prevIn;
        string stringB;
        
        
        // Check to see if we have reached the end of the file before using buffer
        //        if(inStream.eof())
        //        {
        //            cout << endl;
        //            return;
        //        }
        
        inStream >> buffer;
        stringB = buffer;
        
        if(stringB == "County")
        {
            strcpy(data.city, cityBuffer.c_str());
            cityBuffer = "";
            strcpy(data.county, (stringA + " " + stringB).c_str());
            inStream >> data.population;
            return;            
        }
        else
        {
            if(cityBuffer.size() > 0)
            {
                // there is already one word store so place a space character
                // the next word is added
                cityBuffer += " " + stringA;
            }
            else
            {
                cityBuffer += stringA;
            }
            readCounty(inStream, stringB);
        }
        
    }
    
    void dataToText (string fileName)
    {
        
        HashFunctions hasFunctions;
        hasFunctions.initializeArray();
        
        ifstream inAcctsFile(fileName, ios::binary);
        
        if (!inAcctsFile)
        {
            cout << "binary file could not be opened" << endl;
            return;
        }
        
        
        ofstream outAcctsFile ("county_records.txt");
        
        if (!outAcctsFile) {
            cout << "report file could not be opened" << endl;
            return;
        }
        
        countyData data;
        countyData lastItemData = data;
        int count = 0;
        
        // print out a header '\t' = tab character
        outAcctsFile << "City: \t\tCounty: \t\tPopulation:" << endl << endl;
        
        // the first time
        inAcctsFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
        while (inAcctsFile && !inAcctsFile.eof()  )
        {
            count++;
            
            outAcctsFile << data.city << "\t" << data.county <<
			"\t" << data.population << endl;
            
			//lastItemData = data;
            
            // do it again and start the loop again
            inAcctsFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));

        }
        
        cout << "Number of cities listed: " << count << endl;
        cout << "Last city in list: " << lastItemData.city << endl;

    }
    
private:
    
    countyData data;
    string cityBuffer;
    char countyBuffer[50];    
};
