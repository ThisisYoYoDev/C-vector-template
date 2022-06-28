# C-vector-template
template in c for vector


## How to install
Just drop the `vector.h` header file in your project.

### Macro definitions

#### **CREATE_VECTOR**
*CREATE_VECTOR allow you to initialize the structure of your vector.*

Example:
```c

typedef struct {
    int x;
    int y;
} point_t;

CREATE_VECTOR(point, point_t);
```
point_t = type of the vector
point = name of the struct
The type of the vector here is ```vector_point_t```

#### **VECTOR_INIT**
*VECTOR_INIT allow you to initialize the variable of the vector and to allocate it.*
VECTOR_INIT has optional parameters either you specify a size of your choice or the size will be that of the BUFFER (128).

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);
    VECTOR_INIT(point, v2, 50);
}
```
point = name of the struct (declare in CREATE_VECTOR)
v1 | v2 = created variable
50 = capacity of the vector

#### **VECTOR_RESERVE**
*VECTOR_RESERVE aKa VECTOR_RESIZE*
VECTOR_RESERVE allow you to realloc your vector for given size.

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_RESERVE(v1, 50);
}
```
v1 = variable of the vector
50 = add 50 elements to the capacity of the vector


#### **VECTOR_PUSH_BACK**
*VECTOR_PUSH_BACK: Push a value at the end of a vector.*
VECTOR_PUSH_BACK can take one or more element to add in the vector.

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_BACK(v1, (point_t){1, 1});
    /* or */
    VECTOR_PUSH_BACK(v1, (point_t){10, 10}, (point_t){5, 5}, (point_t){-999, 999});
}
```


#### **VECTOR_PUSH_AT**
*VECTOR_PUSH_AT: Push a value at a given index.*
Same usage that VECTOR_PUSH_BACK but at a given index.

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_BACK(v1, (point_t){1, 1});
    /* or */
    VECTOR_PUSH_BACK(v1, (point_t){10, 10}, (point_t){5, 5}, (point_t){-999, 999});

    VECTOR_PUSH_AT(v1, 0, (point_t){1, 1});
    /* or */
    VECTOR_PUSH_AT(v1, 3, (point_t){10, 10}, (point_t){5, 5}, (point_t){-999, 999});
}
```
3 = index to push the element

#### **VECTOR_PUSH_FRONT**
*VECTOR_PUSH_FRONT: Push a value at the front of a vector*
Same usage that VECTOR_PUSH_BACK.

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    /* or */
    VECTOR_PUSH_FRONT(v1, (point_t){10, 10}, (point_t){5, 5}, (point_t){-999, 999});
}
```

#### **VECTOR_POP_BACK**
*VECTOR_POP_BACK: Pop a value at the end of a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    VECTOR_POP_BACK(v1);
}
```

#### **VECTOR_POP_FRONT**
*VECTOR_POP_FRONT: Pop a value at the front of a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    VECTOR_POP_FRONT(v1);
}
```

#### **VECTOR_POP_AT**
*VECTOR_POP_AT: Pop a value at a given index.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    VECTOR_POP_AT(v1, 2);
}
```
2 = index to pop

#### **VECTOR_AT**
*VECTOR_AT: Get a value at a given index.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    printf("{%d,%d}", VECTOR_AT(v1, 0).x, VECTOR_AT(v1, 0).y);
}
```

#### **VECTOR_SIZE**
*VECTOR_SIZE: Get the size of a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    printf("Size: %ld\n", VECTOR_SIZE(v1));
}
```

#### **VECTOR_CAPACITY**
*VECTOR_CAPACITY: Get the capacity of a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    printf("Size: %ld\n", VECTOR_CAPACITY(v1));
}
```

#### **VECTOR_FIRST**
*VECTOR_FIRST: Get the first value of a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    printf("FIRST: %d\n", VECTOR_FIRST(v1).x);
}
```

#### **VECTOR_LAST**
*VECTOR_LAST: Get the first value of a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1});
    printf("LAST: %d\n", VECTOR_LAST(v1).y);
}
```

#### **VECTOR_BEGIN**
*VECTOR_BEGIN: Get the begin iterator of a vector*

#### **VECTOR_END**
*VECTOR_END: Get the end iterator of a vector*

#### **VECTOR_CLEAR**
*VECTOR_CLEAR: Clear a vector (set size to 0)*
this macro does not destroy the vector.


#### **VECTOR_FOREACH**
*VECTOR_FOREACH: Iterate over a vector.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_FOREACH(v_int, i) {
        printf("{%d,%d}", VECTOR_AT(v1, i).x, VECTOR_AT(v1, i).y);
    }
}
```

#### **VECTOR_FOREACH_AUTO**
*VECTOR_FOREACH_AUTO: Iterate over a vector and give pointer to type.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_FOREACH_AUTO(v_int, i) {
        printf("{%d,%d}", i->x, i->y);
    }
}
```

#### **VECTOR_FOREACH_AUTO_BACK**
*VECTOR_FOREACH_AUTO_BACK: Iterate over a vector in reverse order and give pointer to type.*
same usage that VECTOR_FOREACH_AUTO

#### **VECTOR_FOREACH_BACKWARD**
*VECTOR_FOREACH_BACKWARD: Iterate over a vector in reverse order.*
same usage that VECTOR_FOREACH

#### **VECTOR_SWAP**
*VECTOR_SWAP: Swap two values at two given indices.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_SWAP(v1, 0, 2);
}
```

#### **VECTOR_MERGE**
*VECTOR_MERGE: Merge two vectors.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);
    VECTOR_INIT(point, v2);

    VECTOR_PUSH_FRONT(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_PUSH_FRONT(v2, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_MERGE(v1, v2);
}
```
v1 = dest
v2 = src

#### **VECTOR_ERASE_IF**
*VECTOR_ERASE_IF: Erase a value (by index) if a condition is valid.*

Example:
```c
void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_BACK(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    bool toto = true;
    printf("AT 3: %d\n", VECTOR_AT(v1, 3).x);
    VECTOR_ERASE_IF(v1, 3, toto == true);
    printf("AT 3: %d\n", VECTOR_AT(v1, 3).x);
}
```

#### **VECTOR_ERASE_ALL_IF**
*VECTOR_ERASE_ALL_IF: Erase all values if a condition is valid.*
Example:
```c
int compare(int a, int b)
{
    return What you want;
}

void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_BACK(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    bool toto = true;
    printf("AT 3: %d\n", VECTOR_AT(v1, 3).x);
    VECTOR_ERASE_ALL_IF(v1, 3, toto == true, compare);
    printf("AT 3: %d\n", VECTOR_AT(v1, 3).x);
}
```

#### **VECTOR_SORT**
*VECTOR_SORT: Sort values in a vector.*
Example:
```c
int compare(int a, int b)
{
    return What you want;
}

void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_BACK(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_SORT(v1, compare);
}
```

#### **VECTOR_DELETE_ARRAY**
*VECTOR_DELETE_ARRAY: Delete a vector array.*

#### **DELETE_VECTOR**
*DELETE_VECTOR: Delete a vector.*

Example:
```c
int compare(int a, int b)
{
    return What you want;
}

void example_vector(void)
{
    VECTOR_INIT(point, v1);

    VECTOR_PUSH_BACK(v1, (point_t){1, 1}, (point_t){2, 2}, (point_t){3, 3}, (point_t){4, 4});
    VECTOR_SORT(v1, compare);
    DELETE_VECTOR(v1);
}
```
