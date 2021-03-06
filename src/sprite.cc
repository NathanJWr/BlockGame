#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include "display.h"
SDL_Surface* player;
SDL_Surface* asteroid1;
SDL_Surface* asteroid2;
SDL_Surface* asteroid3;
SDL_Surface* asteroid1_exp;
SDL_Surface* asteroid2_exp;
SDL_Surface* asteroid3_exp;
SDL_Surface* bullet;
SDL_Surface* heart;
SDL_Surface* ruby;

void querySprite(Sprite* const sprite) {
  SDL_QueryTexture(sprite -> texture,
      NULL,
      NULL,
      &(sprite -> tex_rect.w),
      &(sprite -> tex_rect.h));
  sprite -> tot_frames = sprite -> tex_rect.w / sprite -> tex_rect.h;
  sprite -> tex_rect.w /= sprite -> tot_frames;
  sprite -> tex_rect.x = 0;
  sprite -> tex_rect.y = 0;
  sprite -> delay = 100;
}
void setupAllSprites() {
  player = loadImageSurface("assets/images/ship.png");
  asteroid1 = loadImageSurface("assets/images/asteroid1.png");
  asteroid2 = loadImageSurface("assets/images/asteroid2.png");
  asteroid3 = loadImageSurface("assets/images/asteroid3.png");
  asteroid1_exp = loadImageSurface("assets/images/asteroid1_explode.png");
  asteroid2_exp = loadImageSurface("assets/images/asteroid2_explode.png");
  asteroid3_exp = loadImageSurface("assets/images/asteroid3_explode.png");
  bullet = loadImageSurface("assets/images/laser.png");
  heart = loadImageSurface("assets/images/heart.png");
  ruby = loadImageSurface("assets/images/ruby.png");
}
void renderSprite(Sprite* const sprite,
    SDL_Rect* const pos) {

  if(sprite -> texture == NULL) {
    printf("Texture not loaded\n");
    exit(1);
  }
  sprite -> current_frame = (SDL_GetTicks() / sprite -> delay) % sprite -> tot_frames;
  sprite -> tex_rect.x = sprite -> current_frame * sprite -> tex_rect.w;
  renderTexture(sprite -> texture, &(sprite -> tex_rect), pos);
}

void destroySprite(Sprite* const sprite) {
  if(sprite -> texture != NULL) {
    SDL_DestroyTexture(sprite -> texture);
    sprite -> texture = NULL;
  }
}

void setupHeartSprite(Sprite* const h) {
  h -> texture = surfaceToTextureSafe(heart);
  querySprite(h);
}

void setupPlayerSprite(Sprite* const p) {
  p -> texture = surfaceToTextureSafe(player);
  querySprite(p);
}

void setupBulletSprite(Sprite* const b) {
  b -> texture = surfaceToTextureSafe(bullet);
  querySprite(b);
}

void setupAsteroidSprite(int type,
    Sprite* const asteroid,
    Sprite* const explosion) {

  if(type == 1) {
    asteroid -> texture = surfaceToTextureSafe(asteroid1);
    explosion -> texture = surfaceToTextureSafe(asteroid1_exp);
  }
  else if(type == 2) {
    asteroid -> texture = surfaceToTextureSafe(asteroid2);
    explosion -> texture = surfaceToTextureSafe(asteroid2_exp);
  }
  else if(type == 3) {
    asteroid -> texture = surfaceToTextureSafe(asteroid3);
    explosion -> texture = surfaceToTextureSafe(asteroid3_exp);
  }
  querySprite(asteroid);
  querySprite(explosion);
}

void setupRubySprite(Sprite* const r) {
  r -> texture = surfaceToTextureSafe(ruby);
  querySprite(r);
}

void cleanupSpriteSurfaces() {
  SDL_FreeSurface(player);
  SDL_FreeSurface(asteroid1);
  SDL_FreeSurface(asteroid2);
  SDL_FreeSurface(asteroid3);
  SDL_FreeSurface(asteroid1_exp);
  SDL_FreeSurface(asteroid2_exp);
  SDL_FreeSurface(asteroid3_exp);
  SDL_FreeSurface(bullet);
  SDL_FreeSurface(heart);
  SDL_FreeSurface(ruby);
}
