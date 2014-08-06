  I. Installation
 II. Configuration
III. Utilisation
 IV. Divers

  I. Installation
  ------------------
  
 *** Premi�re installation ***

Pour assouvir votre besoin d'awesomitude, vous pourrez jouer � 9K apr�s avoir d�compress�
l'archive dans le dossier de votre choix. Placez vous ensuite via le terminal dans le dossier bin 
de celui qui a �t� d�compress� :

cd dossier/LIF7/PROJET/bin

Pour lancer le jeu en SDL :

Modifiez la ligne 6 et 7 du makefile : celle-ci doit appara�tre de cette fa�on :

	 JEU	= texte
	#JEU	= graphique

Utilisez la commande : make clean
Puis utilisez la commande : make
et enfin utilisez la commande ./9K_gfx


Pour lancer le jeu en Ncurses :

Modifiez la ligne 6 et 7 du makefile : celle-ci doit appara�tre de cette fa�on :

	 #JEU	= texte
	  JEU	= graphique

Utilisez la commande : make clean
Puis utilisez la commande : make
et enfin utilisez la commande ./9K_txt

N'oubliez pas d'avoir vos biblioth�ques SDL (image, ttf), FMOD et ncurses mises � jour pour pouvoir jouer.
 
 
 *** Mise � jour ***
 
 A votre grand d�sespoir, il n'y a pas de mises � jour pr�vues pour ce jeu. 
 Malgr� tout, vous pouvez nous contacter sur kevin.sauvageon@gmail.com melchior.fracas@wanadoo.fr
 pour toutes demandes de d�tails, d'autographes, de droit de reproduction, de droit d'adaptation et toutes questions sur la portance du code.
 
 
 
 II. Configuration
---------------------

 Le jeu tel que vous le prennez est configur� optimalement. Cependant, si, � vos risques et p�rils,
 vous ressentez l'envie d'une nouvelle exp�rience de jeu, vous pouvez configurer les variables suivantes :
 points de score par javelot �vit�, intervalle de chute des javelots (qui peut �tre en fonction du score), HP, le nombre de javelot par vague.
 
 
 III. Utilisation
---------------------

 Pour jouer, s�lectionnez votre mode de jeu. Ensuite, appuyez sur les touches pour faire bouger L�onidas.
 Bougez rapidement : il faut �viter les javelots que l'arm�e perse vous lance. Attention : les javelots 
 vous arrive dessus de plus en plus vite.
 Pour le mode illimit�, une fois la partie termin�e, faites une capture d'�cran et, le cas �ch�ant, 
 montrez la � vos amis et comparez vos scores, apr�s tout vous valez surement mieux qu'eux !




 IV. Divers
---------------

 Le nom de Leonidas ne nous appartient pas et pourra �tre remplac�e par "Roger, le fier grec", suite �
 une demande de la soci�t� poss�dant L�onidas. La musique est aussi soumise � ces conditions.
 
 Il n'y a pas de site d'aide pour r�ussir � terminer 9K. C'est une �preuve que vous devez finir seul.
 Seulement apr�s avoir fini 9K, vous pourrez vous consid�rer comme un vrai spartiate.








