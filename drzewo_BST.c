#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define N 100

typedef struct drzewo
{
    int dana;
    struct drzewo *lewy;
    struct drzewo *prawy;
}drzewo;

void insertBST(drzewo **T,int key)
{
    if (*T == NULL)
    {
        *T = (drzewo*)malloc(sizeof(drzewo));
        (*T) -> lewy = NULL;
        (*T) -> prawy = NULL;
        (*T) -> dana = key;
    }
    else if(key<(*T)->dana)
    {
        insertBST(&((*T)->lewy),key);
    }
    else if(key>(*T)->dana)
    {
        insertBST(&((*T)->prawy),key);
    }
}

void izp(drzewo *T,int *lv,int clv)
{
    clv ++;
    if (clv > *lv)
        *lv = clv;
    if(T->lewy != NULL)
    {
        izp(T->lewy,lv,clv);
    }
    if(T->prawy != NULL)
    {
        izp(T->prawy,lv,clv);
    }
}

void printlvl(drzewo *T,int lv,int clv)
{
    if(clv == lv)
    {
        printf("%d ",T->dana);
    }
    else
    {
        clv ++;
        if (T->lewy != NULL)
            printlvl(T->lewy,lv,clv);
        if (T->prawy != NULL)
            printlvl(T->prawy,lv,clv);
    }
}

void level_order(drzewo *T)
{
    if(T)
    {
        int lv = -1, clv = -1;
        izp(T,&lv,clv);
        clv ++;
        for(int i=0;i<=lv;i++)
        {
            printlvl(T,i,clv);
            printf("\n");
        }
    }
}

void printlvl_v2(drzewo *T,int lv,int clv,int d,int* csp,int dnd)
{
    if(clv == lv)
    {
        if (T->dana > 9)
        {
            while ((*csp) < d-1)
            {
                (*csp)++;
                printf(" ");
            }
            printf("%d",T->dana);
            (*csp) += 2;
        }
        else
        {
            while ((*csp) < d)
            {
                (*csp)++;
                printf(" ");
            }
            printf("%d",T->dana);
            (*csp) +=1;
        }
    }
    else
    {
        clv ++;
        if (T->lewy != NULL)
        {
            if (dnd%2 != 0)
                dnd ++;
            printlvl_v2(T->lewy,lv,clv,(d-dnd/2),csp,dnd/2);
        }
        if (T->prawy != NULL)
        {
            if (dnd%2 != 0)
                dnd ++;
            if (T->dana > 9)
                d++;
            printlvl_v2(T->prawy,lv,clv,(d+dnd/2),csp,dnd/2);
        }
    }
}
void graficznie(drzewo *T)
{
    if(T)
    {
        int csp;
        int lv = -1, clv = -1,d,dnd;
        izp(T,&lv,clv);
        //printf("%d\n",lv);
        d = lv * pow(2,lv);
        dnd = d;
        clv ++;
         for(int i=0;i<=lv;i++)
        {
            csp = 0;
            printlvl_v2(T,i,clv,d,&csp,dnd);
            printf("\n");
            printf("\n");
            printf("\n");
        }
    }
}

void inorder(drzewo *T)
{
    if (T)
    {
        inorder(T->lewy);
        printf("%d ",T->dana);
        inorder(T->prawy);
    }
}

void preorder(drzewo *T)
{
    if (T)
    {
        printf("%d ",T->dana);
        preorder(T->lewy);
        preorder(T->prawy);
    }
}

void postorder(drzewo *T)
{
    if (T)
    {
        postorder(T->lewy);
        postorder(T->prawy);
        printf("%d ",T->dana);
    }
}

void printBST(drzewo *T)
{
    int wybor;
    printf("[1] - inorder\n");
    printf("[2] - preorder\n");
    printf("[3] - postorder\n");
    printf("[4] - level order\n");
    printf("[5] - reprezentacja graficzna\n");
    printf("podaj jaki tryb wypisania\n");
    printf("podaj: ");
    scanf("%d",&wybor);
    switch(wybor)
    {
    case(1):
        {
            inorder(T);
            break;
        }
    case(2):
        {
            preorder(T);
            break;
        }
    case(3):
        {
            postorder(T);
            break;
        }
    case(4):
        {
            level_order(T);
            break;
        }
    case(5):
        {
            graficznie(T);
            break;
        }
    }
}

