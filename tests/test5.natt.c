#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
int first_ = 2;

int second_ = 4;

int a_ = 0;

int b_ = 1;

char* text_ = "";


if ((first_<second_)&&(!a_)) {
text_ = "less";

} else {}
if ((first_>second_)&&(!a_)) {
text_ = "more";

} else {}

printf("%s", text_);


if (!(!b_)) {
text_ = "changed";

} else {}
printf("%s", text_);



return 0;
}