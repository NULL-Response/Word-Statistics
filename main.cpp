#include "class_definition.h"
#include "headers_and_prototypes.h"

int mode1,mode2,mode3;

int main()
{
    using std::string;
    using std::vector;
	string open_file,result_file;
	if(instructions(open_file,result_file)) return 1;
	vector<Word> w;
	if(fill_the_Word_vec(open_file,w)) return 1;
	if(Sort(w)) return 1;
	if(show_Words(result_file,w)) return 1;
	return 0;
}
