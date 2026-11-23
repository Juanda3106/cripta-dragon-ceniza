# Diseno del proyecto

## Analisis en 4 pasos

- **Entradas:** nombre del jugador y numeros de opcion escritos por teclado.
- **Salidas:** textos de la historia, estado de las habitaciones, resultado de cada ataque, subidas de nivel y final de la partida.
- **Restricciones:** vida entre 0 y el maximo, opciones dentro del rango de cada menu, entrada que se puede agotar, memoria sin fugas, combate sin azar.
- **Proceso:** crear el mundo, explorar con un menu, combatir por turnos al encontrar enemigos, ganar experiencia y terminar en victoria, derrota o salida.

Del enunciado se sacaron los sustantivos como clases y atributos (jugador, enemigo, objeto, habitacion, vida, inventario, salidas, nivel) y los verbos como metodos (atacar, curar, usar, moverse, recoger, ganar experiencia).

## Pilares de la POO

| Pilar | Donde se demuestra |
|---|---|
| **Encapsulamiento** | Atributos `private` con getters en `Objeto`, `Habitacion`, `Jugador`, `Enemigo`, `Dragon`, `Nigromante` y `Juego`. Validaciones en los constructores de `Entidad`, `Objeto` y `Enemigo`, y en `Entidad::recibirDanio` y `Entidad::curar`. `Jugador::subirNivel` es privado: solo `Jugador::ganarExperiencia` cambia el nivel. Los atributos de `Entidad` son `protected`, solo para sus derivadas. |
| **Abstraccion** | `Entidad` y `Enemigo` son abstractas: `atacar()` y `getTipo()` son el contrato. No se puede crear una entidad generica ni un enemigo generico. |
| **Herencia** | `Jugador` y `Enemigo` heredan de `Entidad`; `Orco`, `Dragon` y `Nigromante` heredan de `Enemigo`. Los constructores se encadenan en la lista de inicializacion: `Nigromante` llama a `Enemigo` y `Enemigo` llama a `Entidad`. |
| **Polimorfismo** | `Juego::contraatacar` recorre un `std::vector<Enemigo*>` y llama a `enemigo->atacar(*this->jugador)`: corre `Orco::atacar`, `Dragon::atacar` o `Nigromante::atacar` segun el tipo real. Los destructores virtuales de `Entidad` y `Enemigo` hacen seguro el `delete` en `Juego::~Juego`. |

### Encapsulamiento

Cada clase protege sus datos y solo deja cambiarlos por sus metodos. Nadie puede poner la vida en un valor negativo, porque la unica forma de cambiarla es `recibirDanio` o `curar`, y los dos usan un ternario para mantenerla entre 0 y `vidaMaxima`. Lo mismo pasa con la subida de nivel: `subirNivel` es privado, asi que desde fuera solo se puede *dar experiencia* con `ganarExperiencia`, y es el propio jugador quien decide cuando sube y como cambian sus estadisticas. La unica excepcion son los atributos `protected` de `Entidad`, que usan sus derivadas: `Orco` lee `vida` para saber si entra en furia.

### Abstraccion

`Entidad` dice *que* puede hacer algo que pelea, pero no *como*. El metodo `atacar` es virtual puro, asi que la clase no se puede instanciar. `Enemigo` agrega otro contrato, `getTipo`, y tampoco implementa `atacar`, por lo que sigue siendo abstracta. `Juego` solo necesita saber que un enemigo ataca, tiene un tipo y vale cierta experiencia. No conoce los detalles de la furia, del aliento de fuego ni del drenaje.

### Herencia

Un jugador y un enemigo *son una* entidad: heredan nombre, vida, ataque, `recibirDanio`, `curar` y `estaVivo` sin repetir codigo. `Orco`, `Dragon` y `Nigromante` solo agregan lo que los hace distintos. Cada constructor derivado llama al de su base en la lista de inicializacion, con sus propias estadisticas. El Nigromante incluso reutiliza `curar`, heredado de `Entidad`, para su drenaje.

### Polimorfismo

El punto central esta en `Juego::contraatacar`. Todos los enemigos estan en un vector de punteros a `Enemigo`, y la linea `enemigo->atacar(*this->jugador)` es la misma para todos. En ejecucion, C++ mira el tipo real del objeto: un orco puede entrar en furia, un dragon cuenta sus ataques para escupir fuego y un nigromante drena vida. **La prueba esta en el bonus B:** al agregar la clase `Nigromante`, `Juego::contraatacar` no cambio ni una linea. Hacen falta punteros porque un `std::vector<Enemigo>` por valor no podria guardar derivadas, y ademas `Enemigo` es abstracta.

