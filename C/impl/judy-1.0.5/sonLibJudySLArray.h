#ifndef SONLIB_JUDYSLARRAY_H_
#define SONLIB_JUDYSLARRAY_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Judy.h"

#ifdef __cplusplus
extern "C" {
#endif	


int stjudy_equalKey(const void *key1, const void *key2);


//Constructs an empty JudySL array
Pvoid_t stjudy_construct();

//Frees the passed in JudySL array
void stjudy_destruct(Pvoid_t *JSLArray);

//Insert element, overiding if already present.
void stjudy_insert(Pvoid_t  *JSLArray, void *key, void *value);

//Search for value, returns null if not present.
Pword_t stjudy_search(Pvoid_t *JSLArray, void *key);

//Removes element, DOES NOT RETURN REMOVED VALUE
void stjudy_remove(Pvoid_t *JSLArray, void *key);

//Same as judy_remove
void stjudy_removeAndFreeKey(Pvoid_t *JSLArray, void *key);

//Defunct. Judy array cannot return size unless it is being destroyed
void stjudy_size(Pvoid_t *JSLArray);

//Search (exclusive) for the next key present that is greater than the passed key string
uint8_t stjudy_getNextKey(Pvoid_t *JSLArray, void *key);

//Returns value of the associated next key
PWord_t stjudy_getNextValue(Pvoid_t *JSLArray, void *key);

//Print every pair in JudySL in alphanumeric order
void stjudy_printAll(Pvoid_t *JSLArray)

#ifdef __cplusplus
}
#endif
#endif


