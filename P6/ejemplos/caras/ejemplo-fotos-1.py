import cv2
 
#Cargamos nuestro modelo classificador de Haar:
modelo = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')
  
#Cargamos la imagen
img = cv2.imread('imagen_input.jpg')
imagen = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
 
#Buscamos los rostros:
rostros = modelo.detectMultiScale(imagen, scaleFactor=1.5, minNeighbors=6 )
# scaleFactor y minNeighbors son parámetros estándar para esta función. 
# El primero es el factor de escala: la función intentará encontrar rostros 
# escalando la imagen varias veces, y este factor indica en cuánto se reduce la imagen cada vez. 
# El segundo parámetro indica la calidad de las detecciones: un valor elevado resulta en menos detecciones pero con más fiabilidad.
# Si hacemos scaleFactor más cercano a 1.0 tardará un poco más de tiempo, pero será más fiable (no se le escaparán algunas caras)

#Ahora recorremos el array 'rostros' y dibujamos los rectángulos sobre la imagen original:
for (x,y,ancho, alto) in rostros:
    cv2.rectangle(img, (x,y), (x+ancho, y+alto), (0,0,255) , 3)
  
#Abrimos una ventana con el resultado:
cv2.imshow('Output', img)
print("\nMostrando resultado. Pulsa cualquier tecla para salir.\n")
cv2.waitKey(0)
cv2.destroyAllWindows()

