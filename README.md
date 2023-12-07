# Project: Spell Checker

We have implemented a spell checker in C that, based on a given dictionary, identifies words in a text that are not present in the dictionary.

## Compilation
To compile our entire project, you need to execute the command **make**. This will compile the entire project and create an executable for each of the different tests. You can remove all executables by running the command: **make clean**.

## Using the Executables
To run a dictionary verification test (all tests starting with "test_dico"), you need to execute the following command:


    ./bin/<test_name> textes/<with_or_without_accent>/<text_to_check> dictionnaire/<used_dictionary>

Example : `./bin/test_dico_arbre_prefixe textes/sans_accents/test.txt dictionnaire/dico1.txt`

If there is a syntax error in the arguments, you can request help by typing:

    ./bin/<name_of_the_test> h
    
Other tests are functionality tests of our spell checker and can be executed simply by running the following command:

    ./bin/<name_of_the_test>
---
# projet : Correcteur Orthographique

Nous avons réalisé en C un vérificateur orthographique qui, en se basant sur un dictionnaire donné, retourne les mots d'un texte qui ne sont pas présent dans le dictionnaire.

## Compilation
Pour compiler l'ensemble de notre projet, vous devez vous placer dans le répertoire : `champeth_rollandu_ruchlejs_apman`, et exécuter la commande **make**. Cela compilera l'ensemble du projet et créera un exécutable pour chacun des différents tests.
Vous pouvez supprimer l'ensemble des exécutables en exécutant la commande : **make clean**.

## Utilisation des exécutables
Afin d'exécuter un test de vérification de dictionnaire (tout les test commençant par "test_dico"), vous devez rester dans le répertoire `champeth_rollandu_ruchlejs_apman` et réaliser la commande suivante : 

    ./bin/<nom_du_test> textes/<avec_ou_sans_accent>/<texte_a_verifier> dictionnaire/<dictionnaire_utilisé>

Exemple : `./bin/test_dico_arbre_prefixe textes/sans_accents/test.txt dictionnaire/dico1.txt`

En cas de mauvaise syntaxe au niveau des arguments, vous pouvez faire appel à l'aide en tapant : 
    
    ./bin/<nom_du_test> h

Les autres tests sont des tests de fonctionnalité de notre vérificateur orthographique et s'exécute simplement en réalisant la commande suivante :

    ./bin/<nom_du_test>
