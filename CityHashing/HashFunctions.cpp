//
//  HashFunctions.cpp
//  CityHashing
//
//  Created by David Thacker on 3/13/13.
//  Copyright (c) 2013 David Argyle Thacker. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class HashFunctions{
public:
    
    HashFunctions(){
        
    }
    
    int hash( const string & key, int tableSize)
    {
        int hashVal = 0;
        
        for( int i = 0; i < key.length(); i++ )
            hashVal = (37 * hashVal) + (key[ i ]);
            hashVal %= tableSize;
            hashVal = hashVal * 1111;
            hashVal %= tableSize;
        if( hashVal < 0 )
            hashVal += tableSize;
        
        addCounter(hashVal);
        
        return hashVal;
    }
    
    void addCounter( int i )
    {
        //        int c = counter[i];
        counter[i] = ++counter[i];
        //        cout << "adding " << c + 1 << " to index " << i << endl;
    }
    
    void initializeArray()
    {
        for(int i = 0; i < counterSize; i++)
            counter[i] = 0;
    }
    
    int countCollisions()
    {
        int totalCollisions = 0;
        for(int i = 0; i < counterSize; i++)
        {
            int c = counter[i];
            if(c == 0){
                collisonNone++;
            }
            else if(c > 0){
                if(c == 1 )
                {
                    collisonOne++;
                }
                else if(c == 2 )
                {
                    collisonTwo++;
                }
                else if( c == 3 )
                {
                    collisonThree++;
                }
            
                else if ( c == 4 )
                {
                    collisonFour++;
                }
                else if ( c == 5 )
                {
                    collisonFive++;
                }
                totalCollisions++;
            }
                
        }
        
        cout << "p(0) = " << collisonOne << endl;
        cout << "p(1) = " << collisonOne << endl;
        cout << "p(2) = " << collisonTwo << endl;
        cout << "p(3) = " << collisonThree << endl;
        cout << "p(4) = " << collisonFour << endl;
        cout << "p(5) = " << collisonFive << endl;
        
        return totalCollisions;
    }
    
    void printArray()
    {
        for(int i = 0; i < counterSize; i++)
        {
            int c = counter[i];
            cout << c << endl;
        }
    }
    
    float poisson(int x, float N, float n){
        
        float r = n / N;
        float t = ((r * x) * (exp(-r)));
        return (t/factorial(x));
        
    }
    
    float factorial(float n)
    {
        return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }
    
private:
    int counterSize = 750;
    int counter[750];
    int collisonNone = 0;
    int collisonOne = 0;
    int collisonTwo = 0;
    int collisonThree = 0;
    int collisonFour = 0;
    int collisonFive = 0;
    
};