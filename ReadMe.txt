Le fichier test.c a été exclu du makefile, il n'est plus utilisé pour le moment
Pour le moment, j'ai fait un "logiciel" un peu dans la logique de R ou Python. 
Après avoir fait 'make', tu exécutes 'main' et tu sera dans une sorte d'interpréteur où tu pourra entrer les commandes 
contenu dans le dossier cmd_terminal.
ex de deroulement:
./main
  ls -l 
  mkdir test
  etc...
Les commandes ls et mkdir exécutées seront bien celles qui sont codées dans cmd_terminal.
Pour le moment,les commandes disponibles sont ls, mkdir, rmdir,touch(creer un fichier),unlink(supprimer un ficher, éventuellement à renommer par 'rm')
cp et mv, sachant que cp et mv ne sont pas totalement fonctionnelles dans le cas des répertoires.

Dans le main, on créé un processus fils à chaque nouvelle entrée de l'utilisateur afin d'exécuter sa commande.
Les fonctions appelées dans le main se trouve dans la 1ere partie du fichier my_functions.c (j'ai mis un délimiteur ligne 300).

analyseInput est la fonction principale permettant d'interpréter et traiter l'entrée de l'utilisateur(je sais elle est très moche)

Il faut voir pour eventuellement ajouter d'autres commandes et pour gérer l'aspect mémoire comme demand dans le sujet.
Je suppose qu'il faut allouer un espace mémoire, mais la façon de le faire est assez flou pour moi.


UPDATE: le script install.sh permet de copier le dossier cmd_terminal dans /usr/local/test afin que les commandes soit utilisables depuis n'importe où. (les noms de dossier seront changés par la suite)
le script uninstall.sh permet de supprimer le dossier /usr/local/test.
Pour permettre le deplacement et la suppression de repertoire dans /usr/local, on doit changer temporairement les permissions utilisateurs.

Rappel: executer script shell: -le rendre executable: chmod +x install.sh
                                -l'executer: ./install.sh
