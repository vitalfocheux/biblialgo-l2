//valgrind ./algorithms --gtest_filter=(NomTest).*

#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void array_create(struct array *self) {
  assert(self != NULL);
  self->size = 0;
  self->data = calloc((self->size + 1), sizeof(int));
  self->capacity = 1;
}

void array_create_from(struct array *self, const int *other, size_t size) {
  assert(self != NULL);
  self->size = size;
  self->data = calloc(self->size, sizeof(int));
  self->capacity = self->size;
  for(size_t i = 0; i < size; ++i){ //on insère les éléments de other dans self->data
    self->data[i] = other[i];
  }
}

void array_destroy(struct array *self) {
  assert(self != NULL);
  free(self->data);
  self->data = NULL;
}

bool array_empty(const struct array *self) {
  assert(self != NULL);
  if(self->size == 0){
    return true;
  }
  return false;
}

size_t array_size(const struct array *self) {
  assert(self != NULL);
  return self->size;
}

bool array_equals(const struct array *self, const int *content, size_t size) {
  assert(self != NULL);
  if(array_size(self) != size){ //si les 2 tableaux ne sont pas de même taille renvoie faux
    return false;
  }
  for(size_t i = 0; i < size; ++i){ //sinon on parcours les indices des 2 tableaux pour regarder leurs éléments
    if(content[i] != self->data[i]){
      return false;
    }
  }
  return true;
}


void array_push_back(struct array *self, int value) {
  if(self->size == self->capacity){ //si la capacité du tableau est égale à sa taille alors on va allouer un tableau d'une capacité 2 fois plus grande que l'ancienne
    self->capacity *= 2;
    int *data_temp = calloc(self->capacity, sizeof(int));
    for(size_t i = 0; i < array_size(self); ++i){
      data_temp[i] = self->data[i];
    }
    free(self->data);
    self->data = data_temp; 
  }
  self->data[self->size] = value; //on ajoute la valeur à l'indice de la taille du tableau
  self->size += 1;
}

void array_pop_back(struct array *self) {
  int *data_temp = calloc(self->capacity, sizeof(int));
  for(size_t i = 0; i < array_size(self)-1; ++i){
    data_temp[i] = self->data[i];
  }
  free(self->data);
  self->data = data_temp;
  self->size -= 1;
}

void array_insert(struct array *self, int value, size_t index) {
  if(index == array_size(self)){ //si on veut insérer à la fin alors on utilise la fonction array_push_back
    array_push_back(self, value);
  }else{
    if(self->size == self->capacity){ //sinon si la taille est égale à la capacité on va allouer un tableau d'une capacité 2 fois plus grande que l'ancienne 
      self->capacity *= 2;
      int *data_temp = calloc(self->capacity + 1, sizeof(int));
      if(index == 0){               //si l'index est égale à 0 alors on initalise l'indice 0 du nouveau tableau à la valeur est on y insère tous les autres éléments de self
        data_temp[0] = value;
        for(size_t i = 0; i < array_size(self); ++i){
          data_temp[i+1] = self->data[i];
        }
      }else{                        //sinon on insère tous les éléments de self dans le nouveau tableau jusqu'à l'index puis ensuite on insère la valeur et enfin on insère le reste des éléments de self
        for(size_t i = 0; i < index; ++i){
          data_temp[i] = self->data[i];
        }
        data_temp[index] = value;
        for(size_t i = index; i < array_size(self); ++i){
          data_temp[i+1] = self->data[i];
        }
      }
      free(self->data);
      self->data = data_temp;
    }else{
      int *data_temp = calloc(self->capacity, sizeof(int)); //sinon on va allouer un nouveau tableau de la même taille pour insérer les éléments de self->data avec l'index en moins
      if(index == 0){               //si l'index est égale à 0 alors on initalise l'indice 0 du nouveau tableau à la valeur est on y insère tous les autres éléments de self
        data_temp[0] = value;
        for(size_t i = 0; i < array_size(self); ++i){
          data_temp[i+1] = self->data[i];
        }
      }else{                        //sinon on insère tous les éléments de self dans le nouveau tableau jusqu'à l'index puis ensuite on insère la valeur et enfin on insère le reste des éléments de self
        for(size_t i = 0; i < index; ++i){
          data_temp[i] = self->data[i];
        }
        data_temp[index] = value;
        for(size_t i = index; i < array_size(self); ++i){
          data_temp[i+1] = self->data[i];
        }
      }
      free(self->data);
      self->data = data_temp;
    }
    ++self->size;
  }
}

