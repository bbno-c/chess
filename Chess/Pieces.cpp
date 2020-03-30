#include "Pieces.h"

Pieces::Pos::Pos(const Pos& p, int dx = 0, int dy = 0)
{
    *this = p;
    x += dx;
    y += dy;
}

Pieces::Pos::Pos(int _x, int _y)
{
    x = _x; y = _y;
}

bool Pieces::Pos::operator<(const Pos& p) const
{
    return (x < p.x) || (x == p.x && y < p.y);
}

bool Pieces::Pos::operator==(const Pos& p) const
{
    return x == p.x && y == p.y;
}

Pieces::Pos::Pos()
{
    x = -1;
    y = -1;
}

std::map<Pieces::Pos, Pieces::Piece>& Pieces::GetWhitePieces()
{
    return _whitePieces;
}

std::map<Pieces::Pos, Pieces::Piece>& Pieces::GetBlackPieces()
{
    return _blackPieces;
}

sf::Sprite* Pieces::GetSprites()
{
    return _piecesSprites;
}

std::map<Pieces::Pos, Pieces::Piece>& Pieces::MoverPieces()
{
    return _turn == Turn::white ? _whitePieces : _blackPieces;
}

std::map<Pieces::Pos, Pieces::Piece>& Pieces::OpponentPieces()
{
    return _turn == Turn::white ? _blackPieces : _whitePieces;
}

Pieces::Turn Pieces::GetTurn()
{
    return _turn;
}

void Pieces::SetSprite(std::string piecesTexture)
{
    sf::Image texture;
    texture.loadFromFile(piecesTexture);
    _pieceTexture.loadFromImage(texture);

    for (size_t i = 0; i < 18; i++)
    {
        _piecesSprites[i].setTexture(_pieceTexture);
    }
}

void Pieces::Reset()
{
    _turn = Turn::white;
    _whitePieces.clear();
    _blackPieces.clear();

    for (int i = 1; i < 10; ++i)
    {
        _whitePieces[Pos(1 + ((i - 1) % 3), 6 + int((i - 1) / 3))] = Piece::white_pawn;
        _blackPieces[Pos(6 + ((i - 1) % 3), 1 + int((i - 1) / 3))] = Piece::black_pawn;
    }
}

void Pieces::FlipTurn()
{
    _turn = _turn == Turn::white ? Turn::black : Turn::white;
}

bool Pieces::MakeMove(Pos from, Pos to)
{
    std::vector<Pos> allowed = PossibleMoves(from);

    if (find(allowed.begin(), allowed.end(), to) == allowed.end())
        return false;

    MoverPieces()[to] = MoverPieces()[from];
    MoverPieces().erase(from);

    FlipTurn();
    return true;
}

std::vector<Pieces::Pos> Pieces::PossibleMoves(const Pos& from)
{
    std::vector<Pos> moves;

    auto isOwn = [&](int dx, int dy) -> bool { return MoverPieces().count(Pos(from, dx, dy)); };
    auto isOpponent = [&](int dx, int dy) -> bool { return OpponentPieces().count(Pos(from, dx, dy)); };
    auto isInsideBoard = [&](int dx, int dy) -> bool { Pos p(from, dx, dy); return p.x < 9 && p.x > 0 && p.y < 9 && p.y > 0; };
    auto isFree = [&](int dx, int dy) -> bool { return !isOwn(dx, dy) && isInsideBoard(dx, dy) && !isOpponent(dx, dy); };

    auto addMove = [&](int dx, int dy) -> bool
    {
        if (isFree(dx, dy) && !isOpponent(dx, dy))
        {
            moves.push_back(Pos(from, dx, dy));
            return true;
        }
        return false;
    };

    if (!isOwn(0, 0))
        return moves;

    auto moving_piece = MoverPieces()[from];
    switch (moving_piece)
    {
    case Piece::white_pawn:
    case Piece::black_pawn:
        addMove(0, -1);
        addMove(0, 1);
        addMove(-1, 0);
        addMove(1, 0);
        break;
    }
    return moves;
}

void Pieces::AIMove()
{
    for (auto& from : MoverPieces())
    {
        if (true)
        {

        }
        int x = from.first.x;
        int y = from.first.y;
        if (MakeMove(from.first, Pos(x, y + 1)))
        {
            return;
        }
        if (MakeMove(from.first, Pos(x - 1, y)))
        {
            return;
        }
        if (MakeMove(from.first, Pos(x, y - 1)))
        {
            return;
        }
        if (MakeMove(from.first, Pos(x + 1, y)))
        {
            return;
        }
    }
}

