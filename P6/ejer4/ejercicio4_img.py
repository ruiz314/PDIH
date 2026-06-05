import cv2
import sys
import os

# Validación del número de argumentos en la línea de comandos
if len(sys.argv) < 2:
    print("\n[ERROR] Uso correcto: python ejercicio4_img.py <nombre_imagen.jpg>\n")
    sys.exit(1)

# Captura del parámetro del archivo de imagen
nombre_imagen = sys.argv[1]

# Carga el modelo classificador de Haar
modeloCara =cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
modeloCuerpo = cv2.CascadeClassifier('haarcascade_fullbody.xml')

# Verificación de que los modelos se han cargado correctamente
if modeloCara.empty():
    print("Error: No se pudo cargar el clasificador de cara")
    exit()
if modeloCuerpo.empty():
    print("Error: No se pudo cargar el clasificador de cuerpo")
    exit()

# Cargamos la imagen
img = cv2.imread(nombre_imagen)

# Control de excepciones ante rutas inexistentes o corruptas
if img is None:
    print(f"[ERROR] No se pudo cargar la imagen '{nombre_imagen}'")
    sys.exit(1)

# Procesamiento en escala de grises
imagen = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
 
# Buscar los rostros:
rostros = modeloCara.detectMultiScale(imagen, scaleFactor=1.5, minNeighbors=6)

# Buscar los cuerpos:
cuerpos = modeloCuerpo.detectMultiScale(imagen, scaleFactor=1.01, minNeighbors=3)

# Dibujar rectángulos
for (x,y,ancho, alto) in rostros:
    cv2.rectangle(img, (x,y), (x+ancho, y+alto), (0,0,255) , 3)
for (x,y,ancho, alto) in cuerpos:
    cv2.rectangle(img, (x,y), (x+ancho, y+alto), (255,0,0) , 3)

# Guardar la imagen en disco
# Separamos el nombre del archivo de su extensión
nombre_base, extension = os.path.splitext(nombre_imagen)
# Creamos el nuevo nombre para el archivo de salida
nombre_salida = f"resultado_{nombre_base}{extension}"

# Guardamos la imagen modificada en la carpeta de trabajo
cv2.imwrite(nombre_salida, img)
print(f"Imagen resultante guardada con éxito como: {nombre_salida}")

#Abrimos una ventana con el resultado:
cv2.imshow(f'Output - {nombre_imagen}', img)
print("\nMostrando resultado del ejercicio 4. Pulsa cualquier tecla para salir.\n")

cv2.waitKey(0)
cv2.destroyAllWindows()