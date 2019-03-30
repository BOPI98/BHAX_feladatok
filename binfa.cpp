
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class LZWBinFa
{
public:
	LZWBinFa ():fa(&gyoker){
		//kiirCsom(*fa);
	}
	~LZWBinFa ()
	{
		szabadit (gyoker.egyesGyermek());
		szabadit(gyoker.nullasGyermek());
	}


	void operator<<(char b)
	{
		
		if(b == '0')
		{
			if(!(fa->balNulla))
			{
				Csomopont *uj = new Csomopont('0');
				fa->ujNullasGyermek(uj);
				fa = &gyoker;
			}
			else
			{
				fa = fa->nullasGyermek();
			}
		}
		else
		{
			if(!fa->egyesGyermek())
			{
				Csomopont *uj= new Csomopont('1');
				fa->ujEgyesGyermek(uj);
				fa = &gyoker;
			}
			else
			{
				fa = fa->egyesGyermek();
			}
		}
	}


	void kiir (void)
	{
		melyseg = 0;
		kiirIn(&gyoker, std::cout);
	}

	int getMelyseg(void);
	double getAtlag(void);
	double getSzoras(void);

	//std::ostream << 'valami';

	friend std::ostream & operator<< (std::ostream & os, LZWBinFa & bf)
	{
		bf.kiir(os);
		return os;
	}

	void kiir(std::ostream & os)
	{
		melyseg = 0;
		kiirIn(&gyoker, os);
	}

LZWBinFa & operator= (const LZWBinFa & lzw){
		std::cout << "Másoló értékadás meghívódott" << std::endl;

          gyoker.ujEgyesGyermek ( masol ( lzw.gyoker.egyesGyermek (), lzw.fa ) );
          gyoker.ujNullasGyermek ( masol ( lzw.gyoker.nullasGyermek (), lzw.fa ) );

          if ( lzw.fa == & ( lzw.gyoker ) )
               fa = &gyoker;
}



private:
	class Csomopont
	{
	public:

		Csomopont(char b = '/'):betu(b), balNulla(0), jobbEgy(0){}
		~Csomopont(){}


		Csomopont * nullasGyermek() const
		{
			return balNulla;
		}
		Csomopont *egyesGyermek () const
		{
			return jobbEgy;
		}
		void ujNullasGyermek (Csomopont * gy)
		{
			balNulla = gy;
		}
		void ujEgyesGyermek(Csomopont * gy)
		{
			jobbEgy = gy;
		}
		char getBetu () const
		{
			return betu;
		}
		Csomopont *balNulla;
		Csomopont *jobbEgy;
	private:
		char betu;
		

		//Csomopont (const Csomopont &); //int x = b;
		//Csomopont & operator= (const Csomopont &); //x = b;
	};

	Csomopont *  masol ( Csomopont * cs, Csomopont * regifa ) {

          Csomopont * ujelem = NULL;

          if ( cs != NULL ) {
               ujelem = new Csomopont ( cs->getBetu() );

               ujelem->ujEgyesGyermek ( masol ( cs->egyesGyermek (), regifa ) );
               ujelem->ujNullasGyermek ( masol ( cs->nullasGyermek (), regifa ) );

               if ( regifa == cs )
                    fa = ujelem;

          }

          return ujelem;
     }
	
	Csomopont *fa;
	int melyseg, atlagosszeg, atlagdb;
	double szorasosszeg;

	LZWBinFa (const LZWBinFa &);
	//LZWBinFa & operator= (const LZWBinFa &);

	//in-order kiíratás
	void kiirIn (Csomopont * elem, std::ostream & os)
	{
		if(elem != NULL)
		{
			++melyseg;
			kiirIn(elem->egyesGyermek(), os);
			for(int i = 0;i < melyseg  ;++i)
				os << "---";
			os << elem->getBetu() << "(" << melyseg - 1 << ")" << std::endl;
			kiirIn(elem->nullasGyermek(), os);
			--melyseg;
		}
	}

	//post-order kíratás
	void kiirPost (Csomopont * elem, std::ostream & os)
	{
		if(elem != NULL)
		{
			++melyseg;
			kiirPost(elem->egyesGyermek (), os);
			kiirPost(elem->nullasGyermek (), os);
			for(int i = 0;i < melyseg; ++i)
				os << "---";
			os << elem->getBetu() << "(" << melyseg -1 << ")" << std::endl;
			--melyseg;
 		}
	}

	//pre-ordere kiíratás
	void kiirPre (Csomopont * elem, std::ostream & os)
	{
		if(elem != NULL)
		{
			++melyseg;
			for(int i = 0; i < melyseg; ++i)
				os << "---";
			
			os << elem->getBetu() << "(" << melyseg - 1 << ")" << std::endl;
			
			kiirPre(elem->egyesGyermek (), os);
			kiirPre(elem->nullasGyermek(), os);
			--melyseg;
		}
	}

	void szabadit(Csomopont * elem)
	{
		if(elem != NULL)
		{
			szabadit(elem->nullasGyermek ());
			szabadit(elem->egyesGyermek ());
			delete elem;
		}
	}
	void kiirCsom(Csomopont  elem){
		std::cout << elem.getBetu() << "sima" <<std::endl;
	}
	/*void kiirCsom2(Csomopont & elem){
		std::cout << elem.getBetu() << std::endl;
	}*/
protected:

	Csomopont gyoker;
	int maxMelyseg;
	double atlag, szoras;

	void rmelyseg(Csomopont * elem);
	void ratlag (Csomopont *elem);
	void rszoras (Csomopont * elem);
};

