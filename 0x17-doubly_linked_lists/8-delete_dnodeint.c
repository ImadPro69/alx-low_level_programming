#include "lists.h"

/**
 * delete_dnodeint_at_index - Deletes the node at a given index of a dlistint_t linked list
 * @head: Double pointer to the head node of the list
 * @index: Index of the node to be deleted
 *
 * Return: 1 if succeeded, -1 if failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *current, *prev_node;
	unsigned int i;

	if (head == NULL || *head == NULL)
		return (-1);

	current = *head;
	if (index == 0)
	{
		*head = (*head)->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(current);
		return (1);
	}

	for (i = 0; i < index; i++)
	{
		if (current == NULL)
			return (-1);
		current = current->next;
	}

	prev_node = current->prev;
	prev_node->next = current->next;
	if (current->next != NULL)
		current->next->prev = prev_node;

	free(current);
	return (1);
}
