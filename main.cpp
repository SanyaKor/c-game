 #include <SFML/Graphics.hpp>
#include"Animal.hpp"
#include "Map.hpp"
#include "Header.h"

vector<Animal> Make_list(int ar,int aw, int random_number,int xm,int ym,int xx ,int yy,string* atype){// создание вектора
    vector <Animal> list;
    int n;
    for ( n = 0; n<ar; n++)// пока n   меньше зайцев создавать нового и добавлять в вектор
    {
        random_number = rand()%3;// рандомное число
        xx = rand()%(xm-2)+1;// рандомная координата по иксу
        yy = rand()%(ym-2)+1;
        Animal r = *new Animal(atype[random_number], yy*50, xx*50, 50, 50 ,0);//конструктор
        list.push_back(r);// добавление в веткор
    }
    
    for ( n = ar; n<ar+aw; n++)
    {
        xx = rand()%(xm-2)+1;
        yy = rand()%(ym-2)+1;
        random_number = rand()%2+3;
        Animal enemy = *new Animal(atype[random_number], yy*50,xx*50, 50, 50 ,random_number-2);
        list.push_back(enemy);
    }
    
    return list;
}

vector<Animal>* Del_animal(vector<Animal>* list , int &ar,int &aw,int &menu_type,RenderWindow &window)// удаление из вектора
{
    for(int k=0;k<list->size();k++)
    {
        if(list->at(k).health<=0)// если здоровье меньше или равно 0
        {
            if(list->at(k).t==0) // уменшьаем переменную с колвом определенного типа
                ar--;
            else
                aw--;
            list->erase(list->begin()+k);// удалить с таким то индексом
            if(aw==0)
            {
                menu_type=4;// если нет волков то тип меню равен 4
                list->clear();
                
            }
            else if(ar==0)
            {
                menu_type=5;
                list->clear();
            }
            else if(list->size()==0)
            {
                list->clear();
                
            }
          
        }
    }
    return list;
}

vector<Animal>* Add_animal(vector<Animal>* list,int &ar,int &aw,int xx, int yy,
                int random_number,string* atype)// добавление в вектор
{
    for(int k = 0;k<list->size();k++)
    {
        if(list->at(k).t==0 && list->at(k).child==1 && list->at(k).s==true )// елси это заяц и у него ребенок равен 1 и он сделал ход
        {
            list->at(k).child=-1; // ребенок равен -1 чтобы не клепать кучу зайцев в одном месте
            xx = list->at(k).getX();// координаты того зайца который родил
            yy = list->at(k).getY();
            random_number = rand()%3;// рандом
            Animal r = *new Animal(atype[random_number], xx, yy, 50, 50 ,0);// создание зайца
            list->push_back(r);// добавление в список
            ar++;
        }
        if(list->at(k).t==2 && list->at(k).child==1 && list->at(k).s==true){
            list->at(k).child=-1;
            xx = list->at(k).getX();
            yy = list->at(k).getY();
            random_number = rand()%2+3;
            Animal r = *new Animal(atype[random_number], xx, yy, 50, 50 ,random_number-2);
            list->push_back(r);
            aw++;
        }
    }
    return list;
}




