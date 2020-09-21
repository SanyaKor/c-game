#include "Map.hpp"

Map::Map(int x,int y,string F){// обычный конструктор ,получаем на вход размеры карты, и файл с текстурой
    xmap = x;
    ymap = y;
    File = F;
    image.loadFromFile(F);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    map = new string*[xmap];// создание обычного двумерного массив тип  string(строка)
    
    for ( int i = 0; i < xmap; i++)
        
    {
        map[i] = new string[ymap];
    }
}

Map::~Map(){
};//деструктор очищает массив

string** Map::MapMaker(){
    for ( int i = 0; i < xmap; i++) // создается массив из пробелов(земля)
    {
        for ( int j = 0; j < ymap; j++)
        {
            map[i][j] = " ";
            
        }
    }
    
    for ( int i = 1; i < xmap-1; i++)// расставляются по прмяоугольнику нужные тайлы
    {
        map[i][0] = "0";
        map[i][ymap-1] = "1";
    }
    for ( int i = 1; i < ymap-1; i++)
    {
        map[0][i] = "2";
        map[xmap-1][i] = "3";
    }
    map[0][0] = "5";// ставим углы
    map[xmap-1][ymap-1] = "6";
    map[0][ymap-1] = "8";
    map[xmap-1][0] = "7";
    // map[4][5] = "9";
    
    
    for ( int i = 0; i < xmap; i++)
    {
        for ( int j = 0; j < ymap; j++)
        {
            cout << map[i][j];
            
        }
        cout << endl;
    }
    
    return map;
}

void Map::draw(RenderWindow &window){
    for (int i = 0; i < xmap; i++){
        for (int j = 0; j < ymap; j++)
        {
            // в зависимости от элемента вырезаем спрайт из текстуры
            //if (TileMap[i][j] == 'f')  s_map.setTextureRect(IntRect(0, 0, 50, 50));
            if (map[i][j] == ' ')  sprite.setTextureRect(IntRect(450, 0, 50, 50));
            if (map[i][j] == '0')  sprite.setTextureRect(IntRect(350, 0, 50, 50));
            if (map[i][j] == '1')  sprite.setTextureRect(IntRect(400, 0, 50, 50));
            if (map[i][j] == '2')  sprite.setTextureRect(IntRect(250, 0, 50, 50));
            if (map[i][j] == '3')  sprite.setTextureRect(IntRect(100, 0, 50, 50));
            if (map[i][j] == '5')  sprite.setTextureRect(IntRect(200, 0, 50, 50));
            if (map[i][j] == '6')  sprite.setTextureRect(IntRect(150, 0, 50, 50));
            if (map[i][j] == '7')  sprite.setTextureRect(IntRect(50,  0, 50, 50));
            if (map[i][j] == '8')  sprite.setTextureRect(IntRect(300, 0, 50, 50));
            if (map[i][j] == '9')  sprite.setTextureRect(IntRect(500, 0, 50, 50));
            sprite.setPosition(j * 50, i * 50);// ставим позицию
            
            window.draw(sprite);// рисуем
        }
    }
    
}
