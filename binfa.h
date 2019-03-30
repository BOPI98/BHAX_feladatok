#ifndef BINFA_H
#define	BINFA_H


#include <iostream> 

class Binfa 
{
public: 
	
		Binfa();
		~Binfa() =  default;
		Binfa(const Binfa &masik);
		Binfa& operator=(const Binfa &masik);

		Binfa(Binfa && masik);
		Binfa& operator=(Binfa&& masik);

		Binfa& operator<<(char const betu);
		Binfa& operator<<(bool betu);
			int getMaxMelyseg();
		double getAtlagMelyseg();
		double getSzoras();
		

    friend std::ostream& operator<<(std::ostream &out, Binfa &fa);
    friend std::istream& operator>>(std::istream &in, Binfa &fa);
	

private:
	class Csomopont 
	{
		public:
			Csomopont(char const betu='/');
			~Csomopont();
			Csomopont(const Csomopont  &masik);
			Csomopont& operator=(const Csomopont  &masik);
			Csomopont(Csomopont&& masik);
			Csomopont& operator=(Csomopont&& masik);
		char getBetu();

        Csomopont*  getBalGyermek() const;
        Csomopont*  getJobbGyermek() const;


        void ujBalGyermek(Csomopont*  uj);
        void ujJobbGyermek(Csomopont*  uj);
        
		private:
			
			char m_betu;
			Csomopont *m_jobb;
			Csomopont *m_bal;



	};
	Csomopont m_gyoker;
    Csomopont* m_aktualis;

    Csomopont* aktualisMutatoMasolas(const Csomopont* elem1,Csomopont* elem2,const Csomopont* m_aktualis) const;

    void computeMaxMelyseg(Csomopont* const elem,
                        int const aktualisMelyseg,
                        int &maxMelyseg);

    void computeAtlagMelyseg(Csomopont* const elem,
                             int const aktualisMelyseg,
                             int &sumMelyseg,
                             int &levelDarab);

    void computeSzoras(Csomopont* const elem,
                       const int aktualisMelyseg,
                       const double atlagMelyseg,
                       double &szorasOsszeg);

    void kiir(Csomopont* const elem,
              int const aktualisMelyseg,
              std::ostream &out);


	

};

#endif
