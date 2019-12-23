#include "Highscore.h"

Highscore::Highscore()
{
}

Highscore::~Highscore()
{
}

void Highscore::Split(const std::string& s, char c, std::vector<std::string>& v)
{
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);
    
    while (j != std::string::npos)
    {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

void Highscore::ReadData()
{
    std::string line;
    std::vector<std::string> eintrag;

    std::ifstream highscore("Highscore.txt");

    if(highscore.is_open())
    {
        while(getline(highscore, line))
        {
            Split(line, ' ', eintrag);
            names.push_back(eintrag[0]);
            scores.push_back(stoi(eintrag[1]));

            eintrag.clear();
        }
    }

    highscore.close();
}

void Highscore::WriteHighscore(std::string name, int score)
{
    std::ofstream highscore;
    int scoreState;
    int scoreState2;
    std::string nameState;
    std::string nameState2;
    int scoresSize;
    highscore.open("Highscore.txt");

    for(int i = 0; i < scores.size(); i++)
    {
        if(scores[i] < score)
        {
            scoreState = scores[i];
            nameState = names[i];
            scores[i] = score;
            names[i] = name;

            scoresSize = scores.size();

            for(int j = i+1; j <= scoresSize; j++)
            {
                if(j != scores.size)
                {
                    scoreState2 = scores[j];
                    nameState2 = names[j];
                    scores[j] = scoreState;
                    names[j] = nameState;
                    scoreState = scoreState2;
                    nameState = nameState2;
                }
                else
                {
                    scores.push_back(scoreState);
                    names.push_back(nameState);
                }
            }

            break;
        }
    }

    for(int i = 0; i < scores.size(); i++)
    {
        highscore<<names[i]<<" "<<scores[i];
    }

    highscore.close();
}