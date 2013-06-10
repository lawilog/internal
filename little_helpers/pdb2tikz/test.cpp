#include <iostream>
#include <string>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
using namespace std;
using namespace OpenBabel;

int main(int argc,char **argv)
{
	if(argc<2)
	{
		cout<<"usage: "<<argv[0]<<" molecule_file.pdb"<<endl;
		return 1;
	}
	const string infilename = argv[1];
	
	OBMol mol;
	OBConversion conv;
	conv.SetInFormat("pdb");
	if(! conv.ReadFile(&mol, infilename))
	{
		cerr<<"Could not read and parse file \""<< infilename <<"\"."<<endl;
		return 1;
	}
	
	unsigned natoms = mol.NumAtoms();
	cout<<"File has "<< natoms << " atoms:"<<endl;
	for(OBAtomIterator patom = mol.BeginAtoms(); patom != mol.EndAtoms(); ++patom)
	{
		const OBAtom* atom = *patom;
		cout<<"Element "<< atom->GetAtomicNum() <<", at "<< atom->x() <<" "<< atom->y() <<" "<< atom->z() <<endl;
	}
	for(unsigned i = 0; i < natoms; ++i)
	{
		const OBAtom* atom = mol.GetAtomById(i);
		cout<<"Atom number "<< i <<", element "<< atom->GetAtomicNum() <<", at "<< atom->x() <<" "<< atom->y() <<" "<< atom->z() <<endl;
	}
	
	return 0; // exit with success
}
