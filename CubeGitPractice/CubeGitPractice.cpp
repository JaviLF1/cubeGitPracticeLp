#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Movable White Square");
    window.setFramerateLimit(60);

    // Create a white square
    sf::RectangleShape square(sf::Vector2f(50.f, 50.f));
    square.setFillColor(sf::Color::White);

    // Set initial position (center of window)
    square.setPosition({ 375.f, 275.f });

    // Vector to store placed squares
    std::vector<sf::RectangleShape> placedSquares;

    // Movement speed
    float speed = 5.f;

    // Track Enter key state to prevent multiple placements
    bool enterPressed = false;

    // Main game loop
    while (window.isOpen())
    {
        // Handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Handle movement input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            square.move({ 0.f, -speed }); // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            square.move({ 0.f, speed }); // Move down
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            square.move({ -speed, 0.f }); // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            square.move({ speed, 0.f }); // Move right
        }

        // Handle Enter key to place a square
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            //if (!enterPressed) // Only place once per key press

                // Create a copy of the current square
            sf::RectangleShape newSquare = square;
            placedSquares.push_back(newSquare);
            enterPressed = true;

            sf::Vector2f positionNow = square.getPosition();



            std::fstream cubeFile("data.txt", std::ios::app | std::ios::out);


            cubeFile << "sf::Vector2f(" << positionNow.x << "," << positionNow.x << ")" << ";"<<std::endl;

        }
        else
        {
            enterPressed = false; // Reset when key is released
        }

        // Keep square within window bounds
        sf::Vector2f position = square.getPosition();
        if (position.x < 0) square.setPosition({ 0, position.y });
        if (position.y < 0) square.setPosition({ position.x, 0 });
        if (position.x + 50 > 800) square.setPosition({ 750, position.y });
        if (position.y + 50 > 600) square.setPosition({ position.x, 550 });

        // Clear, draw, and display
        window.clear(sf::Color::Black);

        // Draw all placed squares first
        for (const auto& placedSquare : placedSquares)
        {
            window.draw(placedSquare);
        }



        // Draw the current movable square on top
        window.draw(square);

        window.display();
    }

    return 0;
}