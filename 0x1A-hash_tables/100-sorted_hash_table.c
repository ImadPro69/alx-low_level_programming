#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tables.h"

/**
 * shash_table_create - Create a new sorted hash table
 * @size: The size of the hash table
 *
 * Return: Pointer to the created hash table
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = malloc(sizeof(shash_table_t));

	if (ht == NULL)
		return NULL;

	ht->size = size;
	ht->array = calloc(size, sizeof(shash_node_t *));
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - Insert a key/value pair into the sorted hash table
 * @ht: The hash table
 * @key: The key
 * @value: The value
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *new_node, *curr, *prev = NULL;

	if (ht == NULL || key == NULL || *key == '\0')
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	curr = ht->array[index];

	while (curr != NULL && strcmp(curr->key, key) < 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL && strcmp(curr->key, key) == 0)
	{
		free(curr->value);
		curr->value = strdup(value);
		return (1);
	}

	new_node = malloc(sizeof(shash_node_t));
	if (new_node == NULL)
		return (0);

	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = curr;

	if (prev != NULL)
		prev->next = new_node;
	else
		ht->array[index] = new_node;

	if (curr == ht->shead)
		ht->shead = new_node;
	if (curr == NULL)
		ht->stail = new_node;

	if (prev != NULL && prev->snext != NULL)
		prev->snext->sprev = new_node;
	new_node->sprev = prev;
	new_node->snext = curr;

	if (curr != NULL)
		curr->sprev = new_node;

	return (1);
}

/**
 * shash_table_get - Retrieve the value associated with a key from the sorted hash table
 * @ht: The hash table
 * @key: The key
 *
 * Return: The value associated with the key, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *curr;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	curr = ht->array[index];

	while (curr != NULL && strcmp(curr->key, key) < 0)
		curr = curr->next;

	if (curr != NULL && strcmp(curr->key, key) == 0)
		return (curr->value);

	return (NULL);
}

/**
 * shash_table_print - Print the sorted hash table
 * @ht: The hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *curr;

	if (ht == NULL)
		return;

	curr = ht->shead;
	printf("{");

	while (curr != NULL)
	{
		printf("'%s': '%s'", curr->key, curr->value);
		if (curr->snext != NULL)
			printf(", ");
		curr = curr->snext;
	}

	printf("}\n");
}

/**
 * shash_table_print_rev - Print the sorted hash table in reverse order
 * @ht: The hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *curr;

	if (ht == NULL)
		return;

	curr = ht->stail;
	printf("{");

	while (curr != NULL)
	{
		printf("'%s': '%s'", curr->key, curr->value);
		if (curr->sprev != NULL)
			printf(", ");
		curr = curr->sprev;
	}

	printf("}\n");
}

/**
 * shash_table_delete - Delete the sorted hash table
 * @ht: The hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int i;
	shash_node_t *curr, *next;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		curr = ht->array[i];
		while (curr != NULL)
		{
			next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			curr = next;
		}
	}

	free(ht->array);
	free(ht);
}