void array_remove(struct array *self, size_t index) {
  if(index == array_size(self)-1){                        //si on supprime à la fin alors on utilise la fonction array_pop_back
    array_pop_back(self);
  }else{
    int *data_temp = calloc(self->capacity, sizeof(int)); //sinon on alloue un nouveau tableau iù on va insérer tous les éléments de self->data sauf celui situé à l'index
    if(index == 0){
      for(size_t i = 0; i < array_size(self)-1; ++i){
        data_temp[i] = self->data[i+1];
      }
      free(self->data);
      self->data = data_temp;
    }else{
      for(size_t i = 0; i < index; ++i){
        data_temp[i] = self->data[i];
      }
      for(size_t i = index; i < array_size(self)-1; ++i){
        data_temp[i] = self->data[i+1];
      }
      free(self->data);
      self->data = data_temp;
    }
    --self->size;
  }
}

int array_get(const struct array *self, size_t index) {
  if((index >= self->size)||((int)(index) < 0)){
    return 0;
  }
  return self->data[index];
}

void array_set(struct array *self, size_t index, int value) {
  if(((int)(index) >= 0)&&(index < self->size)){
    self->data[index] = value;
  }
  
}

size_t array_search(const struct array *self, int value) {
  for(size_t i = 0; i < self->size; ++i){
    if(self->data[i] == value){
      return i;
    }
  }
  return self->size;
}

size_t array_recherche_dichotomique(const struct array *self, size_t size, int value, size_t lo, size_t hi){
  if(lo == hi){                                                                           //cas où le tableau est un seul élément
    return size;
  }
  size_t moitie = (lo + hi) / 2;                                                          //on calcule l'indice de la moitie du tableau
  if(value < self->data[moitie]){                                                         //si la valeur est plus petite que la veleur du milieu on effectue une recherche sur la premiere moitie du tablea
    return array_recherche_dichotomique(self, size, value, lo, moitie);
  }
  if(value > self->data[moitie]){                                                         //sinon on effectue une recherche sur la deuxieme moitie du tableau
    return array_recherche_dichotomique(self, size, value, moitie + 1, hi);
  }
  return moitie;
}

size_t array_search_sorted(const struct array *self, int value) {
  return array_recherche_dichotomique(self, array_size(self), value, 0, array_size(self));
}

bool array_is_sorted(const struct array *self) {
  if(self->size == 0){
    return true;
  }
  for(size_t i = 1; i < self->size; ++i){
    if(self->data[i-1] >= self->data[i]){
      return false;
    }
  }
  return true;
}


ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
  ptrdiff_t l = i;
  const int pivot = self->data[i]; //on récupère le première élément de self->data en tant que pivot
  int temp = self->data[j];         //on fait une permutation entre le pivot et self->data[j] (souvent le dernier élément)
  self->data[j] = pivot;
  self->data[i] = temp;
  for(ptrdiff_t k = i; k < j; ++k){   //on va regarder tous les éléments de self->data jusqu'au pivot et effectuer une permutation si lélément est plus petit que le pivot
    if(self->data[k] < pivot){
      temp = self->data[k];
      self->data[k] = self->data[l];
      self->data[l] = temp;
      ++l;
    }
  }
  temp = self->data[l];
  self->data[l] = self->data[j];
  self->data[j] = temp;
  return l;
}

void array_quick_sort_recursive(struct array *self, ptrdiff_t i , ptrdiff_t j){
  if(i < j){
    ptrdiff_t indice_pivot = array_partition(self, i, j); //on recherche l'indice du pivot
    array_quick_sort_recursive(self, i, indice_pivot);    //puis on va effectuer récursivement le tri rapide sur la partie gauche du tableau jusqu'au pivot
    array_quick_sort_recursive(self, indice_pivot + 1, j); //puis sur la partie droite du tableau après le pivot
  }
}

