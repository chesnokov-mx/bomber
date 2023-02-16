#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include "token.h"
#include "MatrixToken.h"

using namespace sf;

enum GameStatus {tutorial, game};
enum GameComplexity {easy, medium, hard};

int main()
{

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "saper");

    GameStatus status = tutorial;
    GameComplexity complexity;

    MatrixToken valgala;
    MatrixToken game = valgala.CreateMatrixGame(9, 9, 10);
    MatrixToken mediumgame = valgala.CreateMatrixGame(16, 16, 40);
    MatrixToken hardgame = valgala.CreateMatrixGame(16, 30, 99);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (status == GameStatus::game){
                if(complexity == easy and event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left and !game.BOOM){
                        game.Press((event.mouseButton.x-100)/50, ((event.mouseButton.y-300)/50)%9);
                    }
                    if(event.mouseButton.button == sf::Mouse::Right and !game.BOOM){
                        game.Flag((event.mouseButton.x-100)/50, ((event.mouseButton.y-300)/50)%9);
                    }
                }
                if(complexity == medium and event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left and !mediumgame.BOOM){
                        mediumgame.Press((event.mouseButton.x-100)/50, ((event.mouseButton.y-300)/50)%mediumgame.widY);
                    }
                    if(event.mouseButton.button == sf::Mouse::Right and !mediumgame.BOOM){
                        mediumgame.Flag((event.mouseButton.x-100)/50, ((event.mouseButton.y-300)/50)%mediumgame.widY);
                    }
                }
                if(complexity == hard and event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left and !hardgame.BOOM){
                        std::cout << "coordinate: x- " << event.mouseButton.x << "; y- " << event.mouseButton.y << std::endl;
                        std::cout << " 1- " << (event.mouseButton.x-50)/50 << "; 2- " << ((event.mouseButton.y-300)/50)%hardgame.widY << std::endl;
                        hardgame.Press( ((event.mouseButton.y-300)/50)%hardgame.widY, (event.mouseButton.x-50)/50 );
                    }
                    if(event.mouseButton.button == sf::Mouse::Right and !hardgame.BOOM){
                        hardgame.Flag(((event.mouseButton.y-300)/50)%hardgame.widY, (event.mouseButton.x-50)/50);
                    }
                }
            }
            if (status == GameStatus::game and event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    if ((430 <= event.mouseButton.x and event.mouseButton.x <= 800)
                        and (event.mouseButton.y >= 50 and event.mouseButton.y <= 120)){
                        status = tutorial;
                        game = valgala.CreateMatrixGame(9, 9, 10);
                        mediumgame = valgala.CreateMatrixGame(16, 16, 40);
                        hardgame = valgala.CreateMatrixGame(16, 30, 99);
                    }
                }
            }

            if (status == tutorial and event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if ((30 <= event.mouseButton.x and event.mouseButton.x <= 400)
                        and (event.mouseButton.y >= 880 and event.mouseButton.y <= 940)){
                        complexity = easy;
                        status = GameStatus::game;
                    }
                    if ((430 <= event.mouseButton.x and event.mouseButton.x <= 800)
                        and (event.mouseButton.y >= 880 and event.mouseButton.y <= 940)){
                        complexity = medium;
                        status = GameStatus::game;
                    }
                    if ((830 <= event.mouseButton.x and event.mouseButton.x <= 1200)
                        and (event.mouseButton.y >= 880 and event.mouseButton.y <= 940)){
                        complexity = hard;
                        status = GameStatus::game;
                    }
                }
            }

        }
        window.clear();

        // Отрисовка вступления
        if(status == tutorial)
        {
            int focusedButton = 0;
            if ((30 <= event.mouseMove.x and event.mouseMove.x <= 400)
                and (event.mouseMove.y >= 880 and event.mouseMove.y <= 940)) {
                focusedButton = 1;
            }
            if ((430 <= event.mouseMove.x and event.mouseMove.x <= 800)
                and (event.mouseMove.y >= 880 and event.mouseMove.y <= 940)) {
                focusedButton = 2;
            }
            if ((830 <= event.mouseMove.x and event.mouseMove.x <= 1200)
                and (event.mouseMove.y >= 880 and event.mouseMove.y <= 940)) {
                focusedButton = 3;
            }

            {
                Font font;
                font.loadFromFile("../Images/20354.TTF");
                Font font1;
                font1.loadFromFile("../Images/mm.ttf");
                Text text(L"Добро пожаловать в игру сапер!", font, 70);
                text.setPosition(30, 20);
                text.setFillColor(Color::Blue);
                window.draw(text);

                Text tut1(L"Цель игры — открыть все клетки игрового поля, не содержащие мины.", font1, 35);
                tut1.setPosition(30, 150);
                window.draw(tut1);

                Text tut01(L"Цель игры", font1, 35);
                tut01.setFillColor(Color::Yellow);
                tut01.setPosition(30, 150);
                window.draw(tut01);

                Text tut2(L"Определить расположение мин позволяют соседние с ними клетки, в которых", font1, 35);
                tut2.setPosition(30, 185);
                window.draw(tut2);

                Text tut3(L"находятся числа. Эти числа означают точное количество мин, содержащихся в", font1, 35);
                tut3.setPosition(30, 220);
                window.draw(tut3);

                Text tut4(L"окружающих это число восьми клетках. Несколько соседних клеток с числами", font1, 35);
                tut4.setPosition(30, 255);
                window.draw(tut4);

                Text tut5(L"зачастую указывают на одни и те же мины, что позволяет точно определить", font1, 35);
                tut5.setPosition(30, 290);
                window.draw(tut5);

                Text tut6(L"опасные клетки. Для удобства на клетки можно ставить флажки. Игра", font1, 35);
                tut6.setPosition(30, 325);
                window.draw(tut6);

                Text tut7(L"выигрывается, как только открыты все клетки, не содержащие мин. Если", font1, 35);
                tut7.setPosition(30, 360);
                window.draw(tut7);


                Text tut8(L"открывается клетка с миной — игрок проигрывает.", font1, 35);
                tut8.setPosition(30, 395);
                window.draw(tut8);

                Text tut9(L"В игре есть три уровня сложности: «новичок», представляющий собой поле 9х9", font1, 35);
                tut9.setPosition(30, 500);
                window.draw(tut9);

                Text tut10(L"и содержащий 10 мин, «любитель» — 16x16, 40 мин и «профессионал» — 16x30, 99 мин", font1,
                           35);
                tut10.setPosition(30, 535);
                window.draw(tut10);

                Text ypr(L"Управление:", font1, 50);
                ypr.setFillColor(Color::Red);
                ypr.setPosition(30, 600);
                window.draw(ypr);

                Text yprL(L"Левая клавиша мыши открывает закрытую клетку.", font1, 30);
                yprL.setPosition(50, 670);
                window.draw(yprL);

                Text yprR(L"Правая клавиша мыши помечает клетку флагом/вопросом.", font1, 30);
                yprR.setPosition(50, 700);
                window.draw(yprR);

                Text level(L"Выберите уровень сложности:", font, 40);
                level.setPosition(200, 800);
                window.draw(level);


                ConvexShape firstButton;
                firstButton.setPointCount(4);
                firstButton.setPoint(0, Vector2f(400.f, 880));
                firstButton.setPoint(1, Vector2f(30.f, 880));
                firstButton.setPoint(2, Vector2f(30.f, 940));
                firstButton.setPoint(3, Vector2f(400.f, 940));
                if (focusedButton == 1) {
                    firstButton.setFillColor(Color::Red);
                } else
                    firstButton.setFillColor(Color::Blue);
                window.draw(firstButton);

                ConvexShape secondButton;
                secondButton.setPointCount(4);
                secondButton.setPoint(0, Vector2f(800.f, 880));
                secondButton.setPoint(1, Vector2f(430.f, 880));
                secondButton.setPoint(2, Vector2f(430.f, 940));
                secondButton.setPoint(3, Vector2f(800.f, 940));

                if (focusedButton == 2) {
                    secondButton.setFillColor(Color::Red);
                } else
                    secondButton.setFillColor(Color::Blue);
                window.draw(secondButton);

                ConvexShape thirdButton;
                thirdButton.setPointCount(4);
                thirdButton.setPoint(0, Vector2f(1200.f, 880));
                thirdButton.setPoint(1, Vector2f(830.f, 880));
                thirdButton.setPoint(2, Vector2f(830.f, 940));
                thirdButton.setPoint(3, Vector2f(1200.f, 940));
                if (focusedButton == 3) {
                    thirdButton.setFillColor(Color::Red);
                } else thirdButton.setFillColor(Color::Blue);
                window.draw(thirdButton);

                Text easy(L"Новичок", font1, 30);
                easy.setPosition(150, 890);
                window.draw(easy);

                Text medium(L"Любитель", font1, 30);
                medium.setPosition(550, 890);
                window.draw(medium);

                Text hard(L"Профессионал", font1, 30);
                hard.setPosition(900, 890);
                window.draw(hard);
            }

        }
        //Конец отрисовки вступления
        if(status == GameStatus::game){
            ConvexShape secondButton;
            secondButton.setPointCount(4);
            secondButton.setPoint(0, Vector2f(800.f, 50));
            secondButton.setPoint(1, Vector2f(430.f, 50));
            secondButton.setPoint(2, Vector2f(430.f, 120));
            secondButton.setPoint(3, Vector2f(800.f, 120));
            if ((430 <= event.mouseMove.x and event.mouseMove.x <= 800)
                and (event.mouseMove.y >= 50 and event.mouseMove.y <= 120)) secondButton.setFillColor(Color::Green);
            else secondButton.setFillColor(Color::Blue);
            window.draw(secondButton);

            Font font1;
            font1.loadFromFile("../Images/mm.ttf");
            Text tut1(L"Вернуться", font1, 35);
            tut1.setPosition(520, 60);
            window.draw(tut1);
        }

        if(status == GameStatus::game){
            if(complexity==hard){
                if (hardgame.BOOM == true){
                    Texture loser;
                    loser.loadFromFile("../Images/loser.png");
                    Sprite lloser = Sprite(loser);
                    window.draw(lloser);
                }
                if (hardgame.Number_of_mines == hardgame.GetUnpressedField()){
                    Texture winner;
                    winner.loadFromFile("../Images/winner.png");
                    Sprite win = Sprite(winner);
                    window.draw(win);
                }

                for (int i = 0; i < hardgame.widX * hardgame.widY; i++){
                    hardgame.matrix[i/hardgame.widY][i%hardgame.widY].updateToken();
                    Sprite s = Sprite(hardgame.matrix[i/hardgame.widY][i%hardgame.widY].texture);
                    s.setPosition((i % 30) * 50 + 50, (i / 30) * 50 + 300);
                    window.draw(s);
                }
            }
            if(complexity==medium){
                if (mediumgame.BOOM == true){
                    Texture loser;
                    loser.loadFromFile("../Images/loser.png");
                    Sprite lloser = Sprite(loser);
                    window.draw(lloser);
                }
                if (mediumgame.Number_of_mines == mediumgame.GetUnpressedField()){
                    Texture winner;
                    winner.loadFromFile("../Images/winner.png");
                    Sprite win = Sprite(winner);
                    window.draw(win);
                }
                for (int i = 0; i < mediumgame.widX * mediumgame.widY; i++){
                    mediumgame.matrix[i/mediumgame.widX][i%mediumgame.widY].updateToken();
                    Sprite s = Sprite(mediumgame.matrix[i/mediumgame.widX][i%mediumgame.widY].texture);
                    s.setPosition(((i/mediumgame.widX)*50) + 100, (i%mediumgame.widY)*50 + 300);
                    window.draw(s);
                }
            }

            if(complexity==easy){
                if (game.BOOM == true){
                    Texture loser;
                    loser.loadFromFile("../Images/loser.png");
                    Sprite lloser = Sprite(loser);
                    window.draw(lloser);
                }
                if (game.Number_of_mines == game.GetUnpressedField()){
                    Texture winner;
                    winner.loadFromFile("../Images/winner.png");
                    Sprite win = Sprite(winner);
                    window.draw(win);
                }
                for (int i = 0; i < 81; i++){
                    game.matrix[i/9][i%9].updateToken();
                    Sprite s = Sprite(game.matrix[i/9][i%9].texture);
                    s.setPosition(((i/9)*50) + 100, (i%9)*50 + 300);
                    window.draw(s);
                }
            }
        }

        window.display();
    }
}