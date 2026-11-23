# Guion del videojuego: La Cripta del Dragon de Ceniza

## Premisa

Un nigromante desperto a un dragon que incendio la aldea de un valle. Los dos se ocultan en una antigua cripta. El jugador baja a la cripta, vence al dragon y acaba con el nigromante, que espera en la Sala del Trono.

## Mapa (6 habitaciones)

```
        [Sala del Trono]      <- habitacion final (jefe: Nigromante)
               |
      [Camara del Dragon]     <- jefe intermedio: Dragon
               |
        [Cripta Profunda]
               |
 [Armeria] - [Salon de Guardia]
               |
        [Entrada de la Cripta]   <- inicio
```

Todas las conexiones se pueden recorrer en los dos sentidos. Las salidas se listan en orden alfabetico.

| Habitacion | Salidas |
|---|---|
| Entrada de la Cripta | norte: Salon de Guardia |
| Salon de Guardia | este: Armeria; norte: Cripta Profunda; sur: Entrada de la Cripta |
| Armeria | oeste: Salon de Guardia |
| Cripta Profunda | norte: Camara del Dragon; sur: Salon de Guardia |
| Camara del Dragon | norte: Sala del Trono; sur: Cripta Profunda |
| Sala del Trono | sur: Camara del Dragon |

## Habitaciones

| Habitacion | Descripcion | Enemigos | Objetos en el suelo |
|---|---|---|---|
| Entrada de la Cripta | Una puerta de piedra rota da paso a un vestibulo frio. Antorchas casi apagadas iluminan el camino hacia el norte. | - | Pocion de Vida |
| Salon de Guardia | Un salon amplio con bancos volcados. Huele a humo y a hierro oxidado. | Orco Gruk | - |
| Armeria | Estantes caidos y armaduras oxidadas. Algo brilla bajo una mesa. | - | Espada de Hierro; Pocion de Vida |
| Cripta Profunda | Sarcofagos abiertos y un frio que cala los huesos. Dos sombras se mueven entre las tumbas. | Orco Brak; Orco Zug | Pocion de Vida |
| Camara del Dragon | Una enorme caverna cubierta de ceniza. Sobre una montana de monedas, un dragon abre un ojo. | Dragon Cenizo | Pocion de Vida |
| Sala del Trono | Un trono de huesos domina la sala. Una figura encapuchada alza la cabeza: es el nigromante que desperto al dragon. | Nigromante Morgrath | - |

## Personajes

| Personaje | Vida | Ataque | Experiencia que da | Comportamiento |
|---|---|---|---|---|
| Jugador | 120 | 12 | - | Su dano es el ataque base mas el bonus del arma equipada. Usa objetos de su inventario y sube de nivel. |
| Orco (Gruk, Brak, Zug) | 36 | 7 | 20 | Golpea con su maza. Si le queda menos de la mitad de la vida entra en furia y hace 3 puntos mas de dano. |
| Dragon (Cenizo) | 80 | 12 | 60 | Muerde. Cada tercer ataque escupe su aliento de fuego y hace 8 puntos mas de dano (20 en total). |
| Nigromante (Morgrath) | 90 | 10 | 0 | Lanza un rayo oscuro. Cada segundo ataque usa **Drenaje**: hace su dano y se cura esa misma cantidad, sin pasar de su vida maxima. No da experiencia porque al derrotarlo termina la partida. |

## Niveles y experiencia

- El jugador empieza en el nivel 1 con 0 puntos de experiencia.
- Al derrotar a un enemigo gana la experiencia que ese enemigo vale.
- Cada 50 puntos sube un nivel: +20 de vida maxima, +3 de ataque base y se cura 20 puntos de vida. La experiencia que sobra se conserva.
- En una partida completa se llega al nivel 3: nivel 2 al derrotar a Zug (60 XP) y nivel 3 al derrotar al dragon (10 + 60 = 70 XP).

## Objetos

| Objeto | Tipo | Valor | Descripcion | Efecto |
|---|---|---|---|---|
| Pocion de Vida | `PocionDeVida` | 40 | Restaura 40 puntos de vida. | Cura hasta el maximo de vida. Con la vida llena no se gasta. |
| Espada de Hierro | `Arma` | 6 | Aumenta tu ataque en 6 puntos. | El bonus reemplaza al anterior y no se acumula. Al equiparla sale del inventario. |

## Condiciones de fin

- **Victoria:** derrotar al Nigromante en la Sala del Trono. Vencer al dragon ya no termina la partida.
- **Derrota:** la vida del jugador llega a 0.
- **Salida voluntaria:** elegir `0. Salir del juego` en el menu de exploracion.

## Textos

