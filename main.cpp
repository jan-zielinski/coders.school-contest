#include <string> 
#include <iostream> 
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <iterator>

std::vector<std::pair<char, int>> generateKey();
std::string encode(std::string message, std::vector<std::pair<char, int>> key);
std::string decode(std::string message, std::vector<std::pair<char, int>> key);

int main() {

    std::string message = "Hello, Coders School!";
    std::vector<char> s (message.begin(), message.end());

    auto key = generateKey();
    auto cypher = encode(message, key);
    auto result = decode(cypher,key);
    //Pokazuje klucz
    for(auto x : key)
    {
        std::cout << x.first << " : " << x.second << std::endl;
    }

    //Pokazuje normalną wiadomosć
    for(auto x : s)
    {
        std::cout << x;
    }
    std::cout << std::endl;


    //Pokazuje zakodowaną wiadomość
    for(auto x : cypher)
    {
        std::cout << x;
    }
    std::cout << std::endl;


    //Pokazuje odkodowaną wiadomość
    for(auto x : result)
    {
        std::cout << x;
    }
    std::cout << std::endl;



   
    return 0;
}

std::vector<std::pair<char, int>> generateKey()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> keyInt(95);
    std::vector<char> keyChar(95); 

    std::generate(keyInt.begin(), keyInt.end(), [n=32] () mutable {return n++;});
    std::shuffle(keyInt.begin(), keyInt.end(), g);

    std::generate(keyChar.begin(), keyChar.end(), [n=32] () mutable {return n++;});
    

    std::vector< std::pair<char, int> > key;
   
    for(int i = 0; i < 95; i++)
    {
        key.push_back(std::make_pair(32 + i, keyInt[i]));
    }

    return key;
}

std::string encode(std::string message, std::vector<std::pair<char, int>> key)
{

    for(int i = 0; i < message.size(); i++)
    {
        char temp = message[i];
        auto it = std::find_if(key.begin(), key.end(), 

        [temp]( const auto key) { return key.first == temp; } );
        if(it != key.end())
            { message[i] = it->second; }
    }

    return message;
}

std::string decode(std::string message, std::vector<std::pair<char, int>> key)
{

    for(int i = 0; i < message.size(); i++)
    {
        char temp = message[i];
        auto it = std::find_if(key.begin(), key.end(), 
        
        [temp]( const auto key) { return key.second == temp; } );
        if(it != key.end())
            { message[i] = it->first; }
    }

    return message;
}