void array_quick_sort(struct array *self) {
  array_quick_sort_recursive(self, 0, self->size - 1);
}

void array_heap_sort(struct array *self){
  if(array_is_sorted(self)){
    return;
  }
  int i;
  int hi = 0;
  while(hi < (int)(self->size - 1)){                  //on effectue une boucle tant que le hi est plus petit que la taille du tableau
    i = 0;
    while(i < (int)(self->size - hi)){                //on effectue une boucle tant que i est plus petit que la taille du tableau moins hi
      if(self->data[i] > self->data[(i - 1) / 2]){    //si la valeur à l'indice i est plus grande que son parent alors on va effectuer un echange entre le fils et le pere
        int tmp = self->data[i];
        self->data[i] = self->data[(i - 1) / 2];
        self->data[(i - 1) / 2] = tmp;
        i = 0;
      }
      ++i;
    }
    int tmp = self->data[self->size - hi - 1];        //on va effectuer un echange final entre la derniere valeur et la premiere
    self->data[self->size - hi - 1] = self->data[0];
    self->data[0] = tmp;
    ++hi;
  }
}

bool array_is_heap(const struct array *self) {
  if(array_empty(self)){                        //on teste le cas où self est un tableau vide
    return true;
  }
  int i = self->size - 1;
  while(i > 0){                       //on parcours le tableau depuis la fin jusqu'à la moitié
    if(self->data[i] > self->data[(i - 1) / 2]){   //si le parent est inférieur au fils alors on retourne false
      return false;
    }
    --i;
  }
  return true;
}



void array_heap_add(struct array *self, int value) {
  assert(array_is_heap(self));
  size_t i = self->size;
  array_push_back(self, value);                 //on va inserer la valeur à la fin du tableau
  while(i > 0){                                 //on va effectuer un boucle pour remonter la valeur si elle est plus grande que son parent
    size_t j = (i - 1) / 2;
    if(self->data[i] < self->data[j]){
      return;
    }
    int temp = self->data[i];
    self->data[i] = self->data[j];
    self->data[j]= temp;
    i = j;
  }
}

int array_heap_top(const struct array *self) {
  return self->data[0];
}

void array_heap_remove_top(struct array *self) {
  assert(array_is_heap(self));
  self->data[0] = self->data[self->size - 1];                                     //on modifie la premiere valeur du tableau par la derniere
  size_t i = 0;
  while(i < (self->size - 1) / 2){                                                //on va effectuer une boucle pour descendre la premiere valeur si elle est plus petite qu'une des 2 valeurs de ses fils
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    if((self->data[i] > self->data[left])&&(self->data[i] > self->data[right])){
      return;
    }
    size_t j = (self->data[left] > self->data[right]) ? left : right;
    int temp = self->data[i];
    self->data[i] = self->data[j];
    self->data[j]= temp;
    i = j;
  }
  --self->size;
}



/*
 * list
 */



void list_create(struct list *self) {
  assert(self != NULL);
  self->first = NULL;
  self->last = NULL;
}

void list_create_from(struct list *self, const int *other, size_t size) {
  assert(self != NULL);
  list_create(self);
  for(size_t i = 0; i < size; ++i){
    list_push_back(self, other[i]);
  }
}

void list_destroy(struct list *self) {
  assert(self != NULL);
  while(self->first != NULL){
    list_pop_back(self);
  }
}

bool list_empty(const struct list *self) {
  assert(self != NULL);
  return ((self->first == NULL)&&(self->last == NULL));
}

int list_size_rec(const struct list_node *self){
  if(self->next == NULL){
    return 0;
  }
  return 1 + list_size_rec(self->next);
}

size_t list_size(const struct list *self) {
  assert(self != NULL);
  if(list_empty(self)){
    return 0;
  }
  return 1 + list_size_rec(self->first);
}

