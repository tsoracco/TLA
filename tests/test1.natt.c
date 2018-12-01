#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
int origin_ = 3;

int destination_ = 0;


while (origin_>0) {
origin_ -= 1;

destination_ += 1;

}

printf("%d", destination_);



return 0;
}