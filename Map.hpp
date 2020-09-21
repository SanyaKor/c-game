#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;
using namespace sf;
class Map{
private:
    Image image; // картинка
    Texture texture;// текутсра
    Sprite sprite;// спрайт
    string File;// файл с картинкой
public:
    int xmap;// ширина карты
    int ymap;// длина карты
    string** map; // сама карта
    Map(int x,int y,string F);// конструктор карты(ширина, высота,файл)
    
    ~Map();//  деструктор
    
    string** MapMaker();//сборщик карты
    
    void draw(RenderWindow &window);// прорисовка карты
};