**Sobrescritura y sobrecarga:** `atacar` es *sobrescritura*: `Jugador`, `Orco`, `Dragon` y `Nigromante` lo redefinen con la misma firma y con `override`, y la version se elige en ejecucion. La *sobrecarga* seria tener varios metodos con el mismo nombre y distintos parametros en una clase, y se elige al compilar. El codigo del proyecto no define ninguna sobrecarga.

## Propiedad de la memoria

`Juego` es el unico que usa `new` y el unico que usa `delete`:

| Se crea con `new` en | Se libera con `delete` en |
|---|---|
| `Juego::iniciar` (`Jugador`) | `Juego::~Juego` |
| `Juego::crearHabitacion` (6 `Habitacion`) | `Juego::~Juego` |
| `Juego::colocarEnemigos` (3 `Orco`, 1 `Dragon`, 1 `Nigromante`) | `Juego::~Juego` |

Cada enemigo esta en dos vectores: el de `Juego`, que es el dueno, y el de su habitacion, que solo lo registra. Cuando un enemigo muere, `Habitacion::retirarEnemigosDerrotados` lo quita del vector de la habitacion sin liberarlo. Sigue en el vector de `Juego`, que lo libera una sola vez al final. Por eso `Juego::atacarEnemigo` puede pedirle su recompensa de experiencia despues de que murio.

`Juego` no se debe copiar: una copia tendria los mismos punteros y los liberaria dos veces. `main` crea un solo `Juego` y nunca lo copia.

## Decisiones de diseno

### Pedidas por la especificacion

- **`Objeto` es una sola clase con `TipoObjeto`.** El PDF exige `std::vector<Objeto>` por valor. Un vector asi no puede ser polimorfico: una derivada guardada en el se "rebanaria" (*slicing*) y perderia su parte propia. Si los objetos se vuelven una jerarquia, el inventario pasara a `std::vector<Objeto*>` con dueno explicito.
- **`Enemigo` es una clase intermedia.** El PDF pide que la habitacion guarde punteros a los `Enemigo`. Ademas agrupa lo que tienen en comun los enemigos y no el jugador: `getTipo` y la recompensa de experiencia.
- **`std::map` para las salidas.** Relaciona una direccion con una habitacion y recorre las claves en orden alfabetico, asi que los menus siempre salen igual.
- **`Juego` es el dueno de la memoria.** Tener un solo dueno evita fugas y dobles `delete`, y permite que un enemigo pueda cambiar de habitacion sin cambiar de dueno.
- **Combate determinista, sin aleatoriedad.** Los resultados se pueden calcular a mano y comprobar con pruebas automaticas, y la demostracion siempre sale igual.
- **Indices y no punteros a objetos del inventario.** Al crecer o achicarse un `std::vector<Objeto>` sus elementos se reubican y un puntero a ellos quedaria invalido.
- **Responsabilidades del bonus A repartidas.** El enemigo sabe cuanta experiencia vale (`getRecompensaXp`), el jugador sabe subir de nivel (`ganarExperiencia`, `subirNivel`) y `Juego::atacarEnemigo` solo los conecta.

### Tomadas por defecto, donde la especificacion no decia nada

- `leerOpcion` muestra el mensaje en su propia linea. Asi las simulaciones generadas con archivos se leen bien, aunque la entrada no aparezca en ellas.
- Textos propios, que la especificacion no fijaba: `Como te llamas, aventurero?`, `Elige una opcion:`, `A quien atacas?`, `Opcion no valida. Escribe un numero entre X y Y.` y `Recoges [objeto].`.
- El titulo se muestra como `=== La Cripta del Dragon de Ceniza ===`.
- La pantalla de estado usa las etiquetas `Nombre`, `Nivel`, `Experiencia`, `Vida`, `Ataque base`, `Bonus de ataque` y `Objetos`.
- Si el inventario esta vacio en combate se muestra `Tu inventario esta vacio.` y no se gasta el turno.
- La lista para elegir objetivo no tiene opcion de cancelar.
- Si la entrada se agota (EOF) en el menu principal o en el combate se muestra el texto de salida voluntaria y el juego termina. En los submenus se vuelve al menu anterior, que detecta el EOF.
- Al vencer al Nigromante se muestra `Has derrotado a todos los enemigos.` y despues el texto de victoria.
- `XP_POR_NIVEL` esta en `Jugador.h` (y no en el `.cpp`) porque `Juego` la necesita para mostrar `Experiencia: X/50`.
- El drenaje del Nigromante calcula primero cuanto se curo y despues aplica el dano al objetivo, para poder mostrar los dos numeros en el mismo mensaje.
- `leerLinea` quita un `\r` final y `.gitattributes` mantiene LF en `tests/`. Sin esto, un clon en Windows podria convertir `run_tests.sh` a CRLF y bash no podria ejecutarlo.

