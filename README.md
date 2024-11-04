
# :uk: Conway's Game of Life

Toroidal implementation of "Conway's Game of Life" in C++.

Dependencies:
* Armadillo 12.8.0 or later
* SFML 2.5.1

Known issues:
* Interface has errors on setups with multiple displays
* Game speed its limited by computation power, noticeable on big boards

Controls:

* `Esc`: close game
* `Numeric keys`: select predefined structure
* `Left mouse button`: change cell
* `Right mouse button`: place selected structure
* `R`: randomize board
* `P`: pause
* `Espacio`: run one step
* `C`: clear board
* `S`: save game
* `T`: rotate selection
* `M`: mirror selection
* `Up` / `Down`: increase / decrease game speed
* `Left` / `Right`: increase / decrease amount of random cells

Console arguments:

* `file.txt` (required): defines the name of the save file. If it exists the game tries to load it
* `size` (optional): integer that defines board size. By default its 100. This arguments is ignores of the game is loaded
* Examples:
  * ./main save.txt
  * ./main save.txt 200

Supported operating systems:

Armadillo and SFML are multi-platform, available for Linux, Windows and MacOs, for linux the given makefile compiles the project with g++

I wanted to include a build system like Cmake, but i will put that on hold in favor of continuing to practice C++

# :es: Juego de la vida de Conway

Implementación toroidal del "Juego de la Vida de Conway" en C++

Dependencias:

* Armadillo 12.8.0 o superior
* SFML 2.5.1

Problemas conocidos:

* La interfaz tiene errores al usar multiples pantallas
* La velocidad del juego puede verse limitada por la capacidad de computo, notable en tableros grandes

Controles:

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

Argumentos de consola:

* `archivo.txt` (obligatorio): define el nombre del archivo txt en el que se guardara partida. Si existe, se carga la partida
* `tamaño` (opcional): un entero que establece que tan grande es el tablero de juego. Por defecto es 100. Este argumento se ignora si se esta cargando una partida existente
* Ejemplos:
  * ./main guardado.txt
  * ./main guardado.txt 200

Sistemas operativos soportados:

Armadillo y SFML son multiplataforma, estan disponibles para Linux, Windows y MacOs, para linux se deja diponible el archivo makefile que compila el proyecto usando g++

Inicialmente tenia la idea de incluir un sistema de build como Cmake, pero es algo que dejare pendiente en pos de seguir practicando C++