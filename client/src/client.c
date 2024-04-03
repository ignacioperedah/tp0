#include "client.h"
#include <readline/readline.h>


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	
	

	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	/* if(config == NULL){
		log_info(logger, "No se creo el config");
		exit(0);
	}*/
		

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");

	log_info(logger, "El valor obtenido del archivo de configuración es: %s", ip);
	log_info(logger, "El valor obtenido del archivo de configuración es: %s", puerto);
	log_info(logger, "El valor obtenido del archivo de configuración es: %s", valor);

	// Loggeamos el valor de config

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion, logger);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("tp0.log", "Log Nuevo", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("/home/utnso/Desktop/tp0/client/cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	//leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	while ((leido = readline("> ")) && strcmp(leido, "") != 0)
    {
        // Logueamos la línea leída
        log_info(logger, "Línea ingresada: %s", leido);

        // Liberamos la memoria del string leído
        free(leido);
    }

	// ¡No te olvides de liberar las lineas antes de regresar!
	// Liberamos la memoria del último string leído (que es un string vacío)
    free(leido);

}

void paquete(int conexion, t_log* logger)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	while ((leido = readline("> ")) && strcmp(leido, "") != 0)
    {
        agregar_a_paquete(paquete, leido, strlen(leido) + 1);

		log_info(logger, "Linea ingresada: %s", leido);

        free(leido);
    }

	enviar_paquete(paquete, conexion);
    eliminar_paquete(paquete);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}
