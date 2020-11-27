
/* ------------------------------
 *
 * File       : @(#) list.h 2.0
 * Project    : LBAM
 * Date       : 9/12/91
 * Module     : Lists (list; Header)
 * Programmer : Dylan L. Hoffman
 *
 * Comments   : Implementation of generic dinamic lists.
 *              The technique used is a double-linked list, so the only
 *              requirements are that the first and second component of every element
 *              MUST BE, repectively, a pointer to the next and previous element
 *              of the list. This allows merging different kinds of types in the
 *              same list.
 * 
 * ------------------------------ */

# ifndef __LIST_H
#  define __LIST_H 1

/* ========== DEPENDENCIES ========== */

# include "listmacr.h"

/* ========== END OF DEPENDENCIES ========== */



/* ========== TYPE DEFINITIONS ========== */

    typedef void **list_list_tp;     /* Generic list type     */
    typedef void *list_elem_ptr;     /* List element pointer  */

/* ========== END OF TYPE DEFINITIONS ========== */


/* ========== PROTOTYPES ========== */

/* 
void List_Create (
    list_list_tp l; ** O **
);
 * ** MACRO **
 * Parameters : 'l' is a list type.
 * Comments   : Initializes a list to EMPTY.
 *
 * ------------------------------ */

/*
int List_IsEmpty (
    list_list_tp l; ** I **
);
 * ** MACRO **
 * Returns    : TRUE if 'l' is empty; FALSE if not.
 * Parameters : 'l' is a list type.
 *
 * ------------------------------ */

/*
void List_Insert (
    list_list_tp  l;   ** I/O **
    list_elem_ptr el;  ** I **
);
 * ** MACRO **
 * Use        : for example:  " List_Insert(my_list , (list_elem_ptr)my_element)".
 * Parameters : 'l' is a list type; 'el' is an element type.
 * Comments   : Inserts the element 'el' at the START of the list 'l'.
 *
 * ------------------------------ */

/*
void List_InsertAtEnd (
    list_list_tp  l;   ** I/O **
    list_elem_ptr el;  ** I **
);
 * ** MACRO **
 * Use        : for example:  " List_InsertAtEnd(my_list , (list_elem_ptr)my_element)".
 * Parameters : 'l' is a list type; 'el' is an element type.
 * Comments   : Inserts the element 'el' at the END of the list 'l'.
 *
 * ------------------------------ */

/*
void List_InsertAfter (
    list_elem_ptr el_l; ** I/O **
    list_elem_ptr el;   ** I **
);
 * ** MACRO **
 * Use        : for example:  " List_InsertAtEnd(a_list_elem , (list_elem_ptr)my_element)".
 * Parameters : 'el_l' is an element of a list; 'el' is an element type.
 * Comments   : Inserts the element 'el' just after 'el_l' in itrs list.
 *
 * ------------------------------ */

/*
void List_Extract (
    list_elem_ptr el; ** I **
);
 * ** MACRO **
 * Use        : for example: "List_Extract(my_list , (list_elem_ptr)an_element); "
 * Parameters : 'el' is an element type;
 * Comments   : Extracts the element 'el' from its list, or nothing if
 *              it is empty.
 *
 * ------------------------------ */

/*
list_elem_ptr List_ExtFirst (
    list_list_tp l; ** I/O **
);
 * ** MACRO **
 * Returns    : An element; NULL if error.
 * Use        : for example: "my_elem=List_ExtFirst(my_list); "
 * Parameters : 'l' is a list type.
 * Comments   : Extracts and returns the first element of 'l', or nothing if
 *              it is empty.
 *
 * ------------------------------ */

void list_empty (/*
    list_list_tp *l_ptr;               ** I/O **
    void         (*kill_node)(void *); ** I **
*/);
/* ------------------------------
 * Use        : 'kill_node' is the pointer to the user-implemented function 
 *              that removes the element from memory. The parameter of this function
 *              is the pointer to the element.
 *              For example:  "list_empty(&my_list,kill_my_node) "
 * Parameters : 'l_ptr' is a pointer to a list; 'kill_node' is a function that removes 
 *              elements from memory.
 * Comments   : Empties the list 'l'. 
 *              WARNING: All the elements in the list are phisically removed from
 *                       memory.
 *
 * ------------------------------ */

