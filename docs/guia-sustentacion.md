# Guia de sustentacion

Integrantes: **Juan Sebastian Vasquez Pelaez** y **Juan David Llanos Micolta**.

El reparto de este guion es una **propuesta**: cambienlo segun quien conozca mejor cada parte (ver `docs/reparto-trabajo.md`). Lo importante es que los dos puedan responder cualquier pregunta.

---

## 1. Guion de 10 minutos

| Minuto | Quien | Tema | Que se muestra en pantalla |
|---|---|---|---|
| 0:00 - 1:00 | Juan Sebastian | **Idea y reglas.** Premisa (nigromante, dragon, cripta), mapa de 6 habitaciones, combate por turnos sin azar, objetos y los 2 bonus (niveles y jefe final). | `README.md` (mapa) o `docs/guion.md`. |
| 1:00 - 3:00 | Juan David | **UML.** Jerarquia `Entidad` -> `Jugador`/`Enemigo` -> `Orco`/`Dragon`/`Nigromante`. Las tres relaciones con ejemplos: composicion (`Juego` y sus punteros; `Jugador` y su inventario), agregacion (`Habitacion` - `Enemigo`), asociacion (salidas, `ubicacion`, `habitacionFinal`). | `docs/uml.md` renderizado. |
| 3:00 - 6:00 | Juan Sebastian (abstraccion y encapsulamiento) y Juan David (herencia y polimorfismo) | **Los 4 pilares en el codigo** (45 s cada uno): `Entidad.h` (virtual puro); `Entidad::recibirDanio` y `Jugador::subirNivel` (privado); constructor de `Nigromante` (llama a `Enemigo`); `Juego::contraatacar` (la linea del polimorfismo) junto a `Orco::atacar` y `Nigromante::atacar`. | CLion con esos archivos abiertos en pestanas. |
| 6:00 - 9:00 | Juan David juega, Juan Sebastian narra | **Demostracion en vivo** (seccion 2). | La consola del juego. |
| 9:00 - 10:00 | Juan Sebastian | **Memoria y cierre.** Quien hace `new` y quien hace `delete` (`Juego::~Juego`), por que `Habitacion` no libera, destructor virtual; pruebas automaticas (`bash tests/run_tests.sh`). Ideas para mejorar. | `Juego::~Juego` y la salida de `run_tests.sh`. |

Consejo: tengan las pestanas de CLion abiertas **antes** de empezar, en el orden en que se muestran.

---

## 2. Guion de la demostracion en vivo

Partida corta y segura, con resultado conocido: `tests/demo.in`. **Si algo sale mal o falta tiempo**, ejecuten la partida completa sin teclear:

```bash
./build/AventuraTextual < tests/demo.in
```

(si compilaron con CLion, el ejecutable es `./cmake-build-debug/AventuraTextual.exe`) y vayan bajando por la salida. Esa salida esta guardada en `docs/simulaciones/demo.txt`.