int LZWBinFa::getMelyseg (void)
{
	melyseg = maxMelyseg = 0;
	rmelyseg (&gyoker);
	return maxMelyseg -1;
}

double LZWBinFa::getAtlag (void)
{
	melyseg = atlagosszeg = atlagdb = 0;
	ratlag (&gyoker);
	atlag = ((double) atlagosszeg) / atlagdb;
	return atlag;
}

double LZWBinFa::getSzoras (void)
{
	atlag = getAtlag ();
	szorasosszeg = 0.0;
	melyseg = atlagdb = 0;

	rszoras(&gyoker);
	if(atlagdb - 1 > 0)
		szoras = std::sqrt (szorasosszeg / (atlagdb - 1));
	else
		szoras = std::sqrt (szorasosszeg);
	return szoras;
}

void LZWBinFa::rmelyseg (Csomopont * elem)
{
	if(elem != NULL)
	{
		melyseg++;
		if (melyseg > maxMelyseg)
			maxMelyseg = melyseg;
		rmelyseg (elem->egyesGyermek());
		rmelyseg (elem->nullasGyermek ());
		melyseg--;
	}
}

void LZWBinFa::ratlag (Csomopont * elem)
{
	if(elem !=NULL)
	{
		melyseg++;
		ratlag (elem->egyesGyermek());
		ratlag (elem->nullasGyermek ());
		melyseg--;
		if(elem->egyesGyermek () == NULL && elem->nullasGyermek () == NULL)
		{
			atlagdb++;
			atlagosszeg += melyseg;
		}
	}
}

void LZWBinFa::rszoras (Csomopont * elem)
{
	if(elem != NULL)
	{
		melyseg++;
		rszoras (elem->egyesGyermek());
		rszoras (elem->nullasGyermek ());
		melyseg--;
		if(elem->egyesGyermek () == NULL && elem->nullasGyermek () == NULL)
		{
			atlagdb++;
			szorasosszeg += ((melyseg - atlag) * (melyseg - atlag));
		}
	}
}

void usage (void)
{
	std::cout << "Usage: lzwtree in_file -o out_file" << std::endl;
}

int main(int argc, char *argv[])
{



	if(argc != 4)
	{
		usage ();
		return -1;
	}

	char *inFile = *++argv;
	
	/*std::cout << **argv << std::endl;
	std::cout << *argv[0] << std::endl;
	std::cout << argv[0][0] << std::endl;*/

	if(*((*++argv) + 1) != 'o')
	{
		usage ();
		return -2;
	}

	std::fstream beFile (inFile, std::ios_base::in);

	if(!beFile)
	{
		std::cout << inFile << " nem létezik..." << std::endl;
		usage ();
		return -3;
	}

	std::fstream kiFile (*++argv, std::ios_base::out);

	unsigned char b;

	LZWBinFa binFa;


	
	while(beFile.read ((char *) &b, sizeof (unsigned char)))
		if(b == 0x0a)
			break;
	/*double a = 2.3;
	int b;
	b= (int) a;*/

	bool kommentben = false;

	while(beFile.read((char *) &b, sizeof(unsigned char)))
	{
		if(b == 0x3e)
		{
			// > karakter
			kommentben = true;
			continue;
		}

		if(b == 0x0a)
		{
			//új sor
			kommentben = false;
			continue;
		}

		if(kommentben)
			continue;

		if(b == 0x4e) //N betű
			continue;

		for(int i = 0;i < 8;++i)
		{
			
			if(b & 0x80){
				
				binFa << '1';
			//	binFa.operator<<('1');

			}
			else
				binFa << '0';
			b <<=1;
		}
	}

	//binFa.kiir();
	std::cout << binFa.getMelyseg () << std::endl;
	std::cout << binFa.getAtlag () << std::endl;
	std::cout << binFa.getSzoras () << std::endl;

	LZWBinFa bfa2;
	bfa2 = binFa;
	std::cout << "másolt bfa2" << std::endl;
	std::cout << bfa2.getMelyseg () << std::endl;
	std::cout << bfa2.getAtlag () << std::endl;
	std::cout << bfa2.getSzoras () << std::endl;	

	

	//operator<<(operator<<(kiFile, binFa),binFa);
	kiFile << binFa;

	//kiFile << binFa << binFa;

	//binFa.operator<<(binFa.operator<<(kiFile,binFa),binFa);



	kiFile << "depth = " << binFa.getMelyseg () << std::endl;
	kiFile << "mean = " << binFa.getAtlag () << std::endl;
	kiFile << "var = " << binFa.getSzoras () << std::endl;

	kiFile.close();
	beFile.close();

	return 0;
}