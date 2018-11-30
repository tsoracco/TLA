## Documentación
Se encuentra en el archivo `Informe.pdf`

## Requerimientos

Tener instalado gcc, touch, yacc y lex

## Para ejecutar el proyecto

```bash
git clone https://github.com/tsoracco/TLA.git && cd TLA
chmod 777 ./install.sh
./install.sh
chmod 777 ./compile.sh
```
Y luego, para compilar con un archivo en particular,
```bash
./compile.sh source.natt destination.c
```
donde source.natt es el archivo con extensión .natt a compilar, y destination.c es el archivo donde queda el resultado.


Finalmente, podrá ejecutar su código compilándolo con gcc o clang de manera habitual:

```bash
gcc destination.c -o destination
```

## Programas de ejemplo

Se encuentran en la carpeta `tests`

## Para generar los .c, compilar y ejecutar automáticamente los tests

```bash
chmod 777 ./generateAndRunTests.sh
./generateAndRunTests.sh
```
La salida de los 5 tests se verá en la consola.


## Autores
* Benenzon, Nicolás
* Soracco, Tomás
* Dallas, Tomás
* Atar, Marcos Ariel
