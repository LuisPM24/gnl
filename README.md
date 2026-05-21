*Este proyecto ha sido creado como parte del currículo de 42 por lupalomi*

# Descripción
Este proyecto consiste en una función que retorns una línea de un `file descriptor` dado. De modo que, al ejecutarlo dentro de un bucle, sea capaz de retornar todas las líneas del archivo abierto.

Esta función utiliza las siguientes librerías:
- `unistd.h`: Para el uso de la función [read](https://man7.org/linux/man-pages/man2/read.2.html).
- `stdlib.h`: Para el uso de las funciones [malloc](https://www.man7.org/linux/man-pages/man3/free.3.html) y [free](https://man7.org/linux/man-pages/man3/free.3p.html).
- `limits.h`: Para la implementación de límites en `BUFFER_SIZE`.
- `stdio.h`: Para la implementación de límites de archivos abiertos **solo en la parte bonus**.

Un ejemplo de `main.c` es el siguiente:
```C
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    char    *str;
    int     fd;

    if (argc < 2)
        return (0);
    fd = open (argv[1], O_RDONLY);
    if (fd < 0)
        return (-1);
    str = get_next_line(fd);
    while (str)
    {
        printf("%s", str);
    	free(str);
        str = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```
Este `main.c` abre el archivo pasado por **`argv[1]`** e imprime todas sus líneas.

# Instrucciones

**ATENCIÓN: ESTE ARCHIVO NO INCLUYE MAKEFILE**

Para clonar este proyecto, se debe ejecutar la siguiente línea mediante una terminal, dentro de la carpeta en la que desea usar la función:

```Bash
git clone https://github.com/LuisPM24/gnl.git gnl
```

Posteriormente, se deberá incluir la siguiente línea en el proyecto donde se desea usar la función:

```C
#include "gnl/get_next_line.h"
```

Esta línea permite el uso de todas las funciones pertenecientes al repositorio clonado. Por ello, se recomienda incluir esta línea dentro de un archivo `.h` .

Al compilar, se puede usar `-D BUFFER_SIZE=100` para establecer la cantidad de carácteres que la función es capaz de manejar en cada llamada a la función `read`. Por defecto, este valor es `42`. **Esto no afecta al resultado devuelto de la función. Solo afecta al funcionamiento interno de la misma.**

# Recursos

Para realizar este proyecto se ha recurido a las siguientes herramientas y páginas web:

- Páginas `man` dentro de la propia terminal.
- [Linux Man Pages Online](https://man7.org/linux/man-pages/) para consultas relacionadas con la función [read](https://man7.org/linux/man-pages/man2/read.2.html).

Se requiere un compilador de C (como `cc`) y un sistema compatible con POSIX (Linux o macOS), ya que se utilizan cabeceras estándar como `<unistd.h>`.

**Este proyecto no ha usado IA generativa.**

# Bonus
La ***parte bonus*** de este proyecto consiste en que la función sea capaz de leer y devolver una línea de múltiples archivos de texto a la vez.

Para lograr este apartado, se usa la librería `stdio.h` que implementa la macro `FOPEN_MAX` para limitar la cantidad de archivos abiertos a la vez a un máximo de `256`.

Para implementar la ***parte bonus*** se deverá incluir en el archivo donde se desea usar esta función la siguiente línea:

```C
#include "gnl/get_next_line_bonus.h"
```

Un ejemplo de `main.c` es el siguiente:

```C
#include "get_next_line_bonus.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	char	*str;
	int		fd[2];
	int		active[2];

	if (argc < 3)
		return (1);
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
		return (1);
	fd[1] = open(argv[2], O_RDONLY);
	if (fd[1] < 0)
	{
		close(fd[0]);
		return (1);
	}
	active[0] = 1;
	active[1] = 1;
	while (active[0] || active[1])
	{
		if (active[0])
		{
			str = get_next_line(fd[0]);
			if (str)
			{
				printf("FD 0: %s", str);
				free(str);
			}
			else
				active[0] = 0;
		}
		if (active[1])
		{
			str = get_next_line(fd[1]);
			if (str)
			{
				printf("FD 1: %s", str);
				free(str);
			}
			else
				active[1] = 0;
		}
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}
```
En este `main.c`, se imprimen las primeras 3 líneas de los archivos pasados por `argv[1]` y `argv[2]`.

# Funciones
No existe una distinción entre la `parte obligatoria` y la `parte bonus` debido a que todas las funciones tienen los mismos parámetros y funcionan igual.

### get_next_line.h
Archivo cabecera (`header file`) en el que se incluyen todas las referencias a otras funciones de la parte obligatoria. Se encuentra declarado en todos los archivos `.c` de este repositorio mediante la línea:

```C
#include "get_next_line.h"
```

### get_next_line
Función que lee y devuelve la primera línea de un descriptor de archivo (`fd` o `file descriptor`). Tras la primera llamada, no pierde el puntero de referencia, lo que permite devolver varias líneas sin repetir ninguna.

```C
char	*get_next_line(int fd);
```

### ft_strdup
Función que duplica una cadena de texto `char *` y la devuelve.

```C
char	*ft_strdup(const char *s);
```

### ft_strchr
Función que busca un carácter `char` dentro de una cadena de texto dada `char *`.

```C
char	*ft_strchr(const char *s, int c);
```

### ft_strlcpy
Copia una cantidad de carácteres `size_t` de la cadena de texto `char *` dentro de otra cadena de texto `dst`.

```C
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
```

### ft_strjoin
Une dos cadenas de texto `char *` y devuelve el resultado.

```C
char	*ft_strjoin(char const *s1, char const *s2);
```

### ft_strlen
Mide la longitud de la cadena de texto `char *` y devuelve el resultado.

```C
size_t	ft_strlen(const char *s);
```