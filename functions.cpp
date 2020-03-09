#include "class_definition.h"
#include "headers_and_prototypes.h"

extern int mode1,mode2,mode3;

int show_Words(const std::string &result_file,std::vector<Word> &w)
{
    using namespace std;
	ofstream fout(result_file.c_str(),ios::app);
	int t=0;
	if(!fout) {cout<<"����ļ���ʧ�ܣ��˳��С�";return 1;}
	for(int i=0;i<w.size();i++){
		w[i].Show_word(mode1,result_file);
		t+=w[i].Get_count();
		fout<<endl;
	}
	fout<<"ȫ�Ĺ���"<<t<<"�����ʣ�ȥ�غ���"<<w.size()<<"�����ʡ�";
	fout.clear();fout.close();
	return 0;
}

int instructions(std::string &open_file,std::string &result_file)
{
    using std::cout;
    using std::cin;
    using std::endl;
    using std::string;
    cout<<"��������Ӣ�Ĵ�Ƶͳ��"
            <<"\n���ã�ͳ��Ӣ�ĵ��ʳ���Ƶ�ʡ������ʽ�����ʡ���Ƶ�Σ��������ȣ���ĩβ����ܵ�������ʵ�ʵ���������д��ʶ��Ϊһ�����ʡ�"
            <<"\n������������ļ�������������.txt�����Ի��з���β�����ļ�Ӧ�뱾�������ͬһ�ļ����¡�"
            <<"\n����������������h������ʹ�÷�����ĸ����Ƶ�ʵĹ��ܣ�����c��"<<endl;
	getline(cin,open_file,'\n');
	if(open_file.size()==0) {cout<<"δ�����ļ������˳��С�";return 1;}
	else if(cin.fail()) {cout<<"�޷���ȡ�ļ������˳��С�";return 1;}
	if(open_file=="h"){  cout<<"������ļ���ͷ�Զ�������ʽ�򿪣�˳���ȡ��������������ĸ���¼��ǰָ��λ�ã�������ȡ������ĩβ���õ����ʳ��ȡ�"
                                                "Ȼ�󽫶�ָ�뷵�ص�������ĸλ�ã����ݵ��ʳ��Ƚ�����¼����ʱ�����У������дʿ�Ƚϣ����򴴽����ʡ�"
                                                "�ڲ��������vector�Դ��浥�ʡ����⣬�����ж���д�������ǣ���ǰ�ַ�Ϊ'������һ���ַ�Ϊ��ĸ����"
                                                "��������b'b'bҲ�ᱻ��Ϊ���ʡ�"<<endl<<"�ٴ�����������ļ�����";
        open_file.clear();
        getline(cin,open_file,'\n');
        if(open_file.size()==0) {cout<<"δ�����ļ������˳��С�";return 1;}
        else if(cin.fail()) {cout<<"�޷���ȡ�ļ������˳��С�";return 1;}
	}
	else if(open_file=="c") {character_mode(open_file,result_file);return 2;}
	string t=".txt";
	open_file+=t;
	cout<<"�������ļ�������������.txt�����Ի��з���β������1��Ĭ�Ͻ���ļ���Ϊresult.txt��"
                "\n���ļ������ڣ����ļ����ڳ���������Ϻ�����ڱ�����ͬһ�ļ����£����ļ����ڣ�����������ļ�ĩ��"<<endl;
	getline(cin,result_file,'\n');
	if(result_file.size()==0) {cout<<"δ�����ļ������˳��С�";return 1;}
	else if(cin.fail()) {cout<<"�޷���ȡ�ļ������˳��С�";return 1;}
	if(result_file=="1") result_file="result.txt";
	else result_file+=t;
	cout<<"���������0��ʾ��ͳ�Ƶ��ʳ��ȣ�1��ʾ��ʾ���ʳ��ȣ�"<<endl;
	cin>>mode1;
	if(cin.fail()) {cout<<"�޷���ȡ������������Ͳ�ƥ�䣬�˳��С�";return 1;}
	else if(mode1!=0&&mode1!=1) {cout<<"���볬����Χ���˳��С�";return 1;}
	cout<<"������һ������1��ʾ������˳���������2��ʾ����ĸ������Сд��ĸ��ǰ��'���ȼ�������ĸ����3��ʾ�����ִ����������򣨴�����ͬ����ĸ�����򣩣�"<<endl;
	cin>>mode2;
	if(cin.fail()) {cout<<"�޷���ȡ������������Ͳ�ƥ�䣬�˳��С�";return 1;}
	else if(mode2!=1&&mode2!=2&&mode2!=3) {cout<<"���볬����Χ���˳��С�";return 1;}
	cout<<"�������һ��������1��ʾ��Сд���У�2��ʾ���Դ�Сд���죨����Сд��ʾ����3��ʾ���Դ�Сд���죨���Դ�д��ʾ����"<<endl;
	cin>>mode3;
	if(cin.fail()) {cout<<"�޷���ȡ������������Ͳ�ƥ�䣬�˳��С�";return 1;}
	else if(mode3!=1&&mode3!=2&&mode3!=3) {cout<<"���볬����Χ���˳��С�";return 1;}
	return 0;
}

