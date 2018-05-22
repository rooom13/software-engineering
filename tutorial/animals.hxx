#ifndef animals_hxx
#define animals_hxx

/*
   - ara afegim un nou atribut a la base de tipus std::string
   - afegim accessors d'escriptura i de lectura
 */

#include <iostream>
#include <string>
#include <vector>



class Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "...indefinida..." << std::endl;
	}
	void nom(std::string elNom)
	{
		_nom = elNom;
	}
	std::string& nom()
	{
		return _nom;
	}

private:
	std::string _nom;
};

class Elefant : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "elefant" << std::endl;
	}
};

class Granota : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "granota" << std::endl;
	}
};

class Gat : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "gat" << std::endl;
	}
};

typedef std::list<Animal*> Animals;


class Enclosure 
{	
private:
     std::string _nom;
	Animals animalsEsclavos;
	
public:
	
    void animalesJaula(){
        
        for (Animals::iterator it= animalsEsclavos.begin(); it!=animalsEsclavos.end(); it++)
	{
            std::cout << "\t" << (*it)->nom() << "\n";
		//std::cout << "l'animal anomenat " << (*it)->nom() << " es de l'especie ";
		//(*it)->escriuEspecie();
	}
    }
    
    void nom(std::string elNom)
	{
		_nom = elNom;
	}
	std::string& nom()
	{
		return _nom;
	}
    
    void addAnimal(Animal animal){
	animalsEsclavos.push_back(&animal);
        
	}
    
};

typedef std::list<Enclosure*> Enclosures;

#endif
