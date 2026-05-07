
# install.packages('tuneR', dep=TRUE)
# install.packages('seewave', dep=TRUE)
# install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("/Users/pedro/Desktop/PDIH25/05-22--S5-P5/ejemplo")
# la siguiente linea solo para macOS
setWavPlayer('/usr/bin/afplay')

# cargar archivos de sonido (wav/mp3):
perro <- readWave('perro.wav')
perro
gato  <- readMP3('gato.mp3')
gato

# mostrar los campos del archivo de sonido
str(perro)
str(gato)

# escuchar sonido
listen(gato)

# mostrar la onda del sonido:
plot( extractWave(gato, from = 1, to = 393984) )

