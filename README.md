# La Cripta del Dragon de Ceniza

Juego de rol (RPG) de aventura textual para consola, escrito en C++ como proyecto final del curso.

- **Nombre del proyecto/repositorio:** La Cripta del Dragon de Ceniza - [Juanda3106/cripta-dragon-ceniza](https://github.com/Juanda3106/cripta-dragon-ceniza)
- **Integrantes:** Juan Sebastian Vasquez Pelaez, Juan David Llanos Micolta
- **Curso:** Programacion Orientada a Objetos 2026-2 - Ing. Javier Andres Gallego B.

Un nigromante desperto a un dragon que incendio la aldea del valle. El jugador baja por seis habitaciones, recoge objetos, pelea por turnos contra orcos, sube de nivel, vence al dragon Cenizo y, al final, enfrenta al nigromante Morgrath en la Sala del Trono.

Ademas del minimo del enunciado, el proyecto tiene **dos bonus**:

- **Niveles y experiencia:** cada enemigo da experiencia; cada 50 puntos el jugador sube de nivel (+20 de vida maxima, +3 de ataque base y se cura 20).
- **Jefe final con habilidad propia:** el Nigromante, que cada segundo ataque drena la vida del jugador y se cura.

## Por donde empezar a estudiar

1. [docs/recorrido-del-codigo.md](docs/recorrido-del-codigo.md): el orden para leer el codigo, clase por clase, con trazas de un turno de combate y de la memoria.
2. [docs/guia-sustentacion.md](docs/guia-sustentacion.md): guion de 10 minutos, demostracion en vivo, preguntas probables con respuesta, glosario y trampas.
3. [docs/uml.md](docs/uml.md) y [docs/diseno.md](docs/diseno.md): diagrama de clases, relaciones, pilares y decisiones.

## Requisitos

- Compilador de C++ con soporte de C++20 (tambien compila con C++17).
- CMake 3.20 o superior.
- CLion (opcional): ya incluye CMake y MinGW.

## Como compilar

### Con CLion

1. *File > Open* y elegir la carpeta del proyecto.
2. Esperar a que CMake cargue el proyecto.
3. Elegir la configuracion `AventuraTextual` y pulsar *Run*.

### Con CMake por consola

```bash
cmake -S . -B build
```

```bash
cmake --build build
```

El ejecutable queda en `build/AventuraTextual`.

**En Windows con MinGW** hay que indicar el generador en el primer comando, porque CMake busca Visual Studio por defecto:

```bash
cmake -S . -B build -G "MinGW Makefiles"
```

Ademas, `g++` y `cmake` deben estar en el `PATH`. Si se usan los de CLion, estan en `bin/mingw/bin` y `bin/cmake/win/x64/bin` dentro de su carpeta de instalacion. La carpeta de MinGW tambien debe estar en el `PATH` para ejecutar el juego fuera de CLion, porque ahi estan sus DLL.

## Como jugar

Todo se maneja escribiendo el numero de la opcion y pulsando Enter.

Menu de exploracion (arriba se muestra `[Habitacion] | Nivel: N | Vida: V/M`):

```
1. Mirar alrededor
2. Moverse
3. Recoger un objeto
4. Ver inventario / usar un objeto
5. Ver estado del jugador
0. Salir del juego
```

- Al entrar en una habitacion con enemigos, el combate empieza solo.
- En cada turno se elige `1. Atacar` o `2. Usar un objeto`. No se puede huir.
- Despues de una accion que gasta el turno, cada enemigo vivo contraataca.
- Volver del inventario, o usar un objeto sin efecto, no gasta el turno.
- Derrotar a un enemigo da experiencia; con 50 puntos se sube de nivel.
- La partida se gana al derrotar al Nigromante en la Sala del Trono y se pierde si la vida llega a 0.

Consejo: la Espada de Hierro de la Armeria es casi obligatoria para ganar.

## Mapa

```
        [Sala del Trono]      <- final (Nigromante)
               |
      [Camara del Dragon]
               |
        [Cripta Profunda]
               |
 [Armeria] - [Salon de Guardia]
               |
        [Entrada de la Cripta]   <- inicio
```

## Estructura de carpetas

```
CMakeLists.txt     configuracion de compilacion
.gitignore         archivos que Git no debe versionar
.gitattributes     mantiene LF en tests/*.sh y tests/*.in al clonar en Windows
src/               todo el codigo (.h y .cpp)
docs/recorrido-del-codigo.md   orden de estudio del codigo
docs/guia-sustentacion.md      guion de la sustentacion, preguntas y glosario
docs/uml.md        diagrama de clases y justificacion de relaciones
docs/guion.md      guion del videojuego
docs/diseno.md     pilares de la POO, decisiones de diseno y cambios de la fase 2
docs/reparto-trabajo.md   plantilla de reparto por integrante
docs/plan-commits.md      paquetes de trabajo WP1-WP9 y como subirlos
docs/simulaciones/ salida real de las partidas de prueba
tests/             entradas de las partidas y script de pruebas
```

## Como correr las pruebas

Desde Git Bash, Linux o macOS, despues de compilar:

```bash
bash tests/run_tests.sh
```

El script busca el ejecutable en `build/` y en `cmake-build-debug/` (la carpeta de CLion). Tambien se le puede pasar la ruta como argumento.

Si bash muestra `$'\r': command not found`, el script quedo con finales de linea de Windows (CRLF). Se arregla con el comando de abajo. `.gitattributes` obliga a que `*.sh` y `*.in` se guarden en el repositorio con LF.

```bash
sed -i 's/\r$//' tests/run_tests.sh tests/*.in
```

Las pruebas comprueban las partidas `ganar`, `perder`, `pociones`, `demo` e `invalida`, y que el juego termine bien si la entrada se acaba en cualquier punto de la partida ganadora.

Para generar de nuevo una simulacion:

```bash
./build/AventuraTextual < tests/ganar.in > docs/simulaciones/ganar.txt
```

En estos archivos no aparece lo que se escribe, porque la entrada viene de un archivo y la consola no la repite.

## Requisito del PDF y donde se cumple

| Requisito | Donde se cumple |
|---|---|
| Clase base abstracta `Entidad` con virtual puro `atacar()` | `src/Entidad.h` |
| `Jugador` hereda de `Entidad` y tiene inventario | `src/Jugador.h` |
| Al menos dos tipos de `Enemigo` con ataque propio | `Orco::atacar`, `Dragon::atacar` y `Nigromante::atacar` |
| Clase `Objeto` (`PocionDeVida`, `Espada`) | `src/Objeto.h`; se crean en `Juego::colocarObjetos` |
| `Jugador` guarda `std::vector<Objeto>` | atributo `inventario` de `Jugador` |
| `Habitacion` con descripcion, punteros a `Enemigo` y salidas | `src/Habitacion.h` |
| Habitacion inicial y movimiento entre habitaciones | `Juego::construirMundo`, `Juego::moverse` |
| Combate por turnos simple al encontrar enemigos | `Juego::combatir`, `Juego::contraatacar` |
| Usar objetos del inventario | `Jugador::usarObjeto`, `Juego::gestionarInventario` |
| Los 4 pilares de la POO | `docs/diseno.md` y `docs/guia-sustentacion.md` |
| Asociacion, agregacion y composicion | `docs/uml.md` |
| `std::vector` y `std::map` | `Habitacion`, `Jugador`, `Juego` |
| Memoria dinamica con punteros para el polimorfismo | `std::vector<Enemigo*>` en `Juego`; `new` en `Juego::colocarEnemigos`, `delete` en `Juego::~Juego` |
| Bonus: niveles y experiencia | `Jugador::ganarExperiencia`, `Jugador::subirNivel`, `Enemigo::getRecompensaXp` |
| Bonus: jefe final | `src/Nigromante.h`, `src/Nigromante.cpp`; Sala del Trono en `Juego::crearHabitaciones` |

## Elementos usados que no aparecen en lo visto en clase

El material del curso no estaba disponible al escribir el codigo, asi que esta lista sale de las restricciones del proyecto y de lo que suele ser mas avanzado. **El equipo debe revisarla contra sus apuntes** y quitar lo que si se haya visto.

| Elemento | Donde | Por que hace falta |
|---|---|---|
| `enum class` | `TipoObjeto` en `Objeto.h` | Nombra los tipos de objeto sin usar numeros magicos. |
| `std::getline` | `leerLinea` en `Entrada.cpp` | Lee lineas completas, incluso vacias, sin dejar datos en el buffer. |
| `std::stoi` | `leerOpcion` en `Entrada.cpp` | Convierte a entero, solo despues de validar que son digitos y que son pocos. |
| `std::vector::erase` y `begin()` | `Jugador::usarObjeto`, `Habitacion::retirarObjeto` | Quita un elemento de un vector por su indice. |
| `std::pair` | recorridos del `std::map` en `Habitacion::mostrarSalidas` y `Juego::elegirDestino` | Es el tipo de cada elemento de un `std::map`: `first` es la clave y `second` el valor. |
| `static_cast<int>` | comparaciones con `size()` | Convierte el tamano sin signo a `int` para evitar avisos del compilador. |
| `std::string::back`, `pop_back` | `leerLinea` | Quitan el `\r` final de archivos guardados en Windows. |
