#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Data{
	public:
		Data(){
			datasize=0;
			message="NULL";
			name="NULL";
			sign=0;
			thread_id=NULL;
		}
	int datasize;//���ݴ�С�������ֽ�
	string message;//������Ϣ
	string name;//�ļ���
	int sign;//��־λ
	int thread_id;//�����߳�id 
	void set(){
		datasize=0;
			message="NULL";
			name="NULL";
			sign=0;
			thread_id=NULL;
	}
};
class Memory{
public:
	Data Mem [16];

	int free=16;//���п��� 
	queue<int> q;//����FIFO�㷨�ĵ������� 
    vector<int> Alloc(int Mb_num,int thread_id){//�����ڴ�� ���ط�����ڴ������ 
        //Mb_num ������ڴ����    thread_id  �߳�id
          vector<int> iv(Mb_num);
          if(Mb_num<=free) {
          	for(int i=0;i<Mb_num;i++){
          		for(int j=0;j<16;j++){
          			if(Mem[j].sign==0){
          				iv[i]=j;
          				Mem[j].thread_id=thread_id;
          				Mem[j].sign=1;
          				q.push(j);
          				break;
					  }
				  }
			  }
			  free=free-Mb_num;
		  } else{//��Ҫ�û� 
		  	int i=0;
		  	for(i=0;i<free;i++){
          		for(int j=0;j<16;j++){
          			if(Mem[j].sign==0){
          				iv[i]=j;
          				Mem[j].thread_id=thread_id;
          				Mem[j].sign=1;
          				q.push(j);
          				break;
					  }
				  }
			  }
			  for(int j=0;j<Mb_num-free;j++){
			  	int z=q.front();//Ҫ�û���ȥ�Ŀ�� 
			  	disk::swap(thread_id,Mem[z].datasize,Mem[z].message,Mem[z].name);//�����û���
				q.pop(); 
			  	Mem[z].set();
			  	Mem[z].thread_id=thread_id;
			  	Mem[z].sign=1;
			  	q.push(z);
			  	iv[i]=z;
			  	i++;
			  }
			free=0;
		  }
          
        return iv;        
   }
    int Write(int thread_id,int data_id,int datasize,string message,string name){//д�ڴ�� �ɹ�����1 
        // thread_id �߳�id  data_id �ڴ���      
        if(Mem[data_id].thread_id==thread_id&&datasize<=4) {//ƥ���߳�id ���ݴ�С������4�ֽ� 
        	Mem[data_id].datasize=datasize;
        	Mem[data_id].message=message;
        	Mem[data_id].name=name;
        	return 1;
		} else
		return 0;
    }
    int Delete(int thread_id){//�ͷ��ڴ�
        //thread_id  �߳�id �����߳�ռ�õ��ڴ����գ���ɾ���Ի������йص����� 
        //return 0/1  ʧ��/�ɹ�   ʧ
        int F=q.front();
        int G=free;
       for(int i=0;i<16-G;i++){//ɾ�����գ��޸�free������q 
        	int a=q.front();
        	q.pop();
        	if(Mem[a].thread_id==thread_id){
        		Mem[a].set();
        		free++;
			}
			else q.push(a); 
		}
		if(disk::DelSwap(thread_id))//���ô��̹���ĺ��� �һ���ɾ���ɹ�������1 
			return 1;
		else
			return 0;
    }
    int InMem(string name){//�ж��ļ��Ƿ����ڴ�  �ɹ�����1 
    	for(int i=0;i<16;i++){
    		if(Mem[i].name==name)
    			return 1;
		}
		return 0;
	}
	void show(){//��ʾ�ڴ����� 
		for(int i=0;i<16;i++){
			cout<<i<<" "<<Mem[i].sign<<" "<<Mem[i].thread_id<<" "<<Mem[i].name<<" "<<Mem[i].datasize<<" "<<Mem[i].message<<endl;
		}
	} 
}; 
