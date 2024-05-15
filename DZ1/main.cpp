#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RU");
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Table");

    sf::Color Brown(128, 64, 48);

    // Стол
    sf::RectangleShape table(sf::Vector2f(800, 400));
    table.setFillColor(sf::Color::Green);
    table.setPosition(100, 100);
    table.setOutlineThickness(40);
    table.setOutlineColor(Brown);



    //лузы
    sf::CircleShape pockets[6] = {
        sf::CircleShape(22),
        sf::CircleShape(22),
        sf::CircleShape(22),
        sf::CircleShape(22),
        sf::CircleShape(22),
        sf::CircleShape(22),
    };
    pockets[0].setPosition(75, 75);
    pockets[1].setPosition(875, 75);
    pockets[2].setPosition(480, 60);
    pockets[3].setPosition(75, 485);
    pockets[4].setPosition(480, 495);
    pockets[5].setPosition(875, 485);

    for (int i = 0; i < 6; i++) {
        pockets[i].setFillColor(sf::Color::Black);
        window.draw(pockets[i]);
    }

    // Мячики
    sf::CircleShape balls[4] = {
        sf::CircleShape(15),
        sf::CircleShape(15),
        sf::CircleShape(15),
        sf::CircleShape(15),
    };
    int x{}, y{};
    for (int i = 0; i < 4; i++) {
        x = 100 + rand() % 700;
        y = 100 + rand() % 300;
        balls[i].setPosition(x, y);
        balls[i].setFillColor(sf::Color::Yellow);
        window.draw(balls[i]);
        std::cout << i + 1 << ". " << x << " " << y << std::endl;
    }

    int var{};

    int varX{}, varY{};
    int points{};
    int currY{}, currX{};
    bool isStrike = false;
    bool isMove = false;

    while (window.isOpen())
    {
        if (isStrike == false && isMove == false) {
            std::cout << "Число очков = " << points << std::endl;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // вывод стола
        window.draw(table);

        if (isStrike == false) {
            //вывод мячей
            for (int i = 0; i < 4; i++) {
                window.draw(balls[i]);
            }
        }
        else
        {
            for (int h{}; h < 4; h++) {
                balls[h].setPosition((h * 20) + 60, 30);
            }
        }

        //вывод лузов
        for (int i = 0; i < 6; i++) 
        {
            window.draw(pockets[i]);
        }

        window.display();

        if (!isStrike) {
            if (!isMove) {
                std::cout << "Выберите шар: ";
                std::cin >> var;
                var--;

                std::cout << "Выберите вектор направления (x, y) " << std::endl;
                std::cout << "X = ";
                std::cin >> varX;
                std::cout << "Y = ";
                std::cin >> varY;
            }

            sf::Vector2f velocity(varX, varY); // скорость по x и y
            isMove = true;
            sf::Clock clock;
            float dt = 0.f;
            for (int i = 0; i < 6; i++) {
                
                for (int j = 0; j < 800; j++) {
                    dt = clock.restart().asSeconds();
                    sf::Vector2f curr(balls[var].getPosition());
                    // Обновление позиции шара
                    curr += velocity * dt * 5.f;
                    if ((pockets[i].getPosition().x - pockets[i].getRadius() <= curr.x + balls[var].getRadius()) 
                        && (curr.x - balls[var].getRadius() <= pockets[i].getPosition().x + pockets[i].getRadius()) 
                        && (pockets[i].getPosition().y - pockets[i].getRadius() <= curr.y + balls[var].getRadius()) 
                        && (curr.y - balls[var].getRadius() <= pockets[i].getPosition().y + pockets[i].getRadius()))//проверка столкновения с лузами
                    {
                        balls[var].setPosition((var * 20) + 60, 30);
                        points++;
                        isMove = false;
                        break;
                    }
                    for (int k = 0; k < 4; k++) {
                        if ((balls[k].getPosition().x - balls[k].getRadius() <= curr.x) && (curr.x <= balls[k].getPosition().x + balls[k].getRadius()) && (balls[k].getPosition().y - balls[k].getRadius() <= curr.y) && (curr.y <= balls[k].getPosition().y + balls[k].getRadius()) && var != k) //проверка столкноваения с другими шарами
                        {
                            isStrike = true;
                            isMove = false;
                            break;
                        }
                    }
                    // Проверка столкновения с границами окна
                    if (curr.x + balls[var].getRadius() > 890 || curr.x - balls[var].getRadius() < 90)
                    {
                        // Остановить шар при касании границ
                        velocity.x = 0.f;
                        isMove = false;
                        
                    }
                    if (curr.y + balls[var].getRadius() > 500 || curr.y - balls[var].getRadius() <100)
                    {
                        // Остановить шар при касании границ
                        velocity.y = 0.f;
                        isMove = false;
                    }
                    balls[var].setPosition(curr);

                    curr = sf::Vector2f(curr.x, curr.y);

                }
            }
        }
        window.clear();
    }


    return 0;
}