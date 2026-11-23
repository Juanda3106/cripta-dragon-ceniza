#include "Juego.h"

#include <iostream>

#include "Dragon.h"
#include "Enemigo.h"
#include "Entrada.h"
#include "Habitacion.h"
#include "Jugador.h"
#include "Nigromante.h"
#include "Orco.h"

// ---------- Valores de los objetos ----------
const int CURACION_POCION = 40;
const int BONUS_ESPADA = 6;

// ---------- Posicion de cada habitacion en el vector habitaciones ----------
// Deben coincidir con el orden en que crearHabitaciones las crea.
const int INDICE_ENTRADA = 0;
const int INDICE_SALON = 1;
const int INDICE_ARMERIA = 2;
const int INDICE_CRIPTA = 3;
const int INDICE_CAMARA = 4;
const int INDICE_TRONO = 5;

// ---------- Opciones de los menus ----------
const int OPCION_SALIR = 0;
const int OPCION_MIRAR = 1;
const int OPCION_MOVERSE = 2;
const int OPCION_RECOGER = 3;
const int OPCION_INVENTARIO = 4;
const int OPCION_ESTADO = 5;
const int OPCION_CANCELAR = 0;
const int ACCION_ATACAR = 1;
const int ACCION_USAR_OBJETO = 2;

// ---------- Textos ----------
const std::string NOMBRE_POR_DEFECTO = "Aventurero";
const std::string PEDIR_OPCION = "Elige una opcion:";
const std::string TEXTO_TITULO = "=== La Cripta del Dragon de Ceniza ===";
const std::string TEXTO_INTRODUCCION =
    "Un nigromante desperto a un dragon que incendio tu aldea. Los dos se ocultan en la "
    "Cripta de Ceniza. Tu mision: bajar, vencer al dragon y acabar con el nigromante.";
const std::string TEXTO_VICTORIA =
    "El nigromante se desploma y su magia oscura se disipa. La cripta queda en silencio. "
    "Has liberado el valle. VICTORIA";
const std::string TEXTO_DERROTA =
    "Tus fuerzas se agotan y todo se oscurece. El valle seguira esperando a un heroe. DERROTA";
const std::string TEXTO_SALIDA = "Abandonas la cripta. Hasta pronto.";

// ======================= Creacion y destruccion =======================

// Juego se crea en el Stack (en main); todavia no hay nada en el Heap.
Juego::Juego()
    : jugador(nullptr),
      habitacionFinal(nullptr) {
}

// Juego es el unico dueno: cada new de esta clase tiene aqui su unico delete.
// Gracias al destructor virtual de Entidad, delete llama al destructor del tipo real.
Juego::~Juego() {
    delete this->jugador;
    for (Habitacion* habitacion : this->habitaciones) {
        delete habitacion;
    }
    for (Enemigo* enemigo : this->enemigos) {
        delete enemigo;
    }
}

// ======================= Preparacion de la partida =======================

void Juego::iniciar() {
    this->mostrarIntroduccion();
    this->jugador = new Jugador(this->pedirNombre());   // el jugador vive en el Heap
    this->construirMundo();
    this->jugador->getUbicacion()->describir();
    this->menuExploracion();
}

void Juego::mostrarIntroduccion() const {
    std::cout << TEXTO_TITULO << std::endl;
    std::cout << TEXTO_INTRODUCCION << std::endl;
}

std::string Juego::pedirNombre() const {
    std::cout << "Como te llamas, aventurero?" << std::endl;
    std::string nombre;
    if (!leerLinea(nombre) || nombre.empty()) {
        return NOMBRE_POR_DEFECTO;
    }
    return nombre;
}

void Juego::construirMundo() {
    this->crearHabitaciones();
    this->conectarHabitaciones();
    this->colocarEnemigos();
    this->colocarObjetos();
    // ASOCIACION: Juego y Jugador solo apuntan a habitaciones que ya existen.
    this->habitacionFinal = this->habitaciones[INDICE_TRONO];
    this->jugador->setUbicacion(this->habitaciones[INDICE_ENTRADA]);
}

// El orden de creacion es el de las constantes INDICE_...
void Juego::crearHabitaciones() {
    this->crearHabitacion("Entrada de la Cripta",
        "Una puerta de piedra rota da paso a un vestibulo frio. "
        "Antorchas casi apagadas iluminan el camino hacia el norte.");
    this->crearHabitacion("Salon de Guardia",
        "Un salon amplio con bancos volcados. Huele a humo y a hierro oxidado.");
    this->crearHabitacion("Armeria",
        "Estantes caidos y armaduras oxidadas. Algo brilla bajo una mesa.");
    this->crearHabitacion("Cripta Profunda",
        "Sarcofagos abiertos y un frio que cala los huesos. "
        "Dos sombras se mueven entre las tumbas.");
    this->crearHabitacion("Camara del Dragon",
        "Una enorme caverna cubierta de ceniza. "
        "Sobre una montana de monedas, un dragon abre un ojo.");
    this->crearHabitacion("Sala del Trono",
        "Un trono de huesos domina la sala. Una figura encapuchada alza la cabeza: "
        "es el nigromante que desperto al dragon.");
}

