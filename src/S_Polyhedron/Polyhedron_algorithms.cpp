#include <SCD/S_Polyhedron/Polyhedron_algorithms.h>

#ifdef WITH_OPENGL
# if defined __APPLE__
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
# endif // __APPLE__
#endif // WITH_OPENGL

#include <SCD/File_Parsing/SimplestParsing.h>


using namespace SCD;

Polyhedron_algorithms::Polyhedron_algorithms(void):fastVertexes_(NULL),lastVertexes_(NULL),displayList_(-1)
{

}

Polyhedron_algorithms::Polyhedron_algorithms(const Polyhedron_algorithms &p):triangles_(p.triangles_),fastVertexes_(NULL),lastVertexes_(NULL),displayList_(p.displayList_)
{
	for (unsigned i=0;i<p.vertexes_.size();++i)
	{
		vertexes_.push_back(p.vertexes_[i]->clone());
	}

	updateVertexNeighbors();

	updateFastArrays();
}

Polyhedron_algorithms::~Polyhedron_algorithms(void)
{
	if (fastVertexes_!=NULL)
	{
		delete[] fastVertexes_;
	}
	for (unsigned int i=0;i<vertexes_.size();++i)
	{
		delete vertexes_[i];
	}
}

const Polyhedron_algorithms& Polyhedron_algorithms::operator =(const Polyhedron_algorithms &p)
{
		if (this==&p)
	{
		return *this;
	}
	else
	{
		clear();
		displayList_=p.displayList_;
		triangles_=p.triangles_;

		for (unsigned i=0;i<p.vertexes_.size();++i)
		{
			vertexes_.push_back(p.vertexes_[i]->clone());
		}

		updateVertexNeighbors();

		updateFastArrays();


		return *this;
	}
}




#ifdef WITH_OPENGL
void Polyhedron_algorithms::drawGL()
{
	if (vertexes_.size()>0)
	{

		if (displayList_==-1)
		{
			/*OpenGL displaylist*/

			displayList_=glGenLists(1);

			glNewList(displayList_,GL_COMPILE);

			glBegin(GL_TRIANGLES);


			glColor3d(0.6,0.8,0.7);

			for (unsigned i=0;i<triangles_.size();i++)
			{
				glNormal3d(triangles_[i].normal[0],triangles_[i].normal[1],triangles_[i].normal[2]);


				glVertex3d(vertexes_[triangles_[i].a]->getCordinates()[0],
					vertexes_[triangles_[i].a]->getCordinates()[1],
					vertexes_[triangles_[i].a]->getCordinates()[2]);

				glVertex3d(vertexes_[triangles_[i].b]->getCordinates()[0],
					vertexes_[triangles_[i].b]->getCordinates()[1],
					vertexes_[triangles_[i].b]->getCordinates()[2]);

				glVertex3d(vertexes_[triangles_[i].c]->getCordinates()[0],
					vertexes_[triangles_[i].c]->getCordinates()[1],
					vertexes_[triangles_[i].c]->getCordinates()[2]);
			}




			glEnd();



			glEndList();





		}

	


		glCallList(displayList_);


	}


}
#endif

void Polyhedron_algorithms::openFromFile(const std::string &filename)
{
	clear();

	FileParsing::SimplestParsing is;

  is.load(filename.c_str());

	int ent;
	is.jumpSeparators();  
	is()>>ent;
	is.jumpSeparators();   
	is()>>ent;//récupération du nombre de points
	is.find("\n");
	is.jumpSeparators(); 
	for (int g=0;g<ent;g++)
	{
		Scalar y[3];
		is()>>y[0];//récupération des coordonnées
		is.jumpSeparators(); 
		is()>>y[1];//récupération des coordonnées
		is.jumpSeparators(); 
		is()>>y[2];//récupération des coordonnées
		is.jumpSeparators(); 

		S_PolyhedronVertex *v;
		v=new S_PolyhedronVertex();
		v->setCordinates(y[0],y[1],y[2]);
		v->setNumber(unsigned (vertexes_.size()));
		vertexes_.push_back(v);

	}

	while (is.find("normal:"))//récupération des normales
	{
		is.jumpSeparators(); 
		Scalar y[3];

		PolyhedronTriangle t;

		is()>>y[0];
		is.jumpSeparators(); 
		is()>>y[1];
		is.jumpSeparators(); 
		is()>>y[2];
		is.jumpSeparators(); 

		t.normal.Set(y[0],y[1],y[2]);
		t.normal.normalize();

		is.find("vertices");//récupération des indices
		is.find("p");
		is()>>t.a;
		is.find("p");
		is.jumpSeparators(); 
		is()>>t.b;
		is.find("p");
		is.jumpSeparators(); 
		is()>>t.c;



		//updatingNeighbors
		vertexes_[t.a]->addNeighbor(vertexes_[t.b]);
		vertexes_[t.a]->addNeighbor(vertexes_[t.c]);

		vertexes_[t.b]->addNeighbor(vertexes_[t.a]);
		vertexes_[t.b]->addNeighbor(vertexes_[t.c]);

		vertexes_[t.c]->addNeighbor(vertexes_[t.a]);
		vertexes_[t.c]->addNeighbor(vertexes_[t.b]);

		triangles_.push_back(t);



	}

	for (unsigned int i=0;i<vertexes_.size();i++)
	{
		vertexes_[i]->updateFastArrays();
	}

	deleteVertexesWithoutNeighbors();


}

