Commande

4.1.2 Message de pseudo

      Commande : NICK
   Paramètres : <pseudo> [ <nombre de sauts> ]

   Le message NICK est utilisé pour donner un surnom à l'utilisateur ou modifier le surnom précédent.
   1. Le paramètre <hopcount> est uniquement utilisé par les serveurs pour indiquer
   la distance entre un pseudo et son serveur d'origine. Une connexion locale a
   un nombre de sauts de 0. S'il est fourni par un client, il doit être ignoré.

   Si un message NICK arrive sur un serveur qui connaît déjà un
   surnom identique pour un autre client, une collision de surnoms se produit.
   À la suite d'une collision de surnoms, toutes les instances du surnom
   sont supprimés de la base de données du serveur et une commande KILL est émise
   pour supprimer le pseudonyme de la base de données de tous les autres serveurs. Si le pseudonyme
   Le message à l'origine de la collision était un changement de surnom, puis le
   l'ancien pseudo d'origine doit également être supprimé.

   Si le serveur reçoit un NICK identique d'un client qui est
   directement connecté, il peut émettre une ERR_NICKCOLLISION au local
   client, abandonnez la commande NICK et ne générez aucun kill.


   Réponses numériques :

           ERR_NONICKNAMEGIVEN ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE ERR_NICKCOLLISION

   Exemple:

   NICK Wiz ; Présentation du nouveau pseudo « Wiz ».

   :WiZ NICK Kilroy ; WiZ a changé son surnom en Kilroy.

4.1.3 Message utilisateur

      Commande : USER
   Paramètres : <nom d'utilisateur> <nom d'hôte> <nom de serveur> <nom réel>

   Le message USER est utilisé au début de la connexion pour spécifier
   le nom d'utilisateur, le nom d'hôte, le nom de serveur et le nom réel du nouvel utilisateur.
   également utilisé dans la communication entre les serveurs pour indiquer un nouvel utilisateur
   arrivant sur IRC, car seulement après que l'UTILISATEUR et le Pseudonyme ont été
   reçu d'un client, un utilisateur devient-il enregistré.

   Entre les serveurs, USER doit être préfixé par le NICKname du client.
   Notez que le nom d'hôte et le nom de serveur sont normalement ignorés par l'IRC
   serveur lorsque la commande USER provient d'un client directement connecté
   (pour des raisons de sécurité), mais ils sont utilisés de serveur à serveur
   communication. Cela signifie qu'un NICK doit toujours être envoyé à un
   serveur distant lorsqu'un nouvel utilisateur est présenté au reste du
   réseau avant que l'UTILISATEUR qui l'accompagne ne soit envoyé.

   Il faut noter que le paramètre realname doit être le dernier paramètre,
   car il peut contenir des caractères d'espacement et doit être préfixé par un
   deux points (':') pour s'assurer que cela est reconnu comme tel.

   Puisqu'il est facile pour un client de mentir sur son nom d'utilisateur en s'appuyant sur
   uniquement sur le message USER, l'utilisation d'un « Identity Server » est
   recommandé. Si l'hôte depuis lequel un utilisateur se connecte dispose d'un tel
   serveur activé, le nom d'utilisateur est défini comme dans la réponse du
   « Serveur d'identité ».

   Réponses numériques :

           ERR_NEEDMOREPARAMS ERR_DEJAENREGISTRED

   Exemples :


   UTILISATEUR invité tolmoon tolsun :Ronnie Reagan



Oikarinen & Reed [Page 15]

RFC 1459               Protocole de chat relais Internet, mai 1993


                                   ; L'utilisateur s'enregistre avec un
                                   nom d'utilisateur de « invité » et nom réel
                                   "Ronnie Reagan".


   :testnick UTILISATEUR invité tolmoon tolsun :Ronnie Reagan
                                   ; message entre serveurs avec le
                                   surnom pour lequel la commande USER
                                   appartient à