bool list_equals(const struct list *self, const int *data, size_t size) {
  struct list_node *courant = self->first;
  if((list_size(self) != size)||(courant->data != data[0])){ //on vérifie le cas où ils n'auraient pas la même taille ou les cas où leurs premiers éléments sont différents
    return false;
  }
  courant = courant->next;
  for(size_t i = 1; i < size; ++i){   //ensuite on va effectuer un parcours où on va regarder chaque éléments un par un
    if(data[i] != courant->data){
      return false;
    }
    courant = courant->next;
  }
  return true;
}

void list_push_front(struct list *self, int value) {
  if(list_empty(self)){
    self->first = malloc(sizeof(struct list_node)); //si la liste est vide on va initialisé self->first et self->last à la même valeur
    self->first->data = value;
    self->first->next = NULL;
    self->first->prev = NULL;
    self->last = self->first;
  }else{  
    struct list_node *push = malloc(sizeof(struct list_node));  //sinon le prev de self->first devient le nouveau noeud et le next du nouveau noeud  devient self->first
    push->data = value;
    self->first->prev = push;
    push->next = self->first;
    push->prev = NULL;
    self->first = push;
  }  
}

void list_pop_front(struct list *self) {
  assert(!list_empty(self));
  if(list_size(self) == 1){             //si la liste à une taille de 1 on va supprimer juste self->first qui est aussi égal à self->last et mettre ses 2 à NULL
    free(self->first);
    self->first = NULL;
    self->last = NULL;
  }else{
    struct list_node *pop = self->first; //sinon avec un noeud temporaire on va récupérer self->first et self->first devient son next
    self->first = self->first->next;
    self->first->prev = NULL;
    free(pop);
  }
}

void list_push_back(struct list *self, int value) {
  if(list_empty(self)){
    self->first = malloc(sizeof(struct list_node));     //si la liste est vide on fait comme dans list_push_front
    self->first->data = value;
    self->first->next = NULL;
    self->first->prev = NULL;
    self->last = self->first;
  }else{
    struct list_node *push = malloc(sizeof(struct list_node));  //sinon le next de self->last devient le nouveau noeud et le prev du nouveau noeud  devient self->last
    push->data = value;
    self->last->next = push;
    push->prev = self->last;
    push->next = NULL;
    self->last = push;
  }
}

void list_pop_back(struct list *self) {
  assert(!list_empty(self));
  if(list_size(self) == 1){           //si la taille de la liste est égal à 1 on fait comme dans list_pop_front
    free(self->first);
    self->first = NULL;
    self->last = NULL;
  }else{
    struct list_node *pop = self->last; //sinon avec un noeud temporaire on va récupérer self->last et self->last devient son prev
    self->last = self->last->prev;
    self->last->next = NULL;
    free(pop);
  }
}


void list_insert(struct list *self, int value, size_t index) {
  assert((int)(index) >= 0);
  assert(index <= list_size(self));
  if(index == 0){                                             //si on veut insérer au début on fait list_push_front
    list_push_front(self, value); 
  }else if(index == list_size(self)){                         //sinon si on veut insérer à la fin on fait list_push_back
    list_push_back(self, value);
  }else{
    struct list_node *elt = malloc(sizeof(struct list_node)); //sinon on va allouer un nouveau noeud initialisé avec value
    elt->data = value;
    struct list_node *courant = self->first;
    for(size_t i = 1; i < index; ++i){      //puis on va effectuer un parcours pour faire pointer le next du nouveau noeud au noeud que l'on souhaite
      courant = courant->next;              //le prev du next on va le faire pointer sur nouveau noeud et le next du noeud courant devient le nouveau noeud
    }
    elt->next = courant->next;
    courant->next->prev = elt;
    elt->prev = courant;
    courant->next = elt;
  }
}

