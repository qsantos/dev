#define _XOPEN_SOURCE // getaddrinfo()
#include <poll.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int listen_to(const char* node, const char* service)
{
	// initialize addrinfo
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;

	// solve target
	struct addrinfo* result;
	if (getaddrinfo(node, service, &hints, &result))
		return -1;

	// try and listen on the first available interface
	int sock;
	struct addrinfo* cur = result;
	while (cur)
	{
		sock = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if (sock == -1)
			continue;

		int v = 1;
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(int));

		if (bind(sock, cur->ai_addr, cur->ai_addrlen) != -1 && listen(sock, 10) != -1)
			break;

		close(sock);
		cur = cur->ai_next;
	}

	if (!cur)
		sock = -1;
	freeaddrinfo(result);
	return sock;
}

int main()
{
	int server = listen_to(NULL, "4242");
	printf("Server: %i\n", server);

	// The structure for two events
	struct pollfd fds[1024];

	size_t n_fds = 0;

	fds[n_fds].fd = server;
	fds[n_fds].events = POLLIN;
	n_fds++;

	while (1)
	{
		int ret = poll(fds, n_fds, 10);
		if (ret < 0)
			break;
		if (ret == 0)
			continue;

		for (size_t i = 0; i < n_fds; i++)
		{
			if (!fds[i].revents & POLLIN)
				continue;
			fds[i].revents = 0;

			if (i == 0) // server
			{
				// new client
				int client = accept(server, NULL, NULL);
				if (n_fds >= 1024)
				{
					close(client);
				}
				else
				{
					printf("+ %i\n", client);

					// append client to poll list
					fds[n_fds].fd = client;
					fds[n_fds].events = POLLIN;
					n_fds++;
				}
			}
			else // client
			{
				char buf;
				int ret = recv(fds[i].fd, &buf, 1, MSG_PEEK);
				if (ret == 0) // client disconnected
				{
					printf("- %i\n", fds[i].fd);

					// remove client from poll list (swap and pop)
					if (i != n_fds-1)
						memcpy(&fds[i], &fds[n_fds-1], sizeof(struct pollfd));
					n_fds--;
				}
				else
				{
					// receive data
					while (recv(fds[i].fd, &buf, 1, MSG_DONTWAIT) > 0);
				}
			}
		}
	}
}
