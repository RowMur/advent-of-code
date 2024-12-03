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

    char *mul_pattern = "mul\\([0-9]+,[0-9]+\\)";
    regex_t mul_re;
    if (regcomp(&mul_re, mul_pattern, REG_EXTENDED) != 0)
    {
        printf("Error with making Regex");
        return 1;
    }

    char *do_pattern = "do()";
    regex_t do_re;
    if (regcomp(&do_re, do_pattern, REG_EXTENDED) != 0)
    {
        printf("Error with making Regex");
        return 1;
    }

    char *dont_pattern = "don't()";
    regex_t dont_re;
    if (regcomp(&dont_re, dont_pattern, REG_EXTENDED) != 0)
    {
        printf("Error with making Regex");
        return 1;
    }

    int summed_mul = 0;
    int is_enabled = 1;

    const unsigned MAX_LENGTH = 1000000;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file))
    {
        const char *s = buffer;

        regmatch_t mul_pmatch[1];
        regmatch_t do_pmatch[1];
        regmatch_t dont_pmatch[1];

        while (1)
        {
            int mul_status = regexec(&mul_re, s, 1, mul_pmatch, 0);
            int do_status = regexec(&do_re, s, 1, do_pmatch, 0);
            int dont_status = regexec(&dont_re, s, 1, dont_pmatch, 0);

            if (mul_status != 0 && do_status != 0 && dont_status != 0)
            {
                break;
            }

            int next_do = do_pmatch[0].rm_so;
            int next_dont = dont_pmatch[0].rm_so;
            int next_mul = mul_pmatch[0].rm_so;

            if (mul_status != 0)
            {
                next_mul = 100000;
            }
            if (do_status != 0)
            {
                next_do = 100000;
            }
            if (dont_status != 0)
            {
                next_dont = 100000;
            }

            if (do_status == 0 && next_do < next_dont && next_do < next_mul)
            {
                printf("Next do at %d\n", next_do);
                is_enabled = 1;
                s += do_pmatch[0].rm_eo;
                continue;
            }
            else if (dont_status == 0 && next_dont < next_mul)
            {
                printf("Next don't at %d\n", next_dont);
                is_enabled = 0;
                s += dont_pmatch[0].rm_eo;
                continue;
            }

            if (mul_status != 0)
            {
                break;
            }

            if (!is_enabled)
            {
                s += mul_pmatch[0].rm_eo;
                continue;
            }

            regoff_t off = next_mul + (s - buffer);
            regoff_t len = mul_pmatch[0].rm_eo - next_mul;
            printf("offset = %lld; length = %lld\n", off, len);

            int num_length = len - 5;
            char nums[num_length];
            sprintf(nums, "%.*s", num_length, s + mul_pmatch[0].rm_so + 4);
            printf("substring = \"%s\"\n", nums);

            const char sep[2] = ",";
            int first_num = atoi(strtok(nums, sep));
            int second_num = atoi(strtok(NULL, sep));

            summed_mul += first_num * second_num;
            s += mul_pmatch[0].rm_eo;
        }
    }

    printf("Summed mul: %d\n", summed_mul);

    regfree(&mul_re);
    regfree(&do_re);
    regfree(&dont_re);
    fclose(file);

    return 0;
}