| # | Escribir | Que pasa | Pausa para explicar |
|---|---|---|---|
| 1 | `Heroe` | Nombre. Aparece la Entrada de la Cripta. | - |
| 2 | `3`, `1` | Recoge la Pocion de Vida. | **Composicion por valor:** el objeto se copia del vector de la habitacion al vector del jugador (`Juego::recogerObjeto`). |
| 3 | `2`, `1` | Va al norte, al Salon. El combate con Gruk empieza solo. | **Asociacion:** `ubicacion` cambia a otra habitacion. |
| 4 | `1`, `1`, `1` | Tres ataques. En el 2.o, Gruk entra en furia (10 de dano). Gruk muere: `Heroe gana 20 puntos de experiencia.` Vida 103/120. | **Polimorfismo:** el contraataque es `Orco::atacar` llamado desde `Juego::contraatacar`. |
| 5 | `2`, `1` | Va al este, a la Armeria. | - |
| 6 | `3`, `1` | Recoge la Espada de Hierro. | - |
| 7 | `4`, `2` | Equipa la espada: `Ataque total: 18.` | Se usa un **indice** del inventario, no un puntero. |
| 8 | `2`, `1` | Vuelve al Salon (oeste). | - |
| 9 | `2`, `2` | Va al norte, a la Cripta. Combate con Brak y Zug. | **Agregacion:** la habitacion tiene 2 punteros a enemigos que no son suyos. |
| 10 | `1`, `1` y `1`, `1` | Ataca a Brak dos veces (elige objetivo 1). Brak muere: +20 XP. | Los muertos no contraatacan: `retirarEnemigosDerrotados`. |
| 11 | `1` y `1` | Solo queda Zug (objetivo automatico). Zug muere: `!Heroe sube al nivel 2! Vida maxima: 140, ataque base: 15.` Vida 95/140. | **Bonus A, encapsulamiento:** `subirNivel` es privado; `Juego` solo llama a `ganarExperiencia`. |
| 12 | `2`, `1` | Va al norte, a la Camara del Dragon. | - |
| 13 | `1` cuatro veces | El dragon muerde (12, 12) y en el **3er** ataque escupe fuego (20). Muere al 4.o golpe: +60 XP, **nivel 3**. Vida 71/160. Victoria? **No**: el dragon ya no es el jefe final. | **Polimorfismo:** misma llamada, `Dragon::atacar`. |
| 14 | `4`, `1` | Bebe la pocion: `recupera 40 puntos de vida (vida 111/160)`. | `usarObjeto` devuelve `true` y la pocion se borra del vector. |
| 15 | `2`, `1` | Va al norte, a la Sala del Trono. Combate con Morgrath. | **Bonus B.** |
| 16 | `1` cinco veces | Rayo oscuro (10), **drenaje** (10 de dano y se cura 10), rayo, drenaje. Morgrath muere al 5.o golpe. Texto de **VICTORIA**. Vida final 71/160. | **Lo mas importante:** al agregar `Nigromante`, `Juego::contraatacar` **no cambio ni una linea**. |

Duracion aproximada: 3 minutos si se teclea sin detenerse demasiado en los pasos 5 a 8.

---

## 3. Pilares y relaciones: donde se ven

| Concepto | Clase y metodo donde se ve |
|---|---|
| Abstraccion | `Entidad::atacar` (virtual puro, `= 0`); `Enemigo::getTipo` (virtual puro). |
| Encapsulamiento | Atributos `private` en `Jugador`, `Enemigo`, `Objeto`, `Habitacion`, `Juego`. `Entidad::recibirDanio` y `Entidad::curar` (la vida siempre queda entre 0 y el maximo). `Jugador::subirNivel` (privado). `Jugador::getInventario` devuelve una referencia `const`. |
| Herencia | `class Jugador : public Entidad`, `class Enemigo : public Entidad`, `class Orco/Dragon/Nigromante : public Enemigo`. Constructores encadenados: `Nigromante::Nigromante` -> `Enemigo::Enemigo` -> `Entidad::Entidad`. |
| Polimorfismo | `Juego::contraatacar`: `enemigo->atacar(*this->jugador)`. Implementaciones: `Orco::atacar`, `Dragon::atacar`, `Nigromante::atacar`, `Jugador::atacar`. Destructor virtual en `Entidad` y `Enemigo`. |
| Composicion | `Juego` -> `Jugador`, `Habitacion`, `Enemigo` (`new` en `Juego::iniciar`, `Juego::crearHabitacion`, `Juego::colocarEnemigos`; `delete` en `Juego::~Juego`). `Jugador::inventario` y `Habitacion::objetos` (`std::vector<Objeto>` por valor). |
| Agregacion | `Habitacion::enemigos` (`std::vector<Enemigo*>`): se llena en `Juego::colocarEnemigo` y se vacia en `Habitacion::retirarEnemigosDerrotados`, sin `delete`. |
| Asociacion | `Habitacion::salidas` (`std::map<std::string, Habitacion*>`, llenado con `Habitacion::conectar`); `Jugador::ubicacion` (`Jugador::setUbicacion`); `Juego::habitacionFinal` (usado en `Juego::comprobarVictoria`). |

---

## 4. Preguntas probables del profesor

**1. Por que `Entidad` es abstracta?**
Porque tiene un metodo virtual puro: `virtual void atacar(Entidad& objetivo) = 0;`. No tiene sentido una "entidad generica" que no sepa atacar: siempre es un jugador o un enemigo concreto. El compilador no deja crear objetos de una clase abstracta; solo se pueden usar punteros o referencias a ella.

