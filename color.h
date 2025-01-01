#ifndef COLOR_H
#define COLOR_H

#include <allegro5/allegro.h>

// Définition des couleurs et des points associés
const ALLEGRO_COLOR COLOR_WHITE   = al_map_rgb(255, 255, 255); // Blanc : 50 points
const ALLEGRO_COLOR COLOR_ORANGE  = al_map_rgb(255, 165, 0);   // Orange : 60 points
const ALLEGRO_COLOR COLOR_CYAN    = al_map_rgb(0, 255, 255);   // Cyan : 70 points
const ALLEGRO_COLOR COLOR_GREEN   = al_map_rgb(0, 255, 0);     // Vert : 80 points
const ALLEGRO_COLOR COLOR_RED     = al_map_rgb(255, 0, 0);     // Rouge : 90 points
const ALLEGRO_COLOR COLOR_BLUE    = al_map_rgb(0, 0, 255);     // Bleu : 100 points
const ALLEGRO_COLOR COLOR_MAGENTA = al_map_rgb(255, 0, 255);   // Magenta : 110 points
const ALLEGRO_COLOR COLOR_YELLOW  = al_map_rgb(255, 255, 0);   // Jaune : 120 points
const ALLEGRO_COLOR COLOR_GREY    = al_map_rgb(200, 200, 200); // Gris (optionnel, sans points spécifiques)
const ALLEGRO_COLOR COLOR_BLACK   = al_map_rgb(0, 0, 0);       // Noir (optionnel, sans points spécifiques)

const ALLEGRO_COLOR COLOR_GOLD   = al_map_rgb(255, 215, 0);  // Doré
const ALLEGRO_COLOR COLOR_SILVER = al_map_rgb(192, 192, 192); // Argenté

#endif // COLOR_H
