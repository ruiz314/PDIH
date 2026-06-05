import cv2
import sys
import os

# Validación del número de argumentos en la línea de comandos
if len(sys.argv) < 2:
    print("\n[ERROR] Uso correcto: python ejercicio4_vid.py <nombre_video.mp4>\n")
    sys.exit(1)

# Captura del parámetro del archivo de imagen
nombre_video = sys.argv[1]

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

# Inicializa la captura del archivo de vídeo pasado por parámetro
camara = cv2.VideoCapture(nombre_video)

# Valida que el archivo realmente exista y OpenCV pueda decodificarlo
if not camara.isOpened():
    print(f"\n[ERROR] No se pudo abrir el archivo de vídeo: '{nombre_video}'\n")
    sys.exit(1)


# Extrae las propiedades nativas del vídeo original para que el de salida sea idéntico
fps_leido = int(camara.get(cv2.CAP_PROP_FPS))      # Cuadros por segundo
ancho = int(camara.get(cv2.CAP_PROP_FRAME_WIDTH))  # Resolución: Ancho en píxeles
alto = int(camara.get(cv2.CAP_PROP_FRAME_HEIGHT))  # Resolución: Alto en píxeles

# Control de seguridad: Si los FPS no se leen bien, asignamos 30 por defecto para evitar el fallo
fps = int(fps_leido) if fps_leido > 0 else 30

# Guardar video de salida
# Obtenemos la ruta absoluta de la carpeta donde se está ejecutando el script
directorio_actual = os.path.dirname(os.path.abspath(__file__))

# Extraemos solo el nombre del archivo de vídeo (eliminando rutas previas si las hay)
nombre_archivo_puro = os.path.basename(nombre_video)
nombre_base, _ = os.path.splitext(nombre_archivo_puro)

# Combinamos todo en una ruta absoluta limpia para Windows
video_salida = os.path.join(directorio_actual, f"resultado_{nombre_base}.avi") # Guarda en formato AVI para máxima compatibilidad con códecs en Windows

# Definimos el códec de compresión de vídeo.
fourcc = cv2.VideoWriter_fourcc(*'XVID')

# Instanciamos el objeto grabador con la ruta, el códec, los FPS y el tamaño de los fotogramas
grabador = cv2.VideoWriter(video_salida, fourcc, fps, (ancho, alto), isColor=True)

# Validación de que el grabador se haya inicializado correctamente en el sistema operativo
if not grabador.isOpened():
    print("[ERROR] No se pudo inicializar el grabador de vídeo. Revisa los permisos de la carpeta.")
    sys.exit(1)

print(f"\n Procesando vídeo: '{nombre_video}' ({ancho}x{alto} a {fps} FPS)")
print(f"El resultado con las detecciones se guardará en: '{video_salida}'")
print("Presiona la tecla 'ESC' en la ventana gráfica para interrumpir el proceso.\n")

#Procesamiento frame a frame del vídeo
while camara.isOpened():
    hay_frame, img = camara.read()

    if not hay_frame:
        print("Fin del archivo de vídeo alcanzado.")
        break

    # Convertimos el frame a escala de grises para el algoritmo de Viola-Jones
    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Buscar los rostros:
    rostros = modeloCara.detectMultiScale(gris, scaleFactor=1.5, minNeighbors=6)

    # Buscar los cuerpos:
    cuerpos = modeloCuerpo.detectMultiScale(gris, scaleFactor=1.5, minNeighbors=3)

    # Dibujar rectángulos
    for (x,y,ancho, alto) in rostros:
        cv2.rectangle(img, (x,y), (x+ancho, y+alto), (0,0,255) , 3) # Rojo
    for (x,y,ancho, alto) in cuerpos:
        cv2.rectangle(img, (x,y), (x+ancho, y+alto), (255,0,0) , 3) # Azul

    print("Fin del procesamiento de vídeo. Guardando resultado final...")
    # Guardar el video en disco
    # Separamos el nombre del archivo de su extensión
    nombre_base, extension = os.path.splitext(nombre_video)
    # Creamos el nuevo nombre para el archivo de salida
    nombre_salida = f"resultado_{nombre_base}{extension}"

    # Guardamos el video modificado en la carpeta de trabajo
    grabador.write(img)
    print(f"Video resultante guardado con éxito como: {nombre_salida}")

    #Abrimos una ventana con el resultado:
    cv2.imshow(f'Ejercicio 4 - {nombre_video}', img)
    
    # Escuchamos los eventos del teclado durante 1 milisegundo
    key = cv2.waitKey(1)
    # 27 es el código ASCII para la tecla 'Esc' (Escape)
    if key == 27:
        print("Proceso interrumpido manualmente por el usuario.")
        break

# Liberar los descriptores para que Windows cierre correctamente los archivos de video
camara.release()
grabador.release()
cv2.destroyAllWindows()
print(f"Archivo de vídeo exportado correctamente en la raíz del proyecto.\n")