int main()
{
    bool list_maker=true;//нужно ли создавать веткор животных
    srand(time(0));// для рандома
    string atype[5];// вектор их разных типов животных
    Font font;// шрифт
    font.loadFromFile("/Users/shurig/Desktop/project1/project1/images/arial.ttf");// загружаем шрифт
    Text text("",font , 20);// конструктор текста
    text.setColor(Color::Black);// указываем цвет
    bool info = false;// переменная информации
    bool pause = false;// переменная паузы
    float speed_s = 0.5;// скорость игры
    int rrr=0;
    int menu_type = 0;// тип меню
    int xm = 10,ym =10,k=2;// размер карты и переменная для скорости
    int xx=0, yy=0,ar=1,aw=0, random_number=0;// координаты для игроков
    // кол-во зайцев волков
    // рандомное число
    atype[0] = "/Users/shurig/Desktop/project1/project1/images/rabbit123.png";
    atype[1] = "/Users/shurig/Desktop/project1/project1/images/rabbit124.png";
    atype[2] = "/Users/shurig/Desktop/project1/project1/images/rabbit125.png";
    atype[3] = "/Users/shurig/Desktop/project1/project1/images/wolfez.png";
    atype[4] = "/Users/shurig/Desktop/project1/project1/images/wolfem.png";
    
    int AR = ar,AW =aw;// нужно чтобы хранить колво зайцев по укмолчанию // так как когда игра закончится нужно  будет создавать новый вектор из персонажей
    RenderWindow window(sf::VideoMode(50*ym, 50*xm), "Ostrov");// рисуем окошко
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, 30));// // создаем обьект прямоугольник
    if(window.getSize().x<12*50)
        text.setCharacterSize(window.getSize().x/25 + 2);// измение размера тектса в зависимости от окна
    vector<Animal> list;// вектор животных
    Map m(xm,ym,"/Users/shurig/Desktop/project1/project1/images/texture1.png");// конструктор карты
    
    string** mmaker = m.MapMaker();// скейщик карты
    
    while (window.isOpen())// пока открыто окно
    {
        sf::Event event;// событие
        
        while (window.pollEvent(event))// пока событие
        {
            if (event.type == sf::Event::Closed)// если крестик нажать окно закроется
                window.close();
            
            if(event.type == sf::Event::KeyPressed)// если нажать паузу играть стопорнется
            {
                if(event.key.code == Keyboard::P){
                    pause = !pause;
                    
                }
                if(event.key.code == Keyboard::Escape)// esc закрывает окно
                    window.close();
                if(event.key.code == Keyboard::I && !pause){
                    info = !info;
                }
                if(event.key.code == Keyboard::Up && !pause && k<4){// изменение скорости
                    speed_s = speed_s*2;
                    k++;
                }
                if(event.key.code == Keyboard::Down && !pause && k>0){
                    speed_s = speed_s/2;
                    k--;
                }
                
            }
        }
        
        if(menu_type!=1){// если тип меню не равен 1( ЕСЛИ 1 ТО ИГРА ЗАПУСКАЕТСЯ)
            menu_type = menu(window,menu_type);// запустить меню
            list_maker = true;// создатель вектора
        }
        if(menu_type==1 && !pause){// если тип меню 1 и не пауза
            if(list_maker){
                list = Make_list(AR,AW,random_number,xm,ym,xx,yy,atype);// создать вектор
                list_maker=false;// чтобы не создавать каждый цикл новый вектор
                ar = AR;
                aw = AW;
            }
            for(int i=0;i<list.size();i++)
            {
                window.clear();// чистка окна
                m.draw(window);// прорисовка карты
                list.at(i).move(mmaker,ar,speed_s,rrr);// движение персонажа
                for(int k=0;k<list.size();k++)
                {
                    list.at(i).Follow(&list.at(k));// проверка на преследование
                    list.at(i).CheckCollision(&list.at(k));// проверка на пересечение
                }
                list = *Add_animal(&list, ar, aw, xx, yy, random_number, atype);// добавление элементов в вектор
                list = *Del_animal(&list,ar,aw,menu_type,window);// удаление элементов их вектора
            }
            
            for(int i=0;i<list.size();i++)
            {
                list.at(i).draw(window);// прорисовка всех компонентов
            }
            
            if(info){
                std::ostringstream w,r,s;// потом для вывода данных в инфу
                w << aw; r << ar; s << speed_s;
                text.setString("\tINFO:\tWolfes:" + w.str()
                               + "\tRabbits:" + r.str() + "\tSpeed:" + s.str());
                window.draw(rectangle);// рисуем прямоугольник
                window.draw(text);// и текст поверх
            }
            
            window.display();// ну показать
        }
        
        
    }
    return 0;
}
