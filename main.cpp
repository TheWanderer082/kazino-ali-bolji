#include <SFML/Graphics.hpp>/
#include <iostream>
#include <cmath>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

using namespace sf;
using namespace std;

Text settext(int charsize ,int x, int y, int outlinethickness,Color txtcolor,Color outlinecolor, string txt)
{
    Vector2f position(x, y);
    Text funtext;
    funtext.setCharacterSize(charsize);
    funtext.setPosition(position);
    funtext.setFillColor(txtcolor);
    funtext.setOutlineColor(outlinecolor);
    funtext.setOutlineThickness(outlinethickness);

    funtext.setString(txt);
    return funtext;

}

Sprite setsprite(int x , int y ,float xscale , float yscale)
{
    Sprite funsprite;
    Vector2f spriteposition(x, y);
    funsprite.setPosition(spriteposition);
    funsprite.setScale(xscale, yscale);

    return funsprite;
}

float rotation = 0;
int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(1920, 1080), "Mrtvi UI", Style::Fullscreen);

    Font font;
    font.loadFromFile("piksel.ttf");

    Sprite shape = setsprite(1920 / 2 - 400, 1080 / 2, 0.03 * 2.2, 0.03 * 2.2);
    Texture place_holder;
    place_holder.loadFromFile("ball(1).png");
    shape.setTexture(place_holder);

    Sprite table = setsprite(1920 / 2 - 400, 1080 / 2, 1, 1);
    Texture place_holder2;
    place_holder2.loadFromFile("table-outline.png");
    table.setTexture(place_holder2);

    Sprite inner_table = setsprite(65, 45, 1, 1);
    Texture place_holder3;
    place_holder3.loadFromFile("table-inline.png");
    inner_table.setTexture(place_holder3);

    FloatRect bounds_ball = shape.getGlobalBounds();

    shape.setOrigin(bounds_ball.width / 2 + 5200, bounds_ball.height / 2 + 5200);
    //table.setOrigin(1980 / 2 - table.getGlobalBounds().width / 2, 1080 / 2 - table.getGlobalBounds().height);




    float x = 0;
    float acceleration = 0.00277 * (rand() % 36 + 1);
    int n_of_rotations = 3;

    bool deceel = false;


    FloatRect gb = table.getGlobalBounds();
    table.setOrigin(gb.width / 2 , gb.height / 2);

    table.setScale(2.2,2.2);
    inner_table.setScale(2.2, 2.2);

    float wheel_accel = 0;

    float speed = 0.02;

    bool tru = true;


    while (window.isOpen())
    {
        Text rot = settext(50, 1500, 150, 5, Color::Yellow, Color::Black, to_string(acceleration) + " - ubrzanje");
        rot.setFont(font);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
        }

        // 'entity' can be a sf::Sprite, a sf::Text, a sf::Shape or any other transformable class

        // set the absolute rotation of the entity
        if (tru){
            shape.setRotation(x);
        }

        table.setRotation(wheel_accel);

        x = x + acceleration;

        if (acceleration > 0.3 || deceel){
            acceleration = acceleration / 1.0001;


            deceel = true;
        }

        else if (tru){
            acceleration = acceleration * 1.0001;

        }

        wheel_accel = wheel_accel - speed;

        if (acceleration < 0.004){

            x = x - 0.024;
            deceel = false;
            tru = false;
            shape.setRotation(x);

        }


        // rotate the entity relatively to its current orientation
        //shape.rotate(10.f);

        // retrieve the absolute rotation of the entity





        window.clear();

        window.draw(table);
        window.draw(shape);
        //window.draw(rot);
        window.draw(inner_table);
        window.display();


    }

    return 0;
}
