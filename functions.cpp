#include "class_definition.h"
#include "headers_and_prototypes.h"

extern int mode1,mode2,mode3;

int show_Words(const std::string &result_file,std::vector<Word> &w)
{
    using namespace std;
	ofstream fout(result_file.c_str(),ios::app);
	int t=0;
	if(!fout) {cout<<"结果文件打开失败，退出中。";return 1;}
	for(int i=0;i<w.size();i++){
		w[i].Show_word(mode1,result_file);
		t+=w[i].Get_count();
		fout<<endl;
	}
	fout<<"全文共有"<<t<<"个单词，去重后共有"<<w.size()<<"个单词。";
	fout.clear();fout.close();
	return 0;
}

int instructions(std::string &open_file,std::string &result_file)
{
    using std::cout;
    using std::cin;
    using std::endl;
    using std::string;
    cout<<"程序名：英文词频统计"
            <<"\n作用：统计英文单词出现频率。输出格式：单词——频次（——长度），末尾输出总单词数和实际单词数，缩写将识别为一个单词。"
            <<"\n输入待分析的文件名（不需输入.txt），以换行符结尾，该文件应与本程序放于同一文件夹下。"
            <<"\n若需更多帮助，输入h；若需使用分析字母出现频率的功能，输入c："<<endl;
	getline(cin,open_file,'\n');
	if(open_file.size()==0) {cout<<"未输入文件名，退出中。";return 1;}
	else if(cin.fail()) {cout<<"无法读取文件名，退出中。";return 1;}
	if(open_file=="h"){  cout<<"程序从文件开头以二进制形式打开，顺序读取，遇到单词首字母后记录当前指针位置，继续读取至单词末尾，得到单词长度。"
                                                "然后将读指针返回单词首字母位置，根据单词长度将单词录入临时变量中，与现有词库比较，无则创建单词。"
                                                "内部声明类的vector以储存单词。另外，程序判断缩写的依据是（当前字符为'，且下一个字符为字母）。"
                                                "所以形如b'b'b也会被认为单词。"<<endl<<"再次输入待分析文件名：";
        open_file.clear();
        getline(cin,open_file,'\n');
        if(open_file.size()==0) {cout<<"未输入文件名，退出中。";return 1;}
        else if(cin.fail()) {cout<<"无法读取文件名，退出中。";return 1;}
	}
	else if(open_file=="c") {character_mode(open_file,result_file);return 2;}
	string t=".txt";
	open_file+=t;
	cout<<"输入结果文件名（不需输入.txt），以换行符结尾。输入1则默认结果文件名为result.txt。"
                "\n若文件不存在，该文件将在程序运行完毕后出现在本程序同一文件夹下；若文件存在，结果将附至文件末。"<<endl;
	getline(cin,result_file,'\n');
	if(result_file.size()==0) {cout<<"未输入文件名，退出中。";return 1;}
	else if(cin.fail()) {cout<<"无法读取文件名，退出中。";return 1;}
	if(result_file=="1") result_file="result.txt";
	else result_file+=t;
	cout<<"输入参数，0表示不统计单词长度，1表示显示单词长度："<<endl;
	cin>>mode1;
	if(cin.fail()) {cout<<"无法读取输入或输入类型不匹配，退出中。";return 1;}
	else if(mode1!=0&&mode1!=1) {cout<<"输入超出范围，退出中。";return 1;}
	cout<<"输入另一参数，1表示按出现顺序降序输出，2表示按字母表排序（小写字母在前，'优先级低于字母），3表示按出现次数降序排序（次数相同按字母表排序）："<<endl;
	cin>>mode2;
	if(cin.fail()) {cout<<"无法读取输入或输入类型不匹配，退出中。";return 1;}
	else if(mode2!=1&&mode2!=2&&mode2!=3) {cout<<"输入超出范围，退出中。";return 1;}
	cout<<"输入最后一个参数，1表示大小写敏感，2表示忽略大小写差异（仅以小写表示），3表示忽略大小写差异（仅以大写表示）。"<<endl;
	cin>>mode3;
	if(cin.fail()) {cout<<"无法读取输入或输入类型不匹配，退出中。";return 1;}
	else if(mode3!=1&&mode3!=2&&mode3!=3) {cout<<"输入超出范围，退出中。";return 1;}
	return 0;
}

int fill_the_Word_vec(const std::string &open_file,std::vector<Word> &w)
{
    using namespace std;
    ifstream fin(open_file,ios::binary);
    char temp;
    if(!fin) {cout<<"读取文件失败，退出中。";return 1;}
    streampos pos;//set pos to record the reading pointer
	while(fin){
		pos=fin.tellg();//acquire the temporary reading pointer
		fin.get(temp);
		if(!fin) break;
		if(isalpha(temp)){
			int l=1;//l is the length of the word
			while(fin){//get the length
				fin.get(temp);
				if(!fin) break;
				if(isalpha(temp)) l++;
				else if(temp=='\''){
                    fin.get(temp);
                    if(!fin) break;
                    if(isalpha(temp)) l+=2;
				}
				else break;//if the word ends, break the loop
			}
			fin.clear();//in case the file ends with a word rather than blank characters
			fin.seekg(pos);//back to where the word starts
			char t[l+1];//set t to store the word
			for(int i=0;i<l;i++) fin.get(t[i]);
			t[l]='\0';
            if(mode3==1) {}
            else if(mode3==2){
                for(int i=0;i<l;i++) {if(isupper(t[i])) t[i]=tolower(t[i]);}
            }
            else if(mode3==3){
                for(int i=0;i<l;i++) {if(islower(t[i])) t[i]=toupper(t[i]);}
            }
            int repeated=0;//to judge if it already exists
            for(int i=0;i<w.size();i++)
                if(!strcmp(w[i].Get_word(),t)) {w[i].Set_word(w[i].Get_count()+1);repeated=1;break;}
            if(repeated==0)
                w.push_back(Word(t,1,l));
		}
	}
	fin.clear();
	fin.close();
	return 0;
}

