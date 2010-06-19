#include "sonLibExcept.h"
#include <stdlib.h>
#include "stSafeC.h"

/**
 * Exception object that is thrown.
 * @ingroup stExcept
 */
struct stExcept {
    const char *id;          /**< symbolic exception id */
    const char *msg;         /**< natural-language error message */
    struct stExcept *cause;  /**< error stack, NULL if no causing errors */
};

/*
 * Exception content Top Of Stack.
 * FIXME: should be in thread-local storage.
 */
struct _stExceptContext *_cexceptTOS = NULL;

stExcept *stExcept_newv(const char *id, const char *msg, va_list args) {
    stExcept *except = stSafeCCalloc(sizeof(stExcept));
    except->id = id;
    except->msg = stSafeCDynFmtv(msg, args);
    return except;
}

stExcept *stExcept_new(const char *id, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    stExcept *except = stExcept_newv(id, msg, args);
    va_end(args);
    return except;
}

stExcept *stExcept_newCausev(stExcept *cause, const char *id, const char *msg, va_list args) {
    stExcept *except = stExcept_newv(id, msg, args);
    except->cause = cause;
    return except;
}

stExcept *stExcept_newCause(stExcept *cause, const char *id, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    stExcept *except = stExcept_newCausev(cause, id, msg, args);
    va_end(args);
    return except;
}

void stExcept_free(stExcept *except) {
    if (except != NULL) {
        if (except->cause != NULL) {
            stExcept_free(except->cause);
        }
        stSafeCFree((char*)except->msg);
        stSafeCFree(except);
    }
}

const char* stExcept_getId(const stExcept *except) {
    return except->id;
}

const char* stExcept_getMsg(const stExcept *except) {
    return except->msg;
}

stExcept *stExcept_getCause(const stExcept *except) {
    return except->cause;
}

void stThrow(stExcept *except) {
    assert(except != NULL);
    if (_cexceptTOS == NULL) {
        stSafeCErr("Exception: %s: %s", except->id, except->msg);
    }
    _cexceptTOS->except = except;
    longjmp(_cexceptTOS->env, 1);
}

void stThrowNew(const char *id, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    stExcept *except = stExcept_newv(id, msg, args);
    va_end(args);
    stThrow(except);
}

void stThrowNewCause(stExcept *cause, const char *id, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    stExcept *except = stExcept_newCausev(cause, id, msg, args);
    va_end(args);
    stThrow(except);
}
