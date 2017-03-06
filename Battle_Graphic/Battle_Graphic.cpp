// Battle_Graphic.cpp : Defines the entry point for the application.
//

#include <stdlib.h>
#include <stdio.h>
#include "stdafx.h"
#include "SDL.h"
#include "AgentReader.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include <windows.h>
#include <string.h>
#include <Commdlg.h>
#include "SDL_ttf.h"
#define MAX_LOADSTRING 100

const int BATTLE_HEIGHT = 600;
const int BATTLE_WIDTH = 475;

const int SCREEN_HEIGHT = 670;
const int SCREEN_WIDTH = 810;
const int SCREEN_BPP = 32;
int textW = 200;
int textH = 30;

SDL_Window *gWindow = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *battlefield = NULL;
SDL_Surface * text = NULL;
SDL_Surface *readMe = NULL;

SDL_Texture *field = NULL;
SDL_Texture *readMeTexture = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect rect{ 0, 0, 9,8};
SDL_Rect battle{ 30, 30, BATTLE_WIDTH, BATTLE_HEIGHT };
SDL_Rect readMeRect{ 510, 30, 300,285};

bool init();
void close();
void render_messageSurface();
void renderReadMe();
void clearScreen();
void fileReader(char filename[], TTF_Font *font);
void filepicker(TTF_Font *font);

void renderContourMap();
int render_shooting_symbol(TTF_Font *, int index, int x, int y);
void draw_one_ellipse(int x1, int y1,int st);
void draw_one_rec(int x1, int y1,int st);
//void draw_and_move_rec_after_3000();

int main(int argc, char* args[]) {

	if (!init()) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Error", "Can Not Successfully Init", NULL);
	}
	else {

		TTF_Init();
		TTF_Font* font = TTF_OpenFont("arial.ttf", 12);
		renderer= SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		battlefield = SDL_LoadBMP("battlefield.bmp");
		readMe = SDL_LoadBMP("tuli.bmp");
		clearScreen();

		renderReadMe();
		filepicker(font);

		TTF_CloseFont(font);
		close();
	}

	return 0;

}

bool init() 
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Error", "Can Not Successfully Init", NULL);
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("Battle of Ankra",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Error", "Can Not Successfully Create Window", NULL);
			success = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(gWindow);
		
		}
	}
	return success;

}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//free surface
	SDL_FreeSurface(screenSurface);
	SDL_FreeSurface(text);
	SDL_FreeSurface(battlefield);
	SDL_FreeSurface(readMe);

	//destroy texture
	SDL_DestroyTexture(readMeTexture);
	SDL_DestroyTexture(field);

	TTF_Quit();
	SDL_Quit();

}

void render_messageSurface()
{
	SDL_Surface * text = NULL;
	TTF_Font* font = TTF_OpenFont("arial.ttf", 14);
	SDL_Color foregroundColor = { 0, 0, 0 };
	SDL_Color backgroundColor = { 255, 255, 255 };

	if (font == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Render Error", "OpenFont Failed", NULL);
		return;
	}

	text = TTF_RenderText_Solid(font, "finally show the world", foregroundColor);
	if (text != NULL) {

		SDL_Rect textLocation = { 510, 330, textW, textH };

		field = SDL_CreateTextureFromSurface(renderer, text);
		SDL_QueryTexture(field, NULL, NULL, &textW, &textH);
		SDL_RenderCopy(renderer, field, NULL, &textLocation);
		SDL_RenderPresent(renderer);
		
		SDL_Delay(3000);
		SDL_FreeSurface(text);
		TTF_CloseFont(font);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Render Error", "TTF_RenderText_Solid Failed", NULL);
	}
}


void clearScreen()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void renderContourMap()
{
	if (battlefield == NULL) {
		
	}
	else {
		int w = 0;
		int h = 0;
		SDL_SetRenderTarget(renderer, NULL);
		field = SDL_CreateTextureFromSurface(renderer, battlefield);
		SDL_QueryTexture(field, NULL, NULL, &w, &h);
		SDL_RenderCopy(renderer, field, NULL, &battle);
		SDL_RenderPresent(renderer);

	}
}

void renderReadMe() 
{
	if (readMe == NULL) {

	}
	else {
		int w = 0;
		int h = 0;
		SDL_SetRenderTarget(renderer, NULL);
		readMeTexture = SDL_CreateTextureFromSurface(renderer, readMe);
		SDL_QueryTexture(readMeTexture, NULL, NULL, &w, &h);
		SDL_RenderCopy(renderer, readMeTexture, NULL, &readMeRect);
		SDL_RenderPresent(renderer);
	}
}

int render_shooting_symbol(TTF_Font * font, int index, int x, int y)
{

	
	SDL_Color foregroundColor = { 0, 0, 0 };

	if (font == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Render Error", "OpenFont Failed", NULL);
		return -1;
	}
	std::string string = "S";
	text = TTF_RenderText_Solid(font, string.c_str(), foregroundColor);
	if (text != NULL) {
		int texW = 8;
		int texH = 8;
		SDL_Rect textLocation = { x, y, texW, texH };

		SDL_Texture *field = SDL_CreateTextureFromSurface(renderer, text);
		SDL_QueryTexture(field, NULL, NULL, &texW, &texH);
		SDL_RenderCopy(renderer, field, NULL, &textLocation);
		SDL_RenderPresent(renderer);

		//SDL_Delay
		
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Render Error", "TTF_RenderText_Solid Failed", NULL);
		return -1;
	}
}

