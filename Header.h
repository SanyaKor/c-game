#include "SFML/Graphics.hpp"
#include<iostream>

using namespace sf;
using namespace std;

int  menu(RenderWindow & window,int menu_type) {
    Texture menuBackground;// картинка меню
    sf::Font font;/// шрифт
    
    font.loadFromFile("/Users/shurig/Desktop/project1/project1/images/arial.ttf");// загружаем шрифт
    Text menu[7];// 7 кнопок
    menu[0].setFont(font);// загружаем шрифт в текст
    menu[0].setColor(Color::Black);// указываем цвет
    menu[0].setString("Play");// прописываем сам текст
    menu[0].setPosition(sf::Vector2f(window.getSize().x/2-30,// указываем позицию по середине экрана
                                     window.getSize().y/4));
    
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::Black);
    menu[1].setString("Settings");
    menu[1].setPosition(sf::Vector2f(window.getSize().x/2-50,
                                     window.getSize().y/2-window.getSize().y/12));
    
    menu[2].setFont(font);
    menu[2].setColor(sf::Color::Black);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(window.getSize().x/2-30,
                                     window.getSize().y/2+window.getSize().y/12));
    
    menu[3].setFont(font);
    menu[3].setColor(sf::Color::Black);
    menu[3].setString("Rabbits:");
    menu[3].setPosition(sf::Vector2f(window.getSize().x/2-45,
                                     window.getSize().y/2-window.getSize().y/12));
    
    menu[4].setFont(font);
    menu[4].setColor(sf::Color::Red);
    menu[4].setString("Rabbits Wins");
    menu[4].setPosition(sf::Vector2f(window.getSize().x/2-85,
                                     window.getSize().y/2-window.getSize().y/12));
    
    menu[5].setFont(font);
    menu[5].setColor(sf::Color::Red);
    menu[5].setString("Wolfes Wins");
    menu[5].setPosition(sf::Vector2f(window.getSize().x/2-85,
                                     window.getSize().y/2-window.getSize().y/12));
    
    menu[6].setFont(font);
    menu[6].setColor(sf::Color::Black);
    menu[6].setString("Back to menu");
    menu[6].setPosition(sf::Vector2f(window.getSize().x/2-90,
                                     window.getSize().y/2+window.getSize().y/12));
    
    menuBackground.loadFromFile("/Users/shurig/Desktop/project1/project1/images/background.png");
    Sprite menuBg(menuBackground);
    bool isMenu = 1;// открыто меню или нет
    int menuNum = 0;// номер меню
    menuBg.setPosition(0, 0);
    menuBg.setScale((float)window.getSize().x/600, (float)window.getSize().y/600);// чтобы картинка изменяла размер в зависимости от окна
    
    while (isMenu)// если меню
    {
        menuNum = 0;
        if(menu_type==0){// если типа меню 0(начальное меню_
            if(IntRect(window.getSize().x/2-30,
                       window.getSize().y/4, 60, 30).contains(Mouse::getPosition(window)))
            {// если мы навели на текст изменить его цвет и присвоить номер кнопки menunum
                menu[0].setColor(Color::Red);
                menuNum = 1;
            }
            else
                menu[0].setColor(sf::Color::Black);
            
            
            if(IntRect(window.getSize().x/2-50, window.getSize().y/2
                       -window.getSize().y/12, 120, 30).contains(Mouse::getPosition(window)))
            {
                menu[1].setColor(Color::Red);
                menuNum = 2;}
            else
                menu[1].setColor(sf::Color::Black);
            
            
            if(IntRect(window.getSize().x/2-30, window.getSize().y/2
                       +window.getSize().y/12, 60, 30).contains(Mouse::getPosition(window)))
            {
                menu[2].setColor(Color::Red);
                menuNum = 3;
            }
            else menu[2].setColor(sf::Color::Black);
            
        }
        else
        {
            if(IntRect(window.getSize().x/2-90,  window.getSize().y/2
                       +window.getSize().y/12,180, 50).contains(Mouse::getPosition(window)))
            {
                menu[6].setColor(Color::Red);
                menuNum = 4;
            }
            else menu[6].setColor(sf::Color::Black);
            
        }
        if (Mouse::isButtonPressed(Mouse::Left))// если лева я кнопка мыши нажата и тип кнопки такой то
        {
            if (menuNum == 1)
            {
                menu_type=1; // присвоить тип меню и вернуть
                return menu_type;
            }
            if (menuNum == 3)
            {
                window.close();
                isMenu = false;
            }
            if(menuNum==2){
                menu_type=2;
                return menu_type;
            }
            if(menuNum==4){
                menu_type=0;
                return menu_type;
            }
        }
        window.draw(menuBg);
        if(menu_type==0){// прорисовывать определенные кнопки в зависимости от номера меню
            window.draw(menu[0]);
            window.draw(menu[1]);
            window.draw(menu[2]);
        }
        else if(menu_type==2)
        {
            window.draw(menu[6]);
            window.draw(menu[3]);
        }
        else if(menu_type==4){
            window.draw(menu[4]);
            window.draw(menu[6]);
        }
        else if(menu_type==5){
            window.draw(menu[5]);
            window.draw(menu[6]);
        }
        window.display();
    }
    return 0;
}
