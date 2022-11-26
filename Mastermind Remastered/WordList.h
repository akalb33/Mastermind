#pragma once


class WordList
{
public:
   static std::string GetWord();

private:
   static const unsigned int mSize = 60; 
   static const std::string mWords[mSize];
};
