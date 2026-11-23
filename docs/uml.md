# Diagrama de clases (UML)

Proyecto: *La Cripta del Dragon de Ceniza* (version final, con niveles y el jefe Nigromante).

`Entrada` no aparece en el diagrama porque no es una clase: es un modulo de funciones libres (`leerLinea`, `leerOpcion`) que usa `Juego`.

```mermaid
classDiagram
    direction TB

    class Entidad {
        <<abstract>>
        #string nombre
        #int vida
        #int vidaMaxima
        #int ataque
        +Entidad(string nombre, int vida, int ataque)
        +~Entidad()
        +atacar(Entidad& objetivo)* void
        +recibirDanio(int danio) void
        +curar(int cantidad) void
        +estaVivo() bool
        +getNombre() string
        +getVida() int
        +getVidaMaxima() int
        +getAtaque() int
    }

    class Jugador {
        -vector~Objeto~ inventario
        -int bonusAtaque
        -Habitacion* ubicacion
        -int nivel
        -int experiencia
        +Jugador(string nombre)
        +atacar(Entidad& objetivo) void
        +agregarObjeto(Objeto objeto) void
        +usarObjeto(int indice) bool
        +ganarExperiencia(int xp) void
        +getInventario() vector~Objeto~
        +getBonusAtaque() int
        +getNivel() int
        +getExperiencia() int
        +setUbicacion(Habitacion* habitacion) void
        +Habitacion* getUbicacion()
        -beberPocion(Objeto pocion) bool
        -equiparArma(Objeto arma) void
        -subirNivel() void
    }

    class Enemigo {
        <<abstract>>
        -int recompensaXp
        +Enemigo(string nombre, int vida, int ataque, int recompensaXp)
        +~Enemigo()
        +getTipo()* string
        +getRecompensaXp() int
    }

    class Orco {
        +Orco(string nombre)
        +atacar(Entidad& objetivo) void
        +getTipo() string
        -estaEnFuria() bool
    }

    class Dragon {
        -int ataquesRealizados
        +Dragon(string nombre)
        +atacar(Entidad& objetivo) void
        +getTipo() string
    }

    class Nigromante {
        -int ataquesRealizados
        +Nigromante(string nombre)
        +atacar(Entidad& objetivo) void
        +getTipo() string
    }

    class TipoObjeto {
        <<enumeration>>
        PocionDeVida
        Arma
    }

    class Objeto {
        -string nombre
        -string descripcion
        -TipoObjeto tipo
        -int valor
        +Objeto(string nombre, string descripcion, TipoObjeto tipo, int valor)
        +getNombre() string
        +getDescripcion() string
        +getTipo() TipoObjeto
        +getValor() int
    }

    class Habitacion {
        -string nombre
        -string descripcion
        -map~string, Habitacion*~ salidas
        -vector~Enemigo*~ enemigos
        -vector~Objeto~ objetos
        +Habitacion(string nombre, string descripcion)
        +conectar(string direccion, Habitacion* destino) void
        +getSalidas() map~string, Habitacion*~
        +agregarEnemigo(Enemigo* enemigo) void
        +retirarEnemigosDerrotados() void
        +hayEnemigosVivos() bool
        +getEnemigos() vector~Enemigo*~
        +agregarObjeto(Objeto objeto) void
        +retirarObjeto(int indice) Objeto
        +getObjetos() vector~Objeto~
        +getNombre() string
        +describir() void
        -mostrarEnemigos() void
        -mostrarObjetos() void
        -mostrarSalidas() void
    }

    class Juego {
        -Jugador* jugador
        -vector~Habitacion*~ habitaciones
        -vector~Enemigo*~ enemigos
        -Habitacion* habitacionFinal
        +Juego()
        +~Juego()
        +iniciar() void
        -mostrarIntroduccion() void
        -pedirNombre() string
        -construirMundo() void
        -crearHabitaciones() void
        -crearHabitacion(string nombre, string descripcion) void
        -conectarHabitaciones() void
        -conectarIdaYVuelta(int origen, string ida, int destino, string vuelta) void
        -colocarEnemigos() void
        -colocarEnemigo(int indiceHabitacion, Enemigo* enemigo) void
        -colocarObjetos() void
        -menuExploracion() void
        -mostrarMenuExploracion() void
        -ejecutarOpcionExploracion(int opcion) bool
        -moverse() bool
        -Habitacion* elegirDestino()
        -recogerObjeto() void
        -gestionarInventario() bool
        -mostrarEstadoJugador() void
        -mostrarObjetosNumerados(vector~Objeto~ objetos) void
        -comprobarVictoria() bool
        -combatir() bool
        -atacarEnemigo() bool
        -contraatacar() void
        -Enemigo* elegirObjetivo()
        -mostrarEnemigosNumerados() void
        -mostrarMenuCombate() void
    }

    Entidad <|-- Jugador : es un
    Entidad <|-- Enemigo : es un
    Enemigo <|-- Orco : es un
    Enemigo <|-- Dragon : es un
    Enemigo <|-- Nigromante : es un

    Juego "1" *-- "1" Jugador : posee
    Juego "1" *-- "6" Habitacion : posee
    Juego "1" *-- "*" Enemigo : posee
    Jugador "1" *-- "*" Objeto : inventario
    Habitacion "1" *-- "*" Objeto : suelo

    Habitacion "0..1" o-- "*" Enemigo : registra

    Habitacion "*" --> "*" Habitacion : salidas
    Jugador "*" --> "0..1" Habitacion : ubicacion
    Juego "*" --> "1" Habitacion : habitacionFinal

    Objeto ..> TipoObjeto : usa
```

