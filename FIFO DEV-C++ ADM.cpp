#include <stdio.h>

struct Proceso {
    char nombre;
    int tiempo_creacion;
    int tiempo_cpu;
    int tiempo_espera;
    int tiempo_retorno;
    float penalizacion;
};

void FIFO(int n, Proceso procesos[]) {
    int tiempo_actual = 0;
    int total_espera = 0, total_retorno = 0;
    float total_penalizacion = 0.0;

    // Ordenamos los procesos por tiempo de creación (orden de llegada) en caso de que no estén ordenados
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (procesos[i].tiempo_creacion > procesos[j].tiempo_creacion) {
                Proceso temp = procesos[i];
                procesos[i] = procesos[j];
                procesos[j] = temp;
            }
        }
    }

    printf("Proceso\tLlegada\tDuración\tEspera\tRetorno\tPenalización\n");

    for (int i = 0; i < n; i++) {
        // Si el tiempo actual es menor que el tiempo de creación del proceso, avanzamos el tiempo
        if (tiempo_actual < procesos[i].tiempo_creacion) {
            tiempo_actual = procesos[i].tiempo_creacion;
        }

        // Calculamos el tiempo de espera y el tiempo de retorno para el proceso actual
        procesos[i].tiempo_espera = tiempo_actual - procesos[i].tiempo_creacion;
        procesos[i].tiempo_retorno = procesos[i].tiempo_espera + procesos[i].tiempo_cpu;

        // Calculamos el factor de penalización para el proceso actual
        procesos[i].penalizacion = (float)procesos[i].tiempo_retorno / procesos[i].tiempo_cpu;

        // Actualizamos el tiempo actual sumando el tiempo de CPU del proceso
        tiempo_actual += procesos[i].tiempo_cpu;

        // Acumulamos los tiempos y penalización totales para cálculos de promedios
        total_espera += procesos[i].tiempo_espera;
        total_retorno += procesos[i].tiempo_retorno;
        total_penalizacion += procesos[i].penalizacion;

        // Imprimimos los resultados de cada proceso
        printf("%c\t%d\t%d\t\t%d\t%d\t%.2f\n", procesos[i].nombre, procesos[i].tiempo_creacion,
               procesos[i].tiempo_cpu, procesos[i].tiempo_espera, procesos[i].tiempo_retorno, procesos[i].penalizacion);
    }

    // Imprimimos los promedios de espera, retorno y penalización
    printf("Tiempo de espera promedio: %.2f\n", (float)total_espera / n);
    printf("Tiempo de retorno promedio: %.2f\n", (float)total_retorno / n);
    printf("Penalización promedio: %.2f\n", total_penalizacion / n);
}

int main() {
    int n = 5;
    Proceso procesos[] = {
        {'A', 3, 1, 0, 0, 0.0},
        {'B', 2, 5, 0, 0, 0.0},
        {'C', 0, 4, 0, 0, 0.0},
        {'D', 5, 3, 0, 0, 0.0},
        {'E', 7, 2, 0, 0, 0.0}
    };

    FIFO(n, procesos);

    return 0;
}

