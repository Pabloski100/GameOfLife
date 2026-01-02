# :uk: Conway's Game of Life

Toroidal implementation of "Conway's Game of Life" in C++.

## Last Changes

- The repo owner finally learned some elemental Cmake and now the game is easier to build

## Dependencies:
* Armadillo 12.8.0 or later
* SFML 2.5.X or 2.6.X

## How to build and run the game (Linux)

1. Install system wide dependencies

The game depends on Armadillo for matrix operations, and needs to be installed system-wide, on linux you can run:

`sudo apt install libarmadillo-dev`

Also, for now is also necessary to install OpenAL, an audio API. The game currently doesn't use audio, but the current build process needs OpenAL to be available (i must look up how to disable the audio part of SFML on te build), run:

`sudo apt install libopenal-dev`

2. Build

In the base of this repository, run:

`cmake -S src -B build`

then:

`cmake --build build`

3. Execute

If everything went ok, you should see an executable called `gof` inside the build directory, run it and play

## How to install and run (Windows and MacOs)

The dependencies used are cross platform, so the game should be able to run on Windows and MacOs. I cant provide specific instructions since i have not built C++ projects on those operating systems, yet i guess the overall steps are the same as linux:

1. Install Armadillo
2. Install SFML dependencies if necessary
3. Build with Cmake


## Known issues:
* Interface has errors on setups with multiple displays
* Game speed its limited by computation power, noticeable on big boards

## Controls:

* `Esc`: close game
* `Numeric keys`: select predefined structure
* `Left mouse button`: change cell
* `Right mouse button`: place selected structure
* `R`: randomize board
* `P`: pause
* `Space bar`: run one step
* `C`: clear board
* `S`: save game
* `T`: rotate selection
* `M`: mirror selection
* `Up` / `Down`: increase / decrease game speed
* `Left` / `Right`: increase / decrease amount of random cells

## Console arguments:

* `file.txt` (required): defines the save file name. If it exists the game tries to load it
* `size` (optional): integer that defines board size, 100 by default. This argument is ignored if the game is loaded
* Examples:
  * ./main save.txt
  * ./main save.txt 200

# :es: Juego de la vida de Conway

Implementación toroidal del "Juego de la Vida de Conway" en C++

## Últimos cambios

- El dueño del repo finalmente aprendió algo de Cmake y es más fácil correr el juego

## Dependencias:
* Armadillo 12.8.0 o mayor
* SFML 2.5.X o 2.6.X

## Como hacer build y correr el juego (Linux)

1. Instalar dependencias a nivel de sistema

El juego depende en Armadillo para operaciones matriciales, y necesita ser instalado a nivel de sistema, ne linux se puede correr:

`sudo apt install libarmadillo-dev`

También, por ahora es necesario instalar una API de audio llamada OpenAL, El juego actualmente no ocupa audio, pero el proceso de build necesita OpenAL (debo buscar como desactivar la parte de audio de SFML en la build), puedes correr:

`sudo apt install libopenal-dev`

2. Build

En la base de este repositorio, corre:

`cmake -S src -B build`

Luego:

`cmake --build build`

3. Ejecuta

Si todo salio bien, deberías poder ver un ejecutable llamado `gof` dentro de la carpeta build, ejecútala y juega

## Como hacer build y correr el juego (Windows y MacOs)

Las dependencias usadas son multiplataforma, por lo tanto el juego debería poder correr en Windows y MacOs. No puedo dar instrucciones especificas ya que no hecho build de proyectos C++ en esos sistemas operativos, pero imagino los pasos son similares a los de linux:

1. Instala Armadillo
2. Instala dependencias de SFML si es necesario
3. Hacer build con Cmake

## Problemas conocidos:

* La interfaz tiene errores al usar multiples pantallas
* La velocidad del juego puede verse limitada por la capacidad de computo, notable en tableros grandes

## Controles:

* `Esc`: cerrar juego
* `Teclas numericas`: seleccionar una estructura predefinida
* `Boton izquierdo del mouse`: cambiar celda
* `Boton derecho del mouse`: colocar estructura seleccionada
* `R`: generar tablero aleatorio
* `P`: pausar
* `Espacio`: avanzar un paso
* `C`: limpiar tablero
* `S`: guardar juego
* `T`: rotar selección
* `M`: reflejar selección
* `Arriba` / `Abajo`: aumentar / bajar la velocidad del juego
* `Izquierda` / `Derecha`: aumentar / bajar la cantidad de celdas al generar un tablero aleatorio

## Argumentos de consola:

* `archivo.txt` (obligatorio): define el nombre del archivo txt en el que se guardara partida. Si existe, se carga la partida
* `tamaño` (opcional): un entero que establece que tan grande es el tablero de juego. Por defecto es 100. Este argumento se ignora si se esta cargando una partida existente
* Ejemplos:
  * ./main guardado.txt
  * ./main guardado.txt 200