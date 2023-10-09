#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_ttf.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "sql/structures.h"
#include "sql/database.h"

const int WIDTH = 1000, HEIGHT = 700;
char stmp[100];
int regStat[9], daneshjoStat[9], adminStat[9];
char nam[50], khan[50], user_id[50], nat_id[50], gen[50], birth[50], pass[50];
char lastpass[50], newpass[50], newpass2[50], money[50];
char selfname[50], selfadd[50], self_id[50], selfcap[50], selflunch[50], selfdinner[50];
char foodname[50], food_id[50], foodcost[50];
char cnt[50], date[50];
user *logedIn;
char output[][20] = {"not-found", "success", "permission-denied"};
int ansans = 0;

const long long INF = 1e9;

typedef struct {
    int year, month, day;
    int hr;
} time_type;

time_type time = {2023, 1, 26, 556};

typedef struct {
    int x, y;
} mouse_type;

int comp(int year, int month, int day) {
    int res = (year - 1) * 366;
    if (month > 6) {
        res += 6 * 31;
        res += (month - 7) * 30;
    }
    else
        res += (month - 1) * 31;

    res += day;

    return res;
}

int comper(int hr) {
    int res = (hr / 100) * 60;
    res += hr % 100;
    return res;
}

void updateTime() {
    FILE *f = fopen("time.txt", "r");
    fscanf(f, "%d-%d-%d %d", &time.year, &time.month, &time.day, &time.hr);
    printf("%d-%d-%d %d\n", time.year, time.month, time.day, time.hr);
    fclose(f);
}

bool mouse_in_grid(mouse_type *mouse, int x1, int y1, int x2, int y2) {
    return x1 <= mouse->x && mouse->x <= x2 && y1 <= mouse->y && mouse->y <= y2;
}

int strsz(char *s) {
    int ind = 0;
    while (s[ind] != '|')
        ind++;
    
    return ind;
}

bool login_menu_event(SDL_Window *window, mouse_type *mouse, SDL_Renderer *renderer, char *userName, char *password, int *stat) {
    bool Is_done = 0;
    SDL_Event event;
    if (*stat == 0) {
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            if (mouse_in_grid(mouse, 210, 240, 640, 300))
                                (*stat) = 1;
                            else if (mouse_in_grid(mouse, 210, 320, 640, 385))
                                (*stat) = 2;
                            else if (mouse_in_grid(mouse, 210, 430, 650, 470))
                                (*stat) = 0;
                            else if (mouse_in_grid(mouse, 210, 470, 650, 505))
                               (*stat) = 10;
                            else if (mouse_in_grid(mouse, 210, 430, 650, 470)) {
                                (*stat) = 11;
                            }
                            else 
                                (*stat) = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    else if ((*stat) == 1) {
        SDL_StartTextInput();
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            if (mouse_in_grid(mouse, 210, 240, 640, 300))
                                (*stat) = 1;
                            else if (mouse_in_grid(mouse, 210, 320, 640, 385))
                                (*stat) = 2;
                            else if (mouse_in_grid(mouse, 210, 430, 650, 470))
                                (*stat) = 0;
                            else if (mouse_in_grid(mouse, 210, 470, 650, 505)) 
                                (*stat) = 10;
                            else if (mouse_in_grid(mouse, 210, 430, 650, 470)) {
                                (*stat) = 11;
                            }
                            else 
                                (*stat) = 0;
                            break;
                        }
                    }
                }
                case SDL_TEXTINPUT: {
                    int sz = strsz(userName);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        userName[sz + i] = event.text.text[i];
                    userName[sz + sz1] = '|'; 
                    break;
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            int sz = strsz(userName);
                            if (sz) {
                                userName[sz - 1] = '|';
                                userName[sz] = ' ';
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    else if ((*stat) == 2) {
        SDL_StartTextInput();
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            if (mouse_in_grid(mouse, 210, 240, 640, 300))
                                (*stat) = 1;
                            else if (mouse_in_grid(mouse, 210, 320, 640, 385))
                                (*stat) = 2;
                            else if (mouse_in_grid(mouse, 210, 430, 650, 470)) {
                                (*stat) = 11;
                            }
                            else if (mouse_in_grid(mouse, 210, 470, 650, 505)) {
                                (*stat) = 10;
                            }
                            else 
                                (*stat) = 0;
                            break;
                        }
                    }
                }
                case SDL_TEXTINPUT: {
                    int sz = strsz(password);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        password[sz + i] = event.text.text[i];
                    password[sz + sz1] = '|'; 
                    break;
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            int sz = strsz(password);
                            if (sz) {
                                password[sz - 1] = '|';
                                password[sz] = ' ';
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
        SDL_StopTextInput();
    }
    // printf("username = %s\npassword = %s\n", userName, password);
    return Is_done;
}

void ShowImage(SDL_Surface *surface, SDL_Renderer *renderer, SDL_Rect *startRect) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, startRect);
    SDL_DestroyTexture(texture);
}

void Render_login_menu(SDL_Renderer *renderer, mouse_type *mouse, char *userName, char *password, int *stat) {
    SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
    SDL_Surface *image = NULL;
    if (*stat == 0) {
        if (mouse_in_grid(mouse, 210, 430, 650, 470))
            image = IMG_Load("pictures/loginMenu/stat0/menuVorod.png");
        else if (mouse_in_grid(mouse, 210, 470, 650, 505))
            image = IMG_Load("pictures/loginMenu/stat0/menuEhraz.png");
        else 
            image = IMG_Load("pictures/loginMenu/stat0/menuAdi.png");
    }
    else if (*stat == 1) {
        if (mouse_in_grid(mouse, 210, 430, 650, 470))
            image = IMG_Load("pictures/loginMenu/stat1/menuVorod.png");
        else if (mouse_in_grid(mouse, 210, 470, 650, 505))
            image = IMG_Load("pictures/loginMenu/stat1/menuEhraz.png");
        else 
            image = IMG_Load("pictures/loginMenu/stat1/menuAdi.png");
    }
    else if (*stat == 2) {
        if (mouse_in_grid(mouse, 210, 430, 650, 470))
            image = IMG_Load("pictures/loginMenu/stat2/menuVorod.png");
        else if (mouse_in_grid(mouse, 210, 470, 650, 505))
            image = IMG_Load("pictures/loginMenu/stat2/menuEhraz.png");
        else 
            image = IMG_Load("pictures/loginMenu/stat2/menuAdi.png");
    }

    if (image == NULL) {
        printf("image not found\n");
        SDL_Quit();
        return;
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Rect startRect = {188, 167, 625, 367};
    
    ShowImage(image, renderer, &startRect);
    
    SDL_Surface *surface;
    SDL_Texture *texture;
    if (*stat != 1) {
        int tmp = strsz(userName);
        userName[tmp] = ' ';
        surface = TTF_RenderText_Solid(font, userName, textColor); 
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect startRect1 = {215, 240, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect1);
        SDL_RenderPresent(renderer);
        userName[tmp] = '|';
    }
    else {
        surface = TTF_RenderText_Solid(font, userName, textColor); 
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect startRect1 = {215, 240, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect1);
        SDL_RenderPresent(renderer);
    }

    int tmp = strsz(password);
    for (int i = 0; i < tmp; i++)
        stmp[i] = '*';
    for (int i = tmp; i < 50; i++)
        stmp[i] = ' ';
    stmp[49] = '\0';
    surface = TTF_RenderText_Solid(font, stmp, textColor); 
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect startRect2 = {215, 325, 320, 50};
    SDL_RenderCopy(renderer, texture, NULL, &startRect2);
    SDL_RenderPresent(renderer);

    
    TTF_CloseFont(font);
    SDL_FreeSurface(image);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

bool daneshjo_menu_event(SDL_Window *window, mouse_type *mouse, SDL_Renderer *renderer) {
    bool Is_done = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                if (window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    Is_done = 1;
                }
                break;
            }
            case SDL_QUIT: {
                Is_done = 1;
                break;
            }
            case SDL_MOUSEMOTION: {
                SDL_GetMouseState(&(mouse->x), &(mouse->y));
                // printf("(%d, %d)\n", mouse->x, mouse->y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT: {
                        if (mouse_in_grid(mouse, 10, 13, 75, 50)) {
                            daneshjoStat[0] = -1;
                        }
                        if (mouse_in_grid(mouse, 230, 126, 364, 247)) {
                            daneshjoStat[0] = -2;
                        }
                        if (mouse_in_grid(mouse, 692, 126, 826, 247)) {
                            daneshjoStat[0] = -3;
                        }
                        if (mouse_in_grid(mouse, 846, 126, 980, 247)) {
                            daneshjoStat[0] = -4;
                        }
                        if (mouse_in_grid(mouse, 846, 329, 980, 450)) {
                            daneshjoStat[0] = -5;
                        }
                        if (mouse_in_grid(mouse, 692, 329, 826, 450)) {
                            daneshjoStat[0] = -6;
                        }
                        if (mouse_in_grid(mouse, 538, 329, 672, 450)) {
                            daneshjoStat[0] = -7;
                        }
                        if (mouse_in_grid(mouse, 384, 329, 512, 450)) {
                            daneshjoStat[0] = -8;
                        }
                        if (mouse_in_grid(mouse, 230, 329, 364, 450)) {
                            daneshjoStat[0] = -9;
                        }
                        if (mouse_in_grid(mouse, 846, 532, 980, 653)) {
                            daneshjoStat[0] = -10;
                        }
                        if (mouse_in_grid(mouse, 692, 532, 826, 653)) {
                            daneshjoStat[0] = -11;
                        }
                        if (mouse_in_grid(mouse, 538, 532, 672, 653)) {
                            daneshjoStat[0] = -12;
                        }
                        break;
                    }
                }
            }
            case SDL_KEYDOWN: {
                switch(event.key.keysym.sym) {
                    case SDLK_F1: {
                        updateTime();
                        break;
                    }
                }
                break;
            }
        }
    }
    return Is_done;
}

void Render_daneshjo_menu(SDL_Renderer *renderer, mouse_type *mouse) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *image = NULL;
    image = IMG_Load("pictures/daneshjoMenu/banner.png");
    SDL_Rect Rec = {0, 0, 1000, 63};
    ShowImage(image, renderer, &Rec);

    image = IMG_Load("pictures/daneshjoMenu/amordaneshjoi.png");
    SDL_Rect Rec2 = {0, 64, 1000, 42};
    ShowImage(image, renderer, &Rec2);
   
    image = IMG_Load("pictures/daneshjoMenu/amorghazai.png");
    SDL_Rect Rec4 = {0, 267, 1000, 42};
    ShowImage(image, renderer, &Rec4);

    image = IMG_Load("pictures/daneshjoMenu/gozareshat.png");
    SDL_Rect RecS = {0, 470, 1000, 42};
    ShowImage(image, renderer, &RecS);

    //omor daneshjoi
    if (mouse_in_grid(mouse, 846, 126, 980, 247))
        image = IMG_Load("pictures/daneshjoMenu/sharj2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/sharj1.png");
    SDL_Rect Rec3 = {846, 126, 134, 121};
    ShowImage(image, renderer, &Rec3);

    if (mouse_in_grid(mouse, 692, 126, 826, 247))
        image = IMG_Load("pictures/daneshjoMenu/ersalsharj2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/ersalsharj1.png");
    SDL_Rect Rec5 = {692, 126, 134, 121};
    ShowImage(image, renderer, &Rec5);

    if (mouse_in_grid(mouse, 538, 126, 672, 247))
        image = IMG_Load("pictures/daneshjoMenu/news2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/news1.png");
    SDL_Rect Rec6 = {538, 126, 134, 121};
    ShowImage(image, renderer, &Rec6);

    if (mouse_in_grid(mouse, 384, 126, 518, 247))
        image = IMG_Load("pictures/daneshjoMenu/poll2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/poll1.png");
    SDL_Rect Rec7 = {384, 126, 134, 121};
    ShowImage(image, renderer, &Rec7);

    if (mouse_in_grid(mouse, 230, 126, 364, 247))
        image = IMG_Load("pictures/daneshjoMenu/pass2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/pass1.png");
    SDL_Rect Rec8 = {230, 126, 134, 121};
    ShowImage(image, renderer, &Rec8);

    //omor ghazai
    if (mouse_in_grid(mouse, 846, 329, 980, 450))
        image = IMG_Load("pictures/daneshjoMenu/reserve2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/reserve1.png");
    SDL_Rect Rec10 = {846, 329, 134, 121};
    ShowImage(image, renderer, &Rec10);

    if (mouse_in_grid(mouse, 692, 329, 826, 450))
        image = IMG_Load("pictures/daneshjoMenu/rozforosh2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/rozforosh1.png");
    SDL_Rect Rec11 = {692, 329, 134, 121};
    ShowImage(image, renderer, &Rec11);

    if (mouse_in_grid(mouse, 538, 329, 672, 450))
        image = IMG_Load("pictures/daneshjoMenu/emkan2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/emkan1.png");
    SDL_Rect Rec12 = {538, 329, 134, 121};
    ShowImage(image, renderer, &Rec12);

    if (mouse_in_grid(mouse, 384, 329, 512, 450))
        image = IMG_Load("pictures/daneshjoMenu/tahvil2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/tahvil1.png");
    SDL_Rect Rec13 = {384, 329, 134, 121};
    ShowImage(image, renderer, &Rec13);

    if (mouse_in_grid(mouse, 230, 329, 364, 450))
        image = IMG_Load("pictures/daneshjoMenu/cancel2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/cancel1.png");
    SDL_Rect Rec14 = {230, 329, 134, 121};
    ShowImage(image, renderer, &Rec14);

    // gozareshat
    if (mouse_in_grid(mouse, 846, 532, 980, 653))
        image = IMG_Load("pictures/daneshjoMenu/gozareshmali2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/gozareshmali1.png");
    SDL_Rect Rec15 = {846, 532, 134, 121};
    ShowImage(image, renderer, &Rec15);

    if (mouse_in_grid(mouse, 692, 532, 826, 653))
        image = IMG_Load("pictures/daneshjoMenu/gozaresheghaza2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/gozaresheghaza1.png");
    SDL_Rect Rec16 = {692, 532, 134, 121};
    ShowImage(image, renderer, &Rec16);

    if (mouse_in_grid(mouse, 538, 532, 672, 653))
        image = IMG_Load("pictures/daneshjoMenu/barname2.png");
    else 
        image = IMG_Load("pictures/daneshjoMenu/barname1.png");
    SDL_Rect Rec17 = {538, 532, 134, 121};
    ShowImage(image, renderer, &Rec17);
    //payan

    if (mouse_in_grid(mouse, 10, 13, 75, 50))
        image = IMG_Load("pictures/daneshjoMenu/khoroji2.png");
    else
        image = IMG_Load("pictures/daneshjoMenu/khoroj1.png");

    SDL_Rect Rec1 = {10, 13, 65, 37};
    ShowImage(image, renderer, &Rec1);
    SDL_FreeSurface(image);
    SDL_RenderPresent(renderer);
}

