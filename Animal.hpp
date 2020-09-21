#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include <sstream>
#include <iostream>
#include <unistd.h>

using namespace sf;

using namespace std;

class Animal {
private:
    float w,h,dx,dy;
    //w  , h  это высота и ширина спрайта персонажа
    //dx и dy  это изменение координат по  x  и по y(float потому что изменение может быть дробным)

    float speed, x, y,x1,y1;
    //speed  это скорость нашего персонажа
    
    //x,y  текущая координата персонажа
    
    //x1,y1 точка ,в которую персонаж должен прийти(его цель)

    int dir;  //  направление игрока

    int flag = 0; // флажок ,нужен для изменения направления

    int step = 0; //кол-во итераций за шаг

    int asteps; //кол-во шагов

    
    string AFile; // файл с картинкой персонаж

    Sprite asprite; //спрайт персонажа , вырезается из картинки

    Image aimage; // картинка

    Texture atexture; // текстура
    
public:
    bool life; //  статус персножа
    bool step_is_over = true; // проверка,дошел ли персонаж до клетки
    bool s = false;
    
    int t,score;// тип игрока и колво очков
    int health; // здоровье игока
    int child = 0; //статус беременности
    
    Animal(string F, float X, float Y, float W, float H,int type);// конструктор
    
    ~Animal();// деструктор
    
    void update(string **tilemap);// функция для обновления логики игры,и установка координат
    
    void interactionWithMap(string **tilemap);//взаимодействие игрока с картой , проверка координат и текущей позиции
    
    float getX();// получение текущей координаты по иксу
    
    float getY();// получение текущей координаты по игреку
    
    
    void move(string **tilemap,int ar,float speed_s,int &rrr);// функция движения указывает цели, задает скорссть и направление
    
    void draw(RenderWindow &window);// функция прорисовки
    
    void CheckCollision(Animal* anotherAnimal);// функция проверки пересечений(взаимодействие персонажей и врагов)
    
    void Follow(Animal* anotherAnimal);// функция преследования (для врагов)
};