/*
list_elem_ptr List_First (
    list_list_tp l; ** I **
);
 * ** MACRO **
 * Returns    : list element; NULL if 'l' is empty.
 * Parameters : 'l' is a list type.
 * Comments   : Returns the first element of the list 'l'.
 *
 * ------------------------------ */

/*
void List_Last (
    list_list_tp l;    ** I **
    list_elem_tp last; ** O **
);
 * ** MACRO **
 * Parameters : 'l' is a list type;
 *              'last' is the last elem. of the list; NULL if 'l' is empty.
 * Comments   : Returns the last element of the list 'l'.
 *
 * ------------------------------ */

/*
list_elem_ptr List_Next (
    list_elem_ptr el; ** I **
);
 * ** MACRO **
 * Returns    : list element; NULL if 'l' is empty.
 * Parameters : 'el' is an element type.
 * Comments   : Returns the next element of 'el'.
 *
 * ------------------------------ */

/*
list_elem_ptr List_Prev (
    list_elem_ptr el; ** I **
);
 * ** MACRO **
 * Returns    : list element; NULL if 'l' is empty.
 * Parameters : 'el' is an element type.
 * Comments   : Returns the previous element of 'el'.
 *
 * ------------------------------ */

/*
void List_Join (
    list_list_tp mainList;  ** I/O **
    list_list_tp secList;   ** I **
);
 * ** MACRO **
 * Use        : For example:  "list_join(first_list,second_list); "
 * Parameters : 'mainList' and 'secList' are list types.
 * Comments   : The two lists are joined in just one list. The second list
 *              ('secList') is inserted just AFTER 'mainList'. 
 *              After the operation, 'secList' emptied.
 *
 * ------------------------------ */

list_list_tp list_split (/*
    list_list_tp  *mainList_ptr; ** I/O **
    list_elem_ptr el;            ** I/O **
*/);
/* -----------------------------
 * Returns    : A list type
 * Use        : For example:  "secondList=list_split(&my_list,(list_elem_ptr)element); "
 * Parameters : 'mainList_ptr' is a pointer to a list;
 *              'el' is an element type.
 * Comments   : Splits the list 'mainList' into two different lists.
 *              The first one is still named 'mainList' and starts at the same
 *              element, but finishes in the previous element to 'el'.
 *              The second list starts on 'el' and finishes at 
 *              the last element of the initial list.
 *              Special case: when (el==List_First(*mainList_ptr)), this function copies
 *              'mainList' to 'secList' and empties the former.
 *
 * ------------------------------ */

list_list_tp list_hardCopy ( /*
    list_list_tp  org;                           ** I **
    list_elem_ptr (*copyElement)(list_elem_ptr), ** I **
    void          (*kill_node)(void *)           ** I **
*/);
/* ----------------------------
 * Returns    : list type; destination list.
 * Use        : 'copyElement' is a pointer to a user-implemented function
 *              that phisically duplicates an element. This function 
 *              receives as parameter the pointer to the element to be copied,
 *              and returns the pointer to the copy ('dst'), or NULL if an
 *              error occurs.
 *              'kill_node' is the pointer to the user-implemented function 
 *              that removes the element from memory. The parameter of this function
 *              is the pointer to the element. It's used for cleaning up the
 *              memory if an error occurs during the copying.
 *              For example: " copy = list_hardCopy(my_list, copy_my_elem,kill_my_node); "
 * Parameters : 'org': list type; list to be copied.
 *              'copyElement': a function that duplicates elements.
 *              'kill_node' is a function that removes elements from memory.
 * Comments   : This function "phisically" duplicates the list 'org' using the 
 *              function 'copyElement', and returns the copy, or EMPTY if an error
 *              occurs (usually not enough memory).
 *
 * ------------------------------ */


/* ========== END OF PROTOTYPES ========== */





# endif
