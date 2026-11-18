#include <iostream>
#include <raylib.h>

using namespace std;

//OPCIONES
enum Pantalla{
    CARGA,
    MENU,
    JUEGO,
    PAUSA,
    GAMEOVER
};
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
    if(CheckCollisionPointRec(GetMousePosition(), botonPLAY)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return JUEGO;
        }
    }
    DrawRectangleRec(botonSALIR, RED);
    if(CheckCollisionPointRec(GetMousePosition(), botonSALIR)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return JUEGO;
        }
    }
    return MENU;
}

int main(){
    int ancho = GetMonitorWidth(0);
    int alto = GetMonitorHeight(0);
    InitWindow(ancho, alto, "Pantalla de carga");
    SetTargetFPS(60);
    Pantalla PantallaActual = CARGA;
    int progreso = 0;
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
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}