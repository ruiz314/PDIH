# Práctica 5. Experimentación con el sistema de salida de sonido

[Memoria](https://github.com/ruiz314/PDIH/blob/main/P5/memoria_P5.pdf)

## Requisitos mínimos
1. Crear dos ficheros de sonido (WAV) para realizar los siguientes ejercicios. En el primero debe escucharse el nombre de la persona que realiza la práctica. En el segundo debe escucharse el apellido. 

Fichero de sonido con [nombre](https://github.com/ruiz314/PDIH/blob/main/P5/nombre.wav)

Fichero de sonido con [apellidos](https://github.com/ruiz314/PDIH/blob/main/P5/apellidos.wav)

2. Leer los dos ficheros de sonido creados y dibujar la forma de onda de ambos sonidos (por separado). 

Onda de nombre:

![img](https://github.com/ruiz314/PDIH/blob/main/P5/onda_nombre.png)

Onda de apellidos:

![img](https://github.com/ruiz314/PDIH/blob/main/P5/onda_apellidos.png)

3. Obtener la información de las cabeceras de ambos sonidos. 
4. Unir ambos sonidos en uno nuevo para escuchar el nombre y apellido correctamente. 

5. Dibujar la forma de onda de la señal y reproducir el sonido resultante (una vez unidos). 

![img](https://github.com/ruiz314/PDIH/blob/main/P5/onda_union.png)

6. Almacenar el sonido resultante en un archivo nuevo llamado “basico.wav”

Fichero de sonido con [basico](https://github.com/ruiz314/PDIH/blob/main/P5/basico.wav)


Fichero con ejercicios: [ejercicios.R](https://github.com/ruiz314/PDIH/blob/main/P5/doc/src/ejercicios.R)

## Requisitos ampliados
7. Pasarle un filtro de frecuencia para eliminar las frecuencias entre 10.000Hz y 20.000Hz. Almacenar la señal obtenida como un fichero WAV denominado “filtrado.wav”  
8. Tomar el sonido que se creó antes (lo tendremos en el archivo llamado “basico.wav”) para aplicarle el efecto de eco. Guardar ese sonido en un archivo nuevo llamado “eco.wav”. A continuación, se le debe dar la vuelta al sonido y almacenarlo como un fichero llamado “alreves.wav” 

Fichero con ejercicios: [extra.R](https://github.com/ruiz314/PDIH/blob/main/P5/doc/src/extra.R)
