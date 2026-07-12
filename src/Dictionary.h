#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

class Dictionary {
public:
    std::string getRandomWord(int option) const ;
    std::string getCategory(int option) const;

private:
    static const std::vector<std::string> words;
    static const std::vector<std::string> NYwords;
};

#endif