## Cambios de la fase 2

| Cambio | Archivos | Por que |
|---|---|---|
| **Bonus A.** `Enemigo` guarda `recompensaXp` (nuevo parametro del constructor y `getRecompensaXp`). Orco 20, Dragon 60. | `Enemigo.*`, `Orco.cpp`, `Dragon.cpp` | Cada enemigo sabe cuanto vale. |
| **Bonus A.** `Jugador` gana `nivel`, `experiencia`, `ganarExperiencia`, el privado `subirNivel` y los getters. | `Jugador.*` | Subir de nivel es responsabilidad del jugador y queda encapsulado. |
| **Bonus A.** `Juego::atacarEnemigo` da la experiencia antes de `retirarEnemigosDerrotados`; el menu, el estado y el combate muestran el nivel. | `Juego.cpp` | `Juego` solo conecta al enemigo con el jugador. |
| **Bonus B.** Nueva clase `Nigromante` (vida 90, ataque 10, XP 0, drenaje cada 2.o ataque). | `Nigromante.*`, `CMakeLists.txt` | Jefe final con habilidad propia; demuestra herencia y polimorfismo. |
| **Bonus B.** Sala del Trono al norte de la Camara del Dragon; es la nueva `habitacionFinal`. Pocion de Vida en la Camara. Nuevos textos de introduccion y victoria. | `Juego.cpp` | El dragon pasa a ser jefe intermedio. |
| Se quito `Habitacion::getSalida`. `Juego::elegirDestino` guarda los destinos en un vector mientras recorre el `std::map`. | `Habitacion.*`, `Juego.*` | Evita `find` y `const_iterator`, que eran dificiles de explicar y no hacian falta. |
| `Juego.cpp` dividido en metodos cortos: `construirMundo` llama a `crearHabitaciones`, `conectarHabitaciones` (con `conectarIdaYVuelta`), `colocarEnemigos` y `colocarObjetos`; las habitaciones se ubican con constantes `INDICE_...`. `menuExploracion` usa `mostrarMenuExploracion` y `ejecutarOpcionExploracion`. | `Juego.*` | Ninguna funcion pasa de 25 lineas; cada una se lee como una frase. |
| Las opciones de los menus son constantes (`OPCION_MIRAR`, `ACCION_ATACAR`...). | `Juego.cpp` | Sin numeros magicos en el `switch`. |
| Renombres: `mostrarObjetos` -> `mostrarObjetosNumerados`, `mostrarEnemigos` -> `mostrarEnemigosNumerados` (en `Juego`), `mostrarEstadoCombate` -> `mostrarMenuCombate`; `crearHabitacion` ya no devuelve el puntero. | `Juego.*` | No confundirlos con los metodos privados de `Habitacion` del mismo nombre, y que el nombre diga lo que hace. |
| Cada `.h` tiene las lineas `Relaciones:` y `Para sustentar:`; los pilares se marcan con `// PILAR - ...` y las relaciones con `// COMPOSICION:`, `// AGREGACION:`, `// ASOCIACION:`. | `src/*` | Facilitar el estudio y la sustentacion. |
| Pruebas reescritas con los numeros de la fase 2; `perder` necesita ahora 5 ataques al dragon; nueva partida `demo.in` para la sustentacion. | `tests/*`, `docs/simulaciones/*` | Verificar los dos bonus. |
| Documentos nuevos `recorrido-del-codigo.md` y `guia-sustentacion.md`; el resto de documentos actualizados al estado final. | `docs/*`, `README.md` | Estudiar y sustentar sin haber escrito el codigo. |
