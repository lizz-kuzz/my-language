#include "stack.hpp"
#include "debug.hpp"
#include "utils_stk.hpp"


static int file_status = FILE_CLOSE;
FILE *logs_;

#if MODE == MODE_CANARY_ON || MODE == MODE_HASH_CANARY_ON
elem_data_t *create_calloc_data(stack *stk) {

    unsigned long long *data = (unsigned long long *) calloc(1,(sizeof(unsigned long long) + sizeof(elem_data_t)*stk->capacity + sizeof(unsigned long long)));
    
    data[0] = CANARIES_LEFT;
    data++;

    char *point = (char *)data;
    point += stk->capacity*sizeof(elem_data_t);
    elem_canary_t *point_ = (elem_canary_t *)point;
    *point_ = CANARIES_RIGHT;

    return (elem_data_t *)data;
}
#endif

#if MODE != MODE_RELEASE
void fill_data(stack *stk) {
    for (unsigned i = stk->size; i < stk->capacity; i++) {
            stk->data[i] = POIZON;
    }
}
#endif
static void open_file() {

    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/processor/res/log.txt";
    // const char *LOG_FILE = "C://Users//User//Desktop//programs//stack//log.txt";
    
    if (file_status == FILE_CLOSE) {
        logs_ = fopen(LOG_FILE, "w");
        assert(logs_ != nullptr && "coudn't open file");

        if (logs_ == nullptr)
            printf("Could not open file.\n");

        file_status = 1;
    } else if (file_status == FILE_CLOSE_ADD){
        logs_ = fopen(LOG_FILE, "a");
        assert(logs_ != nullptr && "coudn't open file");

        if (logs_ == nullptr)
            printf("Could not open file.\n");

        file_status = 1;
    }

}

#if MODE != MODE_RELEASE
void stack_ctor_(stack *stk, size_t capacity, const char *func, int line, const char *name_file) 
#else 
void stack_ctor_(stack *stk, size_t capacity) 
#endif
{
    
    #if MODE != MODE_RELEASE
    open_file();
    #endif

    #if MODE != MODE_RELEASE
        stk->info.LINE = line;
        stk->info.FUNC = func;
        stk->info.NAME_FILE = name_file; 
    #endif
    stk->capacity = capacity;


    #if MODE == MODE_HASH_CANARY_ON || MODE == MODE_CANARY_ON
        stk->data = create_calloc_data(stk);
    #else 
        stk->data = (elem_data_t *) calloc(capacity + 1, sizeof(elem_data_t));
    #endif
    #if MODE != MODE_RELEASE
        fill_data(stk);
    #endif
    stk->size = 0;

    #if MODE == MODE_HASH_CANARY_ON || MODE == MODE_CANARY_ON
        stk->canaries_left  = CANARIES_LEFT;
        stk->canaries_right = CANARIES_RIGHT;
    #endif

    #if MODE == MODE_HASH_CANARY_ON || MODE == MODE_HASH_ON
        stk->hash_stk = 0;
        stk->hash_data = count_hash (stk->data, stk->capacity*sizeof(*stk->data));
        stk->hash_stk  = update_hash(stk);
    #endif
    ASSERT(stk);
  
}

void stack_dtor(stack *stk) {

    #if MODE == MODE_CANARY_ON || MODE == MODE_HASH_CANARY_ON
        stk->data -= sizeof(elem_canary_t);
    #endif

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;

    #if MODE != MODE_RELEASE
        if (file_status == 1) {
            fclose(logs_);
            file_status = 2;
        }
    #endif

}

void stack_push(stack *stk, elem_data_t elem) {

    // ASSERT(stk);

    if (stk->size >= stk->capacity) 
        stack_resize(stk);
    stk->data[stk->size] = elem;
    stk->size++;

    #if MODE == MODE_HASH_ON || MODE == MODE_HASH_CANARY_ON
        stk->hash_stk = 0;
        stk->hash_data = count_hash (stk->data, stk->capacity*sizeof(*stk->data));
        stk->hash_stk  = update_hash(stk);
    #endif
        
    ASSERT(stk);

}

#if MODE == MODE_CANARY_ON || MODE == MODE_HASH_CANARY_ON
elem_data_t *stack_realloc_canari(stack *stk) {

    elem_canary_t *data = (elem_canary_t *)stk->data;
    data--;

    data = (elem_canary_t *) realloc(data, sizeof(elem_canary_t) + sizeof(elem_data_t)*stk->capacity + sizeof(elem_canary_t));

    data[0] = CANARIES_LEFT;
    data++;

    char *point = (char *)data;
    point += stk->capacity*sizeof(elem_data_t);
    elem_canary_t *point_ = (elem_canary_t *)point;
    *point_ = CANARIES_RIGHT;

    return (elem_data_t *)data;
}
#endif

void stack_resize(stack *stk) {

    // ASSERT(stk);

    if (stk->capacity == stk->size) {
        stk->capacity *= MULTIPLE;
    } else if (stk->size + 1 == stk->capacity/MULTIPLE) {
        stk->capacity /= MULTIPLE; 
    }

    #if MODE == MODE_RELEASE || MODE == MODE_HASH_ON
        stk->data = (elem_data_t *) realloc(stk->data, stk->capacity * sizeof(elem_data_t));
    #else  
        stk->data = stack_realloc_canari(stk);
    #endif

    #if MODE != MODE_RELEASE
        fill_data(stk);
    #endif
    
    #if MODE == MODE_HASH_ON || MODE == MODE_HASH_CANARY_ON
        stk->hash_stk = 0;
        stk->hash_data = count_hash (stk->data, stk->capacity*sizeof(*stk->data));
        stk->hash_stk  = update_hash(stk);
    #endif
        
    ASSERT(stk);
}

elem_data_t stack_pop(stack *stk) {
    // ASSERT(stk);

    stk->size--;
    elem_data_t value = stk->data[stk->size];

    stk->data[stk->size] = POIZON;
    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10) 
        stack_resize(stk);
    
    #if MODE == MODE_HASH_ON || MODE == MODE_HASH_CANARY_ON
        stk->hash_stk = 0;
        stk->hash_data = count_hash (stk->data, stk->capacity*sizeof(*stk->data));
        stk->hash_stk  = update_hash(stk);
    #endif
    
    ASSERT(stk);
    return value;
}