**2. Que pasaria si los destructores no fueran virtuales?**
En `Juego::~Juego` se hace `delete enemigo` con un `Enemigo*`. Sin destructor virtual, C++ llamaria solo al destructor de `Enemigo` (o de `Entidad`) y no al del tipo real (`Orco`, `Dragon`...). Eso es comportamiento indefinido y puede dejar memoria sin liberar. Con `virtual ~Entidad()`, `delete` destruye el objeto completo.

**3. Quien hace `delete` de cada cosa?**
Solo `Juego::~Juego`: libera el jugador, las 6 habitaciones y los 5 enemigos, cada uno una vez. Los objetos (`Objeto`) no se liberan a mano porque estan por valor dentro de vectores, y los vectores se liberan solos.

**4. Por que `Habitacion` no libera a sus enemigos?**
Porque no es su duena: es una **agregacion**. La habitacion solo registra que enemigos estan ahi. El dueno es `Juego`, que los guarda en su propio vector. Si la habitacion tambien hiciera `delete`, cada enemigo se liberaria dos veces y el programa podria fallar.

**5. Diferencia entre composicion, agregacion y asociacion, con ejemplos de este codigo.**
- *Composicion:* el todo crea y destruye a la parte. `Juego` crea con `new` y libera con `delete` al jugador, las habitaciones y los enemigos; `Jugador` contiene sus `Objeto` por valor.
- *Agregacion:* el todo agrupa partes que pueden existir sin el. `Habitacion` tiene `Enemigo*` pero no los crea ni los libera.
- *Asociacion:* solo "conoce" al otro. El jugador sabe en que habitacion esta (`ubicacion`) y cada habitacion sabe a cuales se conecta (`salidas`).

**6. Por que `std::vector<Objeto>` por valor y no punteros?**
Lo pide el enunciado y es lo mas simple: los objetos viven dentro del vector y se liberan solos, sin `new` ni `delete`. El costo es que `Objeto` no puede tener clases hijas: al guardarlas por valor se "rebanaria" la parte de la hija (*slicing*). Por eso hay un solo `Objeto` con un `TipoObjeto`.

**7. Por que se usan indices y no punteros a elementos del inventario?**
Cuando un `std::vector` crece o se le borra un elemento, puede mover sus elementos a otra zona de memoria. Un puntero guardado antes quedaria apuntando a memoria invalida. Un indice siempre se vuelve a buscar en el vector actual. Por eso `Jugador::usarObjeto` recibe un `int indice`.

**8. Por que `std::map` para las salidas?**
Porque una salida es una pareja *direccion -> habitacion* ("norte" -> Salon de Guardia), y eso es justo lo que guarda un map. Ademas recorre las claves en orden alfabetico, asi los menus siempre muestran las salidas en el mismo orden (este, norte, oeste, sur).

**9. En que linea esta el polimorfismo? Que pasaria si `atacar` no fuera virtual?**
En `Juego::contraatacar`: `enemigo->atacar(*this->jugador);`. `enemigo` es un `Enemigo*`, pero se ejecuta el `atacar` del objeto real. Si `atacar` no fuera virtual, C++ elegiria la version segun el tipo del puntero y no del objeto. Ademas, como `atacar` no tiene codigo en `Entidad`, ni siquiera compilaria: el virtual puro es lo que obliga a cada hija a implementarlo.

**10. Diferencia entre sobrescritura y sobrecarga.**
*Sobrescritura (override):* una clase hija redefine un metodo virtual del padre con la **misma firma**, como `Orco::atacar`; la version se elige en ejecucion. *Sobrecarga:* varios metodos con el mismo nombre y **distintos parametros** en la misma clase; se elige al compilar. En este proyecto hay sobrescritura (`atacar`, `getTipo`) y no hay sobrecarga propia.

**11. Que es el Stack y que es el Heap en este programa?**
El Stack guarda las variables locales: `Juego juego;` en `main`, o las pociones locales en `Juego::colocarObjetos`. Se liberan solas al salir de la funcion. El Heap guarda lo creado con `new`: el `Jugador`, las `Habitacion` y los `Enemigo`. Solo se liberan con `delete`, y eso lo hace `Juego::~Juego`.

**12. Como se conectan el `.h` y el `.cpp`?**
El `.h` declara la clase (atributos y firmas) y el `.cpp` la define (el codigo de cada metodo, con `Clase::metodo`). El `.cpp` hace `#include "Clase.h"`. Quien quiere usar la clase incluye solo el `.h`. CMake compila cada `.cpp` por separado y el enlazador los une. El header guard evita que un `.h` se lea dos veces.