bool reg_menu_event(SDL_Window *window, mouse_type *mouse, SDL_Renderer *renderer) {
    bool Is_done = 0;
    SDL_Event event;
    bool textinput = 0;
    for (int i = 0; i < 7; i++)
        if (regStat[i] == 1)
            textinput = 1;
    if (textinput)
        SDL_StartTextInput();
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                if (window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    Is_done = 1;
                }
                break;
            }
            case SDL_QUIT: {
                Is_done = 1;
                break;
            }
            case SDL_MOUSEMOTION: {
                SDL_GetMouseState(&(mouse->x), &(mouse->y));
                // printf("(%d, %d)\n", mouse->x, mouse->y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT: {
                        for (int i = 0; i < 7; i++)
                            regStat[i] = 0;
                        if (mouse_in_grid(mouse, 280, 25, 719, 94))
                            regStat[0] = 1;
                        else if (mouse_in_grid(mouse, 280, 119, 719, 188))
                            regStat[1] = 1;
                        else if (mouse_in_grid(mouse, 280, 213, 719, 282))
                            regStat[2] = 1;
                        else if (mouse_in_grid(mouse, 280, 307, 719, 376))
                            regStat[3] = 1;
                        else if (mouse_in_grid(mouse, 280, 401, 719, 470))
                            regStat[4] = 1;
                        else if (mouse_in_grid(mouse, 280, 495, 719, 564))
                            regStat[5] = 1;
                        else if (mouse_in_grid(mouse, 280, 589, 719, 658))
                            regStat[6] = 1;
                        else if (mouse_in_grid(mouse, 10, 10, 43, 55))
                            regStat[7] = -1;
                        else if (mouse_in_grid(mouse, 165, 275, 186, 296))
                            regStat[8] ^= 1;
                        else if (mouse_in_grid(mouse, 50, 321, 184, 378)) {
                            regStat[7] = -2;
                        }

                        break;
                    }
                }
            }     
            case SDL_TEXTINPUT: {
                if (regStat[0]) {
                    int sz = strsz(nam);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        nam[sz + i] = event.text.text[i];
                    nam[sz + sz1] = '|'; 
                }
                else if (regStat[1]) {
                    int sz = strsz(khan);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        khan[sz + i] = event.text.text[i];
                    khan[sz + sz1] = '|'; 
                }
                else if (regStat[2]) {
                    int sz = strsz(user_id);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        user_id[sz + i] = event.text.text[i];
                    user_id[sz + sz1] = '|'; 
                }
                else if (regStat[4]) {
                    int sz = strsz(nat_id);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        nat_id[sz + i] = event.text.text[i];
                    nat_id[sz + sz1] = '|'; 
                }
                else if (regStat[6]) {
                    int sz = strsz(gen);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        gen[sz + i] = event.text.text[i];
                    gen[sz + sz1] = '|'; 
                }
                else if (regStat[5]) {
                    int sz = strsz(birth);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        birth[sz + i] = event.text.text[i];
                    birth[sz + sz1] = '|';
                }
                else if (regStat[3]) {
                    int sz = strsz(pass);
                    int sz1 = strlen(event.text.text);
                    for (int i = 0; i < sz1; i++)
                        pass[sz + i] = event.text.text[i];
                    pass[sz + sz1] = '|';
                }
                // int sz = strsz(password);
                // int sz1 = strlen(event.text.text);
                // for (int i = 0; i < sz1; i++)
                //     password[sz + i] = event.text.text[i];
                // password[sz + sz1] = '|'; 
                // break;
            }
            case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (regStat[0]) {
                                int sz = strsz(nam);
                                if (sz) {
                                    nam[sz - 1] = '|';
                                    nam[sz] = ' ';
                                }
                            } 
                            else if (regStat[1]) {
                                int sz = strsz(khan);
                                if (sz) {
                                    khan[sz - 1] = '|';
                                    khan[sz] = ' ';
                                }
                            }
                            else if (regStat[2]) {
                                int sz = strsz(user_id);
                                if (sz) {
                                    user_id[sz - 1] = '|';
                                    user_id[sz] = ' ';
                                }
                            }
                            else if (regStat[3]) {
                                int sz = strsz(pass);
                                if (sz) {
                                    pass[sz - 1] = '|';
                                    pass[sz] = ' ';
                                }
                            }
                            else if (regStat[4]) {
                                int sz = strsz(nat_id);
                                if (sz) {
                                    nat_id[sz - 1] = '|';
                                    nat_id[sz] = ' ';
                                }
                            }
                            else if (regStat[5]) {
                                int sz = strsz(birth);
                                if (sz) {
                                    birth[sz - 1] = '|';
                                    birth[sz] = ' ';
                                }
                            }
                            else if (regStat[6]) {
                                int sz = strsz(gen);
                                if (sz) {
                                    gen[sz - 1] = '|';
                                    gen[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
        }
    }
    if (textinput)
        SDL_StopTextInput();
    // printf("khanevadegi = %s user-id = %s regStat[2] = %d\n", khan, user_id, regStat[2]);
    return Is_done;
}

