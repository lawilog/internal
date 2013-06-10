#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
using namespace std;
using namespace OpenBabel;

inline const string tikz_header();
inline const string tikz_footer();

int main(int argc,char **argv)
{
	if(argc<2)
	{
		cout<<"usage: "<<argv[0]<<" molecule.pdb [molecule.tikz.tex]"<<endl;
		return 1;
	}
	const string infilename = argv[1];
	const string outfilename = (argc > 2) ? argv[2] : infilename+".tikz.tex";
	
	OBMol mol;
	OBConversion conv;
	conv.SetInFormat("pdb");
	if(! conv.ReadFile(&mol, infilename))
	{
		cerr<<"ERROR: Could not read and parse file \""<< infilename <<"\"."<<endl;
		return 1;
	}
	
	// number of atoms in the molecule:
	unsigned natoms = mol.NumAtoms();
	
	// which elements appear in the molecule?
	set<unsigned> elements;
	for(unsigned i = 0; i < natoms; ++i)
		elements.insert( mol.GetAtomById(i) -> GetAtomicNum() );
	
	// order atoms by their z index (change < into > to invert order)
	vector<unsigned> zorder(natoms);
	for(unsigned i = 0; i < natoms; ++i)
		zorder[i] = i;
	
	sort(zorder.begin(), zorder.end(),
		[&mol](const unsigned& i, const unsigned& j)
		{
			return mol.GetAtomById(i)->z() < mol.GetAtomById(j)->z();
		}
	);
	
	// write tikz tex output
	ofstream outfile(outfilename);
	if(! outfile)
	{
		cerr<<"ERROR: Could not open file \""<< infilename <<"\" for writing."<<endl;
		return 1;
	}
	outfile<<tikz_header();
	
	// define all the colors we need
	for(const unsigned& Z: elements)
	{
		const vector<double> color = etab.GetRGB(Z);
		outfile<<"\\definecolor{"<< etab.GetSymbol(Z) <<"}{RGB}{"
			<< round(255*color[0]) <<","
			<< round(255*color[1]) <<","
			<< round(255*color[2]) <<"}\n";
	}
	
	// draw all the atoms
	for(unsigned i = 0; i < natoms; ++i)
	{
		const OBAtom* atom = mol.GetAtomById(zorder[i]);
		const unsigned Z = atom->GetAtomicNum();
		const double x = atom->x();
		const double y = atom->y();
		/*
		outfile<<"\\shade[ball color="<< etab.GetSymbol(Z) <<"] "
			"("<< x <<","<< y <<") "
			"circle ("<< 0.666*etab.GetCovalentRad(Z) <<");\n"; // etab.GetVdwRad(Z)
		*/
		
		outfile<<"\\node ("<< zorder[i] <<") [atom, ball color="<< etab.GetSymbol(Z) <<","
			"minimum width="<< 2.0*0.666*etab.GetCovalentRad(Z) <<"cm] "
			"at ("<< x <<","<< y <<") {};\n";
	}
	
	// draw bonds (not yet pretty)
	const unsigned nbonds = mol.NumBonds();
	for(unsigned j = 0; j < nbonds; ++j)
	{
		const OBBond* bond = mol.GetBondById(j);
		unsigned ia = bond -> GetBeginAtom() -> GetId();
		unsigned ib = bond -> GetEndAtom() -> GetId();
		outfile<<"\\draw [bond] ("<< ia <<") -- ("<< ib <<");\n";
	}
	
	outfile<< tikz_footer();
	
	outfile.close();
	
	return 0;
}

inline const string tikz_header()
{
	return
		"\\documentclass{article}\n"
		"\\usepackage{tikz}\n"
		"\\usepackage{pgfplots}\n"
		"\\usetikzlibrary{external}\n"
		"\\tikzexternalize\n"
		"\\tikzset{external/system call={latex \\tikzexternalcheckshellescape -halt-on-error -interaction=batchmode -jobname \"\\image\" \"\\texsource\"; dvips -o \"\\image\".eps \"\\image\".dvi}}\n"
		"\\begin{document}\n"
		"\\begin{tikzpicture}[scale=1.0,atom/.style={circle, shade, inner sep=0cm}, bond/.style={-,line width=0.2cm}]\n";
}

inline const string tikz_footer()
{
	return
		"\\end{tikzpicture}\n"
		"\\end{document}\n";
}
