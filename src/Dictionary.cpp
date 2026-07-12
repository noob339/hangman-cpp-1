#include "Dictionary.h"

#include <cstdlib>

const std::vector<std::string> Dictionary::words = {
    "Seattle", "Spokane", "Tacoma", "Vancouver", "Bellevue",
    "Kent", "Everett", "Renton", "Yakima", "Kirkland",
    "Bellingham", "Auburn", "Redmond", "Lakewood", "Shoreline",
    "Olympia", "Bothell", "Edmonds", "Lynnwood", "Pullman",
    "Mukilteo", "Monroe", "Snoqualmie", "Leavenworth",
    "Arlington", "Brier", "Snohomish"
};

const std::vector<std::string> Dictionary::NYwords = {
    "New York", "Buffalo", "Albany", "Syracuse", 
    "Oswego", "New Rochelle", "Troy", "Rochester", 
    "Rochester", "Gilboa", "Utica", "Ithica", 
    "Yonkers", "New Paltz", "Schenectady"
};


std::string Dictionary::getRandomWord(int option) const {
    int size = option == 1 ? words.size() : NYwords.size();
    int index = std::rand() % size;

    if(option == 1){
        return words[index];
    }

    return NYwords[index];
    
}

std::string Dictionary::getCategory(int option) const {

    std::string result;
    result = option == 1 ? "Washington State cities" : "New York State Cities";
    return result;
}