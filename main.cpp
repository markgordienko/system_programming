#include <iostream>
#include <ctime>
#define RESET       "\033[0m"
#define BOLDCYAN    "\033[1m\033[36m"
#define RED         "\033[31m"

using namespace std;

int main()
{
    srand(time(0));
    bool isWrong = false;
    int n;
    string isManual;
    cout << "Enter array size: " << endl;
    do {
        cin >> n;
        if (n <= 1) {
            isWrong = true;
            cout << RED << "Array size must be > 1!" << endl;
        } else isWrong = false;
    } while (isWrong);
    long long array[n][n];
    cout << RESET << "Origin array:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = rand() % 9 + 1;
            if (i == j) {
                cout << BOLDCYAN << array[i][j] << "  ";
            } else cout << RESET << array[i][j] << "  ";
        }
        cout << RESET << endl;
    }
    long long *ptr_array = &array[0][0];
    long long *end_array = &array[n-1][n-1];
    asm(
    "mov $8, %%rax\n\t"             //write 8 to rax (array element step value)
    "mulq %[n]\n\t"                 //multiple rax by n (array string step value)
    "mov %[ptr_array], %%rbx\n\t"   //write pointer to 1st element to rbx
    "mov %%rbx, %%rcx\n\t"          //write rbx to rcx
    //getting next pivot element
    "add $8, %%rcx\n\t"             //add 8 to rcx (move cursor 1 element right)
    "add %%rax, %%rcx\n\t"          //add rax (holds an array string step value) to rcx (move cursor 1 element down)
    "push %%rcx\n\t"                //push rcx to stack
    "push %%rax\n\t"                //push rax to stack
    "mov %[n], %%rcx\n\t"           //write n to rcx
    "dec %%rcx\n\t"                 //decrement rcx (n - 1)
    "mul %%rcx\n\t"                 //multiple rax by rcx (<array string step value> * <n - 1>)
    "mov %[ptr_array], %%rdx\n\t"   //write first element address to rdx
    "add %%rax, %%rdx\n\t"          //add rax to rdx (getting first element in the last string address)
    "push %%rdx\n\t"                //push rdx to stack
    "mov %%rbx, %%rcx\n\t"          //write rbx to rcx (pivot element)
    "loop_start:\n\t"
    "pop %%rdx\n\t"                 //get first element in the last string address from stack to rdx
    "pop %%rax\n\t"                 //get array string step value from stack to rax
    "add %%rax, %%rcx\n\t"          //add rax to rcx (move rcx cursor 1 element down)
    "push %%rax\n\t"                //push array string step value to stack
    "push %%rdx\n\t"                //push first element in the last string address to stack
    "add $8, %%rbx\n\t"             //add 8 to rbx (move rbx cursor 1 element right)
    //swap rbx and rcx values
    "mov (%%rcx), %%rdx\n\t"
    "mov (%%rbx), %%rsi\n\t"
    "mov %%rsi, (%%rcx)\n\t"
    "mov %%rdx, (%%rbx)\n\t"
    "pop %%rdx\n\t"                 //get first element in the last string address from stack to rdx
    "cmp %%rcx, %%rdx\n\t"          //check if rcx is at the last string (rdx - rcx ? 0)
    "je curr_end\n\t"               //if rcx is at the last string goto curr_end
    "push %%rdx\n\t"                //push first element in the last string address to stack
    "jmp loop_start\n\t"            //if rcx is not at the last string goto loop_start
    "curr_end:\n\t"
    "add $8, %%rdx\n\t"             //add 8 to rdx (move rdx cursor 1 element right)
    "cmp %%rdx, %[end_array]\n\t"   //check if rdx is at the end_array
    "je end_asm\n\t"                //if rex is at the end_array goto end_asm
    "pop %%rax\n\t"                 //get array string step value from stack to rax
    "pop %%rbx\n\t"                 //get pivot element from stack
    "mov %%rbx, %%rcx\n\t"          //write rbx to rcx
    "add $8, %%rcx\n\t"             //add 8 to rcx (move rcx cursor 1 element right)
    "add %%rax, %%rcx\n\t"          //add rax to rcx (move rcx cursor 1 string down)
    "push %%rcx\n\t"                //push next pivot element to stack
    "mov %%rbx, %%rcx\n\t"          //write rbx to rcx (current pivot)
    "push %%rax\n\t"                //push array string step value to stack
    "push %%rdx\n\t"                //first element in the last string address to stack
    "jmp loop_start\n\t"            //goto loot_start
    "end_asm:\n\t"
    :                                                                   //output
    :[ptr_array]"m"(ptr_array), [end_array]"m"(end_array), [n]"m"(n)    //input
    :"%rax", "%rbx", "%rcx", "rsi", "rdx"                               //clobbered registers
    );
    cout << "Transposed array:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << BOLDCYAN << array[i][j] << "  ";
            } else cout << RESET << array[i][j] << "  ";
        }
        cout << RESET << endl;
    }
    return 0;
}