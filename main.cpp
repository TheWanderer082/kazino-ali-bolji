#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <string>
#include<iostream>
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
RectangleShape setrect(int x , int y , int xposition , int yposition  ,Color rectcolor )
{
    RectangleShape rect;
    Vector2f rectsize(x, y);
    Vector2f rectpos(xposition, yposition);
    rect.setSize(rectsize);
    rect.setOrigin(x/2, y/2);
    rect.setPosition(rectpos);
    rect.setFillColor(rectcolor);

    return rect;

}



Sprite setsprite(double x_scale, double y_scale, int x, int y)
{
    Sprite sp;
    sp.setScale(x_scale, y_scale);
    sp.setPosition(Vector2f(x, y));

    return sp;
}

void draw(Sprite sp[], Text txt[], RectangleShape resh[], int sp_size, int txt_size, int resh_size, RenderWindow window)
{
    for (int i = 0; i < sp_size; i++){
        window.draw(sp[i]);
    }
    for (int i = 0; i < txt_size; i++){
        window.draw(txt[i]);
    }
    for (int i = 0; i < resh_size; i++){
        window.draw(resh[i]);
    }
}

string karta_random()
{
    string row = "row-";
    string column = "-column-";
    int brow = rand() % 4 + 1;
    int bcolumn = rand() % 13 + 1;
    string sbrow = to_string(brow);
    string sbcolumn = to_string(bcolumn);
    string slika = row + sbrow + column + sbcolumn + ".png";


    return slika ;

}

struct card{
    int vrednost;
    char znak;
    string broj;
    Texture pic;
};

card poredjane_karte[52],  karte[52]; int preostale_karte = 52;

void niz_poredjaj()
{
    for (int i = 1; i <= 52; i++){
        poredjane_karte[i - 1].vrednost = i % 13;

        if (i % 13 == 1){
            poredjane_karte[i - 1].broj = 'A';
        }
        else if (i % 13 == 11){
            poredjane_karte[i - 1].broj = 'J';
        }
        else if (i % 13 == 12){
            poredjane_karte[i - 1].broj = 'Q';
        }
        else if (i % 13 == 0){
            poredjane_karte[i - 1].broj = 'K';
        }
        else if (i % 13 == 10){
            poredjane_karte[i - 1].broj = "10";
        }

        else {
            poredjane_karte[i - 1].broj = i % 13 + '0';
        }
        int pomoc = i - 1;

        if (pomoc / 13 == 0){
            poredjane_karte[pomoc].znak = 6;
        }
        else if (pomoc / 13 == 1){
            poredjane_karte[pomoc].znak = 5;
        }
        else if (pomoc / 13 == 2){
            poredjane_karte[pomoc].znak = 3;
        }
        else {
            poredjane_karte[pomoc].znak = 4;
        }

        if (poredjane_karte[i - 1].vrednost == 0){
            poredjane_karte[i - 1].vrednost = 13;
        }
        if (poredjane_karte[i - 1].vrednost > 10){
            poredjane_karte[i - 1].vrednost = 10;
        }
        if (poredjane_karte[i - 1].vrednost == 1){
            poredjane_karte[i - 1].vrednost = 11;
        }
        //cout << poredjane_karte[i - 1] << " ";
         int row = i / 13;
        int column = i % 13;

        if (i % 13 != 0){
            row++;
        }
        else {
            column = 13;
        }
        string name_of_pic_file = "row-" + to_string(row) + "-column-" + to_string(column) + ".png";

        poredjane_karte[i - 1].pic.loadFromFile(name_of_pic_file);


    }

    /*
    Texture load_pic_from_file;
    load_pic_from_file.loadFromFile()

    randtexture.loadFromFile("row-1-column-1.png");
    karta.setTexture(randtexture); */
    //cout << "\n";
}

void del(int index)
{
    for (int i = index; i < preostale_karte - 1; i++){
        //cout << poredjane_karte[i].broj << poredjane_karte[i].znak << "\n";
        poredjane_karte[i].broj = poredjane_karte[i + 1].broj;
        poredjane_karte[i].vrednost = poredjane_karte[i + 1].vrednost;
        poredjane_karte[i].znak = poredjane_karte[i + 1].znak;

    }
    //cout << "radi\n";
    preostale_karte--;


    //cout << "\n";
}