4.2.1 Rejoindre le message

      Commande : JOIN
   Paramètres : <canal>{,<canal>} [<clé>{,<clé>}]

   La commande JOIN est utilisée par le client pour commencer à écouter un
   canal. Le fait qu'un client soit autorisé ou non à rejoindre un canal est
   vérifié uniquement par le serveur auquel le client est connecté ; tous les autres
   les serveurs ajoutent automatiquement l'utilisateur au canal lorsqu'il est reçu
   depuis d'autres serveurs. Les conditions qui affectent ceci sont les suivantes :

           1. l'utilisateur doit être invité si le canal est accessible uniquement sur invitation ;

           2. le pseudo/nom d'utilisateur/nom d'hôte de l'utilisateur ne doit correspondre à aucun
               interdictions actives;

           3. la clé correcte (mot de passe) doit être donnée si elle est définie.

   Ceux-ci sont décrits plus en détail sous la commande MODE (voir
   section 4.2.3 pour plus de détails).

   Une fois qu'un utilisateur a rejoint un canal, il reçoit une notification sur tous les
   commandes que leur serveur reçoit et qui affectent le canal. Ceci
   inclut MODE, KICK, PART, QUIT et bien sûr PRIVMSG/NOTICE.
   La commande JOIN doit être diffusée à tous les serveurs afin que chaque serveur
   sait où trouver les utilisateurs présents sur la chaîne. Cela permet
   livraison optimale des messages PRIVMSG/NOTICE au canal.

   Si une jointure réussit, l'utilisateur reçoit alors le sujet du canal
   (en utilisant RPL_TOPIC) et la liste des utilisateurs présents sur le canal (en utilisant
   RPL_NAMREPLY), qui doit inclure l'utilisateur qui rejoint.

   Réponses numériques :

           ERR_NEEDMOREPARAMS ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN ERR_BADCHANNELKEY
           ERR_CHANNELISFULL ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL ERR_TROP DE CANAUX
           RPL_TOPIC

   Exemples :

   REJOIGNEZ #foobar ; rejoignez la chaîne #foobar.

   REJOIGNEZ &foo fubar ; rejoignez le canal &foo en utilisant la touche "fubar".

   REJOIGNEZ #foo,&bar fubar ; rejoignez le canal #foo en utilisant la touche « fubar »
                                   et &bar sans utiliser de clé.

   REJOIGNEZ #foo,#bar fubar,foobar ; rejoignez le canal #foo en utilisant la touche "fubar".
                                   et canal #bar en utilisant la touche "foobar".

   REJOIGNEZ #foo, #bar ; rejoignez les canaux #foo et #bar.

   :WiZ REJOIGNEZ #Twilight_zone ; REJOIGNEZ message de WiZ




3.2.7 Message d'invitation

      Commande : INVITE
   Paramètres : <pseudo> <canal>

   La commande INVITE est utilisée pour inviter un utilisateur à un canal.
   le paramètre <nickname> est le surnom de la personne à inviter
   le canal cible <channel>. Il n'est pas nécessaire que
   le canal auquel l'utilisateur cible est invité doit exister ou être valide
   canal. Cependant, si le canal existe, seuls les membres du canal
   sont autorisés à inviter d'autres utilisateurs. Lorsque le canal est accessible uniquement sur invitation,
   ensemble d'indicateurs, seuls les opérateurs de canal peuvent émettre la commande INVITE.

   Seuls l'utilisateur invitant et l'utilisateur invité recevront
   notification de l'invitation. Les autres membres du canal ne sont pas
   notifié. (Ceci est différent des changements de MODE, et est parfois le
   source de problèmes pour les utilisateurs.)

   Réponses numériques :

           ERR_NEEDMOREPARAMS ERR_NOSUCHNICK
           ERR_NOTONCHANNEL ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
           RPL_INVITATION RPL_ABSENCE

   Exemples :

   :Angel!wings@irc.org INVITEZ Wiz #Dust

                                   ; Message à WiZ quand il a été
                                   invité par l'utilisateur Angel sur la chaîne
                                   #Poussière

   INVITEZ Wiz #Twilight_Zone ; Commande pour inviter WiZ à
                                   #Twilight_Zone



