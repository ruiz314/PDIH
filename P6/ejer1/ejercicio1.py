import cv2
import sys
import os

# Validación del número de argumentos en la línea de comandos
if len(sys.argv) < 2:
    print("[ERROR] Uso correcto: python ejercicio1.py <nombre_imagen.jpg>")
    sys.exit(1)

# Captura del parámetro del archivo de imagen
nombre_imagen = sys.argv[1]

#Cargamos nuestro modelo classificador de Haar:
modelo = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')
  
#Cargamos la imagen
img = cv2.imread(nombre_imagen)

# Control de excepciones ante rutas inexistentes o corruptas
if img is None:
    print(f"[ERROR] No se pudo cargar la imagen '{nombre_imagen}'")
    sys.exit(1)

# Procesamiento en escala de grises
imagen = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
 
#Buscamos los rostros:
rostros = modelo.detectMultiScale(imagen, scaleFactor=1.5, minNeighbors=6 )

#Ahora recorremos el array 'rostros' y dibujamos los rectángulos sobre la imagen original:
for (x,y,ancho, alto) in rostros:
    cv2.rectangle(img, (x,y), (x+ancho, y+alto), (0,0,255) , 3)

#Imprimir el número de rostros detectados
print(f"Número de rostros detectados con éxito: {len(rostros)}")  

#Guardar la imagen en disco
# Separamos el nombre del archivo de su extensión (ej: 'foto' y '.jpg')
nombre_base, extension = os.path.splitext(nombre_imagen)
# Creamos el nuevo nombre para el archivo de salida
nombre_salida = f"resultado_{nombre_base}{extension}"

# Guardamos la imagen modificada en la carpeta de trabajo
cv2.imwrite(nombre_salida, img)
print(f"[INFO] Imagen resultante guardada con éxito como: {nombre_salida}")

#Abrimos una ventana con el resultado:
cv2.imshow(f'Output - {nombre_imagen}', img)
print("\nMostrando resultado del ejercicio 1. Pulsa cualquier tecla para salir.\n")
cv2.waitKey(0)
cv2.destroyAllWindows()