void Polyhedron_algorithms::updateVertexNeighbors()
{
	for (unsigned i=0;i<triangles_.size();++i)
	{
		//updatingNeighbors
		vertexes_[triangles_[i].a]->addNeighbor(vertexes_[triangles_[i].b]);
		vertexes_[triangles_[i].a]->addNeighbor(vertexes_[triangles_[i].c]);

		vertexes_[triangles_[i].b]->addNeighbor(vertexes_[triangles_[i].a]);
		vertexes_[triangles_[i].b]->addNeighbor(vertexes_[triangles_[i].c]);

		vertexes_[triangles_[i].c]->addNeighbor(vertexes_[triangles_[i].a]);
		vertexes_[triangles_[i].c]->addNeighbor(vertexes_[triangles_[i].b]);
	}

	for (unsigned i=0;i<vertexes_.size();++i)
	{
		vertexes_[i]->updateFastArrays();
	}


}

void Polyhedron_algorithms::clear()
{
	for (unsigned int i=0;i<vertexes_.size();++i)
	{
		delete vertexes_[i];
	}
	vertexes_.clear();
	triangles_.clear();
	updateFastArrays();
}

void Polyhedron_algorithms::clearNeighbors()
{
	for (unsigned i=0;i<vertexes_.size();++i)
	{
		vertexes_[i]->clearNeighbors();
		vertexes_[i]->updateFastArrays();
	}
}

void Polyhedron_algorithms::updateFastArrays()
{
	if (fastVertexes_!=NULL)
	{
		delete[] fastVertexes_;
	}
	if (vertexes_.size()>0)
	{
		fastVertexes_=new S_PolyhedronVertex*[vertexes_.size()];
		for (unsigned int i=0;i<vertexes_.size();++i)
		{
			fastVertexes_[i]=vertexes_[i];
		}

		lastVertexes_=&(fastVertexes_[vertexes_.size()]);
	}
	else
	{
		fastVertexes_=lastVertexes_=NULL;
	}
}

Point3 Polyhedron_algorithms::naiveSupport(const Vector3&v)const
{
	S_PolyhedronVertex** current;

	current=fastVertexes_;

	Scalar supportH=(*current)->supportH(v);

	Vector3 best=(*current)->getCordinates();

	current++;

	while (current<lastVertexes_)
	{

		if ((*current)->supportH(v)>supportH)
		{
			supportH=(*current)->supportH(v);
			best=(*current)->getCordinates();
		}

		current++;
	}

	return best;
}

Point3 Polyhedron_algorithms::support(const Vector3&v,int &lastFeature)const
{
	S_PolyhedronVertex* current;
	Scalar supportH;

	if (lastFeature==-1)
	{
		current=*fastVertexes_;
	}
	else
	{
		current=fastVertexes_[lastFeature];
	}

	bool b=current->isHere(v);

	while (!b)
	{
		supportH= current->getNextVertexH();
		current = current->getNextVertex();
		b=current->isHere(v,supportH);
	}

	lastFeature=current->getNumber();


	return current->getCordinates();



}

void Polyhedron_algorithms::deleteVertexesWithoutNeighbors()
{
	int *cache=new int[vertexes_.size()];
	std::vector<S_PolyhedronVertex*> v;
	int index=0;

	for (unsigned i=0;i<vertexes_.size();++i)
	{
		if (vertexes_[i]->getNumNeighbors()>0)
		{
			v.push_back(vertexes_[i]);
			vertexes_[i]->setNumber(index);
			cache[i]=index++;
		}
		else
		{
			delete vertexes_[i];
			cache[i]=-1;
		}
	}

	for (unsigned i=0;i<triangles_.size();++i)
	{
		triangles_[i].a=cache[triangles_[i].a];
		triangles_[i].b=cache[triangles_[i].b];
		triangles_[i].c=cache[triangles_[i].c];
	}

	vertexes_=v;


	updateFastArrays();

	delete[] cache;

}
