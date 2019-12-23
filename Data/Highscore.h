#include <iostream>
#include <fstream>
#include <vector>

class Highscore
{
    public:
        Highscore();
        ~Highscore();
        void ReadData();
        void WriteHighscore(std::string name, int score);
        void Split(const std::string& s, char c, std::vector<std::string>& v);
        std::vector<std::string> names;
        std::vector<int> scores;
};