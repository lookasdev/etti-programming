#include<stdio.h>
#include <stdlib.h>
#include<string.h>

struct utilizator {
    char nume[31];
    char parola[31];
    int complexitate;
};

struct nod {
    struct utilizator user;
    struct nod * next;
};

int calcHash(int complexitate, int dim) {
    return complexitate % dim;
}

int calcHash2(char* parola, int dim) {
    int suma = 0;
    for(int i = 0; parola[i] != '\0'; i++) {
        suma += parola[i];
    }
    return suma % dim;
}

void introduceInHashmap(struct nod ** hashmap, int dim, struct utilizator user) {
    struct nod * nod_nou = (struct nod *) malloc(1*sizeof(struct nod));
    nod_nou->user = user;
    nod_nou->next = NULL;
    int hashValue = calcHash(user.complexitate, dim);
    
    if(hashmap[hashValue] == NULL) {
        hashmap[hashValue] = nod_nou;
    } else {
        struct nod * curent = hashmap[hashValue];
        while(curent->next != NULL) {
            curent = curent->next;
        }
        curent->next = nod_nou;
    }
}

void introduceInHashmap2(struct nod ** hashmap, int dim, struct utilizator user) {
    struct nod * nod_nou = (struct nod *) malloc(1*sizeof(struct nod));
    nod_nou->user = user;
    nod_nou->next = NULL;
    int hashValue = calcHash2(user.parola, dim);
    
    if(hashmap[hashValue] == NULL) {
        hashmap[hashValue] = nod_nou;
    } else {
        struct nod * curent = hashmap[hashValue];
        while(curent->next != NULL) {
            curent = curent->next;
        }
        curent->next = nod_nou;
        
        struct utilizator utilizatori[101];
        int nrUtilizatori = 0;
        
        curent = hashmap[hashValue];
        while(curent) {
            struct utilizator user = curent->user;
            utilizatori[nrUtilizatori] = user;
            nrUtilizatori++;
            curent = curent->next;
        }
        
        for(int i = 0; i < nrUtilizatori-1; i++) {
            for(int j = i+1; j < nrUtilizatori; j++) {
                if(utilizatori[i].complexitate > utilizatori[j].complexitate) {
                    struct utilizator aux;
                    aux = utilizatori[i];
                    utilizatori[i] = utilizatori[j];
                    utilizatori[j] = aux;
                }
            }
        }
        
        curent = hashmap[hashValue];
        int k = 0;
        while(curent && k < nrUtilizatori) {
            curent->user = utilizatori[k];
            k++;
            curent = curent->next;
        }
    }
}

void printHashmap(struct nod ** hashmap, int dim) {
    for(int i = 0; i < dim; i++) {
        if(hashmap[i] != NULL) {
            struct nod * curent = hashmap[i];
            while(curent) {
                struct utilizator user = curent->user;
                printf("%s %s %d\n", user.nume, user.parola, user.complexitate);
                curent = curent->next;
            }
        }
    }
}

void printHashmap2(struct nod ** hashmap, int dim) {
    for(int i = 0; i < dim; i++) {
        if(hashmap[i] != NULL) {
            struct nod * curent = hashmap[i];
            while(curent) {
                struct utilizator user = curent->user;
                printf("%s\n", user.nume);
                curent = curent->next;
            }
        }
    }
}

void elibereazaHashmap(struct nod ** hashmap, int dim) {
    for(int i = 0; i < dim; i++) {
        if(hashmap[i] != NULL) {
            struct nod * curent = hashmap[i];
            while(curent) {
                struct nod * to_free = curent;
                curent = curent->next;
                free(to_free);
            }
        }
    }
    free(hashmap);
}

int verifMajuscula(char c) {
    if(c >= 'A' && c <= 'Z') return 1;
    return 0;
}

int verifLitera(char c) {
    if(c >= 'A' && c <= 'Z') return 1;
    if(c >= 'a' && c <= 'z') return 1;
    return 0;
}

int calculComplexitate(char * parola) {
    int value = 0;
    int nrSimboluri = 0;
    value += strlen(parola);
    for(int i = 0; parola[i] != '\0'; i++) {
        if(verifMajuscula(parola[i])) value++;
        else if (!verifLitera(parola[i])) nrSimboluri++;
    }
    value += nrSimboluri * 2;
    return value;
}

int main() {
    struct utilizator utilizatori[101];
    int nrUtilizatori = 0;
    
    int dim = 101;
    int dim2 = 7;
    
    struct nod ** hashmap = (struct nod **) calloc (dim, sizeof(struct nod *)); // pt comanda 3
    struct nod ** hashmap2 = (struct nod **) calloc (dim2, sizeof(struct nod *)); // pt comanda 4
    
    while(1) {
        scanf("%s", utilizatori[nrUtilizatori].nume);
        if (strcmp(utilizatori[nrUtilizatori].nume, "STOP") == 0) break;
        scanf("%s", utilizatori[nrUtilizatori].parola);
        utilizatori[nrUtilizatori].complexitate = calculComplexitate(utilizatori[nrUtilizatori].parola);
        nrUtilizatori++;
    }
    
    int comanda;
    scanf("%d", &comanda);
    
    if (comanda == 1) {
        for(int i = 0; i < nrUtilizatori; i++) {
            printf("%s %s\n", utilizatori[i].nume, utilizatori[i].parola);
        }
    } else if (comanda == 2) {
        for(int i = 0; i < nrUtilizatori; i++) {
            printf("%s %s %d\n", utilizatori[i].nume, utilizatori[i].parola,  utilizatori[i].complexitate);
        }
    } else if (comanda == 3) {
        for(int i = 0; i < nrUtilizatori; i++) {
            introduceInHashmap(hashmap, dim, utilizatori[i]);
        }
        printHashmap(hashmap, dim);
    } else if (comanda == 4) {
        for(int i = 0; i < nrUtilizatori; i++) {
            introduceInHashmap2(hashmap2, dim2, utilizatori[i]);
        }
        printHashmap2(hashmap2, dim2);
    }
    
    elibereazaHashmap(hashmap, dim);
    elibereazaHashmap(hashmap2, dim2);
    
    return 0;
}