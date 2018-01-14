#define USER_NUMBER 40
#define ROOM_NUMBER 20

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

struct User
{
    char ip[15];
    int fd;
    int id;
};
struct Room
{
    int turn;
    int roomId;
    int userCount;
    struct User capacity[2];
};
struct threadDataT
{
    int cfd;
    struct sockaddr_in caddr;
};
struct User userNumber[USER_NUMBER];
struct Room roomsCount[ROOM_NUMBER];

int usersOnline = 0;
int roomsCreated = 0;
void SendMessage(int receiverFd, char buffer[50])
{
    printf("%s\n", &buffer[1]);
    write(receiverFd, buffer, sizeof(&buffer));
}
void Login(struct threadDataT *threadData)
{
    memset(userNumber[usersOnline].ip, 0, 15);
    memcpy(userNumber[usersOnline].ip, inet_ntoa((struct in_addr) threadData->caddr.sin_addr), 15);
    userNumber[usersOnline].fd = threadData->cfd;
    usersOnline++;
    userNumber[usersOnline].id = usersOnline;
}
void CreateRoom(struct threadDataT *threadData)
{
    int i;
    for (i = 0; i < ROOM_NUMBER; i++)
    {
        if (roomsCount[i].userCount == 0)
        {
            roomsCount[i].roomId = roomsCreated;
            roomsCount[i].userCount++;
            int j;
            for (j = 0; j < USER_NUMBER; j++)
                if (userNumber[j].fd == threadData->cfd)
                    roomsCount[i].capacity[0] = userNumber[j];
            roomsCreated++;
            SendMessage(threadData->cfd, "cRoom created\n");
            SendMessage(threadData->cfd, "a");
            return;
        }
        
    }
    SendMessage(threadData->cfd, "Brak wolnych pokoi. Sprobuj dolaczyc do juz istniejacego\n");
}
void JoinRoom(struct threadDataT *threadData)
{
    int i, j;
    int emptyRoom = 0;
    for (i = 0; i < ROOM_NUMBER; i++)
    {
        if (roomsCount[i].userCount == 1)
        {
            
            for (j = 0; j < USER_NUMBER; j++)
                if (userNumber[j].fd == threadData->cfd)
                {
                    printf("%d\n", userNumber[j].fd);
                    roomsCount[i].capacity[1] = userNumber[j];
                }
            roomsCount[i].userCount++;
            SendMessage(threadData->cfd, "jYou joined room\n");
            SendMessage(threadData->cfd, "c");
            return;
        }
        else if (roomsCount[i].userCount == 0)
                emptyRoom = 1;        
    }
    if (emptyRoom > 0);
    {    
        SendMessage(threadData->cfd, "cBrak istniejacych pokoi. Stworz nastepny\n");
        return;
    }
    SendMessage(threadData->cfd, "nBrak wolnych pokoi\n");
}
void EndTurn(struct threadDataT *threadData)
{
    int i, j;
    for (i = 0; i < ROOM_NUMBER; i++)
    {
        for (j = 0; j< 2; j++)
            if (roomsCount[i].capacity[j].fd == threadData->cfd)
            {
                if (roomsCount[i].turn == 1)
                {
                    SendMessage(roomsCount[i].capacity[1].fd, "b");
                    SendMessage(roomsCount[i].capacity[0].fd, "c");
                    roomsCount[i].turn = 2;
                }
                else if (roomsCount[i].turn == 2)
                {
                    SendMessage(roomsCount[i].capacity[0].fd, "a");
                    SendMessage(roomsCount[i].capacity[1].fd, "c");
                    roomsCount[i].turn = 1;
                }
            }
    }
}
void *Action(void *tData)
{
    struct threadDataT *threadData = (struct threadDataT*) tData;
    printf("Nowy adres ip: %s\n", inet_ntoa((struct in_addr) threadData->caddr.sin_addr));
    Login(threadData);
    char zapytanie[2];
    while (1)
    {
        switch (zapytanie[0])
        {
            case 'c':
            {
                CreateRoom(threadData);
                break;
            }
            case 'j':
            {
                JoinRoom(threadData);
                break;
            }
            case 'e':
            {
                EndTurn(threadData);
                break;
            }
        }
        
        read(threadData->cfd,zapytanie, 1);
        zapytanie[1] = '\0';
    }
    close(threadData->cfd);
    free(tData);
    pthread_exit(NULL);
}

void HandleConnection(int serverDescriptor)
{
    int result = 0;
    
    pthread_t threadt;
    
    struct threadDataT *tData = malloc(sizeof(struct threadDataT));
    socklen_t len = (socklen_t) sizeof(tData->caddr);
    
    tData->cfd = accept(serverDescriptor, (struct sockaddr*) &tData->caddr, &len);
    
    result = pthread_create(&threadt, NULL, Action, tData);
    
    if (result)
    {
        printf("Blad przy probie utworzenia watku\n");
        exit(4);
    }
    pthread_detach(threadt);
}

int main(int argc, char *argv[])
{
    int serverDescriptor;
    int bindResult;
    int listenResult;
    char reuseAddrVal = 1;
    struct sockaddr_in serverAddr;
    int port = 9876;
    int i;
    
    memset(&roomsCount, 0, sizeof(struct Room));
    for (i = 0; i < ROOM_NUMBER; i++)
        roomsCount[i].turn = 1;
    memset(&serverAddr, 0, sizeof(struct sockaddr));
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    
    serverDescriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (serverDescriptor < 0)
    {
        printf("Blad przy probie utworzenia gniazda\n");
        exit(1);
    }
    
    setsockopt(serverDescriptor, SOL_SOCKET, SO_REUSEADDR, (char*) &reuseAddrVal, sizeof(reuseAddrVal));
    bindResult = bind(serverDescriptor, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    if (bindResult < 0)
    {
        printf("Blad przy probie dowiazania adresu IP i portu do gniazda\n");
        exit(2);
    }
    
    listenResult = listen(serverDescriptor, USER_NUMBER);
    if (listenResult < 0)
    {
        printf("Blad przy probie ustawienia wielkosci kolejki\n");
        exit(3);
    }
    
    while(1)
        HandleConnection(serverDescriptor);
    
    close(serverDescriptor);
    return 0;
}