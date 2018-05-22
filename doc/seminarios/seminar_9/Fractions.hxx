/*
 * Students:
 * 
 * Roman Rey Pedrero:    183694
 * Xiwei Zhou       :    176074
 */


#include <iostream>
#include <stdlib.h>
#include <vector>


template<class Type> 
class Fraction 
{
	private:
		Type _numerator;
		Type _denominator;
		
                //Declaraded as private, it's called everytime in the contructor
		void simplify()
		{
			Type mayor = std::max(_numerator, _denominator);
			
			for(int i = 2; i <= mayor; ++i)
				while(((int)_numerator%i == 0) && ((int)_denominator%i == 0))
				{
					_numerator /= i;
					_denominator /=i;
				}
		}
	public:
		Fraction(Type num, Type den):
			_numerator(num), _denominator(den)
		{
			this->simplify();
			
		}
	
	
		Type numerator() {return _numerator;}
		Type denominator() {return _denominator;}
		
		 virtual Fraction operator + ( Fraction & other) const
		 {
                     
                     
			return Fraction(_numerator *other.denominator() +_denominator * other.numerator(), _denominator * other.denominator())	;	 
		 
		 
		 };
		 
		 
		 Fraction operator * ( Fraction & other) const
		{
			return Fraction( _numerator * other.numerator(),   _denominator* other.denominator());
			
		}
		
                 //cout for debugging
		void cout()
		{
			std::cout<< _numerator<<"/"<<_denominator;

 
	
		
	
		}

};



int main()
{


	//Declare  fractions 
    
        //NOTE: our compiler does not allow byte types
	Fraction<int> f1 =  Fraction<int>(1,1);
	Fraction<int> f2 =  Fraction<int>(1,3);

	Fraction<float> f3 =  Fraction<float>(7.0,2.0);
	Fraction<float> f4 =  Fraction<float>(4.0,5.0);
	
	Fraction<long> f5 =  Fraction<long>(3312,222);
	Fraction<long> f6 =  Fraction<long>(322,5423);
        
        Fraction<short> f7 =  Fraction<short>(32,3);
	Fraction<short> f8 =  Fraction<short>(5,32);
	
	
	//cout the result
	f1.cout(); std::cout<<" + ";f2.cout(); std::cout<<" = "; 
	(f1+f2).cout();	 std::cout<<std::endl;

	f1.cout(); std::cout<<" * ";f2.cout(); std::cout<<" = "; 
	(f1*f2).cout();	 std::cout<<std::endl;
	
	
	f3.cout(); std::cout<<" + ";f4.cout(); std::cout<<" = "; 
	(f3+f4).cout();	 std::cout<<std::endl;
	
	f3.cout(); std::cout<<" * ";f4.cout(); std::cout<<" = "; 
	(f3*f4).cout();	 std::cout<<std::endl;
	
	
	f5.cout(); std::cout<<" + ";f6.cout(); std::cout<<" = "; 
	(f5+f6).cout();	 std::cout<<std::endl;

	f5.cout(); std::cout<<" * ";f6.cout(); std::cout<<" = "; 
	(f5*f6).cout();	 std::cout<<std::endl;
        
        f7.cout(); std::cout<<" + ";f8.cout(); std::cout<<" = "; 
	(f7+f8).cout();	 std::cout<<std::endl;
        
        f7.cout(); std::cout<<" * ";f8.cout(); std::cout<<" = "; 
	(f7*f8).cout();	 std::cout<<std::endl;


}
