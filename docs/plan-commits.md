# Plan de commits

Los commits los hace **cada integrante con su propia cuenta de Git**, para que el historial muestre el trabajo real. Nadie hace commits a nombre de otro ni usa `--author`.

El historial debe mostrar el progreso: primero el MVP (WP1-WP6), despues los dos bonus (WP7 y WP8) y al final los documentos de sustentacion (WP9). Para eso hay tres carpetas de respaldo **hermanas** del proyecto (fuera del repositorio):

| Carpeta | Contenido |
|---|---|
| `../respaldo-1-mvp/` | Estado del MVP (version 1). Fuente de WP1-WP6. |
| `../respaldo-2-niveles/` | MVP + bonus A (niveles y experiencia). Fuente de WP7. |
| `../respaldo-3-final/` | Estado final (bonus A + bonus B + documentos). Fuente de WP8 y WP9. Es igual a la carpeta del proyecto al terminar la fase 2. |

## Preparacion (una sola vez)

Todos los comandos son para **Git Bash**, ejecutados dentro de la carpeta del proyecto.

1. Comprobar que el estado final esta completo en el respaldo (el comando no debe mostrar nada):

   ```bash
   diff -r --exclude=.git --exclude=.idea --exclude=cmake-build-debug --exclude=build ../respaldo-3-final .
   ```

2. Cada integrante configura **su propia** identidad en su computador, si no lo ha hecho:

   ```bash
   git config --global user.name "Su nombre"
   ```

   ```bash
   git config --global user.email "su-correo@ejemplo.com"
   ```

3. Vaciar la carpeta de trabajo, porque el repositorio todavia no tiene commits y los archivos se iran copiando por paquetes. **Solo despues de comprobar el paso 1.** No se borran `.git`, `.idea` ni `cmake-build-debug`:

   ```bash
   rm -rf src tests docs CMakeLists.txt README.md .gitignore .gitattributes
   ```

Si trabajan en computadores distintos con un repositorio remoto (GitHub), cada uno hace `git pull` antes de su paquete y `git push` despues.

Recomendacion: antes de cada commit, compilar y, desde WP5, correr `bash tests/run_tests.sh`. En WP1 a WP4 el `CMakeLists.txt` del MVP todavia nombra archivos que no existen, asi que CMake no compila hasta WP5. Si quieren comprobar esos paquetes, compilen a mano con `g++ -std=c++20 src/*.cpp`.

---

## WP1 Nucleo (MVP)

**Archivos:** `CMakeLists.txt`, `.gitignore`, `.gitattributes`, `src/Entidad.h`, `src/Entidad.cpp`, `src/Entrada.h`, `src/Entrada.cpp` y un `src/main.cpp` provisional.

```bash
R=../respaldo-1-mvp
mkdir -p src
cp $R/CMakeLists.txt $R/.gitignore $R/.gitattributes .
cp $R/src/Entidad.h $R/src/Entidad.cpp $R/src/Entrada.h $R/src/Entrada.cpp src/
```

Crear `src/main.cpp` provisional con este contenido:

```cpp
#include <iostream>

int main() {
    std::cout << "La Cripta del Dragon de Ceniza" << std::endl;
    return 0;
}
```

```bash
git add CMakeLists.txt .gitignore .gitattributes src/Entidad.h src/Entidad.cpp src/Entrada.h src/Entrada.cpp src/main.cpp
git commit -m "feat: agrega la clase abstracta Entidad, el modulo Entrada y la configuracion de CMake"
```

## WP2 Jugador y objetos (MVP)

**Archivos:** `src/Objeto.h`, `src/Objeto.cpp`, `src/Jugador.h`, `src/Jugador.cpp`.

```bash
R=../respaldo-1-mvp
cp $R/src/Objeto.h $R/src/Objeto.cpp $R/src/Jugador.h $R/src/Jugador.cpp src/
git add src/Objeto.h src/Objeto.cpp src/Jugador.h src/Jugador.cpp
git commit -m "feat: agrega la clase Objeto y el Jugador con su inventario"
```

## WP3 Enemigos (MVP)

**Archivos:** `src/Enemigo.h`, `src/Enemigo.cpp`, `src/Orco.h`, `src/Orco.cpp`, `src/Dragon.h`, `src/Dragon.cpp`.

```bash
R=../respaldo-1-mvp
cp $R/src/Enemigo.* $R/src/Orco.* $R/src/Dragon.* src/
git add src/Enemigo.h src/Enemigo.cpp src/Orco.h src/Orco.cpp src/Dragon.h src/Dragon.cpp
git commit -m "feat: agrega la clase abstracta Enemigo, el Orco y el Dragon"
```

## WP4 Mundo (MVP)

**Archivos:** `src/Habitacion.h`, `src/Habitacion.cpp`.

```bash
R=../respaldo-1-mvp
cp $R/src/Habitacion.h $R/src/Habitacion.cpp src/
git add src/Habitacion.h src/Habitacion.cpp
git commit -m "feat: agrega la clase Habitacion con salidas, enemigos y objetos"
```

## WP5 Juego (MVP)

**Archivos:** `src/Juego.h`, `src/Juego.cpp` y el `src/main.cpp` final (reemplaza al provisional). Desde aqui el proyecto compila con CMake.

```bash
R=../respaldo-1-mvp
cp $R/src/Juego.h $R/src/Juego.cpp $R/src/main.cpp src/
git add src/Juego.h src/Juego.cpp src/main.cpp
git commit -m "feat: agrega la clase Juego con la exploracion y el combate por turnos"
```

## WP6 Documentacion y pruebas (MVP)

