
# Projet de Compression de Données

---

[GitHub](https://github.com/DogtorWho/Projet_CDD_L3) - par Jean Thiebault et Teiter Hugo

## Table de contenu

1. [Présentation](#presentation)
2. [Some Gestion des données](#gestion)
    1. [Communication Client - Serveur](#communication)
3. [Les codeurs](#codeurs)
    1. [LZW](#lzw)
        1. [Nos Types Abstraits](#types)
            1. [Dictionnaire](#dictionnaire)
            2. [Tableau de 12-bit](#tab12)
            3. [Tableau d'octet](#tabByte)
        2. [L'encodage](#encodage)
        3. [Le décodage](#decodage)
        4. [Performances](#performances)
    2. [Huffman](#huffman)
        1. [Nos Types Abstraits](#types2)
            1. [Arbre Binaire](#arbre)
            2. [Tableau de fréquence des caractères](#frequence)
            3. [File de prioritée](#file)
        2. [L'encodage](#encodage2)
        3. [Le décodage](#decodage2)
        4. [Performances](#performances2)

# Présentation <a name="presentation"></a>

---

Dans ce projet nous avons mit en place un systeme d'encodage / décodage de fichiers texte au format ASCII.
Ce systeme comprend un programme client et un programme serveur communicant grace au protocole TCP.


# Gestion des données <a name="gestion"></a>

---

Pour pouvoir s'échanger des données, le client doit se connecter au serveur via le protocole TCP, c'est pour cela que tant que le serveur va attendre que le client se connecte a lui avant de commencer quoi que se soit en rapport avec l'encodage.
Dans ce projet nous avons choisit d'envoyer les packets octets par octets entre le client et le serveur.

## Communication Client - Serveur <a name="communication"></a>

Apres avoir etes connecté, le client et le serveur communique comme ci-dessous pour realiser l'encodage puis le décodage :
1. **Client -** 
    - Envoi le nom du fichier à encoder et le type d'encodage choisit
2. **Serveur -** 
    - Recoit les informations
    - Regarde si il possède un fichier du meme nom que celui envoyé dans sa base de fichiers
    - Encode le fichier selon le type choisit
    - Envoi le code du fichier
3. **Client -**
    - Recoit le fichier encoder
    - Decode selon le type choisit au depart
    - Creer finalement le fichier texte décodé

Le serveur coupe la connection dès que son travail est terminé


# Les codeurs <a name="codeurs"></a>

---

Pour ce projet nous avons produit deux codeurs, mais rien n'empecherait d'en ajouter d'autres plus tard.
Dans cette partie nous allons présenter en detaille ces codeurs.

## LZW <a name="lzw"></a>

Le codeur [LZW](https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch) (ou Lempel–Ziv–Welch) utilise un dictionaire genéré independament dans l'encodeur et le décodeur, ce qui à pour avantage que le décodeur n'a besoin que du code sortie a la fin de l'encodage.

> **Attention :**
> Notre codeur ne fonctionne qu'avec des fichiers contenant des caracteres ASCII

### Nos Types Abstraits <a name="types"></a>

L'implémentation du codeur LZW en langage C nous a demandé de créer quelques types abstraits pour nous aider à la manipulation de celui-ci.

#### Dictionnaire <a name="dictionnaire"></a>

Comme ce codeur utilise un systeme de dictionnaire, notre premier TA créé a logiquement été un dictionaire avec la structure suivante :

```c
typedef struct {
	char *mots[DICO_SIZE];
	int nb_mots;
} dico_t; 
```
Celle-ci nous permet de stocker les mots créés durant l'encodage ou le décodage.

En plus des fonctions de bases comme initializer ou libérer la structure, ajouter ou trouver un élément, ou encore l'affichage des données, nous avons dut réfléchir à un moyen pour mettre en pratique l'encodage de très gros fichiers qui consommeraient trop de mémoire si l'on remplissai le dictionnaire naivement.
Pour cela nous avons écrit une fonction qui vide le dictionnaire lorqu'il est plein, tout en gardant les caracterers ASCII stockés au début du dictionnaire.

#### Tableau de 12-bit <a name="tab12"></a>

Dans cette encodeur LZW, nous travaillons avec des paquets de 12 bits et non des octets, c'est pour cela que nous avons créé cette structure nous permettant de stocker nos codes.
Cette structure est constituée des éléments suivant :

```c
typedef struct {
    twelveBit_t *array;
    size_t used;
    size_t size;
} twelveBitArray;
```

Des fonctions d'initialisation, libération, recherche et affichage ont aussi été implementés.
De plus, nous avons rajouté une fonctions qui permet de créer un fichier binaire à partir du tableau.

#### Tableau d'octet <a name="tabByte"></a>

Pour pouvoir encoder un message dans un fichier binaire nous avons eu besoin de découper nos pacquets de 12 bits en octets, ce qui nous a facilité l'écriture de données dans ce fichier.
Cette structure est très semblable à la précédente :

```c
typedef struct {
    byte_t *array;
    size_t used;
    size_t size;
} byteArray;
```

Comme pour le tableau de 12-bit nous avons créé toutes les fonctions de base, plus deux fonctions pour créer un fichier binaire à partir du tableau et un tableau à partir d'un fichier binaire.


### L'encodage <a name="encodage"></a>

Pseudo code :

```
DEBUT
    S = "";
    dico = dico_t; 
    tab_12bit = twelveBitArray;
    tab_codes = twelveBitArray;
    code = 256; // fin des caracteres ASCII
    
    REMPLIR dico avec les caracteres ASCII;
    REMPLIR tab_12bit avec les valeurs binaires des caracteres ASCII;
    
    TANT QUE la source n'est pas vide FAIRE
        LIRE le caractere m dans le flux d'entrée;
        SI (S + m) existe deja dans dico ALORS
            S = S + m;
        SINON
            SI S est un caractere ALORS
                AJOUTER la valeur binaire de S dans tab_codes;
            SINON
                POUR chaque mot de dico FAIRE
                    SI le mot correspond à S ALORS
                        Ajouter la valeur binaire du mot dans tab_codes;
                        STOP;
                    FSI
                FPOUR
            FSI
            SI dico est plein ALORS
                Vider dico;
            FSI
            AJOUTER (S + m) dans dico;
            AJOUTER code dans tab_codes;
            code++;
            S = m;
        FSI
    FTQ   
    
    SI S est un caractere ALORS
        AJOUTER la valeur binaire de S dans tab_codes;
        SINON
            POUR chaque mot de dico FAIRE
                SI le mot correspond à S ALORS
                    AJOUTER la valeur binaire du mot dans tab_codes;
                    STOP;
                FSI
            FPOUR
        FSI
    FSI
    
    tab_byte = byteArray;
    TRANSFORMER tab_12bit en tab_byte;
    TRANSFORMER tab_byte en fichier binaire; // fichier contenant le message encodé
FIN
```

### Le décodage <a name="decodage"></a>

Pseudo code :

```
DEBUT
    S = "";
    dico = dico_t; 
    tab_12bit = twelveBitArray;
    code = 256; // fin des caracteres ASCII

    REMPLIR dico avec les caracteres ASCII;
    REMPLIR tab_12bit avec les valeurs binaires des caracteres ASCII;
    
    msg_encodé = fichier binaire d'entrée;
    tab_byte = byteArray;
    tab_codes = twelveBitArray;
    
    TRANSFORMER msg_encodé en tab_byte;
    TRANSFORMER tab_byte en tab_codes; // tab_codes contient maintenant les codes à décoder
    
    TANT QUE i < à la taille de tab_codes FAIRE
        c = tab_codes[i];
        SI c est différent de 0 ALORS
            SI c est un caractere ALORS
                m = c;
                ECRIRE c dans la sortie;
                SI (S + m) existe deja dans le dictionnaire ALORS
                    S = S + m;
                SINON
                    SI dico est plein ALORS
                        VIDER dico;
                    FSI
                    AJOUTER (s + m) dans dico;
                    AJOUTER code dans tab_12bit;
                    code++;
                    S = m;
                FSI
            SINON // c contient plusieurs caracteres
                SI c n'est pas dans dico ALORS
                    SI dico est plein ALORS
                        Vider dico;
                    FSI
                    AJOUTER (S + S) dans dico;
                    AJOUTER code dans tab_12bit;
                    code++;
                    S = "";
                FSI
                m = c;
                POUR chaque caractere c_m de m FAIRE
                    Ajouter c_m dans le flux de sortie; // reconstitution du message
                    SI (S + c_m) existe deja dans dico ALORS
                        S = (S + c_m);
                    SINON
                        SI dico est plein ALORS
                            Vider dico;
                        FSI
                        AJOUTER (s + c_m) dans dico;
                        AJOUTER code dans tab_12bit;
                        code++;
                        S = c_m;
                    FSI
                FPOUR
            FSI
        FSI
    FTQ
FIN
```


### Performances <a name="performances"></a>

Voici le résultat de la compression de quelques fichiers avec notre algorithme LZW :

| Nom du fichier | Taille du fichier | Taille compressée | Taux de compression |
| :---           | :---              | :---              | :---                |
| Text_de_base   | 241 o             | 270 o             | 112%                |
| 10_000_bytes   | 10 035 o          | 4 881 o           | 49%                 |
| 100_000_bytes  | 100 332 o         | 47 148 o          | 47%                 |
| 1_000_000_bytes| 1 003 320 o       | 468 416 o         | 47%                 |
| Musketeers     | 1 328 616 o       | 736 167 o         | 55%                 |
| Queens         | 656 130 o         | 380 610 o         | 58%                 |


## Huffman <a name="huffman"></a>

Le codeur de [Huffman](https://en.wikipedia.org/wiki/Huffman_coding) est un codeur entropique generant une table de code qui faut transmettre au décodeur en plus du message encodé.
[Ce site](https://www.programiz.com/dsa/huffman-coding) nous a beaucoup inspiré pour la création de ce codeur car la description des étapes et très claire.
> **Attention :**
> Notre codeur ne fonctionne qu’avec des fichiers contenant des caractères ASCII, il supprimera les caracteres non ASCII du fichier décodé.

### Nos Types Abstraits <a name="types2"></a>

Pour pouvoir implementer l'algorithme de Huffman dans un cas concret nous avons eu a construire certains types abstraits qui vons nous etre utile par la suite.


#### Tableau de fréquence des caracteres <a name="frequence"></a>

L'algorithme de Huffman utilise la fréquence des caractères présent dans le fichier d'entrée pour pouvoir l'encoder, pour retenir ces données nous avons mit en place la structure suivante :

```c
typedef struct FreqChar{
  char* A_char; // tableau de caractères
  int* A_freq; // tableau de fréquence
  int size;
} FreqChar;
```

En plus de cela nous avons les fonctions usuelles pour utilisé cette structure et une fonction de tri des tableaux.
La fonction principale de cette structure reste la conversion d'un fichier texte en un tableau de fréquence, ce qui permet de commencer l'encodage.

#### Arbre Binaire <a name="arbre"></a>

Ce codeur repose essentiellment sur un arbre binaire qui va changer de forme au fur et a mesure que les code se créent.
Nous avons donc besoin d'une structure pour pouvoir controler cet arbre :

```c
typedef struct HuffmanTreeNode {
  int key; // fréquence
  char data; // caractère
  char bit; // 0 or 1
  char* binary_value; // ex : 100, 0, 1010
  bool haveData; // utile pour la création des codes

  struct HuffmanTreeNode *left;
  struct HuffmanTreeNode *right;
} HuffmanTreeNode;

typedef struct HuffmanTree {
  struct HuffmanTreeNode *root;
  int size;
} HuffmanTree;
```

Nous avons ajouté des fonctions d'initialisation, de libération, d'insertion ou encore d'affichage pour l'arbre mais aussi pour ses noeuds car les fonctions de l'arbre sont en majorité recursives.
De plus, nous pouvons transformer un tableau de fréquences (la structure ci-dessus) en un arbre de Huffman.
Pour la création des codes nous avons une fonction qui permet d'ajouter aux noeuds leur code lorsque l'arbre est terminé, ainsi qu'une autre permettant de sauvegarder ces codes dans un fichier.


#### File de prioritée <a name="file"></a>

Cette structure ne sert qu'à modifier plus facilement la forme de l'arbre pendant sa création ([Exemple visuel](https://www.programiz.com/dsa/huffman-coding)) ce qui limite les appels récursifs dans l'arbre.

```c
typedef struct QueueNode {
  HuffmanTreeNode *data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode* first;
  int size;
} Queue;
```

Il n'y a pas de fonction spéciale pour cette file de priorité a part l'insertion en premier ou l'insertion ascendante en fonction de la clé du noeud.


### L'encodage <a name="encodage2"></a>

Pseudo code :

```
DEBUT
    tab_freq = FreqChar; // tableau de fréquence
    arbre = HuffmanTree; // arbre de Huffman
    
    TRANSFORMER la source d'entrée en tab_freq;
    TRANSFORMER tab_freq en arbre;
    
    SAUVEGARGER les codes de arbre;
    
    TANT QUE la source n'est pas vide FAIRE
        LIRE le caractere m dans le flux d'entrée;
        ECRIRE le code correspondant à m dans le flux de sortie;
    FTQ
FIN
```


### Le décodage <a name="decodage2"></a>

Pseudo code :

```
DEBUT
    tab_byte = byteArray; // tableau d'octet
    tab_freq = FreqChar; // tableau de fréquence
    arbre = HuffmanTree; // arbre de Huffman
    
    TRANSFORMER la source d'entrée en tab_byte;
    TRANSFORMER la table de codes en tab_freq;
    TRANSFORMER tab_freq en arbre;
    
    // Parcours de l'arbre depuis la racine
    POUR chaque octet de tab_byte FAIRE
        POUR chaque bit de l'octet FAIRE
            SI l'octet vaut 1 ALORS
                ALLER à droite de l'arbre;
            SINON
                ALLER à gauche de l'arbre;
            FSI
            
            SI le noeud de l'arbre a un caractère ALORS
                SI le caractère ne correspond pas à la fin du fichier ALORS
                    ECRIRE le caractère dans le flux de sortie; // reconstitution du message
                SINON
                    STOP; // le message est terminé
                FSI
            FSI
        FPOUR
    FPOUR
FIN
```


### Performances <a name="performances2"></a>

Voici le résultat de la compression de quelques fichiers avec notre algorithme Huffman :

| Nom du fichier | Taille du fichier | Taille compressée | Taux de compression |
| :---           | :---              | :---              | :---                |
| Text_de_base   | 241 o             | 139 o             | 58%                 |
| 10_000_bytes   | 10 035 o          | 5 391 o           | 53%                 |
| 100_000_bytes  | 100 332 o         | 53 801 o          | 54%                 |
| 1_000_000_bytes| 1 003 320 o       | 538 256 o         | 54%                 |
| Musketeers     | 1 328 616 o       | 763 031 o         | 57%                 |
| Queens         | 656 130 o         | 383 883 o         | 58%                 |


---

Rapport de Projet - Jean Thiebault - Teiter Hugo


