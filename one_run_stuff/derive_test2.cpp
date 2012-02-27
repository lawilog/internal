#include <iostream>
using namespace std;

// general data object, used as basis for everything
template<class T>
class DataObject
{
	protected:
		T data;
	
	public:
		DataObject() { cout << "empty DataObject" << endl; }
		DataObject(T& new_data)
		{
			data = new_data;
			cout << "DataObject " << data << endl;
		}
		virtual T getData() const {return data;}
};

// template class DataObject<int>;

class DataObjectInt : public DataObject<int>
{
	public:
		DataObjectInt() : DataObject<int>() {}
		DataObjectInt(int new_data) : DataObject<int>(new_data) {}
		void specialIntFunction() {cout<< (data % 2) << endl;}
};

/*
template<class T>
class ObjectHandler
{
	public:
		virtual int streamDataToNetwork(T* data) = 0;
};
*/

// all data objects of a certain type have special functions
/*
template<>
class DataObject<int>
{
	protected:
		int data;
	
	public:
		void specialIntFunction() {cout<< (data % 2) << endl;}
};
*/

class PersonalID : public DataObjectInt
{
	public:
		PersonalID(int id, bool neg_switch)
		{
			if(neg_switch) data = id;
			else data = -id;
			cout << "PersonalID " << data << endl;
		}
};

class Counter : public DataObjectInt
{
	public:
		Counter(int initial_count, int id) : DataObjectInt(initial_count)
		{
			cout << "Counter #" << id << " = " << initial_count << endl;
		}
		
		
};

int main()
{
	Counter c(1, 42);
	c.specialIntFunction();
	
	PersonalID pid(23, true);
	PersonalID* ptr = & pid;
	cout << "main " << ( ptr -> getData() ) << endl;
	return 0;
}
