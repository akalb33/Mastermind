#include "stdafx.h"
#include "Game.h"
#include "Particle.h"
#include "ScoreManager.h"
#include "Background.h"
#include "Board.h"
#include "Util.h"
#include <assert.h>
#include <SFML/System/Time.hpp>
#include <random>
#include "Score.h"
#include "Piece.h"
#include "Button.h"
#include "Shield.h"
#include "Tray.h"
#include "BoardType.h"
#include "AnswerTray.h"
#include "BlankPiece.h"


#include <iostream>

Game::Game()
   : mScreen(0.0f, 0.0f, 1920.0f, 1080.0f, false, "Mastermind")
   , mTextureManager()
   , mSoundManager()
   , mMenu()
   , mLevelSpeed(0.0f)
   , mLives(0)
{
   Util::InitRandomizer();
   mScreen.setVerticalSyncEnabled(true);

   Character::SetTextureManager(&mTextureManager);
   Character::SetSoundManager(&mSoundManager);
   Character::SetScreen(&mScreen);
   SetMaxCharacters();

   sf::Font font;
   assert(font.loadFromFile("arial.ttf"));
   sf::Text text;
   text.setFont(font);

   ScoreManager::Load();
   sf::Text score;
   score.setString("Score");
   score.setPosition(75.0f, 40.0f);
   score.setFont(font);
   ScoreManager::AddPlayer(150.0f, 100.0f, text, 50.0f);
   ScoreManager::SelectPlayer(0);
   sf::Text highScore;
   highScore.setString("High Score");
   highScore.setPosition(3.0f, 340.0f);
   highScore.setFont(font);
   ScoreManager::SetHighScorePosition(150.0f, 400.0f, text, 50.0f);

   mMenu.SetMenuTitle("Mastermind");
   mMenu.SetText(text);
   mMenu.AddSetting("Start New Word Game");
   mMenu.AddSetting("Start New Color Game");
   mMenu.AddSetting("Players");
   mMenu.AddSettingOption("Players", "1 Player");
   mMenu.AddSettingOption("Players", "2 Player");
   mMenu.AddSetting("Toggle Fullscreen");
   mMenu.AddSetting("Exit");
   mMenu.Load();

   bool gameStarted = false;
   bool goToMenu = true;

   sf::Clock clock;
   while (mScreen.isOpen())
   {
      sf::Event event;
      while (mScreen.pollEvent(event) || goToMenu)
      {
         if (event.type == sf::Event::Closed)
            mScreen.close();
         else if (event.type == sf::Event::Resized)
            mScreen.HandleResizeEvent();
         else if (event.type == sf::Event::KeyReleased || goToMenu)
         {
            if (event.key.code == sf::Keyboard::F11)
            {
               mScreen.ToggleFullScreen();
            }
            else if (event.key.code == sf::Keyboard::Escape || goToMenu)
            {
               goToMenu = false;
               std::string selection = mMenu.ShowMenu(mScreen);
               if((selection == "Exit") || (selection == "WINDOW_CLOSED_EVENT"))
               {
                  Character::KillAll();
                  mScreen.close();
               }
               else if (selection == "Start New Word Game")
               {
                  if (mMenu.GetSelection("Players") == "1 Player")
                  {
                     BoardType::SetToChooseSolution(false);
                  }
                  else
                  {
                     BoardType::SetToChooseSolution(true);
                  }
                  gameStarted = true;
                  StartNewWordGame();
               }
               else if (selection == "Start New Color Game")
               {
                  if (mMenu.GetSelection("Players") == "1 Player")
                  {
                     BoardType::SetToChooseSolution(false);
                  }
                  else
                  {
                     BoardType::SetToChooseSolution(true);
                  }
                  gameStarted = true;
                  StartNewColorGame();
               }
               else if (selection == "Toggle Fullscreen")
               {
                  goToMenu = true;
                  mScreen.ToggleFullScreen();
               }
               else
               {
                  if (!gameStarted)
                  {
                     goToMenu = true;
                  }
               }

               clock.restart();
            }
         }
      }

      mScreen.clear();
      Character::ProcessAll(clock.restart().asSeconds());
      Character::DisplayAll();
      //ScoreManager::DrawScores(mScreen);
      //mScreen.draw(score);
      //mScreen.draw(highScore);



      mScreen.DisplayNewScreen();

   }
   mMenu.Save();
   ScoreManager::Save();
}

Game::~Game()
{

}

