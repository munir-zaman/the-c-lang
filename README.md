# the-c-lang
The C Programming Language

# Implcit Type Conversions

- https://en.cppreference.com/w/c/language/conversion

Some examples :

- signed integral values usually get converted to unsigned values if both operands have the same rank.
    > If the unsigned type has conversion rank greater than or equal to the rank of the signed type, then the operand with the signed type is implicitly converted to the unsigned type.
    ```c
    #define size(array) (sizeof(array) / sizeof(array[0]))
    int main() {
        int array[] = {1, 2, 3, 4};
        int d = -1;
        if (d < size(array)) printf("...");
    }
    ```
    The `sizeof` operator returns `unsigned int`. `d` is a signed integer and is negative. As both operands have the same rank, 
    `d` will be converted to `unsigned int` losing its original value (this wouldn't have been a problem if `d` was positive 
    as converting it to an `unsigned int` wont change its original value)
