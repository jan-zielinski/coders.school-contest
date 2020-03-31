#include <string> 
#include <iostream> 
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>



std::vector<std::pair<char, int>> generateKey();
std::string encrypt(std::string message, std::vector< std::pair<char, int> > key);
std::string decrypt(std::string message, std::vector< std::pair<char, int> > key);



int main() {


    std::string message = "Hello, Coders School!";
    
    auto key = generateKey();
    auto cypher = encrypt(message, key);
    auto result = decrypt(cypher,key);


    assert(message == result && "message != result");
    return 0;
}

/*
    generateKey - fucntion generate a key, which is a vector of pairs with every letter, space, slash etc. (ASCII in range [32,126])
    with shuffled ints witin the same range
*/
std::vector<std::pair<char, int>> generateKey()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> keyInt(95); 

    std::generate(keyInt.begin(), keyInt.end(), [n=32] () mutable {return n++;});   
    std::shuffle(keyInt.begin(), keyInt.end(), g);                      

    std::vector< std::pair<char, int> > key;
   
    for(int i = 0; i < 95; i++)
    {
        key.push_back(std::make_pair(32 + i, keyInt[i]));
    }

    return key;
}

/*
    encrypt - for every letter in 'message', this function is searching for it's equivalent in generated key and change it's value 
*/
std::string encrypt(std::string message, std::vector<std::pair<char, int>> key)
{

    for(int i = 0; i < message.size(); i++)
    {
        char temp = message[i];
        auto it = std::find_if(key.begin(), key.end(), 
        [temp](const auto key) { return key.first == temp; } );

        if(it != key.end())
            { message[i] = it->second; }
    }

    return message;
}

/*
    encrypt - for every letter in encypted 'message' function is searching for it's equivalent in key and change it for it's original value
*/
std::string decrypt(std::string message, std::vector<std::pair<char, int>> key)
{

    for(int i = 0; i < message.size(); i++)
    {
        char temp = message[i];
        auto it = std::find_if(key.begin(), key.end(), 
        [temp](const auto key) { return key.second == temp; } );

        if(it != key.end())
            { message[i] = it->first; }
    }

    return message;
}