void draw_one_ellipse(int x1, int y1,int st)
{
	int w = 4;
	int h = 4;
	switch (st) {
	case READY:
		//green
		filledEllipseRGBA(renderer,
			x1, y1,
			w, h,
			0, 255, 0, 255);
		break;
	case DEAD:
		//black
		filledEllipseRGBA(renderer,
			x1, y1,
			2, 2,
			0, 0, 0, 255);
		break;
	case FIGHT_TO_DEATH:
		//purple
		filledEllipseRGBA(renderer,
			x1, y1,
			w, h,
			128, 0, 128, 255);
		break;
	case ENGAGED:
		//red
		filledEllipseRGBA(renderer,
			x1, y1,
			w, h,
			255, 0, 0, 255);
		break;
	case BROKEN:
		//black-bordered rec
		ellipseRGBA(renderer,
			x1, y1,
			w, h,
			0, 0, 0, 255);
		break;
	case RETREAT:
		//yellow
		filledEllipseRGBA(renderer,
			x1, y1,
			w, h,
			255, 255, 0, 255);
		break;
	}
	SDL_RenderPresent(renderer);
	
}

void draw_one_rec(int x1, int y1, int st)
{
	rect.x = x1;
	rect.y = y1;
	rect.w = 9;
	rect.h = 8;

	switch (st) {
	case READY:
		//green
		SDL_SetRenderDrawColor(renderer, 154, 205, 50, 255); 
		SDL_RenderFillRect(renderer, &rect); 
		break;
	case DEAD: 
		//black
		rect.w = 4;
		rect.h = 4;
		SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255); 
		SDL_RenderFillRect(renderer, &rect); 
		break;
	case FIGHT_TO_DEATH: 
		//purple
		SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255); 
		SDL_RenderFillRect(renderer, &rect); 
		break;
	case ENGAGED:
		//red1
		SDL_SetRenderDrawColor(renderer, 242, 122,122 , 255); 
		SDL_RenderFillRect(renderer, &rect); 
		break;
	case BROKEN: 
		//black-bordered rec
		SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 255);
		SDL_RenderDrawRect(renderer, &rect); 
		break;
	case RETREAT:
		//yellow
		SDL_SetRenderDrawColor(renderer, 204, 204, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		break;
	}
	SDL_RenderPresent(renderer);
}

void fileReader(char filename[], TTF_Font *font)
{
	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "0", filename, NULL);
	for (int i = 0; i < strlen(filename); ++i) {
		if (filename[i] == '\\') {
			filename[i] = '/';
		}
	}

	SDL_Event event;
	bool painting = true;

	//std::ifstream inFile("D:/17-Win/Battle_Graphic/Battle_Graphic/agent_stat_per_round_6.txt");
	std::ifstream inFile(filename);
	if (!inFile) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "File", "File  not found. :(" ,NULL);
		return;
	}
	std::string line;
	renderContourMap();
	while (getline(inFile, line)) {
		if (line.empty()) continue;
		
		
		std::istringstream iss(line);

		std::string betray, action, end;
		int index, x, y, side, state, x_pos = 0, y_pos = 0;

	    if(iss >> betray >>action>>index >> x >> y >> side >> state) {

			if (index == 0) {
				
				SDL_Delay(700);
				SDL_RenderCopy(renderer, field, NULL, &battle);
				SDL_RenderPresent(renderer);
				//clearScreen();
				
			}
			else if (index == 999) {
				std::string info;
				if (betray == "TamerlaneWon") info = "Tamerlane win the battle";
				else if (betray == "OttomanWon") info = "Ottoman win the battle --counterfactual";
				else info = "Draw";

				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Battle Result", info.c_str(), NULL);
			}
			else {
			
				/*draw_battle_border();
				SDL_RenderPresent(renderer);*/

				if (x == -1) {
					x_pos = 20;
					y_pos = 20;
				}
				else {
					x_pos = (int)((double)x / (double)20) + 30;
					y_pos = (int)((double)y / (double)20) + 30;
				}

				SDL_SetRenderTarget(renderer, field);
				if (side == Bayezid) {
					
					draw_one_rec(x_pos, y_pos, state);
				}
				else {
					if (betray == "B" && state != DEAD) 
					{
						ellipseRGBA(renderer,
							x_pos, y_pos,
							6,5,
							0, 0, 255,255);
					}
					draw_one_ellipse(x_pos, y_pos, state);
				}

				if (action == "S") {
					render_shooting_symbol(font, index, x_pos, y_pos);
				}
				
			}
		}
		else {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Format Error", line.c_str(), NULL);
			break; }


		// handle quit and click
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				painting == false; break;
			}

			if (event.type == SDL_KEYDOWN) {
				SDL_Keycode keypressed = event.key.keysym.sym;

				switch (keypressed) {
				case SDLK_q:
					painting = false;
					return;
				}

			}
		}
	}

	SDL_Delay(6000);
	
}

void filepicker(TTF_Font *font)
{
	char filename[MAX_PATH] = "";

	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Text Files\0*.txt\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File, yo!";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "File", filename, NULL);
		fileReader(filename, font);
	}
	else
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "File", "File  not found. :(", NULL);
	}
}


	

    