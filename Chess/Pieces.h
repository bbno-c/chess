#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Pieces
{
public:

    struct Pos
    {
        int x, y;
        Pos(const Pos& p, int dx = 0, int dy = 0);
        Pos(int _x, int _y);
        bool operator<(const Pos& p) const;
        bool operator==(const Pos& p) const;
        Pos();
    };

private:

    sf::Texture _pieceTexture;
    sf::Sprite _piecesSprites[18];

    enum class Piece { white_pawn, black_pawn, king };
    enum class Turn { white, black } _turn;

    std::map<Pos, Piece> _whitePieces, _blackPieces;

public:
    
    std::map<Pos, Piece>& GetWhitePieces();

    std::map<Pos, Piece>& GetBlackPieces();

    sf::Sprite* GetSprites();

    std::map<Pos, Piece>& MoverPieces();

    std::map<Pos, Piece>& OpponentPieces();

    Turn GetTurn();

    void SetSprite(std::string piecesTexture);

    void Reset();

    void FlipTurn();

    bool MakeMove(Pos from, Pos to);

    std::vector<Pos> PossibleMoves(const Pos& from);

    void AIMove();
};

