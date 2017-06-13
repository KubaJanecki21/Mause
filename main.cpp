
#include <afxres.h>
#include "MauseGestures.h"


LPSTR NazwaKlasy = (LPSTR)"Okno";
MSG Komunikat;
//int area=500;
/*bool left_pushed=false;
int start;

int mause_left=20;
int prawy_przycisk=30;

void testMauseMovement(int,int);
std::string target_string[] = { "Lewo", "Prawo","Dol","Gora","Lewo-Gora","Prawo-Gora","Lewo_Dol","Prawo-Dol","Brak" };
enum target_enum
{
    left=0,
    right=1,
    down=2,
    up=3,
    left_up=4,
    right_up=5,
    left_down=6,
    right_down=7,
    none=8

};


class Map{
public:
    int x_start;
    int y_start;
    int ZASIEG;
    Map(int x, int y){
        ZASIEG=100;
        x_start=x;
        y_start=y;
    }

    target_enum getTarget(int x,int y){
        if(x>x_start+ZASIEG){
            if(y>y_start+ZASIEG) return right_down;
            else if(y<y_start-ZASIEG) return right_up;
            else return right;
        } else if(x<x_start-ZASIEG){
            if(y>y_start+ZASIEG) return left_down;
            else if(y<y_start-ZASIEG) return left_up;
            else return left;
        } else if(y>y_start+ZASIEG) return down;
        else if(y<y_start-ZASIEG) return up;
        else return none;
    }

};


Map *m;*/

/*void testMauseMovement(int x,int y){
    if((x>0)&&(x<area)&&(y>0)&&(y<area))
    {
        if((left_pushed)&&(GetTickCount()-start>400)&&(m->getTarget(x,y)!=8)){
            std::cout<<target_string[m->getTarget(x,y)]<<"\n";
            m=new Map(x,y);
            start = GetTickCount();
        }
    }
}
*/

MauseGestures *mg=new MauseGestures(500);

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

    WNDCLASSEX wc;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Blad rejestracji!", "Blad",
                    MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // TWORZENIE OKNA
    HWND hwnd;

    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Oto okienko", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL );

    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno nie dziala!", "Blad", MB_ICONEXCLAMATION );
        return 1;
    }

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    // Pętla komunikatów
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(hwnd,&p);


        mg->testMauseMovement(p.x,p.y);

        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_LBUTTONDOWN:

            //std::cout<<"LPM"<<"\n";
            mg->m=new MauseGestures::Map(LOWORD(lParam),HIWORD(lParam));
            mg->left_pushed=true;
            mg->gest->push_front(20);
            mg->start = GetTickCount();
            break;

        case WM_LBUTTONUP:
            mg->left_pushed=false;
            if(mg->gest->size()!=0)mg->gest->clear();
            //system("cls");
            mg->start=0;

            break;

        case WM_RBUTTONDOWN:

            //std::cout<<"PPM"<<"\n";
            mg->m=new MauseGestures::Map(LOWORD(lParam),HIWORD(lParam));
            mg->right_pushed=true;
            mg->gest->push_front(30);
            mg->start = GetTickCount();
            break;

        case WM_RBUTTONUP:
            mg->right_pushed=false;
            if(mg->gest->size()!=0)mg->gest->clear();
            mg->start=0;
            break;

        case WM_CLOSE:
            DestroyWindow( hwnd );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}

