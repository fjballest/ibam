/* ------------------------------
 *
 * File       : @(#) listmacr.h 1.0
 * Project    : LBAM
 * Date       : 9/12/91
 * Module     : Lists macros (list)
 * Programmer : Dylan L. Hoffman
 *
 * Comments   : Implementation of generic dinamic lists.
 *              The technique used is a double-linked list, so the only
 *              requirements are that the first and second component of every 
 *              element MUST BE, repectively, a pointer to the next and previous
 *              element of the list.
 * 
 * ------------------------------ */

# ifndef __LISTMACR_H
#  define __LISTMACR_H 1


/* ========== DEPENDENCIES ========== */

extern void *list_aux_ptr;   /* Aux. pointer for macros  */

/* ========== END OF DEPENDENCIES ========== */


/* ========== SYMBOL DEFINITIONS ========== */

#define EMPTY 0

/* ========== END OF SYMBOL DEFINITIONS ========== */



/* ========== MACRO DEFINITIONS ========== */

# define List_Create(l)    ((l) = EMPTY)

# define List_IsEmpty(l)   ((l) == EMPTY)

# define List_Next(el)     (*((void **)(el)))

# define List_Prev(el)     (*((void **)(el)+1))

# define List_First(l)     (l)

# define List_Last(l,last)               \
    (last) = (l);                        \
    if (last) while( List_Next(last) )   \
                 (last) = List_Next(last)
    
# define List_Insert(l,el)                   \
    List_Next(el) = (list_elem_ptr)(l);      \
    if (l) List_Prev(List_Next(el)) = (el);  \
    List_Prev(el) = &(l);                    \
    (l) = (el)

# define List_InsertAfter(el_l,el)            \
    if (el_l)  {                              \
       if (List_Next(el_l)) {                 \
          List_Prev(List_Next(el_l)) = (el);  \
       }                                      \
       List_Next(el) = List_Next(el_l);       \
       List_Prev(el) = (el_l);                \
       List_Next(el_l) = (el);                \
    }

# define List_InsertAtEnd(l,el)                                           \
    if (l) {                                                              \
       List_Last( (l) , list_aux_ptr );                                   \
       list_aux_ptr = (list_aux_ptr) ? (list_aux_ptr) : ( (void*)(l) );   \
       List_InsertAfter(list_aux_ptr,el);                                 \
    } else {                                                              \
       List_Insert(l,el);                                                 \
    }

# define List_Extract(el)                                       \
    List_Next(List_Prev(el)) = List_Next(el);                   \
    if (List_Next(el)) List_Prev(List_Next(el)) = List_Prev(el)

# define List_ExtFirst(l)                                                  \
  ( (List_IsEmpty(l)                                                       \
    ? (NULL)                                                               \
    : (list_aux_ptr=List_First(l),                                         \
       List_Next(List_Prev(list_aux_ptr)) = List_Next(list_aux_ptr),       \
       ((List_Next(list_aux_ptr))                                          \
          ? (List_Prev(List_Next(list_aux_ptr)) = List_Prev(list_aux_ptr)) \
          : (NULL)),                                                       \
       list_aux_ptr)                                                       \
      )                                                                    \
  )

# define List_Join(mL,sL)                         \
    if (!List_IsEmpty(sL)) {                      \
       if (!List_IsEmpty(mL)) {                   \
          List_Last((mL),list_aux_ptr);           \
          List_Next(list_aux_ptr)=(sL);           \
          List_Prev(List_First(sL))=list_aux_ptr; \
          List_Create(sL);                        \
       } else {                                   \
          (mL)=(sL);                              \
          List_Create(sL);                        \
       }                                          \
    }


/* ========== END OF MACRO DEFINITIONS ========== */


# endif


