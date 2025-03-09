#include <stdio.h>

struct Proceso {
    char nombre;
    int tiempo_creacion;
    int tiempo_cpu;
    int tiempo_espera;
    int tiempo_retorno;
    float penalizacion; // Factor de penalización o retorno normalizado
    bool completado; // Indica si el proceso ya ha sido ejecutado
};

void SJF(int n, Proceso procesos[]) {
    int tiempo_actual = 0;
    int total_espera = 0, total_retorno = 0;
    float total_penalizacion = 0.0;
    int procesos_completados = 0;

    // Inicializamos el campo "completado" de cada proceso a falso
    for (int i = 0; i < n; i++) {
        procesos[i].completado = false;
    }

    printf("Proceso\tLlegada\tDuración\tEspera\tRetorno\tPenalización\n");

    while (procesos_completados < n) {
        int idx = -1;
        int menor_tiempo_cpu = 1e9;

        // Buscamos el proceso con el menor tiempo de CPU que ya haya llegado y no esté completado
        for (int i = 0; i < n; i++) {
            if (!procesos[i].completado && procesos[i].tiempo_creacion <= tiempo_actual) {
                if (procesos[i].tiempo_cpu < menor_tiempo_cpu) {
                    menor_tiempo_cpu = procesos[i].tiempo_cpu;
                    idx = i;
                }
            }
        }

        // Si no se encontró un proceso listo, avanzamos el tiempo al próximo proceso que llega
        if (idx == -1) {
            tiempo_actual++;
            continue;
        }

        // Procesamos el proceso seleccionado
        procesos[idx].tiempo_espera = tiempo_actual - procesos[idx].tiempo_creacion;
        procesos[idx].tiempo_retorno = procesos[idx].tiempo_espera + procesos[idx].tiempo_cpu;
        procesos[idx].penalizacion = (float)procesos[idx].tiempo_retorno / procesos[idx].tiempo_cpu;

        tiempo_actual += procesos[idx].tiempo_cpu;
        total_espera += procesos[idx].tiempo_espera;
        total_retorno += procesos[idx].tiempo_retorno;
        total_penalizacion += procesos[idx].penalizacion;
        procesos[idx].completado = true; // Marcamos el proceso como completado
        procesos_completados++;

        printf("%c\t%d\t%d\t\t%d\t%d\t%.2f\n", procesos[idx].nombre, procesos[idx].tiempo_creacion,
               procesos[idx].tiempo_cpu, procesos[idx].tiempo_espera, procesos[idx].tiempo_retorno, procesos[idx].penalizacion);
    }

    printf("Tiempo de espera promedio: %.2f\n", (float)total_espera / n);
    printf("Tiempo de retorno promedio: %.2f\n", (float)total_retorno / n);
    printf("Penalización promedio: %.2f\n", total_penalizacion / n);
}

int main() {
    int n = 5;
    Proceso procesos[] = {
        {'A', 3, 1, 0, 0, 0.0, false},
        {'B', 2, 5, 0, 0, 0.0, false},
        {'C', 0, 4, 0, 0, 0.0, false},
        {'D', 5, 3, 0, 0, 0.0, false},
        {'E', 7, 2, 0, 0, 0.0, false}
    };

    SJF(n, procesos);

    return 0;
}

