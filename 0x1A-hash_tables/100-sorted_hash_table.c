#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * shash_table_create - Create a sorted hash table
 * @size: The size of the array
 *
 * Return: Pointer to the created hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = NULL;
	unsigned long int i;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - Insert or update a key/value pair in a sorted hash table
 * @ht: The hash table
 * @key: The key string
 * @value: The value corresponding to the key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new_node = NULL, *tmp = NULL, *prev = NULL;
	unsigned long int index = 0;

	if (ht == NULL || key == NULL || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	while (tmp != NULL)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}

	new_node = malloc(sizeof(shash_node_t));
	if (new_node == NULL)
		return (0);

	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;

	if (prev == NULL)
	{
		ht->array[index] = new_node;
	}
	else
	{
		prev->next = new_node;
	}

	/* Insert the new node in the sorted linked list */
	if (ht->shead == NULL)
	{
		ht->shead = new_node;
		ht->stail = new_node;
		new_node->sprev = NULL;
		new_node->snext = NULL;
	}
	else
	{
		tmp = ht->shead;
		while (tmp != NULL && strcmp(key, tmp->key) > 0)
		{
			prev = tmp;
			tmp = tmp->snext;
		}

		if (prev == NULL)
		{
			new_node->sprev = NULL;
			new_node->snext = tmp;
			tmp->sprev = new_node;
			ht->shead = new_node;
		}
		else if (tmp == NULL)
		{
			new_node->sprev = prev;
			new_node->snext = NULL;
			prev->snext = new_node;
			ht->stail = new_node;
		}
		else
		{
			new_node->sprev = prev;
			new_node->snext = tmp;
			prev->snext = new_node;
			tmp->sprev = new_node;
		}
	}

	return (1);
}

/**
 * shash_table_get - Retrieve a value associated with a key in a sorted hash table
 * @ht: The hash table
 * @key: The key string
 *
 * Return: The value associated with the key, or NULL if key is not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *tmp = NULL;
	unsigned long int index = 0;

	if (ht == NULL || key == NULL)
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	while (tmp != NULL)
	{
		if (strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}

	return (NULL);
}

/**
 * shash_table_print - Print a sorted hash table
 * @ht: The hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *tmp = NULL;
	int is_first = 1;

	if (ht == NULL)
		return;

	printf("{");
	tmp = ht->shead;
	while (tmp != NULL)
	{
		if (!is_first)
			printf(", ");
		printf("'%s': '%s'", tmp->key, tmp->value);
		is_first = 0;
		tmp = tmp->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Print a sorted hash table in reverse order
 * @ht: The hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *tmp = NULL;
	int is_first = 1;

	if (ht == NULL)
		return;

	printf("{");
	tmp = ht->stail;
	while (tmp != NULL)
	{
		if (!is_first)
			printf(", ");
		printf("'%s': '%s'", tmp->key, tmp->value);
		is_first = 0;
		tmp = tmp->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Delete a sorted hash table
 * @ht: The hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node = NULL, *tmp = NULL;
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			tmp = node;
			node = node->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
	}

	free(ht->array);
	free(ht);
}

