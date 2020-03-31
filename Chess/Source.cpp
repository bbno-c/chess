#include <SFML/Graphics.hpp>
#include <iostream>
#include "ChessBoard.h"

int main()
{
    int w = 560, h = 480;
    sf::RenderWindow window(sf::VideoMode(w, h), "TZ");
    window.setKeyRepeatEnabled(false);

    Pieces pieces;
    pieces.SetSprite("../res/pawn2.png");
    ChessBoard game(pieces);
    game.SetSprite("../res/board1.png");

    sf::Sprite* sprite = pieces.GetSprites();

    bool fromAdded = false;

    game.Reset();
    game.PrintBoard();

    while (window.isOpen())
    {
        sf::Vector2i mousPos = sf::Mouse::getPosition(window);
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                break;

            case sf::Event::MouseButtonPressed:
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    if (fromAdded)
                    {
                        game.ConvertFromWindow(mousPos);
                        if (game.PromptInput())
                        {
                            pieces.AIMove();
                            game.PrintBoard();
                        }
                        fromAdded = false;
                        break;
                    }
                    game.ConvertFromWindow(mousPos);
                    fromAdded = true;
                }
            }

            default:
                break;
            }
        }

        window.clear();
        for (size_t i = 0; i < 18; i++)
        {
            window.draw(sprite[i]);
        }
        window.display();
    }
    return 0;
}