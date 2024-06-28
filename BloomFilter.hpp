#include <string>
#include <functional>
#include <vector>

class BloomFilter 
{
private:
    //add whatever you want here
    int size;
    std::vector<bool> bits;
    std::function<size_t(const std::string&)> hash1;
    std::function<size_t(const std::string&)> hash2;

public:
    BloomFilter(int size, std::function<size_t(const std::string&)> hash1, std::function<size_t(const std::string&)> hash2): size(size), bits(size, false), hash1(hash1), hash2(hash2) {};
    //size is the size of the bit array
    //hash1 and hash2 are the two hash functions
    //In our version of Bloom Filter, we use two hash functions
    //to reduce the possibility of false positives
    //(why can we use this trick?)

    ~BloomFilter(){};

    void add(const std::string& item){
        size_t h1 = hash1(item) % size;
        size_t h2 = hash2(item) % size;
        bits[h1] = true;
        bits[h2] = true;
    };
    //add an item into the filter

    bool possibly_contains(const std::string& item){
        size_t h1 = hash1(item) % size;
        size_t h2 = hash2(item) % size;
        return bits[h1] && bits[h2];
    };
    //check if the item exists...possibly!
};

//implement the two hash functions
std::function<size_t(const std::string&)> hash1 = [](const std::string& key){
    size_t value = 0;
    for (auto ch : key)
    {
        value = value * 131 + ch;
    }
    return value;
};
std::function<size_t(const std::string&)> hash2 = [](const std::string& key){
    size_t value = 0;
    for (size_t i = 0; i < key.size(); i++)
    {
        if ((i & 1) == 0)
        {
            value ^= ((value << 7) ^ key[i] ^ (value >> 3));
        }
        else
        {
            value ^= (~((value << 11) ^ key[i] ^ (value >> 5)));
        }
    }
    return value;
};