**Archivos:** `README.md`, todo `docs/` y todo `tests/` del MVP.

```bash
R=../respaldo-1-mvp
cp -r $R/README.md $R/docs $R/tests .
git add README.md docs tests
git commit -m "docs: agrega el README, el UML, el guion, el diseno y las pruebas del MVP"
```

---

## WP7 Niveles y experiencia (bonus A)

Diferencias entre `../respaldo-1-mvp/` y `../respaldo-2-niveles/`:

- **Codigo:** `src/Enemigo.h`, `src/Enemigo.cpp` (`recompensaXp`), `src/Orco.cpp`, `src/Dragon.cpp` (su recompensa), `src/Jugador.h`, `src/Jugador.cpp` (`nivel`, `experiencia`, `ganarExperiencia`, `subirNivel`), `src/Juego.cpp` (dar la XP y mostrar el nivel).
- **Pruebas:** `tests/ganar.in`, `tests/perder.in`, `tests/run_tests.sh`.
- **Documentos:** `docs/uml.md`, `docs/guion.md`, `docs/simulaciones/ganar.txt`, `docs/simulaciones/perder.txt`, `docs/simulaciones/pociones.txt`.

```bash
R=../respaldo-2-niveles
ARCHIVOS="src/Enemigo.h src/Enemigo.cpp src/Orco.cpp src/Dragon.cpp src/Jugador.h src/Jugador.cpp src/Juego.cpp tests/ganar.in tests/perder.in tests/run_tests.sh docs/uml.md docs/guion.md docs/simulaciones/ganar.txt docs/simulaciones/perder.txt docs/simulaciones/pociones.txt"
for f in $ARCHIVOS; do cp "$R/$f" "$f"; done
git add $ARCHIVOS
git commit -m "feat: agrega niveles y experiencia al jugador"
```

Si quieren dos commits, primero el codigo (`feat: agrega niveles y experiencia al jugador`) y despues pruebas y documentos (`test: actualiza las pruebas con niveles y experiencia`).

## WP8 Jefe Nigromante y Sala del Trono (bonus B)

Diferencias entre `../respaldo-2-niveles/` y el estado final, **sin** los documentos de WP9:

- **Codigo nuevo:** `src/Nigromante.h`, `src/Nigromante.cpp`.
- **Codigo que cambia:**
  - `CMakeLists.txt` agrega `Nigromante.*`.
  - `src/Juego.h` y `src/Juego.cpp`: Sala del Trono, nueva victoria y division en metodos cortos.
  - `src/Habitacion.h` y `src/Habitacion.cpp`: se quita `getSalida`.
  - Los demas `.h` y `.cpp` (`Entidad.*`, `Entrada.h`, `Objeto.h`, `Jugador.*`, `Enemigo.h`, `Orco.*`, `Dragon.h`) solo cambian sus comentarios: lineas `Relaciones:`, `Para sustentar:` y `PILAR - ...`.
- **Pruebas:** `tests/ganar.in`, `tests/run_tests.sh` y el nuevo `tests/demo.in`.
- **Documentos actualizados:** `README.md`, `docs/uml.md`, `docs/guion.md`, `docs/diseno.md` (con "Cambios de la fase 2"), `docs/simulaciones/*.txt` (incluye el nuevo `demo.txt`).

```bash
R=../respaldo-3-final
ARCHIVOS="CMakeLists.txt src/Nigromante.h src/Nigromante.cpp src/Juego.h src/Juego.cpp src/Habitacion.h src/Habitacion.cpp src/Entidad.h src/Entidad.cpp src/Entrada.h src/Objeto.h src/Jugador.h src/Jugador.cpp src/Enemigo.h src/Orco.h src/Orco.cpp src/Dragon.h tests/ganar.in tests/demo.in tests/run_tests.sh README.md docs/uml.md docs/guion.md docs/diseno.md docs/simulaciones/ganar.txt docs/simulaciones/perder.txt docs/simulaciones/pociones.txt docs/simulaciones/demo.txt"
for f in $ARCHIVOS; do cp "$R/$f" "$f"; done
git add $ARCHIVOS
git commit -m "feat: agrega el jefe Nigromante y la Sala del Trono"
```

Si quieren separar, un commit para el codigo (`feat: agrega el jefe Nigromante y la Sala del Trono`) y otro para pruebas y documentos (`docs: actualiza UML, guion, diseno y pruebas con el Nigromante`).

## WP9 Documentos de sustentacion

**Archivos:** `docs/recorrido-del-codigo.md` y `docs/guia-sustentacion.md` (nuevos), `docs/plan-commits.md` y `docs/reparto-trabajo.md` (actualizados).

```bash
R=../respaldo-3-final
ARCHIVOS="docs/recorrido-del-codigo.md docs/guia-sustentacion.md docs/plan-commits.md docs/reparto-trabajo.md"
for f in $ARCHIVOS; do cp "$R/$f" "$f"; done
git add $ARCHIVOS
git commit -m "docs: agrega el recorrido del codigo y la guia de sustentacion"
```

---

## Comprobacion final

Al terminar WP9, la carpeta debe ser igual al estado final. Este comando no debe mostrar nada:

```bash
diff -r --exclude=.git --exclude=.idea --exclude=cmake-build-debug --exclude=build ../respaldo-3-final .
```

Despues:

1. Completar los `[POR COMPLETAR]` de `README.md` y `docs/reparto-trabajo.md`, compilar, correr `bash tests/run_tests.sh` y hacer un ultimo commit: `docs: completa el reparto del trabajo`.
2. `git log --oneline` debe mostrar los paquetes en orden, cada uno con el autor que lo hizo.