void Render_reg_menu(SDL_Renderer *renderer, mouse_type *mouse) {
    SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
    SDL_RenderClear(renderer);
    
    SDL_Rect Rect0 = {280, 25, 439, 69};
    if (regStat[0] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/nam1.png");
        ShowImage(surface, renderer, &Rect0);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(nam);
        nam[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, nam, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        nam[sz] = '|';
        SDL_Rect startRect2 = {285, 25, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/nam2.png");
        ShowImage(surface, renderer, &Rect0);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, nam, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 25, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }

    SDL_Rect Rect1 = {280, 119, 439, 69};
    if (regStat[1] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/khan1.png");
        ShowImage(surface, renderer, &Rect1);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(khan);
        khan[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, khan, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        khan[sz] = '|';
        SDL_Rect startRect2 = {285, 119, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/khan2.png");
        ShowImage(surface, renderer, &Rect1);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, khan, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 119, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }

    SDL_Rect Rect2 = {280, 213, 439, 69};
    if (regStat[2] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/user-id1.png");
        ShowImage(surface, renderer, &Rect2);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(user_id);
        user_id[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        user_id[sz] = '|';
        SDL_Rect startRect2 = {285, 213, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/user-id2.png");
        ShowImage(surface, renderer, &Rect2);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 213, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }

    SDL_Rect Rect3 = {280, 307, 439, 69};
    if (regStat[3] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/pass1.png");
        ShowImage(surface, renderer, &Rect3);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(pass);
        pass[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, pass, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        pass[sz] = '|';
        SDL_Rect startRect2 = {285, 307, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/pass2.png");
        ShowImage(surface, renderer, &Rect3);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, pass, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 307, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }

    SDL_Rect Rect4 = {280, 401, 439, 69};
    if (regStat[4] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/kodmeli1.png");
        ShowImage(surface, renderer, &Rect4);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(nat_id);
        nat_id[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, nat_id, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        nat_id[sz] = '|';
        SDL_Rect startRect2 = {285, 401, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/kodmeli2.png");
        ShowImage(surface, renderer, &Rect4);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, nat_id, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 401, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }

    SDL_Rect Rect5 = {280, 495, 439, 69};
    if (regStat[5] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/birth1.png");
        ShowImage(surface, renderer, &Rect5);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(birth);
        birth[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, birth, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        birth[sz] = '|';
        SDL_Rect startRect2 = {285, 495, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/birth2.png");
        ShowImage(surface, renderer, &Rect5);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, birth, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 495, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }

    SDL_Rect Rect6 = {280, 589, 439, 69};
    if (regStat[6] == 0) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/gender1.png");
        ShowImage(surface, renderer, &Rect6);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        int sz = strsz(gen);
        gen[sz] = ' ';
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, gen, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
        gen[sz] = '|';
        SDL_Rect startRect2 = {285, 589, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/gender2.png");
        ShowImage(surface, renderer, &Rect6);
        SDL_FreeSurface(surface);

        TTF_Init();
        TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
        SDL_Color textColor = {0, 0, 0, 255};
        SDL_Surface *surface1 = TTF_RenderText_Solid(font, gen, textColor); 
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

        SDL_Rect startRect2 = {285, 589, 320, 50};
        SDL_RenderCopy(renderer, texture, NULL, &startRect2);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface1);
        TTF_CloseFont(font);
    }


    //ezafat
    SDL_Rect startRec = {50, 321, 134, 57};
    if (mouse_in_grid(mouse, 50, 321, 184, 378)) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/ozviat2.png");
        ShowImage(surface, renderer, &startRec);
        SDL_FreeSurface(surface);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/ozviat1.png");
        ShowImage(surface, renderer, &startRec);
        SDL_FreeSurface(surface);
    }

    SDL_Rect startRec1 = {10, 10, 33, 45};
    if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/back2.png");
        ShowImage(surface, renderer, &startRec1);
        SDL_FreeSurface(surface);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/back1.png");
        ShowImage(surface, renderer, &startRec1);
        SDL_FreeSurface(surface);
    }
    SDL_Rect startRec2 = {165, 275, 21, 21};
    if (regStat[8]) {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/tik2.png");
        ShowImage(surface, renderer, &startRec2);
        SDL_FreeSurface(surface);
    }
    else {
        SDL_Surface *surface = IMG_Load("pictures/menuReg/tik1.png");
        ShowImage(surface, renderer, &startRec2);
        SDL_FreeSurface(surface);
    }
    SDL_Rect startRec3 = {5, 265, 150, 40};
    SDL_Surface *surface = IMG_Load("pictures/menuReg/personel.png");
    ShowImage(surface, renderer, &startRec3);
    SDL_FreeSurface(surface);

    SDL_RenderPresent(renderer);
} 

void clear_login_Menu(char *userName, char *password) {
    for (int i = 0; i < 49; i++)
            userName[i] = password[i] = ' ';
    userName[0] = '|';
    password[0] = '|';
}

void clear_reg_Menu() {
    nam[0] = khan[0] = birth[0] = pass[0] = user_id[0] = nat_id[0] = gen[0] = '|';
    selfname[0] = selfadd[0] = self_id[0] = selfcap[0] = selflunch[0] = selfdinner[0] = '|';
    foodname[0] = food_id[0] = foodcost[0] = '|';
    date[0] = cnt[0] = '|';
    for (int i = 1; i < 49; i++) {
        nam[i] = khan[i] = birth[i] = pass[i] = user_id[i] = nat_id[i] = gen[i] = ' '; 
        selfname[i] = selfadd[i] = self_id[i] = selfcap[i] = selflunch[i] = selfdinner[i] = ' ';
        foodname[i] = food_id[i] = foodcost[i] = ' ';
        date[i] = cnt[i] = ' ';
    }
    for (int i = 0; i < 9; i++)
        regStat[i] = 0;
}

void reg_user(int Is_admin, SDL_Renderer *renderer, bool testcase) {
    if (strsz(nam) == 0)
        return;
    if (strsz(khan) == 0)
        return;
    if (strsz(user_id) == 0)
        return;
    if (strsz(nat_id) == 0)
        return;
    if (strsz(gen) == 0)
        return;
    if (strsz(birth) == 0)
        return;
    if (strsz(pass) == 0)
        return;

    user *new_user = (user *)malloc(sizeof(user));
    int tmp = strsz(birth);
    birth[tmp] = '\0';
    sscanf(birth, "%d-%d-%d", &new_user->birthdate_year, &new_user->birthdate_month, &new_user->birthdate_day);
    
    int sz = strsz(nam);
    nam[sz] = '\0';

    sz = strsz(khan);
    khan[sz] = '\0';

    sz = strsz(nat_id);
    nat_id[sz] = '\0';

    sz = strsz(user_id);
    user_id[sz] = '\0';
    
    sz = strsz(gen);
    gen[sz] = '\0';
    
    sz = strsz(pass);
    pass[sz] = '\0';

    for (int i = 0; i < 50; i++) {
        new_user->family[i] = khan[i];
        new_user->name[i] = nam[i];
        new_user->gender[i] = gen[i];
        new_user->password[i] = pass[i];
        new_user->national_id[i] = nat_id[i];
        new_user->user_id[i] = user_id[i];
    }

    new_user->money_balance = 0;
    new_user->approved = Is_admin;
    new_user->id = -1;
    new_user->masol = regStat[8];
    if (regStat[8])
        new_user->money_balance = INF;

    user *pre_user = get_user(user_id);
    if (pre_user == NULL) {
        printf("this user_id is not taken\n");
        insert_user(new_user);

        char stm[50];
        sprintf(stm, "students/%s", new_user->user_id);
        mkdir(stm);

        ansans = 1;
        if (testcase) {
            free(new_user);
            return;
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        if (!Is_admin) {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/taidSabtenam.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/taidaprov.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
        }

        SDL_RenderPresent(renderer);
        

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }

        
    }
    else {
        if (testcase) {
            free(new_user);
            return;
        }
        printf("this user_id is taken\n");
        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);

        SDL_Surface *surface = IMG_Load("pictures/menuReg/taidNashodan.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);

        SDL_RenderPresent(renderer);
        
        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }

    free(new_user);
}

bool admin_menu_event(SDL_Window *window, mouse_type *mouse, SDL_Renderer *renderer) {
    bool Is_done = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                if (window) {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    Is_done = 1;
                }
                break;
            }
            case SDL_QUIT: {
                Is_done = 1;
                break;
            }
            case SDL_MOUSEMOTION: {
                SDL_GetMouseState(&(mouse->x), &(mouse->y));
                // printf("(%d, %d)\n", mouse->x, mouse->y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT: {
                        if (mouse_in_grid(mouse, 10, 13, 75, 50)) {
                            adminStat[0] = -1;
                        }
                        if (mouse_in_grid(mouse, 230, 126, 364, 247)) {
                            adminStat[0] = -2;
                        }
                        if (mouse_in_grid(mouse, 76, 126, 210, 247)) {
                            adminStat[0] = -3;
                        }
                        if (mouse_in_grid(mouse, 692, 126, 826, 247)) {
                            adminStat[0] = -4;
                        }
                        if (mouse_in_grid(mouse, 538, 126, 672, 247)) {
                            adminStat[0] = -5;
                        }
                        if (mouse_in_grid(mouse, 384, 126, 518, 247)) {
                            adminStat[0] = -6;
                        }
                        if (mouse_in_grid(mouse, 846, 126, 980, 247)) {
                            adminStat[0] = -7;
                        }
                        if (mouse_in_grid(mouse, 846, 329, 980, 450)) {
                            adminStat[0] = -8;
                        }
                        if (mouse_in_grid(mouse, 692, 329, 826, 450)) {
                            adminStat[0] = -9;
                        }
                        if (mouse_in_grid(mouse, 538, 329, 672, 450)) {
                            adminStat[0] = -10;
                        }
                        break;
                    }
                }
            }
        }
    }
    return Is_done;
}

void Render_admin_Menu(SDL_Renderer *renderer, mouse_type *mouse) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *image = NULL;
    image = IMG_Load("pictures/adminMenu/banner.png");
    SDL_Rect Rec = {0, 0, 1000, 63};
    ShowImage(image, renderer, &Rec);
    
    image = IMG_Load("pictures/adminMenu/amormodiriati.png");
    SDL_Rect Rec2 = {0, 64, 1000, 42};
    ShowImage(image, renderer, &Rec2);
   
    image = IMG_Load("pictures/adminMenu/amorghazai.png");
    SDL_Rect Rec4 = {0, 267, 1000, 42};
    ShowImage(image, renderer, &Rec4);

    image = IMG_Load("pictures/adminMenu/gozareshat.png");
    SDL_Rect RecS = {0, 470, 1000, 42};
    ShowImage(image, renderer, &RecS);

    // omor modiriat
    if (mouse_in_grid(mouse, 846, 126, 980, 247))
        image = IMG_Load("pictures/adminMenu/taidkarbar2.png");
    else 
        image = IMG_Load("pictures/adminMenu/taidkarbar1.png");
    SDL_Rect Rec3 = {846, 126, 134, 121};
    ShowImage(image, renderer, &Rec3);

    if (mouse_in_grid(mouse, 692, 126, 826, 247))
        image = IMG_Load("pictures/adminMenu/passchange2.png");
    else 
        image = IMG_Load("pictures/adminMenu/passchange1.png");
    SDL_Rect Rec5 = {692, 126, 134, 121};
    ShowImage(image, renderer, &Rec5);

    if (mouse_in_grid(mouse, 538, 126, 672, 247))
        image = IMG_Load("pictures/adminMenu/deactive2.png");
    else 
        image = IMG_Load("pictures/adminMenu/deactive1.png");
    SDL_Rect Rec6 = {538, 126, 134, 121};
    ShowImage(image, renderer, &Rec6);

    if (mouse_in_grid(mouse, 384, 126, 518, 247))
        image = IMG_Load("pictures/adminMenu/money2.png");
    else 
        image = IMG_Load("pictures/adminMenu/money1.png");
    SDL_Rect Rec7 = {384, 126, 134, 121};
    ShowImage(image, renderer, &Rec7);

    if (mouse_in_grid(mouse, 230, 126, 364, 247))
        image = IMG_Load("pictures/adminMenu/reg2.png");
    else 
        image = IMG_Load("pictures/adminMenu/reg1.png");
    SDL_Rect Rec8 = {230, 126, 134, 121};
    ShowImage(image, renderer, &Rec8);

    if (mouse_in_grid(mouse, 76, 126, 210, 247))
        image = IMG_Load("pictures/adminMenu/pass2.png");
    else 
        image = IMG_Load("pictures/adminMenu/pass1.png");
    SDL_Rect Rec9 = {76, 126, 134, 121};
    ShowImage(image, renderer, &Rec9);

    // omor ghazai
    if (mouse_in_grid(mouse, 846, 329, 980, 450))
        image = IMG_Load("pictures/adminMenu/self2.png");
    else 
        image = IMG_Load("pictures/adminMenu/self1.png");
    SDL_Rect Rec10 = {846, 329, 134, 121};
    ShowImage(image, renderer, &Rec10);

    if (mouse_in_grid(mouse, 692, 329, 826, 450))
        image = IMG_Load("pictures/adminMenu/food2.png");
    else 
        image = IMG_Load("pictures/adminMenu/food1.png");
    SDL_Rect Rec11 = {692, 329, 134, 121};
    ShowImage(image, renderer, &Rec11);

    if (mouse_in_grid(mouse, 538, 329, 672, 450))
        image = IMG_Load("pictures/adminMenu/meal2.png");
    else 
        image = IMG_Load("pictures/adminMenu/meal1.png");
    SDL_Rect Rec12 = {538, 329, 134, 121};
    ShowImage(image, renderer, &Rec12);

    //gozareshat

    if (mouse_in_grid(mouse, 846, 532, 980, 653))
        image = IMG_Load("pictures/adminMenu/amarReserv2.png");
    else 
        image = IMG_Load("pictures/adminMenu/amarReserv1.png");
    SDL_Rect Rec13 = {846, 532, 134, 121};
    ShowImage(image, renderer, &Rec13);

    if (mouse_in_grid(mouse, 692, 532, 826, 653))
        image = IMG_Load("pictures/adminMenu/gozareshShakhs2.png");
    else 
        image = IMG_Load("pictures/adminMenu/gozareshShakhs1.png");
    SDL_Rect Rec14 = {692, 532, 134, 121};
    ShowImage(image, renderer, &Rec14);

    if (mouse_in_grid(mouse, 538, 532, 672, 653))
        image = IMG_Load("pictures/adminMenu/gozareshSamane2.png");
    else 
        image = IMG_Load("pictures/adminMenu/gozareshSamane1.png");
    SDL_Rect Rec15 = {538, 532, 134, 121};
    ShowImage(image, renderer, &Rec15);

    if (mouse_in_grid(mouse, 384, 532, 518, 653))
        image = IMG_Load("pictures/adminMenu/news2.png");
    else 
        image = IMG_Load("pictures/adminMenu/news1.png");
    SDL_Rect Rec16 = {384, 532, 134, 121};
    ShowImage(image, renderer, &Rec16);

    if (mouse_in_grid(mouse, 230, 532, 364, 653))
        image = IMG_Load("pictures/adminMenu/poll2.png");
    else 
        image = IMG_Load("pictures/adminMenu/poll1.png");
    SDL_Rect Rec17 = {230, 532, 134, 121};
    ShowImage(image, renderer, &Rec17);

    //payan

    if (mouse_in_grid(mouse, 10, 13, 75, 50))
        image = IMG_Load("pictures/adminMenu/khoroji2.png");
    else
        image = IMG_Load("pictures/adminMenu/khoroj1.png");

    SDL_Rect Rec1 = {10, 13, 65, 37};
    ShowImage(image, renderer, &Rec1);
    SDL_FreeSurface(image);
    SDL_RenderPresent(renderer);
}

void login_user(SDL_Renderer *renderer, char *userName, char *password, int *stat, bool testcase) {
    if (strsz(userName) == 0)
        return;
    if (strsz(password) == 0)
        return;
    
    int sz = strsz(userName);
    userName[sz] = '\0';
    
    sz = strsz(password);
    password[sz] = '\0';
    

    user *new_user = get_user(userName);
    if (new_user == NULL) {
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/loginMenu/wrongId.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);

        SDL_RenderPresent(renderer);
        SDL_FreeSurface(surface);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        if (strcmp(new_user->password, password) == 0) {
            if (new_user->approved) {
                ansans = 1;
                if (new_user->masol)    
                    (*stat) = 1;
                else
                    (*stat) = 2;

                logedIn = new_user;
            }
            else {
                if (testcase)
                    return;
                SDL_Surface *surface = IMG_Load("pictures/loginMenu/notcom.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);

                SDL_RenderPresent(renderer);
                SDL_FreeSurface(surface);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        else {
            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/loginMenu/wrongPass.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);

            SDL_RenderPresent(renderer);
            SDL_FreeSurface(surface);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    clear_login_Menu(userName, password);
}

void clearChangePass() {
    for (int i = 0; i < 50; i++)
        lastpass[i] = newpass[i] = newpass2[i] = user_id[i] = money[i] = ' ';
    lastpass[0] = newpass[0] = newpass2[0] = user_id[0] = money[0] = '|';
    for (int i = 1; i < 9; i++)
        adminStat[i] = regStat[i] = 0;
}

void ChangePass(SDL_Renderer *renderer, bool testcase) {
    if (strsz(lastpass) == 0)
        return;
    if (strsz(newpass) == 0)
        return;
    if (strsz(newpass2) == 0)
        return;

    int sz = strsz(lastpass);
    lastpass[sz] = '\0';
    sz = strsz(newpass);
    newpass[sz] = '\0';
    sz = strsz(newpass2);
    newpass2[sz] = '\0';

    if (strcmp(lastpass, logedIn->password) == 0) {
        if (strcmp(newpass, newpass2) == 0) {
            for (int i = 0; i < 50; i++)
                logedIn->password[i] = newpass[i];

            update_user(logedIn->id, logedIn);
            
            ansans = 1;
            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/taidpasschange.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            
            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/pass!=pass2.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        ansans = 2;
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/taidNashodan.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }

    clearChangePass();
}

bool changepass(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94)) {
                                adminStat[1] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(lastpass);
                                if (sz) {
                                    lastpass[sz - 1] = '|';
                                    lastpass[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(newpass);
                                if (sz) {
                                    newpass[sz - 1] = '|';
                                    newpass[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(newpass2);
                                if (sz) {
                                    newpass2[sz - 1] = '|';
                                    newpass2[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(lastpass);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            lastpass[sz + i] = event.text.text[i];
                        lastpass[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(newpass);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            newpass[sz + i] = event.text.text[i];
                        newpass[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(newpass2);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            newpass2[sz + i] = event.text.text[i];
                        newpass2[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            ChangePass(renderer, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passghabli1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(lastpass);
            lastpass[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, lastpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            lastpass[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passghabli2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, lastpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadid1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(newpass);
            newpass[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            newpass[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadid2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadiddobare1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(newpass2);
            newpass2[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass2, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            newpass2[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadiddobare2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass2, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void ChangePassDaneshjo(SDL_Renderer *renderer, bool testcase) {
    if (strsz(user_id) == 0)
        return;
    if (strsz(newpass) == 0)
        return;
    if (strsz(newpass2) == 0)
        return;

    int sz = strsz(user_id);
    user_id[sz] = '\0';
    sz = strsz(newpass);
    newpass[sz] = '\0';
    sz = strsz(newpass2);
    newpass2[sz] = '\0';

    user *new_user = get_user(user_id);

    if (new_user == NULL) {
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        if (strcmp(newpass, newpass2) == 0) {
            for (int i = 0; i < 50; i++)
                new_user->password[i] = newpass[i];
            
            update_user(new_user->id, new_user);
            free(new_user);
            ansans = 1;
            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/taidpasschange.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            free(new_user);
            if (testcase) 
                return;
            
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/pass!=pass2.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    clearChangePass();
}

bool changepassdaneshjo(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94)) {
                                adminStat[1] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(user_id);
                                if (sz) {
                                    user_id[sz - 1] = '|';
                                    user_id[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(newpass);
                                if (sz) {
                                    newpass[sz - 1] = '|';
                                    newpass[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(newpass2);
                                if (sz) {
                                    newpass2[sz - 1] = '|';
                                    newpass2[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(user_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            user_id[sz + i] = event.text.text[i];
                        user_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(newpass);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            newpass[sz + i] = event.text.text[i];
                        newpass[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(newpass2);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            newpass2[sz + i] = event.text.text[i];
                        newpass2[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            ChangePassDaneshjo(renderer, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/user_id1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(user_id);
            user_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            user_id[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/user_id2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadid1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(newpass);
            newpass[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            newpass[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadid2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadiddobare1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(newpass2);
            newpass2[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass2, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            newpass2[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/passjadiddobare2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass2, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void deactive_user(SDL_Renderer *renderer, bool del, bool testcase) {
    if (strsz(user_id) == 0)
        return;

    user_id[strsz(user_id)] = '\0';
    user *new_user = get_user(user_id);
    if (new_user == NULL) {
        free(new_user);
        clearChangePass();
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
        
    }
    else {
        if (del == 1)
            delete_user(new_user);
        else {
            new_user->approved = 0;
            update_user(new_user->id, new_user);
        }   
        ansans = 1;
        clearChangePass();
        free(new_user);
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/amaliatMovafagh.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    
}

bool deactiveUser(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i < 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 189, 719, 258)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 480, 268, 501, 289) || mouse_in_grid(mouse, 698, 268, 719, 289)) {
                                adminStat[3] ^= 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            
                            if (adminStat[2]) {
                                int sz = strsz(user_id);
                                if (sz) {
                                    user_id[sz - 1] = '|';
                                    user_id[sz] = ' ';
                                }
                            }
                            
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[2]) {
                        int sz = strsz(user_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            user_id[sz + i] = event.text.text[i];
                        user_id[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            deactive_user(renderer, adminStat[3], 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect1 = {280, 189, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/user_id1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(user_id);
            user_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            user_id[sz] = '|';
            SDL_Rect startRect2 = {285, 189, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/user_id2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 189, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {480, 268, 21, 21};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/tik1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);
        } 
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/tik2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);
        }

        SDL_Rect Rect3 = {698, 268, 21, 21};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/tik2.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/tik1.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);
        }

        SDL_Rect Rect4 = {598, 258, 100, 40};
        {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/deactive.png");
            ShowImage(surface, renderer, &Rect4);
            SDL_FreeSurface(surface);
        }
        SDL_Rect Rect5 = {380, 258, 100, 40};
        {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/delete.png");
            ShowImage(surface, renderer, &Rect5);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45}; 
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }

        

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void ChargeStudent(SDL_Renderer *renderer, bool testcase) {
    if (strsz(user_id) == 0)
        return;
    if (strsz(money) == 0)
        return;

    int money_inc;
    sscanf(money, "%d", &money_inc);

    user_id[strsz(user_id)] = '\0';
    money[strsz(money)] = '\0';
    
    user *new_user = get_user(user_id);
    if (new_user == NULL) {
        clearChangePass();
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
        
    }
    else {
        if (money_inc > logedIn->money_balance) {
            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/taidNashodan.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            ansans = 1;
            new_user->money_balance += money_inc;
            update_user(new_user->id, new_user);
            char tmp[50];
            sprintf(tmp, "students/%s/money.txt", new_user->user_id);
            FILE *file = fopen(tmp, "a");
            fprintf(file, "%.4d-%.2d-%.2d // charging\n+%d\n", time.year, time.month, time.day, money_inc);
            fclose(file);

            if (logedIn->masol != 1) {
                logedIn->money_balance -= money_inc;
                update_user(logedIn->id, logedIn);
                sprintf(tmp, "students/%s/money.txt", logedIn->user_id);

                file = fopen(tmp, "a");
                fprintf(file, "%.4d-%.2d-%.2d charging\n-%d\n", time.year, time.month, time.day, money_inc);
                fclose(file);
            }

            clearChangePass();

            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/adminMenu/deactive/amaliatMovafagh.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

bool chargeStudentAcc(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[2]) {
                                int sz = strsz(user_id);
                                if (sz) {
                                    user_id[sz - 1] = '|';
                                    user_id[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(money);
                                if (sz) {
                                    money[sz - 1] = '|';
                                    money[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[2]) {
                        int sz = strsz(user_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            user_id[sz + i] = event.text.text[i];
                        user_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(money);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            money[sz + i] = event.text.text[i];
                        money[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            ChargeStudent(renderer, 0);
            clearChangePass();
            clear_reg_Menu();
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/user_id1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(user_id);
            user_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            user_id[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/user_id2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/charge1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(money);
            money[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, money, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            money[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/charge2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, money, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void approving(char *userid) {
    user *new_user = get_user(userid);
    if (new_user == NULL) {
        printf("user not found\n");
        ansans = 0;
        return;
    }

    new_user->approved = 1;
    update_user(new_user->id, new_user);
    free(new_user);
}

bool approve_user(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    bool Is_done = 0;
    bool empty = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool chng = 0, ap = 0, notap = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 554, 719, 598)) {
                                notap = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 490, 719, 534)) {
                                ap = 1;
                            }
                            break;
                        }
                    }
                }
            }
        }

        user *new_user = get_notapproved();
        bool rad = 0;
        
        if (new_user == NULL) {
            empty = 1;
            break;
        }

        if (ap) {
            approving(new_user->user_id);
        }
        if (notap) {
            delete_user(new_user);
        }

        rad = 0;
        for (int i = 0; i < 50; i++) {
            if (!rad) {
                nam[i] = new_user->name[i];
                if (new_user->name[i] == '\0') {
                    rad = 1;
                    nam[i] = '|';
                }
            }
            else    
                nam[i] = ' ';
        }
        rad = 0;
        for (int i = 0; i < 50; i++) {
            if (!rad) {
                khan[i] = new_user->family[i];
                if (new_user->family[i] == '\0') {
                    rad = 1;
                    khan[i] = '|';
                }
            }
            else    
                khan[i] = ' ';
        }

        rad = 0;
        for (int i = 0; i < 50; i++) {
            if (!rad) {
                user_id[i] = new_user->user_id[i];
                if (new_user->user_id[i] == '\0') {
                    rad = 1;
                    user_id[i] = '|';
                }
            }
            else    
                user_id[i] = ' ';
        }

        rad = 0;
        for (int i = 0; i < 50; i++) {
            if (!rad) {
                gen[i] = new_user->gender[i];
                if (new_user->gender[i] == '\0') {
                    rad = 1;
                    gen[i] = '|';
                }
            }
            else    
                gen[i] = ' ';
        }

        rad = 0;
        for (int i = 0; i < 50; i++) {
            if (!rad) {
                nat_id[i] = new_user->national_id[i];
                if (new_user->national_id[i] == '\0') {
                    rad = 1;
                    nat_id[i] = '|';
                }
            }
            else    
                nat_id[i] = ' ';
        }



        if (br)
            break;

        if (chng) {
            ChargeStudent(renderer, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);

        SDL_Rect Rect0 = {280, 25, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/nam1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(nam);
            nam[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, nam, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            nam[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/khan1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(khan);
            khan[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, khan, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            khan[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/user-id1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(user_id);
            user_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, user_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            user_id[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect3 = {280, 307, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/gender1.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(gen);
            gen[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, gen, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            gen[sz] = '|';
            SDL_Rect startRect2 = {285, 307, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect4 = {280, 401, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/kodmeli1.png");
            ShowImage(surface, renderer, &Rect4);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(nat_id);
            nat_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, nat_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            nat_id[sz] = '|';
            SDL_Rect startRect2 = {285, 401, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec2 = {280, 490, 439, 44};
        if (mouse_in_grid(mouse, 280, 490, 719, 534)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec3 = {280, 554, 439, 44};
        if (mouse_in_grid(mouse, 280, 554, 719, 598)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/notaproved2.png");
            ShowImage(surface, renderer, &startRec3);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/notaproved1.png");
            ShowImage(surface, renderer, &startRec3);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        free(new_user);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;

    if (empty) {
        SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    
    return Is_done;
}

void defineSelf(SDL_Renderer *renderer, bool testcase) {
    if (strsz(selfname) == 0)
        return;
    if (strsz(selfadd) == 0)
        return;
    if (strsz(self_id) == 0)
        return;
    if (strsz(selfcap) == 0)
        return;
    if (strsz(selflunch) == 0)
        return;
    if (strsz(selfdinner) == 0)
        return;

    selfname[strsz(selfname)] = '\0';
    selfadd[strsz(selfadd)] = '\0';
    self_id[strsz(self_id)] = '\0';
    selfcap[strsz(selfcap)] = '\0';
    selflunch[strsz(selflunch)] = '\0';
    selfdinner[strsz(selfdinner)] = '\0';

    self *new_self = get_self(self_id);

    if (new_self == NULL) {
        free(new_self);
        self *newself = malloc(sizeof(self));
        for (int i = 0; i < 50; i++) {
            newself->name[i] = selfname[i];
            newself->address[i] = selfadd[i];
            newself->self_id[i] = self_id[i];

            newself->lunch_time[i] = selflunch[i];
            newself->dinner_time[i] = selfdinner[i];
        }
        newself->girlish = adminStat[8];

        sscanf(selfcap, "%d", &newself->capacity);
        insert_self(newself);

        char stm[50];
        sprintf(stm, "selfs/%s", self_id);
        mkdir(stm);

        FILE *f = fopen("selfs/self.txt", "a");
        fprintf(f, "%s\t%s\t%s\n", self_id, selfname, selfadd);
        fclose(f);

        free(newself);
        ansans = 1;
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/amaliatMovafagh.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    } 
    else {
        free(new_self);
        clearChangePass();
        clear_reg_Menu();
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    clearChangePass();
    clear_reg_Menu();
}

bool define_self(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 8; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i < 8; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94))
                                adminStat[1] = 1;
                            else if (mouse_in_grid(mouse, 280, 119, 719, 188))
                                adminStat[2] = 1;
                            else if (mouse_in_grid(mouse, 280, 213, 719, 282))
                                adminStat[3] = 1;
                            else if (mouse_in_grid(mouse, 280, 307, 719, 376))
                                adminStat[4] = 1;
                            else if (mouse_in_grid(mouse, 280, 401, 719, 470))
                                adminStat[5] = 1;
                            else if (mouse_in_grid(mouse, 280, 495, 719, 564))
                                adminStat[6] = 1;
                            else if (mouse_in_grid(mouse, 165, 275, 186, 296))
                                adminStat[8] ^= 1;
                            if (mouse_in_grid(mouse, 50, 321, 184, 378))
                                chng = 1;
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(selfname);
                                if (sz) {
                                    selfname[sz - 1] = '|';
                                    selfname[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(selfadd);
                                if (sz) {
                                    selfadd[sz - 1] = '|';
                                    selfadd[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(self_id);
                                if (sz) {
                                    self_id[sz - 1] = '|';
                                    self_id[sz] = ' ';
                                }
                            }
                            else if (adminStat[4]) {
                                int sz = strsz(selfcap);
                                if (sz) {
                                    selfcap[sz - 1] = '|';
                                    selfcap[sz] = ' ';
                                }
                            }
                            else if (adminStat[5]) {
                                int sz = strsz(selflunch);
                                if (sz) {
                                    selflunch[sz - 1] = '|';
                                    selflunch[sz] = ' ';
                                }
                            }
                            else if (adminStat[6]) {
                                int sz = strsz(selfdinner);
                                if (sz) {
                                    selfdinner[sz - 1] = '|';
                                    selfdinner[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(selfname);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selfname[sz + i] = event.text.text[i];
                        selfname[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(selfadd);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selfadd[sz + i] = event.text.text[i];
                        selfadd[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(self_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            self_id[sz + i] = event.text.text[i];
                        self_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[5]) {
                        int sz = strsz(selflunch);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selflunch[sz + i] = event.text.text[i];
                        selflunch[sz + sz1] = '|'; 
                    }
                    else if (adminStat[6]) {
                        int sz = strsz(selfdinner);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selfdinner[sz + i] = event.text.text[i];
                        selfdinner[sz + sz1] = '|';
                    }
                    else if (adminStat[4]) {
                        int sz = strsz(selfcap);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selfcap[sz + i] = event.text.text[i];
                        selfcap[sz + sz1] = '|';
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            defineSelf(renderer, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_name1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selfname);
            selfname[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfname, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selfname[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_name2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfname, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_adres1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selfadd);
            selfadd[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfadd, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selfadd[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_adres2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfadd, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_id1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(self_id);
            self_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            self_id[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_id2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect3 = {280, 307, 439, 69};
        if (adminStat[4] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_cap1.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selfcap);
            selfcap[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfcap, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selfcap[sz] = '|';
            SDL_Rect startRect2 = {285, 307, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_cap2.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfcap, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 307, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect4 = {280, 401, 439, 69};
        if (adminStat[5] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/lunchtime1.png");
            ShowImage(surface, renderer, &Rect4);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selflunch);
            selflunch[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selflunch[sz] = '|';
            SDL_Rect startRect2 = {285, 401, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/lunchtime2.png");
            ShowImage(surface, renderer, &Rect4);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 401, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect5 = {280, 495, 439, 69};
        if (adminStat[6] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/dinnertime1.png");
            ShowImage(surface, renderer, &Rect5);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selfdinner);
            selfdinner[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfdinner, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selfdinner[sz] = '|';
            SDL_Rect startRect2 = {285, 495, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/dinnertime2.png");
            ShowImage(surface, renderer, &Rect5);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selfdinner, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 495, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        //ezafat
        SDL_Rect startRec = {50, 321, 134, 57};
        if (mouse_in_grid(mouse, 50, 321, 184, 378)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/ozviat1.png");
            ShowImage(surface, renderer, &startRec);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/ozviat2.png");
            ShowImage(surface, renderer, &startRec);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {165, 275, 21, 21};
        if (adminStat[8]) {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/tik2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/tik1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        SDL_Rect startRec3 = {5, 265, 150, 40};
        {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/personel.png");
            ShowImage(surface, renderer, &startRec3);
            SDL_FreeSurface(surface);
        }
        
        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void defineFood(SDL_Renderer *renderer, bool testcase) {
    if (strsz(foodname) == 0)
        return;
    if (strsz(foodcost) == 0)
        return;
    if (strsz(food_id) == 0)
        return;

    foodname[strsz(foodname)] = '\0';
    foodcost[strsz(foodcost)] = '\0';
    food_id[strsz(food_id)] = '\0';

    food *new_food = get_food(food_id);

    if (new_food == NULL) {
        free(new_food);

        food *newfood = malloc(sizeof(food));
        for (int i = 0; i < 50; i++) {
            newfood->name[i] = foodname[i];
            newfood->food_id[i] = food_id[i];
        }
        newfood->desert = adminStat[8];
        sscanf(foodcost, "%d", &newfood->cost);
        
        insert_food(newfood);
        
        FILE *f = fopen("foods/food.txt", "a");
        fprintf(f, "%s\t%s\t%s\n", food_id, foodname, foodcost);
        fclose(f);

        free(newfood);

        ansans = 1;
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/amaliatMovafagh.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    } 
    else {
        free(new_food);
        clearChangePass();
        clear_reg_Menu();
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    clearChangePass();
    clear_reg_Menu();
}

bool define_food(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 8; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i < 8; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94))
                                adminStat[1] = 1;
                            else if (mouse_in_grid(mouse, 280, 119, 719, 188))
                                adminStat[2] = 1;
                            else if (mouse_in_grid(mouse, 280, 213, 719, 282))
                                adminStat[3] = 1;
                            else if (mouse_in_grid(mouse, 165, 275, 186, 296))
                                adminStat[8] ^= 1;
                            if (mouse_in_grid(mouse, 50, 321, 184, 378))
                                chng = 1;
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(foodname);
                                if (sz) {
                                    foodname[sz - 1] = '|';
                                    foodname[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(food_id);
                                if (sz) {
                                    food_id[sz - 1] = '|';
                                    food_id[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(foodcost);
                                if (sz) {
                                    foodcost[sz - 1] = '|';
                                    foodcost[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(foodname);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            foodname[sz + i] = event.text.text[i];
                        foodname[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(food_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            food_id[sz + i] = event.text.text[i];
                        food_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(foodcost);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            foodcost[sz + i] = event.text.text[i];
                        foodcost[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            defineFood(renderer, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/foodname1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(foodname);
            foodname[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, foodname, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            foodname[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/foodname2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, foodname, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/food_id1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(food_id);
            food_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, food_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            food_id[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/food_id2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, food_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/foodcost1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(foodcost);
            foodcost[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, foodcost, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            foodcost[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/foodcost2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, foodcost, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        
        //ezafat
        SDL_Rect startRec = {50, 321, 134, 57};
        if (mouse_in_grid(mouse, 50, 321, 184, 378)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/ozviat1.png");
            ShowImage(surface, renderer, &startRec);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/ozviat2.png");
            ShowImage(surface, renderer, &startRec);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {165, 275, 21, 21};
        if (adminStat[8]) {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/tik2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/tik1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        SDL_Rect startRec3 = {5, 265, 150, 40};
        {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/personel.png");
            ShowImage(surface, renderer, &startRec3);
            SDL_FreeSurface(surface);
        }
        
        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void defineMeal(SDL_Renderer *renderer, bool testcase) {
    if (strsz(food_id) == 0)
        return;
    if (strsz(self_id) == 0)
        return;
    if (strsz(cnt) == 0)
        return;
    if (strsz(date) == 0)
        return;

    food_id[strsz(food_id)] = '\0';
    self_id[strsz(self_id)] = '\0';
    date[strsz(date)] = '\0';
    cnt[strsz(cnt)] = '\0';

    self *new_self = get_self(self_id);
    food *new_food = get_food(food_id);

    if (new_self != NULL && new_food != NULL) {
       
        char stm[50];
        sprintf(stm, "selfs/%s/%s", self_id, date);
        mkdir(stm);

        int price = new_food->cost;
        if ((adminStat[0] == 0 && strcmp(new_self->lunch_time, "-1") == 0) || (adminStat[0] == 1 && strcmp(new_self->dinner_time, "-1") == 0)) {
            ansans = 1;
            if (testcase)
                return;
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/arzenemishe.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            if (adminStat[8] == 0) {
                ansans = 1;
                sprintf(stm, "selfs/%s/%s/lunch", self_id, date);
                mkdir(stm);
                sprintf(stm, "selfs/%s/%s/lunch/meal.txt", self_id, date);
                FILE *f = fopen(stm, "w");
                int cnt1;
                sscanf(cnt, "%d", &cnt1);
                fprintf(f, "%s %d %d 0 0\n", new_food->name, cnt1, price);
                fclose(f);

                sprintf(stm, "selfs/%s/lunch.txt", self_id);
                f = fopen(stm, "a");
                fprintf(f, "%s\n", date);
                fclose(f);
            }
            else {
                ansans = 1;
                sprintf(stm, "selfs/%s/%s/dinner", self_id, date);
                mkdir(stm);
                sprintf(stm, "selfs/%s/%s/dinner/meal.txt", self_id, date);
                FILE *f = fopen(stm, "w");
                int cnt1;
                sscanf(cnt, "%d", &cnt1);
                fprintf(f, "%s %d %d 0 0\n", new_food->name, cnt1, price);
                fclose(f);

                sprintf(stm, "selfs/%s/dinner.txt", self_id);
                f = fopen(stm, "a");
                fprintf(f, "%s\n", date);
                fclose(f);
            }

            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/amaliatMovafagh.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
    } 
    else {
        clearChangePass();
        clear_reg_Menu();
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    clearChangePass();
    clear_reg_Menu();
}

bool define_meal(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 8; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i < 8; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94))
                                adminStat[1] = 1;
                            else if (mouse_in_grid(mouse, 280, 119, 719, 188))
                                adminStat[2] = 1;
                            else if (mouse_in_grid(mouse, 280, 213, 719, 282))
                                adminStat[3] = 1;
                            else if (mouse_in_grid(mouse, 280, 307, 719, 376))
                                adminStat[4] = 1;
                            else if (mouse_in_grid(mouse, 165, 275, 186, 296))
                                adminStat[8] ^= 1;
                            else if (mouse_in_grid(mouse, 50, 321, 184, 378))
                                chng = 1;
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(self_id);
                                if (sz) {
                                    self_id[sz - 1] = '|';
                                    self_id[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(food_id);
                                if (sz) {
                                    food_id[sz - 1] = '|';
                                    food_id[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(date);
                                if (sz) {
                                    date[sz - 1] = '|';
                                    date[sz] = ' ';
                                }
                            }
                            else if (adminStat[4]) {
                                int sz = strsz(cnt);
                                if (sz) {
                                    cnt[sz - 1] = '|';
                                    cnt[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(self_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            self_id[sz + i] = event.text.text[i];
                        self_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(food_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            food_id[sz + i] = event.text.text[i];
                        food_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(date);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            date[sz + i] = event.text.text[i];
                        date[sz + sz1] = '|'; 
                    }
                    else if (adminStat[4]) {
                        int sz = strsz(cnt);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            cnt[sz + i] = event.text.text[i];
                        cnt[sz + sz1] = '|';
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            defineMeal(renderer, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_id1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(self_id);
            self_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            self_id[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/self_id2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/food_id1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(food_id);
            food_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, food_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            food_id[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineFood/food_id2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, food_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/tarikh1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(date);
            date[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            date[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/tarikh2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect3 = {280, 307, 439, 69};
        if (adminStat[4] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/cnt1.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(cnt);
            cnt[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, cnt, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            cnt[sz] = '|';
            SDL_Rect startRect2 = {285, 307, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/cnt2.png");
            ShowImage(surface, renderer, &Rect3);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, cnt, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 307, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        //ezafat
        SDL_Rect startRec = {50, 321, 134, 57};
        if (mouse_in_grid(mouse, 50, 321, 184, 378)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/ozviat1.png");
            ShowImage(surface, renderer, &startRec);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/ozviat2.png");
            ShowImage(surface, renderer, &startRec);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {165, 275, 21, 21};
        if (adminStat[8]) {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/tik2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/menuReg/tik1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec3 = {5, 265, 150, 40};
        {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/personel.png");
            ShowImage(surface, renderer, &startRec3);
            SDL_FreeSurface(surface);
        }
        
        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/approve/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

bool Is_digit(char c) {
    return c >= '0' && c <= '9';
}

void charging(SDL_Renderer *renderer, bool testcase) {
    if (strsz(nam) == 0)
        return;
    if (strsz(newpass) == 0)
        return;
    if (strsz(money) == 0)
        return;

    nam[strsz(nam)] = '\0';
    newpass[strsz(newpass)] = '\0';
    money[strsz(money)] = '\0';

    int inc;
    sscanf(money, "%d", &inc);

    bool cartok = 1;
    int cnt1 = 0;
    int cntdash = 0;
    for (int i = 0; i < strlen(nam); i++) {
        if (nam[i] == '-') {
            if (cnt1 != 4)
                cartok = 0;
            cnt1 = 0;
            cntdash++;
        }
        else if (Is_digit(nam[i]))
            cnt1++;
        else
            cartok = 0;
        
    }
    

    if (cnt1 != 4 || cntdash != 3)
        cartok = 0;

    if (cartok) {
        logedIn->money_balance += inc;
        update_user(logedIn->id, logedIn);
        
        char stm[50];
        sprintf(stm, "students/%s/money.txt", logedIn->user_id);
        FILE *f = fopen(stm, "a");
        fprintf(f, "%.4d-%.2d-%.2d // charging\n+%d\n", time.year, time.month, time.day, inc);
        fclose(f);

        ansans = 1;
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/defineSelf/amaliatMovafagh.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    } 
    else {
        clearChangePass();
        clear_reg_Menu();
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    clearChangePass();
    clear_reg_Menu();
}

bool inccharge(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94)) {
                                adminStat[1] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(nam);
                                if (sz) {
                                    nam[sz - 1] = '|';
                                    nam[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(newpass);
                                if (sz) {
                                    newpass[sz - 1] = '|';
                                    newpass[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(money);
                                if (sz) {
                                    money[sz - 1] = '|';
                                    money[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(nam);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            nam[sz + i] = event.text.text[i];
                        nam[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(newpass);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            newpass[sz + i] = event.text.text[i];
                        newpass[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(money);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            money[sz + i] = event.text.text[i];
                        money[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            charging(renderer, 0);
            clear_reg_Menu();
            clearChangePass();
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/cart1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(nam);
            nam[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, nam, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            nam[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/cart2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, nam, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/pass1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(newpass);
            newpass[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            newpass[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/pass2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, newpass, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/sharj1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(money);
            money[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, money, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            money[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/inccharge/sharj2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, money, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void appReserv(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse, bool ruzforosh) {
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
            }
        }

        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            char stm[50];
            if (strcmp(selflunch, "lunch") == 0)
                sprintf(stm, "selfs/%s/%s/lunch/meal.txt", self_id, date);
            else
                sprintf(stm, "selfs/%s/%s/dinner/meal.txt", self_id, date);
            
            FILE *f = fopen(stm, "r");
            char tmp[50];
            char first[50];
            int cnt1, cost, ted, tahvil;
            fscanf(f, "%s %d %d %d", first, &cnt1, &cost, &ted, &tahvil);
            fclose(f);

            if (ruzforosh)
                cost *= 2;

            

            if (cost > logedIn->money_balance) {
                SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/taidNashodan.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
            else {
                logedIn->money_balance -= cost;
                update_user(logedIn->id, logedIn);
                sprintf(tmp, "students/%s/money.txt", logedIn->user_id);

                FILE *file = fopen(tmp, "a");
                fprintf(file, "%.4d-%.2d-%.2d // food reserved\n-%d\n", time.year, time.month, time.day, cost);
                fclose(file);

                cnt1--;
                ted++;

                f = fopen(stm, "w");
                fprintf(f, "%s %d %d %d %d\n", first, cnt1, cost, ted, tahvil);
                fclose(f);
                
                if (strcmp(selflunch, "lunch") == 0)
                    sprintf(stm, "students/%s/lunch.txt", logedIn->user_id);
                else
                    sprintf(stm, "students/%s/dinner.txt", logedIn->user_id);

                f = fopen(stm, "a");
                fprintf(f, "%s\n", date);
                fclose(f);

                if (strcmp(selflunch, "lunch") == 0)
                    sprintf(stm, "students/%s/lunch", logedIn->user_id);
                else
                    sprintf(stm, "students/%s/dinner", logedIn->user_id);
                
                mkdir(stm);

                if (strcmp(selflunch, "lunch") == 0)
                    sprintf(stm, "students/%s/lunch/%s", logedIn->user_id, date);
                else
                    sprintf(stm, "students/%s/dinner/%s", logedIn->user_id, date);
                
                mkdir(stm);

                if (strcmp(selflunch, "lunch") == 0)
                    sprintf(stm, "students/%s/lunch/%s/self.txt", logedIn->user_id, date);
                else
                    sprintf(stm, "students/%s/dinner/%s/self.txt", logedIn->user_id, date);

                f = fopen(stm, "a");
                fprintf(f, "%s\n", self_id);
                fclose(f);

                SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/amaliatMovafagh.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);

        SDL_Rect Rect1 = {280, 119, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/foodname1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, foodname, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/foodcost1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, foodcost, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
}

void Reserved(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse, bool testcase, bool ruzfrosh) {
    if (strsz(self_id) == 0)
        return;
    if (strsz(selflunch) == 0)
        return;
    if (strsz(date) == 0)
        return;

    self_id[strsz(self_id)] = '\0';
    selflunch[strsz(selflunch)] = '\0';
    date[strsz(date)] = '\0';
    
    self *new_self = get_self(self_id);
    int slunch, elunch, sdinner, edinner;
    sscanf(new_self->lunch_time, "%d-%d", &slunch, &elunch);
    sscanf(new_self->dinner_time, "%d-%d", &sdinner, &edinner);
    
    printf("%d -> %d\n%d -> %d\n", slunch, elunch, sdinner, edinner);

    if (new_self == NULL) {
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        if ((strcmp(logedIn->gender, "male") == 0 && new_self->girlish == 1) || (strcmp(logedIn->gender, "male") && new_self->girlish == 0)) {
            free(new_self);
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan1.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            free(new_self);
            bool ok = 0;
            if (strcmp(selflunch, "lunch") == 0) {
                char stm[50];
                sprintf(stm, "selfs/%s/lunch.txt", self_id);

                FILE *f = fopen(stm, "r");
                char tarikh[50];
                while (fscanf(f, "%s", tarikh) != EOF) {
                    // printf("lunch = %s\n", tarikh);
                    if (strcmp(tarikh, date) == 0)
                        ok = 1;
                }
                fclose(f);
            }
            else if (strcmp(selflunch, "dinner") == 0) {
                char stm[50];
                sprintf(stm, "selfs/%s/dinner.txt", self_id);

                FILE *f = fopen(stm, "r");
                char tarikh[50];
                while (fscanf(f, "%s", tarikh) != EOF) {
                    // printf("dinner = %s\n", tarikh);
                    if (strcmp(tarikh, date) == 0)
                        ok = 1;
                }
                fclose(f);
            }

            if (!ok) {
                if (testcase)
                    return;
                
                SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
            else {
                int cmp1 = comp(time.year, time.month, time.day);
                int y, m, d;
                sscanf(date, "%d-%d-%d", &y, &m, &d);
                int cmp2 = comp(y, m, d);

                if ((cmp2 - cmp1 > 2 && !ruzfrosh) || (ruzfrosh && (strcmp(selflunch, "lunch") == 0) && comper(slunch) <= comper(time.hr) && comper(time.hr) <= comper(elunch) - 30) || (ruzfrosh && (strcmp(selflunch, "dinner") == 0) && comper(sdinner) <= comper(time.hr) && comper(time.hr) <= comper(edinner) - 30)) {
                    char stm[50];
                    if (strcmp(selflunch, "lunch") == 0)
                        sprintf(stm, "selfs/%s/%s/lunch/meal.txt", self_id, date);
                    else
                        sprintf(stm, "selfs/%s/%s/dinner/meal.txt", self_id, date);

                    FILE *f = fopen(stm, "r");
                    int cnt1 = 0;
                    int ted;
                    fscanf(f, "%s %d %s %d", foodname, &cnt1, foodcost, &ted);
                    printf("foodname = %s\nfoodcost = %s\n", foodname, foodcost);
                    for (int i = strlen(foodname); i < 50; i++)
                        foodname[i] = ' ';
                    for (int i = strlen(foodcost); i < 50; i++)
                        foodcost[i] = ' ';

                    foodname[49] = '\0';
                    foodname[49] = '\0';
                    fclose(f);
                    if (cnt1 > 0) {
                        if (testcase) {
                            return;
                        }
                        appReserv(renderer, window, mouse, ruzfrosh);
                    }
                    else {
                        SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/notfound1.png");
                        SDL_Rect Rect = {0, 0, 1000, 700};
                        ShowImage(surface, renderer, &Rect);
                        SDL_FreeSurface(surface);
                        SDL_RenderPresent(renderer);

                        bool quit = 0;
                        while (!quit) {
                            SDL_Event event;
                            while (SDL_PollEvent(&event)) {
                                switch(event.type) {
                                    case SDL_KEYDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_QUIT: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                }
                else {
                    SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/notfound.png");
                    SDL_Rect Rect = {0, 0, 1000, 700};
                    ShowImage(surface, renderer, &Rect);
                    SDL_FreeSurface(surface);
                    SDL_RenderPresent(renderer);

                    bool quit = 0;
                    while (!quit) {
                        SDL_Event event;
                        while (SDL_PollEvent(&event)) {
                            switch(event.type) {
                                case SDL_KEYDOWN: {
                                    quit = 1;
                                    break;
                                }
                                case SDL_QUIT: {
                                    quit = 1;
                                    break;
                                }
                                case SDL_MOUSEBUTTONDOWN: {
                                    quit = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    clearChangePass();
    clear_reg_Menu();
}

bool reserv(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94)) {
                                adminStat[1] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(self_id);
                                if (sz) {
                                    self_id[sz - 1] = '|';
                                    self_id[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(date);
                                if (sz) {
                                    date[sz - 1] = '|';
                                    date[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(selflunch);
                                if (sz) {
                                    selflunch[sz - 1] = '|';
                                    selflunch[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(self_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            self_id[sz + i] = event.text.text[i];
                        self_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(date);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            date[sz + i] = event.text.text[i];
                        date[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(selflunch);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selflunch[sz + i] = event.text.text[i];
                        selflunch[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            Reserved(renderer, window, mouse, 0, 0);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(self_id);
            self_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            self_id[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(date);
            date[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            date[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selflunch);
            selflunch[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selflunch[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void testCaseReserv(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse, bool testcase, bool ruzfrosh) {
    if (strsz(self_id) == 0)
        return;
    if (strsz(selflunch) == 0)
        return;
    if (strsz(date) == 0)
        return;

    self_id[strsz(self_id)] = '\0';
    selflunch[strsz(selflunch)] = '\0';
    date[strsz(date)] = '\0';
    
    self *new_self = get_self(self_id);
    int slunch, elunch, sdinner, edinner;
    if (new_self != NULL) {
        sscanf(new_self->lunch_time, "%d-%d", &slunch, &elunch);
        sscanf(new_self->dinner_time, "%d-%d", &sdinner, &edinner);
    }
    if (new_self == NULL) {

        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        if ((strcmp(logedIn->gender, "male") == 0 && new_self->girlish == 1) || (strcmp(logedIn->gender, "male") && new_self->girlish == 0)) {
            if (testcase)
                return;
            free(new_self);
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan1.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            free(new_self);
            bool ok = 0;
            if (strcmp(selflunch, "lunch") == 0) {
                char stm[50];
                sprintf(stm, "selfs/%s/lunch.txt", self_id);

                FILE *f = fopen(stm, "r");
                char tarikh[50];
                while (fscanf(f, "%s", tarikh) != EOF) {
                    // printf("lunch = %s\n", tarikh);
                    if (strcmp(tarikh, date) == 0)
                        ok = 1;
                }
                fclose(f);
            }
            else if (strcmp(selflunch, "dinner") == 0) {
                char stm[50];
                sprintf(stm, "selfs/%s/dinner.txt", self_id);

                FILE *f = fopen(stm, "r");
                char tarikh[50];
                while (fscanf(f, "%s", tarikh) != EOF) {
                    // printf("dinner = %s\n", tarikh);
                    if (strcmp(tarikh, date) == 0)
                        ok = 1;
                }
                fclose(f);
            }

            if (!ok) {
                if (testcase)
                    return;
                
                SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
            else {
                int cmp1 = comp(time.year, time.month, time.day);
                int y, m, d;
                sscanf(date, "%d-%d-%d", &y, &m, &d);
                int cmp2 = comp(y, m, d);

                if ((cmp2 - cmp1 > 2 && !ruzfrosh) || (ruzfrosh && (strcmp(selflunch, "lunch") == 0) && comper(slunch) <= comper(time.hr) && comper(time.hr) <= comper(elunch) - 30) || (ruzfrosh && (strcmp(selflunch, "dinner") == 0) && comper(sdinner) <= comper(time.hr) && comper(time.hr) <= comper(edinner) - 30)) {
                    char stm[50];
                    if (strcmp(selflunch, "lunch") == 0)
                        sprintf(stm, "selfs/%s/%s/lunch/meal.txt", self_id, date);
                    else
                        sprintf(stm, "selfs/%s/%s/dinner/meal.txt", self_id, date);

                    FILE *f = fopen(stm, "r");
                    int cnt1 = 0;
                    int ted;
                    fscanf(f, "%s %d %s %d", foodname, &cnt1, foodcost, &ted);
                    printf("foodname = %s\nfoodcost = %s\n", foodname, foodcost);
                    for (int i = strlen(foodname); i < 50; i++)
                        foodname[i] = ' ';
                    for (int i = strlen(foodcost); i < 50; i++)
                        foodcost[i] = ' ';

                    foodname[49] = '\0';
                    foodname[49] = '\0';
                    fclose(f);
                    if (cnt1 > 0) {
                        char stm[50];
                        if (strcmp(selflunch, "lunch") == 0)
                            sprintf(stm, "selfs/%s/%s/lunch/meal.txt", self_id, date);
                        else
                            sprintf(stm, "selfs/%s/%s/dinner/meal.txt", self_id, date);
                        
                        FILE *f = fopen(stm, "r");
                        char tmp[50];
                        char first[50];
                        int cnt1, cost, ted, tahvil;
                        fscanf(f, "%s %d %d %d", first, &cnt1, &cost, &ted, &tahvil);
                        fclose(f);

                        if (ruzfrosh)
                            cost *= 2;

                        if (cost > logedIn->money_balance) {
                            if (testcase)
                                return;
                            SDL_Surface *surface = IMG_Load("pictures/adminMenu/charge/taidNashodan.png");
                            SDL_Rect Rect = {0, 0, 1000, 700};
                            ShowImage(surface, renderer, &Rect);
                            SDL_FreeSurface(surface);
                            SDL_RenderPresent(renderer);

                            bool quit = 0;
                            while (!quit) {
                                SDL_Event event;
                                while (SDL_PollEvent(&event)) {
                                    switch(event.type) {
                                        case SDL_KEYDOWN: {
                                            quit = 1;
                                            break;
                                        }
                                        case SDL_QUIT: {
                                            quit = 1;
                                            break;
                                        }
                                        case SDL_MOUSEBUTTONDOWN: {
                                            quit = 1;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            logedIn->money_balance -= cost;
                            update_user(logedIn->id, logedIn);
                            sprintf(tmp, "students/%s/money.txt", logedIn->user_id);

                            FILE *file = fopen(tmp, "a");
                            fprintf(file, "%.4d-%.2d-%.2d // food reserved\n-%d\n", time.year, time.month, time.day, cost);
                            fclose(file);

                            cnt1--;
                            ted++;

                            f = fopen(stm, "w");
                            fprintf(f, "%s %d %d %d %d\n", first, cnt1, cost, ted, tahvil);
                            fclose(f);
                            ansans = 1;
                            if (strcmp(selflunch, "lunch") == 0)
                                sprintf(stm, "students/%s/lunch.txt", logedIn->user_id);
                            else
                                sprintf(stm, "students/%s/dinner.txt", logedIn->user_id);

                            f = fopen(stm, "a");
                            fprintf(f, "%s\n", date);
                            fclose(f);

                            if (strcmp(selflunch, "lunch") == 0)
                                sprintf(stm, "students/%s/lunch", logedIn->user_id);
                            else
                                sprintf(stm, "students/%s/dinner", logedIn->user_id);
                            
                            mkdir(stm);

                            if (strcmp(selflunch, "lunch") == 0)
                                sprintf(stm, "students/%s/lunch/%s", logedIn->user_id, date);
                            else
                                sprintf(stm, "students/%s/dinner/%s", logedIn->user_id, date);
                            
                            mkdir(stm);

                            if (strcmp(selflunch, "lunch") == 0)
                                sprintf(stm, "students/%s/lunch/%s/self.txt", logedIn->user_id, date);
                            else
                                sprintf(stm, "students/%s/dinner/%s/self.txt", logedIn->user_id, date);

                            f = fopen(stm, "a");
                            fprintf(f, "%s\n", self_id);
                            fclose(f);
                            if (testcase)
                                return;
                            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/amaliatMovafagh.png");
                            SDL_Rect Rect = {0, 0, 1000, 700};
                            ShowImage(surface, renderer, &Rect);
                            SDL_FreeSurface(surface);
                            SDL_RenderPresent(renderer);

                            bool quit = 0;
                            while (!quit) {
                                SDL_Event event;
                                while (SDL_PollEvent(&event)) {
                                    switch(event.type) {
                                        case SDL_KEYDOWN: {
                                            quit = 1;
                                            break;
                                        }
                                        case SDL_QUIT: {
                                            quit = 1;
                                            break;
                                        }
                                        case SDL_MOUSEBUTTONDOWN: {
                                            quit = 1;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        if (testcase)
                            return;
                        SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/notfound1.png");
                        SDL_Rect Rect = {0, 0, 1000, 700};
                        ShowImage(surface, renderer, &Rect);
                        SDL_FreeSurface(surface);
                        SDL_RenderPresent(renderer);

                        bool quit = 0;
                        while (!quit) {
                            SDL_Event event;
                            while (SDL_PollEvent(&event)) {
                                switch(event.type) {
                                    case SDL_KEYDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_QUIT: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                }
                else {
                    if (testcase)
                        return;
                    SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/notfound.png");
                    SDL_Rect Rect = {0, 0, 1000, 700};
                    ShowImage(surface, renderer, &Rect);
                    SDL_FreeSurface(surface);
                    SDL_RenderPresent(renderer);

                    bool quit = 0;
                    while (!quit) {
                        SDL_Event event;
                        while (SDL_PollEvent(&event)) {
                            switch(event.type) {
                                case SDL_KEYDOWN: {
                                    quit = 1;
                                    break;
                                }
                                case SDL_QUIT: {
                                    quit = 1;
                                    break;
                                }
                                case SDL_MOUSEBUTTONDOWN: {
                                    quit = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    clearChangePass();
    clear_reg_Menu();
}

bool daily_reserv(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[2]) {
                                int sz = strsz(self_id);
                                if (sz) {
                                    self_id[sz - 1] = '|';
                                    self_id[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(selflunch);
                                if (sz) {
                                    selflunch[sz - 1] = '|';
                                    selflunch[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[2]) {
                        int sz = strsz(self_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            self_id[sz + i] = event.text.text[i];
                        self_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(selflunch);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selflunch[sz + i] = event.text.text[i];
                        selflunch[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            sprintf(date, "%d-%d-%d|", time.year, time.month, time.day);
            Reserved(renderer, window, mouse, 0, 1);
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(self_id);
            self_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            self_id[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selflunch);
            selflunch[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selflunch[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void takeFood(SDL_Renderer *renderer, bool testcase) {
    if (strsz(self_id) == 0)
        return;
    if (strsz(selflunch) == 0)
        return;
    if (strsz(date) == 0)
        return;

    self_id[strsz(self_id)] = '\0';
    selflunch[strsz(selflunch)] = '\0';
    date[strsz(date)] = '\0';

    self *new_self = get_self(self_id);
    int slunch, elunch, sdinner, edinner;
    if (new_self != NULL) {
        sscanf(new_self->lunch_time, "%d-%d", &slunch, &elunch);
        sscanf(new_self->dinner_time, "%d-%d", &sdinner, &edinner);
    }

    if (new_self == NULL) {
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        char stm[50];
        sprintf(stm, "students/%s/%s.txt", logedIn->user_id, selflunch);

        FILE *f = fopen(stm, "r");
        char tmp[50];
        bool ok = 0;
        while (fscanf(f, "%s", tmp) != EOF) {
            if (strcmp(tmp, date) == 0)
                ok = 1;
        }
        fclose(f);

        if (!ok) {
            
            if (testcase) {
                return;
            }
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan2.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {

            char stm[50];
            sprintf(stm, "students/%s/%s/%s/self.txt", logedIn->user_id, selflunch, date);

            f = fopen(stm, "r");
            char SELF[50];
            fscanf(f, "%s", SELF);
            fclose(f);

            if (strcmp(SELF, self_id) == 0) {
                

                int y, m, d;
                sscanf(date, "%d-%d-%d", &y, &m, &d);
                if (comp(y, m, d) != comp(time.year, time.month, time.day)) {
                    if (testcase) {
                        return;
                    }

                    SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan4.png");
                    SDL_Rect Rect = {0, 0, 1000, 700};
                    ShowImage(surface, renderer, &Rect);
                    SDL_FreeSurface(surface);
                    SDL_RenderPresent(renderer);

                    bool quit = 0;
                    while (!quit) {
                        SDL_Event event;
                        while (SDL_PollEvent(&event)) {
                            switch(event.type) {
                                case SDL_KEYDOWN: {
                                    quit = 1;
                                    break;
                                }
                                case SDL_QUIT: {
                                    quit = 1;
                                    break;
                                }
                                case SDL_MOUSEBUTTONDOWN: {
                                    quit = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                else {
                    bool ok = 0;
                    if (strcmp(selflunch, "lunch") == 0) {
                        if (comper(slunch) <= comper(time.hr) && comper(time.hr) <= comper(elunch))
                            ok = 1;
                    }
                    else {
                        if (comper(sdinner) <= comper(time.hr) && comper(time.hr) <= comper(edinner))
                            ok = 1;
                    }

                    if (ok) {
                        char stm[50];
                        sprintf(stm, "students/%s/%s.txt", logedIn->user_id, selflunch);
                        FILE *file = fopen(stm, "r");
                        FILE *chert = fopen("chert.txt", "w");
                        char s[50];
                        while (fscanf(file, "%s", s) != EOF) {
                            if (strcmp(s, date))
                                fprintf(chert, "%s\n", s);
                        } 

                        fclose(file);
                        fclose(chert);

                        chert = fopen("chert.txt", "r");
                        file = fopen(stm, "w");

                        char c = fgetc(chert);
                        while (c != EOF) {
                            fputc(c, file);
                            c = fgetc(chert);
                        }

                        fclose(file);
                        fclose(chert);

                        sprintf(stm, "selfs/%s/%s/%s/meal.txt", self_id, date, selflunch);
                        chert = fopen(stm, "r");
                        char tmpp[50];
                        int xx[4];
                        fscanf(chert, "%s %d %d %d %d", tmpp, &xx[0], &xx[1], &xx[2], &xx[3]);
                        xx[3]++;
                        fclose(chert);

                        chert = fopen(stm, "w");
                        fprintf(chert, "%s %d %d %d %d", tmpp, xx[0], xx[1], xx[2], xx[3]);
                        fclose(chert);

                        sprintf(stm, "students/%s/take.txt", logedIn->user_id);
                        file = fopen(stm, "a");

                        self *newself = get_self(self_id);
            
                        fprintf(file, "(%s) hr:%.2d:%.2d\nfrom self %s take meal %s\n", date, time.hr / 100, time.hr % 100, newself->name, tmpp);
                        fclose(file);
                        free(newself);
                        ansans = 1;
                        printf("5\n");

                        if (testcase)
                            return;

                        SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/amaliatMovafagh.png");
                        SDL_Rect Rect = {0, 0, 1000, 700};
                        ShowImage(surface, renderer, &Rect);
                        SDL_FreeSurface(surface);
                        SDL_RenderPresent(renderer);

                        bool quit = 0;
                        while (!quit) {
                            SDL_Event event;
                            while (SDL_PollEvent(&event)) {
                                switch(event.type) {
                                    case SDL_KEYDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_QUIT: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        if (testcase)
                            return;

                        SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan4.png");
                        SDL_Rect Rect = {0, 0, 1000, 700};
                        ShowImage(surface, renderer, &Rect);
                        SDL_FreeSurface(surface);
                        SDL_RenderPresent(renderer);

                        bool quit = 0;
                        while (!quit) {
                            SDL_Event event;
                            while (SDL_PollEvent(&event)) {
                                switch(event.type) {
                                    case SDL_KEYDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_QUIT: {
                                        quit = 1;
                                        break;
                                    }
                                    case SDL_MOUSEBUTTONDOWN: {
                                        quit = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                if (testcase) {
                    return;
                }
                SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan3.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool take_food(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94)) {
                                adminStat[1] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(self_id);
                                if (sz) {
                                    self_id[sz - 1] = '|';
                                    self_id[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(date);
                                if (sz) {
                                    date[sz - 1] = '|';
                                    date[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(selflunch);
                                if (sz) {
                                    selflunch[sz - 1] = '|';
                                    selflunch[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(self_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            self_id[sz + i] = event.text.text[i];
                        self_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(date);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            date[sz + i] = event.text.text[i];
                        date[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(selflunch);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selflunch[sz + i] = event.text.text[i];
                        selflunch[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            takeFood(renderer, 0);
            clearChangePass();
            clear_reg_Menu();
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(self_id);
            self_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            self_id[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(date);
            date[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            date[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selflunch);
            selflunch[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selflunch[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void changeSelf(SDL_Renderer *renderer, bool testcase) {
   if (strsz(self_id) == 0)
        return;
    if (strsz(selflunch) == 0)
        return;
    if (strsz(date) == 0)
        return;

    self_id[strsz(self_id)] = '\0';
    selflunch[strsz(selflunch)] = '\0';
    date[strsz(date)] = '\0';

    self *new_self = get_self(self_id);
    int slunch, elunch, sdinner, edinner;
    if (new_self != NULL) {
        sscanf(new_self->lunch_time, "%d-%d", &slunch, &elunch);
        sscanf(new_self->dinner_time, "%d-%d", &sdinner, &edinner);
    }
    printf("%d -> %d\n%d -> %d\n", slunch, elunch, sdinner, edinner);

    if (new_self == NULL) {
        if (testcase)
            return;

        SDL_Surface *surface = IMG_Load("pictures/adminMenu/definemeal/notfound.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        char stm[50];
        sprintf(stm, "students/%s/%s.txt", logedIn->user_id, selflunch);

        FILE *f = fopen(stm, "r");
        char tmp[50];
        bool ok = 0;
        while (fscanf(f, "%s", tmp) != EOF) {
            if (strcmp(tmp, date) == 0)
                ok = 1;
        }
        fclose(f);

        if (!ok) {
            if (testcase) {
                return;
            }
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan2.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            char stm[50];
            sprintf(stm, "students/%s/%s/%s/self.txt", logedIn->user_id, selflunch, date);

            f = fopen(stm, "r");
            char SELF[50];
            fscanf(f, "%s", SELF);
            fclose(f);

            self *lastself = get_self(SELF);
            
            sscanf(lastself->lunch_time, "%d-%d", &slunch, &elunch);
            sscanf(lastself->dinner_time, "%d-%d", &sdinner, &edinner);

            bool ok = 1;
            if (lastself->girlish != new_self->girlish) {
                printf("jensiat yeki nis\n");
                ok = 0;
            }

            int y, m, d;
            sscanf(date, "%d-%d-%d", &y, &m, &d);
            if (comp(time.year, time.month, time.day) > comp(y, m, d)) {
                printf("zaman\n");
                ok = 0;
            }
            if (comp(time.year, time.month, time.day) == comp(y, m, d)) {
                if (strcmp("lunch", selflunch) == 0 && comper(time.hr) > comper(slunch) - 180) {
                    printf("zaman\n");
                    ok = 0;
                }
                if (strcmp("dinner", selflunch) == 0 && comper(time.hr) > comper(sdinner) - 180) {
                    printf("zaman\n");
                    ok = 0;
                }
            }
            
            if (ok) {
                f = fopen(stm, "w");
                fprintf(f, "%s", new_self->self_id);
                fclose(f);

                SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/amaliatMovafagh.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
            else {
                if (testcase) {
                    return;
                }
                SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan5.png");
                SDL_Rect Rect = {0, 0, 1000, 700};
                ShowImage(surface, renderer, &Rect);
                SDL_FreeSurface(surface);
                SDL_RenderPresent(renderer);

                bool quit = 0;
                while (!quit) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        switch(event.type) {
                            case SDL_KEYDOWN: {
                                quit = 1;
                                break;
                            }
                            case SDL_QUIT: {
                                quit = 1;
                                break;
                            }
                            case SDL_MOUSEBUTTONDOWN: {
                                quit = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool change_self(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 25, 719, 94)) {
                                adminStat[1] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[1]) {
                                int sz = strsz(self_id);
                                if (sz) {
                                    self_id[sz - 1] = '|';
                                    self_id[sz] = ' ';
                                }
                            } 
                            else if (adminStat[2]) {
                                int sz = strsz(date);
                                if (sz) {
                                    date[sz - 1] = '|';
                                    date[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(selflunch);
                                if (sz) {
                                    selflunch[sz - 1] = '|';
                                    selflunch[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[1]) {
                        int sz = strsz(self_id);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            self_id[sz + i] = event.text.text[i];
                        self_id[sz + sz1] = '|'; 
                    }
                    else if (adminStat[2]) {
                        int sz = strsz(date);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            date[sz + i] = event.text.text[i];
                        date[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(selflunch);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selflunch[sz + i] = event.text.text[i];
                        selflunch[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            changeSelf(renderer, 0);
            clear_reg_Menu();
            clearChangePass();
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};
        if (adminStat[1] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id1.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(self_id);
            self_id[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            self_id[sz] = '|';
            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/self_id2.png");
            ShowImage(surface, renderer, &Rect0);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, self_id, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 25, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(date);
            date[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            date[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selflunch);
            selflunch[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selflunch[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void cancelReserv(SDL_Renderer *renderer, bool testcase) {
    if (strsz(selflunch) == 0)
        return;
    if (strsz(date) == 0)
        return;

    selflunch[strsz(selflunch)] = '\0';
    date[strsz(date)] = '\0';

    char stm[50];
    sprintf(stm, "students/%s/%s.txt", logedIn->user_id, selflunch);

    FILE *f = fopen(stm, "r");
    char tmp[50];
    bool ok = 0;
    while (fscanf(f, "%s", tmp) != EOF) {
        if (strcmp(tmp, date) == 0)
            ok = 1;
    }
    fclose(f);

    if (!ok) {
        if (testcase) {
            return;
        }
        SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan2.png");
        SDL_Rect Rect = {0, 0, 1000, 700};
        ShowImage(surface, renderer, &Rect);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);

        bool quit = 0;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_KEYDOWN: {
                        quit = 1;
                        break;
                    }
                    case SDL_QUIT: {
                        quit = 1;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN: {
                        quit = 1;
                        break;
                    }
                }
            }
        }
    }
    else {
        char stm[50];
        sprintf(stm, "students/%s/%s/%s/self.txt", logedIn->user_id, selflunch, date);

        f = fopen(stm, "r");
        char SELF[50];
        fscanf(f, "%s", SELF);
        fclose(f);

        int slunch, elunch, sdinner, edinner;
        self *new_self = get_self(SELF);
        if (new_self != NULL) {
            sscanf(new_self->lunch_time, "%d-%d", &slunch, &elunch);
            sscanf(new_self->dinner_time, "%d-%d", &sdinner, &edinner);
        }

        int y, m, d;
        sscanf(date, "%d-%d-%d", &y, &m, &d);
        bool ok = 1;

        if (comp(time.year, time.month, time.day) > comp(y, m, d))
            ok = 0;
        if (strcmp("lunch", selflunch) == 0) {
            if (comp(time.year, time.month, time.day) == comp(y, m, d) && comper(time.hr) > comper(slunch) - 60)
                ok = 0; 
        }
        else {
            if (comp(time.year, time.month, time.day) == comp(y, m, d) && comper(time.hr) > comper(sdinner) - 60)
                ok = 0; 
        }

        if (ok) {   
            sprintf(stm, "students/%s/%s.txt", logedIn->user_id, selflunch);
            FILE *file = fopen(stm, "r");
            FILE *chert = fopen("chert.txt", "w");
            char s[50];
            while (fscanf(file, "%s", s) != EOF) {
                if (strcmp(s, date))
                    fprintf(chert, "%s\n", s);
            } 

            fclose(file);
            fclose(chert);

            chert = fopen("chert.txt", "r");
            file = fopen(stm, "w");

            char c = fgetc(chert);
            while (c != EOF) {
                fputc(c, file);
                c = fgetc(chert);
            }
            fclose(file);
            fclose(chert);

            sprintf(stm, "selfs/%s/%s/%s/meal.txt", SELF, date, selflunch);
            chert = fopen(stm, "r");
            char tmpp[50];
            int xx[4];
            fscanf(chert, "%s %d %d %d %d", tmpp, &xx[0], &xx[1], &xx[2], &xx[3]);
            xx[3]++;
            fclose(chert);

            chert = fopen(stm, "w");
            fprintf(chert, "%s %d %d %d %d", tmpp, xx[0] + 1, xx[1], xx[2] - 1, xx[3]);
            fclose(chert);

            sprintf(stm, "students/%s/money.txt", logedIn->user_id);
            f = fopen(stm, "a");
            logedIn->money_balance += (xx[1] * 90) / 100;
            update_user(logedIn->id, logedIn);
            fprintf(f, "%.4d-%.2d-%.2d // canceling order\n+%d\n", time.year, time.month, time.day, (xx[1] * 90) / 100);
            fclose(f);
            ansans = 1;
            if (testcase)
                return;

            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/amaliatMovafagh.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else {
            if (testcase) {
                return;
            }
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/taidNashodan5.png");
            SDL_Rect Rect = {0, 0, 1000, 700};
            ShowImage(surface, renderer, &Rect);
            SDL_FreeSurface(surface);
            SDL_RenderPresent(renderer);

            bool quit = 0;
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_KEYDOWN: {
                            quit = 1;
                            break;
                        }
                        case SDL_QUIT: {
                            quit = 1;
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN: {
                            quit = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

bool cancel_reserv(SDL_Renderer *renderer, SDL_Window *window, mouse_type *mouse) {
    clearChangePass();
    clear_reg_Menu();
    bool Is_done = 0;
    while (!Is_done) {
        bool br = 0;
        SDL_Event event;
        bool textinput = 0;
        for (int i = 1; i < 4; i++)
            if (adminStat[i] == 1)
                textinput = 1;
        if (textinput)
            SDL_StartTextInput();

        bool chng = 0;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_WINDOWEVENT_CLOSE: {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        Is_done = 1;
                    }
                    break;
                }
                case SDL_QUIT: {
                    Is_done = 1;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    SDL_GetMouseState(&(mouse->x), &(mouse->y));
                    // printf("(%d, %d)\n", mouse->x, mouse->y);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT: {
                            for (int i = 1; i <= 3; i++)
                                adminStat[i] = 0;

                            if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
                                br = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 119, 719, 188)) {
                                adminStat[2] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 213, 719, 282)) {
                                adminStat[3] = 1;
                            }
                            if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
                                chng = 1;
                            }
                            break;
                        }
                    }
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            if (adminStat[2]) {
                                int sz = strsz(date);
                                if (sz) {
                                    date[sz - 1] = '|';
                                    date[sz] = ' ';
                                }
                            }
                            else if (adminStat[3]) {
                                int sz = strsz(selflunch);
                                if (sz) {
                                    selflunch[sz - 1] = '|';
                                    selflunch[sz] = ' ';
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT: {
                    if (adminStat[2]) {
                        int sz = strsz(date);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            date[sz + i] = event.text.text[i];
                        date[sz + sz1] = '|'; 
                    }
                    else if (adminStat[3]) {
                        int sz = strsz(selflunch);
                        int sz1 = strlen(event.text.text);
                        for (int i = 0; i < sz1; i++)
                            selflunch[sz + i] = event.text.text[i];
                        selflunch[sz + sz1] = '|'; 
                    }
                    break;
                }
            }
        }
        if (textinput)
            SDL_StopTextInput();

        if (br)
            break;

        if (chng) {
            cancelReserv(renderer, 0);
            clear_reg_Menu();
            clearChangePass();
        }

        SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect0 = {280, 25, 439, 69};

        SDL_Rect Rect1 = {280, 119, 439, 69};
        if (adminStat[2] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh1.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(date);
            date[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            date[sz] = '|';
            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/tarikh2.png");
            ShowImage(surface, renderer, &Rect1);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, date, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 119, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect Rect2 = {280, 213, 439, 69};
        if (adminStat[3] == 0) {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham1.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            int sz = strsz(selflunch);
            selflunch[sz] = ' ';
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);
            selflunch[sz] = '|';
            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/daneshjoMenu/reserv/naharsham2.png");
            ShowImage(surface, renderer, &Rect2);
            SDL_FreeSurface(surface);

            TTF_Init();
            TTF_Font *font = TTF_OpenFont("text/Sans.ttf", 70);
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface *surface1 = TTF_RenderText_Solid(font, selflunch, textColor); 
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface1);

            SDL_Rect startRect2 = {285, 213, 320, 50};
            SDL_RenderCopy(renderer, texture, NULL, &startRect2);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface1);
            TTF_CloseFont(font);
        }

        SDL_Rect startRec1 = {10, 10, 33, 45};
        if (mouse_in_grid(mouse, 10, 10, 43, 55)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back2.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/back1.png");
            ShowImage(surface, renderer, &startRec1);
            SDL_FreeSurface(surface);
        }

        SDL_Rect startRec2 = {280, 303, 439, 44};
        if (mouse_in_grid(mouse, 280, 303, 724, 347)) {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button2.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        else {
            SDL_Surface *surface = IMG_Load("pictures/adminMenu/changepass/button1.png");
            ShowImage(surface, renderer, &startRec2);
            SDL_FreeSurface(surface);
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    for (int i = 0; i < 8; i++)
        adminStat[i] = 0;
    return Is_done;
}

void moneyReport() {
    system("cls");

    char stm[50];
    sprintf(stm, "students/%s/money.txt", logedIn->user_id);
    FILE *f = fopen(stm, "r");

    printf("money balance of user = %s with name = %s is %d\n", logedIn->user_id, logedIn->name, logedIn->money_balance);
    char c = fgetc(f);
    while (c != EOF) {
        putchar(c);
        c = fgetc(f);
    }
    return;
}

void mealReport() {
    system("cls");

    char stm[50];
    sprintf(stm, "students/%s/lunch.txt", logedIn->user_id);
    FILE *f = fopen(stm, "r");
    while (fscanf(f, "%s", date) != EOF) {
        sprintf(stm, "students/%s/lunch/%s/self.txt", logedIn->user_id, date);
        FILE *file = fopen(stm, "r");
        fscanf(file, "%s", self_id);
        fclose(file);

        sprintf(stm, "selfs/%s/%s/lunch/meal.txt", self_id, date);
        file = fopen(stm, "r");
        fscanf(file, "%s", foodname);
        fclose(file);

        self *new_self = get_self(self_id);
        printf("date:(%s)\nfor lunch from self %s reserved %s meal\n", date, new_self->name, foodname);
    }
    fclose(f);

    sprintf(stm, "students/%s/dinner.txt", logedIn->user_id);
    f = fopen(stm, "r");

    while (fscanf(f, "%s", date) != EOF) {
        sprintf(stm, "students/%s/dinner/%s/self.txt", logedIn->user_id, date);
        FILE *file = fopen(stm, "r");
        fscanf(file, "%s", self_id);
        fclose(file);

        sprintf(stm, "selfs/%s/%s/dinner/meal.txt", self_id, date);
        file = fopen(stm, "r");
        fscanf(file, "%s", foodname);
        fclose(file);

        self *new_self = get_self(self_id);
        printf("date:(%s)\nfor dinner from self %s reserved %s meal\n", date, new_self->name, foodname);
    }
    fclose(f);
}

void takenReport() {
    system("cls");

    char stm[50];
    sprintf(stm, "students/%s/take.txt", logedIn->user_id);
    FILE *f = fopen(stm, "r");

    char c = fgetc(f);
    while (c != EOF) {
        putchar(c);
        c = fgetc(f);
    }
    return;
}

int tokenizer(char *s, char *token, char result[][200]){
	int res_index = 0;
	char *index;
	while((index = strstr(s, token)) != NULL){
		int len = index - s;
		if(len > 0){
			strncpy(result[res_index], s, len);
			result[res_index][len] = '\0';
			res_index++;
		}
		s = index + strlen(token);
	}
	if(strlen(s) > 0){
		strcpy(result[res_index], s); res_index++;
	}
	return res_index;
}

void COPY(char *s, char *t) {
    for (int i = 0; i < strlen(t); i++)
        s[i] = t[i];
    s[strlen(t)] = '|';
}

int main(int argc, char *argv[]) {
    //making windows and renderer
    make_or_open_database();
    user admin = {-1, "admin", "admin", "admin", "0", "male", 0, 0, 0, 1, 1, INF, "admin"};
    insert_user(&admin);
    char userName[50], password[50];
    userName[0] = password[0] = '|';
    for (int i = 1; i < 50; i++)
        userName[i] = password[i] = ' ';
    userName[49] = password[49] = '\0';

    nam[0] = khan[0] = birth[0] = pass[0] = user_id[0] = nat_id[0] = gen[0] = '|';
    for (int i = 1; i < 50; i++)
        nam[i] = khan[i] = birth[i] = pass[i] = user_id[i] = nat_id[i] = gen[i] = ' '; 
    nam[49] = khan[49] = birth[49] = pass[49] = user_id[49] = nat_id[49] = gen[49] = '\0';
    

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    mouse_type mouse;
    
    FILE *test = fopen("testcase/testcase.txt", "r");
    FILE *f = fopen("ansTestcase.txt", "w");
    char vorodi[200];
    bool login = 0;
    int stat = 0;
    while (fscanf(test, "%s", vorodi) != EOF) {
        ansans = 0;
        char res[100][200];
        int num = tokenizer(vorodi, "#", res);
        char op[100][200];
        char input[100][200];
        int num1 = 1;
        if (num >= 3) {
            num1 = tokenizer(res[2], "|", op);
            for (int i = 0; i < num1; i++) {
                char tmp[100][200];
                int t = tokenizer(op[i], ":", tmp);
                for (int j = 0; j < 50; j++)
                    input[i][j] = tmp[1][j];
            }
        }

        if (num < 3)
            continue;
        
        if (strcmp("change-datetime", res[1]) == 0) {
            ansans = 1;
            sscanf(input[0], "%d-%d-%d", &time.year, &time.month, &time.day);
            sscanf(input[1], "%d", &time.hr);
            printf("%d %d %d %d\n", time.year, time.month, time.day, time.hr);
        }
        else {
            if (login == 0) {
                if (strcmp("login", res[1]) == 0) {
                    COPY(userName, input[0]);
                    COPY(password, input[1]);
                    login_user(renderer, userName, password, &stat, 1);
                    if (ansans == 1)
                        login = 1;
                }
                else if (strcmp("register", res[1]) == 0) {
                    COPY(nam, input[0]);
                    COPY(khan, input[1]);
                    COPY(user_id, input[2]);
                    COPY(pass, input[3]);
                    COPY(nat_id, input[4]);
                    COPY(birth, input[5]);
                    COPY(gen, input[6]);

                    if (strcmp("admin", input[7]) == 0)
                        regStat[8] = 1;
                    else
                        regStat[8] = 0;
                    
                    ansans = 2;
                    reg_user(0, renderer, 1);
                    regStat[8] = 0;
                }
                else if (strcmp("define-self", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("define-food", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("approve", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("define-meal-plan", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("change-student-pass", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("deactivate", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("remove-student", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("charge-student-account", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("reserve", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("charge-account", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("send-charge", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("cancel-reserve", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("take-food", res[1]) == 0) {
                    ansans = 2;
                }
                else if (strcmp("daily-reserve", res[1]) == 0) {
                    ansans = 2;
                }
            }
            else {
                if (strcmp("logout", res[1]) == 0) {
                    if (strcmp(logedIn->user_id, input[0]) == 0) {
                        login = 0;
                        ansans = 1;
                    }
                }
                else if (strcmp("change-pass", res[1]) == 0) {
                    if (strcmp(logedIn->user_id, input[0]) == 0) {
                        COPY(lastpass, input[1]);
                        COPY(newpass, input[2]);
                        COPY(newpass2, input[2]);

                        ChangePass(renderer, 1);
                    }
                }
                else {
                    if (logedIn->masol) {
                        if (strcmp("register", res[1]) == 0) {
                            COPY(nam, input[0]);
                            COPY(khan, input[1]);
                            COPY(user_id, input[2]);
                            COPY(pass, input[3]);
                            COPY(nat_id, input[4]);
                            COPY(birth, input[5]);
                            COPY(gen, input[6]);

                            if (strcmp("admin", input[7]) == 0)
                                regStat[8] = 1;
                            else
                                regStat[8] = 0;

                            ansans = 2;
                            reg_user(1, renderer, 1);
                        }
                        else if (strcmp("define-self", res[1]) == 0) {
                            COPY(self_id, input[0]);
                            COPY(selfname, input[1]);
                            COPY(selfadd, input[2]);
                            COPY(selfcap, input[3]);
                            if (strcmp("girlish", input[4]) == 0)
                                adminStat[8] = 1;
                            else
                                adminStat[8] = 0;
                            COPY(selflunch, input[6]);
                            COPY(selfdinner, input[7]);

                            if (strcmp("lunch", input[5]) == 0)
                                COPY(selfdinner, "-1");
                            if (strcmp("dinner", input[5]) == 0)
                                COPY(selflunch, "-1");

                            ansans = 2;
                            defineSelf(renderer, 1);
                        }
                        else if (strcmp("define-food", res[1]) == 0) {
                            COPY(food_id, input[0]);
                            COPY(foodname, input[1]);
                            if (strcmp("dessert", input[2]) == 0)
                                adminStat[8] = 1;
                            else
                                adminStat[8] = 0;
                            COPY(foodcost, input[3]);

                            ansans = 2;
                            defineFood(renderer, 1);
                        }
                        else if (strcmp("approve", res[1]) == 0) {
                            ansans = 1;
                            for (int i = 0; i < num1; i++) {
                                char tmp[50];
                                for (int j = 0; j < 50; j++)
                                    tmp[j] = input[i][j];

                                approving(tmp);
                            }
                        }
                        else if (strcmp("define-meal-plan", res[1]) == 0) {
                            COPY(self_id, input[0]);
                            COPY(date, input[1]);
                            COPY(food_id, input[3]);
                            COPY(cnt, input[4]);

                            if (strcmp("dinner", input[2]) == 0)
                                adminStat[8] = 1;
                            else
                                adminStat[8] = 0;
                            
                            ansans = 0;
                            defineMeal(renderer, 1);
                        }
                        else if (strcmp("change-student-pass", res[1]) == 0) {
                            COPY(user_id, input[0]);
                            COPY(newpass, input[1]);
                            COPY(newpass2, input[1]);

                            ChangePassDaneshjo(renderer, 1);            
                        }
                        else if (strcmp("deactivate", res[1]) == 0) {
                            COPY(user_id, input[0]);
                            
                            deactive_user(renderer, 0, 1);
                        }
                        else if (strcmp("remove-student", res[1]) == 0) {
                            COPY(user_id, input[0]);
                            
                            deactive_user(renderer, 1, 1);
                        }
                        else if (strcmp("charge-student-account", res[1]) == 0) {
                            COPY(user_id, input[0]);
                            COPY(money, input[1]);

                            ChargeStudent(renderer, 1);
                        }
                        else if (strcmp("reserve", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("charge-account", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("send-charge", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("cancel-reserve", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("take-food", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("daily-reserve", res[1]) == 0) {
                            ansans = 2;
                        }
                    }
                    else {
                        if (strcmp("register", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("define-self", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("define-food", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("approve", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("define-meal-plan", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("change-student-pass", res[1]) == 0) {
                            ansans = 2;            
                        }
                        else if (strcmp("deactivate", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("remove-student", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("charge-student-account", res[1]) == 0) {
                            ansans = 2;
                        }
                        else if (strcmp("reserve", res[1]) == 0) {
                            COPY(self_id, input[0]);
                            COPY(date, input[1]);
                            COPY(selflunch, input[2]);

                            testCaseReserv(renderer, window, &mouse, 1, 0);
                        }
                        else if (strcmp("charge-account", res[1]) == 0) {
                            COPY(money, input[0]);
                            COPY(nam, input[1]);
                            COPY(newpass, input[2]);

                            charging(renderer, 1);
                        }
                        else if (strcmp("send-charge", res[1]) == 0) {
                            COPY(user_id, input[0]);
                            COPY(money, input[1]);

                            user *new_user = get_user(input[0]); 
                            if (new_user != NULL) {
                                if (strcmpi(new_user->name, input[2]) == 0)
                                    ChargeStudent(renderer, 1);
                            }
                            free(new_user);
                        }
                        else if (strcmp("cancel-reserve", res[1]) == 0) {
                            COPY(date, input[0]);
                            COPY(selflunch, input[1]);

                            cancelReserv(renderer, 1);
                        }
                        else if (strcmp("daily-reserve", res[1]) == 0) {
                            COPY(date, input[0]);
                            COPY(selflunch, input[1]);

                            testCaseReserv(renderer, window, &mouse, 1, 1);
                        }
                        else if (strcmp("take-food", res[1]) == 0) {
                            COPY(self_id, input[0]);
                            COPY(date, input[1]);
                            COPY(selflunch, input[2]);

                            takeFood(renderer, 1);
                        }
                    }
                }
            }

            userName[0] = password[0] = '|';
            for (int i = 1; i < 50; i++)
                userName[i] = password[i] = ' ';
            userName[49] = password[49] = '\0';
            clear_reg_Menu();
            clearChangePass();
        }

        fprintf(f, "%s#%s\n", res[0], output[ansans]);
    }

    fclose(f);
    fclose(test);

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SAMAD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool Is_done = 0;
    int menuStat = 0;
    int lastmenu = 0;
    
    clear_reg_Menu();
    clearChangePass();
    while (!Is_done) {
        //check for events
        if (menuStat == 0) {
            lastmenu = 0;
            Is_done = login_menu_event(window, &mouse, renderer, userName, password, &stat);
            if (stat == 10) {
                stat = 0;
                menuStat = 2;
                clear_login_Menu(userName, password);
                continue;
            }
            if (stat == 11) {
                stat = 0;
                login_user(renderer, userName, password, &stat, 0);

                if (stat == 1) {
                    stat = 0;
                    menuStat = 3;
                    continue;
                }
                else if (stat == 2) {
                    stat = 0;
                    menuStat = 1;
                    continue;
                }
            }
            Render_login_menu(renderer, &mouse, userName, password, &stat);
        }
        else if (menuStat == 1) {
            lastmenu = 1;
            Is_done = daneshjo_menu_event(window, &mouse, renderer);
            if (daneshjoStat[0] == -1) {
                daneshjoStat[0] = 0;
                menuStat = 0;
                continue;
            }
            if (daneshjoStat[0] == -2) {
                daneshjoStat[0] = 0;
                Is_done = changepass(renderer, window, &mouse);
                clearChangePass();
            }
            if (daneshjoStat[0] == -3) {
                daneshjoStat[0] = 0;
                adminStat[0] = 0;
                Is_done = chargeStudentAcc(renderer, window, &mouse);
                clearChangePass();
            }
            if (daneshjoStat[0] == -4) {
                daneshjoStat[0] = 0;
                Is_done = inccharge(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (daneshjoStat[0] == -5) {
                daneshjoStat[0] = 0;
                Is_done = reserv(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (daneshjoStat[0] == -6) {
                daneshjoStat[0] = 0;
                Is_done = daily_reserv(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (daneshjoStat[0] == -7) {
                daneshjoStat[0] = 0;
                Is_done = take_food(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (daneshjoStat[0] == -8) {
                daneshjoStat[0] = 0;
                Is_done = change_self(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (daneshjoStat[0] == -9) {
                daneshjoStat[0] = 0;
                Is_done = cancel_reserv(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (daneshjoStat[0] == -10) {
                daneshjoStat[0] = 0;
                moneyReport();
            }
            if (daneshjoStat[0] == -11) {
                daneshjoStat[0] = 0;
                takenReport();
            }
            if (daneshjoStat[0] == -12) {
                daneshjoStat[0] = 0;
                mealReport();
            }
            Render_daneshjo_menu(renderer, &mouse);
        }
        else if (menuStat == 2) {
            Is_done = reg_menu_event(window, &mouse, renderer);
            if (regStat[7] == -1) {
                regStat[7] = 0;
                menuStat = lastmenu;
                stat = 0;
                clear_reg_Menu();
                continue;
            }
            if (regStat[7] == -2) {
                regStat[7] = 0;
                reg_user(lastmenu == 3, renderer, 0);
                clear_reg_Menu();
                continue;
            }
            Render_reg_menu(renderer, &mouse);
        }
        else if (menuStat == 3) {
            lastmenu = 3;
            Is_done = admin_menu_event(window, &mouse, renderer);
            if (adminStat[0] == -1) {
                adminStat[0] = 0;
                menuStat = 0;
                continue;
            }
            if (adminStat[0] == -2) {
                adminStat[0] = 0;
                menuStat = 2;
                continue;
            }
            if (adminStat[0] == -3) {
                adminStat[0] = 0;
                Is_done = changepass(renderer, window, &mouse);
                clearChangePass();
                continue;
            }
            if (adminStat[0] == -4) {
                adminStat[0] = 0;
                Is_done = changepassdaneshjo(renderer, window, &mouse);
                clearChangePass();
            }
            if (adminStat[0] == -5) {
                adminStat[0] = 0;
                Is_done = deactiveUser(renderer, window, &mouse);
                clearChangePass();
            }
            if (adminStat[0] == -6) {
                adminStat[0] = 0;
                Is_done = chargeStudentAcc(renderer, window, &mouse);
                clearChangePass();
            }
            if (adminStat[0] == -7) {
                adminStat[0] = 0;
                Is_done = approve_user(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (adminStat[0] == -8) {
                adminStat[0] = 0;
                Is_done = define_self(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (adminStat[0] == -9) {
                adminStat[0] = 0;
                Is_done = define_food(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            if (adminStat[0] == -10) {
                adminStat[0] = 0;
                Is_done = define_meal(renderer, window, &mouse);
                clearChangePass();
                clear_reg_Menu();
            }
            Render_admin_Menu(renderer, &mouse);
        }

        SDL_Delay(100);
    }

    //destroying
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    // insert_user(&mamad);
    // insert_user(&hossein);
    // user *new_user = get_user("40131062");

    close_database();
    return 0;
}