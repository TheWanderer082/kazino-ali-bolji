#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <string>
#include<iostream>
#include <stdlib.h>
#include <windows.h>

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



Sprite setsprite(int x , int y ,float xscale , float yscale)
{
    Sprite funsprite;
    Vector2f spriteposition(x, y);
    funsprite.setPosition(spriteposition);
    funsprite.setScale(xscale, yscale);

    return funsprite;
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

card poredjane_karte[52],  karte[52]; int preostale_karte = 52, txt_size = 3, sp_size = 1;


RenderWindow window(VideoMode(1920, 1080), "Mrtvi UI", Style::Fullscreen);


string rezultat = "";

Sprite sp_for_draw[100]; Text txt_for_draw[100];

int x_karte = 800, y_karte = 650, order = 51, dealer_zbir = 0, game_score = -1; bool  stand_has_been_hit = false;
int money = 100;
Text txtleave;
Text txtblackjack;
Text txtroullete;
Text txtpoker;
Text txtcasino;

Sprite karta;
Texture randtexture;
string random;

Vector2f kartapozicija(960 , 400);
float xvelocity = 3;
float yvelocity = 3.5;



Font font;


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
        poredjane_karte[i].pic = poredjane_karte[i + 1].pic;

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
Texture bg, tgreen_arrow ,tyellow_arrow;
Sprite arrow;

Text hit, stand, cash, txt_sum_of_cards, txt_sum_of_dealer, game_rez;

int sum_of_cards;
string pare;
string amount_cash;

FloatRect sbounds, hbounds;

int player_starter = 2, dealer_starter = 1, x_dealera = 800;

int bugdif = 0;

bool start;


int its_almost_dry = -9;

int do_blackjack()
{
    x_karte = 800;
    dealer_zbir = 0;
    x_dealera = 800;
    player_starter = 2;
    dealer_starter = 1;

    font.loadFromFile("piksel.ttf");


    window.setFramerateLimit(60);

    txt_size = 9;
    sp_size = 4;


    bg.loadFromFile("sto.png");
    Sprite background;
    background = setsprite(0 , 0, 1.86 , 1.86);
    background.setTexture(bg);

    Texture tgreen_arrow ,tyellow_arrow;
    Sprite arrow;
    tyellow_arrow.loadFromFile("strelica2.png");
    tgreen_arrow.loadFromFile("strelica1.png");
    arrow = setsprite(10 , 0 , 5 , 5);
    arrow.setTexture(tyellow_arrow);
    FloatRect bounds_arrow  = arrow.getGlobalBounds();

    Texture tdeck;
    tdeck.loadFromFile("deck.png"); // napravio sliku za deck
    Sprite deck;
    deck = setsprite (1600 , 400, 4.5 , 4.5); // nacrtao deck

    deck.setTexture(tdeck);

    sum_of_cards = 0;
    pare = to_string(money);
    amount_cash = pare + " $";

    cash = settext(80 , 1680 , 20 , 5 ,Color::Yellow , Color::Black , amount_cash);
    cash.setFont(font);
    hit = settext(80 , 1680 , 700 , 5 ,Color::Yellow , Color::Black , "Hit");
    hit.setFont(font);
    stand = settext(80 , 1680 , 800 , 5 ,Color::Yellow , Color::Black , "Stand");
    stand.setFont(font);
    hbounds = hit.getGlobalBounds(); // ovde sam saznao da nema potrebe za pravljenjem pravougaonika
    sbounds = stand.getGlobalBounds();

    /*Texture base;
    base.loadFromFile("row-3-column-14.png");
    int xplayer = 100 , yplayer = 550 , xdealer , ydealer;
    Sprite testkarta;
    testkarta = setsprite(xplayer , yplayer , 4.5 , 4.5);
    testkarta.setTexture(base);
    Sprite testkarta1;
    testkarta1 = setsprite(100 , 130 , 4.5 , 4.5);
    testkarta1.setTexture(base);*/
    //ovo sam drkao da vidim gde je najbolji polozaj za karte


    start = true;

    while(window.isOpen())
    {
        //cout << "works\n";
        Event esc;
      while(window.pollEvent(esc))
        {
            if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
        }

            if(start)
        {
        //ovde kao sta da se desi kad krene





            start = false;
        }


        Vector2f mis = window.mapPixelToCoords(Mouse::getPosition(window));
        if(bounds_arrow.contains(mis))arrow.setTexture(tgreen_arrow);
            else
            {
                arrow.setTexture(tyellow_arrow);
            }
        if(bounds_arrow.contains(mis) && Mouse::isButtonPressed(Mouse::Left))
        {



            return 1;
        }
        //cout << "works3\n";
        if(hbounds.contains(mis))hit.setFillColor(Color(60 , 105 , 60));
            else
            {
                hit.setFillColor(Color::Yellow);
            }
        if(sbounds.contains(mis))stand.setFillColor(Color(60 , 105 , 60));
            else
            {
                stand.setFillColor(Color::Yellow);
            }

        while(dealer_starter> 0){
            //cout << dealer_starter << " ";
            dealer_starter--;
            sp_for_draw[sp_size] = setsprite(x_dealera, y_karte - 650, 5, 5);
            dealer_zbir = dealer_zbir + karte[order].vrednost;
            sp_for_draw[sp_size++].setTexture(karte[order--].pic);
            x_dealera = x_dealera + 100;
        }
        //cout << "works4/n";

        if(sbounds.contains(mis) && Mouse::isButtonPressed(Mouse::Left))
        {
            //ovde sta se desi kad kliknes stand



            while (dealer_zbir < 17){
                sp_for_draw[sp_size] = setsprite(x_dealera, y_karte - 650, 5, 5);
                dealer_zbir = dealer_zbir + karte[order].vrednost;
                sp_for_draw[sp_size++].setTexture(karte[order--].pic);
                x_dealera = x_dealera + 100;

            }
            stand_has_been_hit = true;
            while (sbounds.contains(mis) && Mouse::isButtonPressed(Mouse::Left)){

            }
        }

        while (player_starter > 0){
            player_starter--;
            sp_for_draw[sp_size] = setsprite(x_karte, y_karte, 5, 5);
            sum_of_cards =sum_of_cards + karte[order].vrednost;
            sp_for_draw[sp_size++].setTexture(karte[order--].pic);
            x_karte = x_karte + 100;
        }

        //cout << "works1\n";


        if(hbounds.contains(mis) && Mouse::isButtonPressed(Mouse::Left))
        {
            // a ovde sta se desi kad kliknes hit

            sp_for_draw[sp_size] = setsprite(x_karte, y_karte, 5, 5);
            sum_of_cards =sum_of_cards + karte[order].vrednost;
            sp_for_draw[sp_size++].setTexture(karte[order--].pic);
            x_karte = x_karte + 100;

            while(hbounds.contains(mis) && Mouse::isButtonPressed(Mouse::Left)){

            }
        }

        txt_sum_of_cards = settext(80, 700, 800, 5, Color::Yellow, Color::Black, to_string(sum_of_cards));
        txt_sum_of_cards.setFont(font);

        txt_sum_of_dealer = settext(80, 700, 150, 5, Color::Yellow, Color::Black, to_string(dealer_zbir));
        txt_sum_of_dealer.setFont(font);
        //stand = settext(80 , 1680 , 800 , 5 ,Color::Yellow , Color::Black , "Stand");


        pare = to_string(money);
        amount_cash = pare + " $";

        cash = settext(80 , 1680 , 20 , 5 ,Color::Yellow , Color::Black , amount_cash);
        cash.setFont(font);


        sp_for_draw[1] = background;
        sp_for_draw[2] = arrow;
        sp_for_draw[3] = deck;

        txt_for_draw[3] = hit;
        txt_for_draw[4] = stand;
        txt_for_draw[5] = cash;
        txt_for_draw[6] = txt_sum_of_cards;
        txt_for_draw[7] = txt_sum_of_dealer;


        if (sum_of_cards == 21){
            // idi na pobeda

            game_score = 1;
        }
        if (sum_of_cards > 21){
            // idi na gubitnika

            game_score = 2;
        }
        if (stand_has_been_hit){
            if (dealer_zbir == 21){
                // idi na gubitnika
                game_score = 2;
            }
            if (dealer_zbir > 21){
                // idi na pobedu
                game_score = 1;
                //cout << "radi?";
            }
            else if (dealer_zbir > sum_of_cards){
                // idi na gubitnika
                game_score = 2;
            }
            else if (sum_of_cards > dealer_zbir){
                // idi na pobedu
                game_score = 1;
            }
            else if (sum_of_cards == dealer_zbir){
                // idi na nereseno
                game_score = 0;
            }
            stand_has_been_hit = false;
        }

        if (game_score == 1){
            rezultat = "VICTORY";
            money = money + 10;
            //cout << money << " ";
            //cout << "dubz\n";
        }
        else if (game_score == 2){
            rezultat = "LOST";
            money = money - 10;
            //cout << money << "\n";
           // cout << "Ls\n";
        }
        else if (game_score == 0){
            rezultat = "DRAW";

        }
        //cout << money << " ";
        game_rez = settext(100, 700, 450, 5, Color::Yellow, Color::Black, rezultat);
        game_rez.setFont(font);

        txt_for_draw[8] = game_rez;



        //cout << sum_of_cards << "\n";
        window.clear();
        //cout << "works2";
        for (int i = 1; i < sp_size; i++){
            window.draw(sp_for_draw[i]);
        }
        for (int i = 3; i < txt_size; i++){
            window.draw(txt_for_draw[i]);
        }

        window.display();

        if (rezultat != ""){
            Sleep(1500);
            return 82;
        }


        //cout << "works2\n";
        //cout << "works3";
    }


    return 0;
}

int next_action;

int blackjack()
{
    next_action = do_blackjack();

    while (next_action != 1){
        rezultat = "";
        x_karte = 800;
        game_score = -1;
        stand_has_been_hit = false;
        dealer_zbir = 0;
        sum_of_cards = 0;
        its_almost_dry = -14;
        player_starter = 2;
        dealer_starter = 1;
        x_dealera = 800;

        next_action = do_blackjack();
    }

    return 1;
}

void casino_homepage()
{
    //cout << "works";
    font.loadFromFile("piksel.ttf");

    window.setFramerateLimit(60);

    txtcasino = settext(200 , 690 , 180 , 5 ,Color::Yellow, Color::Black,"CASINO");
    txtcasino.setFont(font);
    txt_for_draw[0] = txtcasino;


    txtleave = settext(70 , 890 , 780 , 5 ,Color::Yellow, Color::Black,"Leave");
    txtleave.setFont(font);
    txt_for_draw[1] = txtleave;

    txtpoker = settext(70 , 890 , 580 , 5 ,Color::Yellow, Color::Black,"Poker");
    txtpoker.setFont(font);
    txt_for_draw[2] = txtpoker;

        txtroullete = settext(70 , 860 , 680 , 5 ,Color::Yellow, Color::Black,"Roullete");
    txtroullete.setFont(font);
    txt_for_draw[3] = txtroullete;

    txtblackjack = settext(70 , 830 , 480 , 5,Color::Yellow, Color::Black,"Blackjack");
    txtblackjack.setFont(font);
    txt_for_draw[4] = txtblackjack;

    karta = setsprite(960 , 400 , 4.5 , 4.5 );
    Texture ace_if_spades;
    ace_if_spades.loadFromFile("row-1-column-1.png");
    karta.setTexture(ace_if_spades);
    bugdif++;

    while(window.isOpen())
    {
        //cout << bugdif << " ";
        Event event;
        while (window.pollEvent(event))
        {
           if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
        }

    Vector2f mis = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    FloatRect bounds_leave = txtleave.getGlobalBounds();
    FloatRect bounds_blackjack = txtblackjack.getGlobalBounds();
    FloatRect bounds_poker = txtpoker.getGlobalBounds();
    FloatRect bounds_roullete = txtroullete.getGlobalBounds();

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (bounds_leave.contains(mis))
        {
            window.close();
        }
    }
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (bounds_blackjack.contains(mis))
        {
            window.clear();

            if (blackjack() == 1){

                casino_homepage();
            }
        }
    }
            if (bounds_leave.contains(mis))txtleave.setFillColor(Color(60,105,60));
        else
        {
            txtleave.setFillColor(Color::Yellow);
        }
             if (bounds_blackjack.contains(mis))txtblackjack.setFillColor(Color(60,105,60));
        else
        {
            txtblackjack.setFillColor(Color::Yellow);
        }
            if (bounds_roullete.contains(mis))txtroullete.setFillColor(Color(60,105,60));
        else
        {
            txtroullete.setFillColor(Color::Yellow);
        }
             if (bounds_poker.contains(mis))txtpoker.setFillColor(Color(60,105,60));
        else
        {
            txtpoker.setFillColor(Color::Yellow);
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

        window.clear(Color(60,105,60));


        txt_for_draw[1] = txtleave;
        txt_for_draw[2] = txtpoker;
        txt_for_draw[3] = txtroullete;
        txt_for_draw[4] = txtblackjack;

        for (int i = 0; i < 1; i++){
            window.draw(sp_for_draw[i]);
        }

        for (int i = 0; i <= 4; i++){
            window.draw(txt_for_draw[i]);
        }


        window.display();

    }

}





int main()
{
    srand(time(0));

    niz_poredjaj();
    shuffle();

    casino_homepage();


}