void shuffle()
{
    niz_poredjaj();
    preostale_karte = 52;
    for (int i = 0; i < 52; i++){
        //cout << "rado";
        int index = rand() % preostale_karte;

        karte[i].vrednost = poredjane_karte[index].vrednost;
        karte[i].znak = poredjane_karte[index].znak;
        karte[i].broj = poredjane_karte[index].broj;
        karte[i].pic = poredjane_karte[index].pic;

        del(index);
        //cout << karte[i] << " ";
    }
   // cout << "\n";
 //   cout << "radi";

}

int main()
{
    srand(time(0));
    niz_poredjaj();
    shuffle();

    Sprite sp_for_draw[100]; Text txt_for_draw[100]; RectangleShape resh_for_draw[100];
    int sp_size = 0, txt_size = 0, resh_size = 0;

    RenderWindow window(VideoMode(1920, 1080), "Mrtvi UI", Style::Fullscreen);
    window.setFramerateLimit(60);

    RectangleShape leave;
    RectangleShape play;

    leave = setrect(160 , 60 , 960 , 725, Color(0, 100 ,0));
    resh_for_draw[resh_size++] = leave;

    play = setrect(140 , 60 , 950 , 625 , Color(0, 100 ,0));
    resh_for_draw[resh_size++] = play;


    Text txtleave;
    Text txtplay;
    Text txtblackjack;
    Font font;
    font.loadFromFile("piksel.ttf");

    txtblackjack = settext(200 , 550 , 280 , 5 ,Color::Yellow, Color::Black,"BLACKJACK");
    txtblackjack.setFont(font);
    txt_for_draw[0] = txtblackjack;


    txtleave = settext(70 , 890 , 680 , 5 ,Color::Yellow, Color::Black,"Leave");
    txtleave.setFont(font);
    txt_for_draw[1] = txtleave;


    txtplay = settext(70 , 890 , 580 , 5,Color::Yellow, Color::Black,"Play");
    txtplay.setFont(font);
    txt_for_draw[2] = txtplay;

    txt_size = 3;
    Sprite karta;
    Texture randtexture;
    string random;

    karta = setsprite(5, 5, 960, 400);
    karta.setTexture(poredjane_karte[0].pic);

    Vector2f kartapozicija(960 , 400);

    float xvelocity = 3;
    float yvelocity = 3.5;

    while(window.isOpen())
    {
        UI:
        Event event;
        while (window.pollEvent(event))
        {
           if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
        }

    Vector2f mis = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    FloatRect bounds_leave = leave.getGlobalBounds();
    FloatRect bounds_play = play.getGlobalBounds();

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (bounds_leave.contains(mis))
        {
            window.close();
        }
    }
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (bounds_play.contains(mis))
        {
            goto igraj;
        }
    }
            if (bounds_leave.contains(mis))txtleave.setFillColor(Color(0,100,0));
        else
        {
            txtleave.setFillColor(Color::Yellow);
        }
             if (bounds_play.contains(mis))txtplay.setFillColor(Color(0,100,0));
        else
        {
            txtplay.setFillColor(Color::Yellow);
        }
        if (kartapozicija.x < -80 || kartapozicija.x > 1684)
        {
            xvelocity *= -1;
            random = karta_random();
            randtexture.loadFromFile(random);
            karta.setTexture(randtexture);

        }

        if (kartapozicija.y <-10 || kartapozicija.y > 786)
        {
            yvelocity *= -1;
            random = karta_random();
            randtexture.loadFromFile(random);
            karta.setTexture(randtexture);

        }
        kartapozicija.x += xvelocity;
        kartapozicija.y += yvelocity;
        karta.setPosition(kartapozicija);
        sp_for_draw[0] = karta;
        sp_size = 1;
        window.clear(Color(0,100,0));


        txt_for_draw[1] = txtleave;
        txt_for_draw[2] = txtplay;

        for (int i = 0; i < sp_size; i++){
            window.draw(sp_for_draw[i]);
        }

        for (int i = 0; i < txt_size; i++){
            window.draw(txt_for_draw[i]);
        }


        window.display();
    }

    igraj:
        Texture bg;
        bg.loadFromFile("sto.png");
        Sprite background = setsprite(1.88, 1.88, 0, 0);

        background.setTexture(bg);

    while(window.isOpen())
    {
        Event esc;
      while(window.pollEvent(esc))
        {
            if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
        }
        window.clear();
        window.draw(background);
        window.display();

    }

}
