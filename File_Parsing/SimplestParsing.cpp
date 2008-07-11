#include "SimplestParsing.h"
#include <iostream>

using namespace FileParsing;

SimplestParsing::SimplestParsing()
{

}

SimplestParsing::~SimplestParsing()
{
	if (stream_.is_open())
	{
		stream_.close();
	}
}
std::ifstream& SimplestParsing::operator()()
{
	return stream_;
}

bool SimplestParsing::find(const std::string& s)
{
	bool b=false,ef= false;//b signifie que la chaine a été trouvée, ef signifie que la fin de fichier est atteinte
	int i;
	while (!(b)&&!(ef))
	{
		i=0;
		b=true;
		while ((b)&&(static_cast<unsigned int>(i)<s.size()))
		{
			char a;
			stream_.get(a);
			if (stream_.eof()) 
			{
				b=false;
				ef=true;
			}
			if (a!=s[i++])
				b=false;

		}
		if (b) return true;//chaine trouvée
		else 
		{
			stream_.seekg(-i+1,std::ios_base::cur);//retour à la position qu'on avait avant de trouver les caractères semblables   
		}
	}
	return b;

}

bool SimplestParsing::jumpSeparators()
{
	char c;
	do
	{
		stream_.get(c);
		if (stream_.eof()) 
			return false;//fin de fichier

	}while ((c==' ')||(c=='\t')||(c=='\n')||(c==13));//les caractères blances
	stream_.seekg(-1,std::ios_base::cur);//on revient car le dernier caractère n'est pas blanc
	return true;
}

bool SimplestParsing::checkIfNextString(const std::string & s)
{
	bool b=true;
	int i=0;
	while ((b)&&(static_cast<unsigned int>(i)<s.size()))//tant que la chaine correspond temporairement à celle en cours de lecture
	{
		char a;
		stream_.get(a);
		if (stream_.eof()) 
		{
			b=false; 
			i--;
		}
		if (a!=s[i++])
			b=false;

	}
	if (b) 
		return true; //chaine trouvée
	else //chaine non trouvée
	{
		stream_.seekg(-i,std::ios_base::cur);//retour à la case départ
		return false;
	}

}