library(tuneR)
library(seewave)
library(audio)

# Establecer el path concreto en cada caso a la carpeta de trabajo
setwd("/Users/inesr/OneDrive/Documentos/GitHub/PDIH/P5")

# Ejercicio 2. Leer los dos ficheros de sonido creados y dibujar la forma de 
# onda de ambos sonidos (por separado).

# Cargar archivos de sonido (wav):
nombre <- readWave('nombre.wav')
nombre
apellidos <- readWave('apellidos.wav')
apellidos

# Mostrar la onda del sonido:
plot( extractWave(nombre, from = 1, to = 32879) )
plot( extractWave(apellidos, from = 1, to = 49007) )

# Ejercicio 3. Obtener la información de las cabeceras de ambos sonidos.
str(nombre)
str(apellidos)

# Ejercicio 4. Unir ambos sonidos en uno nuevo para escuchar el nombre y apellido correctamente. 
# Unir sonidos
union <- pastew(apellidos, nombre, output="Wave") # orden: nombre, apellidos

# Mostrar información del sonido
union

# Ejercicio 5. Dibujar la forma de onda de la señal y reproducir el sonido resultante (una vez unidos). 
# Generar y mostrar dibujo de la onda
plot(extractWave(union, from=1, to=81886))

# Reproducir sonido
listen(union)

# Ejercicio 6. Almacenar el sonido resultante en un archivo nuevo llamado “basico.wav” 
writeWave(union, file.path("basico.wav"))

# Cargar el fichero
basico <- readWave('basico.wav')

# Mostrar información del sonido
basico
