#include "Entrada.h"

#include <iostream>

const int MAX_CARACTERES_OPCION = 6;

// Solo se aceptan digitos y pocos caracteres: asi std::stoi nunca puede fallar.
bool esNumeroValido(const std::string& texto) {
    if (texto.empty() || static_cast<int>(texto.size()) > MAX_CARACTERES_OPCION) {
        return false;
    }
    for (char caracter : texto) {
        if (caracter < '0' || caracter > '9') {
            return false;
        }
    }
    return true;
}

bool leerLinea(std::string& linea) {
    if (!std::getline(std::cin, linea)) {
        return false;
    }
    // Un archivo guardado en Windows puede dejar un '\r' al final de la linea.
    if (!linea.empty() && linea.back() == '\r') {
        linea.pop_back();
    }
    return true;
}

int leerOpcion(const std::string& mensaje, int minimo, int maximo) {
    std::string linea;
    while (true) {
        std::cout << mensaje << std::endl;
        if (!leerLinea(linea)) {
            return ENTRADA_AGOTADA;
        }
        if (esNumeroValido(linea)) {
            int numero = std::stoi(linea);
            if (numero >= minimo && numero <= maximo) {
                return numero;
            }
        }
        std::cout << "Opcion no valida. Escribe un numero entre " << minimo
                  << " y " << maximo << "." << std::endl;
    }
}
