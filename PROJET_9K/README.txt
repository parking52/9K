  I. Installation
 II. Configuration
III. Utilisation
 IV. Divers

  I. Installation
  ------------------
  
 *** Première installation ***

Pour assouvir votre besoin d'awesomitude, vous pourrez jouer à 9K après avoir décompressé
l'archive dans le dossier de votre choix. Placez vous ensuite via le terminal dans le dossier bin 
de celui qui a été décompressé :

cd dossier/LIF7/PROJET/bin

Pour lancer le jeu en SDL :

Modifiez la ligne 6 et 7 du makefile : celle-ci doit apparaître de cette façon :

	 JEU	= texte
	#JEU	= graphique

Utilisez la commande : make clean
Puis utilisez la commande : make
et enfin utilisez la commande ./9K_gfx


Pour lancer le jeu en Ncurses :

Modifiez la ligne 6 et 7 du makefile : celle-ci doit apparaître de cette façon :

	 #JEU	= texte
	  JEU	= graphique

Utilisez la commande : make clean
Puis utilisez la commande : make
et enfin utilisez la commande ./9K_txt

N'oubliez pas d'avoir vos bibliothèques SDL (image, ttf), FMOD et ncurses mises à jour pour pouvoir jouer.
 
 
 *** Mise à jour ***
 
 A votre grand désespoir, il n'y a pas de mises à jour prévues pour ce jeu. 
 Malgré tout, vous pouvez nous contacter sur kevin.sauvageon@gmail.com melchior.fracas@wanadoo.fr
 pour toutes demandes de détails, d'autographes, de droit de reproduction, de droit d'adaptation et toutes questions sur la portance du code.
 
 
 
 II. Configuration
---------------------

 Le jeu tel que vous le prennez est configuré optimalement. Cependant, si, à vos risques et périls,
 vous ressentez l'envie d'une nouvelle expérience de jeu, vous pouvez configurer les variables suivantes :
 points de score par javelot évité, intervalle de chute des javelots (qui peut être en fonction du score), HP, le nombre de javelot par vague.
 
 
 III. Utilisation
---------------------

 Pour jouer, sélectionnez votre mode de jeu. Ensuite, appuyez sur les touches pour faire bouger Léonidas.
 Bougez rapidement : il faut éviter les javelots que l'armée perse vous lance. Attention : les javelots 
 vous arrive dessus de plus en plus vite.
 Pour le mode illimité, une fois la partie terminée, faites une capture d'écran et, le cas échéant, 
 montrez la à vos amis et comparez vos scores, après tout vous valez surement mieux qu'eux !




 IV. Divers
---------------

 Le nom de Leonidas ne nous appartient pas et pourra être remplacée par "Roger, le fier grec", suite à
 une demande de la société possèdant Léonidas. La musique est aussi soumise à ces conditions.
 
 Il n'y a pas de site d'aide pour réussir à terminer 9K. C'est une épreuve que vous devez finir seul.
 Seulement après avoir fini 9K, vous pourrez vous considérer comme un vrai spartiate.








