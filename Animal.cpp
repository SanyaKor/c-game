#include "Animal.hpp"
#include<iostream>

using namespace std;
using namespace sf;

Animal::Animal(string F, float X, float Y, float W, float H,int type){
    dx=0; dy=0; speed=0; dir =0;// скорость направление ихменение координат
    life = true;// статус
    health = 20;// здоровье
    score = 0;// очки
    t = type;// тип
    AFile = F;// файл
    w = W; h = H;// высота и ширина
    aimage.loadFromFile(F);//загружаем картинку
    atexture.loadFromImage(aimage);// загружаем спрайт
    asprite.setTexture(atexture);// считываем спрайт с текстуры
    x = X; y = Y;//присваивание координат
    asprite.setTextureRect(IntRect(0, 0, w, h));// выбираем их текстурки нужные размер
    asprite.setPosition(x,y);// указываем координаты
    child = 0;// ребенок по умолчаню 0
}

Animal::~Animal(){}

void Animal::update(string **tilemap)
{
    
    if (health <= 0){
        life = false;
        speed = 0;
        asprite.setColor(Color::Red);
    }
    
    switch (dir)// переключатель направления
    {
        case 0: dx = speed; dy = 0; break; // если направление такое то, то задается скорость
        case 1: dx = -speed; dy = 0; break;
        case 2: dx = 0; dy = speed; break;
        case 3: dx = 0; dy = -speed; break;
            
    }
    
    x += dx;// добавление изменения координат в текущие координаты
    y += dy;
    
    speed = 0;
    asprite.setPosition(x,y);//установка координат
    interactionWithMap(tilemap);// проверка по карте
    
    
    
}
void Animal::interactionWithMap(string **tilemap){
    int r=0;
    for (int i = y / 50; i < (y + 50) / 50; i++)// текущую координату делим на 50 и получаем элемент массива в карте(так как одна клетка 50 на 50 и проходимся по тайлам,проверяя текущую клетку)
        for (int j = x / 50; j<(x + 50) / 50; j++)
        {
            if (tilemap[i][j] != " "){// если элемент  не равен пробелу (пробел это земля ),   то стопорим координаты в хависимости от направления, флажок нужен чтобы указать три других любых направления ,  где есть земля)
                flag  = 1;
                if (dy>0 && dx==0){
                    y = i * 50 - 50;
                    r = rand()%3;
                    if(r==3){
                        dir = 4;
                    }
                    else dir = r;
                }
                if (dy<0 && dx==0)
                {
                    y = i * 50 + 50;
                    r = rand()%3;
                    dir = r;
                }
                if (dx>0 && dy==0)
                {
                    x = j * 50 - 50;
                    r = rand()%3+1;
                    dir = r;
                }
                if (dx < 0 && dy==0)
                {
                    x = j * 50 + 50;
                    r = rand()%3+1;
                    if(r==1){
                        dir = 0;
                    }
                    else dir = r;
                }
                
                
                
            }
        }
}
float Animal:: getX(){
    return x;
}
float Animal::getY(){
    return y;
}


void Animal::move(string **tilemap,int ar,float speed_s,int &rrr){
    int random_number=0;
    float x = getX();
    float y = getY();
    
    if(dir==0&&!step_is_over){ // если направление и шаг не закончен
        s=false;// флаг для преследования
        if(x1+50>x){// если текущая координата не равна цели то задавать скорость
            speed = speed_s;
        }
        else if (x1+50<=x){ // если равен то закончен
            step_is_over = true;
        }
    }
    if(dir==1&&!step_is_over){
        s=false;
        if(x1-50<x){
            speed = speed_s;
        }
        else if (x1-50>=x){
            step_is_over = true;
        }
    }
    if(dir==2&&!step_is_over){
        s=false;
        if(y1+50>y){
            speed = speed_s;
        }
        else if (y1+50<=y){
        
            step_is_over = true;
        }
    }
        
    if(dir==3&&!step_is_over){
        s=false;
        if(y1-50<y){
            speed = speed_s;
        }
        else if(y1-50>=y){
            step_is_over = true;
        }
    }
    
    
    
    if(step_is_over==true){// если шаг закончен
        x1 = getX(); //указываем цель
        y1 = getY();
        
        if(flag == 0){ // если флажок 0 то задать направление
            random_number = rand()%4;
            dir = random_number;
        }
        flag=0;
        if(t==0 && child!=-1)// если тип животного 0(кролик) то присвоить значение рандома
        {
            int c = rand()%5;
            child = c;
            asteps=0;
        }
        if(t==0){
            asteps++;
        }
        if (t==1 || t==2){//если тип животного не кролик то вычетать каждый шаг из здодовья 2 единицы
            health-=2;
        }
        step_is_over=false;// шаг закончен
        s = true;//// флаг для преследования
        y = round(x/50)*50;// округление координат
        x = round(x/50)*50;
        
    }
    
    
    
    
    
    update(tilemap);
    
}


void Animal::CheckCollision(Animal* anotherAnimal){// мы проверяем обьект с которым в данный момент работаем и другой обьект , переданный по ссылке
    
    if( (abs(getX()-anotherAnimal->getX())<=20)// если расстояние между обьектами меньше 20 по иксу и ио игреку
       && (abs(getY()-anotherAnimal->getY())<=20))
        
    {
        if((t==1 || t==2) && anotherAnimal->t==0)// сравниваем типы обьектов и присваиваем текущим полям определенные значения
        {
            anotherAnimal->life = false;
            anotherAnimal->health = 0;
            health+=10;
            score+=1;
        }
        else if((anotherAnimal->t==1 || anotherAnimal->t==2)&& t==0)
        {
            life = false;
            health = 0;
            anotherAnimal->health+=10;
            anotherAnimal->score+=1;
        }
        if(t==1 && anotherAnimal->t==2 && anotherAnimal->child==0){
            anotherAnimal->child = 1;
        }
        if(anotherAnimal->t==1 && t==2 && child==0){
            child = 1;
        }
    }
   
}


void Animal::Follow(Animal* anotherAnimal){
    if (  ((t==1  && anotherAnimal->t==0)
           || (t==2  && anotherAnimal->t==0))
        && (abs(getX()-anotherAnimal->getX())<=75 )// если расстояние между зайцем и волком меньше 75 по модулю (по иксу и по игреку)
        // то волк идет в сторогну зайца // так же выполняется проверка закончил волк шаг или нет  t = true;
        
        && (abs(getY()-anotherAnimal->getY())<=75)
        && s==true)
    {
        flag=1;
        if(getX()<anotherAnimal->getX())
            dir = 0;
        if(getX()>anotherAnimal->getX())
            dir = 1;
        if(getY()<anotherAnimal->getY())
            dir = 2;
        if(getY()>anotherAnimal->getY())
            dir = 3;
    }
    else if((t==1 && anotherAnimal->t==2 && anotherAnimal->child==0 && s==true)
            && (abs(getX()-anotherAnimal->getX())<=75)
            && (abs(getY()-anotherAnimal->getY())<=75))
    {
        flag=1;
        if(getX()<anotherAnimal->getX())
            dir = 0;
        if(getX()>anotherAnimal->getX())
            dir = 1;
        if(getY()<anotherAnimal->getY())
            dir = 2;
        if(getY()>anotherAnimal->getY())
            dir = 3;
    }

}

void Animal::draw(RenderWindow &window){
    window.draw(asprite);
}