// COMPOSICION: Juego crea la habitacion con new y guarda el puntero para liberarla al final.
void Juego::crearHabitacion(const std::string& nombre, const std::string& descripcion) {
    this->habitaciones.push_back(new Habitacion(nombre, descripcion));
}

void Juego::conectarHabitaciones() {
    this->conectarIdaYVuelta(INDICE_ENTRADA, "norte", INDICE_SALON, "sur");
    this->conectarIdaYVuelta(INDICE_SALON, "este", INDICE_ARMERIA, "oeste");
    this->conectarIdaYVuelta(INDICE_SALON, "norte", INDICE_CRIPTA, "sur");
    this->conectarIdaYVuelta(INDICE_CRIPTA, "norte", INDICE_CAMARA, "sur");
    this->conectarIdaYVuelta(INDICE_CAMARA, "norte", INDICE_TRONO, "sur");
}

// conectar es de un solo sentido; por eso cada pasillo se conecta dos veces.
void Juego::conectarIdaYVuelta(int origen, const std::string& ida, int destino, const std::string& vuelta) {
    this->habitaciones[origen]->conectar(ida, this->habitaciones[destino]);
    this->habitaciones[destino]->conectar(vuelta, this->habitaciones[origen]);
}

// PILAR - POLIMORFISMO: se crea un Orco, un Dragon o un Nigromante, pero desde aqui
// en adelante todos se manejan igual, como Enemigo*.
void Juego::colocarEnemigos() {
    this->colocarEnemigo(INDICE_SALON, new Orco("Gruk"));
    this->colocarEnemigo(INDICE_CRIPTA, new Orco("Brak"));
    this->colocarEnemigo(INDICE_CRIPTA, new Orco("Zug"));
    this->colocarEnemigo(INDICE_CAMARA, new Dragon("Cenizo"));
    this->colocarEnemigo(INDICE_TRONO, new Nigromante("Morgrath"));
}

// El mismo puntero queda en dos vectores con papeles distintos.
void Juego::colocarEnemigo(int indiceHabitacion, Enemigo* enemigo) {
    this->enemigos.push_back(enemigo);                                // COMPOSICION: Juego es el dueno
    this->habitaciones[indiceHabitacion]->agregarEnemigo(enemigo);   // AGREGACION: la habitacion solo lo registra
}

// Los objetos van por valor: cada habitacion guarda su propia copia.
void Juego::colocarObjetos() {
    const Objeto pocion("Pocion de Vida", "Restaura 40 puntos de vida.",
                        TipoObjeto::PocionDeVida, CURACION_POCION);
    const Objeto espada("Espada de Hierro", "Aumenta tu ataque en 6 puntos.",
                        TipoObjeto::Arma, BONUS_ESPADA);
    this->habitaciones[INDICE_ENTRADA]->agregarObjeto(pocion);
    this->habitaciones[INDICE_ARMERIA]->agregarObjeto(espada);
    this->habitaciones[INDICE_ARMERIA]->agregarObjeto(pocion);
    this->habitaciones[INDICE_CRIPTA]->agregarObjeto(pocion);
    this->habitaciones[INDICE_CAMARA]->agregarObjeto(pocion);
}

// ======================= Exploracion =======================

void Juego::menuExploracion() {
    bool continuar = true;
    do {
        this->mostrarMenuExploracion();
        int opcion = leerOpcion(PEDIR_OPCION, OPCION_SALIR, OPCION_ESTADO);
        continuar = this->ejecutarOpcionExploracion(opcion);
    } while (continuar);
}

void Juego::mostrarMenuExploracion() const {
    std::cout << std::endl;
    std::cout << this->jugador->getUbicacion()->getNombre()
              << " | Nivel: " << this->jugador->getNivel()
              << " | Vida: " << this->jugador->getVida() << "/" << this->jugador->getVidaMaxima()
              << std::endl;
    std::cout << OPCION_MIRAR << ". Mirar alrededor" << std::endl;
    std::cout << OPCION_MOVERSE << ". Moverse" << std::endl;
    std::cout << OPCION_RECOGER << ". Recoger un objeto" << std::endl;
    std::cout << OPCION_INVENTARIO << ". Ver inventario / usar un objeto" << std::endl;
    std::cout << OPCION_ESTADO << ". Ver estado del jugador" << std::endl;
    std::cout << OPCION_SALIR << ". Salir del juego" << std::endl;
}

