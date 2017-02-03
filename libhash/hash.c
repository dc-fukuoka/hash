#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

/* list in the hash */
struct list_t {
	char *key;
	int val;
	struct list_t *next;
};

static list_t *add_list(const char *key, const int val, list_t *next)
{
	list_t *lp;
	if (!(lp = (list_t*)malloc(sizeof(*lp)))) {
		return NULL;
	} else {
		if (!(lp->key = (char*)malloc(strlen(key)+1))) {
			free(lp);
			return NULL;
		}
		strcpy(lp->key, key);
		lp->val = val;
		lp->next = next;
	}
	return lp;
}

static void clear_list(list_t *lp)
{
	while (lp) {
		free(lp->key);
		free(lp);
		lp = lp->next;
	}
}

hashtable_t *gen_hashtable(int size)
{
	hashtable_t *hp;
	int i;
	
	if (!(hp= (hashtable_t*)malloc(sizeof(*hp)))) {
		return NULL;
	} else {
		hp->size = size;
		if (!(hp->table =(list_t**)malloc(sizeof((*(hp->table)))*size))) {
			free(hp);
			return NULL;
		}
	}
	for (i=0; i<size; i++)
		hp->table[i] = NULL;
	return hp;
}

void clear_hashtable(hashtable_t *hp)
{
	int i;
	
	for (i=0; i<hp->size; i++)
		clear_list(hp->table[i]);
	free(hp->table);
	free(hp);
}

int get_hashval(hashtable_t *hp, const char *key)
{
	unsigned int val = 0;
	char *pkey, *ckey;
	
        ckey= strdup(key);
	for (pkey=ckey; *pkey!='\0'; pkey++)
		val = (val << 3) + (unsigned int)*pkey;
	free(ckey);
	return val % hp->size;
}

static list_t *search_list(hashtable_t *hp, const char *key, const int hashval)
{
	list_t *lp = hp->table[hashval];
	while(lp) {
		if (!strcmp(lp->key, key))
			return lp;
		lp = lp->next;
	}
	return NULL;
}

int getval_hashtable(hashtable_t *hp, const char *key, bool *found)
{
	int hashval;
	list_t *lp;
	
	hashval = get_hashval(hp, key);
	if ((lp = search_list(hp, key, hashval))) {
		*found = true;
		return lp->val;
	}
	*found = false;
	return -1;
}

bool add_hashtable(hashtable_t *hp, const char *key, int val)
{
	int hashval;
	list_t *lp;

	hashval = get_hashval(hp, key);
	if(!(lp = search_list(hp, key, hashval))) {
		hp->table[hashval] = add_list(key, val, hp->table[hashval]);
		hp->count++;
		return true;
	} else {
		lp->val = val; /* it exists, overwrite */
		return false;
	}
}

bool del_hashtable(hashtable_t *hp, const char *key)
{
	int hashval;
	list_t *lp;
	
	hashval= get_hashval(hp, key);
	if ((lp = hp->table[hashval])) {
		if (!strcmp(lp->key, key)) {
			hp->table[hashval] = lp->next;
			hp->count--;
			free(lp->key);
			free(lp);
			return true;
		}
	} else {
		while (lp->next) {
			list_t *del = lp->next;
			lp->next = lp->next->next;
			hp->count--;
			free(del->key);
			free(del);
			lp = lp->next;
			return true;
		}
	}
	return false;
}