**13. Para que sirve la forward declaration `class Habitacion;`?**
Para usar punteros a una clase sin incluir su `.h`. `Jugador.h` solo necesita saber que `Habitacion` existe para guardar un `Habitacion*`. Asi se evitan includes circulares y se compila menos. El `#include` real va en el `.cpp`, donde se llaman sus metodos.

**14. Como funciona la subida de nivel?**
Cuando un enemigo muere, `Juego::atacarEnemigo` llama a `jugador->ganarExperiencia(objetivo->getRecompensaXp())`. `ganarExperiencia` suma la XP y, mientras llegue a 50, resta 50 y llama al metodo privado `subirNivel`, que da +20 de vida maxima, +3 de ataque base y cura 20. Es un `while` y no un `if` por si en el futuro se gana XP para varios niveles de golpe.

**15. En que se diferencia el Nigromante del Orco y del Dragon?**
Los tres heredan de `Enemigo` y tienen la misma firma de `atacar`. El Orco depende de su propia vida (furia si le queda menos de la mitad). El Dragon cuenta sus ataques y cada 3.o hace mas dano. El Nigromante cuenta sus ataques y cada 2.o **se cura** lo mismo que hace de dano, usando `curar` (heredado de `Entidad`). Ademas es el jefe final y no da experiencia.

**16. Por que agregar el Nigromante no obligo a cambiar `Juego::contraatacar`?**
Porque `contraatacar` no pregunta de que tipo es cada enemigo: llama a `atacar` sobre un `Enemigo*` y el polimorfismo elige la version correcta. Solo hubo que crear la clase y ponerla en el mapa con `new Nigromante("Morgrath")` en `Juego::colocarEnemigos`. Esa es la ventaja del polimorfismo: se agrega comportamiento sin tocar el codigo que lo usa.

**17. Por que el jugador gana la XP antes de `retirarEnemigosDerrotados` y como sigue siendo valido el puntero?**
`retirarEnemigosDerrotados` solo quita el puntero del vector de la habitacion; no hace `delete`. El objeto sigue vivo en el Heap porque su dueno, `Juego`, todavia lo tiene en `this->enemigos`. Se da la XP antes por orden logico: primero se premia la victoria y despues se limpia la habitacion.

**18. Por que existe `Enemigo` si ya existe `Entidad`?**
Porque `Habitacion` y `Juego` necesitan un tipo comun solo para los enemigos (no para el jugador), con lo que solo ellos tienen: `getTipo` y la recompensa de experiencia. Asi `std::vector<Enemigo*>` no puede contener por error al jugador.

**19. Por que los atributos de `Entidad` son `protected` y los demas `private`?**
`protected` deja que las clases hijas los usen directamente (`Orco` lee `vida` para la furia; `Jugador::subirNivel` cambia `vidaMaxima` y `ataque`), pero los sigue ocultando del resto del programa. En las demas clases no hay hijas que los necesiten, asi que son `private`.

**20. Para que sirve `override`?**
Le dice al compilador "esto redefine un metodo virtual del padre". Si por error la firma no coincide (por ejemplo, falta un `const` o cambia un parametro), el compilador da error en vez de crear en silencio un metodo nuevo que nunca se llamaria.

**21. Como evita el programa colgarse con entradas invalidas o si se acaba la entrada?**
`leerOpcion` lee la linea completa, valida que sean solo digitos (y pocos) y que esten en el rango; si no, avisa y repite. Si se acaba la entrada devuelve `ENTRADA_AGOTADA` y cada menu lo trata como "salir". Las pruebas lo verifican cortando la partida en cada linea posible.

**22. Que es `this->`?**
Es un puntero al objeto que esta ejecutando el metodo. `this->vida` es la vida de *este* objeto. Se usa por convencion del curso y para distinguir un atributo de un parametro con el mismo nombre.

**23. Que se podria mejorar?**
Volver los objetos una jerarquia (armas, armaduras) con `std::vector<Objeto*>` y un dueno claro; guardar y cargar partida; dejar huir del combate; que los enemigos se muevan entre habitaciones (la agregacion ya lo permite); prohibir copiar `Juego`. No se hicieron para mantener el proyecto simple y dentro de lo visto en clase.

---