void countBST(drzewo *T,int lv,int clv,int *il)
{
    if(clv == lv)
    {
        (*il)+=1;
    }
    else
    {
        clv ++;
        if (T->lewy != NULL)
            countBST(T->lewy,lv,clv,il);
        if (T->prawy != NULL)
            countBST(T->prawy,lv,clv,il);
    }
}

bool checkBST(drzewo *T,int lev,int clv,bool *k_p)
{
    if (lev-1 != clv)
    {
        if (T->lewy == NULL || T->prawy == NULL)
            return false;
        clv ++;
        if(!checkBST(T->lewy,lev,clv,k_p))
            return false;
        if(!checkBST(T->prawy,lev,clv,k_p))
            return false;
        return true;
    }
    else
    {
        if(!(*k_p) && T->lewy == NULL)
            (*k_p)=true;
        if((*k_p) && T->lewy != NULL)
            return false;
        if(!(*k_p) && T->prawy == NULL)
            (*k_p)=true;
        if((*k_p) && T->prawy != NULL)
            return false;
        return true;
    }
}

void addlvl(drzewo *T,int lv,int clv,int table[],int *i)
{
    if(clv == lv)
    {
        table[(*i)] = T->dana;
        (*i) ++;
    }
    else
    {
        clv ++;
        if (T->lewy != NULL)
            addlvl(T->lewy,lv,clv,table,i);
        if (T->prawy != NULL)
            addlvl(T->prawy,lv,clv,table,i);
    }
}

void tableBST(drzewo *T,int table[N])
{
    int roz = 0;
    for(int i=0;i<N;i++)
    {
        table[i] = -1;
    }
    if(T)
    {
        int lv = -1, clv = -1;
        izp(T,&lv,clv);
        clv ++;
        for(int i=0;i<=lv;i++)
        {
            addlvl(T,i,clv,table,&roz);
        }
    }

}

void szukaj(drzewo *T,drzewo **wezel,int key,drzewo **wezelp)
{
    while (T!=NULL)
    {
        if(key == T->dana)
        {
            *wezel = T;
            return NULL;
        }
        else if(key<T->dana)
        {
            *wezelp = T;
            T = T ->lewy;

        }
        else if(key>T->dana)
        {
            *wezelp=T;
            T = T->prawy;
        }
    }
}

void max_p(drzewo **T,drzewo **Tp)
{
    while((*T)->prawy != NULL)
    {
        *Tp = *T;
        *T=(*T)->prawy;
        max_p(T,Tp);
    }

}
void max_l(drzewo **T,drzewo **Tp)
{
    while((*T)->lewy != NULL)
    {
        *Tp = *T;
        *T=(*T)->lewy;
        max_l(T,Tp);
    }

}

