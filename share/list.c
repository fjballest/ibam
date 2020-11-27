/* ------------------------------
 *
 * File       : @(#) list.c 2.0
 * Project    : LBAM
 * Date       : 9/12/91
 * Module     : Lists (list)
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

/* ========== DEPENDENCIES ========== */

# include "list.h"

/* ========== END OF DEPENDENCIES ========== */


/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

 void *list_aux_ptr;   /* Aux. pointer for macros  */

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */


void list_empty (l_ptr,kill_node)
    list_list_tp *l_ptr;                     /** I/O **/
    void         (*kill_node)(/* void * */); /** I **/
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
{
    void *list__pt1,   /* Auxiliar pointers */
         *list__pt2;

    if (!List_IsEmpty(*l_ptr)) {  
        list__pt1 = List_First(*l_ptr);
        while (list__pt1) {
           list__pt2 = List_Next(list__pt1);
           (*(kill_node))(list__pt1);
           list__pt1 = list__pt2;
        }
    }
    List_Create(*l_ptr);
} /* End of list_empty */


list_list_tp list_split (mainList_ptr,el)
    list_list_tp  *mainList_ptr; /** I/O **/
    list_elem_ptr el;            /** I/O **/
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
 *              '*mainList' to 'secList' and empties the former.
 *
 * ------------------------------ */
{
    void *list__pt1;      /* Auxiliar pointer */
    list_list_tp secList; /* Second list */

    if (!List_IsEmpty(*mainList_ptr) && el ) {  /* both parameters must be NON EMPTY */
        if (el == List_First(*mainList_ptr)) {
            secList = *mainList_ptr;
            List_Create(*mainList_ptr);
         } else { 
            secList = (list_list_tp)el;
            list__pt1 = List_Prev(el);
            List_Prev(el) = (list_elem_ptr)(&secList);
            List_Next(list__pt1) = EMPTY;
        }
    }
    return secList;
} /* End of list_split */


list_list_tp list_hardCopy(org, copyElement, kill_node)
    list_list_tp  org;                                  /** I **/
    list_elem_ptr (*copyElement)(/* list_elem_ptr */);  /** I **/
    void          (*kill_node)(/* void * */);           /** I **/
/* ----------------------------
 * Returns    : list type; destination list.
 * Use        : 'copyElement' is a pointer to a user-implemented function
 *              that phisically duplicates an element. This function 
 *              receives as parameter the pointer to the element to be copied,
 *              and returns the pointer to the copy ('dst'), or EMPTY if an
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
{
    int ok;
    list_elem_ptr orgAct, orgNext, dstAct, dstNext,
                  dst;
    
    ok = (int)(dst = (*copyElement)(org));
    orgAct  = (list_elem_ptr)org;
    orgNext = List_Next(org);
    dstAct  = dst;
    dstNext = List_Next(dstAct) =EMPTY;
    while (ok && (orgNext != EMPTY)) {
        ok = (int)(dstNext = (*copyElement)(orgNext));
        if (ok) {
            List_Next(dstAct) = dstNext;
            List_Prev(dstNext) = dstAct;
            orgAct = orgNext;
            orgNext = List_Next(orgAct);
            dstAct = dstNext;
            List_Next(dstAct) = EMPTY;
        }
    };
    
    if (!ok) {  /* ERROR */
        list_empty (dst,kill_node);
    };
    
    return ((list_list_tp)dst);
    
} /* end of list_hardCopy */


/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */
