#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <vector>
#include "Polygon.h"

class TextureManager
{
public:
   enum Textures
   {
      red,
      yellow,
      blue,
      green,
      purple,
      white,
      black,
      whiteScore,
      blackScore,
      board,
      background,
      particle,
      button,
      shield,
      boardType,
      wordBoard,
      tray,
      wordTray,
      A,
      B,
      C,
      D,
      E,
      F,
      G,
      H,
      I,
      J,
      K,
      L,
      M,
      N,
      O,
      P,
      Q,
      R,
      S,
      T,
      U,
      V,
      W,
      X,
      Y,
      Z,
      blank
   };

   TextureManager()
   {
      Init();
      
      AddTexture(red, "red.png");
      AddTexture(yellow, "yellow.png");
      AddTexture(black, "black.png");
      AddTexture(blue, "blue.png");
      AddTexture(green, "green.png");
      AddTexture(white, "white.png");
      AddTexture(A, "A.png");
      AddTexture(B, "B.png");
      AddTexture(C, "C.png");
      AddTexture(D, "D.png");
      AddTexture(E, "E.png");
      AddTexture(F, "F.png");
      AddTexture(G, "G.png");
      AddTexture(H, "H.png");
      AddTexture(I, "I.png");
      AddTexture(J, "J.png");
      AddTexture(K, "K.png");
      AddTexture(L, "L.png");
      AddTexture(M, "M.png");
      AddTexture(N, "N.png");
      AddTexture(O, "O.png");
      AddTexture(P, "P.png"); 
      AddTexture(Q, "Q.png");
      AddTexture(R, "R.png");
      AddTexture(S, "S.png");
      AddTexture(T, "T.png");
      AddTexture(U, "U.png");
      AddTexture(V, "V.png");
      AddTexture(W, "W.png");
      AddTexture(X, "X.png");
      AddTexture(Y, "Y.png");
      AddTexture(Z, "Z.png");


      AddTexture(whiteScore, "white score.png");
      AddTexture(blackScore, "black score.png");
      AddTexture(blank, "Blank.png");
      AddTexture(tray, "tray.png");
      AddTexture(wordTray, "Answer Holder.png");
      AddTexture(shield, "shield.png");
      AddTexture(wordBoard, "word board.png");
      AddTexture(board, "color board.png");
      AddTexture(background, "background.png");
      AddTexture(particle, "Particle.png");
      AddTexture(button, "button.png");
   }

   // This automatically sets default origin and dimensions based on texture
   //    size. Call SetOrigin() and AddPoint() to overwrite these values.
   void AddTexture(Textures textureId, std::string fileName);

   const sf::Texture& GetTexture(Textures textureId) const;

   // This will set the origin of the texture. Rotation, movement and scaling
   //    are relative to the origin. Default dimensions are automatically set
   //    based on the size of the texture. Call AddPoint() to overwrite these.
   void SetOrigin(Textures textureId, float x, float y);

   // The first time this is called, the dimensions will be a point.
   // The second time this is called, the dimensions will be a line.
   // Three or more calls will define a polygon with an automatic line drawn
   //    from the last point added to the first point that was added.
   void AddPoint(Textures textureId, float x, float y);

   const Polygon& GetPolygon(Textures textureId);

private:
   enum State
   {
      noTexture,
      textureWithDefaultDimensions,
      originSetDefaultDimensions,
      pointsAdded
   };

   void Init();
   void SetDefaultDimensions(Textures textureId);

   static const unsigned int MAX_TEXTURES = 100;
   sf::Texture mTexture[MAX_TEXTURES];
   Polygon mPolygon[MAX_TEXTURES];
   State mState[MAX_TEXTURES];
};
