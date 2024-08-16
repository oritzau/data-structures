#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 16
#define DEFAULT_HASHFN strhash

typedef unsigned long (*hashfn_t)(void *);

struct Hashmap {
	void *base;
	hashfn_t hashfn;
	int item_size;
	int buckets;
};

struct Hashmap *hm_new(int item_size, int buckets, hashfn_t hashfn);
void hm_free(struct Hashmap *hm);
void *hm_get(struct Hashmap *hm, void *key);
void hm_add(struct Hashmap *hm, void *key, void *value);
unsigned long strhash(void *);

int main(void)
{
	char *names[] = {
		"John",
		"Josh",
		"Juan",
		"Not4Letters",
		"Null",
		"Jmook",
		"Mang0",
		"Bing",
	};
	struct Hashmap *hm = hm_new(sizeof(int), 0, &strhash);
	for (int i = 0; i < sizeof(names) / sizeof(char *); i++)
		hm_add(hm, names[i], &i);
	void *get = hm_get(hm, "Null");
	printf("%d\n", *(int *)get);
	hm_free(hm);
	free(get);
}

struct Hashmap *hm_new(int item_size, int buckets, hashfn_t hashfn)
{
	struct Hashmap *hm = malloc(sizeof *hm);
	hm->item_size = item_size;
	hm->buckets = buckets ? buckets : DEFAULT_CAPACITY;
	hm->base = calloc(item_size, hm->buckets);
	hm->hashfn = hashfn ? hashfn : DEFAULT_HASHFN;
	return hm;
}

void hm_free(struct Hashmap *hm)
{
	free(hm->base);
	free(hm);
}

void *hm_get(struct Hashmap *hm, void *key)
{
	void *result = malloc(sizeof(hm->item_size));
	memcpy(result, ((char*)hm->base) + (hm->hashfn(key) % hm->buckets) * hm->item_size, hm->item_size);
	return result;
}

void hm_add(struct Hashmap *hm, void *key, void *value)
{
	memcpy(((char *)hm->base) + (hm->hashfn(key) % hm->buckets) * hm->item_size, value, hm->item_size);
}

unsigned long strhash(void *key)
{
	unsigned long result = 0;
	int i = 0;
	char *ckey = (char *)key;
	while (ckey[i + 1])
		result = 31 * result + ckey[i++];
	return result;
}
