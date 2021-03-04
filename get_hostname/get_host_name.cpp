#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

int main() {
	char hname[128];
	struct hostent *hent;
	gethostname(hname, sizeof(hname));
	std::cout << hname << std::endl;

	hent = gethostbyname(hname);
	for(int i = 0; hent->h_addr_list[i]; i++) {
		std::cout << inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])) << std::endl;
	}

	return 0;
}