void list_remove(struct list *self, size_t index) {
  assert(!list_empty(self));
  assert((int)(index) >= 0);
  assert(index < list_size(self));
  if(index == 0){                             //si on veut supprimer au début on fait list_pop_front
    list_pop_front(self);
  }else if(index == list_size(self)-1){       //si on veut supprimer à la fin on fait list_pop_back
    list_pop_back(self);
  }else{                                      
    struct list_node *courant = self->first;  //sinon on va allouer un noeud courant pour effectuer un parcours
    for(size_t i = 1; i < index; ++i){
      courant = courant->next;
    }
    struct list_node *pop = courant->next;    //on va allouer un noeud pour récupérer le noeud que l'on veut supprimer
    courant->next = pop->next;                //on va modifier le noeud suivant du noeud courant pour qu'il ne pointe plus sur le noeud à supprimer
    pop->next->prev = courant;                //on fait la même chose avec le noeud suivant du noeud courant
    free(pop);
  }
}

int list_get(const struct list *self, size_t index) {
  if(((int)(index) < 0)||(index >= list_size(self))){    //si l'index n'est pas valide on renvoie 0
    return 0;
  }
  if(index == 0){                               //si on recherche le premier élément on renvoie self->first->data
    return self->first->data;
  }
  struct list_node *courant = self->first->next;  //sinon on va effectuer un parcours pour trouver le noeud situé à l'index
  for(size_t i = 1; i < index; ++i){
    courant = courant->next;
  }
  return courant->data;
}

void list_set(struct list *self, size_t index, int value) {
  if(((int)(index )>= 0)&&(index < list_size(self))){                    //on ne va rien faire si l'index n'est pas valide
    if(index == 0){                                               //si on veut modifier le premier éléments on modifie le self->first->data
      self->first->data = value;
    }
    if((index == list_size(self) - 1)||(list_size(self) == 1)){  //si on veut modifier le dernier éléments ou que la liste est de taille 1 alors on modifie le self->last->data
      self->last->data = value;
    }
    struct list_node *courant = self->first->next;               //sinon on va effectuer un parcours un noeud courant pour trouver le noeud à l'index souhaiter puis on va modifier son data
    for(size_t i = 1; i < index; ++i){
      courant = courant->next;
    }
    courant->data = value;
  }
}

size_t list_search(const struct list *self, int value) {
  size_t res = 0;
  struct list_node *courant = self->first;
  while(courant != NULL){                   //on va effectuer un parcours jusqu'à ce que la data du noeud courant est égal à la value et on incrémente de 1 le res à chaque fois
    if(courant->data == value){
      return res;
    }
    courant = courant->next;
    ++res;
  }
  return list_size(self);                    //sinon on renvoie la taille de la liste
}

bool list_is_sorted(const struct list *self) {
  if(list_empty(self)){                       //si la liste est vide alors elle est triée
    return true;
  }
  struct list_node *courant = self->first;    //sinon on va effectuer un parcours on va regarder si la data du noeud courant est bien inférieur ou égal à la data du noeud courant suivant
  while(courant->next != NULL){
    if(courant->data > courant->next->data){
      return false;
    }
    courant = courant->next;
  }
  return true;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
  size_t sz1 = list_size(self) / 2;         //on récupère la taille des listes out1 et out2 en effectuant une modification sur la taille de out1  si la taille de self est impair
  size_t sz2 = sz1;
  if(list_size(self)%2 == 1){
    ++sz1;
  }
  for(size_t i = 0; i < sz1; ++i){  //on va récupérer le premire élément de self, puis le supprimer de la liste et enfin l'ajouter à la fin de out1
    int data = list_get(self, 0);
    list_pop_front(self);
    list_push_back(out1, data);
  }
  for(size_t i = 0; i < sz2; ++i){ //on va récupérer le premire élément de self, puis le supprimer de la liste et enfin l'ajouter à la fin de out2
    int data = list_get(self, 0);
    list_pop_front(self);
    list_push_back(out2, data);
  }
}

