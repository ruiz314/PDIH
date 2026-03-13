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


Una vez instalado usamos el Makefile:
```bash
make clean
make
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/6make_clean.png)

Con la orden `ls -l` listo los ficheros que se han generado:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/7listar_ficheros.png)

### Probando el módulo LKM
Insertar el nuevo móulo en el kernel con los comandos:
```bash
sudo insmod hello.ko
lsmod
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/8insertar_modulo.png)

Se observa que `hello` está el primero een la lista y que nada lo usa (`Used = 0`).

Solicitar información sobre el módulo con el comando `modinfo hello.ko`

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/9info_mod.png)

Para eliminar el módulo  se usa el comando `sudo rmmod hello.ko` y como no hay ningún fallo al realizar la operación no se muestra nada por pantalla.

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/10eliminar_mod.png)

Nos hacemos superusuario para ver la salida de la función printk() en el registro de log del kernel:

![img](https://github.com/ruiz314/PDIH/blob/main/S-LKM/images/11registro_log.png)