int fill_the_Word_vec(const std::string &open_file,std::vector<Word> &w)
{
    using namespace std;
    ifstream fin(open_file,ios::binary);
    char temp;
    if(!fin) {cout<<"��ȡ�ļ�ʧ�ܣ��˳��С�";return 1;}
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
    cout<<"�����ַ�����ģʽ����ģʽ��ʶ����ĸ�ĳ���Ƶ�ʡ���Сд��ͬ��\n����������ļ�����";
    getline(cin,open_file,'\n');
    if(open_file.size()==0) {cout<<"δ�����ļ������˳��С�";return 1;}
    else if(cin.fail()) {cout<<"�޷���ȡ�ļ������˳��С�";return 1;}
    string t=".txt";
	open_file+=t;
	cout<<"�������ļ�������������.txt�����Ի��з���β������1��Ĭ�Ͻ���ļ���Ϊresult.txt��"
                "\n���ļ������ڣ����ļ����ڳ���������Ϻ�����ڱ�����ͬһ�ļ����£����ļ����ڣ�����������ļ�ĩ��"<<endl;
	getline(cin,result_file,'\n');
	if(result_file.size()==0) {cout<<"δ�����ļ������˳��С�";return 1;}
	else if(cin.fail()) {cout<<"�޷���ȡ�ļ������˳��С�";return 1;}
	if(result_file=="1") result_file="result.txt";
	else result_file+=t;
	cout<<"���������1��ʾ����ĸ˳����λ��2��ʾ������Ƶ�ʽ������У�"<<endl;
	cin>>mode1;
	if(cin.fail()) {cout<<"�޷���ȡ������������Ͳ�ƥ�䣬�˳��С�";return 1;}
	else if(mode1!=1&&mode1!=2) {cout<<"���볬����Χ���˳��С�";return 1;}
	cout<<"������һ������1��ʾͳһ��Сд��ʾ��2��ʾ��Сд���У�"<<endl;
	cin>>mode2;
	if(cin.fail()) {cout<<"�޷���ȡ������������Ͳ�ƥ�䣬�˳��С�";return 1;}
	else if(mode2!=1&&mode2!=2) {cout<<"���볬����Χ���˳��С�";return 1;}

	ifstream fin(open_file,ios::binary);
	if(!fin) {cout<<"��ȡ�ļ�ʧ�ܣ��˳��С�";return 1;}

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
	if(!fout) {cout<<"����ļ���ʧ�ܣ��˳��С�";return 1;}
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
    fout<<"ȫ�Ĺ�"<<i<<"����ĸ������";
    i=0;
    for(int j=0;j<limit;j++){
        if(!c[j].fre) i++;
    }
	fout<<i<<"����ĸδ���ֹ���"<<endl;
	fout.clear();
	fout.close();

    return 0;
}

