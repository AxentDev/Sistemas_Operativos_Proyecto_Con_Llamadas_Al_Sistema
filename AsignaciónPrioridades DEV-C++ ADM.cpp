#include <stdio.h>
#include <stdbool.h>

struct Proceso {
    char nombre;
    int tiempo_creacion;
    int tiempo_cpu;
    int prioridad;
    int tiempo_espera;
    int tiempo_retorno;
    float penalizacion;
    bool completado;  // Para marcar si el proceso ya fue ejecutado
};

void Prioridad(int n, Proceso procesos[]) {
    int tiempo_actual = 0;
    int total_espera = 0, total_retorno = 0;
    float total_penalizacion = 0.0;
    int procesos_completados = 0;

    printf("Proceso\tLlegada\tDuración\tPrioridad\tEspera\tRetorno\tPenalización\n");

    while (procesos_completados < n) {
        int idx_seleccionado = -1;

        // Buscar el proceso con la mayor prioridad disponible en el tiempo actual
        for (int i = 0; i < n; i++) {
            if (!procesos[i].completado && procesos[i].tiempo_creacion <= tiempo_actual) {
                if (idx_seleccionado == -1 || 
                    procesos[i].prioridad < procesos[idx_seleccionado].prioridad || 
                    (procesos[i].prioridad == procesos[idx_seleccionado].prioridad && procesos[i].tiempo_creacion < procesos[idx_seleccionado].tiempo_creacion)) {
                    idx_seleccionado = i;
                }
            }
        }

        // Si no hay ningún proceso disponible, avanzamos el tiempo hasta el próximo proceso en la cola
        if (idx_seleccionado == -1) {
            tiempo_actual++;
            continue;
        }

        // Procesamos el proceso seleccionado
        Proceso *proceso = &procesos[idx_seleccionado];
        proceso->tiempo_espera = tiempo_actual - proceso->tiempo_creacion;
        proceso->tiempo_retorno = proceso->tiempo_espera + proceso->tiempo_cpu;
        proceso->penalizacion = (float)proceso->tiempo_retorno / proceso->tiempo_cpu;
        proceso->completado = true;

        // Imprimimos los resultados del proceso
        printf("%c\t%d\t%d\t\t%d\t\t%d\t%d\t%.2f\n", proceso->nombre, proceso->tiempo_creacion,
               proceso->tiempo_cpu, proceso->prioridad, proceso->tiempo_espera, 
               proceso->tiempo_retorno, proceso->penalizacion);

        // Actualizamos el tiempo actual y los totales
        tiempo_actual += proceso->tiempo_cpu;
        total_espera += proceso->tiempo_espera;
        total_retorno += proceso->tiempo_retorno;
        total_penalizacion += proceso->penalizacion;
        procesos_completados++;
    }

    // Imprimimos los promedios de espera, retorno y penalización
    printf("Tiempo de espera promedio: %.2f\n", (float)total_espera / n);
    printf("Tiempo de retorno promedio: %.2f\n", (float)total_retorno / n);
    printf("Penalización promedio: %.2f\n", total_penalizacion / n);
}

int main() {
    int n = 5;
    Proceso procesos[] = {
        {'A', 3, 1, 2, 0, 0, 0.0, false},
        {'B', 2, 5, 3, 0, 0, 0.0, false},
        {'C', 0, 4, 3, 0, 0, 0.0, false},
        {'D', 5, 3, 1, 0, 0, 0.0, false},
        {'E', 7, 2, 2, 0, 0, 0.0, false}
    };

    Prioridad(n, procesos);

    return 0;
}