int Sort(std::vector<Word> &w)
{
    if(mode2==1) {;}//show the words in the sequence of first appearance
    else if(mode2==2){//show the words in the sequence of alphabet, lowers first
		for(int i=0;i<w.size();i++)
			for(int j=w.size()-1;j>i;j--)
				if(w[j]<w[j-1]) w[j].switch_word(w[j-1]);
    }
    else if(mode2==3){//show the words in the sequence of frequency
		for(int i=0;i<w.size();i++)
			for(int j=w.size()-1;j>i;j--)
				if((w[j].Get_count()>w[j-1].Get_count())||(w[j].Get_count()==w[j-1].Get_count()&&w[j]<w[j-1])) w[j].switch_word(w[j-1]);
	}
    return 0;
}

int character_mode(std::string &open_file,std::string &result_file)
{
    using namespace std;
    open_file.clear();
    cout<<"进入字符分析模式。本模式仅识别字母的出现频率、大小写相同。\n输入待分析文件名：";
    getline(cin,open_file,'\n');
    if(open_file.size()==0) {cout<<"未输入文件名，退出中。";return 1;}
    else if(cin.fail()) {cout<<"无法读取文件名，退出中。";return 1;}
    string t=".txt";
	open_file+=t;
	cout<<"输入结果文件名（不需输入.txt），以换行符结尾。输入1则默认结果文件名为result.txt。"
                "\n若文件不存在，该文件将在程序运行完毕后出现在本程序同一文件夹下；若文件存在，结果将附至文件末。"<<endl;
	getline(cin,result_file,'\n');
	if(result_file.size()==0) {cout<<"未输入文件名，退出中。";return 1;}
	else if(cin.fail()) {cout<<"无法读取文件名，退出中。";return 1;}
	if(result_file=="1") result_file="result.txt";
	else result_file+=t;
	cout<<"输入参数，1表示按字母顺序排位，2表示按出现频率降序排列："<<endl;
	cin>>mode1;
	if(cin.fail()) {cout<<"无法读取输入或输入类型不匹配，退出中。";return 1;}
	else if(mode1!=1&&mode1!=2) {cout<<"输入超出范围，退出中。";return 1;}
	cout<<"输入另一参数，1表示统一按小写表示，2表示大小写敏感："<<endl;
	cin>>mode2;
	if(cin.fail()) {cout<<"无法读取输入或输入类型不匹配，退出中。";return 1;}
	else if(mode2!=1&&mode2!=2) {cout<<"输入超出范围，退出中。";return 1;}

	ifstream fin(open_file,ios::binary);
	if(!fin) {cout<<"读取文件失败，退出中。";return 1;}

	struct ch{
        char con;
        int fre;
	};
	ch c[52]  {{'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0},{'h',0},{'i',0},{'j',0},
                    {'k',0},{'l',0},{'m',0},{'n',0},{'o',0},{'p',0},{'q',0},{'r',0},{'s',0},{'t',0},
	                {'u',0},{'v',0},{'w',0},{'x',0},{'y',0},{'z',0},{'A',0},{'B',0},{'C',0},{'D',0},
	                {'E',0},{'F',0},{'G',0},{'H',0},{'I',0},{'J',0},{'K',0},{'L',0},{'M',0},{'N',0},
	                {'O',0},{'P',0},{'Q',0},{'R',0},{'S',0},{'T',0},{'U',0},{'V',0},{'W',0},{'X',0},
	                {'Y',0},{'Z',0}};
	char temp;
	while(fin){
        fin.get(temp);
        if(!fin) break;
        if(isalpha(temp)){
            if(mode2==1) temp=tolower(temp);
            else if(mode2==2) ;
            for(int i=0;i<52;i++){
                if(temp==c[i].con) {c[i].fre++;break;}
            }
        }
	}
	fin.clear();
	fin.close();

	ofstream fout(result_file.c_str(),ios::app);
	if(!fout) {cout<<"结果文件打开失败，退出中。";return 1;}
	int limit;
	if(mode2==1) limit=26;
	else if(mode2==2) limit=52;
	long long int i=0;
    for(int j=0;j<limit;j++) i+=c[j].fre;
	if(mode1==1) ;
	else if(mode1==2){
        for(int m=limit-1;m>0;m--)
            for(int n=limit-1;n>limit-m-1;n--){
                if(c[n].fre>c[n-1].fre) {int temp=c[n].fre;c[n].fre=c[n-1].fre;c[n-1].fre=temp;  temp=c[n].con;c[n].con=c[n-1].con;c[n-1].con=(char)temp;}
            }
	}
	for(int n=0;n<limit;n++)
        fout<<c[n].con<<'\t'<<c[n].fre<<'\t'<<100.0*c[n].fre/i<<"%\n";
    fout<<"全文共"<<i<<"个字母，其中";
    i=0;
    for(int j=0;j<limit;j++){
        if(!c[j].fre) i++;
    }
	fout<<i<<"个字母未出现过。"<<endl;
	fout.clear();
	fout.close();

    return 0;
}

