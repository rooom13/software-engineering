/* 
   - usem els accessors d'escriptura i de lectura de l'atribut _nom

   En resum hem après:
   - com escriure per consola fent servir <iostream>
   - simbols de la libreria localitzats al namespace std::
   - les classes acaben en ;
   - el mètodes i atributs per defecte són private
   - com fer subclasses: "Sub : public Super"
   - perquè serveixen els mètodes virtuals
   - polimorfisme
   - usar #ifndef als headers per evitar redefinicions
   - pas de paràmetres per referència
   - col.leccions estàndars vector i list
   - typdefs
   - iteradors
   - std::string
   - ús d'accessors
 */

#include <list>
#include "animals.hxx"

//Animals es una lista de punteros de Animal
typedef std::list<Animal*> Animals;
//Enclosures es un lisa de puntero de Enclosure, donde una enclosure es un Animals (Lista de punteros a Animal))
typedef std::list<Enclosure*> Enclosures;

int main(void)
{
        //Creamos lista de animales
	Animals animals;
        //Creamos lista de jaulas
        Enclosures zoo;
        
        //Creamos jaulas
        Enclosure amfibios;
        Enclosure felinos;
        Enclosure elefantes;
        Enclosure indefinidos;
        
        //Les ponemos su nombre con 
        amfibios.nom("Amfibios");
        felinos.nom("Felinos");
        indefinidos.nom("Misceláneos");
        elefantes.nom("Elefantes");
        
        //Añadimos dirección de jaulas a las listas de jaulas
        zoo.push_back(&felinos);
        zoo.push_back(&amfibios);
        zoo.push_back(&elefantes);
        zoo.push_back(&indefinidos);
        
        //Declaramos dos ranas
        Granota rana2;
        Granota rana1;
        
        //Les ponemos nombre
        rana1.nom("Rana Xiwei");
        rana2.nom("Rana Gustavo");
        
        //Las metemos en su jaula
        amfibios.addAnimal(rana1);
        amfibios.addAnimal(rana2);
        
        
        //Idem para cualquier animal
        Gat gat1;
        Gat gat2;
        gat1.nom("Gato Pinxu");
        gat2.nom("Leon Javier");
        felinos.addAnimal(gat1);
        felinos.addAnimal(gat2);
        
	Elefant unElefant;
        Elefant dosElefant;
	unElefant.nom("Jumbo l'Orellut");
        dosElefant.nom("Mamut enorme");
	elefantes.addAnimal(unElefant); 
        elefantes.addAnimal(dosElefant);
  
        Animal pokemon;
        Animal pokemon2;
        pokemon.nom("Meowth");
        pokemon2.nom("SHarpedi");
        indefinidos.addAnimal(pokemon);
        indefinidos.addAnimal(pokemon2);
    
 
        //La clase Enclosure tiene un metodo que imprime sus animales
        
       // Iteramons el zoo, zoo es un Enclosures
	for (Enclosures::iterator it= zoo.begin(); it!=zoo.end(); it++)
	{
            std::cout << "Jaula de " << (*it)->nom() << ":\n"; //Imprimimos nombre jaula
            
            //Llamamos a metodo de jaula. Jaula corresponde a el contenido del puntero it iterador
            (*it)->animalesJaula();
            
	}           
	return 0;
}
