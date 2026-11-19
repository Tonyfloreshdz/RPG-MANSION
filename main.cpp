#include <iostream>
#include <raylib.h>

using namespace std;

//OPCIONES
enum Pantalla{
    CARGA,
    MENU,
    JUEGO,
    SALIR,
    PAUSA,
    GAMEOVER
};
// DIRECCIONES DE MOVIMIENTO
enum Direccion {
    NINGUNA, //INICIO
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};


int jugadorX=1;
int jugadorY=1;

int progreso = 0;


//PANTALLA DE CARGA
void pantallaCarga(int progreso){
    ClearBackground(BLACK);
    const char *texto = "CARGANDO...";
    int tamanio=40;
    int x = (GetScreenWidth() - MeasureText(texto, tamanio)) / 2;
    DrawText(texto, x, 150, 40, WHITE);
    //Barra de carga
    int anchoBarra = 500;
    int xBarra = (GetScreenWidth() - anchoBarra) / 2;
    DrawRectangle(xBarra, 250, anchoBarra, 30, DARKGRAY);
    DrawRectangle(xBarra, 250, progreso * 5, 30, GREEN);
}
//MENU
Pantalla pantallaMenu(){
    //color de fondo
    ClearBackground(DARKBLUE);

    //Texto Menu
    const char *texto = "MENU PRINCIPAL";
    int tamanio=40;
    int x = (GetScreenWidth() - MeasureText(texto, tamanio)) / 2;
    DrawText(texto, x, 150, 40, WHITE);

    //Botones               x    y  anch  alt
    Rectangle botonPLAY = {300, 200, 200, 50};
    Rectangle botonSALIR = {300, 300, 200, 50};
    DrawRectangleRec(botonPLAY, BLUE);
    Texture2D imgPlay = LoadTexture("assets/images/Menu/play.png");
    DrawTexturePro(imgPlay,{0, 0, (float)imgPlay.width, (float)imgPlay.height}, botonPLAY, {0,0}, 0.0f, WHITE);
    if(CheckCollisionPointRec(GetMousePosition(), botonPLAY)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return JUEGO;
        }
    }
    DrawRectangleRec(botonSALIR, RED);
    if(CheckCollisionPointRec(GetMousePosition(), botonSALIR)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return SALIR;
        }
    }
    return MENU;
}
//MAPA
void mapa(){
    ClearBackground(BLACK);
    //crea mapa
    int mapa[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,0,1,0,0,1},
        {1,0,0,0,0,0,1,0,0,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    //posicion
    
    int nuevaX = jugadorX;
    int nuevaY = jugadorY;
    //movimiento
    if(IsKeyPressed(KEY_W)){
        nuevaY--;
    }
    if(IsKeyPressed(KEY_S)){
        nuevaY++;
    }
    if(IsKeyPressed(KEY_A)){
        nuevaX--;
    }
    if(IsKeyPressed(KEY_D)){
        nuevaX++;
    }
    //coliciones
    if(mapa[nuevaY][nuevaX] != 1){
        jugadorX = nuevaX;
        jugadorY = nuevaY;
    }

    //tamano de cada casilla
    int tamanoCelda = 50;

    DrawRectangle(jugadorX * tamanoCelda, jugadorY * tamanoCelda, tamanoCelda, tamanoCelda, RED);

    //dibuja mapa
    for(int fila = 0; fila < 10; fila++){
        for(int columna = 0; columna < 10; columna++){
            int x = columna * tamanoCelda;
            int y = fila * tamanoCelda;

            if(mapa[fila][columna] == 1){
                DrawRectangle(x,y,tamanoCelda, tamanoCelda, DARKGRAY);
            }else{
                DrawRectangle(x,y,tamanoCelda, tamanoCelda, LIGHTGRAY);
            }
        }
    }
    DrawRectangle(jugadorX * tamanoCelda, jugadorY * tamanoCelda, tamanoCelda, tamanoCelda, RED);
}

int main(){
    int ancho = GetMonitorWidth(0);
    int alto = GetMonitorHeight(0);
    
    InitWindow(ancho, alto, "Pantalla de carga");
    SetTargetFPS(60);
    Pantalla PantallaActual = CARGA;
    
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }
        BeginDrawing();
        switch(PantallaActual){
            case CARGA:
                progreso++;
                if(progreso >= 100){
                    PantallaActual = MENU;
                }
                pantallaCarga(progreso);
                break;

            case MENU:
                PantallaActual = pantallaMenu();
                break;

            case JUEGO:
                mapa();
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}