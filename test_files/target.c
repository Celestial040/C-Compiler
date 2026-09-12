int num1;
static int num2;
int static num3;
const int num4 = 10;
int const num5 = 10;
static const int num6 = 10;
const static int num7 = 10;
int static const num8 = 10;
extern volatile int num9;
volatile int extern num10;
auto int num12;
register int num13;
typedef int MyInt;
typedef int (*FnPtr)(int);
inline int fn_inline(void) { return 0; }


int *p1;
int const *p2;
const int *p3;
int * const p4 = &num1;
const int * const p5 = &num1;
int * volatile p6;
int * restrict p7;
int **p8;
int * const * volatile p9;

int arr1[10];
int arr2[2][3];
int arr3[];
int (*arr_ptr)[10];
int *ptr_arr[10];
int a1, *a2, a3[10];

int fn1(int a, int b);
int fn2(int);
int fn3(int [static 10]);
int fn4(int [*]);
int fn5();
int fn6(int a, ...);
int (*fn_ptr)(int);
int (*fn_ptr_arr[5])(int);
int (*(*fn_complex)(void))(int);

struct S1 { int a; };
struct S2 { int a : 4; };
struct S3 { unsigned int a : 1; };
struct S4 { signed int : 0; };
struct S5 { int n; int data[]; };
struct Node { int val; struct Node *next; };
union U1 { int a; float b; };

enum E1 { E1_A, E1_B, E1_C };
enum E2 { E2_X = 1, E2_Y = 2 };

(int)x;
(unsigned int)x;
(int *)x;
(int (*)(int))x;
(int){10};
(int[]){1, 2, 3};
(int[2]){1, 2};
(int[]){[2] = 5};
(struct S1){.a = 1};

sizeof(int);
sizeof(int *);
sizeof(int[10]);
sizeof x;

int arr4[5] = {[2] = 5, [4] = 10};
struct S1 s1 = {.a = 1};
struct Outer { struct S1 inner; int arr[3]; };
struct Outer o1 = {.inner.a = 1, .arr[1] = 5};

num1 = 5;
num1 += 5;
num1 -= 5;
num1 *= 5;
num1 /= 5;
num1 %= 5;
num1 &= 5;
num1 |= 5;
num1 ^= 5;
num1 <<= 2;
num1 >>= 2;
++num1;
num1++;
--num1;
num1--;
*p1 = 5;
(*p1)++;
*p1++;
++*p1;
arr1[0] = 5;
*arr1 = 5;
*(arr1 + 1) = 5;

num1 + num2;
num1 - num2;
num1 * num2;
num1 / num2;
num1 % num2;
num1 & num2;
num1 | num2;
num1 ^ num2;
num1 << num2;
num1 >> num2;
~num1;
!num1;
+num1;
-num1;
num1 == num2;
num1 != num2;
num1 < num2;
num1 <= num2;
num1 > num2;
num1 >= num2;
num1 && num2;
num1 || num2;
num1 ? num2 : num3;
(num1, num2);

fn1(num1, num2);
s1.a;
struct S1 *ps1 = &s1;
ps1->a;
(*ps1).a;

int lit_dec = 42;
int lit_hex = 0x2A;
int lit_oct = 052;
unsigned int lit_u = 42u;
long lit_l = 42l;
long long lit_ll = 42ll;
unsigned long long lit_ull = 42ull;
float lit_f = 3.14f;
double lit_d = 3.14;
long double lit_ld = 3.14l;
char lit_c = 'a';
char *lit_s = "hello";
char *lit_s2 = "hello" " world";

void fn_statements(void) {
    if (num1 > 0) {
        num1 = 1;
    } else {
        num1 = 0;
    }

    switch (num1) {
        case 1:
            num1 = 10;
            break;
        default:
            num1 = 0;
            break;
    }

    while (num1 > 0) {
        num1--;
    }

    do {
        num1++;
    } while (num1 < 10);

    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;
        if (i == 8) break;
        num1 += i;
    }

    for (;;) {
        break;
    }

    goto end;
end:
    ;

    return;
}

int fn_return_val(void) {
    return num1;
}

char lit_nl = '\n';
char lit_null = '\0';
char lit_hex_esc = '\x41';
char lit_oct_esc = '\101';
wchar_t lit_wc = L'a';
wchar_t *lit_ws = L"hello";

char str_arr[] = "hello";
int arr5[2][3] = {{1, 2, 3}, {4, 5, 6}};
int arr6[3][3] = {{1}, {2}, {3}};
char *str_arr2[] = {"a", "b", "c"};

typedef struct { int x; int y; } Point;
struct S6;
struct S6 { int x; };
typedef struct S1 S1;

enum { ANON_A, ANON_B, ANON_C };
typedef enum { RED, GREEN, BLUE } Color;

void *vp;
int *p10;
static inline int fn_static_inline(int x) { return x; }
struct S1 fn_ret_struct(void);
void fn_struct_param(struct S1 s);
struct S1 arr_of_struct[10];

void fn_scope_demo(void) {
    static int counter = 0;
    counter++;

    int x = 1;
    {
        int x = 2;
        x++;
    }
}

int (*fn_ptr_arr2[])(int) = { fn2, fn2 };
FnPtr fp = fn2;
&fn1;

p1 + 1;
p1 - 1;
p1 - p10;
p1[0];
s1.a += 5;
arr1[0] += 5;
&arr1[0];
&s1.a;

num1 ? num2 : num3 ? num1 : num2;

_Pragma("pack(1)");
int caf\u00e9;
