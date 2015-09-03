//
//  file.h
//  crypto
//
//  Created by Giammarco René Casanova on 31/08/15.
//  Copyright (c) 2015 Washery. All rights reserved.
//

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class crypt {
public:
    string key = "ABC";

    string encrypt(string msg)
    {
        for(unsigned x = 0; x < msg.size(); x++)
            msg[x] ^=  key[x % key.size()];
        
        return msg;
    }
    
    string decrypt(string cyphertext)
    {
        for(unsigned x = 0; x < cyphertext.size(); x++)
            cyphertext[x] ^=  key[x % key.size()];
        
        return cyphertext;
    }
};

class file:crypt {
public:
    string name;
    float size;
    bool cripted;
    
    void set_name(string str)
    {
        name = str;
    }
    
    void cryptfile()
    {
        ifstream inFile;
        ofstream outFile;
        
        inFile.open(name, ios::in | ios::binary);
        
        if (inFile.is_open())
        {
            string str((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
            inFile.close();
            
            str = encrypt(str);

            outFile.open(name+".crypt", ios::out | ios::binary);
            
            if(outFile.is_open())
            {
                outFile.write(str.c_str(), str.size());
                outFile.close();
            }
        }
    }
    
    void decryptfile()
    {
        ifstream inFile;
        ofstream outFile;
        
        inFile.open(name, ios::in | ios::binary);
        
        if (inFile.is_open())
        {
            string str((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
            inFile.close();
            
            str = decrypt(str);
            
            // remove final .crypt
            size_t pos = name.find(".crypt");
            name.erase(pos);
            
            outFile.open(name, ios::out | ios::binary);
            
            if(outFile.is_open())
            {
                outFile.write(str.c_str(), str.size());
                outFile.close();
            }
        }
    }
};