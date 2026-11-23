#ifndef ENTRADA_H
#define ENTRADA_H

#include <string>

/**
 * @brief Modulo de funciones libres para leer del teclado (no es una clase).
 *
 * Relaciones: ninguna con otras clases; Juego llama a estas funciones.
 * Para sustentar: "como evitan que el programa falle si escriben letras o se acaba
 * la entrada". Siempre se lee la linea completa con std::getline, se valida que
 * sean digitos y solo entonces se convierte a numero.
 *
 * No es una clase porque no guarda ningun dato: solo agrupa la lectura segura.
 */

// Valor que devuelve leerOpcion cuando la entrada se agoto (EOF).
const int ENTRADA_AGOTADA = -1;

// Lee una linea; devuelve false si la entrada se agoto (EOF).
bool leerLinea(std::string& linea);

// Muestra el mensaje y pide un entero en [minimo, maximo]. Repite si la entrada es
// invalida (vacia, con letras, fuera de rango, de mas de 6 caracteres).
// Devuelve ENTRADA_AGOTADA si se agoto la entrada (EOF).
int leerOpcion(const std::string& mensaje, int minimo, int maximo);

#endif //ENTRADA_H
