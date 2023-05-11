#include <iostream>
#include <cstring>
using namespace std;
struct HNode{
    int weight;
    int parent;
    int LChild;
    int RChild;
};
struct HCode{
    char data;
    string code;
};
class Huffman{
    private:
        HNode * HTree;
        HCode * HCodeTable;
        int N;
        void code(int i,string newcode);
    public:
        void CreateHTree(int a[],int n,char name[]);    //创建哈夫曼树
        void CreateCodeTable(); //创建编码表
        void SelectMin(int &x, int &y, int end, int a[]);   //选择最小值
        void Encode(char * s,char * d); //编码
        void Decode(char * s,char * d); //解码
        //~ Huffman();    //析构，释放内存
};
void Huffman::SelectMin(int &x, int &y, int end, int a[]) {     //在1到i中找权值最大结点
    x = y = 0;
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for (int i = 0; i < end; i++) {
        if (HTree[i].parent == -1) {
            if (HTree[i].weight < min1) {
                min2 = min1;
                y = x;
                min1 = HTree[i].weight;
                x = i;
            } else if (HTree[i].weight < min2) {
                min2 = HTree[i].weight;
                y = i;
            }
        }
    }
}
/*void SelectMin(int &x,int &y,int n,int a[]){    //在1到i中找权值最大结点
    int num[n];
    for(int i=0;i<n;i++){   //拷贝一份数组a，命名为num数组
        num[i]=a[i];
    }
    for (int i=0;i<n;i++){  //冒泡排序
        for(int j=i+1;j<n;j++){
            if(num[j]<num[i]){
                int post=num[i];
                num[i]=num[j];
                num[j]=post;
            }
        }
    }

    for(int j=0;j<n;j++){
        if(num[0]==a[j]) x=j+1;
        if(num[1]==a[j]) y=j+1;
    }
}
*/
void Huffman::CreateHTree(int a[],int n,char name[]){
    N = n;
    HCodeTable = new HCode[N];
    HTree = new HNode[2*N-1];   //根据权重数组a[]初始化哈夫曼树
    for(int i=0;i<N;i++){
        HTree[i].weight=a[i];
        HTree[i].LChild=HTree[i].RChild=HTree[i].parent=-1;
        HCodeTable[i].data=name[i];
    }
    int x,y;
    for (int i=n;i<2*N-1;i++){  //开始构建
        SelectMin(x,y,i,a); //从1~i中选出两个权值最小结点
        HTree[x].parent=HTree[y].parent=i;
        HTree[i].weight=HTree[x].weight+HTree[y].weight;
        HTree[i].LChild=x;
        HTree[i].RChild=y;
        HTree[i].parent=-1;
    }
}
void Huffman::code(int i,string newcode){   //递归，对第i个结点编码
    if(HTree[i].LChild==-1){
        HCodeTable [i].code = newcode;
        return;
    }
    code(HTree[i].LChild,newcode+"0");
    code(HTree[i].RChild,newcode+"1");
}
void Huffman::CreateCodeTable(){ //生成编码表
    code(2*N-2,"");
    
}
/*
void Huffman::Encode(char * s,char * d){    //编码
    while(*d != '\0'){
        int num=0;
        for(int i=0;i<N;i++){
            if(HCodeTable[i].data==*d){
                
                int leng=HCodeTable[i].code.length();
                //*s=HCodeTable[i].code.data();
                for(int j=0;j<leng;num++,j++){
                    s[num]=HCodeTable[i].code[j];
                }
                //char a=*s;
                //const char *a =(HCodeTable[i].code).data();
                //*s=HCodeTable[i].code;
                num += leng;
                d++;
            }
        }
        s++;
    }
}
*/
void Huffman::Encode(char *s, char *d) {    //编码
    while (*d != '\0') {
        int i;
        for (i = 0; i < N; i++) {
            if (HCodeTable[i].data == *d) break;
        }
        strcpy(s, HCodeTable[i].code.c_str());
        s += HCodeTable[i].code.size();
        d++;
    }
    *s = '\0';
}
void Huffman::Decode(char * s,char * d){    //解码
    while(*s != '\0'){
        int parent = 2 * N - 2;
        while(HTree[parent].LChild != -1){
            if(*s == '0') parent=HTree[parent].LChild;
            else parent=HTree[parent].RChild;
            s++;
        }
        *d = HCodeTable[parent].data;
        d++;
    }
}
void get_point(char *input,int &n,int (&point)[99],char *name){ //统计语句的字符，数量，出现次数
    int a=1;
    int post=0;
    while(*input != '\0'){
        for(int i=0;i<(post+1);i++){
            if (post==0){
                name[0]=*input;
                point[0]=1;
                post++;
                break;
            }
            if (*input==name[i]){
                point[i]++;
                break;
            }
            else if(i==post){
                name[i]=*input;
                point[i]=1;
                post++;
                break;
            }
        }
        input++;
        a++;
    }
    name[post]='\0';
    n=post;
}
int main(){/*
    Huffman hm;
    int a[4]={9,6,2,3}; //假设四个字符的权重分别为9，6，2，3
    int n=4;
    char name[5]={'A','B','Z','C','\0'};    //四个字符与结束符
    hm.CreateHTree(a,n,name);
    //cout<<HCodeTable[0].code<<endl;
    hm.CreateCodeTable();
    char num[99]="\0";
    char output[99]="\0";
    char test_name[99]="ABZCZABCBCAZ";  //注意，目前编码仅可出现ABZC字母
    hm.Encode(num,test_name);   //将test_name进行哈夫曼编码，编码存储到num中
    hm.Decode(num,output);  //将num编码解码为字符存储到output中
    cout<<num<<endl;
    cout<<output<<endl;
    */
    int n;  //字符数量
    char name[99]="\0"; //含有的字符
    int point[99]={0};  //各字符的权值（出现次数）
    char input[99];
    cout<<"请输入要编码的语句："<<endl;
    cin.getline(input,99);
    get_point(input,n,point,name);
    cout<<"经统计该语句含有<"<<n<<">个不同字符，分别为<"<<name<<">,各个字符出现次数分别为<";
    for(int i=0;i<n;i++){
        cout<<point[i];
    }
    cout<<endl;
    Huffman hm;
    hm.CreateHTree(point,n,name);
    hm.CreateCodeTable();
    char code[1024]="\0";
    char output[99]="\0";
    hm.Encode(code,input);   //将input进行哈夫曼编码，编码存储到num中
    hm.Decode(code,output);  //将num编码解码为字符存储到output中
    cout<<"经哈夫曼编码得到的编码为："<<code<<endl;
    cout<<"经解码后为："<<output<<endl;
}
