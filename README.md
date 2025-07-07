[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - Ruleta Rusa

## Descripción del Proyecto

El objetivo de este proyecto es desarrollar un juego de ruleta rusa utilizando 
el lenguaje de programación C++. El juego está diseñado para dos jugadores, 
donde uno puede ser un jugador real y el otro la CPU, o bien dos jugadores 
humanos conectados simultáneamente


**Por ejemplo:**
• switch: Para manejar el menú principal de acciones del jugador 
(disparar, girar, usar objeto).

• if/else: Para verificar condiciones del juego, como las vidas restantes, y 
determinar si el juego termina.

• for y funciones aleatorias (rand() o random_device): Para simular la 
probabilidad de disparo y evitar manipulaciones, haciendo que el 
tambor del revólver tenga una bala en una posición aleatoria.

## Equipo

- **Nombre del equipo:** #Include <chatgpt>

### Integrantes del equipo

1. **Nombre completo:** Lisandro Luis Villalobos Quintanilla 
   **Carnet:** 00025825

2. **Nombre completo:** Bryan Aristides Rivera Rivera
   **Carnet:** 00165825

3. **Nombre completo:** Ricardo Arturo Vergara Morales
   **Carnet:** 00160625

4. **Nombre completo:** Jose Luis Mendez Figueroa
   **Carnet:** 00208125




## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone [URL del repositorio]


## Temas de programacion utilizados 

1. **switch** Se utiliza para manejar el menú de acciones del jugador durante su turno. Permite al jugador elegir entre opciones como disparar, girar la recámara, usar corte o curación, y según su elección, se ejecuta un bloque de código específico.

2. **if \ else** Permiten controlar el flujo del juego según condiciones específicas:
- Verificar si un jugador sigue con vida.
- Determinar si el jugador puede usar objetos especiales como corte o curación.
- Evaluar si el disparo fue exitoso o fallido.

3. **for** 
- Para recorrer el tambor del revólver y comprobar si hay una bala.
- Para vaciar el tambor antes de cargar una nueva bala.
- Para gestionar lecturas y escrituras en archivos de texto al momento de registrar jugadores y victorias.

4. **array** El tambor del revólver está representado por un arreglo de 6 posiciones (int chamber[6]), donde se almacena si una cámara está vacía o contiene una bala (0 o 1).

5. **Funciones** Se modularizó el programa en varias funciones para reducir la repetición de código y mejorar la legibilidad.
- bulletinchamber() verifica si hay bala en el tambor.
- reloadifempty() recarga la pistola si está vacía.
- turnoJugador() controla las decisiones del jugador.
- registrarVictoria() guarda el nombre del jugador que ganó.

6. **Manejo de Archivos**
- Se utiliza ifstream, ofstream y funciones del sistema para leer, escribir y actualizar un archivo de texto llamado registro_victorias.txt, que guarda los nombres de jugadores y la cantidad de partidas ganadas.
- Se implementó una función para detectar si un jugador ya ha jugado anteriormente y mantener su progreso.