/*Implementacion lógica del barril del arma, incluyendo la carga de balas normales y potenciadas,
 girar el barril de forma aleatoria, detectar qué bala se dispara y actualizar la posición del barril.*/

 #include<iostream>//La clasica biblioteca que nos ayuda a que el usuario a leer los mensajes impresos.
 #include<cstdlib>//Para generar posiciones aleatorias del barril y para inicializar el generador de numeros aleatorios.
 #include<ctime>// Obtener la hora actual para crear una semilla variable y que los números aleatorios no se repitan entre ejecuciones.

 using namespace std;

 int main(){
   
   int barril[6];
   int tamanño_barril = 6; //Definimos el tamaño que tendra el barril de la pistola, deduciendo que la pistola es una de 6 tiros.
   int vacio=0; // Para definir los espacios vacios del barril de la pistola.
   int bala_normal =1; //Definimos para el disparo normal predeterminado que tendra la pistola.
   int bala_potenciada =2; //Definimos para disparo potenciado (daño x2).
   int posicion_actual =0; // Para definir la posicion actual del barril en la pistola.

   void cargar_barril(int cantnormal, int cantpotenciada)












    return 0;
 }