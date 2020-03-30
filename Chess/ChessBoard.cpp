#include "ChessBoard.h"

ChessBoard::ChessBoard(Pieces& pieces)
{
    this->_pieces = &pieces;
}

void ChessBoard::SetSprite(std::string boardTexture)
{
    _boardTexture.loadFromFile(boardTexture);
    _boardSprite.setTexture(_boardTexture);
}

sf::Sprite ChessBoard::GetBoardSprite()
{
    return _boardSprite;
}

std::string ChessBoard::GetMove()
{
    return _move;
}

void ChessBoard::Reset()
{
    (*_pieces).Reset();
}

void ChessBoard::PrintBoard()
{
    int n = 0;
    sf::Sprite* sprite = (*_pieces).GetSprites();

    for (int y = 1; y < 9; ++y)
    {
        for (int x = 1; x < 9; ++x)
        {
            if ((*_pieces).GetWhitePieces().count(Pieces::Pos(x, y)))
            {
                sprite[n].setTextureRect(sf::IntRect(0, 0, 70, 60));
                sprite[n].setPosition(_boardCell.width * (x - 1), _boardCell.heigth * (8 - y));
                n++;
            }
            else if ((*_pieces).GetBlackPieces().count(Pieces::Pos(x, y)))
            {
                sprite[n].setTextureRect(sf::IntRect(70, 0, 70, 60));
                sprite[n].setPosition(_boardCell.width * (x - 1), _boardCell.heigth * (8 - y));
                n++;
            }
        }
    }
}

bool ChessBoard::PromptInput()
{
illegalmove:
    if ((int)(*_pieces).GetTurn() == 0)
        std::cout << "White move: ";
    else
        std::cout << "Black move: ";

    if (_move == "")
        return false;

    Pieces::Pos from(-1, -1), to(-1, -1);

    if (_move.length() == 4)
    {
        std::cout << _move << std::endl;
        from.x = _move[0] - '0';
        from.y = _move[1] - '0';
        to.x = _move[2] - '0';
        to.y = _move[3] - '0';
    }
    if (!(*_pieces).MakeMove(from, to))
    {
        _move = "";
        goto illegalmove;
    }
    _move = "";
    PrintBoard();
    return true;
}

void ChessBoard::ConvertFromWindow(sf::Vector2i mousPos)
{
    std::string tmp;
    tmp = std::to_string((int)(std::ceil(mousPos.x / _boardCell.width)) + 1);
    tmp += std::to_string((int)(8 - std::ceil(mousPos.y / _boardCell.heigth)));
    _move += tmp;
}