3.2.8 Commande de coup de pied

      Commande : COUP DE PIED
   Paramètres : <canal> *( "," <canal> ) <utilisateur> *( "," <utilisateur> )
               [<commentaire>]

   La commande KICK peut être utilisée pour demander la suppression forcée d'un utilisateur
   d'un canal. Cela oblige l'utilisateur à se séparer du canal en
   force. Pour que le message soit syntaxiquement correct, il DOIT y avoir
   soit un paramètre de canal et plusieurs paramètres utilisateur, soit autant
   paramètres de canal, car il existe des paramètres utilisateur. Si un « commentaire » est
   étant donné, cela sera envoyé à la place du message par défaut, le surnom
   de l'utilisateur émettant le KICK.

   Le serveur NE DOIT PAS envoyer de messages KICK avec plusieurs canaux ou
   utilisateurs aux clients. Ceci est nécessaire pour maintenir les relations en amont
   compatibilité avec les anciens logiciels clients.

   Réponses numériques :

           ERR_NEEDMOREPARAMS ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL ERR_NOTONCHANNEL


   Exemples :

   KICK &Melbourne Matthew ; Commande pour expulser Matthew de
                                   &Melbourne

   KICK #Finnish John : Parle anglais
                                   ; Ordre d'expulser John de #Finnish
                                   en utilisant « Parler anglais » comme
                                   raison (commentaire).

   :WiZ!jto@tolsun.oulu.fi KICK #Finnois John
                                   ; Message KICK sur la chaîne #Finnish
                                   de WiZ pour supprimer John de la chaîne


3.1.5 Message du mode utilisateur

      Commande : MODE
   Paramètres : <pseudo>
               *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )

   Les MODES utilisateur sont généralement des modifications qui affectent soit la façon dont l'utilisateur
   le client est vu par d'autres ou quels messages « supplémentaires » sont envoyés au client.

   Une commande MODE utilisateur DOIT uniquement être acceptée si l'expéditeur de la
   Le message et le surnom donnés en paramètre sont identiques. Si
   aucun autre paramètre n'est donné, alors le serveur renverra le paramètre actuel
   paramètres pour le pseudo.

      Les modes disponibles sont les suivants :

           a - l'utilisateur est signalé comme absent ;
           i - marque un utilisateur comme invisible ;
           w - l'utilisateur reçoit des coups ;
           r - connexion utilisateur restreinte ;
           o - indicateur d'opérateur ;
           O - indicateur d'opérateur local ;
           s - marque un utilisateur pour la réception des notifications du serveur.

   Des modes supplémentaires pourront être disponibles ultérieurement.



   L'indicateur « a » NE DOIT PAS être basculé par l'utilisateur à l'aide de la commande MODE,
   au lieu de cela, l'utilisation de la commande AWAY est OBLIGATOIRE.

   Si un utilisateur tente de se faire opérateur en utilisant le « +o » ou
   Drapeau « +O », la tentative DOIT être ignorée car les utilisateurs pourraient contourner le
   mécanismes d'authentification de la commande OPER. Il n'existe pas
   restriction, cependant, à quiconque se « déoppe » (en utilisant « -o » ou
   "-O").

   En revanche, si un utilisateur tente de se libérer de ses restrictions
   en utilisant l'indicateur « -r », la tentative DOIT être ignorée. Il n'y a pas
   restriction, cependant, sur quiconque se « défait » (en utilisant « +r »).
   Cet indicateur est généralement défini par le serveur lors de la connexion pour
   raisons administratives. Bien que les restrictions imposées soient laissées à l'appréciation
   à la mise en œuvre, il est typique qu'un utilisateur restreint ne soit pas
   autorisé à changer de pseudo, ni à utiliser l'opérateur de canal
   statut sur les chaînes.

   Le drapeau « s » est obsolète mais PEUT encore être utilisé.

   Réponses numériques :

           ERR_NEEDMOREPARAMS ERR_USERSDONTMATCH
           ERR_UMODEUNKNOWNFLAG RPL_UMODEIS

   Exemples :

   MODE WiZ -w ; Commande de WiZ pour éteindre
                                   réception des messages WALLOPS.

   MODE Ange +i ; Commande d'Ange pour se rendre
                                   invisible.

   MODE WiZ -o ; WiZ 'deopping' (suppression de l'opérateur
                                   statut).
