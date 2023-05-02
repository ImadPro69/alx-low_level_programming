#include "lists.h"

/**
 * delete_nodeint_at_index - deletes the node at index index of a linked list
 * @head: pointer to a pointer to the first node of the list
 * @index: index of the node to be deleted
 *
 * Return: 1 if succeeded, -1 if failed
 */
int delete_nodeint_at_index(listint_t **head, unsigned int index)
{
	listint_t *current, *temp;
	unsigned int i;

	if (*head == NULL) /* empty list */
		return (-1);

	if (index == 0) /* remove first node */
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
		return (1);
	}

	/* find previous node of the node to be deleted */
	current = *head;
	for (i = 0; i < index - 1 && current != NULL; i++)
		current = current->next;

	if (current == NULL || current->next == NULL) /* index out of range */
		return (-1);

	/* remove node */
	temp = current->next;
	current->next = temp->next;
	free(temp);
	return (1);
}
