#include <stdio.h>
#include <regex.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    char *pattern = "mul\\([0-9]+,[0-9]+\\)";
    regex_t re;

    if (regcomp(&re, pattern, REG_EXTENDED) != 0)
    {
        printf("Error with making Regex");
        return 1;
    }

    int summed_mul = 0;

    const unsigned MAX_LENGTH = 1000000;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file))
    {
        const char *s = buffer;
        regmatch_t pmatch[10000];

        printf("String = \"%s\"\n", buffer);
        printf("Matches:\n");

        while (regexec(&re, s, 1, pmatch, 0) == 0)
        {
            regoff_t off = pmatch[0].rm_so + (s - buffer);
            regoff_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
            printf("offset = %lld; length = %lld\n", off, len);

            int num_length = len - 5;
            char nums[num_length];
            sprintf(nums, "%.*s", num_length, s + pmatch[0].rm_so + 4);
            printf("substring = \"%s\"\n", nums);

            const char sep[2] = ",";
            int first_num = atoi(strtok(nums, sep));
            int second_num = atoi(strtok(NULL, sep));

            summed_mul += first_num * second_num;

            s += pmatch[0].rm_eo;
        }
    }

    printf("Summed mul: %d\n", summed_mul);

    regfree(&re);
    fclose(file);

    return 0;
}
