#include <iostream>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <list>
#include <streambuf>

using namespace std;
using namespace boost;


void tokenize(string &buffer, list<string> &tokens){
	//Remove ellipsis 
	replace_all ( buffer, "...", "___");
	replace_all ( buffer, ". . .", "___");
    char_separator<char> sep(".");
	tokenizer<char_separator<char>> tokens1(buffer, sep);
	BOOST_FOREACH(string t, tokens1)
	{
		trim(t);
		tokens.push_back(t);
	}	
}

int main(int argc, char *argv[]) 
{
	if (argc != 3) 
	{
		cout << "Usage mergebooks book1.txt book2.txt" << endl;
		return EXIT_FAILURE;
	}
	
	string content;
	size_t size;

	//Read the first book
	string file1(argv[1]);
	ifstream  in1;
	in1.open(file1.c_str());
	in1.seekg(0, ios::end);
	size = in1.tellg();
	std::string buffer1(size, ' ');
	in1.seekg(0);
	in1.read(&buffer1[0],size); 
	in1.close();

	list<string> file1_sentences;
	tokenize(buffer1, file1_sentences);
	

	//Read the second book
	string file2(argv[2]);
	ifstream  in2;
	in2.open(file2.c_str());
	in2.seekg(0, ios::end);
	size = in2.tellg();
	std::string buffer2(size, ' ');
	in2.seekg(0);
	in2.read(&buffer2[0],size); 
	in1.close();

	in2.close();

	//Tokenize the second book
	list<string> file2_sentences;
	tokenize(buffer2, file2_sentences);

	//Check sentences count
	if (file1_sentences.size() != file2_sentences.size())
	{
		cout << "Books have different sentences count" << endl;
		cout << "Book 1 has sentences count: " << file1_sentences.size() << endl;
	    cout << "Book 2 has sentences count: " << file2_sentences.size() << endl;
		return EXIT_FAILURE;
	}

	//Merging and write the output file
	string output_file = "output.txt";
	ofstream out;
	out.open(output_file);

	list<string>::iterator it1 = file1_sentences.begin();
	list<string>::iterator it2 = file2_sentences.begin();
	
	while (it1 != file1_sentences.end())
	{
		
		out << *it1;
		out << "\n\n";
		out << *it2;
		out << "\n ------------------\n\n";
		
		it2++;
		it1++;
	}
	out.close();
	
	

	return EXIT_SUCCESS;
}


