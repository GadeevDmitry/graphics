#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include <vec.h>
#include <coord_system.h>

void draw_vec      (const vec &vec_beg, const vec &vec_main, const coord_system &sys, sf::RenderWindow &wnd, const sf::Color col);
void draw_line     (const vec &vec_beg, const vec &vec_main, const coord_system &sys, sf::RenderWindow &wnd, const sf::Color col);
void draw_coord_sys(                                         const coord_system &sys, sf::RenderWindow &wnd, const sf::Color col);

void draw_pixel_vec  (const vec &pix_beg, const vec &pix_main, sf::RenderWindow &wnd, sf::Color col);
void draw_pixel_line (const vec &pix_beg, const vec &pix_main, sf::RenderWindow &wnd, sf::Color col);
void draw_pixel_point(const vec &pix_point                   , sf::RenderWindow &wnd, sf::Color col);

#endif // DRAW_H