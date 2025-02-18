#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mlib/mlib.h"

#define ESDL 1

#define MS_PER_FRAME 16
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

#define SPEC2MS(spec) (spec.tv_nsec / 1000000L + spec.tv_sec * 1000L)

typedef SDL_Color(*ColorFunc)(Vertex2D);

typedef struct Vertex3D {
  double x, y, z;
}Vertex3D;

typedef struct Vertex2D {
  double x, y;
}Vertex2D;

typedef struct Line2D {
  double y_slide;
  Vertex2D start;
  Vertex2D end;
  ColorFunc color_distr;
}Line2D;

typedef struct RenderBuffer {
  int width, height;
  int buffer_len;
  double sample_unit_len; // sample unit length for x, y
  SDL_Color back_color;
  SDL_Color* buffer;
}RenderBuffer;

#define SCALE_BUFLEN(width, height, scale_rate) ((width) * (height) * (scale_rate) * (scale_rate))


static void on_draw(SDL_Renderer* render) {
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

  SDL_RenderClear(render);

  SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
  SDL_RenderDrawLine(render, 0, 0, 35, 43);
}

static void update_fps(long frame_time, TTF_Font* font, SDL_Renderer* render) {
  char fps_str[16];

  if (frame_time == 0) {
    sprintf(fps_str, "FPS: inf");
  } else {
    sprintf(fps_str, "FPS: %ld", 1000 / frame_time);
  }

  SDL_Surface* text_surface = TTF_RenderText_Solid(font, fps_str, (SDL_Color) {0, 0, 0, 255});

  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(render, text_surface);

  SDL_Rect text_rect = {
    .x = WINDOW_WIDTH - text_surface->w,
    .y = text_surface->h,
    .h = text_surface->h,
    .w = text_surface->w
  };

  SDL_RenderCopy(render, text_texture, 0, &text_rect);

  SDL_FreeSurface(text_surface);
  SDL_DestroyTexture(text_texture);
}

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    return -ESDL;
  }
  
  if (TTF_Init() == -1) {
    return -ESDL;
  }

  TTF_Font* font = TTF_OpenFont("res/fonts/nerd_hack.ttf", 24);

  if (font == 0) {
    return -ESDL;
  }

  SDL_Window* window = SDL_CreateWindow("Srend", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (render == 0) {
    return -ESDL;
  }

  printf("Init finished\n");

  SDL_Event event;

  struct timespec time_sampler;

  while (true) {
    timespec_get(&time_sampler, TIME_UTC);

    long sample_time_ms = SPEC2MS(time_sampler);

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
      }

      if (event.type == SDL_QUIT) {
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
      }
    }

    on_draw(render);
    
    timespec_get(&time_sampler, TIME_UTC);

    update_fps(SPEC2MS(time_sampler) - sample_time_ms, font, render);

    SDL_RenderPresent(render);

    timespec_get(&time_sampler, TIME_UTC);

    if (SPEC2MS(time_sampler) - sample_time_ms >= MS_PER_FRAME) {
      continue;
    }

    SDL_Delay(MS_PER_FRAME - (SPEC2MS(time_sampler) - sample_time_ms));
  }
}