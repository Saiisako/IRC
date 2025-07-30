127.0.0.1 --> adress loopback qui designe localhost sois le pc en question.
toute adresse comprise de 127.0.0.1 à 127.255.255.255

le port est un uint16_t donc unsigned int sur 16bit

pour remplir BIND() il y a deux facons :

- Soit avec la structure addr_in, puis il faut la: reinterpret_cast<sockaddr*>
- ou faire une structure addr_info :
{
	struct addrinfo hints = {}, *res;
	hints.ai_family = AF_INET;          // ou AF_UNSPEC pour IPv4+IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;        // pour bind

	int err = getaddrinfo(NULL, "6667", &hints, &res);
	if (err == 0)
	{
		bind(fd, res->ai_addr, res->ai_addrlen);
		freeaddrinfo(res);
	}
}






la commande nc sur terminal est une commande qui est litteralement un client IRC.
Dans le sujet c'est ecris juste faire un serveur et pas de client justement carr
netcat est deja un client qui se connecte a un serveur.

password :

Entre 8 et 30 caractères
Une minuscule au moins
Une majuscule au moins
Un chiffre au moins
Un des caractères spéciaux suivants: ! ' - _ { } [ ] ( ) @ $ £ ? ; :
ATTENTION 

Modifier memset car interdit.