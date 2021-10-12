//programa en C para consultar los datos de la base de datos
//Programa que te crea una lista de IDs de partida que el jugador ha tenido con un jugador en concreto
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW rowS;
	MYSQL_ROW rowI;
	char consulta [80];
	int idJI=4;
	int idPI[100];
	int idPS[100];
	char nombre[60];
	strcpy (nombre,"Victoria");
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexiￃﾳn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BBDDv1",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexiￃﾳn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
		
		
		
		// Ahora vamos a buscar el ID de las partidas que ha jugado el jugador contincante
		// construimos la consulta SQL
		sprintf (consulta,"SELECT participacion.idP FROM (participacion) WHERE participacion.idJ IN ( SELECT jugador.id FROM (jugador) WHERE jugador.nombre = '%s')",nombre);
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		rowS = mysql_fetch_row (resultado);
		int x=0;
		int y=0;
		if (rowS == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			while (rowS !=NULL) {
			// El resultado debe ser una matriz con 3 filas
			// y una columna que contiene el id de partida
				idPS[x]=atoi(rowS[0]);
				x++;
				rowS = mysql_fetch_row (resultado);
			}
			y=x;
		}
		
		
		// Ahora vamos a buscar las IDs de las partidas que ha jugado el jugador solicitante
		// construimos la consulta SQL
		sprintf (consulta,"SELECT participacion.idP FROM participacion WHERE idJ = %d",idJI);
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		rowI = mysql_fetch_row (resultado);
		int i=0;
		int j=0;
		if (rowI == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			while (rowI !=NULL) {
			// El resultado debe ser una matriz con 3 filas
			// y una columna que contiene el id de partida
				idPI[i]=atoi(rowI[0]);
				i++;
				rowI = mysql_fetch_row (resultado);
			}
			j=i;
		}
		
		char lista[100];
		sprintf(lista,"El ID de las partidas que tienes en comun con %s son:",nombre);
		for (x=0;x<y;x++){
			for (i=0;i<j;i++){
				if(idPS[x]==idPI[i]){
					sprintf(lista,"%s %d,",lista,idPS[x]);
					
				}
			}
		}
		lista[strlen(lista)-1]='\0';
		printf("%s\n",lista);
				
			
		
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}