bool Juego::ejecutarOpcionExploracion(int opcion) {
    switch (opcion) {
        case OPCION_MIRAR:
            this->jugador->getUbicacion()->describir();
            return true;
        case OPCION_MOVERSE:
            return this->moverse();
        case OPCION_RECOGER:
            this->recogerObjeto();
            return true;
        case OPCION_INVENTARIO:
            this->gestionarInventario();
            return true;
        case OPCION_ESTADO:
            this->mostrarEstadoJugador();
            return true;
        default:   // OPCION_SALIR o ENTRADA_AGOTADA: en los dos casos se sale del juego
            std::cout << TEXTO_SALIDA << std::endl;
            return false;
    }
}

bool Juego::moverse() {
    Habitacion* destino = this->elegirDestino();
    if (destino == nullptr) {
        return true;   // se cancelo; si fue EOF, el menu principal lo detecta y sale
    }

    this->jugador->setUbicacion(destino);
    destino->describir();
    if (destino->hayEnemigosVivos() && !this->combatir()) {
        return false;   // el jugador murio o se agoto la entrada
    }
    return !this->comprobarVictoria();
}

// Lista las salidas en el orden del std::map (alfabetico) y guarda cada destino en un
// vector, para traducir el numero que escribe el jugador a una habitacion.
Habitacion* Juego::elegirDestino() const {
    std::vector<Habitacion*> destinos;
    for (const std::pair<const std::string, Habitacion*>& salida : this->jugador->getUbicacion()->getSalidas()) {
        destinos.push_back(salida.second);
        std::cout << destinos.size() << ". " << salida.first << " -> "
                  << salida.second->getNombre() << std::endl;
    }
    std::cout << OPCION_CANCELAR << ". Cancelar" << std::endl;

    int opcion = leerOpcion(PEDIR_OPCION, OPCION_CANCELAR, static_cast<int>(destinos.size()));
    return (opcion > OPCION_CANCELAR) ? destinos[opcion - 1] : nullptr;
}

void Juego::recogerObjeto() {
    Habitacion* actual = this->jugador->getUbicacion();
    const std::vector<Objeto>& objetos = actual->getObjetos();
    if (objetos.empty()) {
        std::cout << "No hay nada que recoger." << std::endl;
        return;
    }

    this->mostrarObjetosNumerados(objetos);
    std::cout << OPCION_CANCELAR << ". Cancelar" << std::endl;
    int opcion = leerOpcion(PEDIR_OPCION, OPCION_CANCELAR, static_cast<int>(objetos.size()));
    if (opcion > OPCION_CANCELAR) {
        // El objeto pasa por valor del suelo al inventario: se copia y se quita del suelo.
        Objeto objeto = actual->retirarObjeto(opcion - 1);
        this->jugador->agregarObjeto(objeto);
        std::cout << "Recoges " << objeto.getNombre() << "." << std::endl;
    }
}

// Se usa en exploracion y en combate. Devuelve true solo si un objeto se uso:
// asi el combate sabe si la accion gasto el turno.
bool Juego::gestionarInventario() {
    const std::vector<Objeto>& inventario = this->jugador->getInventario();
    if (inventario.empty()) {
        std::cout << "Tu inventario esta vacio." << std::endl;
        return false;
    }

    this->mostrarObjetosNumerados(inventario);
    std::cout << OPCION_CANCELAR << ". Volver" << std::endl;
    int opcion = leerOpcion(PEDIR_OPCION, OPCION_CANCELAR, static_cast<int>(inventario.size()));
    if (opcion <= OPCION_CANCELAR) {
        return false;
    }
    return this->jugador->usarObjeto(opcion - 1);   // el menu cuenta desde 1; el vector desde 0
}

void Juego::mostrarEstadoJugador() const {
    std::cout << "Nombre: " << this->jugador->getNombre() << std::endl;
    std::cout << "Nivel: " << this->jugador->getNivel() << std::endl;
    std::cout << "Experiencia: " << this->jugador->getExperiencia() << "/" << XP_POR_NIVEL
              << std::endl;
    std::cout << "Vida: " << this->jugador->getVida() << "/"
              << this->jugador->getVidaMaxima() << std::endl;
    std::cout << "Ataque base: " << this->jugador->getAtaque() << std::endl;
    std::cout << "Bonus de ataque: " << this->jugador->getBonusAtaque() << std::endl;
    std::cout << "Objetos: " << this->jugador->getInventario().size() << std::endl;
}