void list_merge(struct list *self, struct list *in1, struct list *in2) {
  size_t data;
  while((in1->first != NULL)||(in2->first != NULL)){ //tant que in1 et in2 ne sont pas vide on va effectuer un parcours dans les 2
    if(in1->first == NULL){                           //si in1 est vide alors on va récuperer le premier élément de in2, le supprimer de la liste et l'ajouter à la fin de self
      data = list_get(in2, 0);
      list_pop_front(in2);
      list_push_back(self, data);
    }else if(in2->first == NULL){                     //sinon si in2 est vide alors on va récuperer le premier élément de in1, le supprimer de la liste et l'ajouter à la fin de self
      data = list_get(in1, 0);
      list_pop_front(in1);
      list_push_back(self, data);
    }else{                                          //sinon on va comparer le premier élément de in1 avec celui de in2 pour récupérer le plus petit, puis le supprimer de la liste et enfin l'ajouter à la fin de self
      if(in1->first->data < in2->first->data){
        data = list_get(in1, 0);
        list_pop_front(in1);
        list_push_back(self, data);
      }else{
        data = list_get(in2, 0);
        list_pop_front(in2);
        list_push_back(self, data);
      }
    }
  }
}

void list_merge_sort(struct list *self) {
  if(list_is_sorted(self)){               //si la liste est triée on sort de la fonction
    return;
  }
  if(list_size(self) < 2){               //si la taille est égale à 1 on sort de la fonction
    return;
  }
  struct list in1;                    //sinon on va séparer self en 2 listes avec list_split
  struct list in2;
  list_create(&in1);
  list_create(&in2);
  list_split(self, &in1, &in2);
  list_merge_sort(&in1);            //effectuer récursivement list_merge_sort sur in1 et in2
  list_merge_sort(&in2);
  list_merge(self, &in1, &in2);     //puis fusionner avec in1 et in2 trier
  list_destroy(&in1);               //enfin detruire in1 et in2
  list_destroy(&in2);
}

/*
 * tree
 */

void tree_create(struct tree *self) {
  self->root = NULL;
}

void node_destroy(struct tree_node *self){
  if((self->left == NULL)&&(self->right == NULL)){
    free(self);
    self = NULL;
  }else if(self->left == NULL){
    struct tree_node *SAD = self->right;
    
    node_destroy(SAD);
    free(self);
  }else if(self->right == NULL){
    struct tree_node *SAG = self->left;
    
    node_destroy(SAG);
    free(self);
  }else{
    struct tree_node *SAG = self->left;
    struct tree_node *SAD = self->right;
    
    node_destroy(SAG);
    node_destroy(SAD);
    free(self);
  }
}

void tree_destroy(struct tree *self) {
  assert(self != NULL);
  if(tree_empty(self)){
    return;
  }
  if(tree_size(self) == 1){
    free(self->root);
    self->root = NULL;
    return;
  }
  node_destroy(self->root);
  self->root = NULL;
}



bool tree_contains(const struct tree *self, int value) {
  assert(self != NULL);
  struct tree_node *courant = self->root;
  while((courant != NULL)){              
    if(courant->data==value){            
      return true;
    }
    if(value < courant->data){
      courant = courant->left;
    }else{
      courant = courant->right;
    }
  }
  return false;
}

struct tree_node *node_insert(struct tree_node *self, int value){
  if(self == NULL){                                               //si le noeud est nul on va allouer un noeud en initialisant son data à la valeur et son sous arbre gauche et droite à nul
    struct tree_node *node = malloc(sizeof(struct tree_node));
    node->left = NULL;
    node->right = NULL;
    node->data = value;
    return node;
  }
  if(value < self->data){                                         //si la valeur est plus petite que la valeur du noeud on va insérer dans le sous arbre gauche
    self->left = node_insert(self->left, value);
    return self;
  }
  if(value > self->data){                                         //si la valeur est plus grande que la valeur du noeud on va insérer dans le sous arbre droit
    self->right = node_insert(self->right, value);
    return self;
  }
  return self;
}

bool tree_insert(struct tree *self, int value){
  if(tree_contains(self, value)){                       //on vérifie si la valeur est déjà présente ou non
    return false;
  }
  self->root = node_insert(self->root, value);          //sinon on va insérer récursivement depuis la racine
  return true;
}