El diagrama se verifico renderizandolo con `@mermaid-js/mermaid-cli`.

Convenciones del diagrama: `+` publico, `-` privado, `#` protegido. Las clases abstractas llevan `<<abstract>>` y los metodos virtuales puros un `*` despues de los parentesis (`+atacar(Entidad& objetivo)* void`). Un metodo que devuelve un puntero se escribe con el tipo al inicio (`+Habitacion* getUbicacion()`), porque un `*` al final de la linea lo marcaria como abstracto. Los tipos se escriben sin `const` ni `&` para que el diagrama se lea mejor, salvo en `atacar`.

## Relaciones

| Relacion | Tipo | Cardinalidad | Implementacion en C++ | Quien libera |
|---|---|---|---|---|
| `Entidad` <- `Jugador`, `Enemigo`; `Enemigo` <- `Orco`, `Dragon`, `Nigromante` | Herencia ("es un") | - | `: public` | - |
| `Juego` - `Jugador` | Composicion | 1 - 1 | `Jugador* jugador` (puntero propio) | `~Juego()` |
| `Juego` - `Habitacion` | Composicion | 1 - 6 | `std::vector<Habitacion*>` | `~Juego()` |
| `Juego` - `Enemigo` | Composicion | 1 - * (en el juego: 5) | `std::vector<Enemigo*>` | `~Juego()` |
| `Jugador` - `Objeto` | Composicion | 1 - * | `std::vector<Objeto>` (por valor) | automatico |
| `Habitacion` - `Objeto` | Composicion | 1 - * | `std::vector<Objeto>` (por valor) | automatico |
| `Habitacion` - `Enemigo` | Agregacion | 0..1 - * | `std::vector<Enemigo*>` (solo apunta) | no libera |
| `Habitacion` -> `Habitacion` (salidas) | Asociacion (auto-asociacion) | * - * | `std::map<std::string, Habitacion*>` | no libera |
| `Jugador` -> `Habitacion` (ubicacion) | Asociacion | * - 0..1 | `Habitacion* ubicacion` | no libera |
| `Juego` -> `Habitacion` (final: Sala del Trono) | Asociacion | * - 1 | `Habitacion* habitacionFinal` | no libera |

## Justificacion de las relaciones

- **Herencia:** un jugador y un enemigo *son una* entidad: comparten nombre, vida y ataque y cada uno ataca a su manera. Orco, Dragon y Nigromante *son un* enemigo.
- **Composicion `Jugador`-`Objeto` y `Habitacion`-`Objeto`:** los objetos nacen y mueren con quien los contiene (por valor).
- **Composicion `Juego`-(`Jugador`, `Habitacion`, `Enemigo`):** `Juego` los crea con `new` y es el unico que los destruye.
- **Agregacion `Habitacion`-`Enemigo`:** la habitacion solo *registra* a los enemigos presentes; existen sin ella (podrian moverse entre habitaciones) y no los libera. El Nigromante entra en esta relacion igual que los demas enemigos.
- **Asociacion:** el jugador "esta en" una habitacion, las habitaciones "se conectan con" otras y `Juego` "sabe cual es" la habitacion final; son relaciones de conocimiento entre objetos independientes.
