#include "raylib.h"
#include <deque>
#include <iostream>
#include "raymath.h"


//================================================
//===Variables====================================
//set up a colors for game - before a main functions and its becomr global variables
Color green {173,204, 96, 255};
Color darkGreen {43,51, 24, 255};

int cellSize {30};
int cellCount{25};

//variable to track a time 
double lastUpdateTime {0};

//============================================
//перевірка для точного відтворення часового відрізку з останього руху змії 
bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool AreVectorsEqual(Vector2 v1, Vector2 v2) 
{
    return (v1.x == v2.x) && (v1.y == v2.y);
}

bool ElementInDeque(Vector2 element, std::deque <Vector2> deque) {
    for(unsigned int i =0; i < deque.size(); i++) {
        if(AreVectorsEqual(deque[i], element)) {
            return true;
        }
    }
    return false;
}

//===Variables====================================
class Snake
{
public:
    //аналог масиву для взаємодії з обʼєктами з обох сторін
    //працює гарно з векторами
    std::deque <Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    //moving by add and substract 
    Vector2 direction = {1,0};
    bool addSegments = false;

    //метод класу для промальовки
    void Draw(){
        for(unsigned int i = 0; i < body.size();i++){
            float x = body[i].x;
            float y = body[i].y;
            //DrawRectangle(x*cellSize, y*cellSize, cellSize, cellSize, darkGreen);
            Rectangle segment = Rectangle {x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update(){
        //add one to front
        //use part of raylibMath libs its == (body[0] + direction)
        body.push_front(Vector2Add(body[0],direction));

        if(addSegments == true){

            addSegments = false;

        }else{ //snake moves when its not eat
        //remove last one 
        body.pop_back();
        

        }
        
    }

    void Reset(){
        body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
        direction = {1,0};
    }

};


//===================================
class Food
{
public:
    //Vector2 positon = {5,6};
    Vector2 positon;
    Texture2D texture;

    //constructor to load image
    //Конструктор викликається при створенні нового об'єкта класу Food
    Food(std::deque <Vector2> snakeBody){
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        //to free our memory after using
        UnloadImage(image);
        positon = GenerateRandomPos(snakeBody);
    }

    //destracto to unload a texture when the object is destroid
    ~Food(){
        UnloadTexture(texture);
    }
    // метод класу для промальовки
    void Drav(){
        DrawTexture(texture, positon.x*cellSize, positon.y*cellSize, WHITE);
        //WHITE here is overlay
    }

    Vector2 GenerateRandomCell()
    {
        /*
        float x = GetRandomValue(0, cellCount - 1);: Генерується випадкове число для координати x. 
        GetRandomValue() - це функція з бібліотеки Raylib, яка повертає випадкове ціле число в межах, вказаних у параметрах. 
        У цьому випадку генеруються випадкові числа від 0 до cellCount - 1.
        */

        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }


    //randomizer  
    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody){
        
        Vector2 positon = GenerateRandomCell();
        while (ElementInDeque(positon, snakeBody))
        {
            positon = GenerateRandomCell();
        }
        return positon;
        //return Vector2{x, y};: Створюється об'єкт типу Vector2 з координатами x і y, і цей об'єкт повертається як результат функції.
        //return Vector2{x, y};
    }
};
//=========================================

class Game
{
    public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;

    
    void Draw(){
        food.Drav();
        snake.Draw();
    }

    void Update(){
        
        if(running)
        {
        snake.Update();
        CheckCollitionWithFood();
        CheckColitionWithEdges();
        }
        
    }

    //додаємо стан колізії - взаємодії обʼєктів 
    void CheckCollitionWithFood(){
        if(Vector2Equals(snake.body[0], food.positon))
        {
            food.positon = food.GenerateRandomPos(snake.body);
            snake.addSegments = true;
        }
    }

    void CheckColitionWithEdges(){
        //snake.body[0].x == cellCount - right side of the screen
        //snake.body[0].x == -1 - left side of the screen
        if(snake.body[0].x == cellCount || snake.body[0].x == -1 ){
            GameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1 ){
            GameOver();
        }
    }

    void GameOver(){
        snake.Reset();
        food.positon = food.GenerateRandomPos(snake.body);
        running = false;
    }
};

int main()
{



//initialize a window
InitWindow (cellCount*cellCount, cellCount*cellCount,"Retro Snake");

Game game = Game();

// start loop
SetTargetFPS(60); //the speed of exiting the game - if you don't check the int - the computer will go as fast as it can 
// so FPS depends on the speed of the computer
while (!WindowShouldClose()) // equal (true != WindowShouldClose()) - short cut
{
    BeginDrawing(); // main body our game loop

    if(eventTriggered(0.5)){
        game.Update();
    }

    //=========================================
    //control the moving  
    //snake.direction.y != 1 - handler, so as not to change the direction to the opposite
    if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1){
        game.snake.direction = {0, -1};
    }

    if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1){
        game.snake.direction = {0, 1};
    }

    if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1){
        game.snake.direction = {1, 0};
    }

    if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1){
        game.snake.direction = {-1, 0};
    }

    //======================================


    //set up a color to background - це робиться щоб при зміні кадрів все було красиво та плавно
    ClearBackground(green);

   game.Draw();

    

    EndDrawing();// ended our game body loop - in mechanics of rendering
}

CloseWindow();

}