void removeBST(drzewo *T,int key)
{
    drzewo *wezel,*rl,*rp,*rlp,*rpp,*wezelp;
    szukaj(T,&wezel,key,&wezelp);
    //printf("%d\n",wezel->dana);
    int lvl = -1,lvp= -1;
    if(wezel -> prawy != NULL)
    {
        rp = wezel->prawy;
        if (rp->lewy==NULL)
            rpp = wezel;
        izp(rp,&lvp,-1);
        max_l(&rp,&rpp);
    }
     if(wezel -> lewy != NULL)
     {
        rl = wezel->lewy;
        if(rl->prawy==NULL)
            rlp = wezel;
        izp(rl,&lvl,-1);
        max_p(&rl,&rlp);
     }
    if (wezel -> prawy == NULL && wezel->lewy == NULL)
    {
        //printf("cokolwiek\n");
        if (wezelp->lewy->dana == wezel->dana)
            wezelp -> lewy = NULL;
        else
            wezelp->prawy = NULL;
        free(wezel);
    }
    else if (lvl<lvp)
    {
        // usuwanie rp
        //wezel -> dana = rp->dana;
        if(rpp != wezel)
        {
            wezel -> dana = rp->dana;
            rpp -> lewy = rp->prawy;
        }
        else
            {
            wezel -> dana = rp->dana;
            wezel -> prawy = rp -> prawy;//NULL
            }
        free(rp);
    }
    else
    {
        // usuwanie rl
        //wezel -> dana = rl->dana;
        if(rlp != wezel)
        {
            wezel -> dana = rl->dana;
            rlp -> prawy = rl -> lewy;
        }
        else
        {
            wezel -> dana = rl->dana;
            wezel -> lewy = rl -> lewy;//NULL
        }
        free(rl);
    }


}
bool czy_w_tablicy(int liczby[],int war)
{
    for(int i=0;i<N;i++)
    {
        if (liczby[i] == war)
            return true;
    }
    return false;
}
int main()
{
    int liczby[N];
    for(int i=0;i<N;i++)
        liczby[N]=-1;
    printf("podaj ile dodac liczb losowych: ");
    int wybor, key, lev, il,roz;
    scanf("%d",&il);
    bool k_p = false;
    int table[N];
    drzewo *root = NULL;
    drzewo *current = NULL;
    srand(time(NULL));
    for(int i=0;i<il;i++)
    {
        //printf("cokolwiek\n");
        key = rand()%100;
        while(czy_w_tablicy(liczby,key))
            key = rand()%100;
        liczby[i] = key;
    }
    //printf("cokolwiek\n");
    for(int i=0;i<il;i++)
    {
        insertBST(&root,liczby[i]);
    }
    //printf("cokolwiek\n");
    //int przedzial = 100;
    //int il_znak = 10;
    while(1)
    {
        printf("[1] - dodanie nowego elementu do drzewa\n");
        printf("[2] - wypisanie drzewa\n");
        printf("[3] - wyliczenie liczby wezlow na danym poziomie\n");
        printf("[4] - wyliczenie wysokosci drzewa\n");
        printf("[5] - sprawdzenie czy drzewo ma strukture kopca\n");
        printf("[6] - reprezentacja tablicowa\n");
        printf("[7] - usuniecie elementu z drzewa\n");
        printf("podaj jaka operacje wykonac\n");
        printf("podaj: ");
        scanf("%d",&wybor);
        switch(wybor)
        {
            case(1):
            {
                printf("podaj wartosc\n");
                printf("podaj: ");
                scanf("%d",&key);
                insertBST(&root,key);
                break;
            }
            case(2):
            {
                printBST(root);
                printf("\n");
                break;
            }
            case(3):
                {
                    printf("podaj poziom to policzenia: ");
                    scanf("%d",&lev);
                    il = 0;
                    countBST(root,lev,0,&il);
                    printf("ilosc wezlow na poziomie %d = %d\n",lev,il);
                    break;
                }
            case(4):
                {
                    lev = -1;

                    izp(root,&lev,-1);
                    printf("drzewo ma wysokosc rowna %d\n",lev);
                    break;
                }
            case(5):
                {
                    lev = -1;
                    izp(root,&lev,-1);
                    if(checkBST(root,lev,0,&k_p))
                    {
                        printf("to jest kopiec\n");
                    }
                    else
                        printf("to nie jest kopiec\n");
                    break;
                }
            case(6):
                {
                    lev = -1;
                    izp(root,&lev,-1);
                    if(checkBST(root,lev,0,&k_p))
                    {
                        tableBST(root,table);
                        int i = 0;
                        printf("[ ");
                        while(i<N && table[i] != -1)
                        {
                            printf("%d ",table[i]);
                            i++;
                        }
                        printf("]");
                    }
                    printf("\n");
                    break;
                }
            case(7):
                {
                    if (root != NULL)
                    {
                        printf("podaj wartosc do usuniecia: ");
                        scanf("%d",&key);
                        removeBST(root,key);
                        break;
                    }
                   else
                    printf("drzewo puste\n");
                }
        }
    }
    return 0;
}
