#include "lists.h"

/**
 * free_listint - Frees a listint_t list.
 * @head: Pointer to the head node of the list.
 *
 * Return: void
 */
void free_listint(listint_t *head)
{
	listint_t *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