## 5. Glosario

| Termino | Significado simple |
|---|---|
| Clase | Molde que dice que datos y que acciones tiene un tipo de objeto. |
| Objeto (instancia) | Algo concreto creado a partir de una clase (Gruk es un objeto de la clase `Orco`). |
| Atributo | Dato que guarda cada objeto (`vida`, `nombre`). |
| Metodo | Funcion que pertenece a una clase (`atacar`, `curar`). |
| Constructor | Metodo que se ejecuta al crear el objeto y le da sus valores iniciales. |
| Lista de inicializacion | La parte `: nombre(nombre), vida(vida)` del constructor, que inicializa los atributos antes del cuerpo. |
| Destructor | Metodo (`~Clase`) que se ejecuta cuando el objeto se destruye. |
| Encapsulamiento | Ocultar los datos (`private`) y dejar cambiarlos solo con metodos que los validan. |
| Abstraccion | Mostrar que hace algo sin mostrar como; quedarse con lo esencial. |
| Clase abstracta | Clase con al menos un metodo virtual puro; no se pueden crear objetos de ella. |
| Metodo virtual puro | Metodo con `= 0` y sin codigo; obliga a las hijas a implementarlo. |
| Herencia | Una clase hija recibe los atributos y metodos de su padre ("es un"). |
| Polimorfismo | La misma llamada hace cosas distintas segun el tipo real del objeto. |
| `override` | Marca que un metodo redefine uno virtual del padre; el compilador lo comprueba. |
| Puntero | Variable que guarda la direccion de memoria de otro objeto (`Enemigo*`). |
| Referencia (`&`) | Otro nombre para un objeto que ya existe; evita copiarlo. |
| `nullptr` | Valor de un puntero que no apunta a nada. |
| Stack | Memoria de las variables locales; se libera sola al salir de la funcion. |
| Heap | Memoria que se pide con `new` y se libera con `delete`. |
| Fuga de memoria | Memoria del Heap que nunca se libera con `delete`. |
| Header guard | `#ifndef / #define / #endif` que evita leer un `.h` dos veces. |
| Forward declaration | `class X;`: avisa que la clase existe, para usar punteros sin incluir su `.h`. |

---

## 6. Trampas conocidas (lo que puede confundir y como explicarlo)

- **"Si un enemigo muere, por que no se hace `delete` en el combate?"** Porque la habitacion no es duena (agregacion). Solo se quita de su vector; `Juego` lo libera al final. Hacer `delete` antes dejaria un puntero colgante en `Juego::enemigos` y un doble `delete` en `~Juego`.
- **El mismo puntero esta en dos vectores** (`Juego::enemigos` y `Habitacion::enemigos`). No es un error: uno es el dueno y el otro solo lo registra. Ver `Juego::colocarEnemigo`.
- **`std::pair<const std::string, Habitacion*>` en los `for`.** Cada elemento de un `std::map` es una pareja: `first` es la clave ("norte") y `second` el valor (la habitacion). La clave es `const` porque un map no deja cambiar sus claves.
- **`static_cast<int>(vector.size())`.** `size()` devuelve un numero sin signo; se convierte a `int` para compararlo con indices y opciones sin avisos del compilador.
- **`opcion - 1`.** Los menus cuentan desde 1 y los vectores desde 0.
- **`curar(20)` en `subirNivel`.** Primero sube la vida maxima y despues cura, para que la curacion pueda llegar al nuevo tope.
- **El Nigromante se cura antes de que se le muestre el dano al jugador.** Es solo el orden de los mensajes: necesita saber cuanto se curo para escribirlo en la misma frase.
- **`ataque` vs `bonusAtaque`.** Subir de nivel cambia el ataque **base**; la espada da un bonus aparte. El dano del jugador es la suma.
- **La espada desaparece del inventario al equiparla.** Es una regla de esta version: el bonus queda en `bonusAtaque`.
- **`Enemigo.h` no declara `atacar`.** Lo hereda de `Entidad` todavia sin implementar; por eso `Enemigo` sigue siendo abstracta.
- **`XP_POR_NIVEL` esta en el `.h` y las otras constantes del jugador en el `.cpp`.** Es porque `Juego` tambien la usa para mostrar `Experiencia: X/50`.
- **Las simulaciones no muestran lo que se escribio.** La entrada viene de un archivo y la consola no la repite.
