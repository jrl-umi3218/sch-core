
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

#include <sch/File_Parsing/SimplestParsing.h>


using namespace FileParsing;

SimplestParsing::SimplestParsing()
{
}

SimplestParsing::~SimplestParsing()
{
}

void SimplestParsing::load(const char* filename)
{
  std::ifstream tmp_is(filename);

  if(!tmp_is.is_open())
  {
    std::stringstream errmsg;
    errmsg << "EXCEPTION : Unable to open File " << filename << std::endl;
    throw std::invalid_argument(errmsg.str());

  }

  stream_ << tmp_is.rdbuf();
}

std::stringstream& SimplestParsing::operator()()
{
  return stream_;
}

bool SimplestParsing::find(const std::string& s)
{
  bool chainFound=false;
  //eof: end of file found?
  bool eof= false;
  int i;
  while (!(chainFound)&&!(eof))
  {
    i=0;
    chainFound=true;
    while ((chainFound)&&(static_cast<unsigned int>(i)<s.size()))
    {
      char a;
      stream_.get(a);
      if (stream_.eof())
      {
        chainFound=false;
        eof=true;
      }
      if (a!=s[i++])
        chainFound=false;

    }
    if (chainFound)
      return true;
    else
    {
      // back to the initial position
      stream_.seekg(-i+1,std::ios_base::cur);
    }
  }
  return chainFound;
}

bool SimplestParsing::jumpSeparators()
{
  char c;
  do
  {
    stream_.get(c);
    if (stream_.eof())
      return false;//end of file

  }
  while ((c==' ')||(c=='\t')||(c=='\n')||(c==13)); //white chars
  stream_.seekg(-1,std::ios_base::cur);//the last char is not white.
  return true;
}

bool SimplestParsing::checkIfNextString(const std::string & s)
{
  bool b=true;
  int i=0;
  //while the chain corresponds to the one being read
  while ((b)&&(static_cast<unsigned int>(i)<s.size()))
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
    return true; //chain found
  else //chaine not found
  {
    stream_.seekg(-i,std::ios_base::cur);//back to the beginning
    return false;
  }

}

