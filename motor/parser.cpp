#include <iostream>
#include "parser.h"

using namespace std;

Parser::Parser(const char* fichero): documento(fichero)
{
	try{
		documento.LoadFile();
	}
	catch(ticpp::Exception& e){
		cerr << "Parser::Parser(): " << e.what() << endl;
		exit(1);
	}
}

Parser::Parser(const string fichero): documento(fichero)
{
	try{
		documento.LoadFile();
	}
	catch(ticpp::Exception& e){
		cerr << "Parser::Parser(): " << e.what() << endl;
		exit(1);
	}
}

std::string Parser::contenido(const ticpp::Element* elemento) const
{
	try{
		return elemento->GetText();
	}
	catch(ticpp::Exception& e){
	}
	return string();
}

std::string Parser::atributo(const std::string& nombre, const ticpp::Element* elemento) const
{
	return elemento->GetAttribute(nombre);
}

void Parser::encontrar_aux(const string& nombre, ticpp::Element* padre, ticpp::Element*& elemento, bool& parada)
{
	if(padre && !parada){
		// Hay que explorar todos los subárboles de los hijos
		ticpp::Iterator<ticpp::Element> hijo;
		for (hijo = hijo.begin(padre); hijo != hijo.end() && !parada; hijo++){
			if(hijo->Value() == nombre){
				elemento = hijo.Get();
				parada = true;
			}
			else
				encontrar_aux(nombre, hijo.Get(), elemento, parada);
		}
	}
}

ticpp::Element* Parser::encontrar(const string& nombre, ticpp::Element* inicio)
{
	ticpp::Element* padre = inicio;
	if(!padre)
		padre = documento.FirstChildElement(false);
	
	bool parada = false;
	ticpp::Element* elemento = 0;
	
	if(padre){
		if(padre->Value() == nombre)
			return padre;
		else
			encontrar_aux(nombre, padre, elemento, parada);
	}
	
	if(!elemento)
		cout << "Encontrar devuelve NULL" << endl;
	
	return elemento;
}

void Parser::encontrar_aux(const string& nombre, ticpp::Element* padre, vector<ticpp::Element*>& v)
{
	if(padre){
		ticpp::Iterator<ticpp::Element> hijo;
		for (hijo = hijo.begin(padre); hijo != hijo.end(); hijo++){
			if(hijo->Value() == nombre)
				v.push_back(hijo.Get());
			encontrar_aux(nombre, hijo.Get(), v);
		}
	}
}

bool Parser::encontrar(const string& nombre, vector<ticpp::Element*>& v, ticpp::Element* inicio)
{
	ticpp::Element* padre = inicio;
	if(!padre)
		padre = documento.FirstChildElement(false);
	
	size_t tamano = v.size();
	
	if(padre){
		if(padre->Value() == nombre)
			v.push_back(padre);
		encontrar_aux(nombre, padre, v);
	}
	
	return tamano < v.size();
}

bool Parser::save(const std::string& filename){
	try{
		documento.SaveFile(filename);
	}
	catch(ticpp::Exception& e){
		return false;
	}
	return true;
}

ticpp::Element* Parser::add(const std::string& nombre, ticpp::Element* padre){

	ticpp::Element* raiz = padre ? padre : documento.FirstChildElement(false);

	if(raiz){
		ticpp::Node* node = raiz->LinkEndChild( new ticpp::Element(nombre) );
	if(node)
		return node->ToElement();
	}

	return 0;
}

