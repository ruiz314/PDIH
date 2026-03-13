# Seminario. Módulos cargables del kernel (LKM)
## Cuestiones a resolver 

El objetivo principal es conocer cómo funciona el sistema de módulos cargables del kernel de Linux y hacer un módulo sencillo. 

El estudiante debe estudiar el sistema de LKM de Linux. A continuación desarrollará un módulo sencillo en lenguaje C y lo cargará en el kernel usando las herramientas 
estudiadas. Comprobará su correcto funcionamiento inspeccionando los logs del sistema y finalmente descargará el módulo. 

Como resultado se mostrará al profesor el funcionamiento correcto del LKM desarrollado así como el proceso de carga en el kernel. 

**En el documento a entregar se describirá cómo se ha creado y cargado el módulo, y se incluirán varias capturas de pantalla mostrando el proceso y el resultado.**

## Resolución
### Preparación del sistema para construir LKMs
Uso una máquina virtual con Ubuntu 22.

```bash
sudo apt-get update
```
![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/1update.png)

```bash
sudo apt-cache search linux-headers-$(uname -r)

sudo apt-get install linux-headers-$(uname -r)
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/2uname_r.png)

```bash
uname -a
```
![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/3uname_a.png)

### El código del módulo 

Para este seminario usaremos como código de ejemplo el facilitado por “derekmolloy” en su repositorio: 
[derekmolloy/exploringBB/extras/kernel](https://github.com/derekmolloy/exploringBB/tree/master/extras/kernel/) 

**Compilación**:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/4error_compilador.png)

Para solucionar el **error** he instalado el compilador con las siguientes ordenes:

```bash
sudo apt update
sudo apt install gcc-12
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/5instalar_compilador.png)


Una vez instalado usamos el [Makefile](https://github.com/ruiz314/PDIH/blob/main/S-LKM/modulo/Makefile):
```bash
make clean
make
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/6make_clean.png)

Con la orden `ls -l` listo los ficheros que se han generado:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/7listar_ficheros.png)

### Probando el módulo LKM
Insertar el nuevo módulo en el kernel con los comandos:
```bash
sudo insmod hello.ko
lsmod
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/8insertar_modulo.png)

Se observa que `hello` está el primero en la lista y que nada lo usa (`Used = 0`).

Solicitar información sobre el módulo con el comando `modinfo hello.ko`

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/9info_mod.png)

Para eliminar el módulo  se usa el comando `sudo rmmod hello.ko` y como no hay ningún fallo al realizar la operación no se muestra nada por pantalla.

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/10eliminar_mod.png)

Nos hacemos superusuario para ver la salida de la función `printk()` en el registro de log del kernel:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/11registro_log.png)

### Modificación fichero hello.c
Vamos a editar el código para personalizarlo. En concreto los cambios se pueden ver en el fichero [hello2.c](https://github.com/ruiz314/PDIH/blob/main/S-LKM/modulo/hello2.c):

```c
#include <linux/init.h>             // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>           // Core header for loading LKMs into the kernel
#include <linux/kernel.h>           // Contains types, macros, functions for the kernel


MODULE_LICENSE("GPL");              ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Derek Molloy");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux driver for the BBB.");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module

static char *name = "PDIH";        ///< An example LKM argument -- default value is "world" -- modified value is PDIH
module_param(name, charp, S_IRUGO); ///< Param desc. charp = char ptr, S_IRUGO can be read/not changed
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< parameter description

static int __init helloBBB_init(void){
   printk(KERN_INFO "EBB: Hola %s desde el LKM BBB!\n", name);
   return 0;
}

static void __exit helloBBB_exit(void){
   printk(KERN_INFO "EBB: Adios %s desde el LKM BBB!\n", name);
}

module_init(helloBBB_init);
module_exit(helloBBB_exit);
```

También modifico el fichero Makefile:

```bash
obj-m+=hello2.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
```

Listamos lo que hay en la carpeta de trabajo y se observa que están los ficheros antiguos para [hello.c](https://github.com/ruiz314/PDIH/blob/main/S-LKM/modulo/hello.c). Es por eso que se usa `make clean` y luego make de nuevo para compilar el nuevo fichero.

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/12compilacion.png)

Ahora están los ficheros actualizados. Y podemos cargar el módulo con el comando `sudo insmod hello2.ko`:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/13instalacion_modulo_nuevo.png)

De nuevo podemos observar que $Used = 0$.

Para solicitar información del módulo usamos el comando `modinfo`:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/14info_mod2.png)

Borramos el módulo con `rmmmod`:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/15eliminar_mod2.png)

Accedemos a `/var/log` para comprobar que los cambios que hemos hecho con respecto a [hello.c](https://github.com/ruiz314/PDIH/blob/main/S-LKM/modulo/hello.c) se hayan llevado a cabo:
 ```bash
sudo su -
cd /var/log
tail -f kern.log
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/16registro_log2.png)

Podemos observar en la imagen que en vez de decir `world`, ahora dice PDIH. Esto es así porque hemos cambiado el valor de la variable `name`. Además, el mensaje está en español porque hemos traducido los mensajes de `printk`.
