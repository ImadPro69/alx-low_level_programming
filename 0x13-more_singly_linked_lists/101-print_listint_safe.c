#include "lists.h"

/**
 * print_listint_safe - Prints a listint_t linked list safely
 *
 * @head: Pointer to the first node of the list
 *
 * Return: Number of nodes in the list
 */
size_t print_listint_safe(const listint_t *head)
{
	size_t count = 0;
	const listint_t *current, *next;

	if (head == NULL)
		exit(98);

	current = head;
	while (current != NULL)
	{
		count++;
		printf("[%p] %d\n", (void *)current, current->n);
		next = current->next;
		if (next >= current)
		{
			printf("-> [%p] %d\n", (void *)next, next->n);
			exit(98);
		}
		current = next;
	}

	return (count);
}

