//���ܣ�������Ҫ�������˵�����㣬�����Լ�ÿ������Ҫ���ֵĿ������д�������
//ֻ�ܴ���λͼ�����ݲ�ͬɫ���depth����
//��ûд���ļ�ͷ��ȡͼƬ�ֱ���
#include
#include
#include
#include
#include
#include

#define depth 4
 
static int mask(char(*pic)[600*depth],const int x,const int y,const int w,const int h)
{
    int i=0,j=0,q=0;
    //�洢ɫ�����ɫ
    char color_std[depth];
    for(q=0;q<depth;q++){
        color_std[q]=pic[y][depth*x+q];
    }
 
    for(j=y;j<y+h;j++){
        for(i=depth*x;i<depth*x+w*depth;i+=depth){
                for(q=0;q<depth;q++){
                    pic[j][i+q]=color_std[q];
                }
        }
    }
 
}
 
int reg(char* filename,const int x, const int y,const int w,const int h,const int num){
    int fd=open(filename,O_RDWR);
 
    lseek(fd,54,SEEK_SET);
    int i=0,j=0,q=0,p=0;
    char pic[450][600*depth];   
    read(fd,pic,sizeof(pic));
     
    //������Ҫ��ͼ�ĵ������
    for(j=y;j<y+h-1;j+=h/num){
        for(i=x;i<x+w-1;i+=(w/num)) {
            mask(pic,i,j,w/num,h/num);
        }
    }
     
    lseek(fd,54,SEEK_SET);
    write(fd,pic,sizeof(pic));
    close(fd);
}
 
int main(int argc, const char *argv[])
{
    int x=atoi(argv[1]);
    int y=atoi(argv[2]);
    int w=atoi(argv[3]);
    int h=atoi(argv[4]);
    int n=atoi(argv[5]);
    reg("./image",/*W,H,*/x,y,w,h,n);
    return 0;
}