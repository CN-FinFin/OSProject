#include <string>
#include<string.h>
#include<ctime>
#include<iostream>
#include<map>
#include "memmanager.h"
using namespace std;

//Ŀ¼ 
class Dir{
	public:
		Dir(){
			FileName="NULL";
			FileOwner="NULL";
			Date=NULL;
			FileStructure="NULL";
			adr=0; 
		}
	 string FileName; //�ļ���
	 string FileOwner ;//�ļ�������
	 char *Date;//����ʱ�� 
	 string  FileStructure;//�ļ��ṹ 
	 int adr;//�ٴ����д�ŵĵ�ַ��Ϣ 
	 void setFileName(string a);
	 void setFileOwner(string b);
	 void setDate(char *c);
	 void setFileStructure(string x);
	 void setadr(int y);
	 void show();
};
	void Dir::setFileName(string a){
  		FileName=a;
	}
	void Dir::setFileOwner(string b){
		FileOwner=b;
	}
	void Dir::setDate(char *c){
	 	Date=c;
	}
	void Dir::setFileStructure(string x){
	 	FileStructure=x;
	 }
	void Dir::setadr(int y){
	 	adr=y;
	 }
	void Dir::show(){
	 	cout<<FileName<<endl;
	 }
	 
	 
class DirMan{
	public:
	map<string,Dir> DirMap;
	void CreatNullDir(string x);//������Ŀ¼�� 
	void DelNullDir();//ɾ����Ŀ¼�� 
	void DelFile(string x);//ɾ���ļ� 
	void CreatDir(string owner,string filename,int address,string structer);//Ϊ�ļ�����Ŀ¼�� 
	void ShowDirMan();//������ʾ��ǰ������Ŀ¼�� 
};
	void DirMan::CreatNullDir(string x){ //x�� �ļ�ӵ���ߣ� 
		//��Ŀ¼��ʱ�� 
		Dir dir;
		time_t now=time(0);
		char*dt=ctime(&now);
		dir.Dir::setDate(dt);
		dir.Dir::setFileOwner(x);
		//��Ŀ¼���ļ��� 
		dir.Dir::setFileName("NULLFILE");
		//��Ŀ¼�ĵ�ַ
		dir.Dir::setadr(0); 
		//�ļ��ṹ
		dir.Dir::setFileStructure("NULL"); 
		DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
	}

	void DirMan::DelNullDir(){
		DirMap.erase("NULL");
	}
	void DirMan::DelFile(string x){
		int t=Memory::InMem(x);//�ڴ�����еĺ����������ļ����ж��Ƿ����ڴ��� 
		if(!t){
			DirMap.erase(x); //ɾ��Ŀ¼ 
			//�˴���Ҫɾ���ļ��ڴ����ж�Ӧ�����ݣ� 
		}
	}
	void DirMan::CreatDir(string owner,string filename,int address,string structer){
		Dir dir;
		//ʱ�� 
		time_t now=time(0);
		char*dt=ctime(&now);
		dir.Dir::setDate(dt);
		//ӵ���� 
		dir.Dir::setFileOwner(owner);
		//�ļ��� 
		dir.Dir::setFileName(filename);
		//��ַ
		dir.Dir::setadr(address);
		//�ļ��ṹ
		dir.Dir::setFileStructure(structer);
		//����Ŀ¼
		DirMap.insert(map<string, Dir>::value_type(dir.FileName, dir));
		cout<<dir.FileName<<"�Ѵ����ɹ�"<<endl; 
	}
	void DirMan::ShowDirMan(){
		map<string,Dir>::iterator it;
		for(it=DirMap.begin();it!=DirMap.end();it++){
			pair<string,Dir> item=*it;
			cout<<item.second.FileName<<endl;
		}
	} 