void Game::SetMaxCharacters()
{
   Character::SetMaxLimit<Background>(1);
   Character::SetMaxLimit<Particle>(500);
   Character::SetMaxLimit<Board>(1);
   Character::SetMaxLimit<Piece>(140);
   Character::SetMaxLimit<Button>(1);
   Character::SetMaxLimit<Score>(140);
   Character::SetMaxLimit<Shield>(1);
   Character::SetMaxLimit<Tray>(1);
   Character::SetMaxLimit<AnswerTray>(1);
   Character::SetMaxLimit<BlankPiece>(4);
}

void Game::UpdateMenuOptions()
{
}

void Game::StartNewWordGame()
{
   BoardType::SetToColor(false);
   Piece::InitScaleLimits();
   Character::KillAll();
   Background* pBackground = Character::Resurrect<Background>();
   assert(pBackground != 0);
   pBackground->mX = 960.0f;
   pBackground->mY = 540.0f;

   if (BoardType::IsPlayerChoosingSolution())
   {
      AnswerTray* pAnswerTray = Character::Resurrect<AnswerTray>();
      assert(pAnswerTray != 0);
      pAnswerTray->mX = 985.0f;
      pAnswerTray->mY = 65.0f;
   }

   Tray* pTray = Character::Resurrect<Tray>();
   assert(pTray != 0);
   pTray->mX = 400.0f;
   pTray->mY = 750.0f;

   Board* pBoard = Character::Resurrect<Board>();
   assert(pBoard != 0);
   pBoard->Init();
   pBoard->mX = 960.0f;
   pBoard->mY = 540.0f;
   pBoard->mScale = 1.0f;
   pBoard->SetTexture(TextureManager::wordBoard);
   Piece::SetBoard(pBoard);
   pBoard->Reset();

   Button* pButton = Character::Resurrect<Button>();
   assert(pButton != 0);
   pButton->mX = 960.0f;
   pButton->mY = 1030.0f;
   Board::SetButton(pButton);

   for (unsigned int i = 0; i < 26; i++)
   {
      unsigned int row = i / 8;
      unsigned int column = i % 8;
      Piece* pPiece = Character::Resurrect<Piece>();
      assert(pPiece != 0);
      pPiece->Init('A' + i, 
                   171.65f + (column * 65.608f) + Util::RandomFloat(-1.25f, 1.25f), 
                   663.146f + (row * 49.5f), 
                   Piece::dropped, 
                   3 + row, 
                   Piece::available, 
                   false);
   }

   pBoard->GenerateCombination();
}

void Game::StartNewColorGame()
{
   BoardType::SetToColor(true);
   Piece::InitScaleLimits();
   Character::KillAll();
   Background* pBackground = Character::Resurrect<Background>();
   assert(pBackground != 0);
   pBackground->mX = 960.0f;
   pBackground->mY = 540.0f;
   

   Board* pBoard = Character::Resurrect<Board>();
   assert(pBoard != 0);
   pBoard->Init();
   pBoard->mX = 960.0f;
   pBoard->mY = 540.0f;
   pBoard->SetTexture(TextureManager::board);
   pBoard->mScale = 1.8f;
   Piece::SetBoard(pBoard);
   pBoard->Reset();
   pBoard->GenerateCombination();
   /////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////
   Piece* pRed = Character::Resurrect<Piece>();
   assert(pRed != 0);
   pRed->Init('2', 400.0f, 880.0f, Piece::dropped, 3, Piece::available, false);

   Piece* pGreen = Character::Resurrect<Piece>();
   assert(pGreen != 0);
   pGreen->Init('3', 475.0f, 880.0f, Piece::dropped, 3, Piece::available, false);

   Piece* pYellow = Character::Resurrect<Piece>();
   assert(pYellow != 0);
   pYellow->Init('4', 550.0f, 880.0f, Piece::dropped, 3, Piece::available, false);

   Piece* pBlack = Character::Resurrect<Piece>();
   assert(pBlack != 0);
   pBlack->Init('6', 400.0f, 800.0f, Piece::dropped, 3, Piece::available, false);

   Piece* pWhite = Character::Resurrect<Piece>();
   assert(pWhite != 0);
   pWhite->Init('5', 475.0f, 800.0f, Piece::dropped, 3, Piece::available, false);

   Piece* pBlue = Character::Resurrect<Piece>();
   assert(pBlue != 0);
   pBlue->Init('1', 550.0f, 800.0f, Piece::dropped, 3, Piece::available, false);

   Button* pButton = Character::Resurrect<Button>();
   assert(pButton != 0);
   pButton->mX = 960.0f;
   pButton->mY = 1030.0f;
   Board::SetButton(pButton);

   Shield* pShield = Character::Resurrect<Shield>();
   pShield->mVelocityY = 0.0f;
   pBoard->SetShield(pShield);

}


