#include "motor.h"

int main(int argc, char **argv)
{
	Universo universo("XML/configuracion.xml");
	
	universo.bucle_principal();	
	
	return 0;
}
