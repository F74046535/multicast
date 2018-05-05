#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
 
struct sockaddr_in localSock;
struct ip_mreq group;
int sd;
int datalen;
char databuf[1024];
 
int main(int argc, char *argv[])
{
/* Create a datagram socket on which to receive. */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("Opening datagram socket error");
		exit(1);
	}
	else
	printf("Opening datagram socket....OK.\n");
		 
	/* Enable SO_REUSEADDR to allow multiple instances of this */
	/* application to receive copies of the multicast datagrams. */
	{
		int reuse = 1;
	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
	{
		perror("Setting SO_REUSEADDR error");
		close(sd);
		exit(1);
	}
	else
		printf("Setting SO_REUSEADDR...OK.\n");
	}
	 
	/* Bind to the proper port number with the IP address */
	/* specified as INADDR_ANY. */
	memset((char *) &localSock, 0, sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(4321);
	localSock.sin_addr.s_addr = INADDR_ANY;
	if(bind(sd, (struct sockaddr*)&localSock, sizeof(localSock)))
	{
		perror("Binding datagram socket error");
		close(sd);
		exit(1);
	}
	else
		printf("Binding datagram socket...OK.\n");
	 
	/* Join the multicast group 226.1.1.1 on the local 203.106.93.94 */
	/* interface. Note that this IP_ADD_MEMBERSHIP option must be */
	/* called for each local interface over which the multicast */
	/* datagrams are to be received. */
	group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
	group.imr_interface.s_addr = inet_addr("127.0.0.1");
	if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
	{
		perror("Adding multicast group error");
		close(sd);
		exit(1);
	}
	else
		printf("Adding multicast group...OK.\n");
	 
	/* Read from the socket. */
	datalen = sizeof(databuf);
	if(read(sd, databuf, datalen) < 0)
	{
		perror("Reading datagram message error");
		close(sd);
		exit(1);
	}
	else
	{
		printf("Reading datagram message...OK.\n");
		printf("The message from multicast server is: \"%s\"\n", databuf);
	}
     int sizeu;
    //int w=recvfrom(sd,&sizeu,sizeof(sizeu),0,(struct sockaddr*)&localSock,sizeof(localSock));
    int w=read(sd,&sizeu,sizeof(sizeu));
    printf("%d\n",sizeu);
    printf("read picture in byte array!\n");
    char p_arrayu[240000];
    char p_arrayuu[240000];
    int bbc;
    printf("yes\n");
    int cc;
    int m=0;
    for(cc=0;cc<3;cc++)
    {   
        sizeu=sizeu-60000;
        m++;
        if(sizeu<0)
        {
            break;
        }
    }
    for(bbc=0;bbc<m;bbc++)
    {
        //int v=recvfrom(sd,p_arrayu,60000,0,(struct sockaddr *)&localSock,sizeof(localSock));
        printf("yes\n");
        int v=read(sd,p_arrayu,60000);
        int i=0;
        for(i=0;i<60000;i++)
        {
            p_arrayuu[i+bbc*60000]=p_arrayu[i];
        }
        
    }
    FILE *imgu;
    imgu=fopen("c1.jpg","w");
    fwrite(p_arrayuu,1,sizeof(p_arrayuu),imgu);
    printf("the file is sent sucessfully");
    printf("the new file is c1.jpg");
    fclose(imgu);

    

	return 0;
}
