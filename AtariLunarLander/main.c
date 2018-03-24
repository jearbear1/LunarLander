//
//  main.c
//  AtariLunarLander
//
//  Created by Jeremiah Onwubuya on 3/16/18.
//  Copyright © 2018 Jeremiah Onwubuya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL_image.h>


#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
// Speed in Pixels/Seconds
#define SCROLL_SPEED (300)

// Spirte Size
#define SPRITE_SIZE    32


int main(int argc, const char * argv[]) {
    
 // Attempt to initialize graphics library
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    
    //Initialize Key Variables
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Surface *imageSurface = NULL;
    
    
    
    // Creating Surfaces and Addresses
    SDL_Surface *temp = NULL;
    SDL_Surface *sprite = NULL;
    SDL_Surface *oCISLY = SDL_LoadBMP("/Users/jeremiahonwubuya/Desktop/AtariLunarLander/oCISLY.bmp");
    SDL_Surface *youWin = SDL_LoadBMP("/Users/jeremiahonwubuya/Desktop/AtariLunarLander/youwin.bmp");
    
    // set sprite positions
    SDL_Rect dstSprite = {arc4random_uniform(440), 0, 32, 32};
    
    SDL_Rect dstOCISLY = {arc4random_uniform(440), 378, 96, 96};
    
    SDL_Rect dstYouWin = {280, 210, 64, 64};
    
    
    
    // Attempt to create SDL Window
    window = SDL_CreateWindow("Atari Lunar Lander", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    // Print an Error if the window fails to initialize
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create The Title of the Window
    SDL_SetWindowTitle(window, "Atari Lunar Lander");
    
    // Create SDL Render Window
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;
    renderer = SDL_CreateRenderer(window, -1, render_flags);
    
    // if rendering the window fails
    if (!renderer) {
        printf("error creating render: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    windowSurface = SDL_GetWindowSurface(window);
    
    // Load A bitmap image as an Surface
    windowSurface = SDL_LoadBMP("/Users/jeremiahonwubuya/Desktop/AtariLunarLander/outerspace.bmp");
    
    
    if (!windowSurface) {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    //Load Image data into graphics hardware memory
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, windowSurface);
    
    
    if (!texture) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    
    // load bitmap image into an SDL_Surface "temp" and store "temp" into the SDL_Surface "sprite" that is optimized for Blitting
    temp   = SDL_LoadBMP("/Users/jeremiahonwubuya/Desktop/AtariLunarLander/player.bmp");
    sprite = SDL_ConvertSurface(temp, temp->format, 0);
    SDL_FreeSurface(temp);
    
    
    
    // Making Textures
    SDL_Texture *playerTexture = SDL_CreateTextureFromSurface(renderer, sprite);
    SDL_Texture *oCISLYTexture = SDL_CreateTextureFromSurface(renderer, oCISLY);
    SDL_Texture *youWinTexture = SDL_CreateTextureFromSurface(renderer, youWin);
    
    if (!sprite) {
        printf("error creating sprite: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    
    
    // updating the Window Surface to be the BitMap Image
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderCopy(renderer, playerTexture, NULL, &dstSprite);
    SDL_RenderCopy(renderer, oCISLYTexture, NULL, &dstOCISLY);
    SDL_RenderPresent(renderer);
    
    
    
    
    bool isRunning = true;

    SDL_Event event;
    
    while (isRunning) {
        
        while (SDL_PollEvent(&event) != 0 ) {
            if (event.type == SDL_QUIT) {
                // close button clicked
                isRunning = false;
                break;
            }
            
            if (event.type == SDL_KEYDOWN) {
                // close program upon buttons pressed
                switch(event.key.keysym.sym){
                    case SDLK_q:
                        printf("program stopped");
                        isRunning = false;
                        break;
                    case SDLK_ESCAPE:
                        printf("programm stopped");
                        isRunning = false;
                        break;
                        
                }
                
                // Animating the Sprite
                
                if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT) {
                    dstSprite.x -= 20;
                    dstSprite.w = 32;
                    dstSprite.h = 32;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderCopy(renderer, playerTexture, NULL, &dstSprite);
                    SDL_RenderCopy(renderer, oCISLYTexture, NULL, &dstOCISLY);
                    SDL_RenderPresent(renderer);
                    printf("sprite moved leftt to position %d \n", dstSprite.x);
            
         }
                
                if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT) {
                    dstSprite.x += 20;
                    dstSprite.w = 32;
                    dstSprite.h = 32;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderCopy(renderer, playerTexture, NULL, &dstSprite);
                    SDL_RenderCopy(renderer, oCISLYTexture, NULL, &dstOCISLY);
                    SDL_RenderPresent(renderer);
                    printf("sprite moved right to position %d \n", dstSprite.x);
            
                }
                
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
                    dstSprite.y -= 20;
                    dstSprite.w = 32;
                    dstSprite.h = 32;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderCopy(renderer, playerTexture, NULL, &dstSprite);
                    SDL_RenderCopy(renderer, oCISLYTexture, NULL, &dstOCISLY);
                    SDL_RenderPresent(renderer);
                    printf("sprite moved up to position %d \n", dstSprite.y);
         
                }
                
                if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
                    dstSprite.y += 20;
                    dstSprite.w = 32;
                    dstSprite.h = 32;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderCopy(renderer, playerTexture, NULL, &dstSprite);
                    SDL_RenderCopy(renderer, oCISLYTexture, NULL, &dstOCISLY);
                    SDL_RenderPresent(renderer);
                    printf("sprite moved down to position %d \n", dstSprite.y);
               
                }
                
            }
            
            
          // Prevent Sprite from colliding with the edges of the screen
            
            if ( dstSprite.x < 0 ) {
                dstSprite.x = 0;
            }
            else if ( dstSprite.x > WINDOW_WIDTH-SPRITE_SIZE ) {
                dstSprite.x = WINDOW_WIDTH-SPRITE_SIZE;
            }
            if ( dstSprite.y < 0 ) {
                dstSprite.y = 0;
            }
            else if ( dstSprite.y > WINDOW_HEIGHT-SPRITE_SIZE ) {
                dstSprite.y = WINDOW_HEIGHT-SPRITE_SIZE;
            }
           
            
            if(dstSprite.x >=  dstOCISLY.x && dstSprite.y >=  dstOCISLY.y ) {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderCopy(renderer, youWinTexture, NULL, &dstYouWin);
                SDL_RenderPresent(renderer);
                
                // Clean Up
                // Free Surfaces
                SDL_FreeSurface(sprite);
                sprite = NULL;
                SDL_FreeSurface(windowSurface);
                windowSurface = NULL;
                SDL_FreeSurface(imageSurface);
                imageSurface = NULL;
                SDL_FreeSurface(oCISLY);
                oCISLY = NULL;
                SDL_FreeSurface(youWin);
                youWin = NULL;
                // Destroy Texture and Window
                texture = NULL;
                SDL_DestroyTexture(texture);
                playerTexture = NULL;
                SDL_DestroyTexture(playerTexture);
                window = NULL;
                SDL_DestroyTexture(oCISLYTexture);
                oCISLYTexture = NULL;
                SDL_DestroyTexture(youWinTexture);
                youWinTexture = NULL;
                SDL_DestroyWindow(window);
                SDL_Delay(5000);
                SDL_Quit();
                
            }
            
            // Draw the Sprite
            SDL_BlitSurface(sprite, NULL, windowSurface, &dstSprite);
            
            
            SDL_UpdateWindowSurface(window);
        }
        
    }
    
    return 0;
}