struct tree_node *node_delete_minimum(struct tree_node *self, struct tree_node **min){
  if(self->left == NULL){
    struct tree_node *right = self->right;
    self->right = NULL;
    *min = self;
    return right;
  }
  self->left = node_delete_minimum(self->left, min);
  return self;
}

struct tree_node *node_delete(struct tree_node *self){
  struct tree_node *left = self->left;
  struct tree_node *right = self->right;
  free(self);
  self = NULL;
  if((left == NULL)&&(right == NULL)){            //si le noeud est une feuille on retourne nul
    return NULL;
  }
  if(left == NULL){                               //si le sous arbre gauche est vide on retourne le sous arbre droit
    return right;
  }
  if(right == NULL){                              //si le sous arbre droit est vide on retourne le sous arbre gauche
    return left;
  }
  right = node_delete_minimum(right, &self);      //si le sous arbre gauche et droit ne sont pas vide les deux on va rechercher les minimum dans le sous arbre droit pour le placer à la place du noeud
  self->left = left;
  self->right = right;
  return self;
}

struct tree_node *node_remove(struct tree_node *self, int value){
  if(self == NULL){                                   //si le noeud est null on renvoie null car le parent est une feuille
    return NULL;
  }
  if(value < self->data){                             //si la valeur est plus petite que la valeur du noeud on supprimer dans le sous arbre gauche
    self->left = node_remove(self->left, value);
    return self;
  }
  if(value > self->data){                            //si la valeur est plus grande que la valeur du noeud on va supprimer dans le sous arber droit
    self->right = node_remove(self->right, value);
    return self;
  }
  return node_delete(self);                          //on a atteint la valeur donc on va supprimer le noeud
}

bool tree_remove(struct tree *self, int value){
  assert(!tree_empty(self));
  if(!tree_contains(self, value)){                    //on vérifie si la valeur est présente ou non
    return false;
  }
  self->root = node_remove(self->root, value);        //sinon on va supprimer récursivement depuis la racine
  return true;
}

bool tree_empty(const struct tree *self) {
  return (self->root == NULL);
}

int node_size(const struct tree_node *self){
  if(self == NULL){                                         //si le noeud est une feuille on retourne 0
    return 0;
  }
  return 1 + node_size(self->left) + node_size(self->right);  //on retourne récursivement node_size sur le sous arbre gauche et droit avec plus 1
}

size_t tree_size(const struct tree *self){
  assert(self != NULL);
  return node_size(self->root);
}

size_t tree_height_rec(const struct tree_node *self){
  if(self == NULL){                                     //si le noeud est une feuille on retourne 0
    return 0;
  }
  size_t hSAG = tree_height_rec(self->left) + 1;       //on calcule la hauteur du sous arbre gauche plus 1
  size_t hSAD = tree_height_rec(self->right) + 1;      //on calcule la hauteur du sous arbre droit plus 1
  if(hSAG >= hSAD){                            //si la hauteur du saous arbre gauche est plus grand on le retourne
    return hSAG;
  }                                            //sinon on retourne le sous arbre droit
  return hSAD;
}

size_t tree_height(const struct tree *self) {
  return tree_height_rec(self->root);
}

void node_walk_pre_order(const struct tree_node *self, tree_func_t func, void *user_data){
  if(self == NULL){
    return;
  }
  func(self->data, user_data);
  node_walk_pre_order(self->left, func, user_data);
  node_walk_pre_order(self->right, func, user_data);
}

void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {
  node_walk_pre_order(self->root, func, user_data);
}

void node_walk_in_order(const struct tree_node *self, tree_func_t func, void *user_data){
  if(self == NULL){
    return;
  }
  node_walk_in_order(self->left, func, user_data);
  func(self->data, user_data);
  node_walk_in_order(self->right, func, user_data);
}

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
  node_walk_in_order(self->root, func, user_data);
}

void node_walk_post_order(const struct tree_node *self, tree_func_t func, void *user_data){
  if(self == NULL){
    return;
  }
  node_walk_post_order(self->left, func, user_data);
  node_walk_post_order(self->right, func, user_data);
  func(self->data, user_data);
}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
  node_walk_post_order(self->root, func, user_data);
}