- **Introduccion:** Un nigromante desperto a un dragon que incendio tu aldea. Los dos se ocultan en la Cripta de Ceniza. Tu mision: bajar, vencer al dragon y acabar con el nigromante.
- **Victoria:** El nigromante se desploma y su magia oscura se disipa. La cripta queda en silencio. Has liberado el valle. VICTORIA
- **Derrota:** Tus fuerzas se agotan y todo se oscurece. El valle seguira esperando a un heroe. DERROTA
- **Salida voluntaria:** Abandonas la cripta. Hasta pronto.

## Partida de ejemplo

Salida real de `tests/pociones.in`. El jugador recoge la pocion, vence a Gruk (gana 20 de experiencia), se cura, mira su estado y sale del juego. Lo que escribe el jugador no aparece, porque la entrada viene de un archivo. Las partidas completas estan en `docs/simulaciones/`.

```
=== La Cripta del Dragon de Ceniza ===
Un nigromante desperto a un dragon que incendio tu aldea. Los dos se ocultan en la Cripta de Ceniza. Tu mision: bajar, vencer al dragon y acabar con el nigromante.
Como te llamas, aventurero?
=== Entrada de la Cripta ===
Una puerta de piedra rota da paso a un vestibulo frio. Antorchas casi apagadas iluminan el camino hacia el norte.
Enemigos: ninguno.
Objetos en el suelo: Pocion de Vida
Salidas: norte

Entrada de la Cripta | Nivel: 1 | Vida: 120/120
1. Mirar alrededor
2. Moverse
3. Recoger un objeto
4. Ver inventario / usar un objeto
5. Ver estado del jugador
0. Salir del juego
Elige una opcion:
1. Pocion de Vida - Restaura 40 puntos de vida.
0. Cancelar
Elige una opcion:
Recoges Pocion de Vida.

Entrada de la Cripta | Nivel: 1 | Vida: 120/120
1. Mirar alrededor
2. Moverse
3. Recoger un objeto
4. Ver inventario / usar un objeto
5. Ver estado del jugador
0. Salir del juego
Elige una opcion:
1. norte -> Salon de Guardia
0. Cancelar
Elige una opcion:
=== Salon de Guardia ===
Un salon amplio con bancos volcados. Huele a humo y a hierro oxidado.
Enemigos: Gruk (Orco, vida 36/36)
Objetos en el suelo: ninguno.
Salidas: este, norte, sur

--- COMBATE ---
Heroe (nivel 1): 120/120
1. Gruk (Orco) vida 36/36
1. Atacar
2. Usar un objeto
Elige una opcion:
Heroe ataca a Gruk con 12 de dano.
Gruk queda con 24/36 de vida.
El orco Gruk golpea con su maza a Heroe (7 de dano).
Heroe queda con 113/120 de vida.

--- COMBATE ---
Heroe (nivel 1): 113/120
1. Gruk (Orco) vida 24/36
1. Atacar
2. Usar un objeto
Elige una opcion:
Heroe ataca a Gruk con 12 de dano.
Gruk queda con 12/36 de vida.
El orco Gruk entra en furia y golpea a Heroe (10 de dano).
Heroe queda con 103/120 de vida.

--- COMBATE ---
Heroe (nivel 1): 103/120
1. Gruk (Orco) vida 12/36
1. Atacar
2. Usar un objeto
Elige una opcion:
Heroe ataca a Gruk con 12 de dano.
Gruk queda con 0/36 de vida.
Gruk ha sido derrotado.
Heroe gana 20 puntos de experiencia.
Has derrotado a todos los enemigos.

Salon de Guardia | Nivel: 1 | Vida: 103/120
1. Mirar alrededor
2. Moverse
3. Recoger un objeto
4. Ver inventario / usar un objeto
5. Ver estado del jugador
0. Salir del juego
Elige una opcion:
1. Pocion de Vida - Restaura 40 puntos de vida.
0. Volver
Elige una opcion:
Heroe bebe Pocion de Vida y recupera 17 puntos de vida (vida 120/120).

Salon de Guardia | Nivel: 1 | Vida: 120/120
1. Mirar alrededor
2. Moverse
3. Recoger un objeto
4. Ver inventario / usar un objeto
5. Ver estado del jugador
0. Salir del juego
Elige una opcion:
Nombre: Heroe
Nivel: 1
Experiencia: 20/50
Vida: 120/120
Ataque base: 12
Bonus de ataque: 0
Objetos: 0

Salon de Guardia | Nivel: 1 | Vida: 120/120
1. Mirar alrededor
2. Moverse
3. Recoger un objeto
4. Ver inventario / usar un objeto
5. Ver estado del jugador
0. Salir del juego
Elige una opcion:
Abandonas la cripta. Hasta pronto.
```
