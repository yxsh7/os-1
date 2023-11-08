
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
	int fd,fd1;
	char * myfifo = "myfifo";
	char * myfifo1 = "myfifo1";
	char buf[1024];
	
	mkfifo(myfifo,0666);
	mkfifo(myfifo1,0777);

	fd=open(myfifo,O_WRONLY); 
	write(fd,"Hello Everyone! \nWelcome to Progressive Education Society's Modern College of Engineering! \nPune, Maharashtra, India.",sizeof("Hello Everyone! \nWelcome to Progressive Education Society's Modern College of Engineering! \nPune, Maharashtra, India."));

	close(fd);

	unlink(myfifo);

	fd1=open(myfifo1,O_RDONLY);
	read(fd1,buf,sizeof(buf));
	printf("%s", buf);
	unlink(myfifo1);
	close(fd1);
	return 0;
}
