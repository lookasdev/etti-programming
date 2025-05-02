#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Element {
    char cuvant[31];
    int gasit;
    int aparitii;
};

struct Nod {
    char cuvant[31];
    int freq;
    struct Nod * left;
    struct Nod * right;
};

struct Nod* creeazaNod(char* cuvant, int freq) {
    struct Nod *newNode = (struct Nod*) malloc(sizeof(struct Nod));
    strcpy(newNode->cuvant, cuvant);
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Nod* insereazaInArbore(struct Nod * root, char *cuvant, int freq) {
    if(root == NULL) return creeazaNod(cuvant, freq);
    
    if(strcmp(cuvant, root->cuvant) < 0) {
        root->left = insereazaInArbore(root->left, cuvant, freq);
    } else if(strcmp(cuvant, root->cuvant) >= 0)
    {
        root->right = insereazaInArbore(root->right, cuvant, freq);
    }
    
    return root;
}

void afisareInOrdine(struct Nod * root) {
    if(root != NULL) {
        afisareInOrdine(root->left);
        printf("%s\n", root->cuvant);
        afisareInOrdine(root->right);
    }
}

void afisareInPostOrdine(struct Nod * root) {
    if(root != NULL) {
        afisareInPostOrdine(root->left);
        afisareInPostOrdine(root->right);
        printf("%s\n", root->cuvant);
    }
}

struct Nod* findNode(struct Nod* root, char * cautat) {
    if(root == NULL) return NULL;
    
    int cmp = strcmp(cautat, root->cuvant);

    if (cmp == 0) return root;
    else if (cmp < 0) findNode(root->left, cautat);
    else if (cmp > 0) findNode(root->right, cautat);

}

void parcurge(struct Nod * root, struct Element elemente[], int *k) {
    if(root != NULL) {
        parcurge(root->left, elemente, k);
        strcpy(elemente[*k].cuvant, root->cuvant);
        elemente[*k].aparitii = root->freq;
        (*k)++;
        parcurge(root->right, elemente, k);
    }
}

int main() {
    struct Element elemente[1001];
    
    for(int i = 0; i < 1001; i++) {
        strcpy(elemente[i].cuvant, "0");
        elemente[i].gasit = 0;
        elemente[i].aparitii = 0;
    }
    
    char cuvinte[1001][31];
    int comanda, indexCuvant;
    scanf("%d %d", &comanda, &indexCuvant);
    
    int k = 0;
    
    while(1) {
        if(scanf("%s", cuvinte[k]) == EOF) break;
        k++;
    }
    
    int k2 = 0;
    for(int i = 0; i < k; i++) {
        int ok = 0;
        for(int j = 0; j < k2; j++) {
            if(strcmp(elemente[j].cuvant, cuvinte[i]) == 0)
            {
                elemente[j].aparitii++;
                ok = 1;
                break;
            }
            
        }
        if(!ok) {
            strcpy(elemente[k2].cuvant, cuvinte[i]);
            elemente[k2].aparitii++;
            k2++;
        }
    }
    
    // printf("%d\n", k2);
    
    struct Nod* array[26];
    for(int i = 0; i < 26; i++) {
        array[i] = NULL;
    }
    for(int i = 0; i < k2; i++) {
        char aux[31];
        strcpy(aux,  elemente[i].cuvant);
        int index = aux[0] - 'a';

        array[index] = insereazaInArbore(array[index], elemente[i].cuvant, elemente[i].aparitii);
    }

    if(comanda == 1) {
        
        for(int i = 0; i < k; i++) {
            printf("%s\n", cuvinte[i]);
        }
        
    } else if (comanda == 2) {
        
        for(int i = 0; i< k2; i++) {
            printf("%s %d\n", elemente[i].cuvant, elemente[i].aparitii);
        }
        
    } else if (comanda == 3) {
        
        for(int i = 0; i < 26; i++) {
            afisareInOrdine(array[i]);
        }
        
    } else if (comanda == 4) {
        
        char cautat[31];
        strcpy(cautat, cuvinte[indexCuvant]);
        int index = cautat[0] - 'a';
        
        struct Nod * toFind = findNode(array[index], cautat);
        afisareInPostOrdine(toFind);
        
    } else if (comanda == 5) {
        char cautat[31];
        strcpy(cautat, cuvinte[indexCuvant]);
        int index = cautat[0] - 'a';
        
        struct Nod * toFind = findNode(array[index], cautat);
        struct Element elemente2[101];
        int k3 = 0;
        parcurge(toFind, elemente2, &k3);
        // printf("%d", k3);
        
        for(int i = 0; i < k3-1; i++) {
            for(int j = i + 1; j < k3; j++) {
                if(elemente2[i].aparitii < elemente2[j].aparitii) {
                    struct Element aux = elemente2[i];
                    elemente2[i] = elemente2[j];
                    elemente2[j] = aux;
                }
            }
        }
        
        for(int i = 0; i < 2; i++) {
            printf("%s\n", elemente2[i].cuvant);
        }
    }
    return 0;
}