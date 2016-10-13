//
//  TextGenerator.h
//  safari
//
//  Created by Srikanth Talapadi on 05/08/16.
//
//

#include "cocos2d.h"

#ifndef TextGenerator_h
#define TextGenerator_h
#include "cocos2d.h"

class TextGenerator {
public:
    enum class POS
    {
        NOUN = 1,
        PRONOUN = 2,
        ADJECTIVE = 3,
        VERB = 4,
        ADVERB = 5,
        PREPOSITION = 6,
        CONJUNCTION = 7,
        INTERJECTION = 8,
        ARTICLE = 9
    };
    
    static TextGenerator* getInstance();
    
    std::vector<std::vector<std::string>> generateMatrix(std::string word, int numRows, int numCols);
    std::string generateAWord();
    int getNumGraphemesInString(std::string word);
    std::vector<std::string> getGraphemes(std::string word);
    std::string generateASentence();
    std::vector<std::string> getAllChars();
    std::vector<std::string> getValidCombinations(std::string chars, int maxLength);
    std::map<std::string, std::string> getSynonyms(int maxNum);
    std::map<std::string, std::string> getAntonyms(int maxNum);
    std::map<std::string, std::string> getHomonyms(int maxNum);
    std::map<std::string, std::map<std::string, std::string>> getInitialSyllableWords(int maxNum, int maxChoices);
    std::vector<std::string> getWords(TextGenerator::POS partOfSpeech, int maxLength, int level);
    std::vector<std::string> getOrderedConcepts(int level);
    std::vector<std::vector<std::pair<std::string, TextGenerator::POS>>> getSentenceWithPOS(TextGenerator::POS partOfSpeech, int maxLength, int level);
    
protected:
    std::map<int, int> getRandomLocations(int numLoc, int totalNum);

};

#endif /* TextGenerator_h */
