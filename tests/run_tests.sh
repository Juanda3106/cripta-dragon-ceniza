#!/usr/bin/env bash
# Pruebas de aceptacion de La Cripta del Dragon de Ceniza.
# Uso (desde cualquier carpeta):  bash tests/run_tests.sh [ruta/al/ejecutable]
# Sin argumento busca el ejecutable en build/ y en cmake-build-debug/.
# Termina con codigo distinto de 0 si alguna verificacion falla.

RAIZ="$(cd "$(dirname "$0")/.." && pwd)"
PRUEBAS="$RAIZ/tests"
LIMITE_SEGUNDOS=10

EJECUTABLE="$1"
if [ -z "$EJECUTABLE" ]; then
    for candidato in "$RAIZ/build/AventuraTextual" "$RAIZ/build/AventuraTextual.exe" \
                     "$RAIZ/cmake-build-debug/AventuraTextual" "$RAIZ/cmake-build-debug/AventuraTextual.exe"; do
        if [ -f "$candidato" ]; then
            EJECUTABLE="$candidato"
            break
        fi
    done
fi
if [ ! -f "$EJECUTABLE" ]; then
    echo "No se encontro el ejecutable. Compila primero o pasalo como argumento."
    exit 2
fi
echo "Ejecutable: $EJECUTABLE"

FALLOS=0
SALIDA=""
CODIGO=0

ok()    { echo "  ok    $1"; }
fallo() { echo "  FALLO $1"; FALLOS=$((FALLOS + 1)); }

# Corre el juego con la entrada indicada. timeout detecta un posible bucle infinito.
jugar() {
    SALIDA="$(timeout "$LIMITE_SEGUNDOS" "$EJECUTABLE" < "$1")"
    CODIGO=$?
}

espera_texto() {
    if printf '%s\n' "$SALIDA" | grep -qF -- "$1"; then
        ok "contiene: $1"
    else
        fallo "falta el texto: $1"
    fi
}

no_espera_texto() {
    if printf '%s\n' "$SALIDA" | grep -qF -- "$1"; then
        fallo "no deberia aparecer: $1"
    else
        ok "no contiene: $1"
    fi
}

espera_cuenta() {
    local cuenta
    cuenta="$(printf '%s\n' "$SALIDA" | grep -cF -- "$1")"
    if [ "$cuenta" -eq "$2" ]; then
        ok "$2 veces: $1"
    else
        fallo "se esperaban $2 veces y hubo $cuenta: $1"
    fi
}

espera_codigo_cero() {
    if [ "$CODIGO" -eq 0 ]; then
        ok "codigo de salida 0"
    else
        fallo "codigo de salida $CODIGO"
    fi
}

echo "== ganar =="
jugar "$PRUEBAS/ganar.in"
espera_codigo_cero
espera_texto "Heroe queda con 103/120 de vida."
espera_texto "Heroe gana 20 puntos de experiencia."
espera_texto "Ataque total: 18."
espera_texto "!Heroe sube al nivel 2! Vida maxima: 140, ataque base: 15."
espera_texto "Cripta Profunda | Nivel: 2 | Vida: 95/140"
espera_texto "aliento de fuego"
espera_texto "Heroe queda con 51/140 de vida."
espera_texto "Cenizo ha sido derrotado."
espera_texto "Heroe gana 60 puntos de experiencia."
espera_texto "!Heroe sube al nivel 3! Vida maxima: 160, ataque base: 18."
espera_texto "Camara del Dragon | Nivel: 3 | Vida: 71/160"
no_espera_texto "El dragon cae"
espera_texto "Heroe (nivel 3): 71/160"
espera_cuenta "lanza un rayo oscuro a Heroe (10 de dano)." 2
espera_cuenta "drena la vida de Heroe (10 de dano) y recupera 10 de vida." 2
espera_texto "Morgrath ha sido derrotado."
espera_texto "Heroe queda con 31/160 de vida."
espera_texto "El nigromante se desploma y su magia oscura se disipa. La cripta queda en silencio. Has liberado el valle. VICTORIA"
no_espera_texto "DERROTA"

echo "== perder =="
jugar "$PRUEBAS/perder.in"
espera_codigo_cero
espera_texto "Heroe queda con 103/120 de vida."
espera_texto "entra en furia"
espera_texto "!Heroe sube al nivel 2! Vida maxima: 140, ataque base: 15."
espera_texto "Cripta Profunda | Nivel: 2 | Vida: 68/140"
espera_cuenta "El dragon Cenizo muerde a Heroe" 4
espera_texto "Heroe queda con 0/140 de vida."
espera_texto "Heroe ha sido derrotado."
espera_texto "DERROTA"
no_espera_texto "VICTORIA"

echo "== pociones =="
jugar "$PRUEBAS/pociones.in"
espera_codigo_cero
espera_texto "Heroe queda con 103/120 de vida."
espera_texto "recupera 17 puntos de vida (vida 120/120)."
espera_texto "Nivel: 1"
espera_texto "Experiencia: 20/50"
espera_texto "Abandonas la cripta. Hasta pronto."

echo "== demo =="
jugar "$PRUEBAS/demo.in"
espera_codigo_cero
espera_texto "!Heroe sube al nivel 2!"
espera_texto "aliento de fuego"
espera_texto "!Heroe sube al nivel 3!"
espera_texto "recupera 40 puntos de vida (vida 111/160)."
espera_texto "drena la vida de Heroe"
espera_texto "Heroe queda con 71/160 de vida."
espera_texto "VICTORIA"
no_espera_texto "DERROTA"

echo "== invalida =="
jugar "$PRUEBAS/invalida.in"
espera_codigo_cero
espera_cuenta "Opcion no valida." 4
espera_texto "Abandonas la cripta. Hasta pronto."

echo "== EOF a mitad de partida =="
# La partida ganadora se corta despues de cada linea: nunca debe colgarse ni fallar.
TOTAL_LINEAS="$(wc -l < "$PRUEBAS/ganar.in")"
CORTE="$(mktemp)"
CORTES_MALOS=0
for lineas in $(seq 0 "$TOTAL_LINEAS"); do
    head -n "$lineas" "$PRUEBAS/ganar.in" > "$CORTE"
    jugar "$CORTE"
    if [ "$CODIGO" -ne 0 ]; then
        echo "  corte en la linea $lineas: codigo $CODIGO"
        CORTES_MALOS=$((CORTES_MALOS + 1))
    fi
done
rm -f "$CORTE"
if [ "$CORTES_MALOS" -eq 0 ]; then
    ok "termina bien con la entrada cortada en cada una de las $TOTAL_LINEAS lineas"
else
    fallo "$CORTES_MALOS cortes terminaron mal"
fi

echo
if [ "$FALLOS" -eq 0 ]; then
    echo "TODAS LAS PRUEBAS PASARON"
    exit 0
fi
echo "PRUEBAS FALLIDAS: $FALLOS"
exit 1
