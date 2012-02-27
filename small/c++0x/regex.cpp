#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main()
{
	string haystack = "Is there an echo in here?";
	regex needle("echo");
	cout<<( regex_search(haystack.begin(), haystack.end(), needle) ? "found" : "not found" )<<endl;
	string replaced = regex_replace(haystack, needle, string("apple"));
	
	// RFC 2822
	regex valid_email_address("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\\])");
	//regex valid_email_address_simplfied("[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?");
	
	const char text[] = "My eMail-address is not any@address.com, but some.thing@cool.org.";
	cmatch match;
	if(regex_search(text, match, valid_email_address))
	{
		for(size_t i = 0; i < match.size(); ++i)
		{
			string str(match[i].first, match[i].second);
			cout<< str <<endl;
		}
	}
	
	return 0;
}
