#include <stdio.h>
void function_0(int var_0, int* var_1_out) {
int var_2;
var_2=3;
int var_3;
var_3=5;
int var_4;
var_4=var_0+var_3;
int var_1;
var_1=var_4*var_2;
*var_1_out=var_1;
}
int main() {
int var_5;
var_5=5;
int var_6;
function_0(var_5, &var_6);
printf("%d\n", var_6);
return 0;
}
