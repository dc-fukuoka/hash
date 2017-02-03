#ifndef HASH_H
#define HASH_H

struct list_t;
typedef struct list_t list_t;

/* hash table */
typedef struct hashtable_t {
	int size;
	int count;
	list_t **table;
} hashtable_t;

/* user functions */
hashtable_t* gen_hashtable(int size);
void         clear_hashtable(hashtable_t *hp);
int          get_hashval(hashtable_t *hp, const char *key);
int          getval_hashtable(hashtable_t *hp, const char *key, bool *found);
bool         add_hashtable(hashtable_t *hp, const char *key, int val);
bool         del_hashtable(hashtable_t *hp, const char *key);
#endif /* HASH_H */
