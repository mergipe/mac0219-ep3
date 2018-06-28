#include <cstdio>
#include <cstdint>
#include <cstdlib>

#include <argp.h>
#include <cinttypes>

// Número de argumentos na linha de comando.
static const int arg_num = 3;

static char doc[] =
    "Esse programa...";

static char args_doc[] = "N k m";

static struct argp_option options[] = 
{
    {0,   0, 0, 0,               "ARGS:"},
    {"N", 0, 0, OPTION_DOC |
                OPTION_NO_USAGE, "número de pontos amostrados aleatoriamente"},
    {"k", 0, 0, OPTION_DOC |
                OPTION_NO_USAGE, "constante inteira"},
    {"M", 0, 0, OPTION_DOC |
                OPTION_NO_USAGE, "constante inteira"},
    {0}
};

struct arguments
{
    char *args[3];
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = (struct arguments *) state->input;

    switch(key)
    {
        case ARGP_KEY_ARG:
        {
            if (state->arg_num >= arg_num)
                argp_state_help(state, stderr, ARGP_HELP_STD_HELP);

            arguments->args[state->arg_num] = arg;

            break;
        }

        case ARGP_KEY_END:
        {
            if (state->arg_num < arg_num)
                argp_state_help(state, stderr, ARGP_HELP_STD_HELP);

            break;
        }

        default:
        {
            return ARGP_ERR_UNKNOWN;
        }
    }

    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv)
{
    struct arguments args;
    uint64_t N;
    int k, M;
    char *end_N, *end_k, *end_M;

    argp_parse(&argp, argc, argv, 0, 0, &args);
    N = strtol(args.args[0], &end_N, 10);
    k = strtol(args.args[1], &end_k, 10);
    M = strtol(args.args[2], &end_M, 10);

    if (*end_N != '\0' || *end_k != '\0' || *end_M != '\0')
    {
        argp_help(&argp, stderr, ARGP_HELP_STD_HELP, "main");
    }

    return EXIT_SUCCESS;
}