void Juego::mostrarObjetosNumerados(const std::vector<Objeto>& objetos) const {
    int numero = 1;
    for (const Objeto& objeto : objetos) {
        std::cout << numero << ". " << objeto.getNombre() << " - "
                  << objeto.getDescripcion() << std::endl;
        numero++;
    }
}

// Se gana al vaciar la Sala del Trono (habitacionFinal). Vencer al dragon no basta.
bool Juego::comprobarVictoria() const {
    bool gano = this->jugador->getUbicacion() == this->habitacionFinal
                && !this->habitacionFinal->hayEnemigosVivos();
    if (gano) {
        std::cout << TEXTO_VICTORIA << std::endl;
    }
    return gano;
}

// ======================= Combate =======================

// Un turno: el jugador elige una accion y, si gasto el turno, los enemigos contraatacan.
bool Juego::combatir() {
    Habitacion* sala = this->jugador->getUbicacion();

    while (this->jugador->estaVivo() && sala->hayEnemigosVivos()) {
        this->mostrarMenuCombate();
        int accion = leerOpcion(PEDIR_OPCION, ACCION_ATACAR, ACCION_USAR_OBJETO);
        if (accion == ENTRADA_AGOTADA) {
            std::cout << TEXTO_SALIDA << std::endl;
            return false;
        }

        // Volver del inventario, o un objeto sin efecto, no gasta el turno.
        bool gastoTurno = (accion == ACCION_ATACAR) ? this->atacarEnemigo()
                                                    : this->gestionarInventario();
        if (gastoTurno) {
            this->contraatacar();
        }
    }

    if (!this->jugador->estaVivo()) {
        std::cout << TEXTO_DERROTA << std::endl;
        return false;
    }
    std::cout << "Has derrotado a todos los enemigos." << std::endl;
    return true;
}

bool Juego::atacarEnemigo() {
    Enemigo* objetivo = this->elegirObjetivo();
    if (objetivo == nullptr) {
        return false;
    }
    this->jugador->atacar(*objetivo);

    // El enemigo sabe cuanta XP vale y el jugador sabe subir de nivel; Juego solo los conecta.
    // El puntero sigue siendo valido aunque el enemigo este derrotado: Juego es su dueno.
    if (!objetivo->estaVivo()) {
        this->jugador->ganarExperiencia(objetivo->getRecompensaXp());
    }
    // Los derrotados salen ahora mismo de la habitacion: asi no contraatacan.
    this->jugador->getUbicacion()->retirarEnemigosDerrotados();
    return true;
}

// PILAR - POLIMORFISMO: este es el corazon del proyecto. La variable es Enemigo*, pero en
// ejecucion corre Orco::atacar, Dragon::atacar o Nigromante::atacar segun el tipo real.
// Cuando se agrego el Nigromante, este metodo no cambio ni una linea.
void Juego::contraatacar() {
    for (Enemigo* enemigo : this->jugador->getUbicacion()->getEnemigos()) {
        if (!this->jugador->estaVivo()) {
            break;
        }
        enemigo->atacar(*this->jugador);
    }
}

Enemigo* Juego::elegirObjetivo() const {
    const std::vector<Enemigo*>& presentes = this->jugador->getUbicacion()->getEnemigos();
    if (presentes.size() == 1) {
        return presentes[0];   // un solo enemigo: se elige solo
    }

    std::cout << "A quien atacas?" << std::endl;
    this->mostrarEnemigosNumerados();
    int opcion = leerOpcion(PEDIR_OPCION, 1, static_cast<int>(presentes.size()));
    return (opcion == ENTRADA_AGOTADA) ? nullptr : presentes[opcion - 1];
}

// Durante el combate el vector de la habitacion solo tiene enemigos vivos, porque los
// derrotados se retiran justo despues de cada ataque del jugador.
void Juego::mostrarEnemigosNumerados() const {
    int numero = 1;
    for (Enemigo* enemigo : this->jugador->getUbicacion()->getEnemigos()) {
        std::cout << numero << ". " << enemigo->getNombre() << " (" << enemigo->getTipo()
                  << ") vida " << enemigo->getVida() << "/" << enemigo->getVidaMaxima()
                  << std::endl;
        numero++;
    }
}

void Juego::mostrarMenuCombate() const {
    std::cout << std::endl;
    std::cout << "--- COMBATE ---" << std::endl;
    std::cout << this->jugador->getNombre() << " (nivel " << this->jugador->getNivel() << "): "
              << this->jugador->getVida() << "/" << this->jugador->getVidaMaxima() << std::endl;
    this->mostrarEnemigosNumerados();
    std::cout << ACCION_ATACAR << ". Atacar" << std::endl;
    std::cout << ACCION_USAR_OBJETO << ". Usar un objeto" << std::endl;
}
