#include <stdio.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	//Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char nombre[60];
	char consulta [300];
	//Creamos la conexi￳n al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//Inicializar la conexi￳n  
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bd", 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	printf ("Dame el nombre del usuario\n");
	scanf("%s",nombre);
	
	
	sprintf(consulta, "SELECT PARTIDAS.tablon FROM (JUGADORES,PARTIDAS,RELACION) WHERE JUGADORES.usuario = '%s' AND JUGADORES.ID = RELACION.ID_J AND RELACION.ID_P=PARTIDAS.ID;",nombre);
	
	err=mysql_query(conn,consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//Recogemos el resultado de la consulta
	
	resultado= mysql_store_result(conn);
	row= mysql_fetch_row(resultado);
	if (row==NULL)
		printf("No se han obtenido datos en la consulta \n");
	else
		while (row!=NULL){
			
			//La columna [0] tiene el nombre del tablero
			printf("Tablero:%s\n",row [0]);
			//Obtenemos la siguiente fila 
			row=mysql_fetch_row(resultado); 
		}
	mysql_close(conn);
	exit(0);
}
