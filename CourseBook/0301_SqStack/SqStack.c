#include "SqStack.h"

Status InitStack(SqStack* S) {
    if(S == NULL) {
        return ERROR;
    }
    (*S).base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if((*S).base == NULL) {
        exit(OVERFLOW);
    }
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack* S) {
    if(S == NULL) {
        return ERROR;
    }
    
    free((*S).base);
    
    (*S).base = NULL;
    (*S).top = NULL;
    (*S).stacksize = 0;
    
    return OK;
}

Status ClearStack(SqStack* S) {
    if(S == NULL || (*S).base == NULL) {
        return ERROR;
    }
    
    (*S).top = (*S).base;
    
    return OK;
}

Status StackEmpty(SqStack S) {
    if(S.top == S.base) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackLength(SqStack S) {
    if(S.base == NULL) {
        return 0;
    }
    
    return (int) (S.top - S.base);
}

Status GetTop(SqStack S, SElemType* e) {
    if(S.base == NULL || S.top == S.base) {
        return 0;
    }
    *e = *(S.top - 1);
    return OK;
}

Status Push(SqStack* S, SElemType e) {
    if(S == NULL || (*S).base == NULL) {
        return ERROR;
    }
    if((*S).top - (*S).base >= (*S).stacksize) {
        (*S).base = (SElemType*) realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if((*S).base == NULL) {
            exit(OVERFLOW);
        }
        
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    *(S->top++) = e;
    return OK;
}

Status Pop(SqStack* S, SElemType* e) {
    if(S == NULL || (*S).base == NULL) {
        return ERROR;
    }
    
    if((*S).top == (*S).base) {
        return ERROR;
    }
    *e = *(--(*S).top);
    
    return OK;
}

Status StackTraverse(SqStack S, void(Visit)(SElemType)) {
    SElemType* p = S.base;
    
    if(S.base == NULL) {
        return ERROR;
    }
    
    while(p < S.top) {
        Visit(*p++);
    }
    
    printf("\n");
    
    return OK;
}
