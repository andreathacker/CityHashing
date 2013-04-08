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
#include "HashFunctions.cpp"
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
    
    void initialize(fstream & stream){
        
        //        fstream countyFile(fileName.c_str());
        
        
        countyData emptyData;
        
        strcpy(emptyCity, (strCity).c_str());
        strcpy(emptyCounty, (strCounty).c_str());
        
        strcpy(emptyData.city, emptyCity);
        strcpy(emptyData.county, emptyCounty);
        emptyData.population = 0;
        
        cout << "Initializing..." << endl;
        int count = 0;
        while (count < 751)	{
            
            count++;
            
            stream.seekp(count * sizeof(emptyData));
            stream.write(reinterpret_cast<const char *>( &emptyData ),
                         sizeof( emptyData ) * count);
            
            cout << emptyData.city << "    " << emptyData.county << "    " << emptyData.population << endl;
        }
         cout << "Finished Initializing..." << endl;
        
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
        fstream outputHashFile ("hashRecords.dat", ios::binary | ios::app);
        
        if (!outputCountyFile) {
            cout << "data file could not be opened" << endl;
            return;
        }
        
        int count = 0;
        int hashVal = 0;
        HashFunctions hashFunctions;
        hashFunctions.initializeArray();
        readCounty(inputCountyFile, "");
        
        while (!inputCountyFile.eof())	{
            
            count++;
            
            outputCountyFile.write(reinterpret_cast<const char *>( &data ),
                                   sizeof( countyData ));
            
            hashVal = hashFunctions.hash(data.city, 750);
            
            outputHashFile.seekp(hashVal * sizeof(data));
            outputHashFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
            
            if(data.city != emptyCity){
                collisionResolution(hashVal, outputHashFile, data);
            }else{
                outputHashFile.seekp(hashVal * sizeof(data));
                outputHashFile.write(reinterpret_cast<char *> (&data), sizeof(countyData));
            }
            
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
    
    void collisionResolution(int hashVal, fstream &stream, countyData mData){
        hashVal = (hashVal + 1) % 750;
        stream.seekp(hashVal * sizeof(mData));
        stream.read(reinterpret_cast<char *> (&data), sizeof(countyData));
        
        if(data.city != emptyCity){
            collisionResolution(hashVal, stream, data);
        }else{
            stream.seekp(hashVal * sizeof(data));
            stream.write(reinterpret_cast<char *> (&data), sizeof(countyData));
        }
        
        
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
    
    void hashFromBinary ()
    {
        ifstream inputCountyFile("records.dat", ios::binary);
        
        if (!inputCountyFile)
        {
            cout << "binary file could not be opened" << endl;
            return;
        }
        
        ifstream hashFile("hashed_county.txt", ios::out);
        hashFile.close();
        
        fstream countyHashFile;
        countyHashFile.open("hashed_county.txt", ios::in | ios::out | ios::binary);
        
        if (!countyHashFile) {
            cout << "report file could not be opened" << endl;
            return;
        }
        
        initialize(countyHashFile);        
        
        string city = "";
        
        HashFunctions hashFunctions;
        hashFunctions.initializeArray();
        
        countyData data;
        countyData lastItemData = data;
        int hashVal = 0;
        int count = 0;
        
        // print out a header '\t' = tab character
        // outAcctsFile << "City: \t\tCounty: \t\tPopulation:" << endl << endl;
        
        // the first time
        inputCountyFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
        while (inputCountyFile && !inputCountyFile.eof()  )
        {
            count++;
            city = data.city;
//            hashVal = hashFunctions.hash(city, 750);
//            
//            countyHashFile.seekp(hashVal * sizeof(data));
//            countyHashFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
//            cout << data.city << "    " << data.county << "    " << data.population << endl;
//            if(data.city != emptyCity){
//                collisionResolution(hashVal, countyHashFile, data);
//            }else{
//                countyHashFile.seekp(hashVal * sizeof(data)); 
//                countyHashFile.write(reinterpret_cast<char *> (&data), sizeof(countyData));
//            }
            
            // do it again and start the loop again
            inputCountyFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
            
        }
        
        int countHash = 0;
        while(countHash < 751) {
            
            countyHashFile.seekp(countHash * sizeof(data));
            countyHashFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
            
            // cout << data.city << "    " << data.county << "    " << data.population << endl;
            countHash++;
        }
        
    }
    
    void dataToText ()
    {
        ifstream inAcctsFile("records.dat", ios::binary);
        
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
        
        
        string city = "";
        
        HashFunctions hashFunctions;
        hashFunctions.initializeArray();
        
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
            city = data.city;
            hashFunctions.hash(city, 750);
            outAcctsFile << data.city << "\t" << data.county <<
			"\t" << data.population << endl;
            
			//lastItemData = data;
            
            // do it again and start the loop again
            inAcctsFile.read(reinterpret_cast<char *> (&data), sizeof(countyData));
            
        }
        
        hashFunctions.countCollisions();
        //hashFunctions.printArray();
        //cout << "Number of collisions = " << hashFunctions.countCollisions() << endl;
        
        cout << "Number of cities listed: " << count << endl;
        //cout << "Last city in list: " << lastItemData.city << endl;
        
    }
    
private:
    
    countyData data;
    string cityBuffer;
    char countyBuffer[50];
    
    string strCity = "EMPTY_CITY_______________";
    string strCounty = "EMPTY_COUNTY_____________";
    
    char emptyCity[25];
    char emptyCounty[25];
};
