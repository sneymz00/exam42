#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

fd_set readfds, openedfds;
int event_count, max_fd_open;
char send_buf[42];
char read_buf[2048];
char *msj[FD_SETSIZE];
int ids[FD_SETSIZE];

int extract_message(char **buf, char **msg)
{
  char  *newbuf;
  int i;

  *msg = 0;
  if (*buf == 0)
    return (0);
  i = 0;
  while ((*buf)[i])
  {
    if ((*buf)[i] == '\n')
    {
      newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
      if (newbuf == 0)
        return (-1);
      strcpy(newbuf, *buf + i + 1);
      *msg = *buf;
      (*msg)[i + 1] = 0;
      *buf = newbuf;
      return (1);
    }
    i++;
  }
  return (0);
}

char *str_join(char *buf, char *add)
{
  char  *newbuf;
  int   len;

  if (buf == 0)
    len = 0;
  else
    len = strlen(buf);
  newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
  if (newbuf == 0)
    return (0);
  newbuf[0] = 0;
  if (buf != 0)
    strcat(newbuf, buf);
  free(buf);
  strcat(newbuf, add);
  return (newbuf);
}

void print_error(const char *error) {
  write(2, error, strlen(error));
  exit(EXIT_FAILURE);
}

void send_all_clients(const char *msj, const int sender, const int server_fd) {
  for (int fd = 0; fd <= max_fd_open; fd++) {
    if (FD_ISSET(fd, &openedfds) && fd != sender && fd != server_fd)
      send(fd, msj, strlen(msj), 0);
  }
}

int main(const int argc, const char **argv) {
  int server_fd, new_conn_fd, len;
  struct sockaddr_in servaddr, cli; 
  int bytes_read, current_id = 0;
  char *line = NULL;

  // If no argument is given, it should write in stderr 
  // "Wrong number of arguments" followed by a \n and exit with status 1
  if (argc != 2)
    print_error("Wrong number of arguments\n");

  // socket create and verification 
  server_fd = socket(AF_INET, SOCK_STREAM, 0); 
  if (server_fd == -1)
    print_error("Fatal error\n"); 

  // assign IP, PORT 
  bzero(&servaddr, sizeof(servaddr)); 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
  servaddr.sin_port = htons(atoi(argv[1])); 
  
  // Binding newly created socket to given IP and verification 
  if ((bind(server_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    print_error("Fatal error\n"); 

  if (listen(server_fd, 10) != 0) {
    close(server_fd);
    print_error("Fatal error\n"); 
  }

  FD_ZERO(&openedfds);
  FD_SET(server_fd, &openedfds);
  max_fd_open = server_fd;

  // Main task
  while(1) {
    readfds = openedfds;

    // Check sockets events
    event_count = select(max_fd_open + 1, &readfds, NULL, NULL, NULL);

    // Loop for every event to attend
    for (int fd = 0; fd <= max_fd_open && event_count; fd++) {
      if (!FD_ISSET(fd, &readfds))
        continue;

      --event_count;
      if (fd == server_fd) { // New connection
        new_conn_fd = accept(server_fd, NULL, NULL);
        if (new_conn_fd < 0)
          continue;


        FD_SET(new_conn_fd, &openedfds);
        if (new_conn_fd > max_fd_open)
          max_fd_open = new_conn_fd;
        msj[new_conn_fd] = NULL;
        ids[new_conn_fd] = current_id++;
        sprintf(send_buf, "server: client %d just arrived\n", ids[new_conn_fd]);
        send_all_clients(send_buf, new_conn_fd, server_fd);
      }
      else { // Client event
        bytes_read = recv(fd, read_buf, 2046, 0);
        if (bytes_read <= 0) { // Client left or had an error
          close(fd);
          free(msj[fd]);
          msj[fd] = NULL;
          sprintf(send_buf, "server: client %d just left\n", ids[fd]);
          send_all_clients(send_buf, fd, server_fd);
          FD_CLR(fd, &openedfds);
        }
        else { // Client talking, and buffer with data
          read_buf[bytes_read] = '\0';
          msj[fd] = str_join(msj[fd], read_buf);
          while (extract_message(&msj[fd], &line) > 0) {
            sprintf(send_buf, "client %d: ", ids[fd]);
            send_all_clients(send_buf, fd, server_fd);
            send_all_clients(line, fd, server_fd);
            free(line);
            line = NULL;
          }
        }
      }
    }
  }
}