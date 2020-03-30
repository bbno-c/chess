#pragma once
#include "Pieces.h"
#include <SFML/Graphics.hpp>

class ChessBoard
{
    Pieces* _pieces;

    sf::Texture _boardTexture;
    sf::Sprite _boardSprite;

    const struct BoardCell
    {
        int width = 70;
        int heigth = 60;

    } _boardCell;

    std::string _move;

public:

    ChessBoard(Pieces& pieces);

    void SetSprite(std::string boardTexture);

    sf::Sprite GetBoardSprite();

    std::string GetMove();
    
    void Reset();

    void PrintBoard();

    bool PromptInput();

    void ConvertFromWindow(sf::Vector2i mousPos);
};

